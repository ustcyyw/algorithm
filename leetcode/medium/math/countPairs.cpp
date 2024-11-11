/**
 * @Time : 2022/8/22-8:56 PM
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
     * 执行用时：196 ms, 在所有 C++ 提交中击败了55.05%的用户
     * 内存消耗：138.8 MB, 在所有 C++ 提交中击败了11.01%的用户
     *
     * 相乘能被k除尽的（n1, n2）
     * 其中一个数有一个因子a，另外一个数有因子b 且要满足a * b = k
     *
     * 分类讨论，要针对k的因子进行讨论
     * 将nums根据因子对(a,b)进行分组
     * 比如 k = 8, (a,b) 可以为(1,8) (2,4) (4,2), (8,1)
     * (a,b) 与 (b,a) 是等价的，乘法交换律
     * 也可以从计算的代码证明这一点，我们只是在扫描的时候统计只有因子a，b的数，和同时拥有a,b的数
     *
     * 但是(1,8)与(2,4)之间还是可能出现重复
     * 例如 数 2 8 在分类(1,8)中出现一次，也会在(2,4)中出现一次
     * 也要进行去重
     * 能被较大的因子b整除的数，就不应该出现在下一对因子的记数计算中
     */
    long long countPairs(vector<int>& nums, int k) {
        long long res = 0;
        for(int a = 1; a < (int)sqrt(k) + 1; a++){
            vector<int> aux;
            if(k % a != 0) continue;
            int b = k % a, countA = 0, countB = 0, both = 0;
            for(int num : nums){
                if(num % b != 0) aux.push_back(num);
                if(num % a == 0 && num % b == 0){
                    res += both + countA + countB;
                    both++;
                } else if(num % a == 0){
                    countA++;
                    res += countB + both;
                } else if(num % b == 0){
                    countB++;
                    res += countA + both;
                }
            }
            nums = aux;
        }
        return res;
    }

    /**
     * xy / k = x / k * y，将x和k进行约分会得到形如 a / b 的最简分数
     * （特殊情况 b = 1，也就是k是x的一个因子时）
     * 那么 xy / k = a / b * y = a * (y / b)，这样写是因为a已经没法b再约分
     *
     * 如果两个数 x * y 能被k整除
     * 就是 y / b 能整除，那就要求b是y的一个因子
     *
     * 在枚举x的时候，需要知道前面有多少个y含有因子b
     * 但是因为x在变化，b = k / gcd(x,k)，b也在变化
     * 因而需要统计y的因子的情况
     */
    long long countPairs2(vector<int>& nums, int k) {
        long long res = 0;
        unordered_map<int, int> map; // 统计因子出现的情况
        for(int x : nums){
            int b = k / gcd(x, k);
            res += map.count(b) ? map[b] : 0;
            for(int i = 1; i < (int) sqrt(x) + 1; i++){
                if(x % i != 0) continue;
                if(x / i == i) map[i]++;
                else {
                    map[i]++;
                    map[x / i]++;
                }
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}