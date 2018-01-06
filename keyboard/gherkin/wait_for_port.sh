#!/bin/bash

start_ports=$(ls /dev/tty*)

while true; do
  ports=$(ls /dev/tty*)
  diff_ports=$(diff <(echo "$start_ports") <(echo "$ports") | grep -E "^>.+" | cut -f2- -d" ")
  if [ "x$diff_ports" != "x" ]; then
    echo $diff_ports
    exit 1
  fi
  sleep 1
done
