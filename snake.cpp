#include <iostream>
#include <conio.h> // Para getch() e kbhit()
#include <cstdlib> // Para system("cls")

using namespace std;

bool gameOver;
const int largura = 20;
const int altura = 10;
int x, y, frutaX, frutaY, pontuacao;
int caudaX[100], caudaY[100];
int nCauda;
enum Direcao { STOP = 0, ESQUERDA, DIREITA, CIMA, BAIXO };
Direcao dir;

void Configurar()
{
    gameOver = false;
    dir = STOP;
    x = largura / 2;
    y = altura / 2;
    frutaX = rand() % largura;
    frutaY = rand() % altura;
    pontuacao = 0;
}

void Desenhar()
{
    system("cls");

    for (int i = 0; i < largura + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            if (j == 0)
                cout << "#"; // Parede esquerda

            if (i == y && j == x)
                cout << "O"; // Cabeça da cobra
            else if (i == frutaY && j == frutaX)
                cout << "F"; // Fruta
            else
            {
                bool printarCauda = false;
                for (int k = 0; k < nCauda; k++)
                {
                    if (caudaX[k] == j && caudaY[k] == i)
                    {
                        cout << "o"; // Cauda da cobra
                        printarCauda = true;
                    }
                }

                if (!printarCauda)
                    cout << " ";
            }

            if (j == largura - 1)
                cout << "#"; // Parede direita
        }
        cout << endl;
    }

    for (int i = 0; i < largura + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Pontuacao:" << pontuacao << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = ESQUERDA;
            break;
        case 'd':
            dir = DIREITA;
            break;
        case 'w':
            dir = CIMA;
            break;
        case 's':
            dir = BAIXO;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void AlgoritmoDoJogo()
{
    int prevX = caudaX[0];
    int prevY = caudaY[0];
    int prev2X, prev2Y;
    caudaX[0] = x;
    caudaY[0] = y;

    for (int i = 1; i < nCauda; i++)
    {
        prev2X = caudaX[i];
        prev2Y = caudaY[i];
        caudaX[i] = prevX;
        caudaY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case ESQUERDA:
        x--;
        break;
    case DIREITA:
        x++;
        break;
    case CIMA:
        y--;
        break;
    case BAIXO:
        y++;
        break;
    default:
        break;
    }

    if (x >= largura) x = 0; else if (x < 0) x = largura - 1;
    if (y >= altura) y = 0; else if (y < 0) y = altura - 1;

    for (int i = 0; i < nCauda; i++)
        if (caudaX[i] == x && caudaY[i] == y)
            gameOver = true;

    if (x == frutaX && y == frutaY)
    {
        pontuacao += 10;
        frutaX = rand() % largura;
        frutaY = rand() % altura;
        nCauda++;
    }
}

int main()
{
    Configurar();
    while (!gameOver)
    {
        Desenhar();
        Input();
        AlgoritmoDoJogo();
    }
    return 0;
}
