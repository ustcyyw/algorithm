/**
 * @Time : 2024/3/20-9:37 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 二分答案
 * 假设一共要选val个人，并且在考虑第i个人时 前面已经选了cnt人
 * 那么b[i] >= cnt, a[i] >= val - cnt - 1都满足 这个人的要求就达到了 他一定可以入选
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
ll T, n, a[N], b[N];

bool check(int val) {
    for(int i = 1, cnt = 0; i <= n; i++) {
        if(b[i] >= cnt && a[i] >= val - cnt - 1) cnt++;
        if(cnt == val) return true;
    }
    return false;
}

int solve() {
    int lo = 1, hi = n;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i] >> b[i];
        cout << solve() << "\n";
    }
};
