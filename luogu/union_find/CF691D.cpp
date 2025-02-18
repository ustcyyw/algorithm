/**
 * @Time : 2025/2/17-10:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF691D 1700 并查集 贪心
 */
 /*
  * 给定的m个交换位置 就是一种等价关系 在同一个连通分量（等价关系）中 数可以任意换位置
  * 将大的换到前面即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5, M = 3e6 + 5, mod = 1e9 + 7;
int T, n, m, nums[N];

struct UF {
    vector<int> id;
    UF(int total) {
        for(int i = 0; i <= total; i++)
            id.push_back(i);
    }

    int find(int p) {
        return id[p] == p ? p : id[p] = find(id[p]);
    }

    void connect(int p, int q) {
        p = find(p), q = find(q);
        if(p == q) return;
        id[p] = q;
    }
};

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        UF uf(n);
        for(int i = 1, a, b; i <= m; i++) {
            cin >> a >> b;
            uf.connect(a, b);
        }
        map<int, vector<int>> idx, val;
        for(int i = 1; i <= n; i++) {
            int id = uf.find(i);
            idx[id].push_back(i), val[id].push_back(nums[i]);
        }
        for(auto& [id, arr] : idx) {
            sort(val[id].begin(), val[id].end());
            reverse(val[id].begin(), val[id].end());
            for(int i = 0; i < arr.size(); i++)
                nums[arr[i]] = val[id][i];
        }
        for(int i = 1; i <= n; i++)
            cout << nums[i] << " ";
    }
};