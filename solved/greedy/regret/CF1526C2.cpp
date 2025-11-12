/**
 * @Time : 2024/3/6-4:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 反悔贪心 如果要选择相同数量的负数 将最小的抛弃 这样尽可能会让前缀和大
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
int n, T, nums[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    priority_queue<int, vector<int>, greater<>> pq;
    ll neg_sum = 0, pos_sum = 0, pos = 0, res = -1;
    for(int i = 0, num; i < n; i++) {
        cin >> num;
        if(num >= 0) pos++, pos_sum += num;
        else {
            pos_sum += num, pq.push(num);
            if(pos_sum + neg_sum < 0) pos_sum -= pq.top(), pq.pop();
        }
        res = max(res, pos + (ll)pq.size());
    }
    cout << res << "\n";
};