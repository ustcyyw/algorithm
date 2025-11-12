/**
 * @Time : 2023/12/1-10:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 总和是sum

其它球最大是 sum - t
最少是 n - 1

不可能的情况
1. 其它骰子都取最小 这个骰子取的数还是让和大于s: a + n - 1 > s
a > s - n + 1     a >= max(1, s - n + 2)
1. 其它骰子都取最大 这个骰子取的数还是让和小于s：a + sum - t < s
a < s - sum + t   a <= min(t, s - sum + t - 1)
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
long long nums[N], n, s;

int main() {
    cin >> n >> s;
    long long sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
        sum += nums[i];
    }
    for(int i = 1; i <= n; i++) {
        long long lo = max(1ll, s - n + 2), hi = min(nums[i], s - sum + nums[i] - 1);
        int res = 0;
        if(nums[i] >= lo) res += nums[i] - lo + 1;
        if(hi >= 1) res += hi;
        cout << res << endl;
    }
    return 0;
}