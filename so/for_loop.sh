#!/bin/bash


read -r n

for ((i = 1; i <= n; i++)); do
  #jesli nie jest to 1 to spacja
  if [ "$i" -gt 1 ]; then
    echo -n " "
  fi

  echo -n "$i"
done

echo "" #znak \n w bash
