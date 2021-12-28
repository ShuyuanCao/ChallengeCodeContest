#include <iostream>
#define MAX_HITS 10

using namespace std;

int W, H;
int board[20][20];
int startX, startY, minNumOfMoves;
int directions[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}}; // up, down, right, left

void dfs(int x, int y, int numOfMoves)
{
    // overceeds max num of hits, which is 10 times
    if(numOfMoves >= MAX_HITS) return;

    // traverse through 4 directions
    for(int d = 0; d < 4; d++)
    {
        // NOTE: newX, newY can be negative
        int newX = x + directions[d][0];
        int newY = y + directions[d][1];

        // if (newX, newY) on this direction is block, change direction.
        if(board[newX][newY] == 1) continue;

        // if (newX, newY) is not block, find the position where we should stop on this direction.
        while(!board[newX][newY]) 
        {
            newX += directions[d][0];
            newY += directions[d][1];
        }

        // check boundary, 0 <= x < H, 0 <= y < W.
        if(newX >= 0 && newX < H && newY >= 0 && newY < W)
        {
            // if (newX, newY) is block, change it to vacant square and continue doing dfs
            // after doing dfs, we have to restore the value of square (newX, newY)
            if(board[newX][newY] == 1) 
            {
                board[newX][newY] = 0;
                // if we throw it once, increase numOfMoves by 1
                dfs(newX - directions[d][0], newY - directions[d][1], numOfMoves + 1);
                board[newX][newY] = 1;
            }
            
            // if (newX, newY) is the goal, update minNumOfMoves
            if(board[newX][newY] == 3)
            {
                minNumOfMoves = minNumOfMoves > numOfMoves + 1? numOfMoves + 1 : minNumOfMoves;
            }
        }
    }
}

int main()
{
    char c;
    // W: width, H: height
    while(cin >> W >> H, W && H)
    {
        memset(board, -1, sizeof(board));
        for(int i = 0; i < H; i++)
        {
            for(int j = 0; j < W; j++)
            {
                cin >> board[i][j];
                if(board[i][j] == 2)
                {
                    board[i][j] = 0;
                    startX = i;
                    startY = j;
                }
            }

            // at the end of each row
            c = getchar();
        }

        minNumOfMoves = INT_MAX;
        dfs(startX, startY, 0);
 
        // print out number of moves
        if(minNumOfMoves < INT_MAX) cout << minNumOfMoves << endl;
        else cout << -1 << endl;
    }
    return 0;
}