#define _CRT_SECRURE_NO_WARNINGS
#define MAX_STACK_SIZE 255
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include "tree.h"
#include "tree_stack.h"

//�������� �켱������ �����ִ� �Լ�
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

//���� ǥ�� ������ ���� ǥ�� �������� ��ȯ���ִ� �Լ�
const char* infix_to_postfix(char infix[]) {
	char ch, top_op;
	int length = strlen(infix);
	char* postfix = malloc(sizeof(char) * MAX_STACK_SIZE);
	int j = 0;
	StackType s;
	init_stack(&s);

	for (int i = 0; i < length; i++) {	//���� ǥ�� ������ ���̸�ŭ �ݺ�
		ch = infix[i];	//����ǥ�� ������ �� ���ھ� ��� ch�� �����Ѵ�.

		//���� ch�� +-*/^sctel�� ���� �����ȣ���
		if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' ||
			ch == 's' || ch == 'c' || ch == 't' || ch == 'e' || ch == 'l') {
			//������ ���� ���� �ִ� ���� sctel���
			if (peek(&s) == 's' || peek(&s) == 'c' || peek(&s) == 't' || peek(&s) == 'e' || peek(&s) == 'l') {
				postfix[j++] = pop(&s);	//postfix[j]�� ���ÿ��� pop�� ���� ���� �� j 1����
				postfix[j++] = ' ';	//����
			}
			//������ ������� �ʰ� ch�� �켱������ ���ÿ��� peek�� �����ȣ�� �켱�������� �۰ų� ���ٸ�
			while ((is_empty(&s) == 0) && (prec(ch) <= prec(peek(&s)))) {
				postfix[j++] = pop(&s);	//postfix[j]�� ���ÿ��� pop�� ���� ���� �� j 1����
				postfix[j++] = ' ';	//����
			}
			push(&s, ch);	//���ÿ� ch�� push
		}
		//���� ch�� (���
		else if (ch == '(') {
			if (infix[i + 1] == '-') {	//��ȣ �ڿ� ������ ���� ���
				//(-1)�� 0 1 - �� ����� ����
				postfix[j++] = '0';
				postfix[j++] = ' ';
				i++;
				i++;
				postfix[j++] = infix[i++];
				postfix[j++] = ' ';
				postfix[j++] = '-';
				postfix[j++] = ' ';
			}
			else {	//��ȣ �ڰ� ������ �ƴ϶��
				push(&s, ch);	//���ÿ� ch�� push
			}
		}
		//���� ch�� )���
		else if (ch == ')') {
			top_op = pop(&s);
			while (top_op != '(') {	//top_op�� (�� �ƴ� ������ �ݺ�
				//���ÿ� �׿��ִ� ��� �����ȣ���� postfix�� ����
				postfix[j++] = top_op;
				postfix[j++] = ' ';
				top_op = pop(&s);
			}

			//������ ���� ���� �ִ� ���Ұ� �ﰢ�Լ� Ȥ�� ����,�α� �Լ����
			if (peek(&s) == 's' || peek(&s) == 'c' || peek(&s) == 't' || peek(&s) == 'e' || peek(&s) == 'l') {
				postfix[j++] = pop(&s);
				postfix[j++] = ' ';
			}
		}
		//���� ch�� �����ȣ�� �ƴ� ���ڶ��
		else {
			postfix[j++] = ch;
			if (infix[i + 1] == '+' || infix[i + 1] == '-' || infix[i + 1] == '*' || infix[i + 1] == '/' ||
				infix[i + 1] == '^' || infix[i + 1] == '(' || infix[i + 1] == ')' || infix[i + 1] == '\0') {
				postfix[j++] = ' ';
			}
		}
	}
	//���ÿ� �����ִ� ��� �����ȣ���� postfix�� ����
	while (is_empty(&s) == 0) {
		postfix[j++] = pop(&s);
		postfix[j++] = ' ';
	}
	//postfix�� ���� ����ִ� ��� �κ��� \0�� �ٲ۴�.
	for (int i = j; i < MAX_STACK_SIZE; i++)
		postfix[i] = '\0';
	
	return postfix;	//������� ���� ǥ����� ��ȯ
}

