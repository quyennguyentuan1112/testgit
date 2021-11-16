#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>

using namespace std;

int **init_board()
{
    int **t = new int *[5];
    for (int i = 0; i < 5; i++)
    {
        t[i] = new int[5];
        if (i == 0)
        {
            for (int j = 0; j < 5; j++)
                t[i][j] = 1;
        }
        if (i == 4)
        {
            for (int j = 0; j < 5; j++)
                t[i][j] = -1;
        }
    }
    t[1][0] = 1;
    t[1][4] = 1;
    t[2][0] = 1;
    t[2][4] = -1;
    t[3][0] = -1;
    t[3][4] = -1;
    return t;
}

int **copy_board(int **board)
{
    int **n_b = new int *[5];
    for (int i = 0; i < 5; i++)
    {
        n_b[i] = new int[5];
        for (int j = 0; j < 5; j++)
        {
            n_b[i][j] = board[i][j];
        }
    }
    return n_b;
}

void print_board(int **board)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (board[4 - i][j] == 1)
                cout << "X ";
            else if (board[4 - i][j] == -1)
                cout << "O ";
            else
                cout << "- ";
        }
        cout << endl;
    }
}

struct Position
{
    int x;
    int y;
    Position() { x = y = 0; }
    Position(int a, int b)
    {
        x = a;
        y = b;
    }
};

struct Move
{
    Position pos_start, pos_end;
    Move(Position s, Position e)
    {
        pos_start = s;
        pos_end = e;
    }
};

