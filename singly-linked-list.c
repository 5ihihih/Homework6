#include<stdio.h>
#include<stdlib.h>

/*�����Ϳ� �ּҸ� ������ �� �ִ� Node���� ����*/
typedef struct Node {
	int key;
	struct Node* link;
} listNode;

/*ù��° ��带 ����Ű�� ������ ����*/
typedef struct Head {
	struct Node* first;
} headNode;

headNode* initialize(headNode* h);
int freeList(headNode* h);
int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);
void printList(headNode* h);

int main()
{
    printf("[----- [����ȭ] [2022078036] -----]\n\n");

	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/*����Ʈ�� �ʱ�ȭ�ϴ� �Լ�*/
headNode* initialize(headNode* h) {

	/*���� ����Ʈ�� �ƴ� ��� freelist()�� ȣ���� ���鸮��Ʈ�� �����*/
	if(h != NULL)   
		freeList(h);

    /*����尡 �ƹ��͵� ����Ű�� �ʵ��� �Ѵ�*/
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

/*����Ʈ�� ���� ����Ʈ�� ����� �Լ�*/
int freeList(headNode* h){
	listNode* p = h->first;

	listNode* prev = NULL;
	/*p�� NULL�� ���Ե� ������ ����� �޸� ������ �ݺ��Ѵ�*/
	while(p != NULL) {      
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}

/*����Ʈ�� �պκп� ��带 �����ϴ� �Լ�*/
int insertFirst(headNode* h, int key){

	/*������ ��带 ����*/
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	/*������ ����� link�� ù��° ��尡 �ǵ��� �Ѵ�*/
	node->link = h->first;
	h->first = node;

	return 0;
}


/*��带 �����ϴ� �Լ�*/
int insertNode(headNode* h, int key){

    /*������ ��� ����*/
    listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;   
    node->link = NULL;

    if(h->first == NULL){
        h->first = node;
        return 0;
    } 

	listNode* n = h->first;
	listNode* trail = h->first;

    while(n != NULL){
        /*n�� ����Ű�� ����� ������ >= ������ ����� �������� ���
        n�� ����Ű�� ����� �տ� ���ο� ��带 �����ؾ� �Ѵ�*/
        if(n->key >= key){       
            /*n�� ù��° ��带 ����ų ���
			��带 ù �κп� ����*/ 
            if(n == h->first){
                h->first = node;
                node->link = n;
            }
            /*n�� �ι�° �̻� ��带 ����ų ���
            trail�� ����Ű�� ���� n�� ����Ű�� ����� ���̿� ���ο� ��� ����*/
            else{
				node->link = n;
				trail->link = node;
            }
            return 0;
        }
        /*n�� ����Ű�� ����� ������ < ������ ����� ������
        trail�� n�� ���� ��带 ����Ű���� �Ѵ�*/
        trail = n;   
        n = n->link; 
    }
}

/*����Ʈ�� �������� ��带 �����ϴ� �Լ�*/
int insertLast(headNode* h, int key){

    /*������ ��� ����*/
    listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

    /*�� ����Ʈ�� ��� ������ ��带 ����Ʈ�� ù��° ���� �����*/
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

    /*n�� ����Ʈ�� ������ ��带 ����Ű���� �ݺ��Ѵ�*/
	while(n->link != NULL) {
		n = n->link;
	}

    /*n�� ����Ű�� ��忡 ������ ����� �ּҸ� �ִ´�*/
	n->link = node;
	return 0;
}


/*ù��° ��带 �����ϴ� �Լ�*/
int deleteFirst(headNode* h){

    /*�� ����Ʈ�� ��� "nothing to delete."�� ����Ѵ�*/
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;

    /*������ ����� ���� ����� �ּҸ� first�� �����ϰ� �޸𸮸� �����Ѵ�*/
	h->first = n->link;
	free(n);

	return 0;
}


/*��带 �����ϴ� �Լ�*/
int deleteNode(headNode* h, int key){

    /*�� ����Ʈ�� ��� "nothing to delete."�� ����Ѵ�*/
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	while(n != NULL) {
        /*n�� ����Ű�� ����� ������ = ������ ����� ������*/
		if(n->key == key) {
            /*n�� ù��° ��带 ����ų ��� first�� �ι�° ��带 ����Ű���� �Ѵ�*/
			if(n == h->first) {
				h->first = n->link;
			} 
            /*n�� �ι�° �̻��� ��带 ����ų ��� trail�� �ٴ��� ��带 ����Ű���� �Ѵ�*/
            else { 
				trail->link = n->link;
			}
            /*������ ����� �޸𸮸� �����Ѵ�*/
			free(n);
			return 0;
		}

        /*n�� ����Ű�� ����� ������ != ������ ����� ������
        trail�� n�� ���� ��带 ����Ű���� �Ѵ�*/
		trail = n;
		n = n->link;
	}

    /*�Է¹��� �����Ͱ� ����Ʈ�� ���� ��� n�� NULL���� ���� while���� ����������
     �Է¹��� �����͸� ã�� �� ���ٴ� ������ ����Ѵ�*/
	printf("cannot find the node for key = %d\n", key);
	return 0;
}

/*������ ��带 �����ϴ� �Լ�*/
int deleteLast(headNode* h){

    /*�� ����Ʈ�� ��� "nothing to delete."�� ����Ѵ�*/
    if(h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

    /*n�� ����Ű�� ��尡 ������ ����� ��� ������ ����� �޸𸮸� �����Ѵ�*/
	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

    /*n�� ������ ��带 ����Ű�� �ʴ� ��� trail�� n�� ���� ����� �ּҸ� �ֱ⸦ �ݺ��Ѵ�*/
	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

    /*trail�� ����Ű�� ��忡 ��� �ּҰ��� NULL�� �����ϰ� ������ ����� �޸𸮸� �����Ѵ�*/
	trail->link = NULL;
	free(n);

	return 0;
}


/*����Ʈ�� �������� �迭�ϴ� �Լ�*/
int invertList(headNode* h){

    /*�� ����Ʈ�� ��� "nothing to invert..."�� ����Ѵ�*/
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

    
	while(n != NULL){
		trail = middle;         //������ �������� �Ǵ� �� ��� �� �� ��带 ����Ų��
		middle = n;             //������ �������� �Ǵ� �� ��� �� �� ��带 ����Ų��
		n = n->link;            //n�� ������ ����� �� ����� ���� ��带 ����Ű���� �Ѵ�
		middle->link = trail;   //����� ������ ���������� �����
	}

    /*���� ����Ʈ�� ������ ��带 ù��° ���� �����Ѵ�*/
	h->first = middle;

	return 0;
}

/*����Ʈ�� ����ϴ� �Լ�*/
void printList(headNode* h){
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

    /*�� ����� ��� "Nothing to print...."�� ����Ѵ�*/
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

    /*p�� ������ ��尡 ���� �ִ� NULL���ڰ� ���Ե� ������ ����� ����� �ݺ��Ѵ�*/
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

    /*����� ������ ����Ѵ�*/
	printf("  items = %d\n", i);
}