//���� ǥ�� ������ ������ �̿��Ͽ� Ʈ���� ����� �Լ�
TreeNode* make_exp_Tree(char* postfix) {
	tree_Stack ts;	//ts��� tree_Stack ������ ����
	init_stack_ts(&ts);	//ts�� �ʱ�ȭ

	char* tmp = strtok(postfix, " ");	//tmp�� postfix ���ڿ��� ���� �������� ���� ���� ����

	while (tmp != NULL) {	//�� �̻� ���� ���ڿ��� ���� ������ �ݺ�
		//���� ������ ���ڿ��� +-*/^�� ���� �����ȣ���
		if (strcmp(tmp, "+") == 0 || strcmp(tmp, "-") == 0 || strcmp(tmp, "*") == 0 || strcmp(tmp, "/") == 0 || strcmp(tmp, "^") == 0) {
			TreeNode* right = pop_ts(&ts);	//TreeNode�� right�� ���ÿ� ����� ���� pop�Ͽ� ����
			TreeNode* left = pop_ts(&ts);	//TreeNode�� left�� ���ÿ� ����� ���� pop�Ͽ� ����
			push_ts(&ts, CreateNode(tmp, left, right));	//������ �����ȣ�� �θ� ���� �ϰ�, ������ ���� ���� ����Ǿ��ִ� ���� �� ���� �ڽ� ���� �ϴ� Ʈ���� ���ÿ� ����
		}
		//���� ������ ���ڿ��� �ﰢ�Լ� Ȥ�� ����, �α��Լ����
		else if (strcmp(tmp, "s") == 0 || strcmp(tmp, "c") == 0 || strcmp(tmp, "t") == 0 || strcmp(tmp, "e") == 0 || strcmp(tmp, "l") == 0) {
			TreeNode* right = pop_ts(&ts);	//TreeNode�� right�� ���ÿ� ����� ���� pop�Ͽ� ����
			push_ts(&ts, CreateNode(tmp, NULL, right));//������ �����ȣ�� �θ� ���� �ϰ�, ������ ���� ���� ����Ǿ��ִ� ���Ҹ� �ڽ� ���� �ϴ� Ʈ���� ���ÿ� ����
		}
		//���� ������ ���ڿ��� �����ȣ�� �ƴ� ���ڶ��
		else {
			push_ts(&ts, CreateNode(tmp, NULL, NULL));	//������ ���ڸ� �θ� ���� �ϰ� NULL �� ���� �ڽ� ���� �ϴ� Ʈ���� ���ÿ� ����
		}

		tmp = strtok(NULL, " ");	//tmp�� ���� ���� �������� ������ ���ڸ� ����
	}
	return pop_ts(&ts);	//�ݺ��� ������ ������ ���� ���� �����ִ� Ʈ���� ����
}

int main() {
	printf("*****���ǻ���*****\n");
	printf("�� ���⿡���� ��Ģ����, �������, �ﰢ�Լ�, �����Լ�, �α��Լ��� ����� �����մϴ�.\n");
	printf("1. ������ ������ ���� �׻� �յڿ� �Ұ�ȣ�� �Բ� �����ּ���.\n");
	printf("2. �ﰢ�Լ��� �Է��Ͻ� ���� sin,cos,tan�� ù ���ڸ� �����ּ���.\n");
	printf("3. �ﰢ�Լ��� ����Ͻ� ������ �Է��Ͻ� ���� ���� ������ �Է����ּ���.\n");
	printf("4. �����Լ��� �Է��Ͻ� ���� e, �α��Լ��� �Է��Ͻ� ���� l�� �����ּ���.\n");
	printf("ex) (-5)+s2+3*5-l(e2)\n");
	printf("\n\n");

	char input[MAX_STACK_SIZE];
	
	printf("����� ����ǥ�ü����� �Է����ּ���.\n");
	gets(input);
	
	char* postfix = infix_to_postfix(input);
	printf("\n����ǥ�ü���: %s\n", postfix);

	TreeNode* exp = make_exp_Tree(postfix);

	printf("������ȸ: ");
	PrintNode_preorder(exp);

	printf("\n������ȸ: ");;
	PrintNode_inorder(exp);

	printf("\n������ȸ: ");
	PrintNode_postorder(exp);

	printf("\n������ȸ: ");
	PrintNode_levelorder(exp);
	printf("\n");

	double result = calculate_exp_Tree(exp);
	printf("\n��갪: %f\n", result);

	FreeTree(exp);
	return 0;
}