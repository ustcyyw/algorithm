/**
 * @Time : 2024/5/17-3:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 贪心
 */
/*
  * 涉及执行任务安排任务这类 需要确定一个最优顺序的 用贪心来找顺序
  *
  * 考虑 b<0 的情况 两个任务(a1, b1) (a2, b2)
  * 如果第一个任务完成后还可以执行第二个任务 r >= a1, r + b1 >= a2
  * 但是第二个任务执行后 无法完成第二个任务  r >= a2, r + b2 < a1
  * 这种情况下 应该先执行第一个任务
  * r >= a2 - b1, r < a1 - b2
  * 因此 a1 - b2 > a2 - b1, a1 + b1 > a2 + b2
  * 所以应该执行 ai + bi 更大的任务
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100 + 5, D = 1e9;
int T, n, m, r;
vector<vector<int>> pos, neg;

// 加分的时候 先做门槛低的 这样可以尽量提高分数
bool pick(vector<vector<int>>& arr) {
    for(vector<int>& proj : arr) {
        if(r < proj[0]) return false;
        r += proj[1];
    }
    return true;
}

bool solve() {
    sort(pos.begin(), pos.end());
    sort(neg.begin(), neg.end(), [](auto& a, auto& b) -> bool {
        return a[0] + a[1] > b[0] + b[1];
    });
    return pick(pos) && pick(neg) && r >= 0; // 执行完所有任务后 rating还得 >= 0
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> r;
    for(int i = 1, a, b; i <= n; i++) {
        cin >> a >> b;
        if(b >= 0) pos.push_back({a, b});
        else neg.push_back({a, b});
    }
    cout << (solve() ? "YES" : "NO");
};