/**
 * @Time : 2024/11/25-4:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1490E 二分答案 1400
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, nums[N], arr[N];

bool check(int idx) {
    for(ll sum = 0, i = 1; i <= n; i++) {
        if(i <= idx) sum += nums[i];
        else {
            if(sum < nums[i]) return false;
            sum += nums[i];
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            arr[i] = nums[i];
        }
        sort(nums + 1, nums + n + 1);
        int lo = 1, hi = n;
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            if(!check(mid)) lo = mid + 1;
            else hi = mid;
        }
        cout << n - lo + 1 << "\n";
        int val = nums[lo];
        for(int i = 1; i <= n; i++)
            if(arr[i] >= val) cout << i << " ";
        cout << "\n";
    };
};