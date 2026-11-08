@echo off
setlocal EnableExtensions EnableDelayedExpansion

REM ===============================
REM Graph Representations - Runner
REM Runs ALL tests and prints a summary.
REM ===============================

set CXX=g++
set CXXFLAGS=-std=c++17 -O2

set TOTAL=0
set PASS=0
set FAIL=0

echo.
echo ===============================
echo Graph Representations - Tests
echo ===============================
echo.

echo Compiling...
call :compile GraphMatrix.cpp g_matrix.exe
call :compile GraphList.cpp g_list.exe
call :compile GraphEdgeList.cpp g_edge.exe
call :compile GraphArcLists.cpp g_arc.exe

echo.
call :run_suite "Adjacency Matrix" g_matrix.exe tests\matrix
call :run_suite "Adjacency List"   g_list.exe   tests\list
call :run_suite "Edge List"        g_edge.exe   tests\edge-list
call :run_suite "Arc Lists"        g_arc.exe    tests\arc-lists

echo.
echo ===============================
echo Summary
echo   Total: !TOTAL!
echo   Pass : !PASS!
echo   Fail : !FAIL!
echo ===============================
echo.
echo (This script never stops early. It runs all tests.)

echo.
echo Press any key to close...
pause >nul

if !FAIL! NEQ 0 exit /b 1
exit /b 0

:compile
set SRC=%~1
set OUT=%~2
if not exist "%SRC%" (
  echo [MISSING] %SRC%
  set /a FAIL+=1
  goto :eof
)
%CXX% %CXXFLAGS% "%SRC%" -o "%OUT%"
if errorlevel 1 (
  echo [COMPILE FAIL] %SRC%
  set /a FAIL+=1
) else (
  echo [OK] %SRC%
)
goto :eof

:run_suite
set LABEL=%~1
set EXE=%~2
set DIR=%~3

echo.
echo --- %LABEL% ---
if not exist "%EXE%" (
  echo [SKIP] executable not found: %EXE%
  goto :eof
)
if not exist "%DIR%" (
  echo [SKIP] tests folder not found: %DIR%
  goto :eof
)

for %%F in ("%DIR%\*.in") do (
  set /a TOTAL+=1
  set BASE=%%~nF
  set IN=%%F
  set OUT=%DIR%\!BASE!.out
  set GOT=%DIR%\!BASE!.got

  "%EXE%" < "!IN!" > "!GOT!"

  fc /n "!OUT!" "!GOT!" >nul
  if errorlevel 1 (
    echo [FAIL] !BASE!
    set /a FAIL+=1
  ) else (
    echo [PASS] !BASE!
    set /a PASS+=1
    del /q "!GOT!" >nul 2>&1
  )
)

goto :eof
