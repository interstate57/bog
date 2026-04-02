#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")/.."

make clean >/dev/null
make >/dev/null

fail=0
for cmd in tests/cmd_*.txt; do
  name="$(basename "$cmd" .txt)"
  data="tests/${name/cmd/data}.txt"
  expected="tests/${name/cmd/expected}.txt"
  out="tests/${name/cmd/out}.txt"

  if [[ ! -f "$data" ]]; then
    echo "[FAIL] missing data file for $cmd ($data)"
    fail=1
    continue
  fi
  if [[ ! -f "$expected" ]]; then
    echo "[FAIL] missing expected file for $cmd ($expected)"
    fail=1
    continue
  fi

  # Some tests intentionally exit non-zero (e.g., parsing errors).
  set +e
  ./a.out "$data" <"$cmd" >"$out"
  rc=$?
  set -e
  if diff -u "$expected" "$out" >/dev/null; then
    echo "[OK]   $name"
  else
    echo "[FAIL] $name (see $out)"
    diff -u "$expected" "$out" || true
    fail=1
  fi

  # Expected return codes:
  # - parser_errors: program prints "Parsing error!" and exits with code 3
  if [[ "$name" == "cmd_parser_errors" ]]; then
    if [[ "$rc" -ne 3 ]]; then
      echo "[FAIL] $name unexpected exit code: $rc (expected 3)"
      fail=1
    fi
  else
    if [[ "$rc" -ne 0 ]]; then
      echo "[FAIL] $name unexpected exit code: $rc (expected 0)"
      fail=1
    fi
  fi
done

if [[ "$fail" -ne 0 ]]; then
  exit 1
fi

echo "All tests passed."

