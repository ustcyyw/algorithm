/**
 * @Time : 2025/2/20-10:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF762B 1400 贪心 模拟
 */
 /*
  * 要装配最多 usb鼠标先装所有仅usb的，p2的先装p2的
各自剩余的再拿去装both的 计算出最大装配数num

1. c1 <= a && c2 <= b
装配数 c1 + c2, 价格就是取最低的那些鼠标
2. c1 <= a && c2 > b
装配数 c1 + b + min(c2 - b, c) 价格就是取最低的那些
3. c1 > a && c2 <= b
装配数 c2 + a + min(c1 - a, c)
4. c1 > a && c2 > b
装配数 a + b + min(c1 - a + c2 - b, c)
专属的拿完之后 不断取两类鼠标中最小的 直到拿完或者拿够c
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5;
int n, num, a, b, c;
vector<int> arr1, arr2;
vector<ll> sum1, sum2;
string t;

void init(vector<int>& arr, vector<ll>& sum) {
    sort(arr.begin(), arr.end());
    sum.assign(arr.size() + 1, 0);
    for(int i = 1; i <= arr.size(); i++)
        sum[i] = sum[i - 1] + arr[i - 1];
}

void solve() {
    int c1 = arr1.size(), c2 = arr2.size();
    ll cnt = 0, cost = 0;
    if(c1 <= a && c2 <= b) {
        cnt = c1 + c2, cost = sum1[c1] + sum2[c2];
    } else if(c1 <= a && c2 > b) {
        cnt = c1 + b + min(c2 - b, c), cost = sum1[c1] + sum2[b + min(c2 - b, c)];
    } else if(c1 > a && c2 <= b) {
        cnt = c2 + a + min(c1 - a, c), cost = sum1[a + min(c1 - a, c)] + sum2[c2];
    } else {
        cnt = a + b + min(c1 - a + c2 - b, c);
        cost = sum1[a] + sum2[b];
        int i = a, j = b, k = a + b;
        while(k < cnt) {
            if(i == c1) cost += arr2[j++];
            else if(j == c2) cost += arr1[i++];
            else if(arr1[i] < arr2[j]) cost += arr1[i++];
            else cost += arr2[j++];
            k++;
        }
    }
    cout << cnt << " " << cost;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> a >> b >> c >> n;
    for(int i = 1; i <= n; i++) {
        cin >> num >> t;
        if(t == "USB") arr1.push_back(num);
        else arr2.push_back(num);
    }
    init(arr1, sum1), init(arr2, sum2);
    solve();
};