/**
 * @Time : 2024/1/23-11:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
* 考虑在i时是否重新计数 需要考虑 i + 1, i + 2，...，n这些位置的情况
* 那么不妨先从n位置开始考虑 要能让计数值达到 h[n]
* 那么其开始时间最晚是 time = t[n] - h[n] + 1
* 记前一个位置的最晚开始时间是 temp = t[n - 1] - h[n - 1] + 1
*
* 如果 time > temp 说明从time开始计数 无法兼顾到 n-1 位置的
* 在这个基础之上还有 time > t[n - 1] 那么就没有必要为了兼顾n-1位置而将计数起始时间提前
*
* 上述情况的相反情况为 time <= temp || time <= t[n - 1]
* 就是从time开始计数 可以兼顾到n-1位置
* 或者time在n-1位置的时间之前 那么在n-1这个位置时不能重置计数
* 于是需要让计数时间提前 n和n-1得一起计数
*
* 在考虑j位置的时候 向前考虑 j是否要兼顾j-1,j-2等 找到第一个不需要兼顾的位置i
* 此时的计数起点为time 那么计数时间为 total = t[j] - time + 1
* 这一部分的总花费就是 total * (total + 1) / 2
* 然后再从i为开头 继续上述过程
*/
#include<bits/stdc++.h>
using namespace std;

const int N = 105;
long long T, n, h[N], t[N];

void solve() {
    long long res = 0;
    for(int j = n; j > 0; ) {
        int i = j, time = t[i] - h[i] + 1;
        while(i > 0) {
            int temp = t[i - 1] - h[i - 1] + 1;
            if(time > temp && time > t[i - 1]) break; // i - 1 位置不再需要兼顾
            time = min(time, temp);
            i--;
        }
        res += (t[j] - time + 1) * (t[j] - time + 2) / 2;
        j = i - 1;
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> t[i];
        for(int i = 1; i <= n; i++)
            cin >> h[i];
        solve();
    }
}