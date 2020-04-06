#frontend="phase6/csci3060u-project-frontend"
backend="csci3060u-project-backend/src/lib"
#cd $frontend

dtfloc="randomTextFiles/*.txt" #change this to the path to the daily transaction files
mergedTransactionFile="testFile.txt" #change this to the path of the merged transaction file

: > $mergedTransactionFile #clear merged transaction file

transactions=( login logout create delete advertise bid refund addCredit )

#run front end
#./testScript.sh

#merge transaction files
for filename in $dtfloc
do
	echo $filename
	cat $filename >> $mergedTransactionFile
done

#run backend
cd $backend

javac -cp *.java
java Main
