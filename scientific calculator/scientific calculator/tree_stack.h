#pragma once
#pragma warning(disable:4996)
#define _CRT_SECRURE_NO_WARNINGS
#define MAX_STACK_SIZE 255
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"

typedef struct {	//Ʈ���� ���ҷ� ������ ����
	TreeNode* data[MAX_STACK_SIZE];
	int top;
} tree_Stack;

void init_stack_ts(tree_Stack* s) {	//���� �ʱ�ȭ
	s->top = -1;
}

int is_empty_ts(tree_Stack* s) {	//������ ������� �˻��ϴ� �Լ�
	if (s->top == -1)
		return 1;
	else
		return 0;
}

int is_full_ts(tree_Stack* s) {	//������ ���� �� �ִ��� �˻��ϴ� �Լ�
	if (s->top == MAX_STACK_SIZE - 1)
		return 1;
	else
		return 0;
}

void push_ts(tree_Stack* s, TreeNode* a) {	//���ÿ� ���Ҹ� �����ϴ� �Լ�
	if (is_full_ts(s) == 1) {
		printf("������ �� ���� �� ������ �� �����ϴ�.\n");
		return;
	}
	else
		s->data[++(s->top)] = a;
}

TreeNode* pop_ts(tree_Stack* s) {	//���ÿ��� ���Ҹ� ������ �Լ�
	if (is_empty_ts(s) == 1) {
		printf("������ ����־� ���Ҹ� ������ �� �����ϴ�.\n");
		return 0;
	}
	else
		return s->data[(s->top)--];
}

TreeNode* peek_ts(tree_Stack* s) {	//���ÿ��� ���� ���� �ִ� ���Ҹ� Ȯ���ϴ� �Լ�
	if (is_empty_ts(s) == 1) {
		printf("������ ����־� ���Ҹ� �� �� �����ϴ�.\n");
		return 0;
	}
	else
		return s->data[s->top];
}