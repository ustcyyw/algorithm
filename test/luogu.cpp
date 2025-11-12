/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, ans[N], out[N], m;
vector<vector<int>> arrs, infos;

void solve() {
    for(int i = 0, time = 1, j = 0; i < m; i++) {
        while(j < n && infos[j][0] <= i) j++;
        // 先找当前i位置最小的数
        int val = INT_MAX;
        for(int k = j; k < n; k++) {
            int idx = infos[k][1];
            // 表示在前置位置就已经比别的数组同位置大的情况 那么当前这一位就不用考虑了
            if(out[idx] == time) continue;
            val = min(val, arrs[idx][i]);
        }
        ans[i] = val;
        bool flag = false;
        for(int k = j; k < n; k++) {
            int idx = infos[k][1];
            if(out[idx] == time) continue;
            if(arrs[idx][i] > val) out[idx] = time;
            // 当某个依照字符序应该放在未排序最底层的数组已经选到最后一个元素，将其放在未排序最底层
            // 那么从当前位置之后 还剩余元素的数组都是可能落到最下层的 再对这些剩余的数组继续排列
            if(out[idx] != time && i == arrs[idx].size() - 1) flag = true;
        }
        // 对其它未排序的数组进行新一轮排序, 轮次序号更新
        if(flag) time++;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        infos = {}, arrs.assign(n, {}), fill(out, out + n + 1, 0);
        for(int i = 0, c; i < n; i++) {
            cin >> c;
            infos.push_back({c, i});
            for(int j = 1, num; j <= c; j++) {
                cin >> num;
                arrs[i].push_back(num);
            }
        }
        sort(infos.begin(), infos.end());
        m = infos.back()[0];
        solve();
        for(int i = 0; i < m; i++)
            cout << ans[i] << " ";
        cout << "\n";
    }
}