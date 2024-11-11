/**
 * @Time : 2024/7/15-1:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1593D2 数学 数论 dp
 */
 /*
  * 要让两个数多次减去一个k变得相等 那么这两个数一定关于k同余
  * 题目的意思就是找到至少n / 2个数 关于k同余 找最大的k
  *
  * 最后相等的那个值，一定是数组中的某个数 因为减到比他更小的数没意义 无非就是所有选出来的数再多一次减操作
  * 因此可以排序后枚举相等的值 则选取的数一定是是比它大的数
  * 这样要减少的差值就确定了，加上这个所枚举的数 还要再找n / 2 - 1个数
  * 这些减少的差值的gcd就是要找的答案 因为这个gcd的整数次求和 刚好能等于各个差值
  * 于是定义 dp[i][j]：截止第i个差值，已经选取了j个值的gcd的情况（是一个set）
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, nums[45], ans = -1;
map<int, int> mp;

void cal(vector<int>& arr) {
    int m = arr.size();
    set<int> dp[45][45];
    for(int i = 1; i < m - 1; i++) {
        int num = arr[i + 1];
        dp[i][1].insert(arr[i]);
        for(int j = 1; j <= i; j++) {
            for(int other : dp[i][j]) {
                dp[i + 1][j].insert(other);
                dp[i + 1][j + 1].insert(gcd(num, other));
            }
        }
    }
    dp[m - 1][1].insert(arr[m - 1]);
    for(int j = n / 2 - 1; j < m; j++) {
        for(int num : dp[m - 1][j])
            ans = max(ans, num);
    }
}

int solve() {
    for(auto& p : mp) {
        if(p.second >= n / 2)
            return -1;
    }
    sort(nums + 1, nums + n + 1);
    for(int i = 1; i <= n / 2 + 1; i++) {
        vector<int> arr(1, 0);
        for(int j = i + 1; j <= n; j++)
            arr.push_back(nums[j] - nums[i]);
        cal(arr);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        mp = {};
        ans = -1;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            mp[nums[i]]++;
        }
        cout << solve() << "\n";
    }
};