/**
 * @Time : 2024/11/15-11:00 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF978G 贪心 模拟 1700
 */
 /*
  * 优先复习考试最临近的 被公布之后才加入复习计划
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 105;
int T, n, m, ans[N];
vector<vector<int>> exams[N];

// 要比较经过某条边到达非树结点的距离，优先得到最小距离的边
struct cmp {
    bool operator()(vector<int> &a, vector<int> &b) {
        return a[1] - b[1] >= 0;
    }
};
priority_queue<vector<int>, vector<vector<int>>, cmp> pq;

bool solve() {
    set<int> ready;
    for(int i = 1; i <= n; i++) {
        for(auto& exam : exams[i]) // 宣布考试的 都放入备考集合
            pq.push(exam);
        if((ready.empty() || *ready.begin() > i) && pq.empty()) // 没有可以考试的 并且也没有可以准备的 休息
            continue;
        if(!ready.empty() && *ready.begin() == i) { // 进行考试
            ans[i] = m + 1;
            ready.erase(ready.begin());
            continue;
        }
        if(pq.top()[1] == i) return false; // 到考试当天了 这个考试还没准备好
        vector<int> temp = pq.top();
        pq.pop();
        ans[i] =  temp[3], temp[2]--;
        if(temp[2] == 0) ready.insert(temp[1]);
        else pq.push(temp);
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    vector<int> marked(n + 1, 0);
    for(int i = 1, s, d, c; i <= m; i++) {
        cin >> s >> d >> c;
        exams[s].push_back({s, d, c, i});
        marked[d]++;
        if(marked[d] > 1) { // 有两个考试在同一天
            cout << "-1";
            return 0;
        }
    }
    if(!solve()) cout << "-1";
    else {
        for(int i = 1; i <= n; i++)
            cout << ans[i] << " ";
    }
};