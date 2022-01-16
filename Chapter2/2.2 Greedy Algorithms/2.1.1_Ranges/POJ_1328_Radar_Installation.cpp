#include <iostream>
#include <cstring>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <cmath>

using namespace std;

int n, d;

// 雷达在x轴上所处的范围
typedef struct {
    double left, right;
}point;

point ranges[1000];

bool cmp(const point& p1, const point& p2)
{
    // 贪心，通过岛屿的位置确定雷达雷达的位置所能处的范围
    return p1.left < p2.left;
}

/**
 * @brief 
 *  以每个小岛为坐标原点建立圆，获得与x轴的左交点left和右交点right，获得了
 *  雷达在x轴上可以存在的区间，然后贪心枚举。
 *  
 *  ！！！ 雷达是要安装在海岸线上的。所以只需要判断x轴上的线段区间即可。
 * 
 * @return int 
 */
int main()
{
    memset(ranges, INT_MAX, sizeof(ranges));

    int numOfCase = 0;
    while(scanf("%d %d", &n, &d), n && d)
    {
        bool flag = false; // 判断是否有无法覆盖的点
        for(int i = 0; i < n; i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);

            if(y > d) flag = true; // 存在无法覆盖的点

            // 雷达在[left, right]区间内都可以cover到点(x, y)
            ranges[i].left = x - sqrt(d * d - y * y); // 区间范围内的左端点
            ranges[i].right = x + sqrt(d * d - y * y); // 区间范围内的右端点
        }

        if(flag)
        {
            printf("Case %d: -1\n", ++numOfCase);
            // 剪枝
            continue;
        }

        // 根据x坐标排序islands数组
        sort(ranges, ranges + n, cmp);

        // 比较x轴上的线段区间，统计雷达个数
        int ans = 1;
        double right = ranges[0].right;
        for(int i = 1; i < n; i++)
        {
            // 选择最小线段的边界
            if(ranges[i].left <= right) right = min(ranges[i].right, right);
            else
            {
                right = ranges[i].right;
                ans++;
            }
        }

        printf("Case %d: %d\n", ++numOfCase, ans);
    }

    return 0;
}
