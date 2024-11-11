/**
 * @Time : 2024/3/29-10:52 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 长度要能被n整除，2e5以内 因子最多的数也就160个因子
  * 因此可以枚举可选的长度
  * 对于给定的长度len。s要以长度为len的子串进行重复，其中最多运行出现一个不同的子串 并且该子串只有一个字母不同
  * 因此s的首尾两个子串 一定有一个是重复出现的串
  * 那就看看以这两个串为模版 是否能匹配s 或者匹配过程中最多一个字母不同
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5, M = 13 * 9;
int T, n;
string s;

bool count(string p, int m) {
    for(int i = 0, j = 0, cnt = 0; i < n; i++, j = (j + 1) % m) {
        if(p[j] != s[i]) cnt++;
        if(cnt > 1) return false;
    }
    return true;
}

int solve() {
    vector<int> lens;
    for(int i = 1; i <= (int)sqrt(n) + 1; i++) {
        if(n % i == 0) {
            lens.push_back(i);
            lens.push_back(n / i);
        }
    }
    sort(lens.begin(), lens.end());
    for(int i = 0; i < lens.size() - 1; i++) {
        int len = lens[i];
        if(count(s.substr(0, len), len) || count(s.substr(n - len, len), len))
            return len;
    }
    return n;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        cin >> s;
        cout << solve() << "\n";
    }
};