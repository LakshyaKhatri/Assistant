#include"someImportantFunctions.h"
#include<string.h>

fstream ioMath;

class MathCommand
{
	private:
		char order[100];
		unsigned int actionCode;
	public:
		void parseOrder();
		void searchOrder();
		void perform();
		MathCommand()
		{
			
		}
};

void MathCommand::parseOrder()
{

}
