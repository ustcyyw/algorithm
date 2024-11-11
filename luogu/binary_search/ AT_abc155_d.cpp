/**
 * @Time : 2023/12/18-8:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 二分答案
 * 要找最小的num，小于等于num的元素数量为cnt，且保证cnt >= k
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
long long n, k, arr[N];

int search1(long long num, long long a, int i) {
    int lo = i + 1, hi = n;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(a * arr[mid] > num) lo = mid + 1;
        else hi = mid;
    }
    return n - lo;
}

int search2(long long num, long long a, int i) {
    int lo = i, hi = n - 1;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(a * arr[mid] <= num) lo = mid;
        else hi = mid - 1;
    }
    return lo - i;
}
// 检查小于等于num的数的个数是否 >= k
bool check(long long num) {
    long long cnt = 0;
    for(int i = 0; i < n; i++) {
        cnt += arr[i] >= 0 ? search2(num, arr[i], i) : search1(num, arr[i], i);
        if(cnt >= k) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n);
    long long lo = -1e18, hi = 1e18;
    while(lo < hi) {
        long long mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << endl;
}