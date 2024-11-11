/**
 * @Time : 2024/4/23-5:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5005;
int n, k, cnt[32];

void solve() {
    if(__builtin_popcount(n) > k || k > n) {
        cout << "NO";
        return ;
    }
    cout << "YES" << "\n";
    for(int i = 0; i < 32; i++) {
        if((1 << i) & n) cnt[i]++;
    }
    int sum = __builtin_popcount(n);
    for(int i = 31; i >= 0 && k > sum; i--) {
        if(cnt[i] == 0) continue;
        // 如果当前拆分的数目不够 就将大的数拆成两个相等的小的数 这样拆分项数+1。直到当前数已经拆完了 或者项数=k
        int diff = k - sum, t = min(diff, cnt[i]);
        sum += t, cnt[i] -= t;
        cnt[i - 1] += 2 * t;
    }
    for(int i = 0, num = 1; i < 32; i++, num *= 2) {
        while(cnt[i]-- > 0)
            cout << num << " ";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    solve();
};