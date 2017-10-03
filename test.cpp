using namespace std;
#include<iostream>
#include<stdlib.h>
#include<termios.h>
#include<fstream>
#include<string.h>
#include<unistd.h>
#include"someImportantFunctions.h"

fstream iCommand;								//object of class fstream , will perform the input operations from file to program
char finalAction[150];
int flag = 0;
class Jarvis
{
	private:
		char order[100];
		char action[100];
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
		system("espeak -g3 -s150 -a200 -v english_wmids \"See you later !\"");
		sleep(1.5);
		exit(0);
	}
}

void Jarvis::searchOrder()
{
	Jarvis temp;
	iCommand.seekg(ios::beg);								//takes file pointer to the beginning

	//Until EOF is reached do this :-
	while(iCommand.read((char *) &temp, sizeof(temp)))
	{
		if(stricmp(temp.order,this->order) == 0)
		{
			//makes the action to be performed
			strcpy(finalAction,"espeak -a200 -g3 -s150 -v english_wmids \"");
			strcat(finalAction,temp.action);
			strcat(finalAction,"\"");
			strcpy(this->action,temp.action);
			flag = 0;
			return;
		}
	}

	//If order not found
	cout<<"I cannot understand what you say !"<<endl;
	system("espeak -g3 -s150 -a200 -v english_wmids \"I Cannot understand what you say !\"");
	sleep(0.6);
	cout<<"I will learn these things soon."<<endl;
	system("espeak -g3 -s150 -a200 -v english_wmids \"I will learn these things soon.\"");
	flag = 1;
}

void Jarvis::perform()
{
	if(flag == 0)
		cout<<action<<"\n";

	system(finalAction);
	finalAction[0] = '\0';
}


int main()
{
	Jarvis jarvis1;
	iCommand.open("Commands.txt", ios::ate | ios::out | ios::in | ios::binary );
	if(iCommand.fail())
	{
		cout<<"Error in opening Commands.dat\n";
		exit(0);
	}
	
	cout<<"Hello! How can Jarvis help you ?\n";
	system("espeak -g3 -s150 -a200 -v english_wmids \"Hello ! How can Jarvis help you ?\"");

	while(1)
	{
		iCommand.clear();
		jarvis1.getOrder();
		jarvis1.searchOrder();
		jarvis1.perform();
	}
	
	return 0;

}
