using namespace std;
#include<unistd.h>
#include<dos.h>
#include<windows.h>
#include <stdio.h>
#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<string.h>

#define FOUND 1
#define NOTFOUND 0

//for checking that the command found or not
short isCommandFound = NOTFOUND;

/* *************************************************************************************************************************************************************/
//function getch

TCHAR getch()
{
  DWORD mode, cc;
  HANDLE h = GetStdHandle( STD_INPUT_HANDLE );
  if (h == NULL)
  {
        return 0; // console not found
  }
  GetConsoleMode( h, &mode );
  SetConsoleMode( h, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT) );
  TCHAR c = 0;
  ReadConsole( h, &c, 1, &cc, NULL );
  SetConsoleMode( h, mode );
  return c;
}



/* *********************************************************************************************************************************************************/

//compares strings ignoring case
int xstricmp (const char *p1, const char *p2)
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

/* *********************************************************************************************************************************************************/

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


/* ***********************************************************************************************************************************************************/


//Singly Linked List for strings

class LinkedList
{
	private:
		typedef struct Node
		{
			//defines data for user defined type
			char data[20];
			struct Node *next;
		}Node;

		Node *START;

	public:
		LinkedList()
		{
			START = NULL;
		}

		void traverse();
		void insertData(const char* const);
		void removeData(char*);
		int getFirst(char *);
		void deleteList();
};

void LinkedList::traverse()
{
		Node *p;
		p = START;
		while(p != NULL)
		{
			cout<<endl<<p->data;
			p = p->next;
		}
}

void LinkedList::insertData(const char* const d)
{
	//Node to be inserted
	Node *temp;
	temp = new Node;

	//copies given data to node
	strcpy(temp->data,d);
	temp->next = NULL;

	if(START == NULL)
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

//removes a given word *word is not given by the user . It is generated while parsing the order.*
void LinkedList::removeData(char *d)
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

	while(strcmp(d,q->data) != 0 && q->next != NULL)
	{
		prev = q;
		q = q->next;
	}

	if(strcmp(d,q->data) == 0)
	{
		prev->next = q->next;
		delete q;
	}
}

int LinkedList::getFirst(char *toBeReturned)
{
	if(START == NULL)
		return 0;
	Node *p = NULL;
	p = START;
	strcpy(toBeReturned,START->data);
	START = START->next;
	delete p;
	return 1;
}

void LinkedList::deleteList()
{
	//destroys the linked list object
	while(START != NULL)
	{
	    Node *p = START;
		START = START->next;
		delete p;
	}
}

/* ************************************************************************************************************************************************************/

//A function that converts a long to string

void ltoa(long num,char *string)
{
	int digit,i = 0;
	long numCopy = num;
	int totalDigits = 0;
	bool negetive = false;

	if(num < 0)
	{
		negetive = true;
		num = -num;
		totalDigits++;
		numCopy = -numCopy;
	}

	while(numCopy > 0)
	{
		numCopy /= 10;
		totalDigits++;
	}

	int lastDigit = totalDigits;
	//string[totalDigits--] = '\0';

	while(num > 0)
	{
		digit = num%10;
		num /= 10;
		string[--totalDigits] = (char)('0' + (char)digit);
	}

	if(negetive == true)
	{
		string[0] = '-';
	}

	string[lastDigit] = '\0';

}
