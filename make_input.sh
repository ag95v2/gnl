#!/bin/bash


echo "Some text" > input1.txt
for i in {1..1000000}
do
   echo "Some text" >> input1.txt
done
