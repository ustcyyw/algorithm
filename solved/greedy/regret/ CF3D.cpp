/**
 * @Time : 2024/3/1-12:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 遍历过程中 如果遇到右括号，就一定要有左括号匹配 将左括号数量记为cnt
  * 如果遇到了?
  * 1. cnt > 0, 可以暂时将?视为右括号 去和左括号匹配
  * 2. cnt = 0, 那么必须将之前视为右括号的?当作左括号
  * 那么连同之前将其视为右括号进行匹配的左括号 都需要右括号来匹配 cnt += 2
  * 将默认的右括号变为左括号 代价的变化为 left[i]-right[i]
  * 为了让代价最小 应该将left[i]-right[i]最小的?进行转变 给代价和增加一个最小的量
  * 反悔贪心
  *
  * 最终cnt != 0说明可以匹配成功
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 5e4 + 5;
int n, l, r;
string s;

ll solve() {
    priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;
    ll cnt = 0, cost = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '(') cnt++;
        else { // 遇到?或者), ?默认视为)
            if(s[i] == '?') { // ?默认先是右括号
                cin >> l >> r;
                s[i] = ')';
                cost += r, pq.push({l - r, i});
            }
            if(cnt == 0) { // 没有左括号可匹配的情况
                if(pq.empty()) return -1; // 没有?可以转变为( 无法匹配
                cost += pq.top()[0], s[pq.top()[1]] = '(';
                pq.pop();
                cnt += 2;
            }
            cnt--;
        }
    }
    return cnt == 0 ? cost : -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s;
    ll res = solve();
    cout << res << endl;
    if(res != -1) cout << s << endl;
};