#pragma once

typedef enum { EXIT, ADD, SUBSTRACT} CALC;

//���� ����ü
typedef struct EXPRESSION {
	char lData[1000];
	char op;
	char rData[1000];
}EXPRESSION;

CALC UserInput(EXPRESSION* pEx);
void EventloopRun();