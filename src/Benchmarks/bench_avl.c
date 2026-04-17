#include "../MainTask/AVL-Tree/AVL-Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
        if (argc < 2) {
                return 1;
        }
        AVLTree* tree = CreateAVLTree();

        char keys[10000][4];
        for (int i = 0; i < 10000; i++) {
                sprintf(keys[i], "%c%c%c", 'A' + i / 676 % 26, 'A' + i / 26 % 26, 'A' + i % 26);
                AVLTreeInsert(tree, keys[i], "AirportName");
        }

        if (strcmp(argv[1], "scenario_1") == 0) {
                for (int i = 0; i < 50000; i++) {
                        AVLTreeFind(tree, keys[i % 10000]);
                }
        } else {
                for (int i = 0; i < 10000; i++) {
                        char new_code[4];
                        sprintf(new_code, "Z%02d", i % 100);
                        AVLTreeInsert(tree, new_code, "NewAirport");
                        AVLTreeFind(tree, keys[i % 10000]);
                }
        }
        FreeAVLTree(tree);
        return 0;
}