/**
 * @Time : 2024/12/11-12:24 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1915E 1300 前缀和
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll T, n, sum[N];

bool check() {
    set<ll> st;
    st.insert(0);
    for(int i = 1; i <= n; i++) {
        if(st.count(sum[i]))
            return true;
        st.insert(sum[i]);
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            if(i % 2 == 0) num = -num;
            sum[i] = sum[i - 1] + num;
        }
        cout << (check() ? "YES" : "NO") << "\n";
    }
};