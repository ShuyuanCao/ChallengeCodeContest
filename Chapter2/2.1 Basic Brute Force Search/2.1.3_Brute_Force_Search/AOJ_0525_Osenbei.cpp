#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

int r, c, ans;
int board[10][10000];

void calculate()
{
    int totalColSum = 0;
    // 查看每一列的情况，如果正面朝上比较多那么就不用翻，少就翻
    for(int i = 0; i < c; i++)
    {
        int sum = 0;
        for(int j = 0; j < r; j++)
        {
            sum += board[j][i];
        }
        // 取每一列的最大值
        sum = max(sum, r - sum);
        // 计算素有列的和
        totalColSum += sum;
    }

    ans = max(totalColSum, ans);
    return;
}

void flip(int depth)
{
    // flip the depth row
    for(int i = 0; i < c; i++)
    {
        board[depth - 1][i] = 1 - board[depth - 1][i];
    }
}

void dfs(int depth)
{
    if(depth == r + 1) calculate();
    else
    {
        dfs(depth + 1); // 不翻转该行
        flip(depth); // 翻转改行
        dfs(depth + 1); // 翻转后继续dfs
    }
}

/**
 * @brief 
 * 思路：
 *      行的规模较小，列的规模较大；
 * 
 *      对行和列分别进行处理：
 *          1. 先对行进行深度优先搜索，遍历对行翻转处理后的所有可能；
 *          2. 对行翻转后的每一种可能进行处理，遍历每一列：若该列为正多反少，则不翻转，反之翻转；
 *          3. 计算行列翻转后的每一种可能的正面朝上的烧饼的数量，找到最大值；
 * 
 * @return int 
 */
int main()
{
    while(scanf("%d %d", &r, &c), r && c)
    {
        // initialize board
        for(int i = 0; i < r; i++)
        {
            for(int j = 0; j < c; j++)
            {
                scanf("%d", &board[i][j]);
            }
        }

        // dfs
        dfs(1);
        printf("%d\n", ans);
    }

    return 0;
}