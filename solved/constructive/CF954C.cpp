/**
 * @Time : 2025/3/19-8:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * cur > pre，向右或者向下
  * cur < pre，向左或者向上
  * 相差全为1 那可以直接考虑n行1列的矩阵
  * 否则 非1的差值只能出现一次 就代表了有多少列
  *
  * 还要注意确定了行列之后 整个过程中没有走出过边界
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 15, mod = 1e9 + 7;
int T, n, nums[N], ans = -1;

bool solve() {
    int diff = 0;
    for(int i = 2; i <= n; i++) {
        if(nums[i] == nums[i - 1]) return false;
        diff = max(diff, abs(nums[i] - nums[i - 1]));
    }
    if(diff == 1) {
        ans = 1;
        return true;
    }
    int row = 0, col = 0;
    int ml = INT_MAX, mr = 0, mu = INT_MAX, md = 0;
    for(int i = 2; i <= n; i++) {
        diff = nums[i] - nums[i - 1];
        if(abs(diff) == 1) {
            col += diff;
        } else {
            if(ans == -1) ans = abs(diff);
            else if(ans != abs(diff)) return false;
            row += diff < 0 ? -1 : 1;
        }
        ml = min(ml, col), mu = min(mu, row);
        mr = max(mr, col), md = max(md, row);
    }
    int x = nums[1] % ans == 0 ? nums[1] / ans : nums[1] / ans + 1, y = nums[1] % ans;
    if(y == 0) y = ans;
    return x + mu >= 1 && y + ml >= 1 && y + mr <= ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    if(solve()) {
        if(ans == -1) ans = (int)1e9;
        cout << "YES\n" << (int)1e9 << " " << ans;
    } else cout << "NO";
}