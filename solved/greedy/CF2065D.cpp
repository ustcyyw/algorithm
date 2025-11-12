/**
 * @Time : 2025/2/12-8:47 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2065D 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll T, n, m, sum[N];
vector<int> aux, b;
vector<vector<int>> arr;

void solve() {
    sort(aux.begin(), aux.end(), [](int& i, int& j) -> bool {
        return sum[i] > sum[j];
    });
    b = { };
    for(int id : aux) {
        for(int num : arr[id])
            b.push_back(num);
    }
    ll ans = 0, cur = 0;
    for(int num : b) {
        cur += num;
        ans += cur;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T--) {
        cin >> n >> m;
        fill(sum, sum + n + 1, 0);
        aux = {}, arr = {};
        for(int i = 0; i < n; i++) {
            vector<int> temp;
            aux.push_back(i);
            for(int j = 1, num; j <= m; j++) {
                cin >> num;
                sum[i] += num, temp.push_back(num);
            }
            arr.push_back(temp);
        }
        solve();
    }
};