vector<Position> biganh(int **board, int a, int b, int player)
{
    int i = a;
    int j = b;
    vector<Position> k;
    Position tren(i + 1, j);
    Position duoi(i - 1, j);
    Position trai(i, j - 1);
    Position phai(i, j + 1);
    Position trenphai(i + 1, j + 1);
    Position duoiphai(i - 1, j + 1);
    Position trentrai(i + 1, j - 1);
    Position duoitrai(i - 1, j - 1);
    if (i != 0 && i != 4)
    {
        if (board[i - 1][j] == -player && board[i + 1][j] == -player)
        {
            board[i - 1][j] = player;
            board[i + 1][j] = player;
            k.push_back(tren);
            k.push_back(duoi);
        }
    }
    if (j != 0 && j != 4)
    {
        if (board[i][j - 1] == -player && board[i][j + 1] == -player)
        {
            board[i][j - 1] = player;
            board[i][j + 1] = player;
            k.push_back(trai);
            k.push_back(phai);
        }
    }
    if (i == 0 && i == 4 && j == 0 && j == 4)
    {
        if ((i == 1 && j == 1) || (i == 1 && j == 3) || (i == 2 && j == 2) || (i == 3 && j == 1) || (i == 3 && j == 3))
        {
            if (board[i - 1][j - 1] == -player && board[i + 1][j + 1] == -player)
            {
                board[i - 1][j - 1] = player;
                board[i + 1][j + 1] = player;
                k.push_back(duoitrai);
                k.push_back(trenphai);
            }
            if (board[i - 1][j + 1] == -player && board[i + 1][j - 1] == -player)
            {
                board[i - 1][j + 1] = player;
                board[i + 1][j - 1] = player;
                k.push_back(duoiphai);
                k.push_back(trentrai);
            }
        }
    }
    int n = k.size();
    if (n != 0)
    {
        vector<Position> l;
        for (int t = 0; t < n; t++)
        {
            l = biganh(board, k[t].x, k[t].y, player);
            int m = l.size();
            for (int v = 0; v < m; v++)
            {
                k.push_back(l[v]);
            }
        }
    }
    return k;
}
vector<Position> ganh(int **board, Move m, int player)
{
    board[m.pos_start.x][m.pos_start.y] = 0;
    board[m.pos_end.x][m.pos_end.y] = player;
    vector<Position> s;
    s = biganh(board, m.pos_end.x, m.pos_end.y, player);
    return s;
}
bool dichuyenko(int **board, int a, int b, int player)
{
    int i = a;
    int j = b;
    if (i != 0)
    {
        if (board[i - 1][j] != player && board[i - 1][j] != -player)
            return 0;
    }
    if (i != 4)
    {
        if (board[i + 1][j] != player && board[i + 1][j] != -player)
            return 0;
    }
    if (j != 0)
    {
        if (board[i][j - 1] != player && board[i][j - 1] != -player)
            return 0;
    }
    if (j != 4)
    {
        if (board[i][j + 1] != player && board[i][j + 1] != -player)
            return 0;
    }
    if ((i == 1 && j == 1) || (i == 1 && j == 3) || (i == 2 && j == 2) || (i == 3 && j == 1) || (i == 3 && j == 3))
    {
        if (board[i - 1][j - 1] != player && board[i - 1][j - 1] != -player)
            return 0;
        if (board[i + 1][j + 1] != player && board[i + 1][j + 1] != -player)
            return 0;
        if (board[i - 1][j + 1] != player && board[i - 1][j + 1] != -player)
            return 0;
        if (board[i + 1][j - 1] != player && board[i + 1][j - 1] != -player)
            return 0;
    }
    if (i == 0 || i == 4 || j == 0 || j == 4)
    {
        if (i == 0 && j == 0)
        {
            if (board[i + 1][j + 1] != player && board[i + 1][j + 1] != -player)
            {
                return 0;
            }
        }
        if (i == 2 && j == 0)
        {
            if (board[i - 1][j + 1] != player && board[i - 1][j + 1] != -player)
            {
                return 0;
            }
            if (board[i + 1][j + 1] != player && board[i + 1][j + 1] != -player)
            {
                return 0;
            }
        }
        if (i == 4 && j == 0)
        {
            if (board[i - 1][j + 1] != player && board[i - 1][j + 1] != -player)
            {
                return 0;
            }
        }
        if (i == 4 && j == 2)
        {
            if (board[i - 1][j - 1] != player && board[i - 1][j - 1] != -player)
            {
                return 0;
            }
            if (board[i - 1][j + 1] != player && board[i - 1][j + 1] != -player)
            {
                return 0;
            }
        }
        if (i == 4 && j == 4)
        {
            if (board[i - 1][j - 1] != player && board[i - 1][j - 1] != -player)
            {
                return 0;
            }
        }
        if (i == 2 && j == 4)
        {
            if (board[i - 1][j - 1] != player && board[i - 1][j - 1] != -player)
            {
                return 0;
            }
            if (board[i + 1][j - 1] != player && board[i + 1][j - 1] != -player)
            {
                return 0;
            }
        }
        if (i == 0 && j == 4)
        {
            if (board[i + 1][j - 1] != player && board[i + 1][j - 1] != -player)
            {
                return 0;
            }
        }
        if (i == 0 && j == 2)
        {
            if (board[i + 1][j - 1] != player && board[i + 1][j - 1] != -player)
            {
                return 0;
            }
            if (board[i + 1][j + 1] != player && board[i + 1][j + 1] != -player)
            {
                return 0;
            }
        }
    }
    return 1;
}
bool vayko(int **board, int i, int j, int player, vector<Position> k)
{
    vector<Position> a;
    if (i != 0)
    {
        if (board[i - 1][j] == -player)
        {
            Position b(i - 1, j);
            a.push_back(b);
        }
    }
    if (i != 4)
    {
        if (board[i + 1][j] == -player)
        {
            Position b(i + 1, j);
            a.push_back(b);
        }
    }
    if (j != 0)
    {
        if (board[i][j - 1] == -player)
        {
            Position b(i, j - 1);
            a.push_back(b);
        }
    }
    if (j != 4)
    {
        if (board[i][j + 1] == -player)
        {
            Position b(i, j + 1);
            a.push_back(b);
        }
    }
    if ((i == 1 && j == 1) || (i == 1 && j == 3) || (i == 2 && j == 2) || (i == 3 && j == 1) || (i == 3 && j == 3))
    {
        if (board[i - 1][j - 1] == -player)
        {
            Position b(i - 1, j - 1);
            a.push_back(b);
        }
        if (board[i + 1][j + 1] == -player)
        {
            Position b(i + 1, j + 1);
            a.push_back(b);
        }
        if (board[i - 1][j + 1] == -player)
        {
            Position b(i - 1, j + 1);
            a.push_back(b);
        }
        if (board[i + 1][j - 1] == -player)
        {
            Position b(i + 1, j - 1);
            a.push_back(b);
        }
    }
    if (i == 0 || i == 4 || j == 0 || j == 4)
    {
        if (i == 0 && j == 0)
        {
            if (board[i + 1][j + 1] == -player)
            {
                Position b(i + 1, j + 1);
                a.push_back(b);
            }
        }
        if (i == 2 && j == 0)
        {
            if (board[i - 1][j + 1] == -player)
            {
                Position b(i - 1, j + 1);
                a.push_back(b);
            }
            if (board[i + 1][j + 1] == -player)
            {
                Position b(i + 1, j + 1);
                a.push_back(b);
            }
        }
        if (i == 4 && j == 0)
        {
            if (board[i - 1][j + 1] == -player)
            {
                Position b(i - 1, j + 1);
                a.push_back(b);
            }
        }
        if (i == 4 && j == 2)
        {
            if (board[i - 1][j - 1] == -player)
            {
                Position b(i - 1, j - 1);
                a.push_back(b);
            }
            if (board[i - 1][j + 1] == -player)
            {
                Position b(i - 1, j + 1);
                a.push_back(b);
            }
        }
        if (i == 4 && j == 4)
        {
            if (board[i - 1][j - 1] == -player)
            {
                Position b(i - 1, j - 1);
                a.push_back(b);
            }
        }
        if (i == 2 && j == 4)
        {
            if (board[i - 1][j - 1] == -player)
            {
                Position b(i - 1, j - 1);
                a.push_back(b);
            }
            if (board[i + 1][j - 1] == -player)
            {
                Position b(i + 1, j - 1);
                a.push_back(b);
            }
        }
        if (i == 0 && j == 4)
        {
            if (board[i + 1][j - 1] == -player)
            {
                Position b(i + 1, j - 1);
                a.push_back(b);
            }
        }
        if (i == 0 && j == 2)
        {
            if (board[i + 1][j - 1] == -player)
            {
                Position b(i + 1, j - 1);
                a.push_back(b);
            }
            if (board[i + 1][j + 1] == -player)
            {
                Position b(i + 1, j + 1);
                a.push_back(b);
            }
        }
    }
    int n = k.size();
    int m = a.size();
    int r = 0;
    for (int p = 0; p < m; p++)
    {
        for (int q = 0; q < n; q++)
        {
            if (a[p].x == k[q].x && a[p].y == k[q].y)
            {
                r++;
            }
        }
    }
    if (r == m)
        return 1;
    return 0;
}
vector<Position> vay(int **board, Move m, int player)
{
    vector<Position> s;
    board[m.pos_start.x][m.pos_start.y] = 0;
    board[m.pos_end.x][m.pos_end.y] = player;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (board[i][j] == -player)
            {
                if (dichuyenko(board, i, j, player))
                {
                    Position a(i, j);
                    s.push_back(a);
                }
            }
        }
    }
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        if (!vayko(board, s[i].x, s[i].y, player, s))
        {
            s.erase(s.begin() + i);
            n--;
            i--;
        }
    }
    return s;
}

