/**
 * @Time : 2023/12/14-8:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 异或 1 + 0 = 0 + 1 = 1， 0 + 0 = 1 + 1 = 0
 * 有数位重叠 异或就会小于数组的和 因此要找二进制位不出现重叠的子数组
 * 可以二分也可以滑动窗口
 */

#include<bits/stdc++.h>
using namespace std;
//const int N = 2e5 + 5;
//int n, a[N], sum[N], x[N];
//
//int search(int i) {
//    int lo = 1, hi = i;
//    while(lo < hi) {
//        int mid = (lo + hi) >> 1;
//        if(sum[i] - sum[mid - 1] == (x[i] ^ x[mid - 1])) hi = mid;
//        else lo = mid + 1;
//    }
//    return lo;
//}
//
//long long solve1() {
//    cin >> n;
//    for(int i = 1; i <= n; i++) {
//        cin >> a[i];
//        sum[i] = sum[i - 1] + a[i];
//        x[i] = x[i - 1] ^ a[i];
//    }
//    long long res = 0;
//    for(int i = 1; i <= n; i++) {
//        int lo = search(i);
//        res += i - lo + 1;
//    }
//    return res;
//}

const int N = 2e5 + 5;
int n, a[N];
long long solve2() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    long long res = 0, sum = 0, x = 0;
    for(int l = 1, r = 1; r <= n; r++) {
        sum += a[r], x ^= a[r];
        while(sum != x) {
            sum -= a[l], x ^= a[l];
            l++;
        }
        res += r - l + 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cout << solve2() << endl;
}
