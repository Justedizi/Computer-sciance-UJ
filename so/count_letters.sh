# KRZYSZTOF PIECHAL
#!/bin/bash

read -r inp

char=${inp:0:1}

if [[ "$inp" == *"+"* ]]; then
  pattern="${char,,}${char^^}"
else
  pattern="$char"
fi

while read -r line; do
  res=$(echo -n "$line" | tr -dc "$pattern" | wc -m)
  echo "$res"
done
