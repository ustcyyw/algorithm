/**
 * @Time : 2023/10/25-8:36 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    /*
     * dp[i][s][c1][c2]: 截止第i行 且第i行状态为s 且总共安排了c1 c2个内/外向的人
     * 使用2位二进制表示状态
     * 二进制的00表示没人 01表示有内向的人 10表示有外向的人 11表示不合法
     */
//    int n, full, res = 0;
//    vector<vector<int>> add, map;
//    int getMaxGridHappiness(int m, int n, int ic, int ec) {
//        if(n > m) swap(n, m);
//        this->n = n;
//        this->full = (1 << n * 2) - 1;
//        map.assign(full + 1, {}); // 状态对应的 排列信息
//        for (int s = full; s; s = (s - 1) & full)
//            map[s] = check(s);
//        map[0] = vector(n + 2, 0);
//        // 缓存新增一行时 幸福度的变化
//        add = vector(full + 1, vector(full + 1, 0));
//        for (int s = full; s; s = (s - 1) & full) {
//            if(map[s].empty()) continue;
//            add[0][s] =  make_add(map[0], map[s]);
//            for (int u = full; u; u = (u - 1) & full) {
//                if(map[u].empty()) continue;
//                add[s][u] = make_add(map[s], map[u]);
//            }
//        }
//        vector<vector<vector<vector<int>>>> dp(m + 1, vector(full + 1, vector(ic + 1, vector(ec + 1, -1))));
//        dp[0][0][0][0] = 0;
//        for (int i = 1; i <= m; i++) {
//            vector<vector<vector<int>>> &pre = dp[i - 1], &cur = dp[i];
//            for (int c1 = 0; c1 <= ic; c1++) {
//                for (int c2 = 0; c2 <= ec; c2++) {
//                    change(pre, cur, c1, c2, 0); // 前置状态可能为0
//                    for (int u = full; u; u = (u - 1) & full) { // 枚举前置状态
//                        change(pre, cur, c1, c2, u);
//                    }
//                }
//            }
//        }
//        return res;
//    }
//
//    void change(vector<vector<vector<int>>>& pre, vector<vector<vector<int>>>&cur, int c1, int c2, int u) {
//        if (map[u].empty()) return;
//        int pc1 = map[u][n], pc2 = map[u][n + 1];
//        if (pc1 > c1 || pc2 > c2) return;
//        // 当前行不安排任何人 那么前置状态直接继承
//        cur[0][c1][c2] = max(cur[0][c1][c2], pre[u][c1][c2]);
//        res = max(res, cur[0][c1][c2]);
//        // 枚举当前状态
//        for (int s = full; s; s = (s - 1) & full) {
//            if (map[s].empty()) continue;
//            int cc1 = map[s][n], cc2 = map[s][n + 1];
//            if (cc1 + pc1 > c1 || cc2 + pc2 > c2) continue;
//            if (pre[u][c1 - cc1][c2 - cc2] != -1)
//                cur[s][c1][c2] = max(cur[s][c1][c2], pre[u][c1 - cc1][c2 - cc2] + add[u][s]);
//            res = max(res, cur[s][c1][c2]);
//        }
//    }
//
//    // 二进制的00表示没人 01表示有内向的人 10表示有外向的人 11表示不合法
//    vector<int> check(int s) {
//        vector<int> arr(n + 2);
//        for (int mask = 3, i = 0; i < n; i++) {
//            int t = (mask & s) >> (i * 2);
//            if (t == 1) arr[i] = 1, arr[n]++;
//            if (t == 2) arr[i] = 2, arr[n + 1]++;
//            if (t == 3) return {};
//            mask <<= 2;
//        }
//        return arr;
//    }
//
//    int make_add(vector<int> &pre, vector<int> &cur) {
//        int sum = cur[n] * 120 + cur[n + 1] * 40;
//        for (int i = 0; i < n; i++) {
//            if (cur[i] == 0) continue;
//            int cnt = count(pre, cur, i);
//            if (cur[i] == 1) sum -= cnt * 30;
//            if (cur[i] == 2) sum += cnt * 20;
//            if (pre[i] == 0) continue;
//            if (pre[i] == 1) sum -= 30;
//            if (pre[i] == 2) sum += 20;
//        }
//        return sum;
//    }
//
//    int count(vector<int> &pre, vector<int> &cur, int i) {
//        int cnt = pre[i] ? 1 : 0;
//        return cnt + (i - 1 >= 0 && cur[i - 1]) + (i + 1 < n && cur[i + 1]);
//    }

