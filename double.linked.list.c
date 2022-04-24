/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>
//<stdio.h>�� <stdlib.h>�� ������ ���� �ҽ��� Ȯ���ϵ��� ����

//ListNode ����ü ����
typedef struct Node {
	int key;	//���� ���� key ����
	struct Node* llink;	//���� link ����
	struct Node* rlink;	//������ link ����
} listNode;


//headNode ����ü ����
typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         lab3�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

//���α׷��� �����Լ�
int main()
{
	char command;	
	int key;
    int count = 0;  //���Ḯ��Ʈ�� �����ϱ����� �ٸ� �޴� �������� ���ϵ��� count���� ����
	headNode* headnode=NULL;
	// ����ü �����ͺ��� headnode�� ����

	printf("------- [����] [2019038003] -------\n");

	do{	//����ڰ� q or Q�� �Է��ϱ� ������ �ݺ��ϴ� do-while��
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		//�޴����

		printf("Command = ");
		scanf(" %c", &command);	//����ڷκ��� ����� �Է¹���

		switch(command) {	
		case 'z': case 'Z':	//command�� z or Z �϶�
			initialize(&headnode);
            count ++;
			break;
		case 'p': case 'P':	//command�� p or P �϶�
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			printList(headnode);
			break;
		case 'i': case 'I': //command�� i or I �϶�
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D': //command�� d or D �϶�
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': //command�� n or N �϶�
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E': //command�� e or E �϶�
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			deleteLast(headnode);
			break;
		case 'f': case 'F': //command�� f or F �϶�
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T': //command�� t or T �϶�
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			deleteFirst(headnode);
			break;
		case 'r': case 'R': //command�� r or R �϶�
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			invertList(headnode);
			break;
		case 'q': case 'Q': //command�� q or Q �϶�
			freeList(headnode);
			break;
		default:	//command�� �������� ���϶�
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");	//�����޼��� ���
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;	//1 ��ȯ
}

//���Ḯ��Ʈ�� �����ϴ� �Լ�
int initialize(headNode** h) {
	//���� h�� ���� �޾ƿ������� ���������͸� �Ű������� ��

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (headNode*)malloc(sizeof(headNode));	
	//������ ���� h�� �����Ҵ�
	(*h)->first = NULL;
	//h�� first�� NULL�� ����

	return 1;	//1 ��ȯ
}

//���Ḯ��Ʈ�� free�ϴ� �Լ�
int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;
	//listNode ������ ���� p ������ first ����

	listNode* prev = NULL;
	//listNode ������ ���� prev ����

	while(p != NULL) {	//p�� NULL�� �ɶ�����
		prev = p;	
		p = p->rlink;
		free(prev);	
		//�ϳ��� free
	}
	free(h);	//���������� h�� free

	return 0;	//0 ��ȯ
}

//���Ḯ��Ʈ�� ����ϴ� �Լ�
void printList(headNode* h) {
	int i = 0;
	listNode* p;
	//listNode ������ ���� p ����

	printf("\n---PRINT\n");

	//h�� NULL���϶�
	if(h == NULL) {
		printf("Nothing to print....\n");	//���� �޼��� ���
		return;	
	}

	//h�� NULL���� �ƴҶ�
	p = h->first;	//p�� h�� first���� ���� 

	while(p != NULL) {	//p�� NULL�ϋ� ����
		printf("[ [%d]=%d ] ", i, p->key);	//�ε����� �� ���
		p = p->rlink;	//������ link�� �̵�
		i++;	//i�� ����
	}

	printf("  items = %d\n", i);	//�� ����Ʈ ���� ���
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
//���Ḯ��Ʈ �������� ��带 �߰��ϴ� �Լ�
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	//listNode �����ͺ��� node�� ���� �� �����Ҵ�
	node->key = key;
	//node�� key���� ����ڷ� ���� �Է¹��� key�� ����
	node->rlink = NULL;	
	node->llink = NULL;
	//node�� rlink,llink NULL ����

	if (h->first == NULL)	//���Ḯ��Ʈ ���������
	{
		h->first = node;	//ù��° ���֤� node�� ����
		return 0;	//0 ��ȯ
	}

	listNode* n = h->first;
	//listNode������ ���� n ���� �� first ����

	while(n->rlink != NULL) {	//���Ḯ��Ʈ�� rlink�� NULL�� �ɶ�����
		n = n->rlink;	//���������� n�� �̵�
	}

	//n�� rlink�� NULL�϶�
	n->rlink = node;	//n�� rlink�� node�� ����
	node->llink = n;	//node�� llink�� n�� ����
	return 0;	//0 ��ȯ
}



/**
 * list�� ������ ��� ����
 */
//���Ḯ��Ʈ�� ���������� ��带 �����ϴ� �Լ�
int deleteLast(headNode* h) {

	if (h->first == NULL)	//���Ḯ��Ʈ�� ���������
	{
		printf("nothing to delete.\n");	//���� �ż��� ���
		return 0;	// 0 ��ȯ
	}

	listNode* n = h->first;
	//listNode ������ ���� n ������ first ����
	listNode* trail = NULL;
	//listNode ������ ���� trail ����

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->rlink == NULL) {	
		h->first = NULL;	//first�� NULL ����
		free(n);	//n free
		return 0;	//0 ��ȯ
	}

	/* ������ ������ �̵� */
	while(n->rlink != NULL) {	//n�� rlink�� NULL�� �ɶ����� 
		trail = n;	//trail�� n�� ����
		n = n->rlink;	//n�� �������� �̵�
	}

	//n�� rlink�� NULL�϶�
	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->rlink = NULL;	//n�� �������� rlink�� NULL�� ����
	free(n);	//n free

	return 0;	//0 ��ȯ
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
//���Ḯ��Ʈ�� ���ۺκп� ��带 �߰��ϴ� �Լ�
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	//listNode ������ ���� node���� �� �����Ҵ�

	node->key = key;	//node�� key���� ����ڷκ��� �Է¹��� key�� ����
	node->rlink = node->llink = NULL;
	//node�� rlink, llink�� NULL ����

	//���Ḯ��Ʈ�� ���������
	if(h->first == NULL)
	{
		h->first = node;	//first�� node ����
		return 1;	//1 ��ȯ
	}

	node->rlink = h->first;	//node�� rlink�� first ����
	node->llink = NULL;		//node�� llink�� NULL ����

	listNode *p = h->first;	
	//listNode ������ ���� p���� �� first ����
	p->llink = node;	//p�� llink�� node ����
	h->first = node;	//first�ǿ� node ����

	return 0;	//0 ��ȯ
}

