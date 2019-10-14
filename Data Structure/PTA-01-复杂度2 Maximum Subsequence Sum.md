### 题目：
Given a sequence of K integers { N
​1
​​ , N
​2
​​ , ..., N
​K
​​  }. A continuous subsequence is defined to be { N
​i
​​ , N
​i+1
​​ , ..., N
​j
​​  } where 1≤i≤j≤K. The Maximum Subsequence is the continuous subsequence which has the largest sum of its elements. For example, given sequence { -2, 11, -4, 13, -5, -2 }, its maximum subsequence is { 11, -4, 13 } with the largest sum being 20.

Now you are supposed to find the largest sum, together with the first and the last numbers of the maximum subsequence.

**Input Specification**

Each input file contains one test case. Each case occupies two lines. The first line contains a positive integer K (≤10000). The second line contains K numbers, separated by a space.

**Output Specification:**

For each test case, output in one line the largest sum, together with the first and the last numbers of the maximum subsequence. The numbers must be separated by one space, but there must be no extra space at the end of a line. In case that the maximum subsequence is not unique, output the one with the smallest indices i and j (as shown by the sample case). If all the K numbers are negative, then its maximum sum is defined to be 0, and you are supposed to output the first and the last numbers of the whole sequence.

**Sample Input:**

10
-10 1 2 3 4 -5 -23 3 7 -21

**Sample Output:**

10 1 4

### 要求分析：

该题目是最大子列和的进阶版，不仅要求输出最大子列和，还要求输出最大子列的首位和末位的数字。
我们采用贪心算法求得最大子列和，算法复杂度为O(N)，以下对题目进行解读：
1. 我们需要一个指针来记录并更新最大子列的首位和末尾的序号。
2. 当最大子序列之和小于0时，我们应该输出整个序列的首位和末尾，并且MaxSum = 0

下面是通过调试的25分**满分**算法：


```
/*本题除了要求出最大子列外，还需要得到子列前后位置的数字*/
#include <stdio.h>
#include <stdlib.h>
int k;
int a[100100];
int first, last, len;
int main(){
	scanf( "%d", &k );
	int MaxSum = -1;
	int ThisSum;
	for ( int i = 0; i < k; i++ ){
		scanf( "%d", &a[i] );
	}

	first = 0;			//随着序列的更新而更新的指针
	last = k-1;
	int tempFirst = 0;  //记录最大序列的标签
	ThisSum = 0;

	for ( int i = 0; i < k; i++ ){		//循环最终会得到MaxSum的值
		ThisSum = ThisSum + a[i];
		if ( ThisSum > MaxSum ){
			MaxSum = ThisSum;
			tempFirst = first;
			last = i;		//记录最后一个数
		}
		else if ( ThisSum < 0 ){
			ThisSum = 0;
			first = i + 1;	//记录下一个序列的第一个数
		}
		//printf("%d\n", a[tempFirst]); 设置的调试点

	}
	if ( MaxSum < 0 ){ 		//这一步需要对MaxSum的值进行处理
		tempFirst = 0;
		MaxSum = 0;
		last = k-1;
	}
	printf( "%d %d %d", MaxSum, a[tempFirst], a[last]);
}

```
