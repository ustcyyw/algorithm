/**
 * @Time : 2024/5/11-11:17 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1157E 贪心 + set
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, a[N];
multiset<int> st;

void solve() {
    for(int i = 1; i <= n; i++) {
        int need = n - a[i];
        auto it = st.lower_bound(need);
        if(it == st.end())
            it = st.begin();
        cout << (a[i] + *it) % n << " ";
        st.erase(it);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        st.insert(num);
    }
    solve();
};