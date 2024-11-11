/**
 * @Time : 2024/7/12-12:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1551B2 构造 + 贪心
 */
/*
 * 出现次数超过k的数字 每个分组都能放一个
 * 不足k的就只能统筹起来看 看看还能k个一组分多少轮
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 3e5 + 10, mod = 1e9 + 7;
typedef long long ll;
int T, n, k, ans[N], need;
map<int, vector<int>> mp;

void color(int& c, vector<int>& arr) {
    for(int i = 0; i < min((int)arr.size(), k) && need > 0; i++, need--) {
        ans[arr[i]] = c++;
        if(c > k) c = 1;
    }
}

void solve() {
    vector<vector<int>> arr;
    for(auto& p : mp)
        arr.push_back({p.first, (int)p.second.size()});
    sort(arr.begin(), arr.end(), [](auto &a, auto &b)-> bool {
        return a[1] > b[1];
    });
    need = INT_MAX;
    int c = 1, sum = 0;
    for(auto& p : arr) {
        if(p[1] >= k) {
            sum += p[1];
            color(c, mp[p[0]]);
        } else break;
    }
    need = (n - sum) / k * k;
    for(auto& p : arr) {
        if(p[1] >= k) continue;
        color(c, mp[p[0]]);
    }
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        mp = {};
        fill(ans, ans + n + 1, 0);
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            mp[num].push_back(i);
        }
        solve();
    }
};