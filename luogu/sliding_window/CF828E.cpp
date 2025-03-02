/**
 * @Time : 2025/3/2-3:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF828E 1900 滑动窗口 数学
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, mod = 1e9 + 7;
ll T, n, k, m, nums[N];
set<int> st;
map<int, int> mp;

void init(int num) {
    for(int i = 2; i <= sqrt(num); i++) {
        while(num % i == 0) {
            st.insert(i), mp[i]++;
            num /= i;
        }
    }
    if(num > 1) st.insert(num), mp[num]++;
}

void solve() {
    ll ans = 0;
    map<int, int> cmp;
    for(int i = 1, j = 1, cnt = 0; i <= n; i++) {
        while(j <= n && cnt < m) {
            int temp = nums[j];
            for(int num : st) {
                while(temp % num == 0) {
                    cmp[num]++;
                    if(cmp[num] == mp[num]) cnt++;
                    temp /= num;
                }
            }
            j++;
        }
        if(cnt == m) ans += n - (j - 1) + 1;
        else break;
        int temp = nums[i];
        for(int num : st) {
            while(temp % num == 0) {
                cmp[num]--;
                if(cmp[num] == mp[num] - 1) cnt--;
                temp /= num;
            }
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    if(k == 1) {
        cout << n * (n + 1) / 2 << "\n";
        return 0;
    }
    init(k);
    m = mp.size();
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    solve();
}