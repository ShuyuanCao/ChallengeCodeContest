#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <algorithm>

using namespace std;

struct Node {
    int num, value; // 硬币的个数和面值
} coins[21];

int use[21];

int cmp(Node a, Node b)
{
    return a.value < b.value; // 按照面值升序排序
}

/**
 * @brief 
 * 贪心策略：
 *      贪心的策略是使得硬币的损耗最低，利用率最高；
 *      所以对于大于面值C的硬币直接付，有多少付多少，然后剩下的面值从大到小排序，首先优先使用大面值，
 *      但是不要超过C，能取多少取多少，小的面值可以组成大的面值，因为是倍数关系；
 *      再从小到大取，补充之前取到的面值，重复。这样可以保证硬币的利用率最大化。
 * 
 * 具体方法：
 *      将硬币从小到大排序，大于或者等于C的硬币直接支付，然后将不能直接支付的先从大到小凑到接近C，再
 *      从小到大向上加，如果能达到就记录并开始下一轮，如果不能就退出。需要注意的是，硬币无法拆分，因此
 *      只能多给不能少给。
 * 
 * @return int 
 */
int main()
{
    int n, c, count = 0;

    while(scanf("%d%d", &n, &c), n && c)
    {
        for(int i = 1; i <= n; i++)
        {
            scanf("%d%d", &coins[i].value, &coins[i].num);
        }

        // 根据面值从小到大把数组coins元素进行排序
        sort(coins + 1, coins + 1 + n, cmp);

        for(int i = 1; i <= n; i++)
        {
            if(coins[i].value >= c) // 面值>=c的话，直接支付
            {
                count += coins[i].num;
                coins[i].num = 0; // 清零
            }
        }

        while(true)
        {
            bool flag = false;
            int sum = c;
            // 每次重置used数组的元素值为0
            memset(use, 0, sizeof(use));

            // 对币值从大到小凑到接近c
            for(int i = n; i > 0; i--)
            {
                if(coins[i].num > 0)
                {
                    // 记录使用的次数
                    use[i] = min(coins[i].num, sum / coins[i].value);
                    // 记录凑到的值
                    sum -= use[i] * coins[i].value;

                    if(sum == 0)
                    {
                        flag = true; // 记录是否已经凑够c
                        break;
                    }
                }
            }

            // 对币值从小到大凑到c, 用小的硬币面额去凑到c
            if(sum > 0)
            {
                for(int i = 1; i <= n; i++)
                {
                    if(coins[i].num > use[i]) // 如果该币种的硬币未被用光
                    {
                        // 一直尝试用该币种i去凑c
                        while(use[i] < coins[i].num)
                        {
                            sum -= coins[i].value; // 记录凑到的值
                            use[i]++; // 记录使用的次数
                            if(sum <= 0)
                            {
                                flag = true; // 记录是否已经凑够c
                                break;  // 跳出while循环
                            }
                        }
                    }

                    if(flag) break; // 跳出for循环
                }
            }

            if(!flag) break; // 如果凑不到c的话，就跳出最外层的while循环

            int minn = INT_MAX;
            // 记录最小的支付数, 即可以支付的周的数量
            for(int i = 1; i <= n; i++)
            {
                if(use[i] > 0)
                {
                    minn = min(minn, coins[i].num / use[i]);
                }
            }
            
            // 从硬币总数量中减去支付数
            for(int i = 1; i <= n; i++)
            {
                coins[i].num -= minn * use[i];
            }

            count += minn;
        }

        printf("%d\n", count);
    }

    return 0;
}