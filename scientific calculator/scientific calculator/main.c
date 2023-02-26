#define _CRT_SECRURE_NO_WARNINGS
#define MAX_STACK_SIZE 255
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include "tree.h"
#include "tree_stack.h"

//연산자의 우선순위를 정해주는 함수
int prec(char op) {
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	case '^': return 3;
	case 's': case 'c': case 't': case 'e': case 'l': return 4;
	}
	return -1;
}

//중위 표기 수식을 후위 표기 수식으로 전환해주는 함수
const char* infix_to_postfix(char infix[]) {
	char ch, top_op;
	int length = strlen(infix);
	char* postfix = malloc(sizeof(char) * MAX_STACK_SIZE);
	int j = 0;
	StackType s;
	init_stack(&s);

	for (int i = 0; i < length; i++) {	//중위 표기 수식의 길이만큼 반복
		ch = infix[i];	//중위표기 수식을 한 문자씩 끊어서 ch에 저장한다.

		//만약 ch가 +-*/^sctel과 같은 연산기호라면
		if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' ||
			ch == 's' || ch == 'c' || ch == 't' || ch == 'e' || ch == 'l') {
			//스택의 가장 위에 있는 것이 sctel라면
			if (peek(&s) == 's' || peek(&s) == 'c' || peek(&s) == 't' || peek(&s) == 'e' || peek(&s) == 'l') {
				postfix[j++] = pop(&s);	//postfix[j]에 스택에서 pop한 것을 저장 후 j 1증가
				postfix[j++] = ' ';	//띄어쓰기
			}
			//스택이 비어있지 않고 ch의 우선순위가 스택에서 peek한 연산기호의 우선순위보다 작거나 같다면
			while ((is_empty(&s) == 0) && (prec(ch) <= prec(peek(&s)))) {
				postfix[j++] = pop(&s);	//postfix[j]에 스택에서 pop한 것을 저장 후 j 1증가
				postfix[j++] = ' ';	//띄어쓰기
			}
			push(&s, ch);	//스택에 ch를 push
		}
		//만약 ch가 (라면
		else if (ch == '(') {
			if (infix[i + 1] == '-') {	//괄호 뒤에 음수가 나올 경우
				//(-1)을 0 1 - 로 만드는 과정
				postfix[j++] = '0';
				postfix[j++] = ' ';
				i++;
				i++;
				postfix[j++] = infix[i++];
				postfix[j++] = ' ';
				postfix[j++] = '-';
				postfix[j++] = ' ';
			}
			else {	//괄호 뒤가 음수가 아니라면
				push(&s, ch);	//스택에 ch를 push
			}
		}
		//만약 ch가 )라면
		else if (ch == ')') {
			top_op = pop(&s);
			while (top_op != '(') {	//top_op가 (가 아닐 때까지 반복
				//스택에 쌓여있는 모든 연산기호들을 postfix에 저장
				postfix[j++] = top_op;
				postfix[j++] = ' ';
				top_op = pop(&s);
			}

			//스택의 가장 위에 있는 원소가 삼각함수 혹은 지수,로그 함수라면
			if (peek(&s) == 's' || peek(&s) == 'c' || peek(&s) == 't' || peek(&s) == 'e' || peek(&s) == 'l') {
				postfix[j++] = pop(&s);
				postfix[j++] = ' ';
			}
		}
		//만약 ch가 연산기호가 아닌 숫자라면
		else {
			postfix[j++] = ch;
			if (infix[i + 1] == '+' || infix[i + 1] == '-' || infix[i + 1] == '*' || infix[i + 1] == '/' ||
				infix[i + 1] == '^' || infix[i + 1] == '(' || infix[i + 1] == ')' || infix[i + 1] == '\0') {
				postfix[j++] = ' ';
			}
		}
	}
	//스택에 남아있는 모든 연산기호들을 postfix에 저장
	while (is_empty(&s) == 0) {
		postfix[j++] = pop(&s);
		postfix[j++] = ' ';
	}
	//postfix의 남은 비어있는 모든 부분을 \0로 바꾼다.
	for (int i = j; i < MAX_STACK_SIZE; i++)
		postfix[i] = '\0';
	
	return postfix;	//만들어진 후위 표기식을 반환
}

