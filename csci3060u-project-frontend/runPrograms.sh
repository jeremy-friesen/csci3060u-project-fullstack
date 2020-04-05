#run programs
FILES="input/*/*"
for f in $FILES
do
	file=${f%%.*} #get file without extension
	test=${file#*/} #remove input directory for path to test
	DIR=$(dirname "${test}")
	
	echo "running test $test"
	
	#make missing directory if it exists
	if [ ! -d term_output/$DIR ];
	then
		mkdir term_output/$DIR
	fi
	
	#run the program
	./main output/$test.dt < input/$test.in > term_output/$test.out
	
done