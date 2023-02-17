#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

// 面试题63：股票的最大利润
// 题目：假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖交易该股
// 票可能获得的利润是多少？例如一只股票在某些时间节点的价格为{9, 11, 8, 5,
// 7, 12, 16, 14}。如果我们能在价格为5的时候买入并在价格为16时卖出，则能
// 收获最大的利润11。

class Solution {
   public:
    int maxDif(vector<int> nums) {
        if (nums.size() < 2) return 0;
        int min = nums[0];
        int maxDif = nums[1] - min;
        for (int i = 2; i < nums.size(); ++i) {
            if (nums[i - 1] < min) {
                min = nums[i - 1];
            }

            int currrentDif = nums[i] - min;
            if (currrentDif > maxDif) {
                maxDif = currrentDif;
            }
        }
        return maxDif;
    }
};

int main() {
    Solution solution;
    vector<int> nums{9, 11, 8, 5, 7, 12, 16, 14};
    cout << solution.maxDif(nums) << endl;
    return 0;
}