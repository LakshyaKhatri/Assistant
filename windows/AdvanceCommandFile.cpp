#include"someImportantFunctions.h"

fstream ioAdvance;

class AdvanceCommand
{
	private:
		char order[100];
		unsigned int actionCode;
	public:
		AdvanceCommand()
		{
			order[0] = '\0';
			actionCode = 0;
		}
		void getData();
		void writeToFile();
		void showCommandFile();
		void overwriteCommand();
};

void AdvanceCommand::getData()
{
	cout<<"Enter the order : ";
	cin.getline(order,99);				//take a complete sentence from the keyboard until "ENTER" key is pressed ( defined in iostream ).
	cout<<"Enter the Action Code : ";
	cin>>actionCode;
}

void AdvanceCommand::writeToFile()
{
	//long unsigned lastByte = 0;
	ioAdvance.seekp(0,ios::end);								//takes file pointer to the end .
	//lastByte = ioAdvance.tellg();
	ioAdvance.write((char *) this,sizeof(*this));
}

void AdvanceCommand::showCommandFile()
{
	ioAdvance.seekg(0);			//takes file pointer to the beginning
	int i = 1;

	while(ioAdvance.read( (char *) this , sizeof(*this)))
		cout<<i++<<". "<<this->order<<"    "<<this->actionCode<<endl;

	fflush(stdin);
	getch();
}

void AdvanceCommand::overwriteCommand()
{
	long unsigned overwriteCommandNo = 0,updateLocation = 0;
	cout<<"\nOverwrite which command\n";
	cin>>overwriteCommandNo;
	cin.ignore();
	updateLocation = (overwriteCommandNo - 1) * sizeof(*this);
	if(ioAdvance.eof())
		ioAdvance.clear();
	ioAdvance.seekp(updateLocation);																//takes file pointer cursor to specified location
	cout<<"Enter new order : ";
	cin.getline(order,99);
	cout<<"Enter new Action Code : ";

	cin>>actionCode;

	ioAdvance.write((char *)this , sizeof(*this));

	cout<<"Done . \n";

	fflush(stdin);
	getch();
}

int main()
{
	ioAdvance.open("AdvanceCommandFile.txt" , ios::ate | ios::out | ios::in );			 			/* opens AdvanceCommandFile.txt in
																							 * concatenate mode| input mode| output mode| input mode| binary mode
																							 * respectively.
																							 */
	AdvanceCommand obj;
	int choice;
	char more = 'y';
	int close = 0;
	if(ioAdvance.fail())			//exits the execution if there is any error while opening the file
	{
		cout<<"Error in opening the file\n";
		exit(1);
	}

	while(1)
	{
		cout<<"Enter your choice :-\n1.Show Commands\n2.Write new command\n3.Overwrite previous command\n4.Exit";
		cin>>choice;
		cin.ignore();
		system("cls");
		switch(choice)
		{
			case 2:
				ioAdvance.clear();
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
				ioAdvance.close();
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
