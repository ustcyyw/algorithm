/**
 * @Time : 2024/7/26-7:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1650D 构造
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n;
vector<int> arr, aux;

int find(int num) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == num) return i;
    }
    return -1;
}

void solve() {
    vector<int> ans;
    for(int i = n; i >= 1; i--) {
        int idx = find(i), m = idx == i - 1 ? 0 : idx + 1;
        ans.push_back(m);
        if(m != 0) {
            for(int j = 0; j < i; j++)
                aux[(j + i - m) % i] = arr[j];
            swap(aux, arr);
        }
    }
    for(int i = n - 1; i >= 0; i--)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        aux.assign(n, 0), arr.assign(n, 0);
        for(int i = 0; i < n; i++)
            cin >> arr[i];
        solve();
    }
};