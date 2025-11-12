/**
 * @Time : 2025/2/24-1:08 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF792E 2500 数学 数论 找规律
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5, M = 400;
int n, nums[505];

bool check(int num) {
    if(num == 0) return 0;
    for(int i = 1; i <= n; i++) {
        if(nums[i] / num < nums[i] % num)
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    sort(nums + 1, nums + n + 1);
    int base = (int)sqrt(nums[1]);
    for(int i = 1; i <= sqrt(nums[1]); i++) {
        if(check(nums[1] / i)) { // 随着i增加, nums[1] / i减小 因此找到第一个之后就可以不用再找了
            base = max(base, nums[1] / i);
            break;
        }
        if(check(nums[1] / i - 1)) base = max(base, nums[1] / i - 1);
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        int c1 = nums[i] / (base + 1), c2 = nums[i] % (base + 1);
        ans += (c1 + (c2 > 0));
    }
    cout << ans << "\n";
};