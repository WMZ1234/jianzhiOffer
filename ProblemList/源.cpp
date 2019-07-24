#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cassert>
#include <stdio.h>
//#include <pthread.h>
//#include <unistd.h>
//#include <windows.h>

using namespace std;


//*******************************二叉树******************************
// 二叉树的前序遍历
struct BinaryTreeNode {
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

void PreOrderRecursively(BinaryTreeNode* root) {//递归
	if (root == NULL) return;
	else {
		cout << root->m_nValue;
		PreOrderRecursively(root->m_pLeft);
		PreOrderRecursively(root->m_pRight);
	}
}

void PreOrderIteratively(BinaryTreeNode* root) {//非递归
	if (root == NULL) return;
	stack<BinaryTreeNode*> nodes;
	BinaryTreeNode *cur, *top;
	cur = root;
	while (cur != NULL||!nodes.empty()) {
		while (cur != NULL) {
			cout << cur->m_nValue;
			nodes.push(cur);
			cur = cur->m_pLeft;
		}

		top = nodes.top();
		nodes.pop();

		cur = top->m_pRight;
	}
}

// 二叉树的中序遍历
void InOrderRecursively(BinaryTreeNode* root) {//递归
	if (root == NULL) return;
	else {
		InOrderRecursively(root->m_pLeft);
		cout << root->m_nValue;
		InOrderRecursively(root->m_pRight);
	}
}

void InOrderIteratively(BinaryTreeNode* root) {//非递归
	if (root == NULL) return;
	stack<BinaryTreeNode*> nodes;
	BinaryTreeNode *cur, *top;
	cur = root;
	while (cur != NULL || !nodes.empty()) {
		while (cur != NULL) {
			nodes.push(cur);
			cur = cur->m_pLeft;
		}

		top = nodes.top();
		cout << top->m_nValue;
		nodes.pop();

		cur = top->m_pRight;
	}
}

// 二叉树的后序遍历
void PostOrderRecursively(BinaryTreeNode* root) {//递归
	if (root == NULL) return;
	else {
		PostOrderRecursively(root->m_pLeft);
		PostOrderRecursively(root->m_pRight);
		cout << root->m_nValue;
	}
}

void PostOrderIteratively(BinaryTreeNode* root) {//非递归
	if (root == NULL) return;
	BinaryTreeNode *cur = root, *last = NULL, *top;
	stack<BinaryTreeNode*> nodes;
	while (cur != NULL || !nodes.empty()) {
		while (cur!=NULL){
			nodes.push(cur);
			cur = cur->m_pLeft;
		}
		top = nodes.top();
		if (top->m_pRight == NULL || top->m_pRight == last) {//当前节点的右子节点为空或已被访问
			cout << top->m_nValue;
			nodes.pop();
			last = top;
		}
		else {
			cur = top->m_pRight;
		}
	}
}




// 二叉树的层序遍历
void LevelOrder(BinaryTreeNode* root) {
	if (root == NULL) return;
	queue<BinaryTreeNode*> nodes;
	BinaryTreeNode* cur;
	nodes.push(root);
	while (!nodes.empty()) {
		cur = nodes.front();
		nodes.pop();

		if (cur->m_pLeft != NULL) nodes.push(cur->m_pLeft);
		if (cur->m_pRight != NULL) nodes.push(cur->m_pRight);
	}
}


//******************************排序*******************************
//冒泡排序
void BubbleSort(int numbers[],int length) {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length - i; j++) {
			if (numbers[i] > numbers[j]) {
				int temp = numbers[i];
				numbers[i] = numbers[j];
				numbers[j] = temp;
			}
		}
	}
}

//选择排序
void SelectSort(int numbers[], int length) {
	for (int i = 0; i < length; i++) {
		int indice = i;
		for (int j = i + 1; j < length; j++) {
			if (numbers[indice] > numbers[j])
				indice = j;
		}

		if (i != indice) {
			int temp = numbers[i];
			numbers[i] = numbers[indice];
			numbers[indice] = temp;
		}
	}
}

