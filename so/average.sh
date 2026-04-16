#!/bin/bash

sum=0
count=0
nums=()

while read -r line; do
  if [[ -n "$line" ]]; then
    sum=$((sum + line))
    nums+=("$line")
    ((count++))
  fi
done

if [ $count -eq 0 ]; then
  exit 0
fi

avg=$((sum / count))
echo "$avg"

sum_of_squares=0
for x in "${nums[@]}"; do
  diff=$((x - srednia))
  square=$((diff * diff))
  sum_of_squares=$((sum_of_squares + square))
done

w=$((sum_of_squares / count))
echo "$w"
