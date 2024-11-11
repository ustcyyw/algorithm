/**
 * @Time : 2024/4/23-9:01 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, M = 1e6 + 5;
ll n, m, nums[N], cnt[M];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    vector<int> res;
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
        sum += nums[i], cnt[nums[i]]++;
    }
    for(int i = 1; i <= n; i++) {
        int num = nums[i];
        sum -= num, cnt[num]--;
        if(sum % 2 == 0 && sum / 2 < M && cnt[sum / 2] > 0)
            res.push_back(i);
        sum += num, cnt[num]++;
    }
    cout << res.size() << "\n";
    for(int idx : res)
        cout << idx << " ";
};