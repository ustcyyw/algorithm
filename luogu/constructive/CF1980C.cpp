/**
 * @Time : 2024/12/3-11:34 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1980C 1300 构造算法
 */
 /*
  * d中最后一个元素d[m]很重要 如果它没有出现在b中，无论怎么操作都得不到b
  * 而其它d中都元素即便不存在于b中 也可以总是将那些操作放在d[m]对应的b中的位置上
  * 最后一次操作用d[m]覆盖就好
  * 其它就只需要检查 b[i] != a[i] 的值，在d[i]中是否有足够的值去替换即可
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, m, a[N], b[N], d[N];

bool solve() {
    set<int> st;
    map<int, int> diff;
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] != b[i]) diff[b[i]]++, cnt++;
        st.insert(b[i]);
    }
    if(!st.count(d[m])) return false;
    for(int i = 1; i <= m; i++) {
        if(diff[d[i]] > 0)
            diff[d[i]]--, cnt--;
    }
    return cnt == 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            cin >> b[i];
        cin >> m;
        for(int i = 1; i <= m; i++)
            cin >> d[i];
        cout << (solve() ? "YES" : "NO") << "\n";
    };
};