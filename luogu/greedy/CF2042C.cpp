/**
 * @Time : 2024/12/27-10:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2042C 1800 贪心 前缀和
 */
/*
  * 假设分成了cnt段 以分成四段为例子
  * 用sum表示鱼相对数量的前缀和，bob的鱼+1，alice的鱼-1
  * 0 * sum[i1] + 1 * (sum[i2] - sum[i1]) + 2 * (sum[i3] - sum[i2]) + 3 * (sum[i4] - sum[i3])
  * sum2 - sum1 + 2sum3 - 2sum2 + 3sum4 - 3sum3
  * = 3sum4 - sum1 - sum2 - sum3
  *
  * 分成cnt段 (cnt - 1) * sum[cnt] - (sum1 + sum2 + sum3 + sum[cnt-1])
  * 也是说分成固定段数时 最后一段的值固定 前面应该选最小的cnt - 1个前缀和
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5;
int T, n, k;
string s;

int solve() {
    priority_queue<int, vector<int>, greater<>> pq;
    int preSum = 0;
    for(char c : s) {
        if(c == '1') preSum++;
        else preSum--;
        pq.push(preSum);
    }
    for(ll cnt = 1, sum = 0; cnt <= n; cnt++) {
        ll temp = (cnt - 1) * preSum - sum;
        if(temp >= k) return cnt;
        sum += pq.top(), pq.pop();
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> k >> s;
        cout << solve() << "\n";
    }
};