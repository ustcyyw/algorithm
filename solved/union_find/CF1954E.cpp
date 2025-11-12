/**
 * @Time : 2024/4/13-4:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 考虑某个确定的伤害值k
 * 第一次使用闪电后 会将生命值 <= k 的敌人杀死。
 * 于是敌人就不是相连的了 就会因死去的敌人而分割成多个相连部分
 * 于是后续使用闪电 就只能在每一个部分独立地使用
 * 接下来再使用闪电 累计伤害变为2k 又会使生命值 <= 2k 的敌人杀死，每个部分又会再次细分
 *
 * 假设第一次使用闪电后 敌人被分割成c1部分
 * 那么第二轮使用闪电（累积伤害2k）就需要使用c1次 然后敌人分为c2部分
 * 那么第三轮使用闪电（累积伤害3k）就需要使用c2次 然后敌人分为c3部分
 * ....以此类推 直到所有敌人死亡
 *
 * 要对于 k 属于 [1, m] 都进行上述计算。 m为敌人最大生命值
 * 如果可以预处理出累计伤害值[1,m]下一共有多少个部分
 * 那么每个k的计算，就只需要 m / k 次
 * 全部加起来则为 m / 1 + m / 2 + m / 3 + ... m / m
 * 熟悉的 m(1 / 1 + 1 / 2 + 1 / 3 + ... 1 / m) = mlogm
 *
 * 而预处理一维坐标的连通性 是并查集的经典套路
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 1e5 + 5, MIN_VAL = -2e9;
int T, n, mh, health[N], id[N], cnt[N] = {0}; // cnt[k]:大小为k的闪电攻击一次后还剩的怪物的连通数量
ll ans[N];
vector<vector<int>> infos;

int find(int p) {
    return id[p] == p ? p : id[p] = find(id[p]);
}
// 连接成功返回true
bool connect(int p, int q) {
    p = find(p), q = find(q);
    if(p == q) return false;
    id[p] = q;
    return true;
}

void solve() {
    sort(infos.begin(), infos.end());
    mh = infos.back()[0]; // 最大怪物生命值
    ans[mh] = 1;
    int cc = 0; // 计算并查集连接成功的次数
    for(int k = mh - 1, j = n - 1; k >= 1; k--) {
        // 伤害为k的闪电 只能将h <= k的怪物一次打倒，那么生命 >= k + 1的怪物们还会连通在一起
        while(j >= 0 && infos[j][0] == k + 1) {
            int idx = infos[j][1];
            if(idx - 1 >= 0 && health[idx - 1] >= k + 1)
                cc += connect(idx, idx - 1);
            if(idx + 1 <= n && health[idx + 1] >= k + 1)
                cc += connect(idx, idx + 1);
            j--;
        }
        cnt[k] = n - 1 - j - cc; // n - 1 - j就是生命值 > k的怪物数量，减去连接次数 就是连通分量的数目
        ans[k] = 1;
        for(int t = k; t < mh; t += k)
            ans[k] += cnt[t];
    }
    for(int i = 1; i <= mh; i++)
        cout << ans[i] << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++) {
        id[i] = i;
        cin >> health[i];
        infos.push_back({health[i], i});
    }
    solve();
};