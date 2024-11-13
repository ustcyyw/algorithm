/**
 * @Time : 2024/11/12-8:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
 /*
  * 出现次数最多的任务数量记为 max_cnt
  * 安排一个出现次数为max_cnt的任务 因为间隔要求 至少需要 (n + 1) * (max_cnt - 1) + 1的时间
  * (n + 1) * (max_cnt - 1) + 1，这个时间的计算
  * 可以形象地想成 一共有 max_cnt 行 每行有 n + 1个位置
  * 每行的第一个位置安排任务，那么相同任务之间间隔了n 并且安排了max_cnt个任务
  * 只不过最后一行只使用了第一个位置
  * 例如 n = 3 时，有任务a出现次数最多 出现了3次
  * a x x x
  * a x x x
  * a
  *
  * 如果有多个出现次数为max_cnt的任务呢?
  * 还是上述的形象的思维 安排了第一个出现最多的任务后 还剩下n列可用
  * 由于最后一行比较特殊
  * 对最后一行对情况进行分类 记出现次数max_cnt的任务有total个
  * 1.total >= n+1个 那么最后一行能被占满 如n = 2, a b c d 4个任务都出现了3次
  * a b c d
  * a b c d
  * a b c d
  * 而其它所有任务 就都可以按列一次安排都将满足间隔条件 并且不浪费任何时间
  * 比如 e 也出现了3次 f出现了1次 g出现了一次 那么可以这样排列
  * a b c d e f
  * a b c d e g
  * a b c d e
  * 或者e现了2次 f出现了2次 那么可以这样排列
  * a b c d e f
  * a b c d e
  * a b c d f
  * 这种情况下 答案就是任务数本身
  *
  * 2. total < n 最后一行没被占满 如 n = 2, a b 个任务都出现了3次
  * a b x x
  * a b x x
  * a b
  * 实质上 在不安排其它任务的情况下 耗时为 (n + 1) * (max_cnt - 1) + total.
  * 后续其它任务依旧是按列填充 依旧可以满足间隔条件
  * 只不过未必能填充满因安排最大频率任务所带来的空闲时间
  * 没有填充满 如e和f各出现1次
  * a b e x
  * a b f x
  * a b
  * 答案是 (n + 1) * (max_cnt - 1) + total，此时因为有空闲时间 任务数 < (n + 1) * (max_cnt - 1) + total
  * 填充满后的继续安排 如d e f各出现2次
  * a b d e
  * a b d f
  * a b e f
  * 答案就是任务数本身， 此时因为填充满了并且还有继续安排 任务数 >= (n + 1) * (max_cnt - 1) + total
  *
  *
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> cnt(26, 0);
        for(char c : tasks)
            cnt[c - 'A']++;
        int max_val = 0, total = 0;
        for(int num : cnt)
            max_val = max(max_val, num);
        for(int num : cnt)
            if(num == max_val) total++;
        if(total >= n + 1) return tasks.size();
        return max((int)tasks.size(), (n + 1) * (max_val - 1) + total);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}