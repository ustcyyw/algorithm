/**
 * @Time : 2024/4/22-5:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, m, r, a[N], mp[N];
char t;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> m;
    int lo = 0, hi = 1;
    for(int i = 1, id; i <= m; i++) {
        cin >> t;
        cin >> id;
        if(t == '?') {
            int pos = mp[id];
            cout << min(hi - pos - 1, pos - lo - 1) << "\n";
        } else if(t == 'R') mp[id] = hi++;
        else mp[id] = lo--;
    }
};