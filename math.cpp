#include"someImportantFunctions.h"
#include<string.h>
#include<stdlib.h>
#include<cstdlib>
#include<fstream>

#define FOUND 1
#define NOTFOUND 0
//action codes for performing any specific operation

#define ADD 1212
#define SUBTRACT 1213
#define DIVIDE 1214
#define MULTIPLY 1215

fstream ioMath;
short flag = NOTFOUND;
LinkedList sentence;
long  num1 = 0,num2 = 0,result = 0;

class MathCommand
{
	private:
		char order[100];
		unsigned int actionCode;
	public:
		void parseOrder();
		void searchOrder();
		void perform();
		MathCommand(char*);
};

MathCommand::MathCommand(char *o)
{
	strcpy(order,o);
}

void MathCommand::parseOrder()
{
	int i = 0, j = 0, k = 1;
	char word[20],number[20];
	do
	{
		word[j++] = order[i]; 
		if(order[i] == ' ' || order[i] == '\0')
		{
			word[j] = '\0';
			if((word[0] >= '0' || word[0] == '-') && word[j-1] <= '9' && k == 1)
			{
				num1 = atol(word);
				k++;
			}

			else if((word[0] >= '0' || word[0] == '-') && word[j-1] <= '9' && k == 2)
			{
				num2 = atol(word);
				k++;
			}

			if( word[0] == '+' || word[0] == 'A' || word[0] == 'a' || word[0] == 's' || word[0] == 'S' || word[0] == 't' || word[0] == 'T' || word[0] == 'A' ||   word[0] == 'i' || word[0] == 'I' || word[0] == '-' || word[0] == 'r' || word[0] == 'R' || word[0] == 'm' || word[0] == 'M' || word[0] == 'd' || word[0] == 'D' ||   word[0] == 'x' || word[0] == '*' || word[0] == 'B' || word[0] == 'b' )
			{
				sentence.insert(word);
			}

			j = 0;
		}

	}while(order[i++] != '\0');

}

void MathCommand::searchOrder()
{
	char *word;
	MathCommand *temp;
	ioMath.open("MathCommandFile.txt", ios::ate | ios::out | ios::in );
	ioMath.seekg(ios::beg);
	while(ioMath.read((char *) &temp, sizeof(temp)))
	{
		if(stricmp(word,order) == 0)
		{
			flag = FOUND;
			switch(actionCode)
			{
				case ADD:
					result = num1 + num2;
					break;
				case SUBTRACT:
					result = num1 - num2;
					break;
				case DIVIDE:
					result = num1 / num2;
					break;
				case MULTIPLY:
					result = num1 * num2;
					break;
			}
		}

		if(flag == FOUND)
			break;
	}
}

void MathCommand::perform()
{
	char finalTask[100];
	finalTask[0] = '\0';
	char finalResult[20];

	if(flag == FOUND)
	{
		strcpy(finalTask,"espeak -g3 -s150 -a200 -v english_wmids");
		strcat(finalTask," \"It would be, ");
		ltoa(result,finalResult,10);
		strcat(finalTask,finalResult);
		strcat(finalTask," .\"");
		cout<<"\033[1;36mIt would be, "<<result<<".\033[0m"<<endl;
		system(finalTask);
	}
}

void main()
{
	MathCommand obj("Add 876 and 728");
	obj.parseOrder();
	obj.searchOrder();
	obj.perform();
}
