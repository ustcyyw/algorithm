/**
 * @Time : 2024/9/3-2:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 树上hash模板 查看树是否同构
 */
/*
 * 如果树是给定边来描述 意味着结点顺序是可调的 树结构和结点存储顺序无关
 * 例题
 * https://codeforces.com/contest/1800/problem/G
 * https://www.luogu.com.cn/problem/P5043
 */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int m1 = 998244353, m2 = 19260817, N = 2e5 + 5;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const ull rnd = rng(); // 取一个随机数
ull h[N]; // h[i]: 结点i这棵子树对应的hash值
int T, n;

vector<vector<int>> graph; // 描述树结构
// 单一值参与计算hash的映射函数
ull g(ull x) {
    return x * x * x * m1 + m2 + rnd;
}

/*
 * 计算某棵树的hash_code并且返回这棵树是否为对称树
 * 判断对称需要使用的信息 各hash值的子树出现了几次
 * 如果有出现奇数次的hash值 只允许出现一次 并且该值对应的树必须是对称的 将其放在中轴上
 */
bool dfs(int v, int f) {
    h[v] = 1; // 重要的初始条件 不能省略
    map<ull, int> mp, cnt;
    for(int w : graph[v]) {
        if(w == f) continue;
        bool flag = dfs(w, v);
        h[v] += g(h[w]), mp[h[w]] = flag, cnt[h[w]]++;
    }
    int flag = 0;
    for(auto& p : cnt) {
        ull code = p.first, c = p.second;
        if(c % 2 == 0) continue;
        if(flag || !mp[code]) return false;
        flag = 1;
    }
    return true;
}

class Solution {
public:
    
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}