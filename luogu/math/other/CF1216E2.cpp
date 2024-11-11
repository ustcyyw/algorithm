/**
 * @Time : 2024/9/6-9:17 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1216E2
 */
/*
  * 定义一个循环节为：1 2 3 ... n 的数字序列 每个节的数字长度记为length
  * 可以发现 将循环节进行分组
  * n <= 9 的组 相邻两个节之间length的公差为 1，共有9节
  * 其中第一个节的长度为1 最后一节的长度为9
  * n <= 99的组 相邻两个节之间length的公差为 2，共有90节
  * 例如 n = 10: 12345678910; n = 11: 1234567891011
  * 其中第一节的长度为11，最后一节的长度为 11 + (cnt - 1) * 2
  * n <= 999的组 相邻两个节之间length的公差为 3，共有900节
  * 按此规律可以得出 前i组的总长度 确定答案落在哪个组中 在这个组具体哪一个节
  * 可以对节数进行二分
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
ll T, k;
// 每组循环节的公差
ll ds[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
// 每组循环节第一个节的长度
ll a1[] = {0,1,11,192,2893,38894,488895,5888896,68888897,788888898};
// 循环节组长度的前缀和
ll preLen[] = {0,45,9045,1395495,189414495,23939649495,2893942449495,339393974949495,38939394344949495,4393939398494949495};
// 循环节组节数目/同时也是个位数，2位数，3位数的数目
ll cnt[] = {0, 9, 90, 900, 9000, 90000, 900000, 9000000, 90000000, 900000000};
// 循环节组节总数的前缀和
ll preCnt[] = {0, 9, 99, 999, 9999, 99999, 999999, 9999999, 99999999, 999999999};

// 二分找到最大的循环节编号，使得序列总长度 < k, 那么下一个循环节就能使得序列总长度 >= k
pair<int, int> find() {
    // 先找到循环节落在第几组
    int i = 0;
    while(preLen[i] < k) i++;
    ll base = preLen[i - 1], num1 = a1[i], d = ds[i];
    // 二分组中的编号 编号从0开始
    int lo = 0, hi = 9 * pow(10, i - 1);
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        ll num2 = num1 + (mid - 1) * d;
        ll length = base + (num1 + num2) * mid / 2;
        if(length >= k) hi = mid - 1;
        else lo = mid;
    }
    return {i, lo}; // 组别号、组中的编号
}

// 计算递增序列（1～n）的数字总长度
ll cal2(ll n) {
    ll ans = 0;
    for(int i = 1; n > 0; i++) {
        ll t = min(n, cnt[i]);
        ans += t * ds[i];
        n -= t;
    }
    return ans;
}

// 答案落在某个循环节中 问题就化简为在自然递增序列里面找答案应该落在哪个数
// 找最大的末尾数字 使这些数字的长度 < 还需要的位置lk，那么该数字+1就是答案所在的数字
int find2(ll lk) {
    ll lo = 0, hi = 900000000;
    while(lo < hi) {
        ll mid = (lo + hi + 1) >> 1;
        if(cal2(mid) >= lk) hi = mid - 1;
        else lo = mid;
    }
    return lo;
}

void solve() {
    pair<int, int> p = find();
    int i = p.first, j = p.second; // i：循环节的组别号，j答案循环节的前一个节的编号
    ll base = preLen[i - 1], num1 = a1[i], d = ds[i], num2 = num1 + (j - 1) * d;
    ll length =  base + (num1 + num2) * j / 2; // 计算前面循环节的总长度
    k -= length; // 现在k表示答案在循环节中的位置
    int num = find2(k);
    k -= cal2(num); // 现在k表示答案在数中的位置
    string s = to_string(num + 1);
    cout << s[k - 1] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> k;
        solve();
    }
};