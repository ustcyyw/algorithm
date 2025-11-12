/**
 * @Time : 2023/8/29-9:46 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e5 + 5;
ll l, n1, n2;
long a[N][2], b[N][2];

ll solve() {
    ll res = 0, lo1 = 0, lo2 = 0;
    for(int i = 0, j = 0; i < n1 || j < n2; ) {
        ll hi1 = i == n1 ? l : lo1 + a[i][1] - 1;
        ll hi2 = j == n2 ? l : lo2 + b[j][1] - 1;
        if(i < n1 && j < n2 && a[i][0] == b[j][0])
            res += min(hi1, hi2) - max(lo1, lo2) + 1;
        if(hi1 >= hi2) lo2 = hi2 + 1, j++;
        else lo1 = hi1 + 1, i++;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> l >> n1 >> n2;
    for(int i = 0; i < n1; i++)
        cin >> a[i][0] >> a[i][1];
    for(int i = 0; i < n2; i++)
        cin >> b[i][0] >> b[i][1];
    cout << solve() << endl;
}