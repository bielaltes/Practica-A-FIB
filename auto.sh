#!/bin/bash

# Define the parameters
program="kdtree_NN"
input_file="test"
param1="3"
param2="100"
param3="1000"

# Loop from n=1000 to n=100000
echo -n > out.csv
for n in {1000..100000..1000}; do
  # Call the program with the parameters
  echo "Running $program with n=$n..."
  ./$program $input_file $param1 $n $param2 $param3 >> out.csv
done
