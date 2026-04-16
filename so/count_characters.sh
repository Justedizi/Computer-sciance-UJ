#!/bin/bash
# -m - ilosc znakow -b - bajty
read -r line
res=$(wc -m "$line")
echo $"res"
