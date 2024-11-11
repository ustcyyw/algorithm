/**
 * @Time : 2024/7/1-4:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1367C 贪心 + 模拟
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 55;
typedef long long ll;
int T, n, k;
string s;

int has_one(int lo) {
    for (int i = lo + 1; i <= lo + k && i < n; i++)
        if (s[i] == '1') return i;
    return -1;
}

void solve() {
    for (int i = 0; i < n;) {
        int t = has_one(i);
        if (t != -1) i = t;
        else {
            if (s[i] == '0') s[i] = '2';
            if (i + k + 1 < n && s[i + k + 1] == '0') s[i + k + 1] = '2';
            i = i + k + 1;
        }
    }
    vector<int> arr;
    for (int i = 0; i < n; i++) {
        if (s[i] != '0') arr.push_back(i);
    }
    int cnt = 0;
    for (int i = 0, m = arr.size(); i < m; i++) {
        if ((i == 0 || arr[i] - arr[i - 1] > k)
            && (i == m - 1 || arr[i + 1] - arr[i] > k)
            && s[arr[i]] == '2')
            cnt++;
    }
    cout << cnt << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k >> s;
        solve();
    }
};