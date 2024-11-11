/**
 * @Time : 2024/4/25-5:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 通过不断的+2操作 可以将任意两个数之差的绝对值变得 <= 1
 * 并且每个数的奇偶性不变 因为每个数都只看一开始的奇偶性
 * 奇偶性相同的数 最后都能只通过+2操作变得相同
 * 因此就只关注数字的奇偶性
 * 相邻的两个数，同时+1，就意味着这两个数可以变为任意数（奇偶性任意变）
 * 如果相邻的两个数相同，假设都是1，并且他们前后两个数相同，假设都是0
 * 那么将这两个1同时+1，他们变为偶数 就等价于0，这四个数就都相同了，他们可以变为任意数了
 * 以此类推 只要遇到相邻两个数相同 就等价于他们不会将其它数隔开，其它数可以跳过他们（视为相邻）来考虑相等性
 *
 * 这就类似于用栈处理消消乐
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll n;
vector<int> arr;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        int t = num % 2;
        if(!arr.empty() && arr.back() == t) arr.pop_back();
        else arr.push_back(t);
    }
    // 栈中最后剩下0个或者1个数，说明前面其它数都是等价相邻且相等 并且有偶数组 他们可以变为任意数
    cout << (arr.size() <= 1 ? "YES" : "NO");
};