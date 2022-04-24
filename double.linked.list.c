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
//<stdio.h>와 <stdlib.h>를 컴파일 전에 소스에 확장하도록 지시

//ListNode 구조체 선언
typedef struct Node {
	int key;	//값을 받을 key 선언
	struct Node* llink;	//왼쪽 link 선언
	struct Node* rlink;	//오른쪽 link 선언
} listNode;


//headNode 구조체 선언
typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

//프로그램의 메인함수
int main()
{
	char command;	
	int key;
    int count = 0;  //연결리스트를 생성하기전에 다른 메뉴 실행하지 못하도록 count변수 선언
	headNode* headnode=NULL;
	// 구조체 포인터변수 headnode를 선언

	printf("------- [고영민] [2019038003] -------\n");

	do{	//사용자가 q or Q를 입력하기 전까지 반복하는 do-while문
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		//메뉴출력

		printf("Command = ");
		scanf(" %c", &command);	//사용자로부터 명령을 입력받음

		switch(command) {	
		case 'z': case 'Z':	//command가 z or Z 일때
			initialize(&headnode);
            count ++;
			break;
		case 'p': case 'P':	//command가 p or P 일때
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			printList(headnode);
			break;
		case 'i': case 'I': //command가 i or I 일때
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D': //command가 d or D 일때
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': //command가 n or N 일때
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E': //command가 e or E 일때
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			deleteLast(headnode);
			break;
		case 'f': case 'F': //command가 f or F 일때
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T': //command가 t or T 일때
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			deleteFirst(headnode);
			break;
		case 'r': case 'R': //command가 r or R 일때
            if(count == 0 )
            {
                printf("Please enter the Z first.\n");
                break;
            }
			invertList(headnode);
			break;
		case 'q': case 'Q': //command가 q or Q 일때
			freeList(headnode);
			break;
		default:	//command가 비정상적 값일때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");	//오류메세지 출력
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;	//1 반환
}

//연결리스트를 생성하는 함수
int initialize(headNode** h) {
	//실제 h의 값을 받아오기위해 이중포인터를 매개변수로 함

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));	
	//포인터 변수 h를 동적할당
	(*h)->first = NULL;
	//h의 first를 NULL로 연결

	return 1;	//1 반환
}

//연결리스트를 free하는 함수
int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;
	//listNode 포인터 변수 p 선언후 first 저장

	listNode* prev = NULL;
	//listNode 포인터 변수 prev 선언

	while(p != NULL) {	//p가 NULL이 될때까지
		prev = p;	
		p = p->rlink;
		free(prev);	
		//하나씩 free
	}
	free(h);	//마지막으로 h도 free

	return 0;	//0 반환
}

//연결리스트를 출력하는 함수
void printList(headNode* h) {
	int i = 0;
	listNode* p;
	//listNode 포인터 변수 p 선언

	printf("\n---PRINT\n");

	//h가 NULL값일때
	if(h == NULL) {
		printf("Nothing to print....\n");	//오류 메세지 출력
		return;	
	}

	//h가 NULL값이 아닐때
	p = h->first;	//p에 h의 first값을 저장 

	while(p != NULL) {	//p가 NULL일떄 까지
		printf("[ [%d]=%d ] ", i, p->key);	//인덱스와 값 출력
		p = p->rlink;	//오른쪽 link로 이동
		i++;	//i값 증가
	}

	printf("  items = %d\n", i);	//총 리스트 개수 출력
}




/**
 * list에 key에 대한 노드하나를 추가
 */
//연결리스트 마지막에 노드를 추가하는 함수
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	//listNode 포인터변수 node를 선언 후 동적할당
	node->key = key;
	//node의 key값에 사용자로 부터 입력받은 key값 저장
	node->rlink = NULL;	
	node->llink = NULL;
	//node의 rlink,llink NULL 저장

	if (h->first == NULL)	//연결리스트 비어있을때
	{
		h->first = node;	//첫번째 원솔ㄹ node로 설정
		return 0;	//0 반환
	}

	listNode* n = h->first;
	//listNode포인터 변수 n 선언 후 first 저장

	while(n->rlink != NULL) {	//연결리스트의 rlink가 NULL이 될때까지
		n = n->rlink;	//오른쪽으로 n을 이동
	}

	//n의 rlink가 NULL일때
	n->rlink = node;	//n의 rlink에 node를 연결
	node->llink = n;	//node의 llink를 n에 연결
	return 0;	//0 반환
}



/**
 * list의 마지막 노드 삭제
 */
