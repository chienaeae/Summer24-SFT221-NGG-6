#!/bin/sh
echo "Starting test runner..."
test_runner="C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\TestWindow\vstest.console.exe"
tests_dll="C:\Canada-Job\Seneca\5-Summer 2024\SFT221-NCC\Week 10\mySolution1\x64\Debug\UnitTest1.dll"
failure_string="Failed:"
testout=$("$test_runner" "$tests_dll")
if [[ $testout == *"$failure_string"* ]]; then
    echo >&2 "Unit test are not passing! Push aborted!"
    exit 1
fi
echo >&2 "All tests run successfully."
exit 0
