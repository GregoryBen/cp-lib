@echo off
set /a i = 1
:loop
  echo %i%
  gen.exe > in
  check.exe < in > out1
  brute.exe < in > out2
  fc out1 out2 > nul
  if errorlevel 1 goto fail
  set /a i = %i% + 1
  goto loop
:fail
  echo Found failing test!
