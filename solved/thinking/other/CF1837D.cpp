/**
 * @Time : 2024/1/19-3:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 最多两个组别 前缀优先左括号（正常的匹配括号）和前缀优先右括号
  */
#include<bits/stdc++.h>
using namespace std;

long long T, n;
string s;

bool check() {
    int left = 0, right = 0;
    for(char c : s) {
        if(c == '(') left++;
        else right++;
    }
    return left == right;
}

void solve() {
    if(n % 2 == 1 || !check()) {
        cout << -1 << endl;
        return;
    }
    vector<int> ans;
    int left = 0, right = 0, f1 = 0, f2 = 0;
    for(char c : s) {
        if(c == '(') {
            left++;
            if(right) right--, left--, ans.push_back(f2);
            else {
                if(f1 == 0) f1 = f2 + 1;
                ans.push_back(f1);
            }
        } else {
            right++;
            if(left) right--, left--, ans.push_back(f1);
            else {
                if(f2 == 0) f2 = f1 + 1;
                ans.push_back(f2);
            }
        }
    }
    cout << max(f1, f2) << endl;
    for(int g : ans)
        cout << g << " ";
    cout << "" << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T--) {
        cin >> n;
        cin >> s;
        solve();
    }
}