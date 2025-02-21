/**
 * @Time : 2025/2/20-4:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : cdq分治算法
 */
 /*
  * cdq分治算法 解决三维偏序问题 (x,y,z) 三个维度
  * 在分治[l,r]区间的过程中，计算左边区间[l,mid]对右边区间(mid, r]上的元素而言 对答案的贡献
  * 比如左边区间与右边区间的元素i，一共能构成多少对满足条件的数对(j,i)
  *
  * 首先选择一个维度进行排序 比如x 这样在分治[l,r]区间时
  * [l,mid]区间上的元素在这个维度一定小于(mid, r]上的元素
  * （或者一定满足某个要求的条件）
  * 然后分别在两个子区间以y维度进行排序，于是在枚举右边元素i时
  * 就能通过单调性筛选出左边对元素j，然后使用线段树或者树状数组来存储左边元素z维度的信息
  * 再根据i.z来确定查找范围 得出记数
  *
  * 分治算法的递归层数 logn
  * 对于每一层
  *     要对y维度进行排序 nlogn
  *     要根据单调性进行一次元素扫描，扫描过程中用线段树维护z维度信息 nlogn
  * 所以整体的时间复杂度是 n(logn)^2
  *
  * 例题 CF1045G
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}