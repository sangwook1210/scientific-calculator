#pragma once
#pragma warning(disable:4996)
#define _CRT_SECRURE_NO_WARNINGS
#define MAX_STACK_SIZE 255
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"

typedef struct {	//트리를 원소로 가지는 스택
	TreeNode* data[MAX_STACK_SIZE];
	int top;
} tree_Stack;

void init_stack_ts(tree_Stack* s) {	//스택 초기화
	s->top = -1;
}

int is_empty_ts(tree_Stack* s) {	//스택이 비었는지 검사하는 함수
	if (s->top == -1)
		return 1;
	else
		return 0;
}

int is_full_ts(tree_Stack* s) {	//스택이 가득 차 있는지 검사하는 함수
	if (s->top == MAX_STACK_SIZE - 1)
		return 1;
	else
		return 0;
}

void push_ts(tree_Stack* s, TreeNode* a) {	//스택에 원소를 삽입하는 함수
	if (is_full_ts(s) == 1) {
		printf("스택이 꽉 차서 더 삽입할 수 없습니다.\n");
		return;
	}
	else
		s->data[++(s->top)] = a;
}

TreeNode* pop_ts(tree_Stack* s) {	//스택에서 원소를 꺼내는 함수
	if (is_empty_ts(s) == 1) {
		printf("스택이 비어있어 원소를 삭제할 수 없습니다.\n");
		return 0;
	}
	else
		return s->data[(s->top)--];
}

TreeNode* peek_ts(tree_Stack* s) {	//스택에서 가장 위에 있는 원소를 확인하는 함수
	if (is_empty_ts(s) == 1) {
		printf("스택이 비어있어 원소를 볼 수 없습니다.\n");
		return 0;
	}
	else
		return s->data[s->top];
}