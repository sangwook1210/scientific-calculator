#pragma once
#pragma warning(disable:4996)
#define _CRT_SECRURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef char element_t;
typedef struct TreeNode {
	element_t data[10];
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

//부모 노드와 두 자식노드를 연결하는 이진트리를 만드는 함수
TreeNode* CreateNode(element_t* a, TreeNode* b, TreeNode* c) {
	TreeNode* NewNode = (TreeNode*)malloc(sizeof(TreeNode));
	strcpy(NewNode->data, a);
	NewNode->left = b;
	NewNode->right = c;

	return NewNode;
}

//트리를 전위순회하며 출력하는 함수
void PrintNode_preorder(TreeNode* Node) {
	if (Node != NULL) {
		printf("%s", Node->data);
		printf(" ");
		PrintNode_preorder(Node->left);
		PrintNode_preorder(Node->right);
	}
}

//트리를 중위순회하며 출력하는 함수
void PrintNode_inorder(TreeNode* Node) {
	if (Node != NULL) {
		PrintNode_inorder(Node->left);
		printf("%s", Node->data);
		printf(" ");
		PrintNode_inorder(Node->right);
	}
}

//트리를 후위순회하며 출력하는 함수
void PrintNode_postorder(TreeNode* Node) {
	if (Node != NULL) {
		PrintNode_postorder(Node->left);
		PrintNode_postorder(Node->right);
		printf("%s", Node->data);
		printf(" ");
	}
}

//연산 트리를 계산하는 함수
double calculate_exp_Tree(TreeNode* root) {
	if (root == NULL)
		return 0;

	if (root->left == NULL && root->right == NULL) {	//단말 노드라면
		return atof(root->data);	//데이터를 실수로 변환하여 리턴
	}
	else if (root->left == NULL && root->right != NULL) {	//노드에 삼각함수가 저장되어 있다면
		double right = calculate_exp_Tree(root->right);
		if (strcmp(root->data, "s") == 0) {
			return sin(right);	//sin함수의 계산값을 리턴
		}
		else if (strcmp(root->data, "c") == 0) {
			return cos(right);	//cos함수의 계산값을 리턴
		}
		else if (strcmp(root->data, "t") == 0) {
			return tan(right);	//tan함수의 계산값을 리턴
		}
		else if (strcmp(root->data, "e") == 0) {
			return exp(right);	//tan함수의 계산값을 리턴
		}
		else if (strcmp(root->data, "l") == 0) {
			return log(right);	//tan함수의 계산값을 리턴
		}
	}
	else {
		double left = calculate_exp_Tree(root->left);	//왼쪽 자식 노드의 계산값을 left에 저장
		double right = calculate_exp_Tree(root->right);	//오른쪽 자식 노드의 계산값을 right에 저장

		//각 연산기호에 맞춰 알맞은 연산을 한다
		if (strcmp(root->data, "+") == 0) {
			return left + right;
		}
		else if (strcmp(root->data, "-") == 0) {
			return left - right;
		}
		else if (strcmp(root->data, "*") == 0) {
			return left * right;
		}
		else if (strcmp(root->data, "/") == 0) {
			return left / right;
		}
		else if (strcmp(root->data, "^") == 0) {
			return pow(left, right);
		}
	}
}

//트리를 free하는 함수
void FreeTree(TreeNode* Root) {
	if (Root == NULL)
		return;
	FreeTree(Root->left);
	FreeTree(Root->right);
	FreeTree(Root);
}

typedef struct {	//트리가 원소로 들어가는 큐
	TreeNode* data[MAX_STACK_SIZE];
	int front, rear;
} tree_Queue;

void init_queue_tq(tree_Queue* q) {	//원형큐를 초기화하는 함수
	q->front = q->rear = 0;
}

int is_empty_tq(tree_Queue* q) {	//원형큐가 비어있는지 검사하는 함수
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}

int is_full_tq(tree_Queue* q) {	//원형큐가 가득 차있는지 검사하는 함수
	if ((q->rear + 1) % MAX_STACK_SIZE == q->front)
		return 1;
	else
		return 0;
}

void enqueue_tq(tree_Queue* q, TreeNode* a) {	//원형큐에 원소를 집어넣는 함수
	if (is_full_tq(q) == 1) {
		printf("큐가 포화상태입니다.");
		return;
	}
	q->rear = (q->rear + 1) % MAX_STACK_SIZE;
	q->data[q->rear] = a;
}

TreeNode* dequeue_tq(tree_Queue* q) {	//원형큐에서 원소를 꺼내는 함수
	if (is_empty_tq(q) == 1) {
		printf("큐가 공백상태입니다.");
		return 0;
	}
	q->front = (q->front + 1) % MAX_STACK_SIZE;
	return q->data[q->front];
}

//큐를 사용하여 트리를 레벨순회하는 함수
void PrintNode_levelorder(TreeNode * Node) {
	tree_Queue q;	//q라는 원형큐 생성
	init_queue_tq(&q);	//q 초기화

	if (Node == NULL)
		return;
	enqueue_tq(&q, Node);	//Node가 NULL이 아니라면 원형큐에 집어넣는다.
	while (is_empty_tq(&q) == 0) {	//원형큐가 빌 때까지 반복
		Node = dequeue_tq(&q);	//Node에 dequeue_tq한 것을 대입
		printf("%s", Node->data);	//Node의 값을 출력한 후
		printf(" ");
		//Node의 left와 right를 enqueue_tq한다
		if (Node->left)	
			enqueue_tq(&q, Node->left);
		if (Node->right)
			enqueue_tq(&q, Node->right);
	}
}