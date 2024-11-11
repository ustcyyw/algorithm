/**
 * @Time : 2024/11/7-10:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1914D 暴力枚举
 */
/*
  * b[j], c[k]是前缀的最大值的时候
  * 1. 如果 j != k 直接选就是
  * 2. 如果 j == k 要将其中一个换成次大值
  * 会不会出现选两个次大值更好的情况
  * b[j1] + c[k1] <= b[j1] + c[k]， b[j1] + c[k1] <= b[j] + c[k1]
  * 可以将c[k1]换成c[k] 或者 考虑将b[j1]换成b[j] 都更好
  * 以上两种方案都不行说明 如果j1 == k 且 j == k1
  * 但 j != j1 那么 j != k，两个最大值不同下标 那直接选择最大值好了
  *
  * 本题一个简单的做法是
  * 考虑a和b已经选定的情况下 c最坏也能选到第三大的数
  * 因此只要每个数组 前3大的数即可
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, a[N], b[N], c[N];
int pb1[N], pb2[N], sb1[N], sb2[N], pc1[N], pc2[N], sc1[N], sc2[N];

void init(int* nums, int* pre1, int* pre2, int* suf1, int* suf2) {
    nums[0] = nums[n + 1] = 0;
    int j1 = 1, j2 = 0;
    pre1[1] = 1;
    for(int i = 2; i <= n; i++) {
        int num = nums[i];
        if(num >= nums[j1]) j2 = j1, j1 = i;
        else if(num > nums[j2]) j2 = i;
        pre1[i] = j1, pre2[i] = j2;
    }
    j1 = n, j2 = n + 1;
    suf1[n] = n;
    for(int i = n - 1; i >= 1; i--) {
        int num = nums[i];
        if(num >= nums[j1]) j2 = j1, j1 = i;
        else if(num > nums[j2]) j2 = i;
        suf1[i] = j1, suf2[i] = j2;
    }
}

void solve() {
    init(b, pb1, pb2, sb1, sb2), init(c, pc1, pc2, sc1, sc2);
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int bl1 = pb1[i - 1], bl2 = pb2[i - 1], br1 = sb1[i + 1], br2 = sb2[i + 1];
        int cl1 = pc1[i - 1], cl2 = pc2[i - 1], cr1 = sc1[i + 1], cr2 = sc2[i + 1];
        int temp = 0;
        if(i != 1 && i != n) // 前后各取一个的情况
            temp = max(b[bl1] + c[cr1], c[cl1] + b[br1]);
        if(i >= 3) { // 左边取两个的情况
            if(bl1 != cl1) temp = max(temp, b[bl1] + c[cl1]);
            else temp = max({temp, b[bl1] + c[cl2], b[bl2] + c[cl1]});
        }
        if(i <= n - 2) { // 右边取两个的情况
            if(br1 != cr1) temp = max(temp, b[br1] + c[cr1]);
            else temp = max({temp, b[br1] + c[cr2], b[br2] + c[cr1]});
        }
        ans = max(ans, temp + a[i]);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            cin >> b[i];
        for(int i = 1; i <= n; i++)
            cin >> c[i];
        solve();
    }
};