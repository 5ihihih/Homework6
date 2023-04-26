#include<stdio.h>
#include<stdlib.h>

/*데이터와 주소를 저장할 수 있는 Node구조 선언*/
typedef struct Node {
	int key;
	struct Node* link;
} listNode;

/*첫번째 노드를 가리키는 포인터 선언*/
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
    printf("[----- [오인화] [2022078036] -----]\n\n");

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

/*리스트를 초기화하는 함수*/
headNode* initialize(headNode* h) {

	/*공백 리스트가 아닐 경우 freelist()를 호출해 공백리스트로 만든다*/
	if(h != NULL)   
		freeList(h);

    /*헤드노드가 아무것도 가리키지 않도록 한다*/
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

/*리스트를 공백 리스트로 만드는 함수*/
int freeList(headNode* h){
	listNode* p = h->first;

	listNode* prev = NULL;
	/*p에 NULL이 대입될 때까지 노드의 메모리 해제를 반복한다*/
	while(p != NULL) {      
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}

/*리스트의 앞부분에 노드를 삽입하는 함수*/
int insertFirst(headNode* h, int key){

	/*삽입할 노드를 생성*/
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	/*삽입할 노드의 link가 첫번째 노드가 되도록 한다*/
	node->link = h->first;
	h->first = node;

	return 0;
}


/*노드를 삽입하는 함수*/
int insertNode(headNode* h, int key){

    /*삽입할 노드 생성*/
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
        /*n이 가리키는 노드의 데이터 >= 삽입할 노드의 데이터일 경우
        n이 가리키는 노드의 앞에 새로운 노드를 삽입해야 한다*/
        if(n->key >= key){       
            /*n이 첫번째 노드를 가리킬 경우
			노드를 첫 부분에 삽입*/ 
            if(n == h->first){
                h->first = node;
                node->link = n;
            }
            /*n이 두번째 이상 노드를 가리킬 경우
            trail이 가리키는 노드와 n이 가리키는 노드의 사이에 새로운 노드 삽입*/
            else{
				node->link = n;
				trail->link = node;
            }
            return 0;
        }
        /*n이 가리키는 노드의 데이터 < 삽입할 노드의 데이터
        trail과 n이 다음 노드를 가리키도록 한다*/
        trail = n;   
        n = n->link; 
    }
}

/*리스트의 마지막에 노드를 삽입하는 함수*/
int insertLast(headNode* h, int key){

    /*삽입할 노드 생성*/
    listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

    /*빈 리스트일 경우 삽입할 노드를 리스트의 첫번째 노드로 만든다*/
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

    /*n이 리스트의 마지막 노드를 가리키도록 반복한다*/
	while(n->link != NULL) {
		n = n->link;
	}

    /*n이 가리키는 노드에 삽입할 노드의 주소를 넣는다*/
	n->link = node;
	return 0;
}


/*첫번째 노드를 삭제하는 함수*/
int deleteFirst(headNode* h){

    /*빈 리스트일 경우 "nothing to delete."를 출력한다*/
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;

    /*제거할 노드의 다음 노드의 주소를 first에 대입하고 메모리를 해제한다*/
	h->first = n->link;
	free(n);

	return 0;
}


/*노드를 삭제하는 함수*/
int deleteNode(headNode* h, int key){

    /*빈 리스트일 경우 "nothing to delete."를 출력한다*/
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	while(n != NULL) {
        /*n이 가리키는 노드의 데이터 = 삭제할 노드의 데이터*/
		if(n->key == key) {
            /*n이 첫번째 노드를 가리킬 경우 first가 두번째 노드를 가리키도록 한다*/
			if(n == h->first) {
				h->first = n->link;
			} 
            /*n이 두번째 이상의 노드를 가리킬 경우 trail이 다다음 노드를 가리키도록 한다*/
            else { 
				trail->link = n->link;
			}
            /*삭제할 노드의 메모리를 해제한다*/
			free(n);
			return 0;
		}

        /*n이 가리키는 노드의 데이터 != 삭제할 노드의 데이터
        trail과 n이 다음 노드를 가리키도록 한다*/
		trail = n;
		n = n->link;
	}

    /*입력받은 데이터가 리스트에 없을 경우 n이 NULL값을 갖고 while문을 빠져나오고
     입력받은 데이터를 찾을 수 없다는 문구를 출력한다*/
	printf("cannot find the node for key = %d\n", key);
	return 0;
}

/*마지막 노드를 삭제하는 함수*/
int deleteLast(headNode* h){

    /*빈 리스트일 경우 "nothing to delete."를 출력한다*/
    if(h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

    /*n이 가리키는 노드가 마지막 노드일 경우 마지막 노드의 메모리를 해제한다*/
	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

    /*n이 마지막 노드를 가리키지 않는 경우 trail과 n에 다음 노드의 주소를 넣기를 반복한다*/
	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

    /*trail이 가리키는 노드에 담긴 주소값을 NULL로 변경하고 마지막 노드의 메모리를 해제한다*/
	trail->link = NULL;
	free(n);

	return 0;
}


/*리스트를 역순으로 배열하는 함수*/
int invertList(headNode* h){

    /*빈 리스트일 경우 "nothing to invert..."를 출력한다*/
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

    
	while(n != NULL){
		trail = middle;         //연결이 역방향이 되는 두 노드 중 앞 노드를 가리킨다
		middle = n;             //연결이 역방향이 되는 두 노드 중 뒷 노드를 가리킨다
		n = n->link;            //n이 위에서 언급한 뒷 노드의 다음 노드를 가리키도록 한다
		middle->link = trail;   //노드의 연결을 역방향으로 만든다
	}

    /*원래 리스트의 마지막 노드를 첫번째 노드로 지정한다*/
	h->first = middle;

	return 0;
}

/*리스트를 출력하는 함수*/
void printList(headNode* h){
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

    /*빈 노드일 경우 "Nothing to print...."를 출력한다*/
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

    /*p에 마지막 노드가 갖고 있는 NULL문자가 대입될 때까지 노드의 출력을 반복한다*/
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

    /*노드의 개수를 출력한다*/
	printf("  items = %d\n", i);
}
