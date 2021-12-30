#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <climits>
#include <queue>
#include <map>

using namespace std;

map<string, int> dp; // 到string的最小步数为int
int directions[4] = {-4, 4, -1, 1};

void bfs()
{
    queue<string> que;
    que.push("01234567");
    dp["01234567"] = 0;

    while(!que.empty())
    {
        string cur = que.front();
        que.pop();

        // find the position of 0
        int p = 0; 
        for(int i = 0; i < 8; i++)
        {
            if(cur[i] == '0')
            {
                p = i;
                break;
            }
        }

        // traverse through 4 directions
        for(int i = 0; i < 4; i++)
        {
            int nP = p + directions[i];
            // !!! we have to check nP and p here.
            if(nP >= 0 && nP < 8 && !(p == 3 && i == 3) && !(p == 4 && i == 2))
            {
                // 右上角不能往右移动， 左下角不能往左移动
                string next = cur;
                swap(next[p], next[nP]);
                if(dp.find(next) == dp.end())
                {
                    // map中不存在string next, 则把next加入map.
                    // 如果map中不存在，则find函数返回的迭代器和end函数返回的迭代器相同.
                    dp[next] = dp[cur] + 1;
                    que.push(next);
                }
            }
        }
    }
}

/**
 * @brief 
 * 和一般的bfs不同，改题目的bfs没有明确的移动对象，看似任意一个数都可以作为移动对象。
 * 这时我们只要抓住一个格子就行比如格子0。由于题目输入的是多个case，每个case都要运行
 * 一遍就会TLE，不过这题和图的最短路径一样(不考虑权值)，只要运用dp的思想，一次dfs就可以
 * 解决，以后每个case到解空间里去找就行了。
 * 
 * 采取逆向思维可以用广度优先搜索解决。先不考虑如何用最小步数从初始状态到最终状态，所有
 * 结果的最终状态都是(01234567), 那么反过来想只要记录最终状态到所有结果的最小步数，接下来
 * 查表即可。
 * 
 * 用map<string, int>表示(01234567)到string的最小步数int，只要当前结果还未记录就加入map，
 * 直到穷尽所有状态。另外假设p是当前状态0所在的位置，那么移动方向是上下左右后，0所在位置的坐标
 * 的变化就是+4，-4，-1，+1，需要注意的是有些位置不能向某个方向移动(如下)。
 * 
 *      0 1 2 3
 *      4 5 6 7
 *      3的位置不能向右移动到4的位置。
 * 
 * @return int 
 */
int main()
{
    // do BFS to populate map<string, int>
    bfs();

    // read line
    string s;
    while(getline(cin, s))
    {
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        cout << dp[s] << endl;
    }

    return 0;
}