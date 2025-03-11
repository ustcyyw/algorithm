/**
 * @Time : 2025/3/10-8:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF863B 1500 暴力枚举
 */
 /*
  * 这么小的数据量 直接暴力枚举两个单皮划艇的人即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, P = 13331;
int n, nums[105];

int cal(vector<int>& arr) {
    int ans = 0;
    for(int i = 0; i < arr.size(); i += 2) {
        ans += arr[i + 1] - arr[i];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= 2 *  n; i++)
        cin >> nums[i];
    sort(nums + 1, nums + 2 * n + 1);
    int ans = INT_MAX;
    for(int i = 1; i < 2 * n; i++) {
        for(int j = i + 1; j <= 2 * n; j++) {
            vector<int> arr;
            for(int k = 1; k <= 2 * n; k++)
                if(k != i && k != j) arr.push_back(nums[k]);
            ans = min(ans, cal(arr));
        }
    }
    cout << ans << "\n";
}