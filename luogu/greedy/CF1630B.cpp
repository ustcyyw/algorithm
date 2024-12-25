/**
 * @Time : 2024/12/25-12:56 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1630B 1800 贪心 双指针 构造
 */
 /*
  * k段 每段范围内的数要绝对多
  * 范围内的数为cnt,那么范围外的数最多为cnt-k个
  * 满足要求的情况下 让范围内的数尽可能地少，这样y-x会尽可能地小
  * cnt + cnt - k = n, cnt = (n + k) / 2
  * 举一些例子发现cnt是向上取整
  * 于是将原数组进行排序 枚举相邻的cnt个数在范围内 就能定出x和y
  * 然后根据x和y划分数组 每当数组中范围内的数多1个 就分出一个数组
  * 按照xy的求法 这样是一定能分够k组的
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, k, nums[N], arr[N];

void solve() {
    sort(arr + 1, arr + n + 1);
    int m = (n + k + 1) / 2, diff = INT_MAX, x, y;
    for(int i = 1, j = i + m - 1; j <= n; i++, j++) {
        int temp = arr[j] - arr[i];
        if(diff > temp)
            diff = temp, x = arr[i], y = arr[j];
    }
    cout << x << " " << y << "\n";
    int i = 1, j, cnt;
    while(k > 1) {
        j = i, cnt = 0;
        while(j <= n && cnt < 1) {
            cnt += nums[j] >= x && nums[j] <= y ? 1 : -1;
            j++;
        }
        cout << i << " " << j - 1 << "\n";
        k--, i = j;
    }
    cout << i << " " << n << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            arr[i] = nums[i];
        }
        solve();
    }
};