/**
 * @Time : 2023/12/4-11:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 一次操作 a可以越过1个b，但是会多增加一个b
 * 如果先换后面的ab 会创造出更多的b，那么前面的a需要越过的b就会越多 不好
 * 应该从前面开始进行操作
 *
 * 假设前面有 x个a 现在有y个b
 * 第x个a和y个b操作 需要y次操作
 * 之后会有x-1个a和2y个b，第x-1个a和2y个b操作，需要2y次操作
 * 之后会有x-2个a和4y个b，第x-2个a和4y个b操作，需要4y次操作
 * ...
 * 第一个a和 2 ^ (x - 1) * 个b
 * 所以操作次数是 y + 2y + 4y + ... 2 ^ (x - 1) * y = y * (1 + 2 + 4 + 2 ^ (x - 1))
 * 所以需要预处理2的幂次 并且要预处理幂次的前缀和
 *
 * 从左到右 寻找连续的a和连续的b 执行上述操作
 * 将a换到b后面 并且注意连续的a还要计算上之前交换过来的a的数量 可以使用双指针
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5, mod = 1e9 + 7;
long long aux[N], sum[N + 1];
int init = []() -> int{
    aux[0] = 1;
    for(int i = 1; i < N; i++) {
        aux[i] = aux[i - 1] * 2 % mod;
        sum[i] = (sum[i - 1] + aux[i - 1]) % mod;
    }
    return 0;
}();

string s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s;
    int n = s.size();
    long long res = 0;
    for(int i = 0, j = 0, ca = 0; i < n; ) {
        j = i;
        while(j < n && s[j] == 'a') j++;
        ca += j - i; // 注意前面交换过来的a和当前这系列a要合到一块
        i = j;
        while(j < n && s[j] == 'b') j++;
        int cb = j - i;
        i = j;
        if(ca > 0) res = (res + (sum[ca] * cb) % mod) % mod;
    }
    cout << res << endl;
}