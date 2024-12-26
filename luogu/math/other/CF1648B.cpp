/**
 * @Time : 2024/12/25-4:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1648B 1800 数学 调和级数 差分
 */
 /*
  * 经典做法 把除法（因子）有关的问题 尝试转化为乘法（倍数）相关的问题
最简单的例子就是 问 x是否为y的因子，转换一下思维方式就是 x的某个倍数是否为y

在本题中 要求 y >= x时(x可以等于y) 有 y / x(向下取整) 存在集合中
设 z = y / x，写为乘法的形式 那么 xz <= y < (z + 1) * x
假设 小于等于y的数一共有cnt个， 那么就需要有cnt个 (x,z)的数对
对于任意(x,z)数对，都能使得[xz, (z + 1) * x - 1]范围内的y增加一个数对计数

预处理出所有数对增加的计数 重复数字没有意义 先进行去重
由于数组中的数都小于c, 因此 xz > c 就没有实际意义
将数组进行排序 在去重的情况下 最坏的情况数组中是 1、2、3...c
枚举x和z, 对于确定的x，z <= c / x，应该有c / x个需要枚举的z
将所有x需要枚举的z进行求和 c + c / 2 + c / 3 + ... + c / c
= c * (1 + 1 / 2 + 1 / 3 + ... 1 / c) = clogc
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
int T, n, c, diff[N];
vector<int> arr;

void init(int flag) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n && (ll)arr[i] * arr[j] <= c; j++) {
            int l = arr[i] * arr[j], r = min((ll)(arr[j] + 1) * arr[i] - 1, (ll)c);
            diff[l] += flag, diff[r + 1] -= flag;
        }
    }
}

bool solve() {
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    c = arr.back(), n = arr.size();
    init(1);
    vector<int> sum(c + 1, 0);
    for(int i = 1; i <= c; i++)
        sum[i] = sum[i - 1] + diff[i];
    bool ans = true;
    for(int i = 0; i < n; i++) {
        if(sum[arr[i]] != i + 1) {
            ans = false;
            break;
        }
    }
    init(-1);
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> c;
        arr = {};
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            arr.push_back(num);
        }
        cout << (solve() ? "Yes" : "No") << "\n";
    }
};