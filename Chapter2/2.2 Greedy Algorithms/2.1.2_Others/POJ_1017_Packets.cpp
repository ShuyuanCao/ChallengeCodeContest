#include <iostream>
#include <cstdio>
#include <climits>
#include <cstring>

using namespace std;
// 1*1, 2*2, 3*3, 4*4, 5*5, 6*6箱子的个数
int numA, numB, numC, numD, numE, numF;
int left1x1, left2x2;
int numOfBoxes; // 所需要的大箱子的数量；

/**
 * @brief 
 *  对于长宽为1的产品，一个6*6的大箱子可以装36个这样的产品；
 *  对于长宽为2的产品，一个6*6的大箱子可以装9个这样的产品；
 *  对于长宽为3的产品，一个6*6的大箱子可以装4个这样的产品；
 *  对于长宽4、5、6的产品，一个6*6的大箱子可以分别装一个这样的产品；
 * 
 *  我们注意到一个长宽为4、5的产品放进大箱子后，剩余的空间可以用长宽为1、2的产品来填充；一个底面积4*4（底面积16）的产品放入大箱子后，
 *  剩余的面积可以用5个2*2的产品来填充，如果2*2的产品数量不够，可以用1*1的产品来补充。那么底面积为5*5的箱子更简单了，如果装了进去，
 *  那么只能用11个1*1的产品来装填。
 *  
 *  还有长宽为3的产品，因为一个大箱子最多可以装4个长宽为3的产品，如果这种产品有五个，则需要2个大箱子；如果这种产品有9个则需要3个大箱子。
 *  得出了一个结论，长宽为3的产品的数量对4取整可以获得需要的最少的大箱子。那么最后剩下的长宽3的产品的数量可能为1、2、3个，需要分别分情况
 *  进行处理。
 * 
 * @return int 
 */
int main()
{
    while(scanf("%d%d%d%d%d%d", &numA, &numB, &numC, &numD, &numE, &numF))
    {
        if(numA == 0 && numB == 0 && numC == 0 && numD == 0 && numE == 0 && numF == 0) break;

        // 底面积为4*4、5*5、6*6的产品，有一个就需要一个大箱子，底面积为3*3的产品，需要numC / 4个大箱子；
        numOfBoxes = numF + numE + numD + (numC + 3) / 4;

        // 剩余的空间我们采用贪心的策略，先放2*2的产品，装有4*4的产品的箱子还能装下numD * 5 个 2*2的产品。
        left2x2 += numD * 5;

        // 对于3*3底面积的产品，需要分情况进行讨论
        if(numC % 4 == 3) // 装完3*3产品，还剩下的3个该产品，这三个该产品装入新的大箱子后，该箱子只剩一个2*2产品的空间。
        {
            left2x2 += 1;
        }
        else if(numC % 4 == 2) // 装完3*3产品，还剩下2个该产品，这两个产品装入新的大箱子后，该箱子只剩下3个2*2产品的空间。
        {
            left2x2 += 3;
        }
        else if(numC % 4 == 1) // 装完3*3产品，还剩下1个该产品，这个产品装入大箱子后，该箱子只剩下5个2*2的产品的空间。(3*3产品方大箱子中间)
        {
            left2x2 += 5;
        } 

        if(left2x2 < numB) // 需要用新的大箱子装剩余的2*2的产品
        {
            numOfBoxes += ((numB - left2x2 + 8) / 9); // 剩余的需要用新箱子装的2*2的产品。
        }

        // 解决了2*2的产品装箱问题，还需要解决1*1产品的装箱问题，总体积减去其他所有产品的体积就剩下的是能装的1*1的产品个数；
        left1x1 = numOfBoxes * 36 - 36 * numF - 25 * numE - 16 * numD - 9 * numC - 4 * numB;
        if(left1x1 < numA) // 需要装新的箱子
        {
            numOfBoxes += ((numA - left1x1 + 35) / 36);
        }

        printf("%d\n", numOfBoxes);
    }

    return 0;
}