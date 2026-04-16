#!/bin/bash

read -r n

a=0
b=1

for ((i = 1; i <= n; i++)); do
  echo "$a"

  suma=$((a + b))

  a=$b
  b=$suma
done 
