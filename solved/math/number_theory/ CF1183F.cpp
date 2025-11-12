/**
 * @Time : 2024/5/16-10:05 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1183F 贪心 + 数论
 */
/*
 * 选最多三个数 相同的数肯定不能选
记最大的数为a
1. 1个数的方案 拿最大值
2. 2个数的方案 一定有一个数是a。如果最终选出来的答案是b和c  b > c
如果b和c都不是a的因子 将c替换为a 答案更大
如果b与c只有一个是a的因子 将那一个替换为a 答案更大
如果b和c都是a的因子 那么b和c最大是 a / 2, a / 3  b+c < a
不如拿a 再找一个别的a的非因子 找不到就退化为只拿一个数的方案
3. 3个数的方案 如果选出来的数是bcd  b > c > d
如果三个数都不是a的因子 选最小的那个 然后替换为a
如果三个数中只有一个是a的因子 将那一个替换为a
如果三个数中有两个数是a的因子 假设是最大的两个因子 a / 2, a / 3
b + c = 5a/6 < a 直接将b和c去掉 换为a   a + d > b + c + d
如果三个数都是a的因子 假设是可能的最大的三个因子 a / 2, a / 3, a / 5
（注意 a/4不可以，因为存在a/2，不然bcd三个数中有两个数本身就不满足条件）
b + c + d = 5a/6 + a/5 > a 这种情况可以不选择a
但如果三个因子是 a / 2, a / 3, a / 7 < a 可以直接选择a更好

因此除了特殊情况三个因子 a / 2, a / 3, a / 5，一定要拿最大值
选取最大值a后 将a的因子全删掉 那么剩下的数还能选择2个 退化为2的情况
 *
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, k;
set<int> nums;

void remove(int num) {
    for(int i = 1; i <= (int)sqrt(num); i++) {
        if(num % i == 0) {
            if(nums.count(i)) nums.erase(nums.find(i));
            if(nums.count(num / i)) nums.erase(nums.find(num / i));
        }
    }
}

void solve() {
    int a = *nums.rbegin(), ans = a;
    if(a % 2 == 0 && nums.count(a / 2) &&
       a % 3 == 0 && nums.count(a / 3) &&
       a % 5 == 0 && nums.count(a / 5))
        ans = a / 2 + a / 3 + a / 5;
    remove(a); // 删掉最大值的所有因子后 剩余数中找一个最大值 就是两个数方案
    if(!nums.empty()) {
        int b = *nums.rbegin(), temp = a + b; // 两个数的最大方案
        ans = max(ans, temp);
        remove(b); // 在三个数的方案中 b是剩余数的最大值 也必须 然后将其的所有因子也删除
        if(!nums.empty()) ans = max(ans, temp + *nums.rbegin());
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        nums.clear();
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            nums.insert(num);
        }
        solve();
    }
};