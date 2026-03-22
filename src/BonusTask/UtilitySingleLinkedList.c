#include "SingleLinkedList/SingleLinkedList.h"
#include "SingleLinkedList/SingleLinkedList.c"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return -1;
    }

    List* list = newList();
    if (!list) {
        return -1;
    }

    FILE* file = fopen(argv[1], "r");
    int count = 0;
    if (file) {
        char line[1024];
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\r\n")] = '\0';
            char* colon = strchr(line, ':');
            if (colon) {
                *colon = '\0';
                char* code = line;
                char* name = colon + 1;
                if (insert(list, code, name)) {
                    count++;
                }
            }
        }
        fclose(file);
        printf("Загружено %d аэропортов. Система готова к работе.\n", count);
    } else {
        printf("Файл не найден. Начинаем с пустой базы.\n");
    }

    char input[512];
    while (1) {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\r\n")] = '\0';
        if (strlen(input) == 0) continue;

        char* space = strchr(input, ' ');
        char* cmd = input;
        char* args = NULL;
        if (space) {
            *space = '\0';
            args = space + 1;
            while (*args == ' ') args++;
        }
        if (strlen(cmd) == 0) {
            continue;
        }
        if (strcmp(cmd, "quit") == 0) {
            break;
        } else if (strcmp(cmd, "find") == 0) {
            if (!args || *args == '\0') {
                printf("Ошибка: укажите код аэропорта\n");
                continue;
            }
            ListNode* node = find(list, args);
            if (node) {
                printf("%s → %s\n", node->code, node->name);
            } else {
                printf("Аэропорт с кодом '%s' не найден в базе.\n", args);
            }
        } else if (strcmp(cmd, "add") == 0) {
            if (!args || *args == '\0') {
                printf("Ошибка: укажите код:название\n");
                continue;
            }
            char* colon = strchr(args, ':');
            if (!colon) {
                printf("Ошибка: неправильный формат, ожидается код:название\n");
                continue;
            }
            *colon = '\0';
            char* code = args;
            char* name = colon + 1;
            if (strlen(code) == 0 || strlen(name) == 0) {
                printf("Ошибка: код и название не могут быть пустыми\n");
                continue;
            }
            if (insert(list, code, name)) {
                printf("Аэропорт '%s' добавлен в базу.\n", code);
            } else {
                printf("Аэропорт '%s' уже в базе!\n", code);
            }
        } else if (strcmp(cmd, "delete") == 0) {
            if (!args || *args == '\0') {
                printf("Ошибка: укажите код аэропорта\n");
                continue;
            }
            if (delete(list, args)) {
                printf("Аэропорт '%s' удалён из базы.\n", args);
            } else {
                printf("Аэропорт с кодом '%s' не найден в базе!\n", args);
            }
        } else {
            printf("Неизвестная команда: %s\n", cmd);
        }
    }

    deleteList(list);
    return 0;
}