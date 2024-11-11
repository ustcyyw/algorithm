/**
 * @Time : 2023/2/21-3:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
class Solution {
public:
    /*
     * 并查集的做法
     */
    int id[N];
    int minNumberOperations(vector<int>& target) {
        memset(id, 0, size(id));
        int n = target.size(), res = 0, cnt = 0, time = 0; // time记录了并查集的合并次数
        for(int i = 0; i < n; i++)
            id[i] = i;
        vector<vector<int>> bullet(N, vector(0, 0));
        for(int i = 0; i < n; i++)
            bullet[target[i]].push_back(i);
        for(int i = 3; i > 0; i--){
            cnt += bullet[i].size();
            for(int p : bullet[i]){
                if(p != n - 1 && target[p + 1] >= i)
                    time += connect(p, p + 1);
                if(p != 0 && target[p - 1] >= i)
                    time += connect(p - 1, p);
            }
            res += cnt - time;
        }
        return res;
    }

    int connect(int p, int q){
        p = find(p), q = find(q);
        if(p == q) return 0;
        id[q] = p;
        return 1;
    }

    int find(int p){
        if(id[p] == p) return p;
        id[p] = find(id[p]);
        return id[p];
    }

    /*
     * 从差分数组的角度思考
     * 将初始数组转化为target，可以进行子数组整体+1操作
     * 等价于target转化为初始全为0的数组，并且可以进行子数组-1操作
     * 记数组target为数组a
     * d为数组a的差分数组 d[0] = a[0]; d[i] = a[i] - a[i - 1], i >= 1时
     * a[i] = sum{d[0], d[1], ..., d[i]}
     *
     * 差分数组很多时候是对区间[l,r]上的元素整体加上一个值val
     * 相应的操作 d[l] += val, d[r + 1] -= val
     * 本题中是对a进行子数组-1操作
     * 相应的操作就是 d[l] -= 1, d[r + 1] += 1
     * (因为a[l - 1]不变，a[l]减小1，那么d[l] = a[l] - a[l - 1]的值就减小1，d[r + 1]同理)
     * 当r = n - 1是，d[r + 1] = d[n] 要+1
     * 但是在对d求前缀和还原数组a的时候，d[n]是用不上的
     *
     * 原始数组元素全为0 也就是d中除了d[n]以外，所有元素都为0
     * 将a还原成原数组，就是要将d中除了d[n]以外，所有元素都变为0
     *
     * 在进行一次区间减1操作的时候，d中一个元素+1，一个元素减1
     * 我们可以先对所有正的d[i]，找其右边元素d[j] < 0, i < j
     * 对a数组区间[i, j - 1]进行区间减1操作,那么d[i] -= 1， d[j] += 1
     * 直到d中没有负的元素
     *
     * 为什么可以让d中没有负的元素?
     * 因为 sum{d[0], d[1], ..., d[n - 1]} = a[n - 1] > 0，本题中a数组的所有元素都 > 0
     * 因此一次操作后，d中某个正的元素-1，一个负的元素+1，正的更多，可以保证最后d中没有负的元素
     *
     * d中没有负的元素后，再对所有正对元素d[i],与n一组进行操作 d[i] -= 1, d[n] += 1
     * 直到除了d[n]以外所有元素都为0
     *
     * 以上两个阶段，d中的正数和为多少，就操作了多少次，这就是最小操作次数。
     * d中的正数，根据定义就是a[i] - a[i - 1] > 0的部分，以及d[0]
     */
    int minNumberOperations2(vector<int>& target){
        int res = target[0]; // d[0]
        for(int i = 1; i < target.size(); i++)
            res += max(0, target[i] - target[i - 1]); // 只取 a[i] - a[i - 1] > 0 的部分
        return res;
    }
};

int main(){
    Solution s;
    vector<int> arr = {3,1,5,4,2};
    s.minNumberOperations(arr);
    cout << 0 << endl;
}