
#!/bin/bash
#KRZYSZTOF PIECHAL
declare -A counter #cos w stylu dicta 
declare -a order

while read -r id; do

  [ -z "$id" ] && continue

  if [ -z "${counter[$id]}" ]; then
    counter[$id]=0
    order+=("$id")
  fi

  ((counter[$id]++))
done

min_count=-1
rarest=""

for id in "${order[@]}"; do
  a=${counter[$id]}

  if [ "$min_count" -eq -1 ] || [ "$a" -lt "$min_count" ]; then
    min_count=$a
    rarest=$id
  fi
done

echo "$rarest $min_count"
