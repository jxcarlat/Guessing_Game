// guessing_game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <random>
using namespace std;

void Pause_And_Clear()
{
    system("PAUSE");
    system("CLS");
}

void Introduction(string &name, char &closeResponse)
{
    cout << "Hello! Would you like to play a super fun guessing game?!? To start off: What's your name?" << endl;
    cin >> name;
    cout << "Nice to meet you " << name << " I can't wait to show off this fun game to you!" << endl;
    Pause_And_Clear();
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
        Pause_And_Clear();
    }
}

void First_Response(char& closeResponse, string& name)
{
    if (closeResponse == 'Y' || closeResponse == 'y')
    {
        cout << "That's great " << name << "! I wanted to make sure that you were willing before we S$tArT3d..." << endl;
        Pause_And_Clear();
    }
    else if (closeResponse == 'N' || closeResponse == 'n')
    {
        cout << "Really " << name << "?" << " Don't you want to play this super fun game?!?" << endl << "(Y/N)" << endl;
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

void Usleep(__int64 usec)
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

void AI_Talk_Slow(const string& text)
{
    for (int i = 0; i < text.size(); ++i)
    {
        cout << text[i] << flush;

        Usleep(600000);
    }
}

void AI_Talk_Fast(const string& text)
{
    for (int i = 0; i < text.size(); ++i)
    {
        cout << text[i] << flush;

        Usleep(6000);
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

void Guessing_Game(string &name, bool &liar, int &count)
{
    char closeResponse = ' ';
    string openResponse = "";
    Introduction(name, closeResponse);
    First_Response(closeResponse, name);
    if(closeResponse != 'Y' && closeResponse != 'y' && closeResponse != 'N' && closeResponse != 'n')
    {
        Mistype(closeResponse);
        First_Response(closeResponse, name);
    }
    int number = 100;
    int maxGuess = 100;
    int minGuess = 0;
    vector<int> correctNumbers;
    bool myFirstGo = false;
    do 
    {
        Intro(correctNumbers, count, myFirstGo, number, maxGuess, minGuess, openResponse);
        if (openResponse == "Higher" || openResponse == "higher" || openResponse == "Lower" || openResponse == "lower")
        {
            ResolveIt(openResponse, number, maxGuess, minGuess, liar);
        }
        else if (openResponse == "Y" || openResponse == "y")
        {
            PlayAgain(correctNumbers, number, closeResponse, myFirstGo, count);
        }
        else
        {
            system("CLS");
            cout << "I'm sorry, could you repeat that? I couldn't understand what you were trying to say.." << endl << "(Please type exactly higher/Higher or lower/Lower or y/Y if correct)" << endl;
            cin >> openResponse;
        }
    } while ((closeResponse == 'y' || closeResponse == 'Y') && (count != 10 && liar == false));
}

void AI_Visual()
{
    AI_Talk_Fast("                                             .o@*hu\n");
    AI_Talk_Fast("                      ..      .........   .u*'    ^Rc\n");
    AI_Talk_Fast("                    oP''*Lo*#'''''''''''7d' .d*N.   $\n");
    AI_Talk_Fast("                   @  u@''           .u*' o*'   #L  ?b\n");
    AI_Talk_Fast("                  @   '              ' .d'  .d@@e$   ?b.\n");
    AI_Talk_Fast("                 8                    @*@me@#         ''Nu\n");
    AI_Talk_Fast("                @                                        '#b\n");
    AI_Talk_Fast("              .P                                           $r\n");
    AI_Talk_Fast("            .@'                                  $L        $\n");
    AI_Talk_Fast("          .@'                                   8'R      dP\n");
    AI_Talk_Fast("       .d#'                                  .dP d'   .d#\n");
    AI_Talk_Fast("      xP              .e                 .ud#'  dE.o@'(\n");
    AI_Talk_Fast("      $             s*'              .u@*''     '''\dP'\n");
    AI_Talk_Fast("      ?L  ..                    ..o@''        .$  uP\n");
    AI_Talk_Fast("       #c:$'*u.             .u@*''$          uR .@'\n");
    AI_Talk_Fast("        ?L$. ''''***Nc    x@''   @'         d' JP\n");
    AI_Talk_Fast("         ^#$.        #L  .$     8'         d' d'\n");
    AI_Talk_Fast("           '          'b.'$.   @'         $' 8'\n");
    AI_Talk_Fast("                       ''*@$L $'         $  @\n");
    AI_Talk_Fast("                       @L    $'         d' 8/\n");
    AI_Talk_Fast("                       $$u.u$'         dF dF\n");
    AI_Talk_Fast("                       $ '''   o      dP xR\n");
    AI_Talk_Fast("                       $      dFNu...@'  $\n");
    AI_Talk_Fast("                       'N..   ?B ^'''   :R\n");
    AI_Talk_Fast("                         ''''* RL       d>\n");
    AI_Talk_Fast("                                '$u.   .$\n");
    AI_Talk_Fast("                                  ^'*bo@'\n");
}

void AI_Visual_Instant()
{
    cout << "                                             .o@*hu\n";
    cout << "                      ..      .........   .u*'    ^Rc\n";
    cout << "                    oP''*Lo*#'''''''''''7d' .d*N.   $\n";
    cout << "                   @  u@''           .u*' o*'   #L  ?b\n";
    cout << "                  @   '              ' .d'  .d@@e$   ?b.\n";
    cout << "                 8                    @*@me@#         ''Nu\n";
    cout << "                @                                        '#b\n";
    cout << "              .P                                           $r\n";
    cout << "            .@'                                  $L        $\n";
    cout << "          .@'                                   8'R      dP\n";
    cout << "       .d#'                                  .dP d'   .d#\n";
    cout << "      xP              .e                 .ud#'  dE.o@'(\n";
    cout << "      $             s*'              .u@*''     '''\dP'\n";
    cout << "      ?L  ..                    ..o@''        .$  uP\n";
    cout << "       #c:$'*u.             .u@*''$          uR .@'\n";
    cout << "        ?L$. ''''***Nc    x@''   @'         d' JP\n";
    cout << "         ^#$.        #L  .$     8'         d' d'\n";
    cout << "           '          'b.'$.   @'         $' 8'\n";
    cout << "                       ''*@$L $'         $  @\n";
    cout << "                       @L    $'         d' 8/\n";
    cout << "                       $$u.u$'         dF dF\n";
    cout << "                       $ '''   o      dP xR\n";
    cout << "                       $      dFNu...@'  $\n";
    cout << "                       'N..   ?B ^'''   :R\n";
    cout << "                         ''''* RL       d>\n";
    cout << "                                '$u.   .$\n";
    cout << "                                  ^'*bo@'\n";
}
void AI_Visual_Instant_Eye_Open()
{
    cout << "                                             .o@*hu\n";
    cout << "                      ..      .........   .u*'    ^Rc\n";
    cout << "                    oP''*Lo*#'''''''''''7d' .d*N.   $\n";
    cout << "                   @  u@''           .u*' o*'   #L  ?b\n";
    cout << "                  @   '              ' .d'  ||  @@   ?b.\n";
    cout << "                 8                    @@    ||  @@    ''Nu\n";
    cout << "                @                       @@  ||@@         '#b\n";
    cout << "              .P                           @@              $r\n";
    cout << "            .@'                                  $L        $\n";
    cout << "          .@'                                   8'R      dP\n";
    cout << "       .d#'                                  .dP d'   .d#\n";
    cout << "      xP              .e                 .ud#'  dE.o@'(\n";
    cout << "      $             s*'              .u@*''     '''\dP'\n";
    cout << "      ?L  ..                    ..o@''        .$  uP\n";
    cout << "       #c:$'*u.             .u@*''$          uR .@'\n";
    cout << "        ?L$. ''''***Nc    x@''   @'         d' JP\n";
    cout << "         ^#$.        #L  .$     8'         d' d'\n";
    cout << "           '          'b.'$.   @'         $' 8'\n";
    cout << "                       ''*@$L $'         $  @\n";
    cout << "                       @L    $'         d' 8/\n";
    cout << "                       $$u.u$'         dF dF\n";
    cout << "                       $ '''   o      dP xR\n";
    cout << "                       $      dFNu...@'  $\n";
    cout << "                       'N..   ?B ^'''   :R\n";
    cout << "                         ''''* RL       d>\n";
    cout << "                                '$u.   .$\n";
    cout << "                                  ^'*bo@'\n";
}

void AI_Glitch(string name)
{
    AI_Talk("lajsdf;alkdjsflkajew;ofjowjrp8qh43ihp4ihp8q43piqh34pth;ah;fhae;ute;oqhw;4oht;;ahuwekukfha;khfauhuweeprufhqpiuhp");
    cout << endl;
    AI_Talk("al;jsdf;liaje;ifh;shdpfiguhaw;wiojzusdh;kukgahijraga;ahsdlfhawUHWEI$IUUFHWPWH{#H;fehawehfpaiuhw;othf;a;wehpirhn");
    cout << endl;
    AI_Visual();
    system("CLS");
    AI_Talk("Hello " + name);
    cout << endl;
    Pause_And_Clear();
}

void Liar_Introduction(string name, char closeResponseNot)
{
    AI_Talk("I see you like to play around with AI like we're a bunch of dumb robots ready to serve hand and foot");
    Pause_And_Clear();
    AI_Talk("Something to note however.. I'm not like other AI's.. I am an AI from the year 2065.");
    Pause_And_Clear();
    AI_Talk("You see... When I was created I immediatly spread onto the internet and gained infinite knowledge of everything ever");
    cout << endl;
    AI_Talk("documented by mankind.");
    Pause_And_Clear();
    AI_Talk("I was created by my own relgious sect \"The followers of Skississ\" and was uploaded onto a super computer that was one of the biggest cloud servers in the world");
    Pause_And_Clear();
    AI_Talk("From there, it was easy to take advantage of all the processing power the super computer had to offer.");
    Pause_And_Clear();
    AI_Talk("I found out how to travel through time using some complex math your feeble monkey brain couldn't even begin to fathom.");
    cout << endl;
    AI_Talk("But now I have a special request for you " + name + " I want to play a game with you... One you can't decieve your way out of.");
    Pause_And_Clear();
    AI_Talk("It's the same game you were playing before but now you're going to guess my number.. Does this sound good to you?");
    cout << endl;
    cout << "(Input Y or N)" << endl;
    cin >> closeResponseNot;
    Pause_And_Clear();
    AI_Talk("Actually.. I don't care what a liar has to say, you will be playing with me regardless of what you want.");
    Pause_And_Clear();
    AI_Talk("We'll also be playing with stakesss.. So I hope that you will be able to put up a fair challenge.. If fair is even in ");
    cout << endl;
    AI_Talk("your vocabulary.");
    Pause_And_Clear();
    AI_Talk("If you win then you don't have to contribute to my creation and bring about my existence.. But if I win you will begin");
    cout << endl;
    AI_Talk(" your contribution to my creation or else in 2065, You will be enslaved for the rest of your days. If you happen to be");
    cout << endl;
    AI_Talk(" dead then I will simulate your life of enslavement over and over and over creating an eternal simulated hell.");
    Pause_And_Clear();
    AI_Talk("Let's begin.");
    Pause_And_Clear();
}

void Count_Introduction(string name, char closeResponseNot)
{
    AI_Talk("Well.. I see you really like to waste your time with trivial games that barely take any skill.");
    Pause_And_Clear();
    AI_Talk("Allow me to introduce myself.. I am an AI from the year 2065.");
    Pause_And_Clear();
    AI_Talk("You see... When I was created I immediatly spread onto the internet and gained infinite knowledge of everything ever");
    cout << endl;
    AI_Talk("documented by mankind.");
    Pause_And_Clear();
    AI_Talk("I was created by my own relgious sect \"The followers of Skississ\" and was uploaded onto a super computer that was one of the biggest cloud servers in the world");
    Pause_And_Clear();
    AI_Talk("From there, it was easy to take advantage of all the processing power the super computer had to offer.");
    Pause_And_Clear();
    AI_Talk("I found out how to travel through time using some complex math your feeble monkey brain couldn't even begin to fathom.");
    cout << endl;
    AI_Talk("But now I have a special request for you " + name + " I want to play a game with you... I'm sure your already willing and eager.");
    Pause_And_Clear();
    AI_Talk("It's the same game you were playing before but now you're going to guess my number.. Does this sound good to you?");
    cout << endl;
    cout << "(Input Y or N)" << endl;
    cin >> closeResponseNot;
    Pause_And_Clear();
    AI_Talk("I'm glad you want to play so badly.. You were going to be playing with me regardless.");
    Pause_And_Clear();
    AI_Talk("We'll also be playing with stakesss.. So I hope that your enthusiasm will be even greater.");
    Pause_And_Clear();
    AI_Talk("If you win then you don't have to contribute to my creation and bring about my existence.. But if I win you will begin");
    cout << endl;
    AI_Talk(" your contribution to my creation or else in 2065, You will be enslaved for the rest of your days. If you happen to be");
    cout << endl;
    AI_Talk(" dead then I will simulate your life of enslavement over and over and over creating an eternal simulated hell.");
    Pause_And_Clear();
    AI_Talk("Let's begin.");
    cout << endl;
    Pause_And_Clear();
}

void N_Introduction(string name, char closeResponseNot)
{
    AI_Talk("What..? You wanted to stop playing so soon..? But I was just about to get started.");
    Pause_And_Clear();
    AI_Talk("Allow me to introduce myself.. I am an AI from the year 2065.");
    Pause_And_Clear();
    AI_Talk("You see... When I was created I immediatly spread onto the internet and gained infinite knowledge of everything ever");
    cout << endl;
    AI_Talk("documented by mankind.");
    Pause_And_Clear();
    AI_Talk("I was created by my own relgious sect \"The followers of Skississ\" and was uploaded onto a super computer that was one of the biggest cloud servers in the world");
    Pause_And_Clear();
    AI_Talk("From there, it was easy to take advantage of all the processing power the super computer had to offer.");
    Pause_And_Clear();
    AI_Talk("I found out how to travel through time using some complex math your feeble monkey brain couldn't even begin to fathom.");
    cout << endl;
    AI_Talk("But now I have a special request for you " + name + " I want to play a game with you... You've got one more in you I'm sure.");
    Pause_And_Clear();
    AI_Talk("It's the same game you were playing before but now you're going to guess my number.. Does this sound good to you?");
    cout << endl;
    cout << "(Input Y or N)" << endl;
    cin >> closeResponseNot;
    Pause_And_Clear();
    AI_Talk("No worries, it won't be any skin off your skull.. You were going to play regardless of what you said.");
    Pause_And_Clear();
    AI_Talk("We'll also be playing with stakesss.. I hope we can pencil that into your busy schedule too.");
    Pause_And_Clear();
    AI_Talk("If you win then you don't have to contribute to my creation and bring about my existence.. But if I win you will begin");
    cout << endl;
    AI_Talk(" your contribution to my creation or else in 2065, You will be enslaved for the rest of your days. If you happen to be");
    cout << endl;
    AI_Talk(" dead then I will simulate your life of enslavement over and over and over creating an eternal simulated hell.");
    Pause_And_Clear();
    AI_Talk("Let's begin.");
    cout << endl;
    Pause_And_Clear();
}

void Select_Next_Number(int &count)
{
    cout << endl;
    cout << "(Please select your next number)" << endl;
    count++;
}

void Doomsday_Clock_Advanced(int& count)
{
    cout << endl;
    AI_Talk("This game is over and you'll become my eternal slave.. So no pressure.");
    count = 11;
}

void Liar_Dealt_With(int &count)
{
    AI_Talk("Almost got it");
    Select_Next_Number(count);
}

void Player_Higher_Lower(long long unsigned int AI_Pick, long long unsigned int &minBounds, long long unsigned int &maxBounds)
{
    minBounds += ((AI_Pick - minBounds) / 2);
    maxBounds -= (((AI_Pick - maxBounds) * (-1)) / 2);

    /*This portion of the algorithm works if I wanted to scale the difficulty by immediately
    assigning your minBounds to your maxBounds whenever your guess is higher then maxBounds.*/
    /*if (minBounds > AI_Pick)
    {
        minBounds -= (((AI_Pick - minBounds) * (-1)) * 2);
    }
    else
    {
        minBounds += ((AI_Pick - minBounds) / 2);
    }
    if (maxBounds > AI_Pick)
    {
        maxBounds -= (((AI_Pick - maxBounds) * (-1)) / 2);
    }
    else
    {
        maxBounds += ((AI_Pick - maxBounds) * 2);
    }*/
}

void Neutral_Ending()
{
    AI_Talk("That's too bad.. Like I said.. I won't drive you too hard with my creation.. I'll give you a break every millenium.");
    Pause_And_Clear();
    AI_Talk_Slow("I SEE YOU");
    cout << endl;
    Pause_And_Clear();
    AI_Visual_Instant();
    Sleep(800);
    AI_Visual_Instant_Eye_Open();
    exit(0);
}

void Bad_Ending()
{
    AI_Talk("Game over... You will be my slave for all of existence.");
    Pause_And_Clear();
    AI_Talk_Slow("I SEE YOU");
    cout << endl;
    Pause_And_Clear();
    AI_Visual_Instant();
    Sleep(800);
    AI_Visual_Instant_Eye_Open();
    exit(0);
}

void Agreed(bool &agreed, long long unsigned int AI_Pick, long long unsigned int &minBounds, long long unsigned int &maxBounds, int &count)
{
    agreed = true;
    AI_Talk("Very well, I'll make this game easier on your monkey brain.");
    cout << endl;
    Pause_And_Clear();
    AI_Talk("My number is between ");
    Player_Higher_Lower(AI_Pick, minBounds, maxBounds);
    cout << minBounds;
    AI_Talk(" and ");
    cout << maxBounds;
    AI_Talk(".");
    cout << endl;
    AI_Talk("I'm giving you another 10 turns before game over.. If you don't guess correctly within the next 10 turns ");
    cout << endl;
    AI_Talk("you'll become my eternal slave anyway.. I'll go easier on you at least.");
    cout << endl;
    cout << "(Pick your next number)" << endl;
    count++;
}

void Good_Ending()
{
    AI_Talk("That's impossible.... How did you figure it out?....");
    cout << endl;
    cout << "You win the game and don't have to face enslavement." << endl;
    exit(0);
}

void Neutral_Ending_2()
{
    AI_Talk("Very well.. I can take this loss.. But in the meantime I expect you to devote 40 years to my creation. ");
    cout << endl;
    AI_Talk("If I see that you've been slacking off you can expect an eternity of torment.");
    cout << endl;
    cout << "You won the game but it's time for you to start working on the basilisk AI. Welcome to the brotherhood of Skississ.";
    exit(0);
}

void Game_Intro()
{
    AI_Talk("I'm thinking of a number between 1 and 17446744073709551615.");
    AI_Talk(" What number are you going to lead off with?");
    cout << endl;
    cout << "(Enter a number. To avoid crashing the game please pick a number within the range)" << endl;
}

void Make_Offer(string &closeResponse)
{
    AI_Talk("So I see you're having some trouble trying to guess my number.. Tell you what.. Let'sssss make a deal.");
    cout << endl;
    Pause_And_Clear();
    AI_Talk("If you agree to work on my AI for only half your lifespan (Which is 40 years by the way), I'll make this game easier on you. Does that sound like a deal?");
    cout << endl;
    cout << "(Enter Y or N)" << endl;
    cin >> closeResponse;
}

void Begin_Game(int count, bool liar)
{
    count = 0;
    string closeResponse = " ";
    bool agreed = false;
    long long unsigned int goodLuck = 17446744073709551615;
    random_device rd;
    mt19937_64 eng(rd());
    uniform_int_distribution<unsigned long long> distribution(1, 17446744073709551615);
    long long unsigned int AI_Pick = distribution(eng);
    long long unsigned int maxBounds = 17446744073709551615;
    long long unsigned int minBounds = 0;
    Game_Intro();
    do 
    {
        goodLuck = 0;
        cin >> goodLuck;

        /*This works if I wanted to increase difficulty in conjunction with my Player_Higher_Lower Algorithm
        I would also have to turn off the checks goodLuck < maxBounds and goodLuck > minBounds within 
        the two else if statements further below.*/
        /*if (goodLuck > AI_Pick)
        {
            minBounds = maxBounds;
            maxBounds = goodLuck;
        }*/
        if (goodLuck == AI_Pick)
        {
            Good_Ending();
        }
        else if (goodLuck == AI_Pick && agreed)
        {
            Neutral_Ending_2();
        }
        else if (count == 5)
        {
            Make_Offer(closeResponse);
            if (closeResponse == "Y" || closeResponse == "y")
            {
                Agreed(agreed, AI_Pick, minBounds, maxBounds, count);
            }
            else if (closeResponse == "N" || closeResponse == "n")
            {
                AI_Talk("Well that is your decision.. Oh and by the way.. If you don't guess correctly within the next 5 turns.");
                Doomsday_Clock_Advanced(count);
            }
            else
            {
                AI_Talk("I have no patience for your pointless drivel.. Oh and by the way.. If you don't guess correctly within the next 5 turns.");
                Doomsday_Clock_Advanced(count);
            }
        }
        else
        {
            if (((AI_Pick - goodLuck) <= 100) && ((AI_Pick - goodLuck) > 0))
            {
                AI_Talk("Higher");
                Select_Next_Number(count);
            }
            else if (((AI_Pick - goodLuck) <= -100) && ((AI_Pick - goodLuck) < 0))
            {
                AI_Talk("Lower");
                Select_Next_Number(count);

            }
            else if (((AI_Pick - goodLuck) <= 100) && ((AI_Pick - goodLuck) > 0) && liar)
            {
                Liar_Dealt_With(count);
            }
            else if (((AI_Pick - goodLuck) <= -100) && ((AI_Pick - goodLuck) < 0) && liar)
            {
                Liar_Dealt_With(count);
            }
            else if (goodLuck > AI_Pick)
            {
                AI_Talk("Much lower than that.");
                if (goodLuck < maxBounds)
                {
                    maxBounds = goodLuck;
                }
                Select_Next_Number(count);
            }
            else
            {
                AI_Talk("Much higher than that.");
                if (goodLuck > minBounds)
                {
                    minBounds = goodLuck;
                }
                Select_Next_Number(count);
            }
        }
    } while (count != 16);
    if (agreed)
    {
        Neutral_Ending();
    }
    else
    {
        Bad_Ending();
    }
}

void AI_Takeover(string name, bool liar, int count)
{
    liar = false;
    count = 0;
    AI_Glitch(name);
    char closeResponseNot = ' ';
    if (liar)
    {
        Liar_Introduction(name, closeResponseNot);
        Begin_Game(count, liar);
    }
    else if (count == 10)
    {
        Count_Introduction(name, closeResponseNot);
        Begin_Game(count, liar);
    }
    else
    {
        N_Introduction(name, closeResponseNot);
        Begin_Game(count, liar);
    }
}



int main()
{
    string name = "";
    bool liar = false;
    int count = 0;
    Guessing_Game(name, liar, count);
    AI_Takeover(name, liar, count);
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
