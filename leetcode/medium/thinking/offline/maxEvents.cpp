/**
 * @Time : 2022/10/9-10:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个数组 events，其中 events[i] = [startDayi, endDayi] ，表示会议 i 开始于 startDayi ，结束于 endDayi 。

你可以在满足 startDayi <= d <= endDayi 中的任意一天 d 参加会议 i 。注意，一天只能参加一个会议。

请你返回你可以参加的 最大 会议数目。

 

示例 1：



输入：events = [[1,2],[2,3],[3,4]]
输出：3
解释：你可以参加所有的三个会议。
安排会议的一种方案如上图。
第 1 天参加第一个会议。
第 2 天参加第二个会议。
第 3 天参加第三个会议。
示例 2：

输入：events= [[1,2],[2,3],[3,4],[1,2]]
输出：4
 

提示：​​​​​​

1 <= events.length <= 105
events[i].length == 2
1 <= startDayi <= endDayi <= 105

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximum-number-of-events-that-can-be-attended
 */
class Solution {
public:
    /**
     * 类似于离线算法的思想
     * 随着时间戳time的变化，所有start <= time && end >= time的会议都可用
     * 在可用的会议中，选择结束时间最早的优先使用，因为结束时间晚的后续被用上可能更大
     * 如果先选择结束时间晚的，那么早结束的可能就错过了
     */
    int max_time = 1e5;
    int maxEvents(vector<vector<int>>& events) {
        vector<vector<int>> time_line(max_time + 1, vector(0, 0));
        int cnt = 0, n = events.size();
        for(int i = 0; i < n; i++)
            time_line[events[i][0]].push_back(i);
        priority_queue<int, vector<int>, greater<>> pq;
        for(int time = 1; time <= max_time; time++){
            for(int i : time_line[time]) pq.push(events[i][1]);
            while (!pq.empty() && pq.top() < time) pq.pop(); // 已经失效的会议要弹出
            if(!pq.empty()){
                cnt++;
                pq.pop(); // 当前使用了的会议要弹出
            }
        }
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}