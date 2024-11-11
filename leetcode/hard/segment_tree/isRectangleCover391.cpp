/**
 * @Time : 2023/3/24-12:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
# define ls (x << 1)
# define rs (x << 1 | 1)

class Solution {
public:
    /*
     * 扫描线
     * 查看区间内 是否都只被覆盖一次 也就是线条叠加有且仅有一次
     * 查询区间上的线段叠加的最大次数/最小次数，必须都是1
     * 并且会进行区间修改 想到了线段树
     */
    vector<int> min_val, max_val, tag;
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        int up = -1e6, left = 1e6, down = 1e6, right = -1e6;
        for(auto& rec : rectangles){
            up = max(rec[3], up), down = min(rec[1], down);
            left = min(rec[0], left), right = max(rec[2], right);
        }
        vector<vector<int>> infos;
        for(auto& rec : rectangles){
            int temp_up = rec[3] == up ? up : rec[3] - 1;
            infos.push_back({rec[0], rec[1], temp_up, 1});
            infos.push_back({rec[2], rec[1], temp_up, -1});
        }
        sort(infos.begin(), infos.end(),
             [](auto&a, auto&b) -> bool {return a[0] < b[0];});
        int n = up - down + 2, m = infos.size();
        min_val = vector(4 * n, 0), max_val = vector(4 * n, 0), tag = vector(4 * n, 0);
        for(int i = left, j = 0; i < right; i++){ // 扫描线
            while (j < m && infos[j][0] == i){
                change(1, down, up, infos[j][1], infos[j][2], infos[j][3]);
                j++;
            }
            if(min_val[1] != 1 || max_val[1] != 1)
                return false;
        }
        return true;
    }

    void change(int x, int l, int r, int a, int b, int flag){
        if(a <= l && r <= b) {
            tag[x] += flag;
            min_val[x] += flag, max_val[x] += flag;
            return;
        }
        down(x);
        int mid = (l + r) >> 1;
        if(a <= mid) change(ls, l, mid, a, b, flag);
        if(b > mid) change(rs, mid + 1, r, a, b, flag);
        update(x);
    }

    void update(int x){
        min_val[x] = min(min_val[ls], min_val[rs]);
        max_val[x] = max(max_val[ls], max_val[rs]);
    }

    void down(int x){
        if(tag[x] == 0) return;
        tag[ls] += tag[x], tag[rs] += tag[x];
        min_val[ls] += tag[x], min_val[rs] += tag[x];
        max_val[ls] += tag[x], max_val[rs] += tag[x];
        tag[x] = 0;
    }
};

int main(){
    Solution s;
    vector<vector<int>> arr = {{1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4}};
    s.isRectangleCover(arr);
    cout << 0 << endl;
}