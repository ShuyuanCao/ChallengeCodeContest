#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

int N, T;

struct node
{
    /* data */
    int s, e;
};

node cows[25000];

bool cmp(node n1, node n2)
{
    if(n1.s != n2.s) return n1.s < n2.s;
    return n1.e > n2.e;
}

int calc(int ans)
{
    if(N < 1 || cows[0].s != 1) return -1;
    if(N == 1)
    {
        if(cows[0].s == 1 && cows[0].e == T) return 1;
        else return -1;
    }

    int i = 1, maxE = cows[0].e, nextMaxE = cows[0].e;

    // i 从1开始，意味着从第二头牛开始。
    while(i < N)
    {
        if(maxE == T) return ans;

        // 不断地更新maxE和nextMaxE，并统计所需cows的数量
        bool flag = false; // whether updated nextMaxE or not
        if(cows[i].s <= maxE + 1)
        {
            // 找到最大的e并赋值给nextMaxE
            while(i < N && cows[i].s <= maxE + 1)
            {
                if(cows[i].e > nextMaxE)
                {
                    nextMaxE = cows[i].e;
                    flag = true;
                }
                i++;
            }

            // 更新maxE, 用到的cow的数量 + 1
            if(flag)
            {
                maxE = nextMaxE;
                ans++;
            }
        }
        else return -1; // shift 不连续
    }

    if(maxE == T) return ans;
    else return -1;
}

/**
 * @brief 
 * 思路：
 *  简单的区间贪心。
 *  
 *  首先将牛的工作时间按照起始时间最小（第一优先级），结束时间最大的顺序（第二优先级）进行排序，
 *  然后取第n头牛时，需要满足以下条件：
 *      1. 第n头牛的s要小于等于第n-1头牛的e+1；
 *      2. 第n头牛的e要尽可能的大；
 *  
 *  之后就要考虑一些特例情况；
 * 
 *  每一个shift可以有至少一个cow；中间不能有空闲的shift。
 * 
 * @return int 
 */
int main()
{
    while(scanf("%d %d", &N, &T), N && T)
    {
        for(int i = 0; i < N; i++)
        {
            scanf("%d %d", &cows[i].s, &cows[i].e);
        }

        sort(cows, cows + N, cmp);
        printf("%d\n", calc(1));
    }

    return 0;
}