/**
 * @Time : 2023/12/13-8:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 启发式合并
 * 并且借鉴索引优先队列的思路来组织数据
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 3e5 + 5;
// box[i]: 盒子i对应的集合的索引, rb[i] 集合索引i对应的盒子的标号
// ball[i]：球i放置的集合的索引
int n, Q, type, x, y, box[N], rb[N], ball[2 * N];

void change(vector<vector<int>>& sets) {
    int p = box[y], q = box[x];
    if(sets[p].size() > sets[q].size()) {
        swap(box[x], box[y]);
        swap(p, q);
    }
    rb[box[x]] = x, rb[box[y]] = y;
    for(int b : sets[p]) {
        sets[q].push_back(b);
        ball[b] = q;
    }
    sets[p].clear();
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> Q;
    vector<vector<int>> sets(n + 1);
    for(int i = 1; i <= n; i++){
        sets[i].push_back(i);
        box[i] = ball[i] = rb[i] = i;
    }
    while(Q-- > 0) {
        cin >> type;
        if(type == 1) {
            cin >> x >> y;
            change(sets);
        } else if(type == 2) {
            n++;
            cin >> x;
            sets[box[x]].push_back(n);
            ball[n] = box[x];
        } else {
            cin >> x;
            cout << rb[ball[x]] << endl;
        }
    }
};