//插入排序
void InsertSort(int numbers[], int length) {
	for (int i = 1; i < length; i++) {
		int current = numbers[i];
		int preIndice = i - 1;
		while (0 <= preIndice&&numbers[preIndice] > current) {
			numbers[preIndice + 1] = numbers[preIndice];
			preIndice--;
		}
		numbers[preIndice + 1] = current;
	}
}

//快速排序
void QuickSort(int numbers[], int length) {
	int start = 0;
	int end = length - 1;
	if (start >= end) return;
	int current = numbers[start];
	while (start != end) {
		while (numbers[end] >= current&&start < end) end--;
		while (numbers[start] <= current&&start < end) start++;
		if (end > start) {
			int temp = numbers[start];
			numbers[start] = numbers[end];
			numbers[end] = temp;
		}
	}
	numbers[0] = numbers[start];
	numbers[start] = current;
	QuickSort(numbers, start);
	QuickSort(numbers + start + 1, length - start - 1);
}

//希尔排序
void ShellSort(int numbers[],int length) {
	for (int gap = length / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < length; i++) {
			int j = i;
			int current = numbers[i];
			while (j - gap >= 0 && numbers[j - gap] > current) {
				numbers[j] = numbers[j - gap];
				j -= gap;
			}
			numbers[j] = current;
		}
	}
}


// 判断两个字符串是否相等，不考虑顺序
bool IsSame(string str1, string str2) {
	int count[128];
	for (int i = 0; i < 128; i++)
		count[i] = 0;

	for (int i = 0; i < str1.length(); i++) count[str1[i] - '0']++;
	for (int i = 0; i < str2.length(); i++) count[str2[i] - '0']--;

	for (int i = 0; i < 128; i++) {
		if (count[i] != 0) return false;
	}
	return true;
}

// memmove和memcopy
void* _memcopy(void* dest, const void* src, size_t count) {
	char* temp_dest = (char*)dest;
	const char* temp_src = (const char*)src;

	while (count--)
		*temp_dest++ = *temp_src++;
	return temp_dest;
}

void* _memmove(void* dest, const void* src, int count) {
	char* temp_dest = (char*)dest;
	const char* temp_src = (const char*)src;

	if (temp_src < temp_src) {
		temp_src = temp_src + count - 1;
		temp_dest = temp_dest + count - 1;
		while (count--)
			*temp_dest-- = *temp_src--;
	}
	else if (temp_src > temp_dest) {
		while (count--)	{
			*temp_dest++ = *temp_src++;
		}
	}
	return temp_dest;
}

//镜像二叉树
void SymmetryBinaryTree(BinaryTreeNode* root) {
	if (root == NULL || (root->m_pLeft == NULL&&root->m_pRight == NULL))
		return;
	BinaryTreeNode* tmp = root->m_pLeft;
	root->m_pLeft = root->m_pRight;
	root->m_pRight = tmp;

	if (root->m_pLeft != NULL)
		SymmetryBinaryTree(root->m_pLeft);
	if (root->m_pRight != NULL)
		SymmetryBinaryTree(root->m_pRight);
}

//判断是否为对称二叉树
bool IsSymmetricalCore(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2) {
	if (pRoot1 == NULL&&pRoot2 == NULL) return true;
	if (pRoot1 == NULL) return false;
	if (pRoot2 == NULL) return false;
	if (pRoot1->m_nValue != pRoot2->m_nValue) return false;

	return IsSymmetricalCore(pRoot1->m_pLeft, pRoot2->m_pRight)&&IsSymmetricalCore(pRoot1->m_pRight, pRoot2->m_pLeft);
}

bool IsSymmetrical(BinaryTreeNode* root) {
	return IsSymmetricalCore(root, root);
}


