// estado del codigo, nos falta la interfaz de usuario y talvez el modo de juego contra la maquina, nada grave,
// traduje el codigo en casi su totalidad para que se entienda mejor, y te puse anotaciones por si quieres escribir mas del codigo...

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Reversi
{
    vector<vector<char>> mesa;
    int n = 8;
    int particimante;
    int Ganador;
    unordered_map<char, int> fichaRestante;
    unordered_map<char, int> ficahEnMesa;

public:
    Reversi()
    {
        particimante = 1;
        Ganador = 0;
        vector<char> temp;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                temp.push_back('-');
            }
            mesa.push_back(temp);
        }

        //aqui se ve la colocacion de las cuatro fichas tanto las dos negras como las dos
        // chias blancas en el tablero
        mesa[3][3] = 'N';
        mesa[3][4] = 'B';
        mesa[4][3] = 'B';
        mesa[4][4] = 'N';
        fichaRestante.insert({'N', 30});
        fichaRestante.insert({'B', 30});
        ficahEnMesa.insert({'N', 2});
        ficahEnMesa.insert({'B', 2});
    }

private:
    bool revisargiro(char color, int fil, int col, int deltaRow, int deltaCol)
    {
        char oppColour = 'B';
        if (color == 'B')
        {
            oppColour = 'N';
        }

        if ((fil < 0) || (fil >= 8) || (col < 0) || (col >= 8))
        {
            return false;
        }

        if (mesa[fil][col] == oppColour)
        {
            while ((fil >= 0) && (fil < 8) && (col >= 0) && (col < 8))
            {
                fil += deltaRow;
                col += deltaCol;
                if (mesa[fil][col] == '-')
                {
                    return false;
                }
                if (mesa[fil][col] == color)
                {
                    return true;
                }
            }
        }
        return false;
    }
    void cambiaFicha(char color, int fil, int col, int deltaRow, int deltaCol)
    {
        char oppColour = 'B';
        if (color == 'B')
        {
            oppColour = 'N';
        }

        while (mesa[fil][col] == oppColour)
        {
            mesa[fil][col] = color;
            ficahEnMesa[color]++;
            ficahEnMesa[oppColour]--;
            fil += deltaRow;
            col += deltaCol;
        }
        return;
    }

