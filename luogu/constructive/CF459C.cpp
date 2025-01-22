/**
 * @Time : 2025/1/21-10:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF459C 1900 构造算法 思维题
 */
/*
  * 对于确定的某个人，将其d天乘车的情况当作一个序列 序列的一个元素就是当天乘的车的编号
  * 要求任意两个人d天内乘车情况至少有1天不同 也就是要求任意两个序列不相同
  * 序列长度为d，并且每个位置可以选k辆车 不同的序列一共有 k ^ d
  * 如果 k ^ d >= n, 就可以保证每个人选一个序列对应的乘车方案 没有重复
  * 否则 直接输出-1
  *
  * 要找字典序最小的方案
  * 将这些序列 排成n行 则成为一个n * d的矩阵
  * 第一天的安排情况是矩阵的第1列 第二天是矩阵的第2列... 并且是从上往下输出
  * 因此选择的n个序列 靠左的元素要尽可能小，上面的行要尽可能小
  * 于是第一个序列应该选[0,0,..,0], 第二个序列选[0,0,..,1]
  * 第三个序列选[0,0,..,2], 第k个序列选[0,0,..,k-1], 第k+1个序列选[0,0,..,1,0]
  * 这里将车辆编号按0开始，比较方便处理
  * 因为选序列的过程就像是在进行k进制的加法
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 3e5 + 5, mod = 998244353;
int T, n, k, d;

bool check() {
    ll base = 1;
    for(int i = 1; i <= d; i++) {
        base *= k;
        if(base >= n) return true;
    }
    return false;
}

void add(vector<int>& arr1, vector<int>& arr2) {
    for(int i = d - 1, flag = 1; i >= 0; i--) {
        int num = flag + arr1[i];
        arr2[i] = num % k;
        flag = num / k;
    }
}

void solve() {
    vector<vector<int>> grid(n, vector(d, 0));
    for(int i = 1; i < n; i++)
        add(grid[i - 1], grid[i]);
    for(int j = 0; j < d; j++) {
        for(int i = 0; i < n; i++)
            cout << grid[i][j] + 1 << " ";
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n >> k >> d;
        if(!check()) {
            cout << "-1";
        } else solve();
    }
};