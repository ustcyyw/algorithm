/**
 * @Time : 2022/8/9-11:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 在一条无限长的公路上有 n 辆汽车正在行驶。汽车按从左到右的顺序按从 0 到 n - 1 编号，每辆车都在一个 独特的 位置。

给你一个下标从 0 开始的字符串 directions ，长度为 n 。directions[i] 可以是 'L'、'R' 或 'S' 分别表示第 i 辆车是向 左 、向 右 或者 停留 在当前位置。每辆车移动时 速度相同 。

碰撞次数可以按下述方式计算：

当两辆移动方向 相反 的车相撞时，碰撞次数加 2 。
当一辆移动的车和一辆静止的车相撞时，碰撞次数加 1 。
碰撞发生后，涉及的车辆将无法继续移动并停留在碰撞位置。除此之外，汽车不能改变它们的状态或移动方向。

返回在这条道路上发生的 碰撞总次数 。

 

示例 1：

输入：directions = "RLRSLL"
输出：5
解释：
将会在道路上发生的碰撞列出如下：
- 车 0 和车 1 会互相碰撞。由于它们按相反方向移动，碰撞数量变为 0 + 2 = 2 。
- 车 2 和车 3 会互相碰撞。由于 3 是静止的，碰撞数量变为 2 + 1 = 3 。
- 车 3 和车 4 会互相碰撞。由于 3 是静止的，碰撞数量变为 3 + 1 = 4 。
- 车 4 和车 5 会互相碰撞。在车 4 和车 3 碰撞之后，车 4 会待在碰撞位置，接着和车 5 碰撞。碰撞数量变为 4 + 1 = 5 。
因此，将会在道路上发生的碰撞总次数是 5 。
示例 2：

输入：directions = "LLRR"
输出：0
解释：
不存在会发生碰撞的车辆。因此，将会在道路上发生的碰撞总次数是 0 。
 

提示：

1 <= directions.length <= 105
directions[i] 的值为 'L'、'R' 或 'S'

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/count-collisions-on-a-road
 */
class Solution {
public:
    /**
     * 寻找一系列向右行驶的车，并看他们遇到了l还是s
     * 如果遇到s，那么这一系列车都会碰到停着的车（靠右的车碰了之后停下）
     * 如果遇到l，那么最右边一辆和这个l会贡献2，然后变成两个s，于是剩下的r就类似上一种情况，每一辆贡献1
     *
     * 寻找过程中
     * 当前是s 不会累计分数
     * 当前是l，前面已经是s或者由l,r变为的s，于是碰到停着的车(需要预先跳过开头的，因为他们碰不到右行车或者停着的车)
     *
     * 执行用时：40 ms, 在所有 C++ 提交中击败了76.41%的用户
     * 内存消耗：15.9 MB, 在所有 C++ 提交中击败了72.82%的用户
     */
    int countCollisions(string directions) {
        int res = 0, i = 0, n = directions.size();
        while (i < n && directions[i] == 'L') i++;
        for(; i < n; i++){
            if(directions[i] == 'S') continue;
            if(directions[i] == 'L') {
                res++;
                continue;
            }
            int j = i;
            while (j < n && directions[j] == 'R') j++;// 找到下一个不是右行的车
            if(j != n)
                res += directions[j] == 'S' ? j - i : j - i + 1;
            i = j;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}