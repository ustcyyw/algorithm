/**
 * @Time : 2023/9/19-2:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#define ls (x << 1)
#define rs ((x << 1) | 1)
#include<bits/stdc++.h>
using namespace std;
int n, m;
vector<int> vals;
vector<vector<int>> box;
unordered_map<int, int> mp;

void scatter(vector<int>& arr) {
    mp[-1] = 0;
    sort(arr.begin(), arr.end());
    for(int num : arr) {
        if(mp.count(num)) continue;
        mp[num] = mp.size();
    }
}

void add(int l, int r, int x, int pos, int val) {
    if(l == r) {
        vals[x] = min(vals[x], val);
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) add(l, mid, ls, pos, val);
    else add(mid + 1, r, rs, pos, val);
    vals[x] = min(vals[ls], vals[rs]);
}

int search(int l, int r, int x, int a, int b) {
    if(a <= l && r <= b) return vals[x];
    int mid = (l + r) >> 1, res = INT_MAX;
    if(a <= mid) res = search(l, mid, ls, a, b);
    if(b > mid) res = min(res, search(mid + 1, r, rs, a, b));
    return res;
}

string solve() {
    for(int i = 0, j = 0; i < n; i = j) {
        vector<int> aux;
        while (j < n && box[j][0] == box[i][0]) {
            if(box[j][2] > search(0, m, 1, 0, mp[box[j][1]] - 1))
                return "Yes";
            aux.push_back(j);
            j++;
        }
        for(int k : aux)
            add(0, m, 1, mp[box[k][1]],  box[k][2]);
    }
    return "No";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    vals.assign(4 * n + 10, INT_MAX);
    box = {};
    for(int i = 0, a, b, c; i < n; i++) {
        cin >> a >> b >> c;
        vector<int> temp = {a, b, c};
        sort(temp.begin(), temp.end());
        box.push_back(temp);
    }
    sort(box.begin(), box.end());
    vector<int> arr;
    for(auto& temp : box)
        arr.push_back(temp[1]);
    scatter(arr);
    m = mp.size();
    cout << solve() << endl;
}