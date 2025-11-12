/**
 * @Time : 2024/5/8-1:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1141D 贪心
 */
/*
 * 相同的先和相同的匹配
 * 左边的？和右边剩下的匹配
 * 右边的？和左边剩下的匹配
 * 然后是问号和问号直接互相匹配
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, T = 1e9 + 1;
int n;
string s1, s2;

vector<vector<int>> stastic(string& s) {
    vector<vector<int>> ans(27);
    for(int i = 0; i < n; i++) {
        if(s[i] == '?') ans[26].push_back(i + 1);
        else ans[s[i] - 'a'].push_back(i + 1);
    }
    return ans;
}

void march(vector<vector<int>>& ans, vector<int>& arr1, vector<int>& arr2) {
    int m = min(arr1.size(), arr2.size());
    while(m-- > 0) {
        ans.push_back({arr1.back(), arr2.back()});
        arr1.pop_back(), arr2.pop_back();
    }
}

void solve() {
    vector<vector<int>> ans, cnt1 = stastic(s1), cnt2 = stastic(s2);
    for(int i = 0; i < 26; i++)
        march(ans, cnt1[i], cnt2[i]);
    for(int i = 0; i < 26; i++)
        march(ans, cnt1[26], cnt2[i]);
    for(int i = 0; i < 26; i++)
        march(ans, cnt1[i], cnt2[26]);
    march(ans, cnt1[26], cnt2[26]);
    cout << ans.size() << "\n";
    for(auto& p : ans)
        cout << p[0] << " " << p[1] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    cin >> s1 >> s2;
    solve();
};