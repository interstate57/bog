#!/usr/bin/env python3
"""Generate in.txt (100k unique records) and commands.txt (task-style commands)."""
from __future__ import annotations

import json
import random
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
N = 100000
RNG = random.Random(20260329)


def cmp_phone(op: str, lhs_rec: int, rhs_cmd: int) -> bool:
    """Record satisfies 'rec OP cmd' per C++ compare_phone(cmd stored on command)."""
    if op == "eq":
        return lhs_rec == rhs_cmd
    if op == "ne":
        return lhs_rec != rhs_cmd
    if op == "lt":  # rec < cmd  <=>  cmd > rec
        return rhs_cmd > lhs_rec
    if op == "gt":
        return rhs_cmd < lhs_rec
    if op == "le":
        return rhs_cmd >= lhs_rec
    if op == "ge":
        return rhs_cmd <= lhs_rec
    raise ValueError(op)


def cmp_group(op: str, lhs_rec: int, rhs_cmd: int) -> bool:
    return cmp_phone(op, lhs_rec, rhs_cmd)


def cmp_name(op: str, rec_name: str, cmd_name: str) -> bool:
    """strcmp(command.name, record.name) from command.h (field vs threshold on command)."""
    if op == "eq":
        return rec_name == cmd_name
    if op == "ne":
        return rec_name != cmd_name
    if op == "lt":  # strcmp(cmd, rec) > 0  <=>  rec < cmd
        return rec_name < cmd_name
    if op == "gt":  # strcmp(cmd, rec) < 0  <=>  rec > cmd
        return rec_name > cmd_name
    if op == "le":
        return rec_name <= cmd_name
    if op == "ge":
        return rec_name >= cmd_name
    raise ValueError(op)


def simple_like(pattern: str, value: str) -> bool:
    """Subset: supports exact match, prefix%, %suffix, no _ or [...] (stress test only)."""
    if "%" not in pattern and "_" not in pattern and "[" not in pattern:
        return value == pattern
    if pattern.endswith("%") and pattern.count("%") == 1 and "_" not in pattern and "[" not in pattern:
        return value.startswith(pattern[:-1])
    if pattern.startswith("%") and pattern.count("%") == 1:
        return value.endswith(pattern[1:])
    # fallback: conservative
    return False


def apply_atom(
    row: dict,
    field: str,
    op: str,
    val,
) -> bool:
    if field == "phone":
        return cmp_phone(op, row["phone"], int(val))
    if field == "group":
        return cmp_group(op, row["group"], int(val))
    if field == "name":
        if op in ("like",):
            return simple_like(val, row["name"])
        if op in ("nlike",):
            return not simple_like(val, row["name"])
        return cmp_name(op, row["name"], val)
    raise ValueError(field)


def apply_where(row: dict, where) -> bool:
    if where is None:
        return True
    op_a, clauses = where  # op_a is 'and' or 'or'
    outs = [apply_atom(row, f, o, v) for f, o, v in clauses]
    if op_a == "and":
        return all(outs)
    return any(outs)


def sort_key(row: dict, order_keys: list[str]):
    return tuple(row[k] for k in order_keys)


def print_row(row: dict, cols: list[str]) -> str:
    parts = []
    for c in cols:
        if c == "name":
            parts.append(row["name"])
        else:
            parts.append(str(row[c]))
    return " " + " ".join(parts)


def simulate(rows: list[dict], ops: list[dict]) -> tuple[str, int]:
    """Returns (expected stdout without argv line), cumulative select count."""
    data = [dict(r) for r in rows]
    out_lines: list[str] = []
    total_sel = 0
    for op in ops:
        t = op["type"]
        if t == "insert":
            name, phone, group = op["tuple"]
            phone, group = int(phone), int(group)
            if any(
                r["name"] == name and r["phone"] == phone and r["group"] == group
                for r in data
            ):
                pass
            else:
                data.insert(0, {"name": name, "phone": phone, "group": group})
        elif t == "delete":
            where = op.get("where")
            if where is None:
                data.clear()
            else:
                data = [r for r in data if not apply_where(r, where)]
        elif t == "select":
            cols = op["cols"]
            where = op.get("where")
            order = op.get("order")
            # Match C++ list::insert: each match prepended → printed reverse of scan order
            hit = []
            for r in data:
                if apply_where(r, where):
                    hit.insert(0, r)
            if order:
                hit = sorted(hit, key=lambda r: sort_key(r, order))
            if cols == ["*"]:
                cols = ["name", "phone", "group"]
            for r in hit:
                out_lines.append(print_row(r, cols))
            total_sel += len(hit)
        elif t == "quit":
            out_lines.append("")
            break
        else:
            raise ValueError(t)
        # Same as main: printf("\n") after every command except quit (handled above)
        out_lines.append("")
    return "\n".join(out_lines), total_sel


def build_dataset():
    rows = []
    seen = set()
    while len(rows) < N:
        i = len(rows)
        name = f"w{i:05d}" + RNG.choice(["", "x", "yz"])
        phone = 1_000_000 + i * 17 + (RNG.randint(0, 9) if i % 97 == 0 else 0)
        group = (i * 11003 + RNG.randint(0, 31)) % 300_000 + 1
        key = (name, phone, group)
        if key in seen:
            continue
        seen.add(key)
        rows.append({"name": name, "phone": phone, "group": group})
    return rows


