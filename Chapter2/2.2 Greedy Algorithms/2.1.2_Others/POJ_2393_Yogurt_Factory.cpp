#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cmath>

typedef long long ll;
using namespace std;

int cost[10010], deliveries[10010];
int S, N;

int main()
{
    ll sum = 0;
    while(scanf("%d%d", &N, &S), N && S)
    {
        for(int i = 0; i < N; i++) scanf("%d %d", &cost[i], &deliveries[i]);

        // 后一个的cost是基于前一个cost的大小
        for(int i = 1; i < N; i++)
        {
            cost[i] = min(cost[i - 1] + S, cost[i]);
        }

        for(int i = 0; i < N; i++)
        {
            sum += cost[i] * deliveries[i];
        }

        printf("%lld\n", sum);
    }
    return 0;
}