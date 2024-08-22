#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <iomanip>

using namespace std;

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define BRED "\e[1;31m"
#define UBLU "\e[4;34m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"

#define end "\e[0m"

int winsituation(int arr[][4])
{
    int k = 1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++, k++)
        {
            if (arr[i][j] != k && k != 16)
                return 0;
        }
    }
    return 1;
}

int readinput()
{
    return _getch();
}

void createMatrix(int arr[][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            arr[i][j] = 1 + j + 4 * i;
        }
    }
    arr[2][1] = 14;
    arr[2][2] = 10;
    arr[2][3] = 11;
    arr[3][1] = 15;
    arr[3][2] = 12;
    arr[3][3] = 0;
}

void createMatrixRandom(int arr[][4])
{
    int num[15];
    for (int i = 0; i < 15; i++)
        num[i] = i + 1;

    srand(time(NULL));
    int lastn = 14;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (lastn >= 0)
            {
                int val = rand() % (lastn + 1);
                arr[i][j] = num[val];
                num[val] = num[lastn--];
            }
        }
    }
    arr[3][3] = 0;
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int shiftUp(int arr[][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (arr[i][j] == 0 && i < 3)
            {
                swap(&arr[i][j], &arr[i + 1][j]);
                return 1;
            }
        }
    }
    return 0;
}

int shiftDown(int arr[][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (arr[i][j] == 0 && i > 0)
            {
                swap(&arr[i][j], &arr[i - 1][j]);
                return 1;
            }
        }
    }
    return 0;
}

int shiftRight(int arr[][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (arr[i][j] == 0 && j > 0)
            {
                swap(&arr[i][j], &arr[i][j - 1]);
                return 1;
            }
        }
    }
    return 0;
}

int shiftLeft(int arr[][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (arr[i][j] == 0 && j < 3)
            {
                swap(&arr[i][j], &arr[i][j + 1]);
                return 1;
            }
        }
    }
    return 0;
}

void showMatrix(int arr[][4])
{
    cout << "\n\n";
    cout << "\n\n                    ----------------------\n";
    for (int i = 0; i < 4; i++)
    {
        cout << "                    | ";
        for (int j = 0; j < 4; j++)
        {
            if (arr[i][j] != 0)
                cout << setw(2) << arr[i][j] << " |";
            else
                cout << setw(4) << " |";
        }
        cout << "\n";
    }
    cout << "                    ----------------------\n";
}

void showWinScreen()
{
    cout << HYEL "\n\n\n\n\n\n                             -------------------------\n";
    for (int i = 0; i < 4; i++)
    {
        cout << "                             | ";
        for (int j = 0; j < 4; j++)
        {
            if (4 * i + j + 1 != 16)
                cout << setw(2) << 4 * i + j + 1 << " | ";
            else
                cout << "   | ";
        }
        cout << "\n";
    }
    cout << "                             --------------------------\n" << end;
    cout << "\n\n\n\n";
    cout << GRN "           \a     ! ! ! ! ! ! ! ! ! ! YOU WON ! ! ! ! ! ! ! ! ! !\n\n " << end;
}

void showLoseScreen()
{
    cout << RED "0 0  0 0  0 0  0 0  o o  o o  o o  o o 0 0  0 0  0 0  0 0  o o  o o  o o  o o\n";
    cout << " |    |    |    |    |    |    |    |   |    |    |    |    |    |    |    |\n";
    cout << "---  ---  ---  ---  ---  ---  ---  --- ---  ---  ---  ---  ---  ---  ---  ---\n";
    cout << "\n\n\n\n\n                                 YOU LOSE                        \n\n\n\n";
    cout << "0 0  0 0  0 0  0 0  o o  o o  o o  o o 0 0  0 0  0 0  0 0  o o  o o  o o  o o\n";
    cout << " |    |    |    |    |    |    |    |   |    |    |    |    |    |    |    |\n";
    cout << "---  ---  ---  ---  ---  ---  ---  --- ---  ---  ---  ---  ---  ---  ---  ---\n" << end;
}

int main()
{
    char name[30];
    int arr[4][4];
    int mtry = 100;

    cout << BRED << "Enter name:" << end;
    cin >> name;

    while (1)
    {
        createMatrix(arr);

        system("cls");
        cout << "                " UBLU " How to play \n" << end;
        cout << CYN "\nMove Up   :" end " Up arrow key ";
        cout << CYN "\nMove Down :" end " Down arrow key";
        cout << CYN "\nMove Left :" end " Left arrow key";
        cout << CYN "\nMove Right:" end " Right arrow key";
        cout << "\n";
        cout << "\nEach move will decrease total moves by 1\n";
        cout << "\n\n";
        cout << CYN "To Win :" end " Align numbers in the matrix in order from 1 to 15";
        cout << "";
        cout << YEL "\n\n          To win, the matrix should look like this:" << endl;
        cout << HYEL "              -------------------------\n";

        for (int i = 0; i < 4; i++)
        {
            cout << "              | ";
            for (int j = 0; j < 4; j++)
            {
                if (4 * i + j + 1 != 16)
                    cout << setw(2) << 4 * i + j + 1 << " | ";
                else
                    cout << "   |";
            }
            cout << "\n";
        }

        cout << "              -------------------------\n" << end;

        cout << "\n\n";

        cout << GRN "Press enter to start the game..." << end;
        readinput();

        while (!winsituation(arr))
        {
            system("cls");
            if (mtry == 0)
                break;

            cout << MAG "\n\n                      Welcome " << name << "  \n\n" << end;
            cout << HMAG "                    Moves remaining: " << end;
            cout << RED << " " << mtry << end;

            showMatrix(arr);

            int key = readinput();

            switch (key)
            {
            case 72:
                shiftUp(arr);
                mtry--;
                break;

            case 80:
                shiftDown(arr);
                mtry--;
                break;

            case 77:
                shiftRight(arr);
                mtry--;
                break;

            case 75:
                shiftLeft(arr);
                mtry--;
                break;

            default:
                cout << "Invalid move!";
            }
        }

        system("cls");

        if (mtry == 0)
        {
            showLoseScreen();
        }
        else
        {
            showWinScreen();
            cout << HCYN "                                Your score is " << mtry << "\n\n\n\n\n\n\n\n" << end;
        }

        cout << GRN "Do you want to play again? (y/n): " << end;
        char choice;
        cin >> choice;
        if (choice == 'n' || choice == 'N')
            break;
        mtry = 100;
    }

    return 0;
}
