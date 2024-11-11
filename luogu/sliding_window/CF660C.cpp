/**
 * @Time : 2024/4/10-10:38 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 3e5 + 5;
int n, k, nums[N];

void solve() {
    int len = 0, one = 0, l = -1, r = -1, lo = 1, hi = 1;
    while(hi <= n) {
        one += nums[hi];
        while(hi - lo + 1 > k + one) one -= nums[lo++];
        int temp = hi - lo + 1;
        if(temp > len) {
            len = temp;
            l = lo, r = hi;
        }
        hi++;
    }
    cout << len << "\n";
    for(int i = 1; i <= n; i++) {
        if(i >= l && i <= r) cout << 1 << " ";
        else cout << nums[i] << " ";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
    }
    solve();
};