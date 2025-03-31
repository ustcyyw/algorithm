/**
 * @Time : 2025/3/30-11:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF962D 1600 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15, M = 30;
int n;
map<int, ll> ans;
map<ll, set<int>> idx;

void change() {
    auto it = idx.begin();
    ll num = it->first, nm = 2 * num;
    set<int>& st = it->second;
    while(st.size() >= 2) {
        st.erase(st.begin());
        idx[nm].insert(*st.begin());
        st.erase(st.begin());
    }
    if(!st.empty()) ans[*st.begin()] = num;
    idx.erase(it);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        idx[num].insert(i);
    }
    while(!idx.empty()) {
        change();
    }
    cout << ans.size() << "\n";
    for(auto& p : ans)
        cout << p.second << " ";
}