/**
 * @Time : 2025/3/12-10:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2074F 2061 数学 找规律 位运算
 */
 /*
  * 将这个平面图当坐标系处理 而不是一个四叉树
  * x坐标和y坐标在拆分的时候是独立的
  * 但是计算格子数的时候 又取决于小的那个坐标 得用小的那个坐标来当正方形边长
  *
  * 如何拆分 从简单的例子开始看 可以发现需要找到一个 2^k，使得l和r刚好在这个值的左右两边
  * 然后计算两边的长度 这个长度从二进制的角度思考就刚好能拆分出该坐标系的格子
  * 但是如果l和r分布在2^k的同侧 那就平移 参考递归函数
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, P = 13331;
ll T, l1, r1, l2, r2, pow2[32];

int init = []() -> int {
    pow2[0] = 1;
    for(int i = 1; i < 32; i++)
        pow2[i] = pow2[i - 1] * 2;
    return 0;
}();

void add(vector<int>& arr, int num) {
    for(int i = 0; i < 32; i++) {
        if((1 << i) & num)
            arr.push_back(pow2[i]);
    }
}

int findMid(int& l, int& r) {
    for(int i = 0; i < 32; i++) {
        if(pow2[i] > r) {
            int mid = pow2[i - 1];
            if(mid >= l) return mid;
            else {
                l -= mid, r -= mid;
                return findMid(l, r);
            }
        }
    }
    return -1;
}

vector<int> cal(int l, int r) {
    vector<int> arr;
    int mid = findMid(l, r);
    add(arr, mid - l), add(arr, r - mid);
    return arr;
}

void solve() {
    vector<int> arr1 = cal(l1, r1), arr2 = cal(l2, r2);
    ll ans = 0;
    for(int n1 : arr1) {
        for(int n2 : arr2) {
            ll t = min(n1, n2);
            ans += (ll)n1 / t * n2 / t;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> l1 >> r1 >> l2 >> r2;
        solve();
    }
}