#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

int N;

struct Node
{
    int start, end, pos;

    // priority queue 会使用这个重载的小于号排序Node
    friend bool operator<(Node a, Node b)
    {
        if(a.end == b.end) return a.start < b.start;
        // 最小值优先
        return a.end > b.end;
    }
};

Node cows[50000];
int orders[50000];
priority_queue<Node> que;

bool cmp(const Node s1, const Node s2)
{
    // 先按照开始时间有小到大排序
    if(s1.start != s2.start)
    {
        return s1.start < s2.start;
    }
    else 
    {
        return s1.end < s2.end;
    }
}

/**
 * @brief 
 * 思路：
 *   区间贪心。
 *   把尽量多的牛放在一个牛棚里，这样就可以使用到的棚子数量最少。
 *   只要任意两头牛的挤奶时间不重合，就可以放在一个棚子里。因为N值比较大，先标记好
 *   每一头牛的起始坐标，然后按照起始时间从小到大进行排序，然后依次从前往后遍历每一头牛。
 *   
 *   这里需要用一个优先级队列来维护，以结束时间大小来维护，每次将一头牛与队列首的牛进行
 *   比较，如果满足它的起始时间大于队列首的那头牛的结束时间，这两头牛就可以使用同一个
 *   机器，否则就新加一个机器。这里需要注意牛的入队和出队。
 * 
 * @return int 
 */
int main()
{
    memset(cows, -1, sizeof(cows));
    while(scanf("%d", &N), N)
    {
        for(int i = 0; i < N; i++)
        {
            scanf("%d %d", &cows[i].start, &cows[i].end);
            cows[i].pos = i;
        }

        sort(cows, cows + N, cmp);
        // 按照起始时间排过序的牛的挤奶时间
        que.push(cows[0]);
        orders[cows[0].pos] = 1;

        for(int i = 1; i < N; i++)
        {
            if(cows[i].start > que.top().end)
            {
                // cows[i]和que.top()这头牛可以在一个stall
                orders[cows[i].pos] = orders[que.top().pos];
                que.pop();
                // 把cow[i]加入que
                que.push(cows[i]);
            }
            else
            {
                // 把cows[i]加入que
                que.push(cows[i]);
                orders[cows[i].pos] = que.size();
            }
        }
        // que的size就是所需要的stall数量
        printf("%ld\n", que.size());

        for(int i = 0; i < N; i++)
        {
            printf("%d\n", orders[i]);
        }
    }

    return 0;
}