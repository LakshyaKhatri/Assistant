
/* 
 * Note that the commands are stored in ascending order of 
 * orders .So, that the commands can be easily accessed 
 * using Binary or Interpolation search
 */

#include<stdlib.h>
#include<fstream>
#include"someImportantFunctions.h"

fstream interface;

class Command
{
	private:
		char order[100];
		char action[100];
	public:
		Command()
		{
			order[0] = '\0';
			action[0] = '\0';
		}
		void getData();
		void writeToFile();
		void showCommandFile();
		void overwriteCommand();
};

void Command::getData()
{
	cout<<"Enter the order : ";
	cin.getline(order,99);				//take a complete sentence from the keyboard until "ENTER" key is pressed ( defined in iostream ).
	cout<<"Enter the action : ";
	cin.getline(action,99);	
}

void Command::writeToFile()
{
	long unsigned lastByte = 0;
	interface.seekp(0,ios::end);								//takes file pointer to the end .
	lastByte = interface.tellg();
	interface.write((char *) this,sizeof(*this));
}

void Command::showCommandFile()
{
	interface.seekg(0);			//takes file pointer to the beginning
	int i = 1;
	
	while(interface.read( (char *) this , sizeof(*this)))
		cout<<i++<<". "<<this->order<<"    "<<this->action<<endl;

	fflush(stdin);
	getch();
}

void Command::overwriteCommand()
{
	long unsigned overwriteCommandNo = 0,updateLocation = 0;
	cout<<"\nOverwrite which command\n";
	cin>>overwriteCommandNo;
	cin.ignore();
	updateLocation = (overwriteCommandNo - 1) * sizeof(*this);
	if(interface.eof())
		interface.clear();
	interface.seekp(updateLocation);																//takes file pointer cursor to specified location
	cout<<"Enter new order : ";
	cin.getline(order,99);
	cout<<"Enter new action : ";																					//ignores '\n'
	cin.getline(action,99); 

	interface.write((char *)this , sizeof(*this));

	cout<<"Done . \n";

	fflush(stdin);
	getch();
}

int createCommandMainMethod()
{
	interface.open("Commands.txt" , ios::ate | ios::out | ios::in );			 			/* opens Commands.txt in
																							 * concatenate mode| input mode| output mode| input mode| binary mode
																							 * respectively.
																							 */
	Command obj;
	int choice;
	char more = 'y';
	int close = 0;
	if(interface.fail())			//exits the execution if there is any error while opening the file
	{
		cout<<"Error in opening the file\n";
		exit(1);
	}

	while(1)
	{
		cout<<"Enter your choice :-\n1.Show Commands\n2.Write new command\n3.Overwrite previous command\n4.Exit";
		cin>>choice;
		cin.ignore();
		system("clear");
		switch(choice)
		{
			case 2:
				interface.clear();
				obj.getData();
				obj.writeToFile();
				cout<<"Command Inserted"<<endl;
				getch();
				break;
	
			case 1:
				obj.showCommandFile();
				break;
	
			case 3:
				obj.overwriteCommand();
				break;
	
			case 4:
				interface.close();
				//exit(0);
				close = 1;
				break;

			default :
				cout<<"\nInvalid option\n";
				break;
		}

		if(close)
			break;
	}
}
