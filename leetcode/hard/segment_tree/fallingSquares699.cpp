/**
 * @Time : 2022/9/8-5:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 在二维平面上的 x 轴上，放置着一些方块。

给你一个二维整数数组 positions ，其中 positions[i] = [lefti, sideLengthi] 表示：第 i 个方块边长为 sideLengthi ，其左侧边与 x 轴上坐标点 lefti 对齐。

每个方块都从一个比目前所有的落地方块更高的高度掉落而下。方块沿 y 轴负方向下落，直到着陆到 另一个正方形的顶边 或者是 x 轴上 。一个方块仅仅是擦过另一个方块的左侧边或右侧边不算着陆。一旦着陆，它就会固定在原地，无法移动。

在每个方块掉落后，你必须记录目前所有已经落稳的 方块堆叠的最高高度 。

返回一个整数数组 ans ，其中 ans[i] 表示在第 i 块方块掉落后堆叠的最高高度。

 

示例 1：


输入：positions = [[1,2],[2,3],[6,1]]
输出：[2,5,5]
解释：
第 1 个方块掉落后，最高的堆叠由方块 1 组成，堆叠的最高高度为 2 。
第 2 个方块掉落后，最高的堆叠由方块 1 和 2 组成，堆叠的最高高度为 5 。
第 3 个方块掉落后，最高的堆叠仍然由方块 1 和 2 组成，堆叠的最高高度为 5 。
因此，返回 [2, 5, 5] 作为答案。
示例 2：

输入：positions = [[100,100],[200,100]]
输出：[100,100]
解释：
第 1 个方块掉落后，最高的堆叠由方块 1 组成，堆叠的最高高度为 100 。
第 2 个方块掉落后，最高的堆叠可以由方块 1 组成也可以由方块 2 组成，堆叠的最高高度为 100 。
因此，返回 [100, 100] 作为答案。
注意，方块 2 擦过方块 1 的右侧边，但不会算作在方块 1 上着陆。
 

提示：

1 <= positions.length <= 1000
1 <= lefti <= 108
1 <= sideLengthi <= 106

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/falling-squares
 */
class Solution {

public:
    /**
     * 执行用时：24 ms, 在所有 C++ 提交中击败了84.70%的用户
     * 内存消耗：16.6 MB, 在所有 C++ 提交中击败了40.11%的用户
     */
    int N = 8005;
    vector<int> max_val, tag;
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        max_val = vector(N, 0), tag = vector(N, 0);
        unordered_map<int, int> map = scatter(positions);
        vector<int> res;
        int n = map.size();
        for(auto& pos : positions){
            // 方块的区间是左闭右开，所以右边界要-1得到闭区间
            int l = map[pos[0]], r = map[pos[0] + pos[1]] - 1;
            int h = query(1, l, r, 0, n - 1);
            add(1, l, r, 0, n - 1, h + pos[1]);
            res.push_back(max_val[1]);
        }
        return res;
    }
    // 区间[L, R]上的最大值查询
    int query(int x, int L, int R, int l, int r){
        if(L <= l && r <= R) return max_val[x];
        down(x);
        int mid = (l + r) >> 1, res = 0;
        if(L <= mid) res = max(res, query(2 * x, L, R, l, mid));
        if(R > mid) res = max(res, query(2 * x + 1, L, R, mid + 1, r));
        return res;
    }

    // 区间[L, R]上都修改为val
    void add(int x, int L, int R, int l, int r, int val){
        if(L <= l && r <= R){
            max_val[x] = val;
            tag[x] = val;
            return;
        }
        down(x);
        int mid = (l + r) >> 1;
        if(L <= mid) add(2 * x, L, R, l, mid, val);
        if(R > mid) add(2 * x + 1, L, R, mid + 1, r, val);
        max_val[x] = max(max_val[2 * x], max_val[2 * x + 1]);
    }

    void down(int x){
        if(tag[x] == 0) return;
        int ls = 2 * x, rs = 2 * x + 1;
        tag[ls] = tag[x], tag[rs] = tag[x];
        max_val[ls] = tag[x], max_val[rs] = tag[x];
        tag[x] = 0;
    }

    void update(int x){
        max_val[x] = max(max_val[2 * x], max_val[2 * x + 1]);
    }

    unordered_map<int, int> scatter(vector<vector<int>>& positions){
        unordered_set<int> set;
        vector<int> arr;
        for(auto& pos : positions){
            int v = pos[0], w = pos[0] + pos[1];
            add(set, arr, v), add(set, arr, w);
        }
        sort(arr.begin(), arr.end());
        unordered_map<int, int> map;
        for(int i = 0; i < arr.size(); i++)
            map[arr[i]] = i;
        return map;
    }

    void add(unordered_set<int>& set, vector<int>& arr, int v){
        if(!set.count(v)){
            arr.push_back(v);
            set.insert(v);
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}