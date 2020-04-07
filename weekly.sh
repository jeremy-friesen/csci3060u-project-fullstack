#!/bin/bash

frontend="./csci3060u-project-frontend"

# compile frontend
g++ $frontend/src/main.cpp

# clear previous content in files
: > currentusers.txt
: > availableitems.txt

# set file content
text="fullUsername    FS 001110.00
buyUsername     BS 009999.99
sellUsername    SS 000000.00
adminUsername   AA 000050.00"
echo "$text" > currentusers.txt

text="basketball          someUs3r        fullUsername    010.00
sneakers            exampleUsername someBidder      005.00"
echo "$text" > availableitems.txt

# run the daily script 5 times
for i in {1..5}
do
	foldername="day$i"
	./daily.sh $foldername
done