#!/bin/bash

cat > airports_test.txt <<EOF
SVO:Sheremetyevo International Airport
DME:Domodedovo
LED:Pulkovo
EOF

echo "MainTask (AVL Tree)"
../a.out airports_test.txt < MainTask/Tree_test_commands.txt > output_main.txt
if diff output_main.txt MainTask/Tree_expected_output.txt; then
    echo "OK"
else
    echo "FAILED"
fi

echo


echo "BonusTask (Singly Linked List)"
../a.out airports_test.txt < BonusTask/List_test_commands.txt > output_bonus.txt
if diff output_bonus.txt BonusTask/List_expected_output.txt; then
    echo "OK"
else
    echo "FAILED"
fi


rm -f airports_test.txt output_main.txt output_bonus.txt