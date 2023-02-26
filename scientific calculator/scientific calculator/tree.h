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

//�θ� ���� �� �ڽĳ�带 �����ϴ� ����Ʈ���� ����� �Լ�
TreeNode* CreateNode(element_t* a, TreeNode* b, TreeNode* c) {
	TreeNode* NewNode = (TreeNode*)malloc(sizeof(TreeNode));
	strcpy(NewNode->data, a);
	NewNode->left = b;
	NewNode->right = c;

	return NewNode;
}

//Ʈ���� ������ȸ�ϸ� ����ϴ� �Լ�
void PrintNode_preorder(TreeNode* Node) {
	if (Node != NULL) {
		printf("%s", Node->data);
		printf(" ");
		PrintNode_preorder(Node->left);
		PrintNode_preorder(Node->right);
	}
}

//Ʈ���� ������ȸ�ϸ� ����ϴ� �Լ�
void PrintNode_inorder(TreeNode* Node) {
	if (Node != NULL) {
		PrintNode_inorder(Node->left);
		printf("%s", Node->data);
		printf(" ");
		PrintNode_inorder(Node->right);
	}
}

//Ʈ���� ������ȸ�ϸ� ����ϴ� �Լ�
void PrintNode_postorder(TreeNode* Node) {
	if (Node != NULL) {
		PrintNode_postorder(Node->left);
		PrintNode_postorder(Node->right);
		printf("%s", Node->data);
		printf(" ");
	}
}

//���� Ʈ���� ����ϴ� �Լ�
double calculate_exp_Tree(TreeNode* root) {
	if (root == NULL)
		return 0;

	if (root->left == NULL && root->right == NULL) {	//�ܸ� �����
		return atof(root->data);	//�����͸� �Ǽ��� ��ȯ�Ͽ� ����
	}
	else if (root->left == NULL && root->right != NULL) {	//��忡 �ﰢ�Լ��� ����Ǿ� �ִٸ�
		double right = calculate_exp_Tree(root->right);
		if (strcmp(root->data, "s") == 0) {
			return sin(right);	//sin�Լ��� ��갪�� ����
		}
		else if (strcmp(root->data, "c") == 0) {
			return cos(right);	//cos�Լ��� ��갪�� ����
		}
		else if (strcmp(root->data, "t") == 0) {
			return tan(right);	//tan�Լ��� ��갪�� ����
		}
		else if (strcmp(root->data, "e") == 0) {
			return exp(right);	//tan�Լ��� ��갪�� ����
		}
		else if (strcmp(root->data, "l") == 0) {
			return log(right);	//tan�Լ��� ��갪�� ����
		}
	}
	else {
		double left = calculate_exp_Tree(root->left);	//���� �ڽ� ����� ��갪�� left�� ����
		double right = calculate_exp_Tree(root->right);	//������ �ڽ� ����� ��갪�� right�� ����

		//�� �����ȣ�� ���� �˸��� ������ �Ѵ�
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

//Ʈ���� free�ϴ� �Լ�
void FreeTree(TreeNode* Root) {
	if (Root == NULL)
		return;
	FreeTree(Root->left);
	FreeTree(Root->right);
	FreeTree(Root);
}

typedef struct {	//Ʈ���� ���ҷ� ���� ť
	TreeNode* data[MAX_STACK_SIZE];
	int front, rear;
} tree_Queue;

void init_queue_tq(tree_Queue* q) {	//����ť�� �ʱ�ȭ�ϴ� �Լ�
	q->front = q->rear = 0;
}

int is_empty_tq(tree_Queue* q) {	//����ť�� ����ִ��� �˻��ϴ� �Լ�
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}

int is_full_tq(tree_Queue* q) {	//����ť�� ���� ���ִ��� �˻��ϴ� �Լ�
	if ((q->rear + 1) % MAX_STACK_SIZE == q->front)
		return 1;
	else
		return 0;
}

void enqueue_tq(tree_Queue* q, TreeNode* a) {	//����ť�� ���Ҹ� ����ִ� �Լ�
	if (is_full_tq(q) == 1) {
		printf("ť�� ��ȭ�����Դϴ�.");
		return;
	}
	q->rear = (q->rear + 1) % MAX_STACK_SIZE;
	q->data[q->rear] = a;
}

TreeNode* dequeue_tq(tree_Queue* q) {	//����ť���� ���Ҹ� ������ �Լ�
	if (is_empty_tq(q) == 1) {
		printf("ť�� ��������Դϴ�.");
		return 0;
	}
	q->front = (q->front + 1) % MAX_STACK_SIZE;
	return q->data[q->front];
}

//ť�� ����Ͽ� Ʈ���� ������ȸ�ϴ� �Լ�
void PrintNode_levelorder(TreeNode * Node) {
	tree_Queue q;	//q��� ����ť ����
	init_queue_tq(&q);	//q �ʱ�ȭ

	if (Node == NULL)
		return;
	enqueue_tq(&q, Node);	//Node�� NULL�� �ƴ϶�� ����ť�� ����ִ´�.
	while (is_empty_tq(&q) == 0) {	//����ť�� �� ������ �ݺ�
		Node = dequeue_tq(&q);	//Node�� dequeue_tq�� ���� ����
		printf("%s", Node->data);	//Node�� ���� ����� ��
		printf(" ");
		//Node�� left�� right�� enqueue_tq�Ѵ�
		if (Node->left)	
			enqueue_tq(&q, Node->left);
		if (Node->right)
			enqueue_tq(&q, Node->right);
	}
}