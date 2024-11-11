/**
 * @Time : 2024/6/30-5:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1851D 构造
 */
 /*
  * 根据前缀和相邻元素之差（注意特殊的首项）
  * 能得到n-1个数，并且这些差要么就是原本1～n之间的数 要么其中两个数之和
  * 差序列至少有n-2个数是原[1,n]之间的数
  * 重复出现的数或者不在[1,n]之间的数最多只有1个
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
ll T, n, nums[N], marked[N], sum;

bool solve() {
    for(int i = 1; i < n; i++) {
        ll num = nums[i] - nums[i - 1];
        if(num > n || marked[num]) {
            if(sum != -1) return false;
            sum = num;
        } else marked[num] = 1;
    }
    if(sum == -1) return true;
    for(int i = 1; i <= n; i++)
        if(!marked[i]) sum -= i;
    return sum == 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        fill(marked + 1, marked + 1 + n, 0);
        sum = -1;
        for(int i = 1; i < n; i++)
            cin >> nums[i];
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};