public:

    //valor booleano para acesorarce de que nuestro movimiento sea valido en el trablero,
    // de lo contrario el movimiento contara como falso, y realiza los chequeos en las 8 pociciones posibles
    //arriba, abajo, izquierda, derecha, ariba a la derecha e izquierda, abajo a la derecha e izquierda.
    bool movimientoValido(int fil, int col)
    {
        if ((fil < 0) || (fil >= 8) || (col < 0) || (col >= 8))
        {
            return false;
        }

        if (mesa[fil][col] != '-')
        {
            return false;
        }

        char color = 'B';
        if (getPlayer() == 1)
        {
            color = 'N';
        }

        // ficha en la parte superior
        if (revisargiro(color, fil - 1, col, -1, 0))
        {
            return true;
        }
        // ficha en la parte inferior
        if (revisargiro(color, fil + 1, col, 1, 0))
        {
            return true;
        }
        // ficha en la parte izquierda
        if (revisargiro(color, fil, col - 1, 0, -1))
        {
            return true;
        }
        // ficha en la parte derecha
        if (revisargiro(color, fil, col + 1, 0, 1))
        {
            return true;
        }
        //  ficha en la parte inferiro derecha
        if (revisargiro(color, fil + 1, col + 1, 1, 1))
        {
            return true;
        }
        //  ficha en la parte inferior izquierda
        if (revisargiro(color, fil + 1, col - 1, 1, -1))
        {
            return true;
        }
        //  ficha en la parte superior derecha
        if (revisargiro(color, fil - 1, col + 1, -1, 1))
        {
            return true;
        }
        //  ficha en la parte superior izquierda
        if (revisargiro(color, fil - 1, col - 1, -1, -1))
        {
            return true;
        }

        return false;
    }

    // aqui se realiza la el recuento de fichas del jugardor, cauntas tiene en la mesa y cantas en su poder
    // ademas de el movimiento, en este caso la colocacion de la ficha en el tablero
    void movimiento(int fil, int col)
    {
        char color = 'B';
        if (getPlayer() == 1)
        {
            color = 'N';
        }
        mesa[fil][col] = color;
        fichaRestante[color]--;
        ficahEnMesa[color]++;

        // ficha en la parte superior
        if (revisargiro(color, fil - 1, col, -1, 0))
        {
            cambiaFicha(color, fil - 1, col, -1, 0);
        }
        // ficha en la parte inferiro
        if (revisargiro(color, fil + 1, col, 1, 0))
        {
            cambiaFicha(color, fil + 1, col, 1, 0);
        }
        // ficha en la parte izquierda
        if (revisargiro(color, fil, col - 1, 0, -1))
        {
            cambiaFicha(color, fil, col - 1, 0, -1);
        }
        // ficha en la parte derecha
        if (revisargiro(color, fil, col + 1, 0, 1))
        {
            cambiaFicha(color, fil, col + 1, 0, 1);
        }
        // ficha en la parte inferiro derecha
        if (revisargiro(color, fil + 1, col + 1, 1, 1))
        {
            cambiaFicha(color, fil + 1, col + 1, 1, 1);
        }
        // ficha en la parte inferiro izquierda
        if (revisargiro(color, fil + 1, col - 1, 1, -1))
        {
            cambiaFicha(color, fil + 1, col - 1, 1, -1);
        }
        // ficha en la parte superior derecha
        if (revisargiro(color, fil - 1, col + 1, -1, 1))
        {
            cambiaFicha(color, fil - 1, col + 1, -1, 1);
        }
        // ficha en la parte superior izquierda
        if (revisargiro(color, fil - 1, col - 1, -1, -1))
        {
            cambiaFicha(color, fil - 1, col - 1, -1, -1);
        }
        particimante = -1 * particimante;
        return;
    }

    //aqui esta nuestra funcion void que sen encarga de mostranos el tablaero, ademas del recuento de fichas y
    //cual es es jugador que le toca.
    void tablero()
    {
        for (int i = 0; i < n; i++)
        {
            cout << i << "| ";
            for (int j = 0; j < n; j++)
            {
                cout << mesa[i][j] << " | ";
            }
            cout << "\n";
        }
        cout << "   0   1   2   3   4   5   6   7\n";
        cout << "Fichas del jugador " << getPlayer() << ": " << fichaRestante['N'] << "\n";
        cout << "Fichas del jugador " << getOppPlayer() << ": " << fichaRestante['B'] << "\n";
        cout << "Fichas en la mesa del jugador " << getPlayer() << ": " << ficahEnMesa['N'] << "\n";
        cout << "Fichas en la mesa del jugador " << getOppPlayer() << ": " << ficahEnMesa['B'] << "\n";
        return;
    }

    // nuestro valor booleano para arojar el final de la partida, esto es segun sea las valirables pertinesnte, ya sea por que se acabaron la fichas
    // y la partida no puede continuar.
    bool finJuego()
    {
        if (ficahEnMesa['N'] == 0)
        {
            Ganador = -1;
            return true;
        }
        else if (ficahEnMesa['B'] == 0)
        {
            Ganador = 1;
            return true;
        }
        else if (fichaRestante['N'] == 0 && fichaRestante['B'] == 0)
        {
            if (ficahEnMesa['N'] > ficahEnMesa['B'])
            {
                Ganador = 1;
            }
            else if (ficahEnMesa['N'] < ficahEnMesa['B'])
            {
                Ganador = -1;
            }
            else
            {
                Ganador = 0;
            }
            return true;
        }
        return false;
    }
    int getPlayer()
    {
        if (particimante == -1)
        {
            return 2;
        }
        return particimante;
    }
    int getOppPlayer()
    {
        if (particimante == -1)
        {
            return 1;
        }
        return 2;
    }
    int ganador()
    {
        return Ganador;
    }
};

    // la funcion main donde empieza el juego, estan unos cuantos csl para poder despejar el tablero y que no se sature la terminal,
    //y validaciones para mostrarnos el progrso del juego, tanto si se gano la partida, si es un empate en el que quedo el juego, o si
    // nuesto movimientos son validos o no, en esta parte el codigo se encatga de notificarnos si es asi
int main()
{
    Reversi Juego;
    cout << "ha iniciado el juego.\n";
    Juego.tablero();
    int fil;
    int col;

    while (!Juego.finJuego())
    {
        cout << "turno del jugador" << Juego.getPlayer() << "\n";
        cout << "numero de fila ";
        cin >> fil;
        cout << "numero de la columna ";
        cin >> col;

        if (Juego.movimientoValido(fil, col))
        {
            system ("cls");
            Juego.movimiento(fil, col);
        }
        else
        {
            system ("cls");
            cout << "invalido. intente denuevo.\n";
        }

        Juego.tablero();
    }

    cout << "fin del juego.\n";
    if (Juego.ganador() != 0)
    {
        system ("cls");
        cout << "el ganador es-" << Juego.ganador() << ".\n";
    }
    else
    {
        system ("cls");
        cout << "fue un empate.\n";
    }

    return 0;
}
