/**
 * @Time : 2022/8/31-5:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

class Solution {

public:
    /**
     * 能凑出10的因子2 5，5总是比2多，只需要考虑阶乘中的5即可
     * 如果a含有因子5，那么 a + 1, a + 2, a + 3, a + 4都不会含有因子5
     * 因此f(a)=f(a+1)=f(a+2)=f(a+3)=f(a+4) < f(a+5)
     * 所以如果阶乘中的0的数目k是存在的，对应的可取的x有5个，因此函数应该返回5
     * 如果阶乘中的0的数目k不存在，就返回0，如k = 5的时候，因为没有f(x)=5
     *
     * 每间隔5次，阶乘才会增加0，但是并非每次都只增加1个0
     * 比如f(20)的末尾有4个0，但是f(25)的末尾有6个0
     * 因为25中有两个因子5
     * 这也是导致有一些 阶乘中的0的数目k不存在的原因
     *
     * 类似地125中有3个5，625中有4个5...
     * 也就是每加5次0，就要额外加1次，每加25次，又要再额外加1次，每加125次，又又要再额外加1次...
     *
     * 假设某阶乘的末尾有k个0，一共加了n次0（数字每次加5）
     * 应该满足等式 sum(n / mod[i]) = k
     *
     * 给定一共k，检查是否能有一个n满足上式，如果不满足，说明阶乘中的0的数目k不存在
     * n的取值范围0到k，由于sum(n / mod[i]) - k随n单调递增
     * 于是从数学上可以证明上式在实数范围内有且仅有一根，但是不一定式整数
     * 可以使用二分去找根
     */
    const int mod[13] = {1,5,25,125,625,3125,15625,
                         78125,390625,1953125,9765625,48828125,244140625};
    int preimageSizeFZF(int k) {
        int lo = 0, hi = k - 1;
        while (lo <= hi){
            int mid = (lo + hi) >> 1, count = count_zero(mid);
            if(count == k) return 5;
            else if(count < k) lo = mid + 1;
            else hi = mid - 1;
        }
        return 0;
    }

    int count_zero(int n){
        int sum = 0;
        for(int i = 0; i < 13 && n >= mod[i]; i++)
            sum += n / mod[i];
        return sum;
    }
};

int main() {
    Solution s;

    cout << 0 << endl;
}