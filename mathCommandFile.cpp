#include<stdlib.h>
#include<fstream>
#include"someImportantFunctions.h"

fstream ioMath;

class MathCommand
{
	private:
		char order[100];
		unsigned int actionCode;
	public:
		MathCommand()
		{
			order[0] = '\0';
			actionCode = 0;
		}
		void getData();
		void writeToFile();
		void showCommandFile();
		void overwriteCommand();
};

void MathCommand::getData()
{
	cout<<"Enter the order : ";
	cin.getline(order,99);				//take a complete sentence from the keyboard until "ENTER" key is pressed ( defined in iostream ).
	cout<<"Enter the Action Code : "<<endl<<"ADD 1212"<<endl<<"SUBTRACT 1213"<<endl<<"DIVIDE 1214"<<endl<<"SUBTRACT 1215"<<endl;
	cin>>actionCode;
}

void MathCommand::writeToFile()
{
	//long unsigned lastByte = 0;
	ioMath.seekp(0,ios::end);								//takes file pointer to the end .
	//lastByte = ioMath.tellg();
	ioMath.write((char *) this,sizeof(*this));
}

void MathCommand::showCommandFile()
{
	ioMath.seekg(0);			//takes file pointer to the beginning
	int i = 1;
	
	while(ioMath.read( (char *) this , sizeof(*this)))
		cout<<i++<<". "<<this->order<<"    "<<this->actionCode<<endl;

	fflush(stdin);
	getch();
}

void MathCommand::overwriteCommand()
{
	long unsigned overwriteCommandNo = 0,updateLocation = 0;
	cout<<"\nOverwrite which command\n";
	cin>>overwriteCommandNo;
	cin.ignore();
	updateLocation = (overwriteCommandNo - 1) * sizeof(*this);
	if(ioMath.eof())
		ioMath.clear();
	ioMath.seekp(updateLocation);																//takes file pointer cursor to specified location
	cout<<"Enter new order : ";
	cin.getline(order,99);
	cout<<"Enter new Action Code : "<<endl<<"ADD 1212"<<endl<<"SUBTRACT 1213"<<endl<<"DIVIDE 1214"<<endl<<"SUBTRACT 1215"<<endl;

	cin>>actionCode; 

	ioMath.write((char *)this , sizeof(*this));

	cout<<"Done . \n";

	fflush(stdin);
	getch();
}

int main()
{
	ioMath.open("MathCommandFile.txt" , ios::ate | ios::out | ios::in );			 			/* opens MathCommandFile.txt in
																							 * concatenate mode| input mode| output mode| input mode| binary mode
																							 * respectively.
																							 */
	MathCommand obj;
	int choice;
	char more = 'y';
	int close = 0;
	if(ioMath.fail())			//exits the execution if there is any error while opening the file
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
				ioMath.clear();
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
				ioMath.close();
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

	return 0;
}
