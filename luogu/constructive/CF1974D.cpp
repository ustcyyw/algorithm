/**
 * @Time : 2024/5/21-8:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 首先特别地 字符串长度为奇数 or 为2但是两个字符不一样 都没办法完成要求
 * 直接输出no
 *
 * 两个方向独立且是相同的情况
 * 水平方向 枚举r向左走的指令数c1 那么h向左走的指令数为cnt1 - c1
 * 假设r总是走得 >= h，现在r在h的左边 c1 - (cnt1 - c1) = 2 * c1 - cnt1步
 * 因此 向右走的指令 必须是r多走 2 * c1 - cnt1 步
 * c2 - (cnt2 - c2) = 2 * c1 - cnt1
 * 2 * c2 = cnt2 + 2 * c1 - cnt1
 * 如果可以整除 就说明这样安排
 * 如果都找到满足等式的c1和c2 那么就说明这个方向两个机器执行指令后没法重合
 * 还要注意另外一个机器是否进行了指令
 *
 * 如果水平方向一个机器没有执行指令 那么竖直方向换该机器优先走
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 55;
ll T, m;
vector<int> n, s, e, w;
string t, ans;

int check(vector<int>& a, vector<int>& b, char c, char o) {
    int cnt1 = a.size(), cnt2 = b.size();
    for(int c1 = (cnt1 + 1) / 2; c1 <= cnt1; c1++) {
        if((cnt2 + 2 * c1 - cnt1) % 2 == 0) {
            int c2 = (cnt2 + 2 * c1 - cnt1) / 2;
            int c3 = cnt1 - c1, c4 = cnt2 - c2;
            for(int i = 0; i < cnt1; i++)
                ans[a[i]] = i < c1 ? c : o;
            for(int i = 0; i < cnt2; i++)
                ans[b[i]] = i < c2 ? c : o;
            return c3 + c4;
        }
    }
    return -1;
}

bool solve() {
    if(m % 2 == 1 || (m == 2 && t[0] != t[1])) return false;
    ans.assign(m, '.');
    int f1 = check(n, s, 'R', 'H');
    if(f1 == -1) return false;
    int f2 = check(e, w, f1 == 0 ? 'H' : 'R', f1 == 0 ? 'R' : 'H');
    if(f2 == -1) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> m;
        cin >> t;
        s.clear(), n.clear(), e.clear(), w.clear();
        for(int i = 0; i < t.size(); i++) {
            if(t[i] == 'S') s.push_back(i);
            if(t[i] == 'N') n.push_back(i);
            if(t[i] == 'E') e.push_back(i);
            if(t[i] == 'W') w.push_back(i);
        }
        cout << (solve() ? ans : "NO") << "\n";
    }
};