using namespace std;

#include <termios.h>
#include <stdio.h>
#include<iostream>

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

//this structure has been created for manupulating
//the stack 
typedef struct NODE
{
	int number;
	unsigned int *next;
}NODE;

//definition of stack
void stack()
{
	
}