// 12 矩阵中的路径
bool HasPathCore(const char* matrix, int rows, int cols, int row, int col, const char* str, int& pathLength, bool* visited) {
	if (str[pathLength] == '\0') return true;
	bool hasPath = false;
	if (row<rows&&col<cols&&str[pathLength] == matrix[row*cols + col]&&visited[row*cols+col]==false) {
		visited[row*cols + col] = true;
		pathLength++;

		hasPath = HasPathCore(matrix, rows, cols, row - 1, col, str, pathLength, visited) ||
			HasPathCore(matrix, rows, cols, row + 1, col, str, pathLength, visited) ||
			HasPathCore(matrix, rows, cols, row, col-1, str, pathLength, visited) ||
			HasPathCore(matrix, rows, cols, row, col+1, str, pathLength, visited);

		if (!hasPath) {
			pathLength--;
			visited[row*cols + col] = false;
		}
	}
	return hasPath;
}

bool HasPath(const char* matrix, int rows, int cols, const char* str) {
	bool* visited = new bool[rows*cols];
	memset(visited, 0, rows*cols);

	int pathLength = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (HasPathCore(matrix, rows, cols, i, j, str, pathLength,visited)) {
				return true;
			}
		}
	}
	delete[] visited;
	return false;
}

//汉诺塔
void hannoi(int n, char A, char B, char C)  // 把A盘里面的圆圈转移到C盘里面【A--C】。
{
	if (n == 1)
	{
		cout << "移动圆圈" << n << "从盘" << A << "盘" << C << endl;  //把最后一个圆环从起点盘移动到目标盘。  递归基
	}	
	else	{
		hannoi(n - 1, A, C, B);  // 把N-1个圆环从起点盘移动到（当前）没有任何圆环的过度盘；通过B、C盘在此函数调用中调用位置的互换，来实现把N-1个圆环从A盘到B盘的转移【A--B】。
		cout << "移动圆圈" << n << "从盘" << A << "盘" << C << endl;
		hannoi(n - 1, B, A, C);  // 把N-1个圆环从过渡盘移动到目标盘（模仿1和2的操作方法来实现）；通过A、B盘在此函数调用中位置的互换，来实现N-1个圆环从B盘到C盘的转移【B--C】。
	}
}

// 剪绳子 动态规划
int maxProductAfterCutting(int length) {
	if (length < 2) return 0;
	if (length == 2) return 1;
	if (length == 3) return 2;

	int* maxs = new int[length + 1];
	maxs[0] = 0;
	maxs[1] = 1;
	maxs[2] = 2;
	maxs[3] = 3;

	for (int i = 4; i <= length; i++) {
		int max = 0;
		for (int j = 0; j <= i / 2; j++) {
			if (max < maxs[j] * maxs[i - j])
				max = maxs[j] * maxs[i - j];
		}
		maxs[i] = max;
	}

	int maxProduct = maxs[length];	
	delete[] maxs;
	return maxProduct;
}

// 15 二进制中1的个数
int CountOne(int number) {
	int count = 0;
	while (number) {
		count++;
		number = number&(number - 1);
	}
	return count;
}


//二叉树的深度
int DepthOfBinaryTree(BinaryTreeNode* root) {
	if (root == NULL) return 0;
	int left = DepthOfBinaryTree(root->m_pLeft);
	int right = DepthOfBinaryTree(root->m_pRight);

	return left > right ? left + 1 : right + 1;
}

// 反转链表指定节点区间
struct ListNode {
	int m_nValue;
	ListNode* m_pNext;
	ListNode(int x) :m_nValue(x), m_pNext(NULL) {}
};

ListNode* listExchangeOrder(ListNode* head, int from, int to) {
	ListNode* dummy = new ListNode(0);
	dummy->m_pNext = head;
	ListNode* pPrev = dummy;
	ListNode* pCur = dummy->m_pNext;
	for (int i = 1; i < from; i++) {
		pPrev = pPrev->m_pNext;
		pCur = pCur->m_pNext;
	}

	ListNode* pNext = pCur->m_pNext;
	for (int i = 0; i < to - from; i++) {
		pCur->m_pNext = pNext->m_pNext;
		pNext->m_pNext = pPrev->m_pNext;
		pPrev->m_pNext = pNext;
		pNext = pCur->m_pNext;
	}
	return dummy->m_pNext;
}

