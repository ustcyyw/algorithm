/**
 * @Time : 2024/1/22-8:15 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛381 t4
 */

/*
 * 可以将一个点 到达其它点的情况分类讨论
 * 0. 特殊地，x = y 或者 x + 1 = y 等价于所有点是一条链 直接可以得出答案
 *
 * 1. i <= x：可以分为4个部分
 * 1a.[1, i-1] 由i向左依次到达
 * 1b.[y, n] 由i走到x然后跳到y，依次向右到达
 * 1c.[i + 1, mid] 由i向右依次到达
 * 1d.[mid + 1, y - 1] 由i到达x后跳到y，依次向左到达
 * 其中mid满足 mid - i <= x - i + 1 + y - (mid + 1) = x - i + y - mid
 * 2 * mid <= x + y, 因此 mid = (x + y) / 2
 *
 * 由情况1的讨论发现 对于指定的起点i 到达四部分点 距离是连续的
 * 最远距离d2确定，点的个数确定 那么就能确定出最短距离d1。
 * 那么[d1, d2]这个距离的点对数量都+1。区间加 差分算法
 *
 * 于是只需要将剩下两种大情况讨论清楚即可
 * 2. i >= y 与1类似
 * 3. x + 1 <= i <= y - 1
 * 有6种分支case
 * 3a.[1, x - 1] i以距离最短的方式到达x 再向左走
 * 3b.[x, m1 - 1] i以距离最短的方式到达x 再向右走
 * 3c.[m1, i - 1] i直接向左走
 * m1是3b和3c的分界线 求法与情况1中的mid类似 通过距离列等式
 * 3d.[i + 1, m2] i直接向右走
 * 3e.[m2 + 1, y - 1] i以距离最短的方式到达y 再向左走
 * m2是3d和3e的分界线
 * 3f.[y, n] i以距离最短的方式到达y 再向右走
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    int n, x, y;
    vector<ll> diff;
    vector<long long> countOfPairs(int n, int x, int y) {
        if(abs(x - y) <= 1) return sp_case(n);
        diff.assign(n + 2, 0ll);
        if(x > y) swap(x, y);
        this->n = n, this->x = x, this->y = y;
        case1(); case2(); case3();
        vector<ll> res;
        ll sum = 0;
        for(int i = 1; i <= n; i++) {
            sum += diff[i];
            res.push_back(sum);
        }
        return res;
    }
    // 最长长度为len，并且有cnt个点 对答案的贡献 长度 [len - cnt + 1,len]上的点对都+1
    void range_add(int cnt, int len) {
        diff[len - cnt + 1]++, diff[len + 1]--;
    }
    // 针对x及其左边的点的处理
    void case1() {
        int mid = (x + y + 1) / 2;
        for(int i = 1; i <= x; i++) {
            range_add(i - 1, i - 1); // i左边的点 [1, i - 1]
            range_add(mid - i, mid - i); // 点[i + 1, mid]
            range_add(y - 1 - mid, x - i + 1 + y - (mid + 1)); // 点[mid + 1, y - 1]
            range_add(n - y + 1, x - i + 1 + n - y); // [y, n]
        }
    }
    // 针对y及其右边的点的处理
    void case2() {
        int mid = (x + y - 1) / 2;
        for(int i = n; i >= y; i--) {
            range_add(n - i, n - i); // [i + 1, n]
            range_add(i - 1 - mid, i - 1 - mid); // [mid + 1, i - 1]
            range_add(mid - x, mid - x + 1 + i - y); // [x + 1, mid]
            range_add(x, i - y + 1 + x - 1); // [1, x]
        }
    }

    void case3() {
        for(int i = x + 1; i <= y - 1; i++) {
            int dx = min(i - x, y - i + 1), dy = min(y - i, i - x + 1);
            int m1 = (x + i - dx + 2) / 2, m2 = (i + dy + y - 1) / 2;
            range_add(x - 1, dx + x - 1); // [1, x - 1]
            range_add(m1 - x, dx + m1 - 1 - x); // [x, m1 - 1]
            range_add(i - m1, i - m1); // [m1, i - 1]
            range_add(m2 - i, m2 - i); // [i + 1, m2]
            range_add(y - 1 - m2, dy + y - m2 - 1); // [m2 + 1, y - 1]
            range_add(n - y + 1, dy + n - y); // [y, n]
        }
    }

    vector<ll> sp_case(int n) {
        vector<ll> res;
        for(int i = n - 1; i >= 0; i--)
            res.push_back(2 * i);
        return res;
    }
};