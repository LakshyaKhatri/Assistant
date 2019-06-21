//#include"someImportantFunctions.h"

#include"createCommandFile.cpp"

char finalAction[150];

//object of class fstream , will perform the input operations from file to program for general commands
fstream iCommand;

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
		char* passOrder();
};

void GeneralCommand::getOrder()
{
	fflush(stdin);
	fflush(0);
	cin.getline(order,99);

	if(xstricmp(order,(char *)"exit") == 0 || xstricmp(order,(char *)"bye") == 0 || xstricmp(order,(char *)"bbye") == 0)
	{
		cout<<"\033[1;36mSee you Later !\033[0m\n";											//prints text in cyan bright bold color
		system("say.vbs \"See you later !\"");
		iCommand.close();
		system("exit");
		Sleep(1.5);
		exit(0);
	}
}

void GeneralCommand::searchOrder()
{
	GeneralCommand temp;
	iCommand.seekg(ios::beg);								//takes file pointer to the beginning
	char ch = '\0';
	//Until EOF is reached search order in Commands.txt :-
	while(iCommand.read((char *) &temp, sizeof(temp)))
	{
		if(xstricmp(temp.order,this->order) == 0)
		{
			//makes the action to be performed
			finalAction[0] = '\0';
			strcpy(finalAction,"say.vbs \"");
			strcat(finalAction,temp.action);
			strcat(finalAction,"\"");
			strcpy(this->action,temp.action);
			isCommandFound = FOUND;
			return;
		}
	}
}

void GeneralCommand::perform()
{
	cout<<"\033[1;36m"<<action<<"\033[0m"<<"\n";
	system(finalAction);
	finalAction[0] = '\0';
	for(int i=0;i<100;i++)
        order[i] = '\0';
}

char* GeneralCommand::passOrder()
{
    return order;
}

/*int main()
{
	iCommand.open("Commands.txt", ios::ate | ios::out | ios::in );
	if(iCommand.fail())
	{
		cout<<"Error in opening GeneralCommands.txt\n";
		exit(0);
	}
	system("cscript say.vbs \"Hello ! How can Jarvis help you ?\"");
	cout<<"\n\033[1;36mHello! How can Jarvis help you ?\033[0m\n";

	while(1)
	{
		iCommand.clear();
		general.getOrder();
		general.searchOrder();
		general.perform();
	}

	return 0;
}
*/
