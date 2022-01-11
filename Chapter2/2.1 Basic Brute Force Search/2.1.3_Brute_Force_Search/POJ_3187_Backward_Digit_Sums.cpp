#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

int n, target, ans[11];
bool used[11];
int triangle[11][11];

void init()
{
    memset(triangle, 0, sizeof(triangle));

    triangle[1][1] = triangle[2][1] = triangle[2][2] = 1;
    // n层正杨辉三角
    for(int i = 3; i <= n; i++)
    {
        triangle[i][1] = triangle[i][i] = 1;
        for(int j = 2; j < i; j++)
        {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
    }
}

bool dfs(int depth, int sum)
{
    if(depth == n + 1) return sum == target;
    if(sum > target) return false;

    // get all permutations
    for(int i = 1; i <= n; i++)
    {
        if(!used[i])
        {
            ans[depth] = i;
            
            used[i] = true;
            if(dfs(depth + 1, sum + i * triangle[n][depth])) return true;
            used[i] = false;
        }
    }

    return false;
}

/**
 * @brief 
 * Solution 1:
 *      1. 先求1-n的数字的所有的全排列；
 *      2. 对于每一种排列，计算倒置的杨辉三角的最后一行的值是否等于给定的sum值；
 * 
 *      1 2 1
 *       1 1
 *        1
 * Solution 2:
 *      通过倒置的杨辉三角的每一行的值作为系数，乘以对应位置上的1-n的值，来计算sum，
 *      看是否等于给定的值。
 * 
 * @return int 
 */
int main()
{
    // Solution 1
    scanf("%d %d", &n, &target);
    // 初始化正杨辉三角
    init();

    memset(used, 0, sizeof(used));
    memset(ans, 0, sizeof(ans));

    // search for all the permuations of 1~n.
    if(dfs(1, 0))
    {
        printf("%d", ans[1]);
        for(int i = 2; i <= n; i++) printf(" %d", ans[i]);
        printf("\n");
    }

    return 0;
}