
/* 
 * Note that the commands are stored in ascending order of 
 * orders .So, that the commands can be easily accessed 
 * using Binary or Interpolation search
 */

using namespace std;
#include<iostream>
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
	interface.seekg(0,ios::end);								//takes file pointer to the end .
	interface.write((char *) this,sizeof(*this));
}

void Command::showCommandFile()
{
	interface.seekg(0);			//takes file pointer to the beginning
	
	while(interface.read( (char *) this , sizeof(*this)))
		cout<<this->order<<"    "<<this->action<<endl;
}

int main()
{
	interface.open("Commands.txt" , ios::ate | ios::in | ios::out | ios::binary); 		 	/* opens Commands.txt in
																							 * concatenate mode | input mode | output mode | binary mode 
																							 * respectively
																							 */
	Command obj;
	char more = 'y';

	if(interface.fail())			//exits the execution if there is any error while opening the file
	{
		cout<<"Error in opening the file\n";
		exit(1);
	}
	
	do
	{
		obj.getData();
		obj.writeToFile();
		cout<<"Command Inserted"<<endl;
		cout<<"Enter more commands ..? (y/n) : "<<endl;
		fflush(stdin);
		more = getche();
	
	}while(more == 'y');

	obj.showCommandFile();
	interface.close();
	return 0;
}