// 反转链表
ListNode* ReverseList(ListNode* head) {
	ListNode* pPrev = NULL;
	ListNode* pReversedHead = NULL;
	ListNode* pCurrent = head;
	while (pCurrent != NULL) {
		ListNode* pNext = pCurrent->m_pNext;
		if (pCurrent->m_pNext == NULL) pReversedHead = pCurrent;
		pCurrent->m_pNext = pPrev;
		pPrev = pCurrent;
		pCurrent = pNext;
	}
	return pReversedHead;
}

// 长度为n的数组x，0<=a<=b<n,求x[b]-x[a]最大值
int MaxDifference(int x[], int n) {
	int a = x[0] < x[1] ? x[0] : x[1];
	int b = x[1] - x[0];
	for (int i = 2; i < n; i++) {
		if (x[i] - a > b) b = x[i] - a;
		if (x[i] < a) a = x[i];
	}
	return b;
}

/* 背包问题和硬币问题*/
//1. 01背包问题
/*
w:重量数组
v:价值数组
n：物品数
C：背包容量
*/
int KnapSack(int* w, int* v, int n, int C) {//二维数组
	int** dp = new int*[n + 1];
	for (int i = 0; i <= n; i++)
		dp[i] = new int[C + 1];

	for (int i = 0; i <= n; i++)
		dp[i][0] = 0;
	for (int j = 0; j <= C; j++)
		dp[0][j] = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= C; j++) {
			if (w[i - 1] > j) dp[i][j] = dp[i - 1][j];
			else dp[i][j] = dp[i - 1][j] > (dp[i - 1][j - w[i - 1]] + v[i - 1]) ? dp[i - 1][j] : (dp[i - 1][j - w[i - 1]] + v[i - 1]);
		}
	}
	int ret = dp[n][C];
	for (int i = 0; i <= n; i++)
		delete[] dp[i];
	return ret;
}

int KnapSack01(int* w, int* v, int n, int C) {//一维数组
	int* dp = new int[C + 1];
	for (int i = 0; i <= C; i++) {
		dp[i] = w[0] > i ? 0 : v[0];
	}

	for (int i = 1; i < n; i++) {
		for (int j = C; j >= w[i]; j--)
			dp[j] = dp[j] > (v[i] + dp[j - w[i]]) ? dp[j] : (v[i] + dp[j - w[i]]);
	}
	int ans = dp[C];
	delete[] dp;
	return ans;
}

//2.硬币问题
int Coin(int* coinvalue, int n,int value) {
	int* dp = new int[value + 1];
	dp[0] = 0;
	for (int i = 1; i <= value; i++) {
		dp[i] = INT_MAX;
		for (int j = 0; j < n; j++) {
			if (i >= coinvalue[j] && dp[i] > dp[i - coinvalue[j]] + 1)
				dp[i] = dp[i - coinvalue[j]] + 1;
		}
	}
	int ans = dp[value];
	delete[] dp;
	return ans;
}

//3.割绳子问题，是绳子长度乘积最大
int cutrope(int length) {
	if (length < 2) return 0;
	if (length == 2) return 1;
	if (length == 3) return 2;

	int* dp = new int[length + 1];
	dp[0] = 0;
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 3;
	for (int i = 4; i <= length; i++) {
		dp[i] = 0;
		for (int j = 0; j <= i / 2; j++) {
			dp[i] = dp[i] > (dp[j] * dp[i - j]) ? dp[i] : (dp[j] * dp[i - j]);
		}
	}
	int ans = dp[length];
	delete[] dp;
	return ans;
}

