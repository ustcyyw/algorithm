/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
//#include<bits/stdc++.h>
//using namespace std;
//typedef long long ll;
//typedef unsigned long long ull;
//const int N = 2e5 + 5, mod = 1e9 + 7;
//int n, k, flag = 1;
//vector<int> graph[N];
//
//int dfs(int v, int f) {
//    if(graph[v].size() == 1 && f != -1) return 1;
//    vector<int> arr;
//    for(int w : graph[v]) {
//        if(w == f) continue;
//        int cnt = dfs(w, v);
//        if(cnt == -1) return -1;
//        if(cnt > 0) arr.push_back(cnt);
//    }
//    if(arr.empty()) return 1;
//    if(arr.size() > 2) {
//        flag = 0;
//        return -1;
//    } else if(arr.size() == 2) {
//        if(arr[0] + arr[1] + 1 != k) {
//            flag = 0;
//            return -1;
//        }
//        return 0;
//    } else {
//        if(arr[0] + 1 == k) return 0;
//        return arr[0] + 1;
//    }
//}
//
//int main() {
//    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> n >> k;
//    for(int i = 1, v, w; i <= n * k - 1; i++) {
//        cin >> v >> w;
//        graph[v].push_back(w), graph[w].push_back(v);
//    }
//    int cnt = dfs(1, -1);
//    if(cnt != 0) flag = 0;
//    cout << (flag ? "Yes" : "No");
//}

#include<bits/stdc++.h>
using namespace std;
typedef __int128 ll;
typedef unsigned long long ull;
const int N = 3e5 + 5, mod = 1e9 + 7;
long long n;

bool check(ll diff, ll x, ll A) {
    if(x % A != 0 || x <= 0) return false;
    x /= A;
    ll y = x - diff;
    if(y <= 0) return false;
    cout << (long long)x << " " << (long long)y;
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(ll diff = 1; diff <= 1e6; diff++) {
        if(n % diff != 0) continue;
        // x - y = diff, y = x - diff
        ll f = n / diff;
        ll a = 3, b = -3 * diff, c = diff * diff - f;
        ll temp = b * b - 4 * a * c;
        if(temp < 0) continue;
        if((ll)sqrt(temp) * (ll)sqrt(temp) != temp) continue;
        ll x1 = -b - (ll)sqrt(temp), x2 = -b + (ll)sqrt(temp);
        if(check(diff, x1, 2 * a) || check(diff, x2, 2 * a)) return 0;
    }
    cout << -1;
}