bool soquan(int **current_board, int **previous_board, int player)
{
    int a = 0, b = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (current_board[i][j] == player)
                a++;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (previous_board[i][j] == player)
                b++;
        }
    }
    if (a == b)
        return 1;
    return 0;
}
bool ganhko(int a, int b, int **current_board, int player)
{
    int i = a;
    int j = b;
    if (i != 0 && i != 4)
    {
        if (current_board[i - 1][j] == -player && current_board[i + 1][j] == -player)
            return 1;
    }
    if (j != 0 && j != 4)
    {
        if (current_board[i][j - 1] == -player && current_board[i][j + 1] == -player)
            return 1;
    }
    if (i == 0 && i == 4 && j == 0 && j == 4)
    {
        if ((i == 1 && j == 1) || (i == 1 && j == 3) || (i == 2 && j == 2) || (i == 3 && j == 1) || (i == 3 && j == 3))
        {
            if (current_board[i - 1][j - 1] == -player && current_board[i + 1][j + 1] == -player)
                return 1;
            if (current_board[i - 1][j + 1] == -player && current_board[i + 1][j - 1] == -player)
                return 1;
        }
    }

    return 0;
}
bool moko(int **current_board, int **previous_board, int player)
{
    if (soquan(current_board, previous_board, player))
    {
        int a, b;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (current_board[i][j] == previous_board[i][j])
                    continue;
                else
                {
                    if (previous_board[i][j] == (player * (-1)))
                    {
                        a = i;
                        b = j;
                    }
                }
            }
        }
        int i = a;
        int j = b;
        if (ganhko(a, b, current_board, player))
        {
            if (i != 0)
            {
                if (current_board[i - 1][j] == player)
                    return 1;
            }
            if (i != 4)
            {
                if (current_board[i + 1][j] == player)
                    return 1;
            }
            if (j != 0)
            {
                if (current_board[i][j - 1] == player)
                    return 1;
            }
            if (j != 4)
            {
                if (current_board[i][j + 1] == player)
                    return 1;
            }
            if ((i == 1 && j == 1) || (i == 1 && j == 3) || (i == 2 && j == 2) || (i == 3 && j == 1) || (i == 3 && j == 3))
            {
                if (current_board[i - 1][j - 1] == player)
                    return 1;
                if (current_board[i + 1][j + 1] == player)
                    return 1;
                if (current_board[i - 1][j + 1] == player)
                    return 1;
                if (current_board[i + 1][j - 1] == player)
                    return 1;
            }
            if (i == 0 || i == 4 || j == 0 || j == 4)
            {
                if (i == 0 && j == 0)
                {
                    if (current_board[i + 1][j + 1] == player)
                    {
                        return 1;
                    }
                }
                if (i == 2 && j == 0)
                {
                    if (current_board[i - 1][j + 1] == player)
                    {
                        return 1;
                    }
                    if (current_board[i + 1][j + 1] == player)
                    {
                        return 1;
                    }
                }
                if (i == 4 && j == 0)
                {
                    if (current_board[i - 1][j + 1] == player)
                    {
                        return 1;
                    }
                }
                if (i == 4 && j == 2)
                {
                    if (current_board[i - 1][j - 1] == player)
                    {
                        return 1;
                    }
                    if (current_board[i - 1][j + 1] == player)
                    {
                        return 1;
                    }
                }
                if (i == 4 && j == 4)
                {
                    if (current_board[i - 1][j - 1] == player)
                    {
                        return 1;
                    }
                }
                if (i == 2 && j == 4)
                {
                    if (current_board[i - 1][j - 1] == player)
                    {
                        return 1;
                    }
                    if (current_board[i + 1][j - 1] == player)
                    {
                        return 1;
                    }
                }
                if (i == 0 && j == 4)
                {
                    if (current_board[i + 1][j - 1] == player)
                    {
                        return 1;
                    }
                }
                if (i == 0 && j == 2)
                {
                    if (current_board[i + 1][j - 1] == player)
                    {
                        return 1;
                    }
                    if (current_board[i + 1][j + 1] == player)
                    {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
vector<Move> bay_or_mo(int **current_board, int **previous_board, int player)
{
    vector<Move> s;
    if (moko(current_board, previous_board, player))
    {
        int a, b;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (current_board[i][j] == previous_board[i][j])
                    continue;
                else
                {
                    if (previous_board[i][j] == (player * (-1)))
                    {
                        a = i;
                        b = j;
                    }
                }
            }
        }
        Position sau;
        sau.y = b;
        sau.x = a;
        Position trc;
        Move p(trc, sau);
        int i = a;
        int j = b;
        if (i != 0)
        {
            if (current_board[i - 1][j] == player)
            {
                p.pos_start.x = i - 1;
                p.pos_start.y = j;
                s.push_back(p);
            }
        }
        if (i != 4)
        {
            if (current_board[i + 1][j] == player)
            {
                p.pos_start.x = i + 1;
                p.pos_start.y = j;
                s.push_back(p);
            }
        }
        if (j != 0)
        {
            if (current_board[i][j - 1] == player)
            {
                p.pos_start.x = i;
                p.pos_start.y = j - 1;
                s.push_back(p);
            }
        }
        if (j != 4)
        {
            if (current_board[i][j + 1] == player)
            {
                p.pos_start.x = i;
                p.pos_start.y = j + 1;
                s.push_back(p);
            }
        }
        if ((i == 1 && j == 1) || (i == 1 && j == 3) || (i == 2 && j == 2) || (i == 3 && j == 1) || (i == 3 && j == 3))
        {
            if (current_board[i - 1][j - 1] == player)
            {
                p.pos_start.x = i - 1;
                p.pos_start.y = j - 1;
                s.push_back(p);
            }
            if (current_board[i + 1][j + 1] == player)
            {
                p.pos_start.x = i + 1;
                p.pos_start.y = j + 1;
                s.push_back(p);
            }
            if (current_board[i - 1][j + 1] == player)
            {
                p.pos_start.x = i - 1;
                p.pos_start.y = j + 1;
                s.push_back(p);
            }
            if (current_board[i + 1][j - 1] == player)
            {
                p.pos_start.x = i + 1;
                p.pos_start.y = j - 1;
                s.push_back(p);
            }
        }
        if (i == 0 || i == 4 || j == 0 || j == 4)
        {
            if (i == 0 && j == 0)
            {
                if (current_board[i + 1][j + 1] == player)
                {
                    p.pos_start.x = i + 1;
                    p.pos_start.y = j + 1;
                    s.push_back(p);
                }
            }
            if (i == 2 && j == 0)
            {
                if (current_board[i - 1][j + 1] == player)
                {
                    p.pos_start.x = i - 1;
                    p.pos_start.y = j + 1;
                    s.push_back(p);
                }
                if (current_board[i + 1][j + 1] == player)
                {
                    p.pos_start.x = i + 1;
                    p.pos_start.y = j + 1;
                    s.push_back(p);
                }
            }
            if (i == 4 && j == 0)
            {
                if (current_board[i - 1][j + 1] == player)
                {
                    p.pos_start.x = i - 1;
                    p.pos_start.y = j + 1;
                    s.push_back(p);
                }
            }
            if (i == 4 && j == 2)
            {
                if (current_board[i - 1][j - 1] == player)
                {
                    p.pos_start.x = i - 1;
                    p.pos_start.y = j - 1;
                    s.push_back(p);
                }
                if (current_board[i - 1][j + 1] == player)
                {
                    p.pos_start.x = i - 1;
                    p.pos_start.y = j + 1;
                    s.push_back(p);
                }
            }
            if (i == 4 && j == 4)
            {
                if (current_board[i - 1][j - 1] == player)
                {
                    p.pos_start.x = i - 1;
                    p.pos_start.y = j - 1;
                    s.push_back(p);
                }
            }
            if (i == 2 && j == 4)
            {
                if (current_board[i - 1][j - 1] == player)
                {
                    p.pos_start.x = i - 1;
                    p.pos_start.y = j - 1;
                    s.push_back(p);
                }
                if (current_board[i + 1][j - 1] == player)
                {
                    p.pos_start.x = i + 1;
                    p.pos_start.y = j - 1;
                    s.push_back(p);
                }
            }
            if (i == 0 && j == 4)
            {
                if (current_board[i + 1][j - 1] == player)
                {
                    p.pos_start.x = i + 1;
                    p.pos_start.y = j - 1;
                    s.push_back(p);
                }
            }
            if (i == 0 && j == 2)
            {
                if (current_board[i + 1][j - 1] == player)
                {
                    p.pos_start.x = i + 1;
                    p.pos_start.y = j - 1;
                    s.push_back(p);
                }
                if (current_board[i + 1][j + 1] == player)
                {
                    p.pos_start.x = i + 1;
                    p.pos_start.y = j + 1;
                    s.push_back(p);
                }
            }
        }
    }
    return s;
}
vector<Move> get_valid_moves(int **current_board, int **previous_board, int player)
{
    vector<Move> s;
    if (moko(current_board, previous_board, player))
    {
        int a, b;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (current_board[i][j] == previous_board[i][j])
                    continue;
                else
                {
                    if (previous_board[i][j] == (player * (-1)))
                    {
                        a = i;
                        b = j;
                    }
                }
            }
        }
        Position sau;
        sau.y = b;
        sau.x = a;
        Position trc;
        Move p(trc, sau);
        int i = a;
        int j = b;
        if (i != 0)
        {
            if (current_board[i - 1][j] == player)
            {
                p.pos_start.x = i - 1;
                p.pos_start.y = j;
                s.push_back(p);
            }
        }
        if (i != 4)
        {
            if (current_board[i + 1][j] == player)
            {
                p.pos_start.x = i + 1;
                p.pos_start.y = j;
                s.push_back(p);
            }
        }
        if (j != 0)
        {
            if (current_board[i][j - 1] == player)
            {
                p.pos_start.x = i;
                p.pos_start.y = j - 1;
                s.push_back(p);
            }
        }
        if (j != 4)
        {
            if (current_board[i][j + 1] == player)
            {
                p.pos_start.x = i;
                p.pos_start.y = j + 1;
                s.push_back(p);
            }
        }
        if ((i == 1 && j == 1) || (i == 1 && j == 3) || (i == 2 && j == 2) || (i == 3 && j == 1) || (i == 3 && j == 3))
        {
            if (current_board[i - 1][j - 1] == player)
            {
                p.pos_start.x = i - 1;
                p.pos_start.y = j - 1;
                s.push_back(p);
            }
            if (current_board[i + 1][j + 1] == player)
            {
                p.pos_start.x = i + 1;
                p.pos_start.y = j + 1;
                s.push_back(p);
            }
            if (current_board[i - 1][j + 1] == player)
            {
                p.pos_start.x = i - 1;
                p.pos_start.y = j + 1;
                s.push_back(p);
            }
            if (current_board[i + 1][j - 1] == player)
            {
                p.pos_start.x = i + 1;
                p.pos_start.y = j - 1;
                s.push_back(p);
            }
        }
        if (i == 0 || i == 4 || j == 0 || j == 4)
        {
            if (i == 0 && j == 0)
            {
                if (current_board[i + 1][j + 1] == player)
                {
                    p.pos_start.x = i + 1;
                    p.pos_start.y = j + 1;
                    s.push_back(p);
                }
            }
            if (i == 2 && j == 0)
            {
                if (current_board[i - 1][j + 1] == player)
                {
                    p.pos_start.x = i - 1;
                    p.pos_start.y = j + 1;
                    s.push_back(p);
                }
                if (current_board[i + 1][j + 1] == player)
                {
                    p.pos_start.x = i + 1;
                    p.pos_start.y = j + 1;
                    s.push_back(p);
                }
            }
            if (i == 4 && j == 0)
            {
                if (current_board[i - 1][j + 1] == player)
                {
                    p.pos_start.x = i - 1;
                    p.pos_start.y = j + 1;
                    s.push_back(p);
                }
            }
            if (i == 4 && j == 2)
            {
                if (current_board[i - 1][j - 1] == player)
                {
                    p.pos_start.x = i - 1;
                    p.pos_start.y = j - 1;
                    s.push_back(p);
                }
                if (current_board[i - 1][j + 1] == player)
                {
                    p.pos_start.x = i - 1;
                    p.pos_start.y = j + 1;
                    s.push_back(p);
                }
            }
            if (i == 4 && j == 4)
            {
                if (current_board[i - 1][j - 1] == player)
                {
                    p.pos_start.x = i - 1;
                    p.pos_start.y = j - 1;
                    s.push_back(p);
                }
            }
            if (i == 2 && j == 4)
            {
                if (current_board[i - 1][j - 1] == player)
                {
                    p.pos_start.x = i - 1;
                    p.pos_start.y = j - 1;
                    s.push_back(p);
                }
                if (current_board[i + 1][j - 1] == player)
                {
                    p.pos_start.x = i + 1;
                    p.pos_start.y = j - 1;
                    s.push_back(p);
                }
            }
            if (i == 0 && j == 4)
            {
                if (current_board[i + 1][j - 1] == player)
                {
                    p.pos_start.x = i + 1;
                    p.pos_start.y = j - 1;
                    s.push_back(p);
                }
            }
            if (i == 0 && j == 2)
            {
                if (current_board[i + 1][j - 1] == player)
                {
                    p.pos_start.x = i + 1;
                    p.pos_start.y = j - 1;
                    s.push_back(p);
                }
                if (current_board[i + 1][j + 1] == player)
                {
                    p.pos_start.x = i + 1;
                    p.pos_start.y = j + 1;
                    s.push_back(p);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (current_board[i][j] == player)
                {
                    Position trc;
                    Position sau;
                    Move k(trc, sau);
                    k.pos_start.y = j;
                    k.pos_start.x = i;
                    k.pos_end.y = j;
                    k.pos_end.x = i;
                    if (i != 0)
                    {
                        if (current_board[i - 1][j] != 1 && current_board[i - 1][j] != -1)
                        {
                            k.pos_end.x = i - 1;
                            k.pos_end.y = j;
                            s.push_back(k);
                        }
                    }
                    if (i != 4)
                    {
                        if (current_board[i + 1][j] != 1 && current_board[i + 1][j] != -1)
                        {
                            k.pos_end.x = i + 1;
                            k.pos_end.y = j;
                            s.push_back(k);
                        }
                    }
                    if (j != 0)
                    {
                        if (current_board[i][j - 1] != 1 && current_board[i][j - 1] != -1)
                        {
                            k.pos_end.x = i;
                            k.pos_end.y = j - 1;
                            s.push_back(k);
                        }
                    }
                    if (j != 4)
                    {
                        if (current_board[i][j + 1] != 1 && current_board[i][j + 1] != -1)
                        {
                            k.pos_end.x = i;
                            k.pos_end.y = j + 1;
                            s.push_back(k);
                        }
                    }
                    if (i == j + 2)
                    {
                        if (j != 0)
                        {
                            if (current_board[i - 1][j - 1] != 1 && current_board[i - 1][j - 1] != -1)
                            {
                                k.pos_end.x = i - 1;
                                k.pos_end.y = j - 1;
                                s.push_back(k);
                            }
                        }
                        if (j != 2)
                        {
                            if (current_board[i + 1][j + 1] != 1 && current_board[i + 1][j + 1] != -1)
                            {
                                k.pos_end.x = i + 1;
                                k.pos_end.y = j + 1;
                                s.push_back(k);
                            }
                        }
                    }
                    if (i == j)
                    {
                        if (j != 0)
                        {
                            if (current_board[i - 1][j - 1] != 1 && current_board[i - 1][j - 1] != -1)
                            {
                                k.pos_end.x = i - 1;
                                k.pos_end.y = j - 1;
                                s.push_back(k);
                            }
                        }
                        if (j != 4)
                        {
                            if (j != 4 && current_board[i + 1][j + 1] != 1 && current_board[i + 1][j + 1] != -1)
                            {
                                k.pos_end.x = i + 1;
                                k.pos_end.y = j + 1;
                                s.push_back(k);
                            }
                        }
                    }
                    if (i == j - 2)
                    {
                        if (i != 0)
                        {
                            if (i != 0 && current_board[i - 1][j - 1] != 1 && current_board[i - 1][j - 1] != -1)
                            {
                                k.pos_end.x = i - 1;
                                k.pos_end.y = j - 1;
                                s.push_back(k);
                            }
                        }
                        if (j != 4)
                        {
                            if (j != 4 && current_board[i + 1][j + 1] != 1 && current_board[i + 1][j + 1] != -1)
                            {
                                k.pos_end.x = i + 1;
                                k.pos_end.y = j + 1;
                                s.push_back(k);
                            }
                        }
                    }
                    if (i == -j + 2)
                    {
                        if (i != 0)
                        {
                            if (i != 0 && current_board[i - 1][j + 1] != 1 && current_board[i - 1][j + 1] != -1)
                            {
                                k.pos_end.x = i - 1;
                                k.pos_end.y = j + 1;
                                s.push_back(k);
                            }
                        }
                        if (j != 0)
                        {
                            if (j != 0 && current_board[i + 1][j - 1] != 1 && current_board[i + 1][j - 1] != -1)
                            {
                                k.pos_end.x = i + 1;
                                k.pos_end.y = j - 1;
                                s.push_back(k);
                            }
                        }
                    }
                    if (i == -j + 4)
                    {
                        if (i != 0)
                        {
                            if (i != 0 && current_board[i - 1][j + 1] != 1 && current_board[i - 1][j + 1] != -1)
                            {
                                k.pos_end.x = i - 1;
                                k.pos_end.y = j + 1;
                                s.push_back(k);
                            }
                        }
                        if (j != 0)
                        {
                            if (j != 0 && current_board[i + 1][j - 1] != 1 && current_board[i + 1][j - 1] != -1)
                            {
                                k.pos_end.x = i + 1;
                                k.pos_end.y = j - 1;
                                s.push_back(k);
                            }
                        }
                    }
                    if (i == -j + 6)
                    {
                        if (i != 2)
                        {
                            if (i != 2 && current_board[i - 1][j + 1] != 1 && current_board[i - 1][j + 1] != -1)
                            {
                                k.pos_end.x = i - 1;
                                k.pos_end.y = j + 1;
                                s.push_back(k);
                            }
                        }
                        if (j != 2)
                        {
                            if (j != 2 && current_board[i + 1][j - 1] != 1 && current_board[i + 1][j - 1] != -1)
                            {
                                k.pos_end.x = i + 1;
                                k.pos_end.y = j - 1;
                                s.push_back(k);
                            }
                        }
                    }
                }
            }
        }
    }
    return s;
}
int score(int **board, int player)
{
    int k = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (board[i][j] == player)
                k++;
        }
    }
    if (k == 16)
        return 10;
    if (k == 0)
        return -10;
    return 0;
}
int minimax(int **cboard, int **pboard, int player, int depth, bool isMax)
{
    if (depth <= 4)
    {
        int diem = score(cboard, player);
        if (diem == 10)
            return diem - depth;
        if (diem == -10)
            return diem + depth;
        if (isMax)
        {
            int best = -1000;
            Position trc;
            Position sau;
            Move cu(trc, sau);
            vector<Move> s = get_valid_moves(cboard, pboard, player);
            int n = s.size();
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    for (int k = 0; k < 5; k++)
                    {
                        if (cboard[j][k] != pboard[j][k])
                        {
                            if (cboard[j][k] == -player)
                            {
                                cu.pos_end.x = j;
                                cu.pos_end.y = k;
                            }
                            if (pboard[j][k] == -player)
                            {
                                cu.pos_start.x = j;
                                cu.pos_start.y = k;
                            }
                        }
                    }
                }
                pboard[cu.pos_end.x][cu.pos_end.y] = -player;
                pboard[cu.pos_start.x][cu.pos_start.y] = 0;
                cboard[s[i].pos_start.x][s[i].pos_start.y] = 0;
                cboard[s[i].pos_end.x][s[i].pos_end.y] = player;
                best = max(best, minimax(cboard, pboard, player, depth + 1, false));
                cboard[s[i].pos_start.x][s[i].pos_start.y] = player;
                cboard[s[i].pos_end.x][s[i].pos_end.y] = 0;
                pboard[cu.pos_end.x][cu.pos_end.y] = 0;
                pboard[cu.pos_start.x][cu.pos_start.y] = -player;
                s.clear();
            }
            return best;
        }
        else
        {
            int best = 1000;
            Position trc;
            Position sau;
            Move cu(trc, sau);
            vector<Move> s = get_valid_moves(cboard, pboard, -player);
            int n = s.size();
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    for (int k = 0; k < 5; k++)
                    {
                        if (cboard[j][k] != pboard[j][k])
                        {
                            if (cboard[j][k] == player)
                            {
                                cu.pos_end.x = j;
                                cu.pos_end.y = k;
                            }
                            if (pboard[j][k] == player)
                            {
                                cu.pos_start.x = j;
                                cu.pos_start.y = k;
                            }
                        }
                    }
                }
                pboard[cu.pos_end.x][cu.pos_end.y] = player;
                pboard[cu.pos_start.x][cu.pos_start.y] = 0;
                cboard[s[i].pos_start.x][s[i].pos_start.y] = 0;
                cboard[s[i].pos_end.x][s[i].pos_end.y] = -player;
                best = min(best, minimax(cboard, pboard, player, depth + 1, true));
                cboard[s[i].pos_start.x][s[i].pos_start.y] = -player;
                cboard[s[i].pos_end.x][s[i].pos_end.y] = 0;
                pboard[cu.pos_end.x][cu.pos_end.y] = 0;
                pboard[cu.pos_start.x][cu.pos_start.y] = player;
                s.clear();
            }
            return best;
        }
    }
    return 0;
}
void act_move(int **current_board, Move m, int player)
{
    vector<Position> a;
    a = ganh(current_board, m, player);
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        current_board[a[i].x][a[i].y] = player;
    }
    vector<Position> b;
    b = vay(current_board, m, player);
    int k = b.size();
    for (int i = 0; i < k; i++)
    {
        current_board[b[i].x][b[i].y] = player;
    }
}
Move select_move(int **current_board, int **previous_board, int player)
{
    int bestVal = -1000;
    Position trc(1, 1);
    Position sau(1, 2);
    Move bestMove(trc, sau);
    Move cu(trc, sau);
    vector<Move> s = get_valid_moves(current_board, previous_board, player);
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                if (current_board[j][k] != previous_board[j][k])
                {
                    if (current_board[j][k] == -player)
                    {
                        cu.pos_end.x = j;
                        cu.pos_end.y = k;
                    }
                    if (previous_board[j][k] == -player)
                    {
                        cu.pos_start.x = j;
                        cu.pos_start.y = k;
                    }
                }
            }
        }
        previous_board[cu.pos_end.x][cu.pos_end.y] = -player;
        previous_board[cu.pos_start.x][cu.pos_start.y] = 0;
        current_board[s[i].pos_start.x][s[i].pos_start.y] = 0;
        current_board[s[i].pos_end.x][s[i].pos_end.y] = player;
        int moveVal = minimax(current_board, previous_board, player, 0, false);
        current_board[s[i].pos_start.x][s[i].pos_start.y] = player;
        current_board[s[i].pos_end.x][s[i].pos_end.y] = 0;
        previous_board[cu.pos_end.x][cu.pos_end.y] = 0;
        previous_board[cu.pos_start.x][cu.pos_start.y] = -player;
        if (moveVal > bestVal)
        {
            bestVal = moveVal;
            bestMove.pos_start = s[i].pos_start;
            bestMove.pos_end = s[i].pos_end;
        }
    }
    int lon = 0;
    if (bestVal == 0)
    {
        int v = 0;
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                if (current_board[j][k] == player)
                    v++;
            }
        }
        int **pb = copy_board(current_board);
        for (int i = 0; i < n; i++)
        {
            pb = copy_board(current_board);
            act_move(pb, s[i], player);
            int u = 0;
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    if (pb[j][k] == player)
                        u++;
                }
            }
            if ((u - v) > lon && (u - v) >= 2)
            {
                lon = u - v;
                bestMove.pos_start = s[i].pos_start;
                bestMove.pos_end = s[i].pos_end;
            }
            else
            {
                srand(time(NULL));
                int index = rand() % n;
                bestMove = s[index];
            }
            for (int j = 0; j < 5; j++)
            {
                delete[] pb[j];
            }
            delete[] pb;
        }
    }
    return bestMove;
}

void playgame(int **board, int **pre_board, int player)
{
    if (player == 1)
    {
        Move new_move = select_move(board, pre_board, player);
        pre_board = copy_board(board);
        act_move(board, new_move, player);
        print_board(board);
    }
    if (player == -1)
    {
        int xc, yc, xm, ym;
        cout << "nhap xc " << xc << endl;
        cout << "nhap yc " << yc << endl;
        cout << "nhap xm " << xm << endl;
        cout << "nhap ym " << ym << endl;
        Position cu(xc, yc);
        Position moi(xm, ym);
        Move new_move(cu, moi);
        pre_board = copy_board(board);
        act_move(board, new_move, player);
        print_board(board);
    }
    int a;
    cin >> a;
    if (a == 1)
    {
        return playgame(board, pre_board, 1);
    }
    if (a == -1)
    {
        return playgame(board, pre_board, -1);
    }
    return;
}

void play(int first)
{
    int player;
    if (first == 1)
        player = 1;
    else
        player = -1;

    int **board = init_board();
    int **pre_board = copy_board(board);
    print_board(board);
    playgame(board, pre_board, 1);
    return;
}

int main()
{
    play(1);
    return 0;
}
