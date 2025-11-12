/**
 * @Time : 2024/11/15-5:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF978E 1400 很简单的分类讨论
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, w;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> w;
    int max_v = INT_MIN, min_v = INT_MAX;
    for(int i = 1, num, sum = 0; i <= n; i++) {
        cin >> num;
        sum += num;
        max_v = max(max_v, sum), min_v = min(min_v, sum);
    }
    int lo = min_v >= 0 ? 0 : -min_v;
    if(lo > w) {
        cout << 0;
        return 0;
    }
    int hi = min(w, w - max_v);
    cout << max(0, hi - lo + 1);
};