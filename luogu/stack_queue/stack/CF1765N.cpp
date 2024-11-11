/**
 * @Time : 2023/10/17-10:49 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
int T;

void solve(string& s, int k) {
    int n = s.size();
    vector<int> next(n, INT_MAX), zero(n, INT_MAX);
    stack<int> stack;
    if(s[n - 1] == '0') zero[n - 1] = n - 1;
    else stack.push(n - 1);
    for(int i = n - 2; i >= 0; i--) {
        if(s[i] == '0') {
            zero[i] = i;
            continue;
        }
        zero[i] = zero[i + 1];
        while (!stack.empty() && s[i] <= s[stack.top()])
            stack.pop();
        if(!stack.empty()) next[i] = stack.top();
        stack.push(i);
    }
    string res;
    for(int i = 0, start = 1; i < n && k < n - i; ) {
        if(start) { // 是开头元素 不能有前导0
            if(next[i] - i <= k) { // 开头数字有下一个更小的，且删除次数够
                k -= next[i] - i;
                i = next[i];
            } else { // 开头数字没法到达下一个更小的 保留
                start = 0;
                res.push_back(s[i++]);
            }
        } else { // 不是开头元素 通过删除到达下一个更小的或者0
            if(s[i] == '0') res.push_back(s[i++]);
            else {
                int t = min(next[i], zero[i]);
                if(t - i <= k) {
                    k -= t - i;
                    i = t;
                } else res.push_back(s[i++]);
            }
        }
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    string str;
    for(int i = 1, k = 0; i <= T; i++) {
        cin >> str;
        cin >> k;
        solve(str, k);
    }
}