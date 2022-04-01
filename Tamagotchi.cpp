// Tamagotchi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <tuple>
#include <string>
using namespace std;
using std::ifstream;

int Hunger = 100;
int Boredom = 100;
string Name;
int choice;

bool start = false;
enum MoodEnum {happy, unhappy, angry, mad} M;


int menu()
{
    cout << "\nPlease select an action!\n" << "0 - Quit game\n" << "1 - Talk to " << Name << endl << "2 - Feed " << Name << endl << "3 - Play with " << Name << endl << "4 - Mini Game (Higher or Lower)\n" << "5 - Display " << Name << "'s" << " stats\n" << "6 - Save Game\n" << "7 - Clear Save (this will exit the game)\n" << "Option: ";
    cin >> choice;
    return choice;
}

void save()
{
	fstream SaveFile;
	SaveFile.open("SaveFile", ios::out);
	SaveFile << Hunger << endl << Boredom << endl << M << endl << Name << endl;
	SaveFile.close();
}

void MiniGame()
{

    int GameIndex = 5;
    cout << "\n ----------------- Higher or Lower -----------------" << endl;
    cout << " Try and guess the mystery number between 0 and 100! " << endl;
    int MiniGameNum;
    MiniGameNum = rand() % 100 + 1;
    while (GameIndex > 0)
    {
        int guess = 0;
        cout << "Input your guess: ";
        cin >> guess;
        if (guess > MiniGameNum)
        {
            cout << guess << " is more than the mystery number!" << endl;
        }
        if (guess < MiniGameNum)
        {
            cout << guess << " is less than the mystery number!" << endl;
        }
        if (guess == MiniGameNum)
        {
            cout << guess << " is  the mystery number! Well done!" << endl;
			cout << "Score: " << GameIndex * 10 << endl << "This will be added to " << Name << "'s " << " fun level!" << endl;
			Boredom += GameIndex * 10;
			if (Boredom <= 0)
			{
				Boredom = 0;
			}
			if (Boredom >= 100)
			{
				Boredom = 100;
			}
            break;
        }
        GameIndex--;
    }

    bool end = false;
    while (end == false)
    {
        char answer;
        cout << "play again? (y/n): ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            MiniGame();
			break;
        }
        if (answer == 'n' || answer == 'N')
        {
			end = true;
            break;
        }
        else
        {
            cout << "Try again!" << endl;
        }
    }
	cout << "---------------------------------------------------" << endl;
}

class Tamagotchi
{
private:
    int PrivHunger;
    int PrivBoredom;
public:

    Tamagotchi(int h, int b) //CONSTRUCTOR - always public, no return value
    {
        PrivHunger = h;
        PrivBoredom = b;
    }
    ~Tamagotchi() //DESTRUCTOR - always has a ~
    {
		if (choice != 7)
		{
			save();
		}	
    }
    void feed()
    {
		Time();
        PrivHunger += 15;
		cout << "Hunger + 10!" << endl;
        if (PrivHunger <= 0)
        {
            PrivHunger = 0;
        }  
        if (PrivHunger >= 95)
        {
            PrivHunger = 100;
        }
		cout << "Hunger: " << PrivHunger << endl;
		Hunger = PrivHunger;
		M = Mood(Hunger, Boredom);
    }

    void play()
    {
		Time();
		cout << "Fun + 10!" << endl;
		PrivBoredom = Boredom;
		PrivBoredom += 15;

        if (PrivBoredom <= 0)
        {
            PrivBoredom = 0;
        }
        if (PrivBoredom >= 100)
        {
            PrivBoredom = 100;
        }
		cout << "Fun: " << PrivBoredom << endl;
		Boredom = PrivBoredom;
		M = Mood(Hunger, Boredom);
    }

