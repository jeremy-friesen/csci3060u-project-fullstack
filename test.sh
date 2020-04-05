#frontend="phase6/csci3060u-project-frontend"
#cd $frontend

dtfloc="randomTextFiles/*.txt" #change this to the path to the daily transaction files
mergedTransactionFile="testFile.txt" #change this to the path of the merged transaction file

transactions=( login logout create delete advertise bid refund addCredit )

#running test script
#./testScript.sh

#merge transaction files
for filename in $dtfloc
do
	echo $filename
	cat $filename >> $mergedTransactionFile
done
