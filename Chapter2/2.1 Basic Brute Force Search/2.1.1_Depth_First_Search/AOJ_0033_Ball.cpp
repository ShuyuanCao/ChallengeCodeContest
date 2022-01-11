#include <iostream>

using namespace std;

int ball[10];
bool flag;

void dfs(int index, int left, int right)
{
    if(flag) return;

    if(index == 10) 
    {
        flag = true;
        return;
    }

    // put the ball[index] into left side
    if(ball[index] > left) dfs(index + 1, ball[index], right);
    if(ball[index] > right) dfs(index + 1, left, ball[index]);
}

bool iteration(bool flag)
{
    int left = 0, right = 0;

    // iterate through the ball array
    for(int i = 0; i < 10; i++)
    {
        if(flag)
        {
            // !!! have to check ball[i] is less than both left and right at first
            if(ball[i] < left && ball[i] < right) 
            {
                flag = false;
            }
            else if(ball[i] < left)
            {
                // ball[i] >= right
                right = ball[i];
            }
            else if(ball[i] < right)
            {
                // ball[i] >= left
                left = ball[i];
            }
            else // (ball[i] >= left && ball[i] >= right)
            {  
                if(left > right)
                {
                    left = ball[i];
                }
                else
                {
                    right = ball[i];
                }
            }
        }
    }

    return flag;
}

int main()
{
    int lines;
    char c;

    while(cin >> lines, lines)
    {
        for(int i = 0; i < lines; i++)
        {
            memset(ball, 0, sizeof(ball));
            // have to initialize flag to be false
            flag = false;

            for(int j = 0; j < 10; j++)
            {
                cin >> ball[j];
            }

            c = getchar();

            // Solution 1: do DFS
            // dfs(0, 0, 0);

            // Solution 2: iteration
            flag = iteration(true);

            if(flag) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }

    return 0;
}