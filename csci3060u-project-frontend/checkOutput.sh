#run programs
FILES="input/*/*"
for f in $FILES
do
	file=${f%%.*} #get file without extension
	test=${file#*/} #remove initial directory
	
	# Write a file documenting if the file is ok or not
	if diff --strip-trailing-cr ex_output/$test.dt output/$test.dt;
	then
		echo "TEST $test: GOOD" >> out_log/test_results.txt
	else
		# If the file is not good document the issue
		echo "TEST $test: BAD" >> out_log/test_results.txt
		echo "TEST $test:" >> term_log/diff_log.txt
		diff --strip-trailing-cr ex_output/$test.dt output/$test.dt >> out_log/diff_log.txt
		echo $'\n' >> out_log/diff_log.txt
	fi
	
	
done