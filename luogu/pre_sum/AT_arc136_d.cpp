/**
 * @Time : 2023/12/19-9:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 高维前缀和典型题
 */

/*
 * f(s): 表示s的十进制子集
 * 令dp[s]: 表示s的十进制子集的元素个数 (就是f(s)的元素个数)
 * 十进制子集就是指 该子集中的元素 任何一个十进制位上的数字都 <= s相应十进制位上的数字
 * 例如 582 的十进制子集中的元素有 0、1、551、72、401 等等
 * 十进制子集的元素个数 其实就是高维前缀和 每一维度用一个十进制位表示
 *
 * 本题中元素最大为N = 1e6 - 1 = 999999 第一个数是a, 那么第二个数b 要满足a + b不产生进位
 * b各个数位的限制是 <= N - a 相应十进制位上的数字
 * 也就是说第二个数是 f(N - a) 中的元素，这样满足条件的数共有dp[N - a]个
 *
 * 因此预处理出所有dp[s]后，对于某个输入a, 满足条件的数对数量就是 dp[N - a]
 * 但是注意
 * 1.如果 a在f(N - a)中，计算数对就会出现(i,i)，不合理，数量要-1
 * a在f(N - a)中即 a + a 没有发生进位
 * 2.重复计算：dp[s]是预处理出来的 对于一组满足条件的数对(i, j)，计算了两次 因此最终答案要除以2
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 - 1;
int n, nums[N + 5], dp[N + 5];
// 检查某个数和自身相加是否会进位
bool check(int a) {
    while(a > 0) {
        if(a % 10 + a % 10 >= 10) return true;
        a /= 10;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    memset(dp, 0, sizeof(dp));
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
        dp[nums[i]]++;
    }
    for(int i = 1; i <= 6; i++) {
        int p = (int)pow(10, i - 1);
        for(int s = 0; s <= N; s++)
            if((s / p) % 10) dp[s] += dp[s - p];
    }
    long long cnt = 0;
    for(int i = 0; i < n; i++) {
        cnt += dp[N - nums[i]];
        if(!check(nums[i])) cnt--;
    }
    cout << cnt / 2 << endl;
}