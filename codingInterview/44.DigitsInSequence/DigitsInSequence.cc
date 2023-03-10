#include <cmath>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

// 面试题44：数字序列中某一位的数字
// 题目：数字以0123456789101112131415…的格式序列化到一个字符序列中。在这
// 个序列中，第5位（从0开始计数）是5，第13位是1，第19位是4，等等。请写一
// 个函数求任意位对应的数字。

class Solution {
   public:
    int digitAtIndex(int index) {
        if (index < 0) return -1;

        int digits = 1;
        while (true) {
            int numbers = countOfIntegers(digits);
            if (index < numbers * digits) {
                return digitAtIndex(index, digits);
            }

            index -= numbers * digits;
            ++digits;
        }
        return -1;
    }

   private:
    // digits位的数字共有多少
    int countOfIntegers(int digits) {
        if (digits == 1) return 10;

        int count = (int)std::pow(10, digits - 1);
        return 9 * count;
    }

    int digitAtIndex(int index, int digits) {
        int number = beginNumber(digits) + index / digits;  //找到的数字
        int indexFromRight =
            digits - index % digits;  //找到的数字的第几位,从右边数(从1开始)
        for (int i = 1; i < indexFromRight; ++i) {
            //得到那一位数
            number /= 10;
        }
        return number % 10;
    }

    // digits位数的第一个数
    int beginNumber(int digits) {
        if (digits == 1) return 0;

        return (int)std::pow(10, digits - 1);
    }
};

// ====================测试代码====================
void test(const char* testName, int inputIndex, int expectedOutput) {
    Solution solution;
    if (solution.digitAtIndex(inputIndex) == expectedOutput)
        cout << testName << " passed." << endl;
    else
        cout << testName << " FAILED." << endl;
}

int main() {
    test("Test1", 0, 0);
    test("Test2", 1, 1);
    test("Test3", 9, 9);
    test("Test4", 10, 1);
    test("Test5", 189, 9);   // 数字99的最后一位，9
    test("Test6", 190, 1);   // 数字100的第一位，1
    test("Test7", 1000, 3);  // 数字370的第一位，3
    test("Test8", 1001, 7);  // 数字370的第二位，7
    test("Test9", 1002, 0);  // 数字370的第三位，0
    return 0;
}