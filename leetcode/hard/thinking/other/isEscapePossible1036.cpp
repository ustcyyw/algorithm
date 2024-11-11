/**
 * @Time : 2022/9/19-9:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 本题的关键是要发现blocked的数据量只有200
     * 虽然网格本身很大，但是只有200个点不能走
     *
     * 可以思考一下这200个点能围成的最大包围圈，显然两边借助墙
     * 包围圈不管怎么个包围的方式，包围圈的边界 到 墙角的距离都是 <= n-1的
     * 那么包围圈到圈内其它点的距离会更加 <= n-1
     * 如果不借助墙，包围圈只会更小，那么包围圈内任意一点到墙边的的距离也 <= n-1
     *
     * 因此只有从起点开始，可以走到与起点距离 >= n-1的位置，这个点就一定没有被围住
     * 我们可以分别判断source和target有没有被围住
     * 如果都没被围住，就能走到，否则就走不到。
     * 当然还要注意，如果source和target被围在一个圈里，也是可以到达的。
     */
    const int dx[4] = {0,0,-1,1}, dy[4] = {1,-1,0,0};
    int n, m = 1e6, t = 1e7;
    unordered_set<long> block;
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        n = blocked.size();
        for(auto & b : blocked)
            block.insert(get_key(b[0], b[1]));
        int sx = source[0], sy = source[1], tx = target[0], ty = target[1];
        unordered_set<long> s_marked;
        bool s_flag = boocked(s_marked, sx, sy,  sx, sy);
        if(s_marked.count(get_key(tx, ty))) return true;
        if(!s_flag) return false;
        unordered_set<long> t_marked;
        return boocked(t_marked, tx, ty, tx, ty);
    }

    bool boocked(unordered_set<long>& marked, int sx, int sy, int x, int y){
        marked.insert(get_key(x, y));
        if(abs(x - sx) + abs(y - sy) >= n - 1) return true;
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= m || ny >= m) continue;
            long key = get_key(nx, ny);
            if(block.count(key) || marked.count(key)) continue;
            if(boocked(marked, sx, sy, nx, ny)) return true;
        }
        return false;
    }

    long get_key(int x, int y){
        return (long)x * t + y;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}