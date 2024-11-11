/**
 * @Time : 2023/9/15-4:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1.5e6 + 5;
int n, m, nums[N];

long long solve() {
    vector<int> cnt(n + 1, 0);
    set<int> set;
    for(int i = 0; i <= n; i++)
        set.insert(i);
    int res = INT_MAX, l = 0, r = 0;
    while (r < n) {
        int num = nums[r];
        cnt[num]++;
        if(cnt[num] == 1) set.erase(set.find(num));
        if(r - l + 1 > m) {
            int t = nums[l++];
            if(--cnt[t] == 0) set.insert(t);
        }
        if(r - l + 1 == m) res = min(res, *set.begin());
        r++;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        cin >> nums[i];
    cout << solve() << endl;
}