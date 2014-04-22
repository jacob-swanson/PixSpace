lcov --capture --directory . --output-file coverage.info
lcov -e coverage.info "*coverage*" -o coverage.info
genhtml coverage.info --output-directory lcov-out