//数组中三数之和等于某值，每个元素不能重复使用
void DFS(vector<vector<int>>& ret, vector<int>& nums, int pos, int target, int count,
	int sum, vector<int>& path) {//回溯法
	if (count == 3) {
		if (sum == target) ret.push_back(path);
		return;
	}

	for (int i = pos; i < nums.size(); i++) {
		if (i != pos&&nums[i] == nums[i - 1]) continue;
		if ((sum + nums[i] + (2 - count)*nums[nums.size() - 1]) < target) continue;
		if ((sum + (3 - count)*nums[i]) > target) break;
		path.push_back(nums[i]);
		DFS(ret, nums, i + 1, target, count + 1, sum + nums[i], path);
		path.pop_back();
	}
}

vector<vector<int>> threeSum(vector<int> nums) {
	sort(nums.begin(), nums.end());
	vector<vector<int>> ret;
	vector<int> path;
	DFS(ret, nums, 0, 0, 0, 0, path);
	return ret;
}

vector<vector<int>> triSum(vector<int> nums,int target) {//非回溯法
	vector<vector<int>> ret;
	sort(nums.begin(), nums.end());
	int len = nums.size();
	for (int i = 0; i < len - 2; i++) {
		if (i > 0 && nums[i] == nums[i - 1]) continue;
		if ((nums[i] + nums[len - 2] + nums[len - 1]) < target) continue;
		if ((nums[i] + nums[i + 1] + nums[i + 2]) > target) break;
		int j = i + 1;
		int k = len - 1;
		while (j < k) {
			int sum = nums[i] + nums[j] + nums[k];
			if (sum > target) k--;
			else if (sum < target) j++;
			else {
				ret.push_back({ nums[i],nums[j],nums[k] });
				do { ++j; } while (nums[j] == nums[j - 1] && j < k);
				do { --k; } while (nums[k] == nums[k + 1] && j < k);
			}			
		}
	}
	return ret;
}

//排列组合
void permutation(vector<int> nums,int start,int end) {//全排列
	if (start == end) {
		for (int i = 0; i < end; i++)
			cout << nums[i] << ' ';
		cout << endl;
	}
	for (int i = start; i < end; i++) {
		int tmp = nums[i];//交换nums[i]nums[start]
		nums[i] = nums[start];//相当于更换数组的开头
		nums[start] = tmp;

		permutation(nums, start + 1, end);//分解为子问题[start+1,end)上的全排列

		tmp = nums[i];//交换回来
		nums[i] = nums[start];
		nums[start] = tmp;
	}
	
}

void combination(vector<int>& nums, int n, int k, int pos, int count, vector<bool>& visited) {//组合问题
	if (count == k) {
		for (int i = 0; i < n; i++) {
			if (visited[i]) cout << nums[i] << ' ';
		}
		cout <<endl;
		return;
	}
	if (pos == n) return;
	if (!visited[pos]) {
		visited[pos] = true;
		combination(nums, n, k, pos + 1, count + 1, visited);
		visited[pos] = false;
	}
	combination(nums, n, k, pos + 1, count, visited);
}

//二叉树深度
int TreeDepth(BinaryTreeNode* pRoot) {
	if (pRoot == nullptr) return 0;

	int left = TreeDepth(pRoot->m_pLeft);
	int right = TreeDepth(pRoot->m_pRight);

	return left > right ? (left + 1) : (right + 1);
}

//判断平衡二叉树
//1.递归方法
bool IsBalanced1(BinaryTreeNode* pRoot) {
	if (pRoot == nullptr) return true;

	int left = TreeDepth(pRoot->m_pLeft);
	int right = TreeDepth(pRoot->m_pRight);
	if (left - right > 1 || left - right < -1) return false;

	return IsBalanced1(pRoot->m_pLeft) && IsBalanced1(pRoot->m_pRight);
}

