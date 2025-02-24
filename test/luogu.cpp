/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
 /*
  * 假设分组中 较小的数字是num
  * ai / num = c1,  ai % num = c2
  * 最终答案 ans = sum {ai / (num + 1) + (ai % (num + 1) > 0)}
  * 也就是说用num + 1尝试去分组 如果刚好除尽 那么组数 ai / (num + 1)，对于ai来说所有组都是num + 1
  * 否则还多出ai % (num + 1)，就只能再多一组了 这种情况对于ai来说，分为num, num + 1的两类
  * 这样计算的要求是 c1 >= c2
  * 要找到一个最大的num 使得上述要求对于所有i都成立
  *
  * 假设将a排序后，a[1]就是最小的数，对于a[1], sqrt(a[1])可以保证 c11 >= c12
  * 因为sqrt(a[1])作为除数，保证了除的结果c11 >= sqrt(a[1]), 而余数 c12 < sqrt(a[1])
  * 而对于其它ai，由于ai >= a1, 所以除的结果ci1 >= sqrt(a[1]), 余数 ci2 < sqrt(a[1])
  * 依旧可以保证 ci1 >= ci2
  * 因此num至少为sqrt(a[1])
  *
  * 再来看是否有更大的num满足要求
  * 对于a1来说 考虑i为除数 i * c1 + c2 = a1，会有两种情况
  * 1.c1 >= c2
  * c2 = ai % i, 所以 i > c2的
  * 那么换成 c1 = a1 / i 作为除数，商为i，余数依旧是c2，也满足条件
  * 特别注意 当c2为0时，不仅可以换c1为除数 c1 - 1 一样满足条件
  * 2.c1 < c2 （不满足条件的情况）
  * 已知 i > c2， 所以是 i > c2 > c1 在case1中已经计算过了 就不用再考虑
  *
  * 因此对于a1，枚举i找可能的num 范围只需要在 [1,sqrt(a1)]即可
  * 可能的num为 i, a1 / i, a1 / i - 1
  * （这些都可以通过暴力算几个数来找到规律）
  * 已经在前面说明num的一个可能值是sqrt(a1)，因次i就不用管了
  * 还可能的num值就是 a1 / i, a1 / i - 1
  * a1 / i, a1 / i - 1是否为可能的num，就看对于所有的ai是否满足c1 >= c2的条件即可
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