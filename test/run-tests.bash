run_test() {
	diff --strip-trailing-cr -u "$2" <( "$1" < "$3" ) && return
	echo "Test failed for input file '$3'"
	exit 1
}

run_test "$1" sorted-dates     test-dates
run_test "$1" sorted-fractions test-fractions
run_test "$1" sorted-words     test-words

echo "All tests passed"
exit 0
