//#include"someImportantFunctions.h"

#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<unistd.h>
#include"createCommandFile.cpp"
#define FOUND 1
#define NOTFOUND 0

fstream iCommand;								//object of class fstream , will perform the input operations from file to program
char finalAction[150];

int flag = NOTFOUND;

class GeneralCommand
{
	private:
		char order[100];
		char action[100];
	public:
		GeneralCommand()
		{
			order[0] = '\0';
			action[0] = '\0'; 
		}
		void getOrder();
		void searchOrder();
		void perform();
};

void GeneralCommand::getOrder()
{
	fflush(stdin);
	fflush(0);
	cin.getline(order,99);
	
	if(stricmp(order,(char *)"exit") == 0 || stricmp(order,(char *)"bye") == 0)
	{
		cout<<"\033[1;36mSee you Later !\033[0m\n";											//prints text in cyan bright bold color
		system("espeak -g3 -s150 -a200 -v english_wmids \"See you later !\"");
		iCommand.close();
		sleep(1.5);
		exit(0);
	}
}

void GeneralCommand::searchOrder()
{
	GeneralCommand temp;
	//char mathTemp[100];
	iCommand.seekg(ios::beg);								//takes file pointer to the beginning
	char ch = '\0';
	//Until EOF is reached search order in Commands.txt :-
	while(iCommand.read((char *) &temp, sizeof(temp)))
	{
		if(stricmp(temp.order,this->order) == 0)
		{
			//makes the action to be performed
			finalAction[0] = '\0';
			strcpy(finalAction,"espeak -a200 -g3 -s150 -v english_wmids \"");
			strcat(finalAction,temp.action);
			strcat(finalAction,"\"");
			strcpy(this->action,temp.action);
			flag = FOUND;
			return;
		}
	}

	//If order not found search MathCommandFile.txt
	//strcpy(mathTemp,order);
	//flag = isMathCommand(mathTemp);
	//if(flad == FOUND)
	//	return;

	//If order is found nowhere do this
	cout<<"\033[1;36mI cannot understand what you say !\033[0m"<<endl;
	system("espeak -g3 -s150 -a200 -v english_wmids \"I Cannot understand what you say !\"");
	sleep(0.6);
	cout<<"\033[1;36mI will learn these things soon.\033[0m"<<endl;
	system("espeak -g3 -s150 -a200 -v english_wmids \"I will learn these things soon.\"");
	cout<<"\033[1;36mWant to teach me..??\033[0m"<<endl;
	fflush(stdin);
	ch = getche();
	if(ch == 'y')
		createCommandMainMethod();
	flag = NOTFOUND;
}

void GeneralCommand::perform()
{
	if(flag == FOUND)
	{
		cout<<"\033[1;36m"<<action<<"\033[0m"<<"\n";
		system(finalAction);
		finalAction[0] = '\0';
	}
}

int main()
{
	GeneralCommand general;
	//MathCommand math;

	iCommand.open("Commands.txt", ios::ate | ios::out | ios::in );
	if(iCommand.fail())
	{
		cout<<"Error in opening Commands.dat\n";
		exit(0);
	}
	
	cout<<"\n\033[1;36mHello! How can Jarvis help you ?\033[0m\n";
	system("espeak -g3 -s150 -a200 -v english_wmids \"Hello ! How can Jarvis help you ?\"");

	while(1)
	{
		iCommand.clear();
		general.getOrder();
		general.searchOrder();
		general.perform();
	}

	return 0;
}
