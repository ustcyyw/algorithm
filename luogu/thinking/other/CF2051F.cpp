/**
 * @Time : 2024/12/24-11:35 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2051F 2052 思维
 */
 /*
  * 对于位置p
  * ai < p, 操作后有两个可能的位置p,p-1
  * ai > p, 操作后有两个可能的位置p,p+1
  * ai = p, 操作后有两个可能的位置1, n
  *
  * 结合case手玩 可以得出推论
  * 1. joker的可能位置一定是连续的区间
  * 2. 如果选定的位置是joker的可能位置，会多出两个区间[1,1], [n,n]
  * 3. 最多有3个区间
  * 4. 每次操作考虑区间的延伸情况 以及是否会多出[1,1], [n,n]即可
  * 5. 随着区间的延伸 区间可能会连到一起 需要合并区间
  * 6. 一旦joker可能在任意位置 再次操作后 joker仍然可以在任意位置
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, m, q, a[N];

vector<vector<int>> merge(vector<vector<int>>& arr) {
    sort(arr.begin(), arr.end());
    vector<vector<int>> ans;
    int lo = arr[0][0], hi = arr[0][1];
    for(int i = 1; i < arr.size(); i++) {
        if(hi < arr[i][0]) {
            ans.push_back({lo, hi});
            lo = arr[i][0], hi = arr[i][1];
        } else hi = max(hi, arr[i][1]);
    }
    ans.push_back({lo, hi});
    return ans;
}

vector<vector<int>> change(vector<vector<int>>& arr, int x) {
    vector<vector<int>> ans;
    for(auto& t : arr) {
        int lo = t[0], hi = t[1];
        if(x < lo) ans.push_back({lo - 1, hi});
        else if(x > hi) ans.push_back({lo, hi + 1});
        else {
            // 单独一个点 被移动就要改变了
            if(hi - lo + 1 >= 2) ans.push_back({lo, hi});
            ans.push_back({1, 1}), ans.push_back({n, n});
        }
    }
    return merge(ans);
}

void solve() {
    vector<vector<int>> arr = {{m, m}};
    for(int i = 1, cnt = 0; i <= q; i++) {
        if(cnt == n) {
            cout << cnt << " ";
            continue;
        }
        arr = change(arr, a[i]);
        cnt = 0;
        for(auto& t : arr)
            cnt += t[1] - t[0] + 1;
        cout << cnt << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> m >> q;
        for(int i = 1; i <= q; i++)
            cin >> a[i];
        solve();
    }
};