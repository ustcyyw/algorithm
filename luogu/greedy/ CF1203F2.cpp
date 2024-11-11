/**
 * @Time : 2024/5/17-4:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1203F2 贪心 + dp
 */
/*
 * hard版本 要找出尽量多可能执行的任务数
 *
 * 对于 b>=0 的情况 那就尽量去拿到更多分数 拿不到了之后就去考虑 b<0的情况
 *
 * 考虑 b<0 的情况 两个任务(a1, b1) (a2, b2)
 * 如果第一个任务完成后还可以执行第二个任务 r >= a1, r + b1 >= a2
 * 但是第二个任务执行后 无法完成第二个任务  r >= a2, r + b2 < a1
 * 这种情况下 应该先执行第一个任务
 * r >= a2 - b1, r < a1 - b2
 * 因此 a1 - b2 > a2 - b1, a1 + b1 > a2 + b2
 * 所以应该执行 ai + bi 更大的任务
 *
 * 确定了执行顺序后 考虑怎么样执行可以执行得更多
 * 前置任务执行结束后 如果rating尽可能地大 有利于后续执行更多任务
 * (类似于找最长上升子序列 在序列长度一定的情况下 结尾元素更可能小)
 * 定义 dp[i][j] 截止到第i个任务，执行了j个任务时，最大的rating
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100 + 5, D = 1e9;
int T, n, m, r;
vector<vector<int>> pos, neg;

int pick_pos() {
    int cnt = 0;
    for(vector<int>& proj : pos) {
        // 执行完任务后 rating还得 >= 0
        if(r < proj[0]) break;
        r += proj[1], cnt++;
    }
    return cnt;
}

int pick_neg() {
    m = neg.size();
    vector<vector<int>> dp(m + 1, vector(m + 1, -1));
    dp[0][0] = r;
    for(int i = 1; i <= m; i++) {
        dp[i][0] = r;
        int a = neg[i - 1][0], b = neg[i - 1][1];
        for(int j = 1; j <= i + 1; j++) {
            // 当前任务不执行
            dp[i][j] = dp[i - 1][j];
            // 执行当前任务 那么前面需要执行了j-1个任务 并且前面j-1个任务执行完成后还够执行当前任务
            if(dp[i - 1][j - 1] >= a && dp[i - 1][j - 1] + b >= 0)
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + b);
        }
    }
    for(int i = m; i >= 0; i--)
        if(dp[m][i] >= 0) return i;
    return 0;
}

void solve() {
    sort(pos.begin(), pos.end());
    sort(neg.begin(), neg.end(), [](auto& a, auto& b) -> bool {
        return a[0] + a[1] > b[0] + b[1];
    });
    cout << pick_pos() + pick_neg();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> r;
    for(int i = 1, a, b; i <= n; i++) {
        cin >> a >> b;
        if(b >= 0) pos.push_back({a, b});
        else neg.push_back({a, b});
    }
    solve();
};