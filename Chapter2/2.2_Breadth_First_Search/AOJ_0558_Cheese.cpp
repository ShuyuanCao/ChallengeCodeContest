#include <iostream>
#include <queue>
#include <climits>
#include <cstdio>
#include <cstring>

using namespace std;

typedef pair<int, int> P; // first := x, second := y

int H, W, N, startX, startY;
char map[1000][1001];
int steps[1000][1000];
int directions[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}}; 

int bfs(char cheese)
{
    // initialize the steps array
    for(int i = 0; i < H; i++)
    {
        fill(steps[i], steps[i] + W, INT_MAX);
    }

    steps[startX][startY] = 0;
    queue<P> que;
    que.push(P(startX, startY));

    while(!que.empty())
    {
        P p = que.front();
        que.pop();

        // start is cheese
        if(map[p.first][p.second] == cheese) 
        {
            // reset start point
            startX = p.first;
            startY = p.second;
            break;
        }

        // add the points on 4 directions into queue and update steps array
        for(int i = 0; i < 4; i++)
        {
            int newX = p.first + directions[i][0];
            int newY = p.second + directions[i][1];

            if(newX >= 0 && newX < H && newY >= 0 && newY < W && map[newX][newY] != 'X' && steps[newX][newY] == INT_MAX)
            {
                que.push(P(newX, newY));
                steps[newX][newY] = steps[p.first][p.second] + 1;
            }
        }
    }

    return steps[startX][startY];
}

/**
 * @brief 
 * 老鼠的初始体力值为1，并且只能吃硬度不大于当前体力值的奶酪，没吃一个奶酪体力值增加1。
 * 有N个奶酪，硬度分别为1~N. 说明老鼠只能按照1~N的顺序把奶酪吃完。
 * 用广度优先搜索很容易求出从起点到终点的最小步数。初始时，求起点到硬度值为1的奶酪的
 * 最小步数；接着将起点重置为此位置，继续求此位置到达硬度值为2的奶酪；以此类推。因此，
 * 需要做n次广度优先搜索，并累计其值即可。
 * 
 * 'S'为老鼠洞，'.'为空地，'X'是障碍物，1~N代表硬度为1~N的奶酪的工厂。H行W列的地图。
 * 
 * @return int 
 */
int main()
{
    scanf("%d %d %d", &H, &W, &N);
    memset(map, '-', sizeof(map));

    for(int i = 0; i < H; i++)
    {
        scanf("%s", map[i]);
    }

    for(int i = 0; i < H; i++)
    {
        for(int j = 0; j < W; j++)
        {
            if(map[i][j] == 'S')
            {
                startX = i;
                startY = j;
                break;
            }
        }
    }

    int res = 0;
    for(int i = 1; i <= N; i++)
    {
        res += bfs('0' + i);
    }

    cout << res << endl;
    
    return 0;
}