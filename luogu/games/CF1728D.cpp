/**
 * @Time : 2024/12/12-4:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1728D 1800 博弈论 记忆化搜索
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n;
string s;
vector<vector<int>> cache;

int cal(char ca, char cb, int flag) {
    if(flag != 0) return flag;
    if(ca == cb) return 0;
    return ca < cb ? 1 : 2;
}

int dfs(int lo, int hi) {
    if(lo + 1 == hi)
        return s[lo] == s[hi] ? 0 : 1;
    if(cache[lo][hi] != -1) return cache[lo][hi];
    int f1 = dfs(lo + 1, hi - 1), f2 = dfs(lo + 2, hi), f3 = dfs(lo, hi - 2);
    // a拿lo，那么b可以拿hi或者lo+1
    int r1 = cal(s[lo], s[hi], f1), r2 = cal(s[lo], s[lo + 1], f2), a1 = -1;
    if(r1 == 2 || r2 == 2) a1 = 2; // b选了其中一个字母会赢 那么b赢
    else if(r1 == 0 || r2 == 0) a1 = 0; // b没法赢的情况下 选其中一个能平 那么双方打平
    else a1 = 1; // 此时r1和r2都不为2，也都不为0，那么r1=1并且r2=1 无论b拿哪个字母都是a赢 那么a就胜
    // a拿hi，b可以拿lo或者hi-1
    int r3 = cal(s[hi], s[lo], f1), r4 = cal(s[hi], s[hi - 1], f3), a2;
    if(r3 == 2 || r4 == 2) a2 = 2; // b选了其中一个字母会赢 那么b赢
    else if(r3 == 0 || r4 == 0) a2 = 0; // b没法赢的情况下 选其中一个能平 那么双方打平
    else a2 = 1; // 此时r1和r2都不为2，也都不为0，r1=1 并且r2=1 也就是无论b拿哪个字母都是a赢 那么a就胜
    int ans = -1;
    if(a1 == 1 || a2 == 1) ans = 1; // a选其中一个字母能必胜 那么a赢
    else if(a1 == 0 || a2 == 0) ans = 0; // a赢不了 但是选其中一个字母能打平 双方将打平
    else ans = 2; // a赢不了也平不了 那就是b赢
    return cache[lo][hi] = ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> s;
        n = s.size();
        cache.assign(n, vector(n, -1));
        int flag = dfs(0, n - 1);
        if(flag == 1) cout << "Alice\n";
        else if(flag == 2) cout << "Bob\n";
        else cout << "Draw\n";
    }
};