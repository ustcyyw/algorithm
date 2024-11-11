/**
 * @Time : 2023/2/22-1:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
* 区间合并的时候使用摩尔投票的思路 这样找到的数最可能是区间内超过一半的大数
*/
const int N = 2e4 + 5;
# define ls (x << 1)
# define rs ((x << 1) | 1)
class MajorityChecker {
public:
    unordered_map<int, vector<int>> map; // num -> list of index of the num
    int count[4 * N], aux[4 * N], n;
    MajorityChecker(vector<int>& arr) {
        this->n = arr.size();
        for(int i = 0; i < n; i++){
            if(!map.count(arr[i])) map[arr[i]] = {};
            map[arr[i]].push_back(i);
        }
        build(arr,1, 0, n - 1);
    }

    void build(vector<int>& arr, int x, int l, int r){
        if(l == r) {
            aux[x] = arr[l];
            count[x] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(arr, ls, l, mid);
        build(arr, rs, mid + 1, r);
        update(x);
    }

    void update(int x){
        if(aux[ls] == aux[rs]){
            count[x] = count[ls] + count[rs];
            aux[x] = aux[ls];
        } else {
            int t = count[ls] - count[rs];
            count[x] = abs(t);
            aux[x] = t >= 0 ? aux[ls] : aux[rs];
        }
    }

    vector<int> query_num(int x, int a, int b, int l, int r){
        if(a <= l && r <= b) return {aux[x], count[x]};
        int mid = (l + r) >> 1;
        vector<int> res = {-1, 0};
        if(a <= mid)
            res = query_num(ls, a, b, l, mid);
        if(b > mid){
            vector<int> t = query_num(rs, a, b, mid + 1, r);
            if(res[0] == t[0]) res[1] += t[1];
            else if(t[1] >= res[1]) {
                res[0] = t[0];
                res[1] = t[1] - res[1];
            } else res[1] = res[1] - t[1];
        }
        return res;
    }

    int query(int left, int right, int threshold) {
        int num = query_num(1, left, right, 0, n - 1)[0];
        vector<int>& arr = map[num];
        auto lo = lower_bound(arr.begin(), arr.end(), left);
        auto hi = upper_bound(arr.begin(), arr.end(), right);
        return hi - lo >= threshold ? num : -1;
    }
};

int main(){
    vector<int> arr = {1,1,2,2,1,1};
    MajorityChecker s(arr);
    s.query(0,5,4);
    cout << 0 << endl;
}