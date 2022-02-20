#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

int n;
priority_queue<double> que;// 默认是大顶堆

/**
 * @brief 求合并成一个该生物后的最小重量。
 * 
 * 思路：
 *      m1 + m2 >= 2 * sqrt(m1 * m2)
 *      
 *      所以每次取大的去合并，能变小。
 *      直接用优先级队列就好。
 * 
 * @return int 
 */
int main()
{
    while(scanf("%d", &n), n)
    {
        double tmp;
        for(int i = 1; i <= n; i++)
        {
            scanf("%lf", &tmp);
            que.push(tmp);
        }
        
        while(!que.empty())
        {
            double m1 = que.top();
            que.pop();

            if(que.empty())
            {
                printf("%0.3lf", m1);
                break;
            }

            double m2 = que.top();
            que.pop();

            double m3;
            m3 = 2 * sqrt(m1 * m2);
            que.push(m3);
        }
    }

    return 0;
}