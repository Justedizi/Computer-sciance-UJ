#!/bin/bash

read -r inp

char=${inp:0:1}

if [[$"inp" == *"+"*]]; then
  #,, mala litera ^^ duza
  pattern="${char,,}${char^^}"
else
  pattern="$char"
fi

while read -r line; do
  #tr do zamiany znakow flaga -d delate -c complemetn
  res =$(echo "$line" | tr -dc "$pattern" | wc -m)
  echo "$res"
done
