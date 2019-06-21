#include<cstdlib>

//for reading math commands from file
fstream ioMath;

//action codes for performing any specific o peration

#define ADD 1212
#define SUBTRACT 1213
#define DIVIDE 1214
#define MULTIPLY 1215


//for pushing and popping words of given orders
LinkedList sentence;

//for storing numbers given by users and giving their results
double  num1 = 0,num2 = 0,result = 0;

//for checking how many numbers are there on the input stream
short totalNumbersFound = 0;
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
	char *ptr; //for strtod()

	do
	{
		word[j++] = order[i++];
		if(order[i] == ' ' || order[i] == '\0')
		{
			word[j] = '\0';
			if((word[0] >= '0' || word[0] == '-') && word[j-1] <= '9' && totalNumbersFound == 0)
			{
				num1 = strtod(word,&ptr);
				totalNumbersFound++;
			}

			//totalNumbersFound == 1 signifies that one number is found
			//now take the next number in the
			//second veriable.
			else if((word[0] >= '0' || word[0] == '-') && word[j-1] <= '9' && totalNumbersFound == 1)
			{
				num2 = strtod(word,&ptr);
				totalNumbersFound++;
			}

			//if any word starts with the same letter from which the action has started then push it in the linked list.
			if( word[0] == '+' || word[0] == 'A' || word[0] == 'a' || word[0] == 's' || word[0] == 'S' || word[0] == 't' || word[0] == 'T' || word[0] == 'i' || word[0] == 'I' || (word[0] == '-' && word[1] == '\0') || word[0] == 'r' || word[0] == 'R' || word[0] == 'm' || word[0] == 'M' || word[0] == 'd' || word[0] == 'D' ||   word[0] == 'x' || word[0] == '*')
			{
				sentence.insertData(word);
			}

			i++;			//for skipping space
			j = 0;			//for a whole new word
		}

	}while(order[i] != '\0');

}

void MathCommand::searchOrder()
{
    //if no number is detected in the input stream.
	if(totalNumbersFound < 2)
	{
		isCommandFound = NOTFOUND;
		return;
	}
	char word[20];
	word[0] = '\0';
	MathCommand temp;

	while(sentence.getFirst(word) == 1)
	{
		ioMath.clear();
		ioMath.seekg(ios::beg);
		while(ioMath.read((char *) &temp, sizeof(temp)))
		{
			if(xstricmp(word,temp.order) == 0)
			{
				isCommandFound = FOUND;
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

			if(isCommandFound == FOUND)
				break;
		}

		if(isCommandFound == FOUND)
			break;
	}
	while(sentence.getFirst(word));         //deletes all the contents of the list
}

void MathCommand::perform()
{
	char finalTask[100];
	finalTask[0] = '\0';
	char *finalResult,buffer[20];
	strcpy(finalTask,"say.vbs");
	strcat(finalTask," \"It would be, ");
	finalResult = gcvt(result,10,buffer);       //a functions that converts souble to char*
	strcat(finalTask,finalResult);
	strcat(finalTask," .\"");
	cout<<"\033[1;36mIt would be, "<<result<<".\033[0m"<<endl;
	system(finalTask);
	for(int i = 0; i < 99; i++)
        order[i] = '\0';
	totalNumbersFound = 0;
	actionCode = 0;
}

/*int main()
{
	obj.setOrder((char *)"multiply 99 with 2.39");
	obj.parseOrder();

	obj.searchOrder();
	obj.perform();
	return 0;
}
*/
