/**
 * @Time : 2024/4/9-5:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 如果已知最终答案的公倍数是 lm。那么nums中任何一个lm的因子都属于最长序列
  * 反过来想 nums中的某个数 k，他可以 i * k 这个公倍数的序列贡献长度1
  * 对于nums中的所有数，计算他们对各个公倍数的贡献，累加起这些贡献 最大的那个公倍数就是答案
  * 由于题目中公倍数最大为 m = 1e6，nums中元素最大也是1e6
  * 将nums中的元素先进行统计，对于数字k，计算其对哪些公倍数有贡献
  * 就是 k、2k、3k...直到 ik > m 则终止，因此计算次数为 m / k
  * 于是将nums中所有元素进行计算 总的计算次数不会超过
  * m / 1 + m / 2 + m / 3 + ... m / m
  * = m * （1 / 1 + 1 / 2 + 1/ 3 + ... 1 / m）
  * = m * log(m)
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 1e6 + 5;
int n, m, nums[N], aux[N], cnt[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        nums[i] = num;
        if(num <= m) aux[num]++; // 统计nums中的数字
    }
    for(int i = 1; i <= m; i++) {
        if(aux[i] == 0) continue;
        for(int j = 1; j * i <= m; j++) // 计算数字对特定公倍数的贡献
            cnt[j * i] += aux[i];
    }
    int lm = 0, t = 0;
    for(int i = 1; i <= m; i++) {
        if(cnt[i] > t) t = cnt[i], lm = i;
    }
    if(lm == 0) {
        cout << 1 << " "<< 0 << "\n";
        return 0;
    }
    cout << lm << " "<< t << "\n";
    for(int i = 1; i <= n; i++) {
        if(lm % nums[i] == 0) cout << i << " ";
    }
};