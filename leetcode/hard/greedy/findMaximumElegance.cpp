/**
 * @Time : 2023/8/6-10:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 给你一个长度为 n 的二维整数数组 items 和一个整数 k 。

items[i] = [profiti, categoryi]，其中 profiti 和 categoryi 分别表示第 i 个项目的利润和类别。

现定义 items 的 子序列 的 优雅度 可以用 total_profit + distinct_categories2 计算，其中 total_profit 是子序列中所有项目的利润总和，distinct_categories 是所选子序列所含的所有类别中不同类别的数量。

你的任务是从 items 所有长度为 k 的子序列中，找出 最大优雅度 。

用整数形式表示并返回 items 中所有长度恰好为 k 的子序列的最大优雅度。

注意：数组的子序列是经由原数组删除一些元素（可能不删除）而产生的新数组，且删除不改变其余元素相对顺序。



示例 1：

输入：items = [[3,2],[5,1],[10,1]], k = 2
输出：17
解释：
在这个例子中，我们需要选出长度为 2 的子序列。
其中一种方案是 items[0] = [3,2] 和 items[2] = [10,1] 。
子序列的总利润为 3 + 10 = 13 ，子序列包含 2 种不同类别 [2,1] 。
因此，优雅度为 13 + 22 = 17 ，可以证明 17 是可以获得的最大优雅度。
示例 2：

输入：items = [[3,1],[3,1],[2,2],[5,3]], k = 3
输出：19
解释：
在这个例子中，我们需要选出长度为 3 的子序列。
其中一种方案是 items[0] = [3,1] ，items[2] = [2,2] 和 items[3] = [5,3] 。
子序列的总利润为 3 + 2 + 5 = 10 ，子序列包含 3 种不同类别 [1, 2, 3] 。
因此，优雅度为 10 + 32 = 19 ，可以证明 19 是可以获得的最大优雅度。
示例 3：

输入：items = [[1,1],[2,1],[3,1]], k = 3
输出：7
解释：
在这个例子中，我们需要选出长度为 3 的子序列。
我们需要选中所有项目。
子序列的总利润为 1 + 2 + 3 = 6，子序列包含 1 种不同类别 [1] 。
因此，最大优雅度为 6 + 12 = 7 。


提示：

1 <= items.length == n <= 105
items[i].length == 2
items[i][0] == profiti
items[i][1] == categoryi
1 <= profiti <= 109
1 <= categoryi <= n
1 <= k <= n
 */
class Solution {
public:
    /*
     * 可以想到枚举种类数c
     * 对于确定的c，肯定是元素越大越好，会想到排序之后来选元素
     * 而且在和一定的情况下，c越大越好 如果先选出来最大的k个元素，他们的种类数为c1
     * 那更好的策略只能是将这k个元素中最小的依次替换，以求将种类数变为c1+1,c1+2...
     *
     * 但是需要注意一个问题，已经被选取到的种类，只剩下最后一个元素时，不应该将其替换
     * 因为换进来的元素小于等于它，并且元素种类不变
     *
     * 可以用一个栈来存在已经选取的元素 每次从栈顶去选择替换的元素
     */
    long long findMaximumElegance(vector<vector<int>>& items, int k) {
        sort(items.begin(), items.end()), reverse(items.begin(), items.end());
        int n = items.size();
        unordered_map<int, int> map;
        stack<vector<int>> picked;
        long long sum = 0ll, res = 0ll;
        function<void(vector<int>&)> add_item = [&](vector<int>& item) {
            sum += item[0], map[item[1]]++;
            picked.push(item);
        };
        for(int i = 0; i < k; i++)
            add_item(items[i]);
        res = sum + (long long)map.size() * (long long)map.size();
        for(int i = k; i < n; i++) {
            vector<int>& item = items[i];
            if(map.count(item[1])) continue; // 已有的种类 没有替换的意义 同一种类更大的元素在前面已经使用了
            while (!picked.empty() && map[picked.top()[1]] == 1) picked.pop(); // 只剩一个的元素的种类 没有替换的意义
            if(picked.empty()) break;
            vector<int>& aux = picked.top();
            sum -= aux[0], map[aux[1]]--;
            picked.pop();
            add_item(item);
            res = max(res, sum + (long long)map.size() * (long long)map.size());
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}