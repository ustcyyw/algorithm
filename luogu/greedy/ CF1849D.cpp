/**
 * @Time : 2024/6/3-7:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1849D 贪心 双指针
 */
 /*
  * 数字0将整个数组分为多个部分
  * 只要某一个部分中存在2 选择2消费一个硬币 后续就可以双向扩散 将边缘的两个0都变为红色
  * 只要某一个部分只有1 选择1消费一个硬币 可以单向扩散 将边缘的1个0变红色
  * 注意不要将同一个0变两次红色 因为可能这个0的左边和右边都是有数字的
  * 比如 21011
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, MV = 1e9;
typedef long long ll;
int T, n, nums[N], marked[N];

void solve() {
    int ans = 0;
    for(int i = 1, j; i <= n; i = j) {
        while(i <= n && nums[i] == 0) i++;
        if(i > n) break;
        j = i;
        int a = 0;
        while(j <= n && nums[j] != 0) {
            if(nums[j] == 2) a = 1;
            j++;
        }
        int b = (i != 1) + (j - 1 != n); // 端点0的个数
        if(a + 1 > 0 && b > 0 && i > 1 && !marked[i - 1])
            marked[i - 1] = 1, a--, b--;
        if(a + 1 > 0 && b > 0 && j <= n)
            marked[j] = 1;
        ans++;
    }
    for(int i = 1; i <= n; i++)
        if(marked[i] == 0 && nums[i] == 0) ans++;
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    solve();
};