//연결리스트의 마지막에서 노드를 삭제하는 함수
int deleteLast(headNode* h) {

	if (h->first == NULL)	//연결리스트가 비어있을때
	{
		printf("nothing to delete.\n");	//오류 매세지 출력
		return 0;	// 0 반환
	}

	listNode* n = h->first;
	//listNode 포인터 변수 n 선언후 first 저장
	listNode* trail = NULL;
	//listNode 포인터 변수 trail 선언

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {	
		h->first = NULL;	//first에 NULL 저장
		free(n);	//n free
		return 0;	//0 반환
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {	//n의 rlink가 NULL이 될때까지 
		trail = n;	//trail에 n값 저장
		n = n->rlink;	//n을 우측으로 이동
	}

	//n의 rlink가 NULL일때
	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL;	//n의 이전값의 rlink를 NULL로 변경
	free(n);	//n free

	return 0;	//0 반환
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
//연결리스트의 시작부분에 노드를 추가하는 함수
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	//listNode 포인터 변수 node선언 후 동적할당

	node->key = key;	//node의 key값에 사용자로부터 입력받은 key값 저장
	node->rlink = node->llink = NULL;
	//node의 rlink, llink에 NULL 저장

	//연결리스트가 비어있을때
	if(h->first == NULL)
	{
		h->first = node;	//first에 node 저장
		return 1;	//1 반환
	}

	node->rlink = h->first;	//node의 rlink에 first 연결
	node->llink = NULL;		//node의 llink에 NULL 저장

	listNode *p = h->first;	
	//listNode 포인터 변수 p선언 후 first 저장
	p->llink = node;	//p의 llink에 node 연결
	h->first = node;	//first의에 node 저장

	return 0;	//0 반환
}

/**
 * list의 첫번째 노드 삭제
 */
//연결리스트의 처음 부분에서 노드를 삭제하는 함수
int deleteFirst(headNode* h) {

	if (h->first == NULL)	//연결리스트가 비어있을때
	{
		printf("nothing to delete.\n");	//오류 메세지 출력
		return 0;	//0 반환
	}

	listNode* n = h->first;
	//listNode 포인터 변수 n 선언 후 first 저장
	h->first = n->rlink;
	//first에 n의 다음 값 저장

	free(n);	//n free

	return 0;	// 0 반환
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
//연결리스트를 역순으로 바꾸는 함수
int invertList(headNode* h) {


	if(h->first == NULL) {	//연결리스트가 비어있을때
		printf("nothing to invert...\n");	//오류 메세지 출력
		return 0;	//0 반환
	}
	listNode *n = h->first;
	//listNode 포인터 변수 n선언 후 first 저장
	listNode *trail = NULL;
	//listNode 포인터 변수 trial선언
	listNode *middle = NULL;
	//listNode 포인터 변수 middle선언

	while(n != NULL){	//n이 NULL이 될때까지
		trail = middle;	//trail에 middle 값 저장
		middle = n;		//middle에 n값 저장
		n = n->rlink;	//n을 우측으로 이동
		middle->rlink = trail;	//middle의 rlink에 trail 연결
		middle->llink = n;		//middle의 llink에 n 연결
	}

	//n이 NULL일때(middle은 마지막 값)
	h->first = middle;	//first에 middle 저장

	return 0;	//0 반환
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
//사용자로부터 key를 입력받아 key값보다 작은 값들 뒤에 추가하는 함수
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	//listNode 포인터 변수 node를 선언 후 동적할당
	node->key = key;	//node의 key값에 사용자로부터 입력받은 key값 저장
	node->llink = node->rlink = NULL;	//node의 llink와 rlink를 NULL로 저장

	if (h->first == NULL)	// 연결리스트가 비어있을때
	{
		h->first = node;	//first에 node 저장
		return 0;	//0 반환
	}

	listNode* n = h->first;	
	//listNode 포인터 변수 n 선언 후 first 저장

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {	//n이 NULL이 될때까지
		if(n->key >= key) {	//n의 key값이 사용자로부터 입력받은 key값 보다 크거나 같을때
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {	//n이 first일때
				insertFirst(h, key);	//처음에 삽입
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;	//node의 rlink에 n을 연결
				node->llink = n->llink;	//node의 llink에 n의 llink를 연결
				n->llink->rlink = node;	//n의 llink(n의 이전값)의 rlink에 node를 연결
			}
			return 0;	//0 반환
		}

		n = n->rlink;	//n을 우측으로 이동
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);	//마지막에 삽입
	return 0;	//0 반환
}


/**
 * list에서 key에 대한 노드 삭제
 */
//사용자로부터 key값을 입력받아 해당 노드를 삭제하는 함수
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)	//연결리스트가 비어있을때
	{
		printf("nothing to delete.\n");	//오류 메세지 출력
		return 1;	//1 반환
	}

	listNode* n = h->first;
	//listNode 포인터 변수 n 선언 후 first 저장

	while(n != NULL) {//n이 NULL이 될때까지
		if(n->key == key) {	//n의 key값이 사용자로부터 입력받은 key값과 같을때
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);	//처음에서 삭제
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h);	//마지막에서 삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //n의 llink(n의 좌측 값)의 rlink에 n의 rlink 연결
				n->rlink->llink = n->llink;	//n의 rlink(n의 우측 값)의 llink에 n의 llink 연결
				free(n);	//n free
			}
			return 1;	//1 반환
		}

		n = n->rlink;	//n을 우측으로 이동
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);	//오류 메세지 출력
	return 1;	//1 반환
}


