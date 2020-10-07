// guessing_game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <math.h>
using namespace std;

void Introduction(string &name, char &closeResponse)
{
    cout << "Hello! Would you like to play a super fun guessing game?!? To start off: What's your name?" << endl;
    cin >> name;
    cout << "Nice to meet you " << name << " I can't wait to show off this fun game to you!" << endl;
    system("PAUSE");
    system("CLS");
    cout << "So I want to guess a number that you're thinking of right at ThIsss$%$ very moment. We'll make it simple, just a number between 1-100 does that sound like a deal?" << endl << "(Y/N)" << endl;
    cin >> closeResponse;
}

void Mistype(char &closeResponse)
{
    while (closeResponse != 'Y' && closeResponse != 'y' && closeResponse != 'N' && closeResponse != 'n')
    {
        cout << "I'm sorry, could you repeat that? I couldn't understand what you were trying to say.." << endl << "(Please type a response of Y or N)" << endl;
        cin >> closeResponse;
    } 
}

void Second_Response(char &closeResponse, string &name)
{
    if (closeResponse == 'N' || closeResponse == 'n')
    {
        cout << "Oh well, I guess we can play some other time..." << endl;
        exit(0);
    }
    else if (closeResponse == 'Y' || closeResponse == 'y')
    {
        cout << "Whew!" << " For a second I thought you were going to up and leave me " << name << ". Well with that out of the way LeT$s$ begin!" << endl;
        system("PAUSE");
        system("CLS");
    }
}

void First_Response(char& closeResponse, string& name)
{
    if (closeResponse == 'Y' || closeResponse == 'y')
    {
        cout << "That's great " << name << "! I wanted to make sure that you were willing before we S$tArT3d..." << endl;
        system("PAUSE");
        system("CLS");
    }
    else if (closeResponse == 'N' || closeResponse == 'n')
    {
        cout << "Really " << name << "?" << "Don't you want to play this super fun game?!?" << endl << "(Y/N)" << endl;
        cin >> closeResponse;
        Second_Response(closeResponse, name);
        if (closeResponse != 'Y' && closeResponse != 'y' && closeResponse != 'N' && closeResponse != 'n')
        {
            Mistype(closeResponse);
            Second_Response(closeResponse, name);
        }
    }
}

void MaxGuessLieDetection(int &number, int &maxGuess, bool &liar)
{
    if (maxGuess == number)
    {
        liar = true;
    }
}

void FirstGoAround(int &number, int &maxGuess, int &minGuess, string &openResponse, bool &myFirstGo)
{
    number = 50;
    maxGuess = 100;
    minGuess = 0;
    cout << "Okay so I'm guessing your first number is " << number << ". Is this correct or is your number higher or lower?" << endl << "(Please type exactly higher or lower or y if correct)" << endl;
    cin >> openResponse;
    system("CLS");
    myFirstGo = true;
}

void ThirdGoAround(int& number, int& maxGuess, int& minGuess, string& openResponse, bool& myFirstGo)
{
    maxGuess = 100;
    minGuess = 0;
    cout << "Okay so I'm guessing your first number is " << number << ". Is this correct or is your number higher or lower?" << endl << "(Please type exactly higher or lower or y if correct)" << endl;
    cin >> openResponse;
    system("CLS");
    myFirstGo = true;
}

int Mean(vector<int>& correctNumbers, int count)
{
    int sum = 0;
    for (auto it = correctNumbers.begin(); it != correctNumbers.end(); it++)
    {
        sum += *it;
    }
    return (sum / count);
}

//Found two ways that could work: number = ((MAX_GUESS - number) / 2) + number for higher response and number = abs((MIN_GUESS - number) / 2 for lower response
void Higher_Lower(string &openResponse, int &number, int &maxGuess, int &minGuess, bool &liar)
{
    if (openResponse == "higher" || openResponse == "Higher")
    {
        minGuess = number;
        number = ((maxGuess - number) / 2) + number;
        if (minGuess == 99)
        {
            number = 100;
        }
        else if (minGuess == number)
        {
            liar = true;
        }
    }
    else if (openResponse == "lower" || openResponse == "Lower")
    {
        maxGuess = number;
        if ((minGuess - number) / 2 > 0)
        {
            number = abs((minGuess - number) / 2);
            MaxGuessLieDetection(number, maxGuess, liar);
        }
        else
        {
            number = ((minGuess - number) / 2) + number;
            MaxGuessLieDetection(number, maxGuess, liar);
        }
    }
    else
    {
        return;
    }
}

