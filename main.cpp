#include <iostream>
#include <iomanip>

using namespace std;

enum enGameChoice
{
    stone = 1,
    paper = 2,
    scissors = 3
};

enum enRoundState
{
    win = 1,
    draw = 0,
    defeat = -1
};

void GameStartScreen()
{

    cout << "====================================================" << endl
         << "    Welcome to ( Stone - Paper - Scissors ) Game    " << endl
         << "====================================================" << endl
         << "Rules: (arrow show deafeat)" << endl
         << "Paper ---> Stone ---> Scissors" << endl
         << "| <------------------------|" << endl
         << "====================================================" << endl;
}

void PositiveCheck(int &num)
{

    while (num < 0)
    {
        cout << "Please enter a positive number: ";
        cin >> num;
    }
}

int RandomNumber(int From, int To)
{

    return rand() % (To - From + 1) + From;
}

void ChoiceValidation(int &Choice)
{

    while (Choice != 1 && Choice != 2 && Choice != 3)
    {

        cout << "Wrong Choice!! Choose Again" << endl
             << "(1)Stone (2)Paper (3)Scissors" << endl
             << "Your Choice: ";
        cin >> Choice;
    }
}

int GetRounds()
{
    int rounds;

    cout << "How many rounds do yo want to play: ";
    cin >> rounds;
    PositiveCheck(rounds);

    return rounds;
}

enGameChoice GetPersonChoice()
{

    int choice;

    cout << "Your Choice: (1)Stone (2)Paper (3)Scissors ? ";
    cin >> choice;
    ChoiceValidation(choice);

    if (choice == 1)
    {

        return enGameChoice ::stone;
    }
    else if (choice == 2)
    {

        return enGameChoice ::paper;
    }
    else if (choice == 3)
    {

        return enGameChoice ::scissors;
    }
}

enGameChoice GetCompterChoice()
{

    int choice;

    choice = RandomNumber(1, 3);

    if (choice == 1)
    {

        return enGameChoice ::stone;
    }
    else if (choice == 2)
    {

        return enGameChoice ::paper;
    }
    else if (choice == 3)
    {

        return enGameChoice ::scissors;
    }
}

string ChoicePrint(enGameChoice Choice)
{

    switch (Choice)
    {
    case enGameChoice::paper:

        return "Paper";
        break;

    case enGameChoice::scissors:

        return "Scissor";
        break;

    case enGameChoice::stone:

        return "Stone";
        break;
    }
}

void RoundScreen(int Round, enGameChoice Person, enGameChoice Computer, enRoundState RoundState)
{
    string TextColor = "";
    string winnerText = "";

    switch (RoundState)
    {
    case enRoundState::win:
        TextColor = "\033[42m"; // Green
        winnerText = "Person";
        break;
    case enRoundState::draw:
        TextColor = "\033[43m"; // Yellow
        winnerText = "No one";
        break;
    case enRoundState::defeat:
        TextColor = "\033[41m"; // Red
        winnerText = "Computer";
        break;
    }

    cout << endl;

    cout << TextColor << "=====================================================\033[0m" << endl;
    cout << TextColor << left << "  Round " << setw(45) << left << Round << "\033[0m" << endl;
    cout << TextColor << left << "  Your choice: " << setw(38) << left << ChoicePrint(Person) << "\033[0m" << endl;
    cout << TextColor << left << "  Computer choice: " << setw(34) << left << ChoicePrint(Computer) << "\033[0m" << endl;
    cout << TextColor << left << "  Winner: " << setw(43) << left << winnerText << "\033[0m" << endl;
    cout << TextColor << "=====================================================\033[0m" << endl;
}

