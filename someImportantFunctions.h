using namespace std;

#include <termios.h>
#include <stdio.h>
#include<iostream>

/**************************************************************************************************************************************************************/

static struct termios old;
static struct termios new_;
/* Initialize new terminal i/o settings */

void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new_ = old; /* make new settings same as old settings */
  new_.c_lflag &= ~ICANON; /* disable buffered i/o */
  new_.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new_); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
} 

/**********************************************************************************************************************************************************/

//compares strings ignoring case
int stricmp (const char *p1, const char *p2)
{
  const unsigned char *s1 = (const unsigned char *) p1;
  const unsigned char *s2 = (const unsigned char *) p2;
  unsigned char c1, c2, c3;
  do
  {
      c1 = (unsigned char) *s1++;
      c2 = (unsigned char) *s2++;
	  c3 = (unsigned char) *s2;
	  
	  if (c1 == '\0' && ((c2 == ' ' && (c3 == '!' || c3 == '?' || c3 == '.')) || c2 == '?' || c2 == '!' || c2 == '.'))
        return 0;

	  if(c1 == '\0')
		  return c1 - c2;
  }
  while (c1 == c2 || c1 == c2-32 || c1 == c2+32 );	
 	  return c1 - c2;
}

/**********************************************************************************************************************************************************/

/*this structure has been created for manipulating
numbers in the math operations
class Stack
{
	private:
		int top;
		int stck[5];
	public:
		int pop();
		void push(int );
		Stack()
		{
			top = -1;
		}
};

int Stack::pop()
{
	if(top == -1)
	{
		cout<<"\nStack is empty"<<endl;
		return 0;
	}
	return (stck[top--]);
}

void Stack::push(int item)
{
	if(top >= 4)
	{
		cout<<"\nStack Ovewflow"<<endl;
		return;
	}
	stck[++top] = item;
}*/


/************************************************************************************************************************************************************/


//Singly Linked List for strings

class LinkedList
{
	private:
		typedef struct Node
		{
			//defines data for user defined type
			char data[20];
			LinkedList *next;
		}Node;

		Node *START;

	public:
		LinkedList()
		{
			START = NULL;
		}

		void traverse();
		void insert(char*);
		void remove(char*);
		char* getFirst();
		~LinkedList();
};

void LinkedList::traverse()
{
		LinkedList *p;
		p = START;
		while(p != NULL)
		{
			cout<<endl<<p->data;
			p = p->next;
		}
}

void LinkedList::insert(const char* const d)
{
	//Node to be inserted
	Node *temp;
	temp = new Node;

	//copies given data to node
	strcpy(&temp->data,d);
	temp->next = NULL;

	if(START = NULL)
		START = temp;
	else
	{
		Node *ptr = START;
		//until end is reached
		while(ptr->next != NULL)
			ptr = ptr->next;

		//inserts node in list
		ptr->next = temp;
	}
}

void LinkedList::remove(char *d)
{
	Node *q = START;
	Node *prev = NULL;
	//if the given string is in the first node
	if(strcmp(d,START->data) == 0)
	{
		START = START->next;
		delete q;
		return;
	}

	while(strcmp(d,q->data) != 0 || q->next != NULL)
	{
		prev = q;
		q = q->next;
	}

	prev = q->next;
	delete q;
}

char* LinkedList::getFirst()
{
	char temp[20];
	Node *p = START;
	strcpy(temp,START->data);
	START = START->next;
	delete p;
}

LinkedList::~LinkedList()
{
	Node *p = START;
	//destroys the linked list object
	while(p != NULL)
	{
		p = START->next;
		delete START;
		START = p;
	}
}
