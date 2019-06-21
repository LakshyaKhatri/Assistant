#include "someImportantFunctions.h"
#include "general.cpp"
#include "math.cpp"
#include "Advance.cpp"


void orderNotFound()
{
    int ch = '\0';
	cout<<"\033[1;36mI cannot understand what you say !\033[0m"<<endl;
	system("say.vbs \"I Cannot understand what you say !\"");
	Sleep(0.6);
	cout<<"\033[1;36mI will learn these things soon.\033[0m"<<endl;
	system("say.vbs \"I will learn these things soon.\"");
	cout<<"\033[1;36mWant to teach me..??(y/n)\033[0m"<<endl;
	fflush(stdin);
	ch = getch();
	cout << char(ch);
  if(ch == 'y')
		createCommandMainMethod();
    else{
        cout<<"\033[1;36mOkay!\033[0m"<<endl;
    	system("say.vbs \"Okay!\"");
    }
}

int main()
{
    GeneralCommand general;     //for operating general commands
    iCommand.open("Commands.txt", ios::ate | ios::out | ios::in );
	if(iCommand.fail())
	{
		cout<<"Error in opening Commands.txt\n";
		exit(0);
	}

    ioMath.open("MathCommandFile.txt", ios::ate | ios::out | ios::in );
    if(ioMath.fail())
	{
		cout<<"Error in opening the file";
		exit(0);
	}

    ioAdvance.open("AdvanceCommandFile.txt", ios::ate | ios::out | ios::in );
    if(ioAdvance.fail())
	{
		cout<<"Error in opening the file";
		exit(0);
	}

    /* Please insert loading */
    system("cls");
    cout<<"\n\033[1;36mHello! How can Jarvis help you ?\033[0m\n";
    system("say.vbs \"Hello ! How can Jarvis help you ?\"");

    while(1)
    {
        if(iCommand.eof())
            iCommand.clear();
        if(ioMath.eof())
            ioMath.clear();
        general.getOrder();
        general.searchOrder();
        if(isCommandFound == FOUND)
            general.perform();
        else
        {
            MathCommand math;           //for operating math command
            math.setOrder( general.passOrder() );
            math.parseOrder();
            math.searchOrder();
            if(isCommandFound == FOUND)
                math.perform();
            else
            {
                AdvanceCommand advance;           //for operating math command
                advance.setOrder( general.passOrder() );
                advance.parseOrder();
                advance.searchOrder();
                if(isCommandFound == FOUND)
                    advance.perform();
            }
        }
        if(isCommandFound == NOTFOUND)
            orderNotFound();

        isCommandFound = NOTFOUND;
    }
    return 0;
}
