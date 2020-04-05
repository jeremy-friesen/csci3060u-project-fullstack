#run programs
FILES="input/*/*"
for f in $FILES
do
	file=${f%%.*} #get file without extension
	test=${file#*/} #remove input directory
	
	# Write a file documenting if the file is ok or not
	if diff --strip-trailing-cr ex_term_output/$test.out term_output/$test.out;
	then
		echo "TEST $test: GOOD" >> term_log/test_results.txt
	else
		# If the file is not good document the issue
		echo "TEST $test: BAD" >> term_log/test_results.txt
		echo "TEST $test:" >> term_log/diff_log.txt
		diff --strip-trailing-cr ex_term_output/$test.out term_output/$test.out >> term_log/diff_log.txt
		echo $'\n' >> term_log/diff_log.txt
	fi
	
	
done