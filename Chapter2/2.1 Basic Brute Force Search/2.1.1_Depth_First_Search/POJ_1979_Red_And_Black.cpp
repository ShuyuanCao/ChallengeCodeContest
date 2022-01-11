#include <iostream>

using namespace std;

char rect[20][20]; // W and H are not more than 20;
bool visited[20][20];

int W, H; // W: x direction (column); H: y direction (row);
int ans = 0;

void dfs(int x, int y) 
{   // x is row index, and y is column index
    // visited[x][y] = 1;
    rect[x][y] = '#';

    // traverse through 4 directions: up, down, right, left
    // right: (x, y + 1)
    if(y + 1 < W && rect[x][y + 1] == '.') 
    {
        ans++; // set point (x, y + 1) as visited.
        dfs(x, y + 1);
    }
    // left: (x, y - 1)
    if(y - 1 >= 0 && rect[x][y - 1] == '.')
    {
        ans++;
        dfs(x, y - 1);
    }
    // down: (x + 1, y)
    if(x + 1 < H && rect[x + 1][y] == '.')
    {
        ans++;
        dfs(x + 1, y);
    }
    // up: (x - 1, y)
    if(x - 1 >= 0 && rect[x - 1][y] == '.')
    {   
        ans++;
        dfs(x - 1, y);
    }
}

int main()
{   
    int targetX, targetY;
    char c;

    // while(scanf("%d%d\n", &W, &H) && (W || H))
    while(cin >> W >> H, W || H)
    {   // 最后输入为W，H输入为0时，退出循环
        // for each rectangle
        ans = 1;
        memset(rect, 0, sizeof(rect));
        // memset(visited, 0, sizeof(visited));

        // W is column number, and H is row number.
        for(int i = 0; i < H; i++)
        { // i is row index
            for(int j = 0; j < W; j++)
            {   // j is column index
                // read char
                // scanf("%c", &rect[i][j]);
                cin >> rect[i][j];

                if(rect[i][j] == '@')
                {
                    targetX = i;
                    targetY = j;
                }
            }
            // at the end of each row
            c = getchar();
        }

        dfs(targetX, targetY);
        // printf("%d\n", ans);
        cout << ans << endl;
    }

    return 0;
}