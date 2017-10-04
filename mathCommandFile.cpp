#include"someImportantFunctions.h"
#include<string.h>

class MathCommand
{
	private:
		char order[100];
		unsigned int actionCode;
	public:
		void parseOrder();
		void searchOrder();
		void perform();
};

void MathCommand::