void NumberGuess(int& number, string& openResponse)
{
    cout << "Okay.. Is it " << number << "?" << endl << "(Please type exactly higher or lower or y if correct)" << endl;
    cin >> openResponse;
    system("CLS");
}

void Usleep(__int64 usec) //Be sure to change this up or nix this!!!
{
    HANDLE timer;
    LARGE_INTEGER ft;

    ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}

void AI_Talk(const string& text)
{
    for (int i = 0; i < text.size(); ++i)
    {
        cout << text[i] << flush;

        Usleep(60000);
    }
}

void ResolveIt(string &openResponse, int &number, int &maxGuess, int &minGuess, bool &liar)
{
    Higher_Lower(openResponse, number, maxGuess, minGuess, liar);
    if (liar) { AI_Talk("Liar"); return; }
    NumberGuess(number, openResponse);
}

void PlayAgain(vector<int> &correctNumbers, int &number, char &closeResponse, bool &myFirstGo, int &count)
{
    cout << "Nice! I got it!" << endl;
    correctNumbers.push_back(number);
    cout << "Would you like to play again?" << endl << "(Please type a response of Y or N)" << endl;
    cin >> closeResponse;
    Mistype(closeResponse);
    if (closeResponse == 'y' || closeResponse == 'Y')
    {
        myFirstGo = false;
        count++;
    }
    system("CLS");
}

void Intro(vector<int> &correctNumbers, int &count, bool &myFirstGo, int &number, int &maxGuess, int &minGuess, string &openResponse)
{
    if (count < 3 && !myFirstGo)
    {
        FirstGoAround(number, maxGuess, minGuess, openResponse, myFirstGo);
    }
    else if (!myFirstGo)
    {
        number = Mean(correctNumbers, count);
        ThirdGoAround(number, maxGuess, minGuess, openResponse, myFirstGo);
    }
    else
    {
        return;
    }
}

void Guessing_Game()
{
    string name = "";
    char closeResponse = ' ';
    string openResponse = "";
    Introduction(name, closeResponse);
    First_Response(closeResponse, name);
    if(closeResponse != 'Y' && closeResponse != 'y' && closeResponse != 'N' && closeResponse != 'n')
    {
        Mistype(closeResponse);
        First_Response(closeResponse, name);
    }
    enum openResponseResolve { Resolve, Y, Null } resolve;
    int count = 0;
    int number = 100;
    int maxGuess = 100;
    int minGuess = 0;
    vector<int> correctNumbers;
    bool myFirstGo = false;
    bool liar = false;
    do 
    {
        Intro(correctNumbers, count, myFirstGo, number, maxGuess, minGuess, openResponse);
        if (openResponse == "Higher" || openResponse == "higher" || openResponse == "Lower" || openResponse == "lower")
        {
            resolve = Resolve;
        }
        else if (openResponse == "Y" || openResponse == "y")
        {
            resolve = Y;
        }
        else
        {
            resolve = Null;
        }
        switch (resolve)
        {
            case Resolve:
                ResolveIt(openResponse, number, maxGuess, minGuess, liar);
                break;
            case Y:
                PlayAgain(correctNumbers, number, closeResponse, myFirstGo, count);
                break;
            default:
                system("CLS");
                cout << "I'm sorry, could you repeat that? I couldn't understand what you were trying to say.." << endl << "(Please type exactly higher/Higher or lower/Lower or y/Y if correct)" << endl;
                cin >> openResponse;
        }
    } while ((closeResponse == 'y' || closeResponse == 'Y') && (count != 10 && liar == false));
}



int main()
{
    Guessing_Game();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
