/**
 * @Time : 2025/1/20-1:01 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 必须要左边触发一下 才可以任意选择 但是具体先选择哪个数不确定
 * 枚举第一次从左边开始移动并选择的数 可用值要减去 nums[i] + i
 * 然后还剩的可用值 就可用从左边、右边任意取数 那肯定是先拿代价小的数
 * 同一个数 从左拿、从右拿 代价是确定的 取代价小的那种方式
 * 然后将这些数的代价排序 处理前缀和
 * 这样在已知可用值的时候 用二分就能知道可以取几个数
 * 但是要注意 如果二分出的取数范围 包括了当前枚举的nums[i]的选取代价
 * 就需要补上这个选取代价再二分一次
 * 因为枚举这个数的时候 它的选取代价已经计算过了
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7, R = 26;
int T, n, c, nums[N], mp[N];
vector<vector<int>> vals;
vector<ll> sum;

ll cal(int cost, int i) {
    int idx = mp[i];
    int j = upper_bound(sum.begin(), sum.end(), cost) - sum.begin() - 1;
    if(idx > j) return j + 1; // 这里加1是加上第一次选取了的数
    cost += vals[idx][0];
    return upper_bound(sum.begin(), sum.end(), cost) - sum.begin() - 1;
}

ll solve() {
    sort(vals.begin(), vals.end());
    sum.assign(n + 1, 0);
    for(int i = 1; i <= n; i++) {
        sum[i] = vals[i - 1][0] + sum[i - 1];
        mp[vals[i - 1][1]] = i - 1; // 记录原位置在排序后的位置
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) { // 枚举第一次操作要拿的数
        if(nums[i] + i > c) continue;
        ans = max(ans, cal(c - (nums[i] + i), i));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n >> c;
        vals = {};
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            vals.push_back({nums[i] + min(i, n + 1 - i), i});
        }
        cout << solve() << "\n";
    }
};