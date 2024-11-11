/**
 * @Time : 2023/11/28-11:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 最后一个数 肯定是不要拆
 * 倒数第二个数呢 如果已经比最后一个数小了 也不要拆
 * 否则进行拆分 并且不能比最后一个数大 那么为了让前面有更大可能不拆或者少拆
 * 当前数字就应该尽可能拆得大一些 但是又要让总次数少，当前也应该少拆几次
 * 但这不矛盾
 * 比如 当前数是23 后一个数是5
 * 要让拆的次数少 当然每次拆一个5出去 序列变为
 * 3 5 5 5 5 一共拆4次 这是当前数的最少拆分次数了
 * 但是这样会使得后续数字要变得更小 一种更好的办法是
 * 拆为 4 4 5 5 5，同样的拆分次数 但是后续数字可以最大为4
 */
const int N = 2e5 + 5;
int T, n, nums[N];

long long solve() {
    long long cnt = 0;
    for(int i = n - 1, p = nums[n]; i >= 1; i--) {
        if(nums[i] <= p) {
            p = nums[i];
            continue;
        }
        int num = nums[i], t = num % p == 0 ? num / p : num / p + 1;
        cnt += t - 1;
        p = num / t;
    }
    return cnt;
}

int main() {
    cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> n;
        for(int j = 1; j <= n; j++)
            cin >> nums[j];
        cout << solve() << endl;
    }
    return 0;
}