/**
 * list�� ù��° ��� ����
 */
//���Ḯ��Ʈ�� ó�� �κп��� ��带 �����ϴ� �Լ�
int deleteFirst(headNode* h) {

	if (h->first == NULL)	//���Ḯ��Ʈ�� ���������
	{
		printf("nothing to delete.\n");	//���� �޼��� ���
		return 0;	//0 ��ȯ
	}

	listNode* n = h->first;
	//listNode ������ ���� n ���� �� first ����
	h->first = n->rlink;
	//first�� n�� ���� �� ����

	free(n);	//n free

	return 0;	// 0 ��ȯ
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
//���Ḯ��Ʈ�� �������� �ٲٴ� �Լ�
int invertList(headNode* h) {


	if(h->first == NULL) {	//���Ḯ��Ʈ�� ���������
		printf("nothing to invert...\n");	//���� �޼��� ���
		return 0;	//0 ��ȯ
	}
	listNode *n = h->first;
	//listNode ������ ���� n���� �� first ����
	listNode *trail = NULL;
	//listNode ������ ���� trial����
	listNode *middle = NULL;
	//listNode ������ ���� middle����

	while(n != NULL){	//n�� NULL�� �ɶ�����
		trail = middle;	//trail�� middle �� ����
		middle = n;		//middle�� n�� ����
		n = n->rlink;	//n�� �������� �̵�
		middle->rlink = trail;	//middle�� rlink�� trail ����
		middle->llink = n;		//middle�� llink�� n ����
	}

	//n�� NULL�϶�(middle�� ������ ��)
	h->first = middle;	//first�� middle ����

	return 0;	//0 ��ȯ
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
//����ڷκ��� key�� �Է¹޾� key������ ���� ���� �ڿ� �߰��ϴ� �Լ�
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	//listNode ������ ���� node�� ���� �� �����Ҵ�
	node->key = key;	//node�� key���� ����ڷκ��� �Է¹��� key�� ����
	node->llink = node->rlink = NULL;	//node�� llink�� rlink�� NULL�� ����

	if (h->first == NULL)	// ���Ḯ��Ʈ�� ���������
	{
		h->first = node;	//first�� node ����
		return 0;	//0 ��ȯ
	}

	listNode* n = h->first;	
	//listNode ������ ���� n ���� �� first ����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {	//n�� NULL�� �ɶ�����
		if(n->key >= key) {	//n�� key���� ����ڷκ��� �Է¹��� key�� ���� ũ�ų� ������
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {	//n�� first�϶�
				insertFirst(h, key);	//ó���� ����
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n;	//node�� rlink�� n�� ����
				node->llink = n->llink;	//node�� llink�� n�� llink�� ����
				n->llink->rlink = node;	//n�� llink(n�� ������)�� rlink�� node�� ����
			}
			return 0;	//0 ��ȯ
		}

		n = n->rlink;	//n�� �������� �̵�
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);	//�������� ����
	return 0;	//0 ��ȯ
}


/**
 * list���� key�� ���� ��� ����
 */
//����ڷκ��� key���� �Է¹޾� �ش� ��带 �����ϴ� �Լ�
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)	//���Ḯ��Ʈ�� ���������
	{
		printf("nothing to delete.\n");	//���� �޼��� ���
		return 1;	//1 ��ȯ
	}

	listNode* n = h->first;
	//listNode ������ ���� n ���� �� first ����

	while(n != NULL) {//n�� NULL�� �ɶ�����
		if(n->key == key) {	//n�� key���� ����ڷκ��� �Է¹��� key���� ������
			if(n == h->first) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h);	//ó������ ����
			} else if (n->rlink == NULL){ /* ������ ����� ��� */
				deleteLast(h);	//���������� ����
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink; //n�� llink(n�� ���� ��)�� rlink�� n�� rlink ����
				n->rlink->llink = n->llink;	//n�� rlink(n�� ���� ��)�� llink�� n�� llink ����
				free(n);	//n free
			}
			return 1;	//1 ��ȯ
		}

		n = n->rlink;	//n�� �������� �̵�
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);	//���� �޼��� ���
	return 1;	//1 ��ȯ
}


