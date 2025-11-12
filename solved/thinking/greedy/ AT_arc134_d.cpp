/**
 * @Time : 2023/12/11-10:01 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 要得到最小字典序列 首先得保证前n个数的序列是递增的 然后才考虑后n个数的影响
 * 对于前n个数的处理 常规地使用单调栈来处理 得到序列a，相应地得出序列b
 * 最终答案在a + b序列中再做删减
 *
 * 对于所有a[j] = a[0] （最终答案一定是以1个a[0]或者多个a[0]为前缀的）
 * 找到所有b[j]中的最小值，记为val
 *
 * a + b 序列为：
 * (a[0], a[0], ... a[0]), a[j + 1], a[j + 2]... | (b[0], b[1],...,val,.., b[j]), b[j + 1] ...
 *
 * 如果val <= a[0]
 * 因为 a[0] > a[j + 1] >= a[j + 2] 可得 a[j + 1] < val, a[j + 2] < val ...
 * 并且由于val是满足a[j] = a[0]的b[j]中的最小值 b[0] < val, b[1] < val ...
 * 因为从a[j + 1] 到 val的前一个元素 都比val大。
 * 那么把他们都删掉 只保留val和其对应的那个a[0] 字典序会更小
 * 对于 val < a[0]的情况，显然应该只保留val和其对应的那个a[0]
 * 例如[2,2,2 | 3,1,2] --> [2 | 1]
 * 对于val = a[0]的情况，同样
 * 例如[2,2,2 | 3,2,2] --> [2 | 2]
 *
 * 如果val > a[0]
 * a[0] < b[0, j] 上的任意一个数，且a[0] < a[j + 1, a.size() - 1] 上任意一个数
 * 所以 a[0] < a[j + 1] 到 b[j]上任意一个数
 * 如果不以a[0]开头，想得到更小的字典序列，只可能让b[j + 1, b.size() - 1] 上的数开头
 * 但那要求将a序列全删掉，会导致b序列也全被删掉 矛盾了。
 * 因此 最终答案以a[0]开头。
 * 并且应该保存a[0]，因为删除任意一个a[0]，都会让更大的数前移一位，字典序增大
 * 所有a[0]都保留，那么b[0, j]都被保留。再考虑 a[j + 1, a.size() - 1] 上如何删除
 *
 * 此区间上大于b[0]的，肯定要删除，因为将他们都删除后，b[0]会前移动，让字典序更小
 * 例如[2,2,5,6 | 3,4,1,4] --> [2,2 | 3,4]
 *
 * 此区间上小于b[0]的，肯定不删除，因为将部分删除后，前移的元素都是更大；都删除，b[0]前移 也是让字典序更大
 *
 * 此区间上等于b[0]的，是否删除 还要看后续b[1],b[2]等的情况，为避免讨论的麻烦
 * 可以将 > b[0]的删除 记为序列c1; 将 >= b[0]的删除，记为序列c2。 取c1和c2中最小的即为答案
 */
#include<bits/stdc++.h>
using namespace std;
vector<int> a, b;

vector<int> getArr(int j) {
    vector<int> c;
    for(int i = 0; i < j; i++)
        c.push_back(a[i]);
    for(int i = 0; i < j; i++)
        c.push_back(b[i]);
    return c;
}

vector<int> compareTo(vector<int> c1, vector<int> c2) {
    for(int i = 0; i < (int)c1.size(); i++) {
        if(c1[i] > c2[i]) return c2;
        if(c1[i] < c2[i]) return c1;
    }
    return c1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    int n;
    cin >> n;
    for(int i = 0, num; i < n; i++) {
        cin >> num;
        while(!a.empty() && a.back() > num)
            a.pop_back(), b.pop_back();
        a.push_back(num), b.push_back(i);
    }
    for(int i = 0, j = 0, num; j < (int)b.size(); i++) {
        cin >> num;
        if(i == b[j]) b[j++] = num;
    }
    // 计算val
    int val = b[0];
    for(int i = 1; a[0] == a[i]; i++)
        val = min(val, b[i]);
    if(val <= a[0]) {
        cout << a[0] << " " << val << endl;
        return 0;
    }
    //val > a[0]的情况 得出序列c1和c2
    // lower_bound 找大于等于b[0]的最小元素的迭代器 用于删除 >= b[0]的元素
    int j1 = lower_bound(a.begin(), a.end(), b[0]) - a.begin();
    int j2 = upper_bound(a.begin(), a.end(), b[0]) - a.begin();
    vector<int> res = compareTo(getArr(j1), getArr(j2));
    for(int num : res)
        cout << num << " ";
}