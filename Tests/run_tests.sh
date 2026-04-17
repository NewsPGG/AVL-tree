#!/bin/bash

cat > airports_test.txt <<EOF
SVO:Sheremetyevo International Airport
DME:Domodedovo
LED:Pulkovo
EOF

echo "MainTask (AVL Tree)"
./build/airport_tree airports_test.txt < Tests/MainTask/Tree_test_commands.txt > output_main.txt
if diff -Z output_main.txt Tests/MainTask/Tree_expected_output.txt; then
    echo "OK"
else
    echo "FAILED"
    diff -u output_main.txt Tests/MainTask/Tree_expected_output.txt
fi

echo

echo "BonusTask (Singly Linked List)"
./build/airport_list airports_test.txt < Tests/BonusTask/List_test_commands.txt > output_bonus.txt
if diff -Z output_bonus.txt Tests/BonusTask/List_expected_output.txt; then
    echo "OK"
else
    echo "FAILED"
    diff -u output_bonus.txt Tests/BonusTask/List_expected_output.txt
fi

rm -f airports_test.txt output_main.txt output_bonus.txt