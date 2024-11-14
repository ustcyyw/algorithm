/**
 * @Time : 2024/11/13-11:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1932D 贪心 模拟 1400
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, m, nums[N];
char type;
string c;
vector<string> ans;
vector<int> king;
map<char, vector<int>> mp;

void add(vector<int>& arr, char c) {
    for(int i = 0; i + 1 < arr.size(); i += 2) {
        ans.push_back(to_string(arr[i]) + c);
        ans.push_back(to_string(arr[i + 1]) + c);
    }
}

bool solve() {
    sort(king.begin(), king.end());
    for(auto& p : mp) {
        vector<int>& arr = p.second;
        sort(arr.begin(), arr.end());
        if(arr.size() % 2 == 1 && king.empty()) return false;
        add(arr, p.first);
        if(arr.size() % 2 == 1) {
            ans.push_back(to_string(arr.back()) + p.first);
            ans.push_back(to_string(king.back()) + type);
            king.pop_back();
        }
    }
    add(king, type);
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> type;
        mp = {}, king = {}, ans = {};
        for(int i = 1; i <= 2 * n; i++) {
            cin >> c;
            if(c[1] != type) mp[c[1]].push_back(c[0] - '0');
            else king.push_back(c[0] - '0');
        }
        if(!solve()) cout << "IMPOSSIBLE\n";
        else {
            for(int i = 0; i < 2 * n; i += 2)
                cout << ans[i] << " " << ans[i + 1] << "\n";
        }
    }
};