enRoundState StateCheck(enGameChoice Person, enGameChoice Computer)
{

    if (Person == enGameChoice::paper)
    {
        switch (Computer)
        {
        case enGameChoice::paper:

            return enRoundState ::draw;
            break;

        case enGameChoice::stone:

            return enRoundState ::win;
            break;

        case enGameChoice::scissors:

            return enRoundState::defeat;
            break;
        }
    }

    else if (Person == enGameChoice::stone)
    {
        switch (Computer)
        {
        case enGameChoice::paper:

            return enRoundState ::defeat;
            break;

        case enGameChoice::stone:

            return enRoundState ::draw;
            break;

        case enGameChoice::scissors:

            return enRoundState::win;
            break;
        }
    }

    else if (Person == enGameChoice::scissors)
    {

        switch (Computer)
        {
        case enGameChoice::paper:

            return enRoundState ::win;
            break;

        case enGameChoice::stone:

            return enRoundState ::defeat;
            break;

        case enGameChoice::scissors:

            return enRoundState::draw;
            break;
        }
    }
}

void PointsCalc(int &PersonPoints, int &ComputerPoints, enRoundState RoundState)
{

    switch (RoundState)
    {
    case enRoundState::win:

        PersonPoints++;

        break;

    case enRoundState::defeat:

        ComputerPoints++;

        break;
    }
}

void GameOverScreen(int Rounds, int PersonPoints, int ComputerPoints)
{

    string TextColor = "";
    string ColorEnd = "\033[0m";
    string winnerText = "";

    if (PersonPoints > ComputerPoints)
    {

        TextColor = "\033[42m"; // Green
        winnerText = "Person";
    }
    else if (PersonPoints == ComputerPoints)
    {

        TextColor = "\033[43m"; // Yellow
        winnerText = "No one";
    }
    else if (PersonPoints < ComputerPoints)
    {

        TextColor = "\033[41m"; // Red
        winnerText = "Computer";
    }

    cout << endl;

    cout << TextColor << "=====================================================" << ColorEnd << endl
         << TextColor << setw(53) << " " << ColorEnd << endl
         << TextColor << "            + + + G A M E   O V E R + + +            " << ColorEnd << endl
         << TextColor << setw(53) << " " << ColorEnd << endl
         << TextColor << "=====================================================" << ColorEnd << endl
         << TextColor << setw(53) << " " << ColorEnd << endl
         << TextColor << setw(16) << "Game Rounds" << " : " << setw(34) << left << Rounds << ColorEnd << endl
         << TextColor << setw(16) << "Player Wins" << " : " << setw(34) << left << PersonPoints << ColorEnd << endl
         << TextColor << setw(16) << "Computer Wins" << " : " << setw(34) << left << ComputerPoints << ColorEnd << endl
         << TextColor << setw(16) << "Draws" << " : " << setw(34) << left << Rounds - (ComputerPoints + PersonPoints) << ColorEnd << endl
         << TextColor << setw(16) << "Final Winner" << " : " << setw(34) << left << winnerText << ColorEnd << endl
         << TextColor << setw(53) << " " << ColorEnd << endl
         << TextColor << "=====================================================" << ColorEnd << endl;
}

void MainGame()
{

    GameStartScreen();

    int Rounds;
    Rounds = GetRounds();

    int PersonPoints = 0, ComputerPoints = 0;

    enGameChoice Person;
    enGameChoice Computer;

    enRoundState RoundState;

    for (int RoundNumber = 1; RoundNumber <= Rounds; RoundNumber++)
    {

        cout << endl;
        cout << "Round: " << RoundNumber << endl;

        Person = GetPersonChoice();
        Computer = GetCompterChoice();

        RoundState = StateCheck(Person, Computer);

        RoundScreen(RoundNumber, Person, Computer, RoundState);

        PointsCalc(PersonPoints, ComputerPoints, RoundState);
    }

    GameOverScreen(Rounds, PersonPoints, ComputerPoints);
}

void ClearScreen()
{

    cout << "\033[2J\033[H";
}

void Thanks()
{

    cout << "\n";
    cout << "=====================================================" << endl
         << "                Thank You For Playing                " << endl
         << "             Made By: Eng.Youssef Mousad             " << endl
         << "=====================================================" << endl;
    cout << "\n";
}

int main()
{

    srand((unsigned)time(NULL));

    bool NewGameChoice;
    do
    {

        ClearScreen();

        cout << "\n";

        MainGame();

        cout << "\n";

        cout << "Do you want to play again? (1) Yes (0) No" << endl
             << "Your Choice: ";
        cin >> NewGameChoice;

    } while (NewGameChoice);

    Thanks();

    return 0;
}
