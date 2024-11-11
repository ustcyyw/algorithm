/**
 * @Time : 2024/9/3-10:24 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1790D 贪心 数据结构
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 9;
typedef long long ll;
int T, n;
multiset<int> mst;

void solve() {
    int cnt = 0;
    while(!mst.empty()) {
        cnt++;
        int a = *mst.begin();
        while(mst.count(a)) {
            mst.erase(mst.find(a));
            a++;
        }
    }
    cout << cnt << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            mst.insert(num);
        }
        solve();
    }
};