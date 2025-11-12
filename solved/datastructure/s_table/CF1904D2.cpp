/**
 * @Time : 2024/12/5-10:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1904D1 CF1904D2 1600 1800 构造 数据结构 st表
 */
/*
  * 关键1：操作只会使元素增大 因此每次操作 尽量范围小 这样为其它元素留有变化的余量
  * 关键2：应该从b中小的元素开始考虑改变a，这样从小的开始改变 不会影响a中其它位置的大小
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n;
vector<int> a, b;
map<int, vector<int>> mp;
priority_queue<vector<int>, vector<vector<int>>, greater<>>pq;

class STable {
    int n, m;
    vector<vector<int>> dp;

    int f(int num1, int num2) {
        // 可以替换为其它函数
        return max(num1, num2);
    }

public:
    STable(vector<int>& nums) {
        n = nums.size(), m = log2(n);
        dp.assign(n, vector(m + 1, 0));
        for(int i = 0; i < n; i++)
            dp[i][0] = nums[i];
        for(int j = 1; j <= m; j++) {
            int pj = 1 << (j - 1);
            for(int i = 0; i + pj < n; i++) {
                dp[i][j] = f(dp[i][j - 1], dp[i + pj][j - 1]);
            }
        }
    }

    int search(int l, int r) {
        int len = r - l + 1, j = log2(len);
        return f(dp[l][j], dp[r - (1 << j) + 1][j]);
    }
};

bool check_range(STable& sta, STable& stb, int i, int j, int val) {
    if(sta.search(i, j) > val) return false;
    if(-stb.search(i, j) < val) return false;
    return true;
}

bool check() {
    for(int i = 0; i < n; i++)
        if(b[i] < a[i]) return false;
    vector<int> c = b;
    for(int i = 0; i < n; i++)
        c[i] = -c[i];
    STable sta(a), stb(c);
    while(!pq.empty()) {
        int val = pq.top()[0], idx = pq.top()[1];
        pq.pop();
        if(a[idx] == b[idx]) continue;
        // 向前（向后）找a中等于val的元素a[j],在a[i,j]之间不能有更大元素 否则使用不了val
        // 而在b[i,j]之间不能有更小的元素，否则修改后那个位置的a[i] > b[j]了
        if(!mp.count(val)) return false;
        vector<int>& arr = mp[val];
        auto it = upper_bound(arr.begin(), arr.end(), idx);
        if(it != arr.end() && check_range(sta, stb, idx, *it, val)) continue;
        if(it != arr.begin() && check_range(sta, stb, *(--it), idx, val)) continue;
        return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        mp = {}, pq = {}, a.assign(n, 0), b.assign(n, 0);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            mp[a[i]].push_back(i);
        }
        for(int i = 0; i < n; i++) {
            cin >> b[i];
            pq.push({b[i], i});
        }
        cout << (check() ? "YES" : "NO") << "\n";
    };
};