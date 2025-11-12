/**
 * @Time : 2024/4/8-9:12 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 左括号只能变成左括号 右括号可以变右括号
 * 只要左右是匹配的 就可以通过操作变得完全匹配
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 3000 + 5, T = 205;
string s;
unordered_set<char> lb = {'<', '{', '[', '('};
unordered_map<char, char> mp = {{'>', '<'}, {']', '['}, {'}', '{'}, {')', '('}};

string solve() {
    int cnt = 0;
    stack<char> stack;
    for(char c : s) {
        if(lb.count(c)) stack.push(c);
        else {
            if(stack.empty()) return "Impossible";
            if(stack.top() != mp[c]) cnt++;
            stack.pop();
        }
    }
    if(!stack.empty()) return "Impossible";
    return to_string(cnt);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s;
    cout << solve();
};