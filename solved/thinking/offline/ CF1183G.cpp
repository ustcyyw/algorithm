/**
 * @Time : 2024/5/15-2:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 统计后按 数量排序 数量相同按1的数量排序
  * 同一种类的糖果出现最多的次数为 mv
  * 最终结果中 糖果数目最多 1,2,...,mv-1,mv
  * 枚举数量 val，那么糖果数量 >= val的且没有用过的 都可以拿出val个
  * 这样就保证了总数量最大 并且可以每次都拿f最多的
  *
  * 有点离线查询的感觉
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n;
map<int, int> cnt, fav;

struct cmp{
    bool operator()(vector<int>& a, vector<int>& b){
        return a[1] < b[1];
    }
};

void solve() {
    vector<vector<int>> arr;
    for(auto& p : cnt)
        arr.push_back({p.second, fav[p.first]});
    sort(arr.begin(), arr.end());
    ll ans = 0, fc = 0;
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    for(int val = arr.back()[0], i = arr.size() - 1; val >= 1; val--) {
        while(i >= 0 && arr[i][0] >= val) {
            pq.push(arr[i]);
            i--;
        }
        if(!pq.empty()) {
            vector<int> temp = pq.top();
            ans += val, fc += min(temp[1], val);
            pq.pop();
        }
        if(i < 0 && pq.empty()) break; // 没有可用的糖果了
    }
    cout << ans << " " << fc << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        cnt.clear(), fav.clear();
        for(int i = 1, num, f; i <= n; i++) {
            cin >> num >> f;
            cnt[num]++, fav[num] += f;
        }
        solve();
    }
};