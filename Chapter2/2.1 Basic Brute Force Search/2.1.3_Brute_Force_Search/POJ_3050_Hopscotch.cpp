#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <climits>

using namespace std;

bool visited[1000000];
int map[5][5], ans;
int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void dfs(int x, int y, int len, int val)
{
    if(len == 6)
    {
        if(!visited[val])
        {
            visited[val] = true;
            ans++;
        }
        return;
    }

    // traverse through 4 directions
    for(int i = 0; i < 4; i++)
    {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];

        if(nx >= 0 && nx < 5 && ny >= 0 && ny < 5)
        {
            dfs(nx, ny, len + 1, val * 10 + map[nx][ny]);
        }
    }

    return;
}

int main()
{
    char c;

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            scanf("%d", &map[i][j]);
        }
    }

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            dfs(i, j, 1, map[i][j]);
        }
    }

    printf("%d\n", ans);
    return 0;
}