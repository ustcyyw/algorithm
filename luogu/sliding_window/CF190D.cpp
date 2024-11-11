/**
 * @Time : 2024/1/30-3:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5;
int n, k, nums[N];

void solve() {
    int lo = 0, hi = 0;
    long long res = 0;
    unordered_map<int, int> map;
    while(hi < n) {
        int num = nums[hi];
        map[num]++;
        while(map[num] >= k) {
            res += n - 1 - hi + 1;
            map[nums[lo++]]--;
        }
        hi++;
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 0; i < n; i++)
        cin >> nums[i];
    solve();
};