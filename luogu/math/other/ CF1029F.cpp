/**
 * @Time : 2024/4/22-10:21 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 面积一定的情况下 长宽越接近 周长越小
  * 所以找面积对因子 也就是找一对长和宽 但是题目还要求了至少其中一个颜色也是矩形
  * 那么就是在长宽限制范围内 找到另外一个矩形
  * 因此还要预处理a和b的因子，这些因子是他们备选的长宽。
  * 假设当前矩形的宽为l1，长为l2。看是否能将a划分成它的子矩形
  * 那肯定是先考虑将a的一边尽量设置得接近l1，这样另外一边更有机会 <= l2
  * 找到小于等于某个数的最大值 二分查找
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll a, b;
vector<ll> edge1, edge2;

void init(ll num, vector<ll>& edge) {
    for(int i = 1; i <= (int)sqrt(num); i++) {
        if(num % i == 0)
            edge.push_back(i);
    }
}

bool check(ll num, vector<ll>& edge, ll l1, ll l2) {
    auto it = upper_bound(edge.begin(), edge.end(), l1);
    ll x = edge[(--it) - edge.begin()], y = num / x;
    return x <= l1 && y <= l2;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> a >> b;
    init(a, edge1), init(b, edge2);
    ll s = a + b;
    for(int i = (int)sqrt(s); i >= 1; i--) {
        if(s % i == 0 && (check(a, edge1, i, s / i) || check(b, edge2, i, s / i))) {
            cout << (s / i + i) * 2;
            break;
        }
    }
};