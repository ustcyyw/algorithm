/**
 * @Time : 2025/4/29-11:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1051A 1200 模拟 分类讨论
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e3+ 5, mod = 998244353;
ll T;
vector<int> lower, upper, nums;
string s;

void change(vector<int>& arr1, vector<int>& arr2, char c) {
    int idx = arr1.size() > 1 ? arr1[0] : arr2[0];
    s[idx] = c;
}

void solve() {
    int n = s.size();
    for(int i = 0; i < n; i++) {
        char c = s[i];
        if(c >= 'a' && c <= 'z') lower.push_back(i);
        else if(c >= 'A' && c <= 'Z') upper.push_back(i);
        else nums.push_back(i);
    }
    if(!lower.empty() && !upper.empty() && !nums.empty()) return;
    // 只有一种字符的情况
    if(lower.size() == n) s[0] = 'A', s[1] = '0';
    else if(upper.size() == n) s[0] = 'a', s[1] = '0';
    else if(nums.size() == n) s[0] = 'a', s[1] = 'A';
    else if(lower.empty()) change(upper, nums, 'a');
    else if(upper.empty())change(lower, nums, 'A');
    else change(lower, upper, '0');
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> s;
        lower = {}, upper = {}, nums = {};
        solve();
        cout << s << "\n";
    }
}