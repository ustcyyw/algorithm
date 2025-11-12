/**
 * @Time : 2024/3/25-9:18 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 有点像离线查询的思维 因为最后的操作会覆盖前面的操作 所以先从最后的操作来计数
  * 任何一行后面被涂色 对前面列的涂色的影响就是 列涂色时该行不会变（从最后结果来看）
  * 反之亦然 所以用分别用 row, col来存放后续被涂色的行、列
  * 另外 如果某一行被涂色了 前面还有一行对其进行涂色，那么前面的操作是无效的
  *
  * 特别要注意 初始时候每个位置都是0 因此要特别对0进行处理 看看有没有没有操作的位置
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5, MOD = 1e9 + 7;
ll n, m, k;
int info[N][3];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    for(int i = 0; i < k; i++)
        cin >> info[i][0] >> info[i][1] >> info[i][2];
    map<int, ll> map;
    unordered_set<int> row, col;
    for(int i = k - 1; i >= 0; i--) {
        int t = info[i][0], idx = info[i][1], x = info[i][2];
        if(t == 1) { // 行操作
            if(row.count(idx)) continue; // 后面有此行的涂色 因此当前操作无用
            row.insert(idx);
            map[x] += m - (ll)col.size();
        } else {
            if(col.count(idx)) continue;
            col.insert(idx);
            map[x] += n - (ll)row.size();
        }
    }
    map[0] += (ll)(n - row.size()) * (m - col.size()); // 0的特殊处理 将没涂色的全加上
    vector<pair<int, ll>> arr;
    for(auto& p : map)
        if(p.second != 0) arr.emplace_back(p);
    cout << arr.size() << "\n";
    for(auto& p : arr)
        cout << p.first << " " << p.second << "\n";
};
