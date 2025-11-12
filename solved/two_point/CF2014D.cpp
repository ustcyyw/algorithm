/**
 * @Time : 2024/10/12-11:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2014D 双指针
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, d, k;
vector<vector<int>> lefts, rights;

void solve() {
    int cnt1 = 0, cnt2 = INT_MAX, d1 = 1, d2 = 1;
    set<int> set;
    for(int day = 1, i = 0, j = 0; day + d - 1 <= n; day++) {
        while(i < k && lefts[i][0] <= day + d - 1)
            set.insert(lefts[i++][1]);
        while(j < k && rights[j][0] < day)
            set.erase(rights[j++][1]);
        if(set.size() > cnt1) cnt1 = set.size(), d1 = day;
        if(set.size() < cnt2) cnt2 = set.size(), d2 = day;
    }
    cout << d1 << " " << d2 << "\n";
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> d >> k;
        lefts = {}, rights = {};
        for(int i = 1, l, r; i <= k; i++) {
            cin >> l >> r;
            lefts.push_back({l, i}), rights.push_back({r, i});
        }
        sort(lefts.begin(), lefts.end());
        sort(rights.begin(), rights.end());
        solve();
    }
};