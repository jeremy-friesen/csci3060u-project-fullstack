#!/bin/bash

runFrontEnd="./csci3060u-project-frontend/src/a.out"
transactions="./DailyScriptTransactions/$1"

echo "$1"

# run 5 frontend sessions
for i in DailyScriptInputs/$1/*
do
  echo "$i"
  filename=$(basename $i)
  rm $transactions/$filename
  $runFrontEnd currentusers.txt availableitems.txt $transactions/$filename < $i &> /dev/null
done

# combine transaction files into one daily transaction file
rm dailytransactions.txt
for i in $transactions/*
do
  cat $i >> dailytransactions.txt
done

# run backend with daily transactions
java -jar backend.jar