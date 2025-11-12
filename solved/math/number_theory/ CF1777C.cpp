/**
 * @Time : 2024/6/1-5:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1777C 数论 枚举
 */
 /*
  * 时间复杂度的分析 使用调和级数和的近似公式
  * 枚举子序列b的最小元素 然后保证序列中有1~m的因子 用优先队列来维护
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, m;
vector<vector<int>> arr;
set<int> st;

struct cmp{
    bool operator()(vector<int>& a, vector<int>& b){
        int i = a[0], j = b[0];
        return arr[i][a[1]] > arr[j][b[1]];
    }
};
priority_queue<vector<int>, vector<vector<int>>, cmp> pq;

int solve() {
    int ans = INT_MAX, last = -1;
    for(int i = 1, mv = *st.rbegin(); i <= m; i++) {
        for(int j = 1; j * i <= mv; j++) {
            if(st.count(j * i)) arr[i].push_back(j * i);
        }
        if(arr[i].empty()) return -1;
        pq.push({i, 0}), last = max(last, arr[i][0]);
    }
    for(int num : st) {
        while(pq.size() == m) {
            int i = pq.top()[0], j = pq.top()[1];
            if(arr[i][j] < num) pq.pop();
            else break;
            if(j + 1 < arr[i].size())
                last = max(last, arr[i][j + 1]), pq.push({i, j + 1});
        }
        if(pq.size() == m) ans = min(ans, last - num);
        else break;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        arr.assign(m + 1, {}), pq = {}, st.clear();
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            st.insert(num);
        }
        cout << solve() << "\n";
    }
};