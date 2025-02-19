#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculate.h"
#include "ui.h"

//����� �Է�
CALC UserInput(EXPRESSION* pEx) {
    system("cls");
	printf("�����Է�: ");
    scanf("%s %c %s%*c", pEx->lData, &pEx->op, pEx->rData);

    if (pEx->lData[0] == '0' || pEx->rData[0] == '0') {
        printf("���Ŀ� �°� �ٽ� �Է����ּ���.\n");
        return;
    }

    switch (pEx->op) {
    case '+':
        return ADD;
    case '-':
        return SUBSTRACT;
    }
    return;
}

//�̺�Ʈ ����
void EventloopRun() {
    char out;
    CALC calc = 0;
    EXPRESSION* pEx = malloc(sizeof(EXPRESSION));

    while (1) {
        calc = UserInput(pEx);
        switch (calc)
        {
        case ADD: {
            char* result = getAdd(pEx->lData, pEx->rData);
            printf("> %s\n", result);
            free(result);
            break;
        }
        case SUBSTRACT: {
            char* result = getSubstract(pEx->lData, pEx->rData);
            printf("> %s\n", result);
            free(result);
            break;
        }
        default:
            break;
        }

        printf("���α׷��� �����Ͻðڽ��ϱ�? (Y/N) ");
        scanf_s("%c", &out, 1);
        if (out == 'N' || out == 'n') {
            continue;
        }
        else if (out == 'Y' || out == 'y') {
            free(pEx);
            break;
        }
    }
    puts("Bye~!");
    return;
}