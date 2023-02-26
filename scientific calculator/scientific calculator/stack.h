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

void init_stack(StackType* s) {	//스택을 초기화
	s->top = -1;
}

int is_empty(StackType* s) {
	if (s->top == -1)	//비어있으면 1을 반환
		return 1;
	else	//비어있지 않으면 0을 반환
		return 0;
}

int is_full(StackType* s) {
	if (s->top == MAX_STACK_SIZE - 1)	//큐가 가득 차 있으면 1을 반환
		return 1;
	else	//큐가 가득 차 있지 않으면 0을 반환
		return 0;
}

void push(StackType* s, element_s a) {	//스택에 원소를 삽입하는 함수
	if (is_full(s) == 1) {
		printf("스택이 꽉 차서 더 삽입할 수 없습니다.\n");
		return;
	}
	else
		s->data[++(s->top)] = a;
}

element_s pop(StackType* s) {	//스택에서 원소를 꺼내는 함수
	if (is_empty(s) == 1) {
		printf("스택이 비어있어 원소를 삭제할 수 없습니다.\n");
		return 0;
	}
	else
		return s->data[(s->top)--];
}

element_s peek(StackType* s) {	//스택의 가장 위에 있는 원소를 확인하는 함수
	if (is_empty(s) == 1) {
		//printf("스택이 비어있어 원소를 볼 수 없습니다.\n");
		return 0;
	}
	else
		return s->data[s->top];
}