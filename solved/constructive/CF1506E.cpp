/**
 * @Time : 2024/11/25-9:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1506E 构造 贪心 1500
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, base[N];

void min_p(set<int> st) {
    for(int i = 1; i <= n; i++) {
        if(base[i] != 0) cout << base[i] << " ";
        else {
            cout << *st.begin() << " ";
            st.erase(st.begin());
        }
    }
    cout << "\n";
}

void max_p(set<int> st) {
    for(int i = 1, pre = -1; i <= n; i++) {
        if(base[i] != 0) {
            pre = base[i];
            cout << pre << " ";
        }
        else {
            cout << *(--st.lower_bound(pre)) << " ";
            st.erase(--st.lower_bound(pre));
        }
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        fill(base, base + n + 1, 0);
        set<int> st;
        for(int i = 1; i <= n; i++)
            st.insert(i);
        for(int i = 1, num, pre = -1; i <= n; i++) {
            cin >> num;
            if(num != pre) base[i] = num, pre = num, st.erase(num);
        }
        min_p(st), max_p(st);
    };
};