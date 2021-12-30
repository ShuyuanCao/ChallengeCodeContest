#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

int M;
// map存储流星每个落点的时间最小值
int map[301][301];
// have to update the min time on each directions including itself.
int directions[5][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {0, 0}};

struct node{
    int x;
    int y;
    int t;
}s, current;

int bfs()
{

    if(map[0][0] == 0) return -1;
    if(map[0][0] == -1) return 0;

    s.x = s.y = s.t = 0;
    queue<node> que;
    que.push(s);

    while(!que.empty())
    {
        current = que.front();
        que.pop();

        // traverse through 5 directions
        for(int i = 0; i < 5; i++)
        {
            s.x = directions[i][0] + current.x;
            s.y = directions[i][1] + current.y;
            s.t = current.t + 1;

            if(s.x < 0 || s.x > 300 || s.y < 0 || s.y > 300) continue;
            if(map[s.x][s.y] == -1) return s.t; // nearest safe place
            if(map[s.x][s.y] <= s.t) continue; // no need to update current node's time, not a safe way.

            map[s.x][s.y] = s.t;
            que.push(s);
        }
    }

    return -1;
}

int main()
{
    scanf("%d", &M);
    memset(map, -1, sizeof(map));

    // construct the maze
    for(int i = 0; i < M; i++)
    {
        int x, y, t;
        scanf("%d %d %d", &x, &y, &t);

        for(int r = 0; r < 5; r++)
        {
            int nX = directions[r][0] + x;
            int nY = directions[r][1] + y;

            //update the min time on map
            if(nX >= 0 && nX <= 300 && nY >= 0 && nY <= 300)
            {
                if(map[nX][nY] == -1) map[nX][nY] = t;
                else map[nX][nY] = min(map[nX][nY], t);
            }
            else continue;
        }
    }

    // do BFS
    cout << bfs() << endl;

    return 0;
}