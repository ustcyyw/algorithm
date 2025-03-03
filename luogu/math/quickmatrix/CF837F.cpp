/**
 * @Time : 2025/3/2-10:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF837F 2400 分治思想（分类讨论） 二分答案 矩阵快速幂
 */
 /*
  * 用例子手算发现 按操作执行一堆前置0没有意义
  * 真正有价值的数字 其个数是不变的
  * 并且执行过一次操作后 除了前置0外 不会再有0
  * 因此可以先执行一次操作 并且将前置0去掉后再来讨论
  *
  * 根据计算方式 可以发现 由上一个数组得到下一个数组 是矩阵运行
  * 想到二分 + 矩阵快速幂
  * 但是n很大的时候 光得到系数矩阵就超时了
  * 但是还可以发现 当n > 6的时候 执行操作几千次 即便一开始数组中都是1 也超过了1e18了
  * 所以可以分类讨论（类似于根号分治）
  * 当n > 6 就直接暴力计算 直到数组中最后一个元素 > k就停止
  * 否则就二分需要操作多少次 然后矩阵快速幂计算初最后一个元素的值 看是否 > k
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 ull;
const int N = 1e5 + 5, M = 1e6 + 5, mod = 1e9 + 7;
ll T, n, k;
vector<ull> base;

bool ope(vector<ull>& arr) {
    for(int i = 1; i < arr.size(); i++) {
        arr[i] += arr[i - 1];
        if(arr[i] >= k) return true;
    }
    return false;
}

vector<ull> init(vector<ull>& arr) {
    ope(arr);
    vector<ull> ans;
    auto it = find_if(arr.begin(), arr.end(), [](ll x) { return x > 0; });
    if (it != arr.end()) ans.assign(it, arr.end());
    return ans;
}

vector<vector<ull>> get_matrix(int m) {
    vector<vector<ull>> ans(m, vector<ull>(m, 0ll));
    for(int i = 0; i < m; i++) {
        for(int j = i; j < m; j++)
            ans[i][j] = 1;
    }
    return ans;
}

vector<vector<ull>> matrixMul(vector<vector<ull>>& A, vector<vector<ull>>& B){
    int N = A.size(), M = B[0].size(), K = A[0].size();
    vector<vector<ull>> ans(N, vector<ull>(M, 0));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            for(int k = 0; k < K; k++)
                ans[i][j] = ((ull)ans[i][j] + (A[i][k] * B[k][j]));
        }
    }
    return ans;
}

vector<vector<ull>> quickPower(vector<vector<ull>> a, ll b){
    int n = a.size(); // 能进行快速幂的矩阵 是一个方阵
    vector<vector<ull>> ans(n, vector<ull>(n, 0ll));
    for(int i = 0; i < n; i++)
        ans[i][i] = 1;
    while (b != 0){
        if((b & 1) == 1) ans = matrixMul(ans , a);
        a = matrixMul(a, a);
        b >>= 1;
    }
    return ans;
}

bool cal(vector<vector<ull>>& matrix) {
    ull sum = 0;
    for(int i = 0, m = matrix.size(); i < m; i++) {
        sum += base[i] * matrix[i][m - 1];
        if(sum >= k || matrix[i][m - 1] >= k) return true;
    }
    return false;
}

ll solve() {
    if(base.back() >= k) return 1;
    int m = base.size();
    if(m <= 6) {
        vector<vector<ull>> matrix = get_matrix(m);
        ll lo = 1, hi = 1e18;
        while(lo < hi) {
            ll mid = (lo + hi) >> 1;
            vector<vector<ull>> temp = quickPower(matrix, mid);
            if(cal(temp)) hi = mid;
            else lo = mid + 1;
        }
        return lo + 1;
    }
    int cnt = 1;
    while(true) {
        cnt++;
        bool flag = ope(base);
        if(flag) return cnt;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    base = vector<ull>(n, 0ll);
    for(int i = 0, num; i < n; i++) {
        cin >> num;
        base[i] = num;
        if(base[i] >= k) {
            cout << 0;
            return 0;
        }
    }
    base = init(base);
    cout << solve();
}