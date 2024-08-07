#include <iostream>
#include <cstdlib>
#define BEGIN 0
#define END 3
using namespace std;

class Game
{
public:
    void initialize()
    {
        for (int i = BEGIN; i < END; i++)
        {
            for (int j = BEGIN; j < END; j++)
            {
                for (int k = BEGIN; k < END; k++)
                {
                    for (int l = BEGIN; l < END; l++)
                    {
                        Table[i][j][k][l] = '*';
                    }
                }
                bigTable[i][j] = '*';
                moveCounter[i][j] = 0;
            }
        }
        M = -1;
        N = -1;
        Next = 'X';
    }
    void print()
    {
        system("CLS"); // brise sve prethodno sa konzole
        // ispisujemo vrstu po vrstu, zato prvo uvecavamo j, a tek zatim k
        for (int i = BEGIN; i < END; i++)
        {
            for (int k = BEGIN; k < END; k++)
            {
                for (int j = BEGIN; j < END; j++)
                {
                    for (int l = BEGIN; l < END; l++)
                    {
                        cout << Table[i][j][k][l] << " ";
                    }
                    if (j == END - 1)
                    {
                        continue;
                    }
                    cout << "| ";
                }
                cout << endl;
            }
            if (i == END - 1)
            {
                cout << endl;
                continue;
            }
            cout << "-----------------------" << endl;
        }
    }

    bool input()
    {
        int prevM = M;
        int prevN = N;
        cout << "Na potezu: " << Next << endl;
        while (true)
        {
            M = prevM;
            N = prevN;
            if (M == -1)
            {
                cout << "Izaberi polje u kom igras" << endl;
                cin >> M >> N;
                if (bigTable[M][N] != '*')
                {
                    cout << "Polje je zakljucano\n";
                    continue;
                }
            }
            cout << "Odigraj potez" << endl;
            cin >> m >> n;
            if (Table[M][N][m][n] != '*')
            {
                cout << "Mesto je zauzeto\n";
            }
            else
            {
                Table[M][N][m][n] = Next;
                moveCounter[M][N]++;
                if (isWon(Table[M][N])) // proverava da li je polje osvojeno
                {
                    print();
                    cout << "Osvojeno polje\n";
                    system("PAUSE"); // u sustini nepotrebno, ali da bude jasnije sta se sve izdesavalo
                    setMatrix(Table[M][N]);
                    bigTable[M][N] = Next;
                    if (isWon(bigTable)) // ako je doslo do osvojenog polja, proverava da li je pobedjeno u celoj igri
                    {
                        cout << "Pobedio je igrac " << Next << endl;
                        return true; // doslo je do pobede
                    }
                }
                else // ako nije osvojeno polje, proveravamo da li je neresen rezultat
                {
                    if (moveCounter[M][N] == 9)
                    {
                        bigTable[M][N] = 'N'; // zakljucava polje
                    }
                }
                if (Next == 'X')
                {
                    Next = 'O';
                }
                else
                {
                    Next = 'X';
                }
                if (bigTable[m][n] == '*')
                {
                    M = m;
                    N = n;
                }
                else
                {
                    M = -1;
                    N = -1;
                }
                return false; // nije doslo do pobede
            }
        }
    }

private:
    char Table[END][END][END][END]; // cuva stanje table
    char bigTable[END][END];        // cuva pobednike mini igara
    int moveCounter[END][END];      // cuva broj poteza u svakom polju
    char Next;                      // oznacava sledeceg igraca, moze biti X ili O
    int M;                          // koordinate velike table
    int N;
    int m; // koordinate male table
    int n;

    bool isWon(char Matrix[END][END])
    {
        for (int i = BEGIN; i < END; i++) // proverava po vrsti i koloni
        {
            if (Matrix[i][0] == Next && Matrix[i][1] == Next && Matrix[i][2] == Next)
            {
                return true;
            }
            else if (Matrix[0][i] == Next && Matrix[1][i] == Next && Matrix[2][i] == Next)
            {
                return true;
            }
        }
        // proverava dijagonale
        if (Matrix[0][0] == Next && Matrix[1][1] == Next && Matrix[2][2] == Next)
        {
            return true;
        }
        if (Matrix[2][0] == Next && Matrix[1][1] == Next && Matrix[0][2] == Next)
        {
            return true;
        }
        return false;
    }

    void setMatrix(char Matrix[END][END]) // koristim da obelezim osvojena polja
    {
        for (int i = BEGIN; i < END; i++)
        {
            for (int j = BEGIN; j < END; j++)
            {
                Matrix[i][j] = Next;
            }
        }
    }
};

int main()
{
    Game game;
    game.initialize();
    game.print();
    bool end = false;
    while (true)
    {
        end = game.input();
        if (end)
        {
            break;
        }
        game.print();
    }
    return 0;
}
