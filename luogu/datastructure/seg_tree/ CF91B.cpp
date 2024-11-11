/**
 * @Time : 2024/1/27-11:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
# define ls x << 1
# define rs (x << 1) | 1
const int N = 1e5 + 5;
int n, nums[N], ans[N], arr[4 * N];
unordered_map<int, int> mp;

void add(int x, int l, int r, int pos, int val) {
    if(l == r) {
        arr[x] = max(arr[x], val);
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) add(ls, l, mid, pos, val);
    else add(rs, mid + 1, r, pos, val);
    arr[x] = max(arr[ls], arr[rs]);
}

int search(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) return arr[x];
    int mid = (l + r) >> 1, res = -1;
    if(a <= mid) res = search(ls, l, mid, a, b);
    if(b > mid) res = max(res, search(rs, mid + 1, r, a, b));
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    memset(arr, 0, sizeof(arr));
    cin >> n;
    set<int> set;
    vector<int> aux;
    aux.push_back(0);
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
        if(!set.count(nums[i])) {
            set.insert(nums[i]);
            aux.push_back(nums[i]);
        }
    }
    sort(aux.begin(), aux.end());
    int m = aux.size();
    mp.clear();
    for(int i = 0; i < m; i++)
        mp[aux[i]] = i;
    for(int i = n - 1; i >= 0; i--) {
        int j = search(1, 0, m - 1, 0, mp[nums[i]] - 1);
        ans[i] = j == 0 ? -1 : j - i - 1;
        add(1, 0, m - 1, mp[nums[i]], i);
    }
    for(int i = 0; i < n; i++)
        cout << ans[i] << " ";
}