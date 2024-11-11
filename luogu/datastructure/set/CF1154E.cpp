/**
 * @Time : 2024/5/10-4:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1154E 优先队列 + 有序set
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, k, mp[N];
string s;
set<int> q; // 表示人的位置
priority_queue<int> pq;

int find() {
    while(!pq.empty()) {
        int cur = pq.top();
        pq.pop();
        if(s[mp[cur]] == '.') return mp[cur];
    }
    return -1;
}

void solve() {
    char team = '1';
    while(!pq.empty()) {
        int cur = find();
        if(cur == -1) break;
        unordered_set<int> del;
        del.insert(cur);
        auto it = ++q.find(cur);
        for(int i = 0; i < k && it != q.end(); i++, it++)
            del.insert(*it);
        it = --q.find(cur);
        for(int i = 0; i < k && it != q.begin(); i++, it--)
            del.insert(*it);
        for(int idx : del)
            q.erase(idx), s[idx] = team;
        team = team == '1' ? '2' : '1';
    }
    cout << s;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    q.insert(-1); // 哨兵
    for(int i = 0, num; i < n; i++) {
        cin >> num;
        pq.push(num), q.insert(i);
        mp[num] = i;
    }
    s = string(n, '.');
    solve();
};