//2.每个节点只遍历一次的方法
bool IsBalanced(BinaryTreeNode* pRoot, int* depth) {
	if (pRoot == nullptr) {
		*depth = 0;
		return true;
	}

	int left, right;
	if (IsBalanced(pRoot->m_pLeft, &left) && IsBalanced(pRoot->m_pRight, &right)) {
		int diff = left - right;
		if (diff <= 1 && diff >= -1) {
			*depth = left > right ? (left + 1) : (right + 1);
			return true;
		}
	}
	return false;
}
bool IsBalanced2(BinaryTreeNode* pRoot) {
	int depth = 0;
	return IsBalanced(pRoot, &depth);
}


//数组中只出现一次的两个数字，其他数字都出现两次
bool IsBit1(int num, unsigned int indexBit) {//判断数字从右边的第indexBit位是否为1
	num = num >> indexBit;
	return (num & 1);
}

unsigned int FindFirstBits1(int num) {//从右开始第一个是1的位
	int indexBit = 0;
	while (((num & 1) == 0) && (indexBit < 8 * sizeof(int))) {
		num = num >> 1;
		indexBit++;
	}
	return indexBit;
}

void FindNumsAppearOnce(int data[], int length, int* num1, int* num2) {
	int sum = 0;
	for (int i = 0; i < length; i++) sum ^= data[i];

	int indexBit1 = FindFirstBits1(sum);

	*num1 = *num2 = 0;
	for (int i = 0; i < length; i++) {
		if (IsBit1(data[i],indexBit1)) *num1 ^= data[i];
		else *num2 ^= data[i];
	}
}

//一个递增数列中和为s的两个数字
void FindNumbersWithSum(int data[], int length, int sum, int* num1, int* num2) {
	int i = 0, j = length - 1;
	while (i < j) {
		if (sum == data[i] + data[j]) {
			*num1 = data[i];
			*num2 = data[j];
			return;
		}
		else if (sum < data[i] + data[j]) j--;
		else i++;
	}
}

//输入一个正数s，打印出所有和为s的连续正数序列
void PrintContinuousSequence(int wsmall, int big) {
	for (int i = wsmall; i <= big; i++)
		cout << i << ' ';
	cout << endl;
}

void FindContinuousSequence(int sum) {
	int wsmall = 1;
	int big = 2;
	int mid = (sum + 1) / 2;
	int curSum = wsmall + big;
	while (wsmall < mid) {
		if (curSum == sum) PrintContinuousSequence(wsmall, big);
		while (curSum > sum&&wsmall < mid) {
			curSum -= wsmall;
			wsmall++;
			if (curSum == sum) PrintContinuousSequence(wsmall, big);
		}
		big++;
		curSum += big;
	}
}

//翻转单词顺序  ?存在问题
void Reverse(char *pBegin, char *pEnd) {
	if (pBegin == nullptr || pEnd == nullptr) return;
	while (pBegin < pEnd) {
		char tmp = *pBegin;
		*pBegin = *pEnd;
		*pEnd = tmp;

		pBegin++; pEnd--;
	}
}

void ReverseSentence(char *pData) {
	if (pData == nullptr) return;
	char *pBegin = pData;
	char *pEnd = pData;
	while (*pEnd != '\0') pEnd++;
	pEnd--;
	Reverse(pBegin, pEnd);

	pBegin = pEnd = pData;
	while (*pBegin != '\0') {
		if (*pBegin == ' ') {
			pBegin++;
			pEnd++;		
		}
		else if (*pEnd == ' ' || *pEnd == '\0') {
			Reverse(pBegin, --pEnd);
			pBegin = ++pEnd;
		}
		else pEnd++;
	}
}

//memcopy和memmove的实现
void* memcopy(void* dest, const void *src, size_t count) {
	assert(dest != nullptr || src != nullptr);
	char *tmp = (char *)dest;
	char *p = (char *)src;
	while(count--) {
		*tmp-- = *p--;
	}
	return dest;
}

