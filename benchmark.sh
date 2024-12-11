#!/bin/bash

for graph_size in $(seq 8 2 32); do
    ./generate $graph_size 70
    ./convertspace
    for mode in b g h; do
        start_time=$(date +%s%N)
        ./CVC $mode
        end_time=$(date +%s%N)
        execution_time=$((($end_time - $start_time) / 1000000))
        echo "$graph_size;$execution_time" >> "benchmark/test_outputs/time-70-$mode.csv"
    done
done