def main():
    rows = build_dataset()
    # Anchor rows for deterministic checks (task-style values)
    r0 = rows[0]
    r1 = rows[100]
    r2 = rows[10000]
    r_mid = rows[N // 2]
    max_phone = max(r["phone"] for r in rows)

    ops: list[dict] = [
        {
            "type": "select",
            "cols": ["*"],
            "where": ("and", [("name", "eq", r0["name"])]),
            "order": None,
        },
        {
            "type": "select",
            "cols": ["name", "phone", "group"],
            "where": ("and", [("group", "eq", r1["group"])]),
            "order": ["name", "phone", "group"],
        },
        {
            "type": "select",
            "cols": ["*"],
            "where": ("and", [("phone", "eq", r2["phone"])]),
            "order": ["group", "name"],
        },
        # Numeric where + AND
        {
            "type": "select",
            "cols": ["name", "phone"],
            "where": (
                "and",
                [
                    ("group", "eq", r1["group"]),
                    ("phone", "ne", r0["phone"]),
                ],
            ),
            "order": ["phone"],
        },
        # OR on two different fields (task: each clause is a different column)
        {
            "type": "select",
            "cols": ["*"],
            "where": (
                "or",
                [
                    ("group", "eq", r0["group"]),
                    ("phone", "eq", r2["phone"]),
                ],
            ),
            "order": None,
        },
        # phone >= (only rows at global max phone — small result set)
        {
            "type": "select",
            "cols": ["group", "name"],
            "where": ("and", [("phone", "ge", max_phone)]),
            "order": ["group", "name"],
        },
        # name equality
        {
            "type": "select",
            "cols": ["phone", "group"],
            "where": ("and", [("name", "eq", r_mid["name"])]),
            "order": None,
        },
        # LIKE prefix (task-style St% analogue)
        {
            "type": "select",
            "cols": ["name"],
            "where": ("and", [("name", "like", "w0000%")]),
            "order": ["name"],
        },
        # NOT LIKE (narrow — OR would need full LIKE engine to match huge sets)
        {
            "type": "select",
            "cols": ["name", "phone"],
            "where": (
                "and",
                [
                    ("name", "nlike", "ZZZNOPE%"),
                    ("phone", "eq", r_mid["phone"]),
                ],
            ),
            "order": None,
        },
        # insert + re-query (PDF insert)
        {
            "type": "insert",
            "tuple": ("TaskStudent", 12_345_67, 209),
        },
        {
            "type": "select",
            "cols": ["*"],
            "where": ("and", [("group", "eq", 209), ("name", "eq", "TaskStudent")]),
            "order": None,
        },
        # delete some rows
        {
            "type": "delete",
            "where": ("and", [("name", "eq", "TaskStudent")]),
        },
        # Full-table scan (100k lines) before wiping list
        {"type": "select", "cols": ["*"], "where": None, "order": None},
        # delete all remaining then quit (PDF delete;)
        {"type": "delete"},
        {"type": "select", "cols": ["name"], "where": None, "order": None},
        {"type": "quit"},
    ]

    # Write in.txt
    in_path = ROOT / "in.txt"
    with in_path.open("w", encoding="utf-8") as f:
        for r in rows:
            f.write(f"{r['name']} {r['phone']} {r['group']}\n")

    # Serialize commands.txt
    def w(q: dict) -> str:
        t = q["type"]
        if t == "quit":
            return "quit;"
        if t == "insert":
            a, b, c = q["tuple"]
            return f"insert ({a}, {b}, {c});"
        if t == "delete":
            wh = q.get("where")
            if wh is None:
                return "delete;"
            op_a, clauses = wh
            parts = []
            for field, o, val in clauses:
                if o in ("eq", "ne", "lt", "gt", "le", "ge"):
                    sym = {"eq": "=", "ne": "<>", "lt": "<", "gt": ">", "le": "<=", "ge": ">="}[o]
                    parts.append(f"{field} {sym} {val}")
                elif o == "like":
                    parts.append(f"{field} like {val}")
                elif o == "nlike":
                    parts.append(f"{field} not like {val}")
            glue = f" {op_a} "
            return f"delete where {glue.join(parts)};"
        if t == "select":
            cols = q["cols"]
            colstr = "*" if cols == ["*"] else ", ".join(cols)
            tail = ""
            wh = q.get("where")
            if wh:
                op_a, clauses = wh
                parts = []
                for field, o, val in clauses:
                    if o in ("eq", "ne", "lt", "gt", "le", "ge"):
                        sym = {"eq": "=", "ne": "<>", "lt": "<", "gt": ">", "le": "<=", "ge": ">="}[o]
                        parts.append(f"{field} {sym} {val}")
                    elif o == "like":
                        parts.append(f"{field} like {val}")
                    elif o == "nlike":
                        parts.append(f"{field} not like {val}")
                glue = f" {op_a} "
                tail += f" where {glue.join(parts)}"
            od = q.get("order")
            if od:
                tail += " order by " + ", ".join(od)
            return f"select {colstr}{tail};"
        raise ValueError(t)

    cmd_path = ROOT / "commands.txt"
    with cmd_path.open("w", encoding="utf-8") as f:
        for op in ops:
            f.write(w(op) + "\n")

    exp_text, exp_res = simulate(rows, ops)
    meta = {
        "n_rows": len(rows),
        "expected_result_sum": exp_res,
        "anchor": {"r0": r0, "r1": r1, "r2": r2, "r_mid": r_mid},
    }
    (ROOT / "stress_expected.json").write_text(json.dumps(meta, indent=2), encoding="utf-8")
    (ROOT / "stress_expected_body.txt").write_text(exp_text + "\n", encoding="utf-8")

    print(f"Wrote {in_path} ({len(rows)} lines)")
    print(f"Wrote {cmd_path} ({len(ops)} commands)")
    print(f"Expected cumulative select count: {exp_res}")


if __name__ == "__main__":
    main()
