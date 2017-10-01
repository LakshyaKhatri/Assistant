#include <termios.h>
#include <stdio.h>

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
int stricmp(const char *a,const char *b)
{
	int i;
	while(a[i] != '\0' || b[i] != '\0' )
	{
		if(a[i]-b[i] == 0 || a[i] + 32 - b[i] == 0 || a[i] - 32 + b[i] == 0)
		{
			//do nothing
		}
		else 
			return(a[i]-b[i]);
	}
}
