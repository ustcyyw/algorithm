/**
 * @Time : 2024/12/16-12:20 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1722G 1500 构造 位运算
 */
/*
 * 利用高位设置1来让所有数不同 并且根据奇偶性思考
 *
 * 两个部分的长度有4种情况
1.偶数-偶数
那么造出一半之后 在这个基础上都加上base（base = 1 << j 也就是选了某个高位设置为1）
高位的1异或后为0 这两组xor的结果相同
2.偶数-奇数 但是偶数组少
造出偶数组 奇数组这个基础上都加base 最后再加上不影响结果的0
3.偶数-奇数 但是偶数组多
造出奇数组 偶数组在此基础上都加base 然后再加上0 + base
这样选定的高位就有偶数个1了 而低位相当于和0异或 也不影响结果
4.奇数-奇数
造出奇数组arr1 另一组在这个将前m2-1个元素加上base
让arr1[0] + base * 2（另一个高位设置为1），arr2[m2 - 1] = arr1.back() + base * 2
这样两组中都有 base * 2, 并且第二组的 base共有偶数个 异或和中为0 也保证了每个数字不同
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, base = 1 << 29;
int T, n, ans[N];

void build(vector<int>& arr, int m) {
    for(int i = 1; i <= m; i++)
        arr.push_back(i);
}

void add(vector<int>& aux, vector<int>& arr, int m) {
    for(int i = 0; i < m; i++)
        arr.push_back(aux[i] + base);
}

void solve() {
    int m1 = (n + 1) / 2, m2 = n - m1;
    vector<int> arr1, arr2;
    if(m1 % 2 == 0 && m2 % 2 == 0) // 两组数量一致 都是偶数个数
        build(arr1, m1), add(arr1, arr2, m2);
    else if(m1 % 2 == 1 && m2 % 2 == 1) { // 两组数量一致 都是奇数个数
        build(arr1, m1), add(arr1, arr2, m2 - 1);
        arr1[0] += base * 2; arr2.push_back(arr1.back() + base * 2);
    } else if(m1 % 2 == 1 && m2 % 2 == 0) { // 奇数-偶数 奇数个数的多1
        build(arr2, m2), add(arr2, arr1, m2);
        arr1.push_back(0);
    } else { // 偶数-奇数 偶数数量的多1
        build(arr2, m2), add(arr2, arr1, m2);
        arr1.push_back(base);
    }
    for(int i = 0; i < m1; i++) {
        cout << arr1[i] << " ";
        if(i < arr2.size()) cout << arr2[i] << " ";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n;
        solve();
        cout << "\n";
    }
};