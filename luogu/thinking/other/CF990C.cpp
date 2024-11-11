/**
 * @Time : 2024/1/12-3:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 计数括号的剩余 如果是左括号剩余 就是正数，如果是右括号剩余 就是负数。两个都剩余的 没法匹配
 * 如果是左括号有剩余，就得找一个有括号有剩余的放在其右边
 * 如果是自身已经匹配了的，就找令外一个自身也匹配了的 放在其左边右边都可以
 * 注意重复计算的处理即可
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5, F = -1e9;
string s;
int n, cnt[N];
// 计数括号的剩余 如果是左括号剩余 就是正数，如果是右括号剩余 就是负数。两个都剩余的 没法匹配
int countBracket(string& s) {
    int left = 0, right = 0;
    for(char c : s) {
        if(c == '(') left++;
        else {
            if(left > 0) left--;
            else right++;
        }
    }
    if(left && right) return F;
    return left ? left : -right;
}

int main(){
    unordered_map<int, int> map;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> s;
        cnt[i] = countBracket(s);
        map[cnt[i]]++;
    }
    long long res = 0;
    for(int i = 0; i < n; i++) {
        if(cnt[i] == F) continue;
        if(cnt[i] == 0) res += 2 * map[0]; // 放在其左边右边都可以 所以要 * 2
        else res += map[-cnt[i]];
    }
    cout << res / 2 << endl;
}