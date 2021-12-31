#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <climits>

using namespace std;

int num[10];
int cnt;

int getDiff()
{
    int secStart = cnt/2;
    if((num[0] == 0 || num[secStart] == 0) && cnt > 2) return -1; 

    int m = 0, n = 0;
    // setup first num
    for(int i = 0; i < secStart; i++)
    {
        m = m * 10 + num[i]; 
    }

    // setup second num
    for(int j = secStart; j < cnt; j++)
    {
        n = n * 10 + num[j];
    }

    return abs(n - m);
}

int solve()
{
    int minDiff = INT_MAX;

    do
    {
        int diff = getDiff();

        if(diff != -1)
            minDiff = min(minDiff, diff);
    } while (next_permutation(num, num + cnt));
    
    return minDiff;
}

int main()
{
    int lines;
    // setup the num array
    scanf("%d", &lines);
    getchar();

    for(int i = 0; i < lines; i++)
    {
        // enough buffer for input, otherwise "gets" function will not work
        char input[100];
        gets(input);
        int len = strlen(input);
        cnt = 0;

        for(int j = 0; j < len; j++)
        {
            if(isdigit(input[j])) 
                num[cnt++] = input[j] - '0';
        }

        sort(num, num + cnt);
        cout << solve() << endl;
    }

    return 0;
}