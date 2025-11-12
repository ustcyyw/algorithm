/**
 * @Time : 2024/5/21-10:50 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1974G 反悔贪心
 */
/*
 * 钱够就一直买 钱不够将前面买的某一个退还
 * 前面能买得了那个更贵的 说明这些钱当前也可以使用
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5, D = 1e9;
int T, m, salary, cost[N];

void solve() {
    priority_queue<int> pq;
    for(int i = 2, money = salary; i <= m; i++, money += salary) {
        int c = cost[i];
        if(money >= c) money -= c, pq.push(c);
        else if(!pq.empty() && c < pq.top()) {
            money += pq.top() - c;
            pq.pop(), pq.push(c);
        }
    }
    cout << pq.size() << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> m >> salary;
        for(int i = 1; i <= m; i++)
            cin >> cost[i];
        solve();
    }
};