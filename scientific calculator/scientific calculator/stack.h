#pragma once
#define MAX_STACK_SIZE 255
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char element_s;
typedef struct {
	element_s data[MAX_STACK_SIZE];
	int top;
} StackType;

void init_stack(StackType* s) {	//������ �ʱ�ȭ
	s->top = -1;
}

int is_empty(StackType* s) {
	if (s->top == -1)	//��������� 1�� ��ȯ
		return 1;
	else	//������� ������ 0�� ��ȯ
		return 0;
}

int is_full(StackType* s) {
	if (s->top == MAX_STACK_SIZE - 1)	//ť�� ���� �� ������ 1�� ��ȯ
		return 1;
	else	//ť�� ���� �� ���� ������ 0�� ��ȯ
		return 0;
}

void push(StackType* s, element_s a) {	//���ÿ� ���Ҹ� �����ϴ� �Լ�
	if (is_full(s) == 1) {
		printf("������ �� ���� �� ������ �� �����ϴ�.\n");
		return;
	}
	else
		s->data[++(s->top)] = a;
}

element_s pop(StackType* s) {	//���ÿ��� ���Ҹ� ������ �Լ�
	if (is_empty(s) == 1) {
		printf("������ ����־� ���Ҹ� ������ �� �����ϴ�.\n");
		return 0;
	}
	else
		return s->data[(s->top)--];
}

element_s peek(StackType* s) {	//������ ���� ���� �ִ� ���Ҹ� Ȯ���ϴ� �Լ�
	if (is_empty(s) == 1) {
		//printf("������ ����־� ���Ҹ� �� �� �����ϴ�.\n");
		return 0;
	}
	else
		return s->data[s->top];
}