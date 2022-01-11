#include <iostream>

using namespace std;

char garden[100][100];
int W, H, res;
int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // right, left, 

void dfs(int x, int y, const char c)
{
    garden[x][y] = '.';

    // traverse through 4 directions
    for(int i = 0; i < 4; i++)
    {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];

        // if (newX, newY) is within boundary and it is has the same 
        // value with (x, y), continue doing DFS.
        if(newX >= 0 && newX < H && newY >= 0 && newY < W && c == garden[newX][newY]) 
        {
            dfs(newX, newY, c);
        }
    }
}


int main()
{
    char c;

    while(cin >> H >> W, W && H)
    {
        memset(garden, '.', sizeof(garden));

        // W: width, H: height
        for(int i = 0; i < H; i++)
        {
            for(int j = 0; j < W; j++)
            {
                cin >> garden[i][j];
            }

            c = getchar();
        }

        for(int i = 0; i < H; i++)
        {
            for(int j = 0; j < W; j++)
            {
                if(garden[i][j] != '.')
                {
                    // mark those squares connected with garden[i][j] as '.', which means visited.
                    dfs(i, j, garden[i][j]);
                    res++;
                }
            }
        }

        cout << res << endl;
    }

    return 0;
}