/**
 * @Time : 2025/3/17-10:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF845C 1500 差分 离散化
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, M = 63;
int T, n, ls[N], rs[N], arr[3 * N];
vector<int> pos;

int find(int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> ls[i] >> rs[i];
            pos.push_back(ls[i]), pos.push_back(rs[i]), pos.push_back(rs[i] + 1);
        }
        sort(pos.begin(), pos.end());
        pos.erase(unique(pos.begin(), pos.end()), pos.end());
        for(int i = 1; i <= n; i++) {
            int l = find(ls[i]), r = find(rs[i]);
            arr[l]++, arr[r + 1]--;
        }
        int maxV = 0, sum = 0;
        for(int i = 0; i < pos.size() + 1; i++) {
            sum += arr[i];
            maxV = max(maxV, sum);
        }
        cout << (maxV <= 2 ? "YES" : "NO");
    }
}