void* memmove(void* dest, const void *src, size_t count) {
	assert(dest != nullptr || src != nullptr);
	if (dest < src) {
		char *tmp = (char*)dest;
		char *p = (char*)src;
		while (count--) *tmp++ = *p++;
	}
	else {
		char *tmp = (char*)dest + count - 1;
		char *p = (char*)src + count - 1;
		while (count--) *tmp-- = *p--;
	}
	return dest;
}

//******************************************************//
//模拟产生死锁
/*
//定义两把死锁
pthread_mutex_t m_mutex1;
pthread_mutex_t m_mutex2;
int A = 0, B = 0;

//线程1
void* threadFunc1(void* p) {
	pthread_mutex_lock(&m_mutex1);
	A = 1;
	printf("thread 1 write source A\n");
	//Sleep(0.0001);//延迟100微秒

	pthread_mutex_lock(&m_mutex2);
	B = 1;
	printf("thread 1 write source B\n");

	//解锁，实际上是跑不到这里的，因为前面已经死锁了
	pthread_mutex_unlock(&m_mutex2);
	pthread_mutex_unlock(&m_mutex1);

	return NULL;
}

//线程2
void* threadFunc2(void* p) {
	pthread_mutex_lock(&m_mutex2);
	B = 1;
	printf("thread 2 write source B\n");
	//Sleep(0.0001);

	pthread_mutex_lock(&m_mutex1);
	A = 1;
	printf("thread 2 write source A\n");

	pthread_mutex_unlock(&m_mutex1);
	pthread_mutex_unlock(&m_mutex2);

	return NULL;
}

//对应于此问题的main函数
int main() {
	//初始化锁
	if (pthread_mutex_init(&m_mutex1, 0) != 0) {
		printf("init mutex 1 failed\n");
		return -1;
	}
	if (pthread_mutex_init(&m_mutex2, 0) != 0) {
		printf("init mutex 2 failed\n");
		return -1;
	}

	//初始化线程
	pthread_t hThread1;
	pthread_t hThread2;
	if (pthread_create(&hThread1, NULL, &threadFunc1, NULL) != 0) {
		printf("create thread 1 failed\n");
		return -1;
	}
	if (pthread_create(&hThread2, NULL, &threadFunc2, NULL) != 0) {
		printf("create thread 2 failed\n");
		return -1;
	}

	while (1) Sleep(1);

	pthread_mutex_destroy(&m_mutex1);
	pthread_mutex_destroy(&m_mutex2);
	return 0;	
}
*/



//******************************************************//

int main() {


	/*vector<int> nums = { -1,-1,2,2,0,-2,3 };
	vector<vector<int>> ret = triSum(nums,0);
	for (int i = 0; i < ret.size(); i++) {
		for (int j = 0; j < ret[i].size(); j++) {
			cout << ret[i][j] << ' ';
		}
		cout <<endl;
	}*/

	/*int w[3] = { 1,3,5 };
	int v[5] = { 6,3,5,4,6 };
	cout <<cutrope(5)<<endl;
	cout << cutrope(6) << endl;
	cout << cutrope(7) << endl;
	cout << cutrope(8) << endl;
	cout << cutrope(9) << endl;
	cout << cutrope(10) << endl;
	cout << cutrope(11) << endl;*/


	/*ListNode* L = new ListNode(0);
	ListNode *r, *p;
	r = L;
	for (int i = 0; i < 6; i++) {
		p = new ListNode(i);
		r->m_pNext = p;
		r = p;
	}
	r->m_pNext = NULL;
	ListNode* tmp1 = L->m_pNext;
	while (tmp1 != NULL) {
		cout << tmp1->m_nValue << ' ';
		tmp1 = tmp1->m_pNext;
	}
	cout << endl;
	ListNode* tmp = ReverseList(L->m_pNext);
	while (tmp != NULL) {
		cout << tmp->m_nValue << ' ';
		tmp = tmp->m_pNext;
	}*/

	system("pause");
	return 0;
}

