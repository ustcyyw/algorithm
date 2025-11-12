/**
 * @Time : 2024/7/10-5:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1538E 模拟
 */
 /*
  * 主要是合并操作 只有交接处 左边字符的尾部最多3个元素 右边字符头部最多3个元素会影响子串数目
  * 维护子串数目和头尾元素即可
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n;
string x, ope, s1, space, s2;
map<string, string> head, tail;
map<string, ll> cnt;

int count(string& s) {
    int ans = 0;
    for(int i = 0; i + 3 < s.size(); i++)
        if(s.substr(i, 4) == "haha") ans++;
    return ans;
}

string get_head(string& s) {
    if(s.size() <= 3) return s;
    return s.substr(0, 3);
}

string get_tail(string& s) {
    if(s.size() <= 3) return s;
    return s.substr(s.size() - 3);
}

void merge() {
    string temp = tail[s1] + head[s2];
    cnt[x] = cnt[s1] + cnt[s2] + count(temp);
    if(temp.size() == 6)
        head[x] = head[s1], tail[x] = tail[s2];
    else head[x] = get_head(temp), tail[x] = get_tail(temp);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        head = {}, tail = {}, cnt = {};
        for(int i = 1; i <= n; i++) {
            cin >> x >> ope;
            if(ope == ":=") {
                cin >> s1;
                cnt[x] = count(s1);
                head[x] = get_head(s1), tail[x] = get_tail(s1);
            } else {
                cin >> s1 >> space >> s2;
                merge();
            }
            if(i == n) cout << cnt[x] << "\n";
        }
    }
};