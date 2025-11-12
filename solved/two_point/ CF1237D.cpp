/**
 * @Time : 2024/6/13-5:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1237D 双指针 + set
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 3e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, max_v, min_v, a[N], ans[N / 3];

void solve() {
    if(max_v <= min_v * 2) {
        fill(ans, ans + n, -1);
        return;
    }
    for(int i = n, j = 0; i < 3 * n; i++, j = (j + 1) % n)
        a[i] = a[j];
    multiset<int> st;
    for(int i = 0, j = 0, m = 3 * n; i < n; i++) {
        while(j < m && (st.empty() || *st.rbegin() <= a[j] * 2)) {
            st.insert(a[j]);
            j++;
        }
        ans[i] = j - i;
        st.erase(st.find(a[i]));
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    max_v = 0, min_v = INT_MAX;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        max_v = max(max_v, a[i]), min_v = min(min_v, a[i]);
    }
    solve();
    for(int i = 0; i < n; i++)
        cout << ans[i] << " ";
};