/**
 * @Time : 2023/4/28-10:47 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 有2对情侣互相做错了位置 如 02 13 交换一次即可
     * 有3对情侣互相做错了位置 如 02 43 51，可以先交换为01 43 52, 变成2对情侣互相做错了位置的情况。总共交换2次
     * ...
     * 有k对情侣互相做错了位置 就需要k-1次交换
     *
     * 可能有多组情侣（m组） 每一组里面有ki对情侣互相做错了位置
     * 比如 (02 13) (46 75) 两组情侣，每一组都有2对互相做错了位置
     * 总的交换次数为 sum{ki - 1} = sum{ki} - m = n - m。n为总的情侣对数
     *
     * 如何找有多少组互相坐错位置的情侣?
     * 一对情侣的个人编号为 id1 = 2 * j, id2 = 2 * j + 1。记他们的情侣号为 j = id1 / 2 = id2 / 2
     * 对于位置i，i+1的这两个人来说，如果情侣号不同，说明这两对互相坐错了位置
     * 他们是处于同一个错误位置的组别中
     * 如果j1,j2处于同一个错误位置的组别，j2,j3处于同一个错误位置的组别,j1和j2就处于错误组别
     * 这是连通分量 可以使用并查集 对情侣号找连通分量
     */
    vector<int> id;
    int minSwapsCouples(vector<int>& row) {
        int n = row.size(), total = n / 2;
        id = vector(total, 0);
        for(int i = 0; i < total; i++)
            id[i] = i;
        for(int i = 0; i < n; i += 2)
            connect(row[i] / 2, row[i + 1] / 2);
        unordered_set<int> set; // 找有多少组互相坐错位置的情侣对，就是找最终有多少不同的id
        for(int i = 0; i < n; i++) {
            set.insert(find(row[i] / 2));
        }
        return total - set.size();
    }

    int find(int p) {
        if(id[p] != p) id[p] = find(id[p]);
        return id[p];
    }
    void connect(int p, int q) {
        id[find(p)] = find(q);
    }

    /*
     * 这样做可以取到最少交换次数的依据 将位置i和i+1(分别叫左边、右边) 统称为第i个情侣位
     *
     * 假设现在在处理第i个情侣位，前面i-1个情侣位已经正确，接下来如何处理使总交换次数最少?
     * 固定左边或者右边的人 找他们的情侣交换过来，一次交换可以使当前情侣位正确
     * 如果两个人都调走，则需要2次交换才能使当前情侣位正确，显然前一种方法更好
     *
     * 交换左边还是右边? 前置情侣位都已正确，要交换来的人只能从更右边的位置找
     * 1.如果与左边、右边配对的情侣 不在同一个情侣位
     * 那么交换左边 或者 右边都只能减少1个待处理的情侣位
     * 比如 27 35 46。
     * 交换左边的2，将6换过来，得到 67 35 42
     * 交换右边的7，将3换过来，得到 23 75 46
     * 2. 如果与左边、右边配对的情侣 在同一个情侣位
     * 那么左边 或者 右边都能减少2个待处理的情侣位
     * 如 27 36
     * 交换i位置的2，将6换过来，得到 67 32; 交换i+1位置的7，将3换过来，得到 23 76
     * 因此，对于第i个情侣位，所以交换左边 或者 右边并不影响结果
     *
     * 是否存在 当前情侣位不处理，等后续遇到别的需要处理的情侣位时 顺便就处理了 这样节约交换次数 ?
     * 将当前情侣位i和后续情侣位j整体互换位置，不影响别的情侣位
     * 那么现在处理j，依然是回到了依次处理的情况 二者等价。
     * 或者说能被顺带处理的情侣位，他们属于 同一组互相做错位置的情侣，是等价关系。
     * 因此依次处理即可
     *
     * 初始时，处理第0个情侣位，前置可以认为有0个情侣位正确，也满足上述推导
     */

    /*
     * 根据上述推导，按推导过程模拟 计算模拟过程的交换次数即可。
     */
    int minSwapsCouples2(vector<int>& row){
        unordered_map<int, int> map; // 人的编号 -> 人的位置
        int ans = 0, n = row.size();
        for(int i = 0; i < n; i++)
            map[row[i]] = i;
        for(int i = 0; i < n; i += 2) {
            if(row[i] / 2 == row[i + 1] / 2) continue;
            // 交换row[i + 1]和row[i]对应的情侣
            int couple = row[i] % 2 == 0 ? row[i] + 1 : row[i] - 1;
            int j = map[couple];
            swap(row[j], row[i + 1]);
            map[row[j]] = j;
            ans++;
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}