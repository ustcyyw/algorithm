/**
 * @Time : 2025/5/30-14:08
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2114G 2200 构造 前后缀分解 贪心
 */
 /*
  * 相同两个数合成一个大的，所以给定一个数 它最多经过多少次合并得到
  * 就是用这个数一直除以2，直到无法再被2整除，然后剩下的那个值 就是用于合并的最小值
  * 比如16，用于合并的最小值是1；10，用于合并的最小值5
  * 确定了合并的最小值，每次都插入最小值来进行合并，就得到了最大操作次数mv
  * 每个数的操作次数为[1, mv]中任意一个数
  * 比如要得到16
  * 操作1次 就是直接插入16
  * 操作2次 插入两个8
  * 操作3次 插入1个8，两个4
  * 操作5次 插入1个8，1个4，1个2，2个1
  * ...
  * 操作16次 每次插入1个1
  * 是否可以构造出来 也可以用相似的思路 最少当然是直接操作n次
  * 最多 就看构造出每个数都用最多次来构造，总操作次数是否 >= k，是则可以构造成功
  *
  * 但是每个数可以多少次操作得到 并不是独立的 和插入顺序有关
  * 比如 5和10
  * 先插入左边的5，右边的10就只能直接插入
  * 但是可以先插入两个5 合成右边的10 然后再插入左边的5
  * 由于只可以在队列首尾插入 枚举第一个构造出的数 其余数的生成顺序就确定了
  * 但是不可能每次枚举都去计算一遍，就想到了要前后缀分解
  * pre：表示构造数的顺序是从左往右，这个顺序下操作最大次数的前缀和；suf则相反
  * 那么在枚举i位置时，左边的最大操作次数就是suf[1] - suf[i],  右边pre[n] - pre[i];
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, M = 1e6 + 5, mod = 998244353;
ll T, n, k, a[N], pre[N], suf[N];

// 检查 num 不断除以2 会不会变为base
bool check(int num, int base) {
    while(num > 1 && num % 2 == 0 && num != base)
        num /= 2;
    return num == base;
}

vector<int> cal(int num) {
    int cnt = 1;
    while(num % 2 == 0)
        num /= 2, cnt *= 2;
    return {cnt, num};
}

int cal(int num, int base) {
    if(!check(num, base)) return cal(num)[0];
    int c = num / base;
    return 1 + (c - 2) * cal(base)[0];
}

bool solve() {
    for(int i = 1; i <= n; i++) {
        vector<int> t = cal(a[i]);
        ll c2 = suf[1] - suf[i], c3 = pre[n] - pre[i];
        if(t[0] + c2 + c3 >= k) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    int t = 0;
    while(T-- > 0) {
        t++;
        cin >> n >> k;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            pre[i] = pre[i - 1] + cal(a[i], a[i - 1]);
        }
        a[n + 1] = 0, suf[n + 1] = 0;
        for(int i = n; i >= 1; i--)
            suf[i] = suf[i + 1] + cal(a[i], a[i + 1]);
        cout << (solve() ? "YES" : "NO") << "\n";
    }
}