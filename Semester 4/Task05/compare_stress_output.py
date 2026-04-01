#!/usr/bin/env python3
"""Strip leak-checker noise from a.out output and diff against stress_expected_body.txt."""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent


def repair_stdout_leak_splits(lines: list[str]) -> list[str]:
    """Some wrappers inject a leak report into stdout mid-stream, splitting a data row."""
    out: list[str] = []
    i = 0
    while i < len(lines):
        ln = lines[i]
        if (
            ln.strip().startswith("---")
            and lines[i : i + 1]
            and "total allocation" not in ln
        ):
            i += 1
            while i < len(lines) and "WORK TIME" not in lines[i]:
                i += 1
            i += 1  # skip WORK TIME line
            if out and i < len(lines):
                cont = lines[i]
                m = re.match(r"^(\d+) (\d+) (\d+)\s*$", cont)
                prev = out[-1]
                if m and prev.startswith(" ") and prev.count(" ") == 1:
                    tail = prev[1:].strip()
                    if tail.isalnum() or re.match(r"^[\w%]+$", tail):
                        out[-1] = f" {tail}{m.group(1)} {m.group(2)} {m.group(3)}"
                        i += 1
                        continue
            continue
        out.append(ln)
        i += 1
    return out


def extract_body_and_result(raw_lines: list[str]) -> tuple[list[str], int | None]:
    raw_lines = repair_stdout_leak_splits(raw_lines)
    body: list[str] = []
    res: int | None = None
    for line in raw_lines:
        if line.startswith("---") and "---" in line[:10]:
            continue
        if "total allocation" in line or line.startswith("leak ") or line.startswith("WORK "):
            continue
        m = re.search(r"Result\s*=\s*(\d+)", line)
        if m and "Elapsed" in line:
            res = int(m.group(1))
            break
        body.append(line)
    return body, res


def main() -> int:
    raw_path = ROOT / "stress_actual_raw.txt"
    exp_path = ROOT / "stress_expected_body.txt"
    meta_path = ROOT / "stress_expected.json"
    if not raw_path.is_file():
        print("missing stress_actual_raw.txt", file=sys.stderr)
        return 2
    raw = raw_path.read_text(encoding="utf-8", errors="replace").splitlines()
    body, got_res = extract_body_and_result(raw)
    act_path = ROOT / "stress_actual_body.txt"
    act_path.write_text("\n".join(body) + "\n", encoding="utf-8")

    exp = exp_path.read_text(encoding="utf-8").splitlines()
    act = act_path.read_text(encoding="utf-8").splitlines()
    if exp != act:
        print("BODY MISMATCH: line count expected", len(exp), "actual", len(act))
        for i, (e, a) in enumerate(zip(exp, act)):
            if e != a:
                print(f" first diff at line {i+1}:\n  exp: {e!r}\n  act: {a!r}")
                break
        else:
            if len(exp) != len(act):
                print(" length differs", len(exp), len(act))
        return 1

    meta = json.loads(meta_path.read_text(encoding="utf-8"))
    exp_res = meta["expected_result_sum"]
    if got_res != exp_res:
        print(f"RESULT SUM mismatch: expected {exp_res}, got {got_res}")
        return 1

    print("OK: body identical,", len(exp), "lines; Result =", got_res)
    return 0


if __name__ == "__main__":
    sys.exit(main())