    virtual void communicate()
    {
        int ranNum;
        int i;
        ranNum = rand() % 3;

        switch (M)
        {
        case happy:
            switch (ranNum)
            {
            case 0:
                cout << "\nLet's play!\n" << endl;
                break;
            case 1:
                cout << "\nHehe!\n" << endl;
                break;
            case 2:
                cout << "\nNice talking to you!\n" << endl;
                break;
            }
            break;
        case unhappy:
            switch (ranNum)
            {
            case 0:
                cout << "\n:(\n" << endl;
                break;
            case 1:
                cout << "\nHmph!\n" << endl;
                break;
            case 2:
                cout << "\n*ignores you*\n" << endl;
                break;
            }
            break;
        case angry:
            switch (ranNum)
            {
            case 0:
                cout << "\nGrrrrr\n" << endl;
                break;
            case 1:
                cout << "\n*silently judges you*\n" << endl;
                break;
            case 2:
                cout << "\nI don't want to talk to you! >:(\n" << endl;
                break;
            }
            break;
        case mad:
            switch (ranNum)
            {
            case 0:
                cout << "\nRAHHHHH!\n" << endl;
                break;
            case 1:
                cout << "\nD:<\n" << endl;
                break;
            case 2:
                cout << "\n*stares at you with disgust*\n" << endl;
                break;
            }
            break;
        }
        Time();
		M = Mood(Hunger, Boredom);
    }

protected:
    MoodEnum Mood(int Hunger, int Boredom)
    {
        if ((Hunger < 100) & (Boredom < 100))
        {
            M = happy;
        }
        if ((Hunger < 75) & (Boredom < 75))
        {
            M = unhappy;
        }
        if ((Hunger < 50) & (Boredom < 50))
        {
            M = angry;
        }
        if ((Hunger < 25) & (Boredom < 25))
        {
            M = mad;
        }
        return M;
    }

    void Time()
    {
        PrivHunger -= 5;
        if (PrivHunger <= 0)
        {
            PrivHunger = 0;
        }
        Hunger = PrivHunger;

        PrivBoredom -= 5;
        if (PrivBoredom <= 0)
        {
            PrivBoredom = 0;
        }
        Boredom = PrivBoredom; 
    }

}; //Class definitions always have ; at end

void clear()
{
    ofstream SaveFile;
    SaveFile.open("SaveFile");
    SaveFile << "";
	SaveFile.close();
}

int main()
{
    char First;
    string temp1;
    ifstream SaveFile;
    SaveFile.open("SaveFile");
    First = SaveFile.peek();
    if (int(First) > 0)
    {
        int index = 0;
        while (getline(SaveFile, temp1))
        {
            switch (index)
            {
            case 0:
                Hunger = stoi(temp1);
                break;
            case 1:
                Boredom = stoi(temp1);
                break;
            case 2:
                switch (stoi(temp1))
                {
                case 0:
                    M = happy;
                    break;
                case 1:
                    M = unhappy;
                    break;
                case 2:
                    M = angry;
                    break;
                case 3:
                    M = mad;
                    break;
                }
                break;
            case 3:
                Name = temp1;
                break;
            default:
                break;
            }
            index++;
        }
        cout << Name << " has missed you!" << endl;
        SaveFile.close();
    }
    else
    {
        cout << "Please Enter your pet's name: ";
        cin >> Name;
        start = true;
    }

    Tamagotchi NewTam(Hunger, Boredom);
    bool play = true;
    while (play == true)
    {
        string CurrentMood;
        int selection;
        selection = menu();

        switch (selection) {
        case 0:
            return(0);
        case 1:
            NewTam.communicate();
            break;
        case 2:
            NewTam.feed();
            break;
        case 3:
            NewTam.play();
            break;
        case 4:
			MiniGame();
			break;
        case 5 :
			switch (M)
			{
			case 0:
				CurrentMood = "happy";
				break;
			case 1:
				CurrentMood = "unhappy";
				break;
			case 2:
				CurrentMood = "angry";
				break;
			case 3:
				CurrentMood = "mad";
				break;
			}
			cout << "\n" << Name << "'s stats:\n" << "Hunger: " << Hunger << "\nFun: " << Boredom << "\nMood: " << CurrentMood << endl;
			break;
        case 6:
			save();
			cout << "\nProgress saved!" << endl;
			break;
		case 7:
			clear();
			play = false;
			break;
        default: //always use default as failsafe
            cout << "Try again!" << endl;
        }
    }
}

