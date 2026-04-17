#include "../BonusTask/SingleLinkedList/SingleLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (argc < 2) {
        return 1;
    }
    List* list = newList();

    char keys[10000][4];
    for (int i = 0; i < 10000; i++) {
        sprintf(keys[i], "%c%c%c", 'A' + i / 676 % 26, 'A' + i / 26 % 26, 'A' + i % 26);
        insert(list, keys[i], "AirportName");
    }

    if (strcmp(argv[1], "scenario_1") == 0) {
        for (int i = 0; i < 50000; i++) {
            find(list, keys[i % 10000]);
        }
    } else {
        for (int i = 0; i < 10000; i++) {
            char new_code[4];
            sprintf(new_code, "Z%02d", i % 100);
            insert(list, new_code, "NewAirport");
            find(list, keys[i % 10000]);
        }
    }
    deleteList(list);
    return 0;
}