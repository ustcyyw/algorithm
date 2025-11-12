/**
 * @Time : 2024/7/22-3:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1611D 构造
 */
 /*
  * 排列指定的是结点的前后顺序
  * 排列的第一个一定是根结点
  * 第二个一定是和根仅有一条边的
  * 因为如果他不只有一条边 那么其距离和大于其父亲结点 但是他又在其父亲结点前
  *
  * 以此类推 按p的顺序查看结点 它的父亲结点一定得在其前面 并且要比它前一个结点路径长
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, root, p[N], ans[N], father[N];
ll dis[N];

bool solve() {
    if(p[1] != root) return false;
    ans[root] = 0, dis[root] = 0;
    for(int i = 2; i <= n; i++) {
        int pre = p[i - 1], v = p[i], fa = father[v];
        if(dis[fa] == -1) return false;
        ll diff = max(0ll, dis[pre] - dis[fa]);
        ans[v] = diff + 1, dis[v] = dis[fa] + ans[v];
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        fill(dis, dis + n + 1, -1);
        for(int i = 1, fa; i <= n; i++) {
            cin >> fa;
            if(fa != i) father[i] = fa;
            else root = i;
        }
        for(int i = 1; i <= n; i++)
            cin >> p[i];
        if(solve()) {
            for(int i = 1; i <= n; i++)
                cout << ans[i] << " ";
            cout << "\n";
        } else cout << "-1\n";
    }
};