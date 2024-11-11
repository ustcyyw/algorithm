/**
 * @Time : 2024/4/19-9:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 翻转的区间上 正序列对会变成逆序对，逆序对会变成正序对
 * 假设翻转的区间[l,r] 总共有total个数对 原本逆序对有c个 那么原本的正序对有t - c个
 * 翻转后 逆序对有t - c个，正序对有c个。
 * 针对这一区间而言 逆序对的变化数量 = after - before = t - c - c
 * 但是这个区间外的逆序对数量不变 （[1,l-1]和[l,r]上数的大小关系和想对位置不变，[r+1,n]也同理）
 * 因此整个排列的逆序对数量变化 after - before = t - 2c
 * after = before + t - 2c
 * 2c一定是偶数，那么变换后的数量是奇数还是偶数 就只取决于上一次是奇数还是偶数，以及t的奇偶性
 * 和该区间原本的逆序对个数无关，因此不用关注c具体是多少
 * 如果before和t是两奇数或两偶，那么after是偶数
 * 否则before和t是一奇数一偶数，那么after是奇数
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, m, nums[1505];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    int base = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < i; j++) {
            if(nums[j] > nums[i]) base++;
        }
    }
    int before = base % 2; // 初始时候逆序对数量对奇偶性
    cin >> m;
    for(int i = 1, l, r; i <= m; i++) {
        cin >> l >> r;
        int len = r - l + 1, t = (len - 1) * len / 2 % 2;
        int after = (t + before) % 2;
        cout << (after ? "odd" : "even") << "\n";
        before = after;
    }
};