#!/usr/bin/env bash

RED=""
GREEN=""
YELLOW=""
RESET=""

format_time() {
  printf "%02d:%02d" $(($1 / 60)) $(($1 % 60))
}

progress_bar() {
  local current=$1 total=$2
  local percent=$(((total - current) * 100 / total))
  local bars=$((percent / 10))
  printf "[%.*s%.*s] %d%%" "$bars" "##########" "$((10 - bars))" "----------" "$percent"
}

log_event() {
  echo "[$(date '+%F %H:%M')] $1" >>pomodoro.log
}

STOPPED=0 # flaga globalna do kontrolowania przerwania
interrupt() {
  echo -e "\n${YELLOW}Przerwano. Czy zakończyć? (t/n)${RESET}"
  read ans
  if [[ "$ans" == "t" ]]; then
    echo "Zakończono program."
    exit 0
  else
    STOPPED=1
  fi
}
trap interrupt SIGINT

run_pomodoro() {
  local work=${1:-25}
  local break=${2:-5}
  local cycles=${3:-4}

  if ! [[ "$work" =~ ^[0-9]+$ ]] || ! [[ "$break" =~ ^[0-9]+$ ]] || ! [[ "$cycles" =~ ^[0-9]+$ ]]; then
    echo "Błąd: Parametry muszą być liczbami całkowitymi."
    exit 1
  fi

  for ((c = 1; c <= cycles; c++)); do
    if [[ "$STOPPED" -eq 1 ]]; then break; fi

    echo -e "${GREEN}--- POMODORO #$c: praca $work min ---${RESET}"
    local total=$((work * 60))

    for ((t = total; t > 0; t--)); do
      if [[ "$STOPPED" -eq 1 ]]; then break 2; fi
      echo -ne "\r$(format_time "$t")  "
      progress_bar "$t" "$total"
      sleep 1
    done

    log_event "Pomodoro #$c finished"
    echo -e "\n${GREEN}Koniec pracy!${RESET}"

    if [[ $c -lt $cycles ]]; then
      echo -e "${YELLOW}--- Przerwa $break min ---${RESET}"
      total=$((break * 60))
      for ((t = total; t > 0; t--)); do
        if [[ "$STOPPED" -eq 1 ]]; then break 2; fi
        echo -ne "\r$(format_time "$t")  "
        progress_bar "$t" "$total"
        sleep 1
      done
      echo -e "\n${YELLOW}Koniec przerwy!${RESET}"
    fi
  done
}

run_stoper() {
  local accumulated=0
  local start_ts=0
  local running=false

  echo "--- STOPER ---"
  echo "Menu: [1] Start  [2] Stop  [3] Reset  [4] Wyjście"

  while true; do
    # Calculate display time
    local current_display=$accumulated
    if $running; then
      local now=$(date +%s)
      local diff=$((now - start_ts))
      current_display=$((accumulated + diff))
    fi

    # Print Time (overwrite line)
    echo -ne "\r${GREEN}Czas: $(format_time $current_display)${RESET}   "

    # Read input with timeout (1 sec if running, blocking if not)
    local choice
    if $running; then
      read -t 1 -n 1 choice
    else
      read -n 1 choice
    fi

    # Handle input
    if [[ -n "$choice" ]]; then
      # Clear the line to remove the input character visual
      echo -ne "\r\033[K"
      case "$choice" in
      1) # Start
        if ! $running; then
          running=true
          start_ts=$(date +%s)
        fi
        ;;
      2) # Stop
        if $running; then
          running=false
          local now=$(date +%s)
          accumulated=$((accumulated + (now - start_ts)))
        fi
        ;;
      3) # Reset
        running=false
        accumulated=0
        echo -e "\r${YELLOW}Zresetowano.${RESET}"
        sleep 0.5
        echo -ne "\r\033[K" # Clear message
        ;;
      4) # Wyjście
        echo ""
        exit 0
        ;;
      esac
    fi
  done
}

case "$1" in
pomodoro)
  run_pomodoro "$2" "$3" "$4"
  ;; # Added missing semicolon
stoper)
  run_stoper
  ;; # Added missing semicolon
*)
  echo "Użycie:"
  echo "  $0 pomodoro [czas_pracy] [czas_przerwy] [cykle]"
  echo "  $0 stoper"
  ;; # Added missing semicolon
esac
