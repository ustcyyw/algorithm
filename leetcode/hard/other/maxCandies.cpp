/**
 * @Time : 2022/8/19-10:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你 n 个盒子，每个盒子的格式为 [status, candies, keys, containedBoxes] ，其中：

状态字 status[i]：整数，如果 box[i] 是开的，那么是 1 ，否则是 0 。
糖果数 candies[i]: 整数，表示 box[i] 中糖果的数目。
钥匙 keys[i]：数组，表示你打开 box[i] 后，可以得到一些盒子的钥匙，每个元素分别为该钥匙对应盒子的下标。
内含的盒子 containedBoxes[i]：整数，表示放在 box[i] 里的盒子所对应的下标。
给你一个 initialBoxes 数组，表示你现在得到的盒子，你可以获得里面的糖果，也可以用盒子里的钥匙打开新的盒子，还可以继续探索从这个盒子里找到的其他盒子。

请你按照上述规则，返回可以获得糖果的 最大数目 。

 

示例 1：

输入：status = [1,0,1,0], candies = [7,5,4,100], keys = [[],[],[1],[]], containedBoxes = [[1,2],[3],[],[]], initialBoxes = [0]
输出：16
解释：
一开始你有盒子 0 。你将获得它里面的 7 个糖果和盒子 1 和 2。
盒子 1 目前状态是关闭的，而且你还没有对应它的钥匙。所以你将会打开盒子 2 ，并得到里面的 4 个糖果和盒子 1 的钥匙。
在盒子 1 中，你会获得 5 个糖果和盒子 3 ，但是你没法获得盒子 3 的钥匙所以盒子 3 会保持关闭状态。
你总共可以获得的糖果数目 = 7 + 4 + 5 = 16 个。
示例 2：

输入：status = [1,0,0,0,0,0], candies = [1,1,1,1,1,1], keys = [[1,2,3,4,5],[],[],[],[],[]], containedBoxes = [[1,2,3,4,5],[],[],[],[],[]], initialBoxes = [0]
输出：6
解释：
你一开始拥有盒子 0 。打开它你可以找到盒子 1,2,3,4,5 和它们对应的钥匙。
打开这些盒子，你将获得所有盒子的糖果，所以总糖果数为 6 个。
示例 3：

输入：status = [1,1,1], candies = [100,1,100], keys = [[],[0,2],[]], containedBoxes = [[],[],[]], initialBoxes = [1]
输出：1
示例 4：

输入：status = [1], candies = [100], keys = [[]], containedBoxes = [[]], initialBoxes = []
输出：0
示例 5：

输入：status = [1,1,1], candies = [2,3,2], keys = [[],[],[]], containedBoxes = [[],[],[]], initialBoxes = [2,1,0]
输出：7
 

提示：

1 <= status.length <= 1000
status.length == candies.length == keys.length == containedBoxes.length == n
status[i] 要么是 0 要么是 1 。
1 <= candies[i] <= 1000
0 <= keys[i].length <= status.length
0 <= keys[i][j] < status.length
keys[i] 中的值都是互不相同的。
0 <= containedBoxes[i].length <= status.length
0 <= containedBoxes[i][j] < status.length
containedBoxes[i] 中的值都是互不相同的。
每个盒子最多被一个盒子包含。
0 <= initialBoxes.length <= status.length
0 <= initialBoxes[i] < status.length

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximum-candies-you-can-get-from-boxes
 */
class Solution {
public:
    /**
     * 执行用时：96 ms, 在所有 C++ 提交中击败了92.54%的用户
     * 内存消耗：43.6 MB, 在所有 C++ 提交中击败了8.96%的用户
     * 模拟
     */
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys,
                   vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        unordered_set<int> got_key, got_box;
        queue<int> opened_box;
        for(int box : initialBoxes){ // 根据初始箱子的状态添加到对应集合
            if(status[box]) opened_box.push(box); // 开着的箱子直接加入已开集合
            else got_box.insert(box); // 没开的放到手中持有但没打开的箱子集合
        }
        int res = 0;
        while (!opened_box.empty()){
            int size = opened_box.size();
            for(int i = 0; i < size; i++){
                int cur_box = opened_box.front();
                opened_box.pop();
                res += candies[cur_box];
                vector<int>& temp_boxs = containedBoxes[cur_box], temp_keys = keys[cur_box];
                for(int key : temp_keys) {
                    if(!status[key]) // 只有盒子是关闭着的钥匙才有存放的意义
                        got_key.insert(key);
                }
                for(int box : temp_boxs){
                    if(status[box]) opened_box.push(box); // 开着的箱子直接加入已开集合，不用放到手中的箱子集合
                    else got_box.insert(box);
                }
            }
            unordered_set<int> temp_box; // 表示这一轮获取钥匙后，被开的箱子的集合
            for(int box : got_box){ // 检查这一轮之后，有哪些手上的箱子已经拿到钥匙，将其打开并放入已开集合
                if(got_key.count(box)){
                    temp_box.insert(box);
                    opened_box.push(box);
                }
            }
            for(int box : temp_box) // 将被开过的箱子从手中的箱子中移除
                got_box.erase(box);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}