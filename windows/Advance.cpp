//#include<cstdlib>
#include<ctime>

//for reading math commands from file
fstream ioAdvance;

//action codes for performing any specific o peration
#define MUSIC 1
#define STOPMUSIC 2
#define TIME 3
#define DATE 4

void playMusic();
void stopMusic();
void tellTime();
void tellDate();

//for pushing and popping words of given orders
LinkedList sentence2;

class AdvanceCommand
{
	private:
		char order[100];
		unsigned int actionCode;
	public:
		void setOrder(char*);
		void parseOrder();
		void searchOrder();
		void perform();
		AdvanceCommand()
		{
			order[0] = '\0';
			actionCode = 0;
		}
};

void AdvanceCommand::setOrder(char *o)
{
	strcpy(order,o);
}

void AdvanceCommand::parseOrder()
{
	int i = 0, j = 0;
	char word[20];

	do
	{
		word[j++] = order[i++];
		if(order[i] == ' ' || order[i] == '\0')
		{
			word[j] = '\0';
				sentence2.insertData(word);
			i++;			//for skipping space
			j = 0;			//for a whole new word
		}

	}while(order[i] != '\0');

}

void AdvanceCommand::searchOrder()
{
    char word[20];
	word[0] = '\0';
	AdvanceCommand temp;

	while(sentence2.getFirst(word) == 1)
	{
	    //cout<<word<<endl;
		ioAdvance.clear();
		ioAdvance.seekg(ios::beg);
		while(ioAdvance.read((char *) &temp, sizeof(temp)))
		{
		    //cout<<temp.order<<endl;
			if(xstricmp(word,temp.order) == 0)
			{
				isCommandFound = FOUND;
				this->actionCode = temp.actionCode;
				//cout<<"Hello World";
			}

			if(isCommandFound == FOUND)
				break;
		}

		if(isCommandFound == FOUND)
			break;
	}
	while(sentence2.getFirst(word));         //deletes all the contents of the list
}

void AdvanceCommand::perform()
{
	switch(this->actionCode)
	{
	case MUSIC:
	    playMusic();
		break;
	case STOPMUSIC:
		stopMusic();
		break;
	case TIME:
		tellTime();
		break;
	case DATE:
		tellDate();
		break;
    }
	for(int i = 0; i < 99; i++)
        order[i] = '\0';
	actionCode = 0;
}

void playMusic()
{
    char finalO[50],music[20];
        cout<<"\033[1;36mWhich song do you want to listen ??\033[0m"<<endl;
        system("say.vbs \"Which song do you want to listen ??\"");
        cin.getline(music,20);
        strcat(music,".mp3\"");
        strcpy(finalO,"\"");
        strcat(finalO,music);
        cout<<"\033[1;36mPlaying "<<music<<"\033[0m"<<endl;
        system(finalO);
        isCommandFound = FOUND;
}

void stopMusic()
{
        system("taskkill /IM Music.UI.exe /f");
        cout<<"\033[1;36mDone.\033[0m"<<endl;
        system("say.vbs \"Done.\"");
        isCommandFound = FOUND;
}

void tellDate()
{
    char buffer[10];
    time_t t;           //structure for storing time
    char spokenDate[50],date[35];
    strcpy(date,"Current date is ");
    time(&t);        //stores time in  t

    tm *current = localtime(&t);        //change the data type of time
    strcat(date,itoa(current->tm_mday,buffer,10));        //converts the day into string and concatanates it in date array

    switch(1 + current->tm_mon)
    {
    case 1:
        break;
        strcat(date," Jan ");
    case 2:
        strcat(date," Feb ");
        break;
    case 3:
        strcat(date," Mar ");
        break;
    case 4:
        strcat(date," Apr ");
        break;
    case 5:
        strcat(date," May ");
        break;
    case 6:
        strcat(date," June ");
        break;
    case 7:
        strcat(date," July ");
        break;
    case 8:
        strcat(date," Aug ");
        break;
    case 9:
        strcat(date," Sept ");
        break;
    case 10:
        strcat(date," Oct ");
        break;
    case 11:
        strcat(date," Nov ");
        break;
    case 12:
        strcat(date," Dec ");
        break;
    }

    strcat(date,itoa(1900 + current->tm_year,buffer,10));

    cout<<"\033[1;36m"<<date<<" ."<<"\033[0m"<<endl;
    strcpy(spokenDate,"say.vbs \"");
    strcat(spokenDate,date);
    strcat(spokenDate," .\"");
    system(spokenDate);
    isCommandFound = FOUND;
}

void tellTime()
{
    char buffer[10];
    char spokenTime[50],finaltime[35];
    strcpy(finaltime,"Current time is ");
    strcpy(spokenTime,"say.vbs \"");
    time_t t;
    time(&t);
    cout<<"Hello World";
    tm *current;
    strcat(finaltime,itoa(1 + current->tm_hour,buffer,10));
    strcat(finaltime,":");
    strcat(finaltime,itoa(1 + current->tm_min,buffer,10));
    strcat(finaltime,":");
    strcat(finaltime,itoa(1 + current->tm_sec,buffer,10));

    strcat(spokenTime,finaltime);
    strcat(spokenTime," .\"" );
    cout<<"\033[1;36m"<<finaltime<<"\033[0m"<<endl;
    system(spokenTime);
    isCommandFound = FOUND;
}