/*
 * 用三进制表示状态 注意状态枚举方式变化
 */
    int n, full, res = 0;
    vector<vector<int>> add, map;
    int getMaxGridHappiness(int m, int n, int ic, int ec) {
        if (n > m) swap(n, m);
        this->n = n;
        this->full = (int) pow(3, n) - 1;
        map.assign(full + 1, {}); // 状态对应的 排列信息
        for (int s = 0; s <= full; s++)
            map[s] = check(s);
        // 缓存新增一行时 幸福度的变化
        add = vector(full + 1, vector(full + 1, 0));
        for (int s = 0; s <= full; s++) {
            for (int u = 0; u <= full; u++)
                add[s][u] = make_add(map[s], map[u]);
        }
        vector<vector<vector<vector<int>>>> dp(m + 1, vector(full + 1, vector(ic + 1, vector(ec + 1, -1))));
        dp[0][0][0][0] = 0;
        for (int i = 1; i <= m; i++) {
            vector<vector<vector<int>>> &pre = dp[i - 1], &cur = dp[i];
            for (int c1 = 0; c1 <= ic; c1++) {
                for (int c2 = 0; c2 <= ec; c2++) {
                    for (int u = 0; u <= full; u++)  // 枚举前置状态
                        change(pre, cur, c1, c2, u);
                }
            }
        }
        return res;
    }

    void change(vector<vector<vector<int>>> &pre, vector<vector<vector<int>>> &cur, int c1, int c2, int u) {
        int pc1 = map[u][n], pc2 = map[u][n + 1];
        if (pc1 > c1 || pc2 > c2) return;
        // 枚举当前状态
        for (int s = 0; s <= full; s++) {
            int cc1 = map[s][n], cc2 = map[s][n + 1];
            if (cc1 + pc1 > c1 || cc2 + pc2 > c2) continue;
            if (pre[u][c1 - cc1][c2 - cc2] != -1)
                cur[s][c1][c2] = max(cur[s][c1][c2], pre[u][c1 - cc1][c2 - cc2] + add[u][s]);
            res = max(res, cur[s][c1][c2]);
        }
    }

    // 3进制的0表示没人 1表示有内向的人 2表示有外向的人
    vector<int> check(int s) {
        vector<int> arr(n + 2);
        for (int i = 0; i < n; i++) {
            int t = s % 3;
            if (t == 1) arr[i] = 1, arr[n]++;
            if (t == 2) arr[i] = 2, arr[n + 1]++;
            s /= 3;
        }
        return arr;
    }

    int make_add(vector<int> &pre, vector<int> &cur) {
        int sum = cur[n] * 120 + cur[n + 1] * 40;
        for (int i = 0; i < n; i++) {
            if (cur[i] == 0) continue;
            int cnt = count(pre, cur, i);
            if (cur[i] == 1) sum -= cnt * 30;
            if (cur[i] == 2) sum += cnt * 20;
            if (pre[i] == 0) continue;
            if (pre[i] == 1) sum -= 30;
            if (pre[i] == 2) sum += 20;
        }
        return sum;
    }

    int count(vector<int> &pre, vector<int> &cur, int i) {
        int cnt = pre[i] ? 1 : 0;
        return cnt + (i - 1 >= 0 && cur[i - 1]) + (i + 1 < n && cur[i + 1]);
    }
};

int main() {
    Solution s;

    cout << 0 << endl;
}