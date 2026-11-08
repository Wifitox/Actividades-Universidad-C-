#!/usr/bin/env bash
set -u

CXX=${CXX:-g++}
CXXFLAGS=${CXXFLAGS:--std=c++17 -O2}

TOTAL=0
PASS=0
FAIL=0

say() { printf "%s\n" "$*"; }

compile() {
  local src="$1" out="$2"
  if [[ ! -f "$src" ]]; then
    say "[MISSING] $src"
    FAIL=$((FAIL+1))
    return 0
  fi
  $CXX $CXXFLAGS "$src" -o "$out"
  if [[ $? -ne 0 ]]; then
    say "[COMPILE FAIL] $src"
    FAIL=$((FAIL+1))
  else
    say "[OK] $src"
  fi
}

run_suite() {
  local label="$1" exe="$2" dir="$3"
  say ""
  say "--- $label ---"

  if [[ ! -x "$exe" ]]; then
    say "[SKIP] executable not found: $exe"
    return 0
  fi
  if [[ ! -d "$dir" ]]; then
    say "[SKIP] tests folder not found: $dir"
    return 0
  fi

  shopt -s nullglob
  local inputs=("$dir"/*.in)
  if [[ ${#inputs[@]} -eq 0 ]]; then
    say "[SKIP] no .in files in: $dir"
    return 0
  fi

  for in_file in "${inputs[@]}"; do
    local base="$(basename "$in_file" .in)"
    local out_file="$dir/$base.out"
    local got_file="$dir/$base.got"

    TOTAL=$((TOTAL+1))

    "$exe" < "$in_file" > "$got_file"

    if diff -q "$out_file" "$got_file" >/dev/null 2>&1; then
      say "[PASS] $base"
      PASS=$((PASS+1))
      rm -f "$got_file"
    else
      say "[FAIL] $base"
      FAIL=$((FAIL+1))
    fi
  done
}

say ""
say "==============================="
say "Graph Representations - Tests"
say "==============================="
say ""

say "Compiling..."
compile GraphMatrix.cpp   g_matrix
compile GraphList.cpp     g_list
compile GraphEdgeList.cpp g_edge
compile GraphArcLists.cpp g_arc

run_suite "Adjacency Matrix" ./g_matrix tests/matrix
run_suite "Adjacency List"   ./g_list   tests/list
run_suite "Edge List"        ./g_edge   tests/edge-list
run_suite "Arc Lists"        ./g_arc    tests/arc-lists

say ""
say "==============================="
say "Summary"
say "  Total: $TOTAL"
say "  Pass : $PASS"
say "  Fail : $FAIL"
say "==============================="
say ""
say "(This script never stops early. It runs all tests.)"
say ""

read -r -p "Press Enter to close..." _

if [[ $FAIL -ne 0 ]]; then
  exit 1
fi
exit 0
