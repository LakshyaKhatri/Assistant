using namespace std;
#include<iostream>
#include<stdlib.h>
#include<termios.h>
#include<fstream>
#include<string.h>
#include<unistd.h>
#include"someImportantFunctions.h"

ifstream iCommand;								//object of class fstream , will perform the input operations from file to program
char finalAction[150];

class Jarvis
{
	private:
		char order[100];
		char action[150];
	public:
		Jarvis()
		{
			order[0] = '\0';
			action[100] = '\0'; 
		}
		void getOrder();
		void searchOrder();
		void perform();
};

void Jarvis::getOrder()
{
	fflush(stdin);
	fflush(0);
	cin.getline(order,99);

	if(stricmp(order,(char *)"exit") == 0 || stricmp(order,(char *)"bye") == 0)
	{
		cout<<"See you Later !\n";
		system("espeak -g3 -s150 -v english_wmids \"See you later !\"");
		sleep(1.5);
		exit(0);
	}
}

void Jarvis::searchOrder()
{
	Jarvis temp;
	iCommand.seekg(0,ios::beg);								//takes file pointer to the beginning
	
	//Until EOF is reached do this :-
	while(iCommand.read((char *) &temp, sizeof(temp)))
	{
		if(stricmp(temp.order,this->order) == 0)
		{
			//makes the action to be performed
			strcpy(finalAction,"espeak -g3 -s150 -v english_wmids \"");
			strcat(finalAction,this->action);
			strcat(finalAction,"\"");

			return;
		}

	}

	//If order not found
	system("espeak -g3 -s150 -v english_wmids \"I Cannot understand what you say !\"");
	sleep(1.2);
	system("espeak -g3 -s150 -v english_wmids \"I will learn this thing soon.\"");
}

void Jarvis::perform()
{
	cout<<action<<endl;
	system(finalAction);
	finalAction[0] = '\0';
}

int main()
{
	Jarvis jarvis1;
	iCommand.open("Commands.txt",ios::in | ios::binary);
	if(iCommand.fail())
	{
		cout<<"Error in opening Commands.txt\n";
		exit(0);
	}
	
	cout<<"Hello! How can I help you ?\n";
	system("espeak -g3 -s150 -v english_wmids \"Hello ! How can I help you ?\"");
	while(1)
	{
		jarvis1.getOrder();
		jarvis1.searchOrder();
		jarvis1.perform();
	}
	
	return 0;

}
