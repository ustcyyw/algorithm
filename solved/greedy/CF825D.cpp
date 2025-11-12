/**
 * @Time : 2025/3/4-8:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF825D 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, P = 13331;
ll n, k, cnt[26];
string s, t;
vector<int> arr;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s >> t;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] != '?') cnt[s[i] - 'a']++;
        else arr.push_back(i);
    }
    for(int i = 0, m = t.size(); i < m && !arr.empty(); i = (i + 1) % m) {
        if(cnt[t[i] - 'a']) cnt[t[i] - 'a']--;
        else {
            s[arr.back()] = t[i];
            arr.pop_back();
        }
    }
    cout << s;
}