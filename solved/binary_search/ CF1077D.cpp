/**
 * @Time : 2024/4/23-9:26 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll n, k, nums[N], cnt[N];

bool check(int t) {
    int sum = 0;
    for(int i = 1; i < N; i++) {
        sum += cnt[i] / t;
        if(sum >= k) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
        cnt[nums[i]]++;
    }
    int lo = 1, hi = n / k;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    for(int i = 1, tk = 0; i < N && tk < k; i++) {
        while(cnt[i] >= lo && tk < k) {
            cout << i << " ";
            cnt[i] -= lo;
            tk++;
        }
    }
};