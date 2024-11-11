/**
 * @Time : 2024/5/20-9:39 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * abc三个字母 总共就6种排列
  * 一种可能的办法就是aaaabbbbcccc这样的排列方式 一共会产生5个子序列
  * 但是其中三种是aa bb cc这样特殊的 也就是说s和t没有这种特殊序列
  * 那只需要满足s和t不等于交界处产生的2个子序列 这样一定能找到相应的答案
  *
  * 另一种办法是周期进行构造 比如 abcabcabc 一共只会产生3个子序列
  * s和t中有一个或者两个都是aa bb cc这样特殊的 那么周期性构造只需要满足最多一个子序列要求了
  * 一定能找到
  *
  * 另外 特判n=1的情况 这种情况周期性排列只会产生2个子序列
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5, D = 1e9;
int T, n;
string s, t;
map<string, set<string>> mp, mp1, mps;

int init = []() -> int {
    mp["abc"] = {"ab","bc", "aa", "bb", "cc"};
    mp["acb"] = {"ac","cb", "aa", "bb", "cc"};
    mp["bac"] = {"ba","ac", "aa", "bb", "cc"};
    mp["bca"] = {"bc","ca", "aa", "bb", "cc"};
    mp["cab"] = {"ca","ab", "aa", "bb", "cc"};
    mp["cba"] = {"cb","ba", "aa", "bb", "cc"};

    mp1["abc"] = {"ab","bc","ca"};
    mp1["acb"] = {"ac","cb","ba"};
    mp1["bac"] = {"ba","ac","cb"};
    mp1["bca"] = {"bc","ca","ab"};
    mp1["cab"] = {"ca","ab","bc"};
    mp1["cba"] = {"cb","ba","ac"};

    mps["abc"] = {"ab","bc"};
    mps["acb"] = {"ac","cb"};
    mps["bac"] = {"ba","ac"};
    mps["bca"] = {"bc","ca"};
    mps["cab"] = {"ca","ab"};
    mps["cba"] = {"cb","ba"};
    return 0;
}();

string findS() {
    for(auto& p : mps) {
        if (!p.second.count(s) && !p.second.count(t))
            return p.first;
    }
    return "";
}

string find() {
    for(auto& p : mp) {
        if(!p.second.count(s) && !p.second.count(t))
            return p.first;
    }
    return "";
}

string find1() {
    for(auto& p : mp1) {
        if(!p.second.count(s) && !p.second.count(t))
            return p.first;
    }
    return "";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    cin >> s >> t;
    cout << "YES\n";
    if(n == 1) {
        cout << findS();
        return 0;
    }
    string base = find(), ans;
    if(base != "") {
        for(int j = 0; j < 3; j++)
            for(int i = 0; i < n; i++)
                ans.push_back(base[j]);
    } else {
        base = find1();
        for(int i = 0; i < n; i++)
            ans.append(base);
    }
    cout << ans;
};