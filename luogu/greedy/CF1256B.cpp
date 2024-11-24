/**
 * @Time : 2024/11/23-2:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1256B 贪心 模拟 1400
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, nums[N];

int find_min(int lo) {
    int idx = -1, val = INT_MAX;
    for(int i = lo; i <= n; i++) {
        if(nums[i] < val)
            val = nums[i], idx = i;
    }
    return idx;
}

void swap(int lo, int hi) {
    int last = nums[hi];
    for(int i = hi; i > lo; i--)
        nums[i] = nums[i - 1];
    nums[lo] = last;
}

void solve() {
    for(int i = 1; i <= n;) {
        int idx = find_min(i);
        if(idx == i) {
            i++;
            continue;
        }
        swap(i, idx);
        i = idx;
    }
    for(int i = 1; i <= n; i++)
        cout << nums[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};