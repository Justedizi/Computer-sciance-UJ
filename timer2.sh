#!/usr/bin/env bash

RED=""
GREEN=""
YELLOW=""
RESET=""

format_time() {
    printf "%d:%d" $(($1 / 60)) $(($1 % 60))
}

progress_bar() {
    local current=$1 total=$2
    local percent=$(((total - current) * 100 / total))
    local bars=$((percent / 10))
    printf "[%.*s%.*s] %d%%" "$bars" "##########" "$((10 - bars))" "----------" "$percent"
}

log_event() {
    echo "[$(date '+%F %H:%M')] $1" >> pomodoro.txt
}

interrupt() {
    echo -e "\nPrzerwano. Czy zakonczyc (y/n)"
    read ans
    if [[ "$ans" == "y" ]]; then
        echo "zakonczono program"
        exit 0
    fi
}
trap interrupt SIGINT

run_pomodoro() {
    local work=${1:-25}
    local break=${2:-5}
    local cycles=${3:-4}

    for ((c = 1; c <= cycles; c++)); do
        echo "POMODORO #$c: praca $work min" 
        local total_work=$((work * 60))
        
        # Odliczanie czasu pracy
        for ((t = total_work; t > 0; t--)); do
            echo -ne "\r$(format_time "$t") "
            progress_bar "$t" "$total_work"
            sleep 1
        done
        
        log_event "Pomodoro #$c finished"
        echo -e "\nkoniec pracy!"

        if [[ $c -lt $cycles ]]; then
            echo "Przerwa $break min"
            local total_break=$((break * 60))
            for ((t = total_break; t > 0; t--)); do
                echo -ne "\r$(format_time "$t") "
                progress_bar "$t" "$total_break"
                sleep 1
            done
            echo -e "\nKoniec przerwy!"
        fi
    done
}

run_stoper() {
    local running=false
    local sec=0

    while true; do
        echo -ne "\rCzas: $(format_time $sec) "
        if ! $running; then
            echo -e "\n1) start\n2) stop\n3) reset\n4) exit"
            echo -n "Wybor: "
        fi

        local choice
        if $running; then
            read -t 1 -n 1 choice
            ((sec++))
        else
            read -n 1 choice
        fi

        case $choice in
            1)
                running=true
                ;;
            2)
                running=false
                echo "" 
                ;;
            3)
                running=false
                sec=0
                echo -e "\nZresetowano."
                ;;
            4)
                echo ""
                exit 0
                ;;
            *)
                if [[ -n "$choice" ]]; then
                    echo -e "\nNieznana opcja"
                fi
                ;;
        esac
    done
}

case "$1" in
    pomodoro)
        run_pomodoro "$2" "$3" "$4"
        ;;
    stoper)
        run_stoper
        ;;
    *)
        echo "Użycie:"
        echo "  $0 pomodoro [czas_pracy] [czas_przerwy] [cykle]"
        echo "  $0 stoper"
        ;;
esac
