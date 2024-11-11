/**
 * @Time : 2024/7/24-10:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1619D 二分答案 + 思维
 */
 /*
  * 最小值最大 显然要二分答案
  *
  * 在给定最小值val的情况下
  * m个朋友 选择m-1个商店
  * 对每个商店来说 对应礼物值达到val的人 这一个商店就能满足他们的要求
  * 如果有一个商店 可以达到2个人的要求 那么还有m-2个人的要求要达到
  * 并且还可以选择m - 2个商店，那么剩下m - 2个商店的选取 就按每个人最优选一个商店即可
  * 所以 只要有一个商店能满足2人及以上，并且在选择所有商店的前提下能满足每个人的要求
  * 那么 选择该2人商店 剩下的一人再选一个商店即可
  *
  * 反之 则选不出方案。反之有2种情况
  * 1.选择所有商店都不能满足所有人要求 那就很显然不行了
  * 2.能满足所有人要求 但是没有2人商店，也就是得有n个商店了 不满足商店选择要求
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m;
vector<vector<vector<int>>> p;

bool check(int val) {
    set<int> st;
    int two = 0;
    for(int i = 0; i < n; i++) {
        int j = m - 1;
        while(j >= 0 && p[i][j][0] >= val) {
            st.insert(p[i][j][1]);
            j--;
        }
        if(m - 1 - j >= 2) two = 1;
    }
    return st.size() == m && two == 1;
}

void solve() {
    int lo = 1, hi = 1e9;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        p.assign(n, {});
        for(int i = 0; i < n; i++) {
            for(int j = 0, val; j < m; j++) {
                cin >> val;
                p[i].push_back({val, j});
            }
            sort(p[i].begin(), p[i].end());
        }
        solve();
    }
};