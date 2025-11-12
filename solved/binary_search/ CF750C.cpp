/**
 * @Time : 2023/12/11-12:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 但凡有参加div2 分数就是有限的
 *
 * 如果某个分数 在判定过程中发现是太高了 参加了div2导致不可能 那就降低分数
 *
 * 如果是太低了 参加了div1导致不可能 就升高分数
 * 如果这个分数通过验证 那就试试比他高的分数
 *
 * 对初始分数二分答案 但注意最后得到一个分数后 再看看是否可以
 * 最后再由初始分数算出最后分数
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5, T = 1900;
int n, point[N], type[N];

int check(int p) {
    for(int i = 0; i < n; i++) {
        if(p >= T && type[i] == 2) return -1; // 表示分数太高了 但是参加了div2
        if(p < T && type[i] == 1) return 1; // 表示分数太低了 但是参加了div1
        p += point[i];
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    int two = 0;
    for(int i = 0; i < n; i++) {
        cin >> point[i] >> type[i];
        if(type[i] == 2) two++;
    }
    if(two == 0) {
        cout << "Infinity" << endl;
        return 0;
    }
    int lo = -100 * N, hi = 100 * N;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1, flag = check(mid);
        if(flag >= 0) lo = mid;
        else hi = mid - 1;
    }
    if(check(lo) == 0) {
        for(int i = 0; i < n; i++)
            lo += point[i];
        cout << lo << endl;
    }
    else cout << "Impossible" << endl;
}