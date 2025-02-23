/**
 * @Time : 2025/2/22-8:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF797B 1400 贪心 数学
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5, M = 400;
int n;

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n;
    vector<int> arr1;
    ll sum2 = 0, sum1 = 0;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        if(num % 2 == 0 && num > 0) sum2 += num;
        if((num % 2 + 2) % 2 == 1) arr1.push_back(num);
    }
    sort(arr1.begin(), arr1.end());
    sum1 = arr1.back();
    for(int i = arr1.size() - 3; i >= 0; i -= 2) {
        ll temp = arr1[i] + arr1[i + 1] + sum1;
        if(temp > sum1) sum1 = temp;
        else break;
    }
    cout << sum1 + sum2;
};