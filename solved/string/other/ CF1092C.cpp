/**
 * @Time : 2024/4/24-4:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 两个最长的子串a,b 假定a是前缀，b是后缀
  * 那么剩下的更短的子串 每一组都要满足 其中一个是a的前缀 另外一个是b的后缀
  * 如果有任何一组不满足 就说明假定a是前缀错误的 那么应该是b为前缀
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n;
vector<pair<string, int>> infos[N];
string ans;

int checkOne(string& pre, string& suf, string& t1, string& t2, int len) {
    string pt = pre.substr(0, len), st = suf.substr(n - len - 1, len);
    return pt == t1 && st == t2;
}

bool check(string& pre, string& suf, int idp) {
    ans.assign(2 * n - 2, 'S');
    ans[idp] = 'P';
    for(int len = n - 2; len >= 1; len--) {
        auto &p1 = infos[len][0], p2 = infos[len][1];
        string &t1 = p1.first, &t2 = p2.first;
        int id1 = p1.second, id2 = p2.second;
        if(checkOne(pre, suf, t1, t2, len)) ans[id1] = 'P';
        else if(checkOne(pre, suf, t2, t1, len)) ans[id2] = 'P';
        else return false;
    }
    return true;
}

void solve() {
    auto &p1 = infos[n - 1][0], p2 = infos[n - 1][1];
    bool flag = check(p1.first, p2.first, p1.second)
                || check(p2.first, p1.first, p2.second);
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    string t;
    for(int i = 0; i < 2 * n - 2; i++) {
        cin >> t;
        infos[t.size()].emplace_back(t, i);
    }
    solve();
};