/**
 * @Time : 2024/2/6-9:59 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 题意翻译过来就是  就是怎么安排这些人 最大多少个集合 最少多少个集合
 * 并且每个人都有两个邻居，题目给出的是部分邻居信息 有缺失的信息于是存在不同的可能性
 *
 * 3个或3个以上元素的环 任意元素两个邻居都是确定了的。因此他们就是固定集合 无法与别的集合合并
 *
 * 2个元素的环 可能会有树枝。2个元素的环 每个元素可能再安排一个邻居 记可安排数量为space
 * 如果安排一个邻居 相当于一次集合合并 集合数量-1
 * 判断2元环中的元素是否可以再安排邻居 就看元素的度数是否为2。
 * 如果为3则说明题目已经明确给出了邻居 无法再有新安排
 * 2元环如果存在 其合并之后最少剩余的数量为 max(1, two - space)
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
int T, n, nums[N], degree[N], marked[N];
vector<vector<int>> graph;
// 遍历二元环 返回二元环其中一个元素的编号。如果是3元或者更长的环 返回-1
int dfs(int v) {
    marked[v] = true;
    int id = nums[nums[v]] == v ? v : -1;
    for(int w : graph[v]) {
        if(marked[w]) continue;
        int temp = dfs(w);
        if(id == -1) id = temp;
    }
    return id;
}

void solve() {
    int two = 0, more = 0, space = 0;
    for(int i = 1; i <= n; i++) {
        if(marked[i]) continue;
        int v = dfs(i);
        if(v == -1) more++;
        else {
            two++;
            if(degree[v] == 2) space++;
            if(degree[nums[v]] == 2) space++;
        }
    }
    int minV = more + (two ? max(1, two - space) : 0);
    cout << minV << " " << (two + more) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        memset(degree, 0, sizeof(degree)), memset(marked, 0, sizeof(marked));
        graph.assign(n + 1, vector(0, 0));
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            degree[i]++, degree[nums[i]]++;
            graph[i].push_back(nums[i]), graph[nums[i]].push_back(i);
        }
        solve();
    }
};