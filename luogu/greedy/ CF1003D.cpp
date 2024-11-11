/**
 * @Time : 2024/4/16-8:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 5005, M = 1e5 + 5;
int n, q;
vector<int> cnt;

int digit_of(int num) {
    for(int i = 0; i < 32; i++)
        if((1 << i) & num) return i;
    return -1;
}

void solve(int num) {
    vector<int> arr = cnt;
    int ans = 0;
    for(int j = 31, i = 31; i >= 0; i--) {
        int t = 1 << i;
        if((t & num) == 0) continue;
        j = i;
        while(j >= 0 && t > 0) {
            int base = 1 << j, need = t / base, val = min(need, arr[j]);
            arr[j] -= val, t -= val * base, ans += val;
            j--;
        }
        if(t == 0) num ^= 1 << i;
    }
    if(num == 0) cout << ans << "\n";
    else cout << -1 << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> q;
    cnt.assign(32, 0);
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        cnt[digit_of(num)]++;
    }
    for(int i = 1, num; i <= q; i++) {
        cin >> num;
        solve(num);
    }
};