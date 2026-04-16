#!/bin/bash
#drwxr----- 2 user1 students 4096 Mar 22 16:37 folder1
while read -r permissions links owner group size month day time name; do
  #pomijamy pierwsza linie
  if [[ "$permissions" =~ ^[d-] ]]; then
    #zamiana liter na liczbe w osemkowym
    convert() {
      local val=0
      [[ ${1:0:1} == "r" ]] && ((val += 4))
      [[ ${1:1:1} == "w" ]] && ((val += 2))
      [[ ${1:2:1} == "x" ]] && ((val += 1))
      echo -n "$val"
    }

    u=$(convert "${permissions:1:3}")
    g=$(convert "${permissions:4:3}")
    o=$(convert "${permissions:7:3}")

    # foldery zaczynaja sie od d
    suffix=""
    if [[ "${permissions:0:1}" == "d" ]]; then
      suffix="/"
    elif [[ "${permissions:3:1}" == "x" ]]; then
      suffix="*"
    fi

    echo "$name$suffix $u$g$o"
  fi
done
