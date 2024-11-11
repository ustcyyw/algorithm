/**
 * @Time : 2024/3/4-9:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 父节点v有 w1，w2，w3，w4...wm 共m个子结点 其子树中分别有c1, c2, ..., cm个子结点
  * 那么在计算 wi 这个子结点的期望时间时 要看它可能在什么时候被遍历 分别的概率是多少
  * 将m个子结点全排列 所有可能的情况是 m! 种
  * 考虑vi的位置时，可以将剩余m-1个子结点全排列，然后将vi进行插空
  * 每一种情况的可能性均等，都是1/m!
  *
  * 例如 假定只有4个子结点 abcd 现在考虑d的数学期望 先将abc进行排列
  * 再将d分别放入4个可能的位置 分别计算访问的时间 为了方便就用a b c代表相应子树的结点数量
  * 排列为 a b c，插入d，4种情况下d前面的结点数量相加是 0 + a + (a + b) + (a + b + c) = 3a + 2b + c
  * a c b : 3a + 2c + b
  * b a c: 3b + 2a + c
  * b c a: 3b + 2c + a
  * c a b: 3c + 2a + b
  * c b a: 3c + 2b + a
  * 全部情况加起来 12a + 12b + 12c 系数一致
  * 再考虑系数如何计算
  * 从例子可以看出 在任意一种排列中 a前面的系数与其位置有关
  * 在第一个位置 就能贡献3，第二个位置贡献2，第三个位置贡献1
  * 这是一个等差数列 从1累加到m-1，即 0.5*(m-1)*m
  * 有多少个排列中a在第一个位置、在第二个位置，其实就是将a拿走后 b和c的全排列
  * 一般意义下 拿走了要计算的结点 以及计算系数的结点 还剩m-2个结点
  * 因此a前面的系数为 (m-2)! * 0.5*(m-1)*m = 0.5 * m!
  *
  * 因为概率均等，期望就是 所有可能的结果之和 * p
  * 因此，从v访问wi的时间间隔为 (sum - ci) * 0.5 * m! / m! = 0.5 * (sum - ci)
  * sum表示v的所有子结点对应的树中结点之和 也就是cnt[v] - 1
  * time[wi] = 1 + time[v] + 0.5 * (sum - ci)
  * 注意这里+1表示访问到wi 时间戳要+1
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e5 + 5;
int n, cnt[N];
long double ans[N];
vector<vector<int>> graph;

void dfs1(int v) {
    cnt[v]++;
    for(int w : graph[v])
        dfs1(w), cnt[v] += cnt[w];
}

void dfs2(int v) {
    for(int w : graph[v]) {
        ans[w] = 1 + ans[v] + 0.5 * (cnt[v] - 1 - cnt[w]);
        dfs2(w);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    fill(cnt, cnt + n + 1, 0);
    graph.assign(n + 1, {});
    for(int i = 2, v; i <= n; i++) {
        cin >> v;
        graph[v].push_back(i);
    }
    dfs1(1);
    ans[1] = 1;
    dfs2(1);
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
};