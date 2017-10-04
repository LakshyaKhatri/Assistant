#include<stdlib.h>
#include"someImportantFunctions.h"

fstream iMath;

class MathCommand
{
	private:
		char order[100];
		unsigned int actionCode;
	public:
		void getOrder();
		void parseOrder();
		void perform();
};

void MathCommand::getOrder()
{
	fflush(0);
	fflush(stdin);
	cin.getline(order,99);
}

void MathCommand::parseOrder()
{

}
