/**
 * @Time : 2024/7/12-11:17 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1551C 枚举 贪心
 */
 /*
  * 暴力枚举占绝大多数的字母
  * 具体计算时 贪心
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 3e5 + 10, mod = 1e9 + 7;
typedef long long ll;
int T, n;
string s;
vector<vector<int>> infos;

int cal(int j) {
    vector<int> arr;
    for(auto& temp : infos)
        arr.push_back(temp[j] - (temp[5] - temp[j]));
    sort(arr.begin(), arr.end());
    for(int i = n - 1, sum = 0; i >= 0; i--) {
        sum += arr[i];
        if(sum <= 0) return n - (i + 1);
    }
    return n;
}

void solve() {
    int ans = 0;
    for(int i = 0; i < 5; i++)
        ans = max(ans, cal(i));
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        infos = {};
        for(int i = 1; i <= n; i++) {
            cin >> s;
            vector<int> temp(6, 0);
            for(char c : s)
                temp[c - 'a']++;
            temp[5] = s.size();
            infos.push_back(temp);
        }
        solve();
    }
};