/**
 * @Time : 2023/12/13-12:40 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 每一个数num: a = num / k, b = num % k
 * 其中a的那部分一定会计入到答案中
 * b的这一部分 是否能转化为1计入答案 得看与num分在一组的另外一个数取余bj。b + bj >= k 可以给答案贡献1
 *
 * 对于余数 一个小的bi 应该去匹配一个大的bj，这样才容易凑出 >= k
 * 一大一小匹配 排序双指针。
 * 如果对于某个bi，找不到剩余bj凑出 >= k 那就安排一个当前最小的数给他配对 这样剩下的b更大 更利于凑出 >= k
 */

#include<bits/stdc++.h>

using namespace std;
int T, n, k;

void solve() {
    long long res = 0;
    vector<int> arr;
    for(int i = 0, num; i < n; i++) {
        cin >> num;
        arr.push_back(num % k);
        res += num / k;
    }
    sort(arr.begin(), arr.end());
    for(int i = 0, j = n - 1; i < j; ) {
        if(arr[i] + arr[j] >= k)
            res++, i++, j--;
        else i += 2;
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        solve();
    }
};