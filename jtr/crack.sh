#!/bin/sh
set -ex

export HOME=/root
cd /root/sha3

# Baseline short test
time /usr/bin/john --format=Raw-SHA3-256 --pot='short-0.pot' short.txt
# RoCC short test
time /usr/bin/john --format=Raw-SHA3-256-rocc --pot='short-1.pot' short.txt
# RoCC long test
time /usr/bin/john --format=Raw-SHA3-256-rocc --pot='long.pot' --verbosity=4 long.txt

poweroff
