SETLOCAL EnableDelayedExpansion

@REM  # Possibilities:
@REM  # Debug build + coverage
@REM  # Debug build + examples
@REM  # Debug build +   ---
@REM  # Release build
if "%CONFIGURATION%"=="Debug" (
  if "%coverage%"=="1" (
    @REM # coverage needs to build the special helper as well as the main
    cmake -Hmisc -Bbuild-misc -A%PLATFORM% || exit /b !ERRORLEVEL!
    cmake --build build-misc || exit /b !ERRORLEVEL!
    cmake -H. -BBuild -A%PLATFORM% -DUSE_WMAIN=%wmain% -DMEMORYCHECK_COMMAND=build-misc\Debug\CoverageHelper.exe -DMEMORYCHECK_COMMAND_OPTIONS=--sep-- -DMEMORYCHECK_TYPE=Valgrind || exit /b !ERRORLEVEL! || exit /b !ERRORLEVEL!
  ) else (
    cmake -H. -BBuild -A%PLATFORM% -DUSE_WMAIN=%wmain% -DITERTOOLS_BUILD_EXAMPLES=%examples% -DITERTOOLS_BUILD_EXTRA_TESTS=%examples% || exit /b !ERRORLEVEL!
  )
)
if "%CONFIGURATION%"=="Release" (
  cmake -H. -BBuild -A%PLATFORM% -DUSE_WMAIN=%wmain% || exit /b !ERRORLEVEL!
)
