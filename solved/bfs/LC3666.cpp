/**
 * @Time : 2025/10/25-10:09
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3666 2476 bfs set运用
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;
/*
 * 当固定0的数量为c0时，1的数量为n - c0 此时选择k个元素进行翻转
 * 0最多可以选 cr = min(k, c0)
 * 最少得选cl = max(0, k - (n - c0)), 得保证选的1的数量不超过 n - c0
 * 0的数量在[cl,cr]上，会发现选择之后0的数量变化是以2为间隔连续的
 * 那么c0是偶数，就会变成一系列连续的偶数；c0是奇数就会变成一系列连续的奇数
 * 因为这个连续性，只要确定边界，就知道了一次选择，0数量变化的可能性
 * 记0数量变化的值区间为[lo, hi]
 *
 * 求最小操作次数，将0的数量当作状态，可以使用dfs，关键是检查哪些状态已经访问过
 * 反向思维：一般情况下是标记哪些值已经访问过
 * 在本题中，利用变化值的连续性，可以维护哪些值没有访问过
 * 将没有访问过的值并且在区间[lo,hi]上的添加到队列中
 *
 * 那么问题转化为 从一堆数里面，找到值位于区间[lo, hi]上的数
 * 保持数有序，在这些数中二分查找lo应该插入的位置，然后再判断lo的下一个数与hi的关系
 * 并且还要能快速移除单个数，并保持有序性，使用set
 */
class Solution {
public:
    int minOperations(string s, int k) {
        int start = 0, step = 0, n = s.size();
        set<int> st1, st2;
        for(int i = 0; i < n; i++) {
            if(s[i] == '0') start++;
            if(i % 2 == 0) st2.insert(i);
            else st1.insert(i);
        }
        if(start == 0) return 0;
        queue<int> queue;
        queue.push(start);
        while(!queue.empty()) {
            step++;
            int sz = queue.size();
            while(sz--) {
                int c0 = queue.front(); queue.pop();
                int cl = max(0, k - (n - c0)), cr = min(k, c0);
                int dl = cl - (k - cl), dr = cr - (k - cr);
                int hi = c0 - dl, lo = c0 - dr;
                if(lo == 0) return step;
                add(queue, lo % 2 == 1 ? st1 : st2, lo, hi);
            }
        }
        return -1;
    }

    void add(queue<int>& queue, set<int>& st, int lo, int hi) {
        if(lo > hi) return ;
        while(true) {
            auto it = st.lower_bound(lo);
            if(it == st.end() || *it > hi) return;
            queue.push(*it), st.erase(it);
        }
    }
};