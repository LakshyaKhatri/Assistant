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

//for reading math commands from file
fstream ioMath;

//for checking that the command found or not
short flag = NOTFOUND;

//for pushing and popping words of given orders
LinkedList sentence;

//for storing numbers given by users and giving their results
long  num1 = 0,num2 = 0,result = 0;

//for checking how many numbers are there on the input stream
int totalNumbersFound = 0;
class MathCommand
{
	private:
		char order[100];
		unsigned int actionCode;
	public:
		void setOrder(char*);
		void parseOrder();
		void searchOrder();
		void perform();
		MathCommand()
		{
			order[0] = '\0';
			actionCode = 0;
		}
};

void MathCommand::setOrder(char *o)
{
	strcpy(order,o);
}

void MathCommand::parseOrder()
{
	int i = 0, j = 0;
	char word[20],number[20];
	
	do
	{
		word[j++] = order[i++]; 
		if(order[i] == ' ' || order[i] == '\0')
		{
			word[j] = '\0';
			if((word[0] >= '0' || word[0] == '-') && word[j-1] <= '9' && totalNumbersFound == 0)
			{
				num1 = atol(word);
				totalNumbersFound++;
			}

			//totalNumbersFound == 1 signifies that one number is found 
			//now take the next number in the 
			//second veriable.
			else if((word[0] >= '0' || word[0] == '-') && word[j-1] <= '9' && totalNumbersFound == 1)
			{
				num2 = atol(word);
				totalNumbersFound++;
			}

			//if any word starts with the same letter from which the action has started then push it in the linked list. 
			if( word[0] == '+' || word[0] == 'A' || word[0] == 'a' || word[0] == 's' || word[0] == 'S' || word[0] == 't' || word[0] == 'T' || word[0] == 'i' || word[0] == 'I' || (word[0] == '-' && word[1] == '\0') || word[0] == 'r' || word[0] == 'R' || word[0] == 'm' || word[0] == 'M' || word[0] == 'd' || word[0] == 'D' ||   word[0] == 'x' || word[0] == '*')
			{
				sentence.insert(word);
			}
			
			i++;			//for skipping space
			j = 0;			//for a whole new word
		}

	}while(order[i] != '\0');

}

void MathCommand::searchOrder()
{
	char word[20];
	MathCommand temp;
	ioMath.open("MathCommandFile.txt", ios::ate | ios::out | ios::in );
	if(ioMath.fail())
	{
		cout<<"Error in opening the file";
		exit(0);
	}
	
	while(sentence.getFirst(word) == 1)
	{
		ioMath.clear();
		ioMath.seekg(ios::beg);
		while(ioMath.read((char *) &temp, sizeof(temp)))
		{
			if(stricmp(word,temp.order) == 0)
			{
				flag = FOUND;
				switch(temp.actionCode)
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
		ltoa(result,finalResult);
		strcat(finalTask,finalResult);
		strcat(finalTask," .\"");
		cout<<"\033[1;36mIt would be, "<<result<<".\033[0m"<<endl;
		system(finalTask);
	}
}

int main()
{
	MathCommand obj;
	obj.setOrder((char *)"multiply 99 with 2.47");
	obj.parseOrder();
	
	//if no number is detected in the input stream.
	if(totalNumbersFound == 0)
	{
		flag = NOTFOUND;
		return 0;
	}
	obj.searchOrder();
	obj.perform();
	return 0;
}