//후위 표기 수식을 스택을 이용하여 트리로 만드는 함수
TreeNode* make_exp_Tree(char* postfix) {
	tree_Stack ts;	//ts라는 tree_Stack 변수를 선언
	init_stack_ts(&ts);	//ts를 초기화

	char* tmp = strtok(postfix, " ");	//tmp에 postfix 문자열을 띄어쓰기 기준으로 끊은 것을 저장

	while (tmp != NULL) {	//더 이상 끊을 문자열이 없을 때까지 반복
		//만약 끊어진 문자열이 +-*/^와 같은 연산기호라면
		if (strcmp(tmp, "+") == 0 || strcmp(tmp, "-") == 0 || strcmp(tmp, "*") == 0 || strcmp(tmp, "/") == 0 || strcmp(tmp, "^") == 0) {
			TreeNode* right = pop_ts(&ts);	//TreeNode의 right에 스택에 저장된 것을 pop하여 저장
			TreeNode* left = pop_ts(&ts);	//TreeNode의 left에 스택에 저장된 것을 pop하여 저장
			push_ts(&ts, CreateNode(tmp, left, right));	//끊어진 연산기호를 부모 노드로 하고, 스택의 가장 위에 저장되어있던 원소 두 개를 자식 노드로 하는 트리를 스택에 저장
		}
		//만약 끊어진 문자열이 삼각함수 혹은 지수, 로그함수라면
		else if (strcmp(tmp, "s") == 0 || strcmp(tmp, "c") == 0 || strcmp(tmp, "t") == 0 || strcmp(tmp, "e") == 0 || strcmp(tmp, "l") == 0) {
			TreeNode* right = pop_ts(&ts);	//TreeNode의 right에 스택에 저장된 것을 pop하여 저장
			push_ts(&ts, CreateNode(tmp, NULL, right));//끊어진 연산기호를 부모 노드로 하고, 스택의 가장 위에 저장되어있던 원소를 자식 노드로 하는 트리를 스택에 저장
		}
		//만약 끊어진 문자열이 연산기호가 아닌 숫자라면
		else {
			push_ts(&ts, CreateNode(tmp, NULL, NULL));	//끊어진 문자를 부모 노드로 하고 NULL 두 개를 자식 노드로 하는 트리를 스택에 저장
		}

		tmp = strtok(NULL, " ");	//tmp에 다음 띄어쓰기 기준으로 끊어진 문자를 저장
	}
	return pop_ts(&ts);	//반복이 끝나면 스택의 제일 위에 남아있는 트리를 리턴
}

int main() {
	printf("*****주의사항*****\n");
	printf("이 계산기에서는 사칙연산, 음수계산, 삼각함수, 지수함수, 로그함수의 계산이 가능합니다.\n");
	printf("1. 음수를 적으실 때는 항상 앞뒤에 소괄호를 함께 적어주세요.\n");
	printf("2. 삼각함수를 입력하실 때는 sin,cos,tan의 첫 글자만 적어주세요.\n");
	printf("3. 삼각함수에 계산하실 각도를 입력하실 때는 라디안 단위로 입력해주세요.\n");
	printf("4. 지수함수를 입력하실 때는 e, 로그함수를 입력하실 때는 l을 적어주세요.\n");
	printf("ex) (-5)+s2+3*5-l(e2)\n");
	printf("\n\n");

	char input[MAX_STACK_SIZE];
	
	printf("계산할 중위표시수식을 입력해주세요.\n");
	gets(input);
	
	char* postfix = infix_to_postfix(input);
	printf("\n후위표시수식: %s\n", postfix);

	TreeNode* exp = make_exp_Tree(postfix);

	printf("전위순회: ");
	PrintNode_preorder(exp);

	printf("\n중위순회: ");;
	PrintNode_inorder(exp);

	printf("\n후위순회: ");
	PrintNode_postorder(exp);

	printf("\n레벨순회: ");
	PrintNode_levelorder(exp);
	printf("\n");

	double result = calculate_exp_Tree(exp);
	printf("\n계산값: %f\n", result);

	FreeTree(exp);
	return 0;
}