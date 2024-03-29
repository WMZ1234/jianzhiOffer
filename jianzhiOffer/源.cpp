#include <iostream>
#include <stack>
#include <queue>

using namespace std;

//1.赋值运算符函数
//class CMyString {
//public:
//	CMyString(char *pData = nullptr);
//	CMyString(const CMyString& str);
//	CMyString& operator = (const CMyString& str);
//	~CMyString(void);
//private:
//	char* m_pData;
//};

//1.1第一种实现，有瑕疵
/*
//返回类型为引用，考虑a=b=c的连续赋值操作
//函数传参需要引用，这样避免了一次拷贝构造函数提高效率，同时为了不改变传入实例，需要加上const
//this==&str时，不需要执行任何操作
CMyString& CMyString::operator=(const CMyString& str) {
	if (this == &str) return *this;

	delete[] m_pData;
	m_pData = nullptr;

	m_pData = new char[strlen(str.m_pData) + 1];
	strcpy(m_pData, str.m_pData);

	return *this;
}
*/
//1.2第二种实现
//CMyString& CMyString::operator=(const CMyString& str) {
//	if (this != &str) {
//		CMyString strTemp(str);
//		char* pTemp = strTemp.m_pData;
//		strTemp.m_pData = m_pData;
//		m_pData = pTemp;
//	}
//	return *this;
//}

//2.singleton模式/单例模式
//只能生成一个实例
/*
public sealed class Singleton1{
	private Singleton1() {}
	private static Singleton1 instance = NULL;
	public static Singleton1 Instance{
		get{
		if (instance == NULL) instance = new Singleton1();
		return instance;
		}
	}
}
*/

//3.找出数组中重复的数字
//在一个长度为n的数组里所有的数字都在0~n-1之间
bool duplicate(int numbers[], int length, int* duplication) {
	if (numbers == nullptr || length < 2) return false;
	for (int i = 0; i < length; i++) {
		while (numbers[i] != i) {
			if (numbers[i] == numbers[numbers[i]]) {
				*duplication = numbers[i];
				return true;
			}

			int temp = numbers[i];
			numbers[i] = numbers[temp];
			numbers[temp] = temp;
		}
	}
	return false;
}
//不修改数组的情况,不确定找出所有的所有情况的重复数字
int countRange(const int* numbers, int length, int start, int end) {
	int count = 0;
	for (int i = 0; i < length - 1; i++) {
		if (start <= numbers[i] && numbers[i] <= end)
			count++;
	}
	return count;
}

int getDuplication(const int* numbers, int length) {
	if (numbers == nullptr || length < 2) return -1;
	int start = 0;
	int end = length - 1;
	while (start <= end) {
		int mid = (start + end) / 2;
		int count = countRange(numbers, length, start, mid);
		if (start == end) {
			if (count > 1) return start;
			else break;
		}

		if (count > (mid - start + 1)) end = mid;
		else start = mid + 1;
	}
	return -1;
}

//4.二维数组中的查找
bool Find(int* matrix, int rows, int columns, int number) {
	if (matrix == nullptr) return false;
	int i = 0, j = columns - 1;
	while (i < rows&&j >= 0) {
		if (matrix[i*columns + j] == number) return true;
		else if (matrix[i*columns + j] > number) j--;
		else i++;
	}
	return false;
}

//5.替换空格
void ReplaceBlank(char string[], int length) {
	int count = 0;
	for (int i = 0; i < length; i++) {
		if (string[i] == ' ') count += 3;
		else count += 1;
	}
	if (count == length) return;
	int originalCount = length;
	while (originalCount >= 0 && count > originalCount) {
		if (string[originalCount] == ' ') {
			string[count--] = '0';
			string[count--] = '2';
			string[count--] = '%';
		}
		else string[count--] = string[originalCount--];
	}
}

//6.从尾到头打印链表
struct ListNode {
	int m_nValue;
	ListNode* m_pNext;
};

void PrintListReversingly(ListNode* pHead) {
	if (pHead != nullptr) {
		if (pHead->m_pNext != nullptr)
			PrintListReversingly(pHead->m_pNext);
		printf("%d\t", pHead->m_nValue);
	}
}

//二叉树的遍历
struct BinaryTreeNode {
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

void PreOrder(BinaryTreeNode* pRoot) {
	if (pRoot == nullptr) return;
	else {
		printf("%d\t", pRoot->m_nValue);
		PreOrder(pRoot->m_pLeft);
		PreOrder(pRoot->m_pRight);
	}
}

void InOrder(BinaryTreeNode* pRoot) {
	if (pRoot == nullptr) return;
	else {
		PreOrder(pRoot->m_pLeft);
		printf("%d\t", pRoot->m_nValue);
		PreOrder(pRoot->m_pRight);
	}
}

void PostOrder(BinaryTreeNode* pRoot) {
	if (pRoot == nullptr) return;
	else {
		PreOrder(pRoot->m_pLeft);
		PreOrder(pRoot->m_pRight);
		printf("%d\t", pRoot->m_nValue);
	}
}

void PreOrderNonRecur(BinaryTreeNode* pRoot) {
	stack<BinaryTreeNode*> stack1;
	stack1.push(pRoot);
	BinaryTreeNode* pTemp = nullptr;
	while (!stack1.empty()) {
		pTemp = stack1.top();
		printf("%d\t", pTemp->m_nValue);
		stack1.pop();
		if (pTemp->m_pRight != nullptr) stack1.push(pTemp->m_pRight);
		if (pTemp->m_pLeft != nullptr) stack1.push(pTemp->m_pLeft);
	}
}

void InOrderNonRecur(BinaryTreeNode* pRoot) {
	stack<BinaryTreeNode*> stack1;
	BinaryTreeNode* cur = pRoot;
	while (!stack1.empty() || cur != nullptr) {
		while (cur) {
			stack1.push(cur);
			cur = cur->m_pLeft;
		}

		BinaryTreeNode* pTemp = stack1.top();
		stack1.pop();
		printf("%d\t", pTemp->m_nValue);

		cur = pTemp->m_pRight;
	}
}

void PostOrderNonRecur1(BinaryTreeNode* pRoot) {
	stack<BinaryTreeNode*> stack1;
	stack<BinaryTreeNode*> stack2;
	stack1.push(pRoot);
	while (!stack1.empty()) {
		BinaryTreeNode* cur = stack1.top();
		stack1.pop();
		if (cur->m_pLeft != nullptr) stack1.push(cur->m_pLeft);
		if (cur->m_pRight != nullptr) stack1.push(cur->m_pRight);
		stack2.push(cur);
	}

	while (!stack2.empty()) {
		printf("%d\t", stack2.top()->m_nValue);
		stack2.pop();
	}
}

void PostOrderNonRecur2(BinaryTreeNode* pRoot) {
	stack<BinaryTreeNode*> stack1;
	stack1.push(pRoot);
	BinaryTreeNode* h = pRoot;//记录上一个弹出的结点
	BinaryTreeNode* c = nullptr;//记录栈顶结点
	while (!stack1.empty()) {
		c = stack1.top();
		//c结点有左孩子并且左孩子没有被遍历（输出）过，并且右孩子也没有被遍历过
		if (c->m_pLeft != nullptr&&h != c->m_pRight&&c->m_pRight)
			stack1.push(c->m_pLeft);
		//c结点有右孩子并且右孩子没有被遍历过
		else if (c->m_pRight != nullptr&&h != c->m_pRight)
			stack1.push(c->m_pRight);
		else {
			BinaryTreeNode* pTemp = stack1.top();
			printf("%d\t", pTemp->m_nValue);
			stack1.pop();
			h = c;
		}
	}
}

void LevelOrder(BinaryTreeNode* pRoot) {
	queue<BinaryTreeNode*> queue1;
	queue1.push(pRoot);
	while (!queue1.empty()) {
		BinaryTreeNode* pTemp = queue1.front();
		queue1.pop();
		printf("%d\t", pTemp->m_nValue);

		if (pTemp->m_pLeft != nullptr) queue1.push(pTemp->m_pLeft);
		if (pTemp->m_pRight != nullptr) queue1.push(pTemp->m_pRight);
	}
}


//7.根据中序遍历和前序遍历重建二叉树
BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder) {
	int rootValue = startPreorder[0];
	BinaryTreeNode* root = new BinaryTreeNode();
	root->m_nValue = rootValue;
	root->m_pLeft = root->m_pRight = nullptr;

	if (startPreorder == endPreorder) {
		if (startInorder == endInorder&&*startPreorder == *startInorder)
			return root;
		else
			throw exception("Invalid input.");
	}

	int* rootInorder = startInorder;
	while (rootInorder <= endInorder && *rootInorder != rootValue)
		rootInorder++;
	if (rootInorder == endInorder&&*rootInorder != rootValue) throw exception("Invalid input.");

	int leftLength = rootInorder - startInorder;
	int* leftPreorderEnd = startPreorder + leftLength;
	if (leftLength > 0) root->m_pLeft = ConstructCore(startPreorder + 1, leftPreorderEnd, startInorder, rootInorder - 1);
	if (leftLength < endPreorder - startPreorder) root->m_pRight = ConstructCore(leftPreorderEnd + 1, endPreorder, rootInorder + 1, endInorder);
	return root;
}

BinaryTreeNode* Construct(int* preorder, int* inorder, int length) {
	return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}

//8.二叉树的下一个节点
struct BinaryTreeNodeAll{
	int m_nValue;
	BinaryTreeNodeAll* m_pLeft;
	BinaryTreeNodeAll* m_pRight;
	BinaryTreeNodeAll* m_pParent;
};

BinaryTreeNodeAll* GetNext(BinaryTreeNodeAll* pNode) {
	BinaryTreeNodeAll* pNext = nullptr;
	if (pNode->m_pRight != nullptr) {
		BinaryTreeNodeAll* pRight = pNode->m_pRight;
		while (pRight->m_pLeft != nullptr)
			pRight = pRight->m_pLeft;
		pNext = pRight;
	}
	else {
		BinaryTreeNodeAll* pCurrent = pNode;
		BinaryTreeNodeAll* pParent = pNode->m_pParent;
		while (pParent != nullptr&&pCurrent == pParent->m_pRight) {
			pCurrent = pParent;
			pParent = pParent->m_pParent;
		}
		pNext = pParent;
	}
	return pNext;
}

//9.两个栈实现一个队列
template<typename T>
class CQueue {
public:
	CQueue(void);
	~CQueue(void);

	void appendToTail(const T& node);
	T deleteHead();

private:
	stack<T> stack1;
	stack<T> stack2;
};

template<typename T>
void CQueue<T>::appendToTail(const T& node) {
	stack1.pop();
}

template<typename T>
T CQueue<T>::deleteHead() {
	if (stack2.size() <= 0) {
		while (!stack1.empty()) {
			stack2.push(stack1.top());
			stack1.pop();
		}
	}

	if (stack2.empty()) throw new exception("queue is empty!");

	T node = stack2.top();
	stack2.pop();
	return node;
}

//两个队列实现一个栈
template<typename T>
class CStack {
public:
	CStack(void);
	~CStack(void);

	void appendToTail(T node);
	T deleteHead();

private:
	queue<T> queue1;
	queue<T> queue2;
};

template<typename T>
void CStack<T>::appendToTail(T node) {
	queue1.push(node);
}

template<typename T>
T CStack<T>::deleteHead() {
	if (queue1.empty()) throw new exception("stack is empty!");
	while (queue1.size()>1) {
		queue2.push(queue1.front());
		queue1.pop();
	}
	T head = queue1.front();
	queue1.pop();

	while (!queue2.empty()) {
		queue1.push(queue2.front());
		queue2.pop();
	}
	return head;
}


//15.二进制中1的个数
int NumberOf1(int n) {
	int count = 0;
	while (n) {
		++count;
		n = n&(n - 1);
	}
	return count;
}

//17.打印从1到最大的n位数
void PrintNumber(char *number) {
	int length = strlen(number);
	bool isbeginning = true;
	for (int i = 0; i < length; i++) {
		if (isbeginning&&number[i] != '0')
			isbeginning = false;
		if (!isbeginning) printf("%c", number[i]);
	}
	if (isbeginning) printf("%c", '0');
	printf("\t");
}

void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index) {
	if (index == length) {
		PrintNumber(number);
		return;
	}

	for (int i = 0; i < 10; i++) {
		number[index] = i + '0';
		Print1ToMaxOfNDigitsRecursively(number, length, index + 1);
	}
}
void Print1ToMaxOfNDigits(int n) {
	if (n <= 0) return;
	char* number = new char[n + 1];
	number[n] = '\0';
	Print1ToMaxOfNDigitsRecursively(number, n, 0);
	delete[] number;
}

//18.在O(1)时间内删除链表节点
void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted) {
	//不是尾节点
	if (pToBeDeleted->m_pNext != nullptr) {
		ListNode* pNext = pToBeDeleted->m_pNext;
		pToBeDeleted->m_nValue = pNext->m_nValue;
		pToBeDeleted->m_pNext = pNext->m_pNext;

		delete pNext;
		pNext = nullptr;
	}
	//只有一个节点，删除头节点（也是尾节点）
	else if (*pListHead == pToBeDeleted) {
		delete pToBeDeleted;
		pToBeDeleted = nullptr;
		*pListHead = nullptr;		
	}
	//链表中有多个节点，删除尾节点
	else {
		ListNode* pNode = *pListHead;
		while (pNode->m_pNext != pToBeDeleted)
			pNode = pNode->m_pNext;
		pNode->m_pNext = nullptr;
		delete pToBeDeleted;
		pToBeDeleted = nullptr;
	}
}

//删除排序链表中的重复节点
void deleteDuplication(ListNode** pListHead) {
	ListNode* pPreNode = nullptr;
	ListNode* pNode = *pListHead;
	while (pNode != nullptr) {
		ListNode* pNext = pNode->m_pNext;
		bool needDelete = false;
		if (pNext != nullptr && pNode->m_nValue == pNext->m_nValue)
			needDelete = true;
		if (!needDelete) {
			pPreNode = pNode;
			pNode = pNext;
		}
		else {
			int value = pNode->m_nValue;
			ListNode* pToBeDel = pNode;
			while (pToBeDel != nullptr&&pToBeDel->m_nValue == value) {
				pNext = pToBeDel->m_pNext;
				delete pToBeDel;
				pToBeDel = nullptr;
				pToBeDel = pNext;
			}
			
			if (pPreNode == nullptr) *pListHead = pNext;
			else pPreNode->m_pNext = pNext;
			pNode = pNext;
		}
	}
}

//19.正则表达式匹配
bool matchCore(char* str, char* pattern) {
	if (*str == '\0'&&*pattern == '\0') return true;
	if (*str != '\0'&&*pattern == '\0') return false;

	if (*(pattern + 1) == '*') {
		if (*pattern == *str || (*pattern == '.'&&*str != '\0'))
			return matchCore(str + 1, pattern + 2) ||
			matchCore(str + 1, pattern) || matchCore(str, pattern + 2);
		else return matchCore(str, pattern + 2);
	}
	if (*str == *pattern || (*pattern == '.'&&*str != '\0')) return matchCore(str + 1, pattern + 1);
	return false;
}

//20.表示数值的字符串
bool scanUnsignedInteger(const char** str) {
	const char* before = *str;
	while (**str != '\0'&&**str >= '0'&&**str <= '9')
		++(*str);
	return *str > before;
}

bool scanInteger(const char** str) {
	if (**str == '+' || **str == '-') ++(*str);
	return scanUnsignedInteger(str);
}

bool isNumeric(const char* str) {
	if (str == nullptr) return false;
	bool numeric = scanInteger(&str);
	if (*str == '.') {
		++str;
		numeric = scanUnsignedInteger(&str) || numeric;
	}
	if (*str == 'e' || *str == 'E') {
		++str;
		numeric = scanInteger(&str) && numeric;
	}
	return numeric&&*str == '\0';
}

//21.调整数组顺序是奇数位于偶数前面
void RecorderOddEven(int* pData, unsigned int length) {
	if (pData == nullptr || length <=0 ) return;
	int* pBegin = pData;
	int* pEnd = pData + length - 1;
	while (pBegin < pEnd) {
		while (*pBegin & 0x1) pBegin++;
		while (!(*pEnd & 0x1)) pEnd--;
		if (pBegin < pEnd) {
			int temp = *pBegin;
			*pBegin = *pEnd;
			*pEnd = temp;
		}
	}
}

//23.链表中环的入口节点
//两个指针的相遇点
ListNode* MeetingNode(ListNode* pHead) {
	ListNode* pSlow = pHead;
	ListNode* pFast = pSlow->m_pNext;
	while (pSlow != pFast) {
		if (pFast->m_pNext == nullptr)
			return nullptr;
		pSlow = pSlow->m_pNext;
		pFast = pFast->m_pNext;
		if (pFast != nullptr) pFast = pFast->m_pNext;
	}
	return pSlow;
}

ListNode* EntryNodeOfLoop(ListNode* pHead) {
	ListNode* meetingNode = MeetingNode(pHead);
	if (meetingNode == nullptr) return nullptr;
	ListNode* pNode = meetingNode;
	int count = 1;
	while (pNode->m_pNext != meetingNode) {
		pNode = pNode->m_pNext;
		count++;
	}
	ListNode* pSlow = pHead;
	ListNode* pFast = pHead;
	while (count > 0) {
		pFast = pFast->m_pNext;
		count--;
	}
	while (pSlow != pFast) {
		pSlow = pSlow->m_pNext;
		pFast = pFast->m_pNext;
	}
	return pSlow;
}

//24.反转链表
ListNode* ReverseList(ListNode* pHead) {
	ListNode* pReversedHead = nullptr;
	ListNode* pNode = pHead;
	ListNode* pPrev = nullptr;
	while (pNode != nullptr) {
		ListNode* pNext = pNode->m_pNext;
		if (pNext == nullptr) pReversedHead = pNode;
		pNode->m_pNext = pPrev;
		pPrev = pNode;
		pNode = pNext;
	}
	return pReversedHead;
}

//25.合并两个排序的链表
ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
	if (pHead1 == nullptr) return pHead2;
	if (pHead2 == nullptr) return pHead1;
	ListNode* pMergedHead = nullptr;
	if (pHead1->m_nValue <= pHead2->m_nValue) {
		pMergedHead = pHead1;
		pMergedHead->m_pNext = Merge(pHead1->m_pNext, pHead2);
	}
	else {
		pMergedHead = pHead2;
		pMergedHead->m_pNext = Merge(pHead1, pHead2->m_pNext);
	}
	return pMergedHead;
}

//26.判断B是不是A的子结构
bool DoesTree1EqualsToTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2) {
	if (pRoot2 == nullptr) return true;
	if (pRoot1 == nullptr) return false;
	if (pRoot1->m_nValue != pRoot2->m_nValue) return false;
	return DoesTree1EqualsToTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) &&
		DoesTree1EqualsToTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}

bool HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2) {
	if (pRoot2 == nullptr) return true;
	bool result = false;
	if (pRoot1 != nullptr&&pRoot2 != nullptr) {
		if (pRoot1->m_nValue == pRoot2->m_nValue)
			result = DoesTree1EqualsToTree2(pRoot1, pRoot2);
		if (!result) result = DoesTree1EqualsToTree2(pRoot1->m_pLeft, pRoot2);
		if (!result) result = DoesTree1EqualsToTree2(pRoot1->m_pRight, pRoot2);
	}
	return result;
}

//27.镜像二叉树
void MirrorBinarytree(BinaryTreeNode* pRoot) {
	if (pRoot == nullptr) return;
	if (pRoot->m_pLeft != nullptr || pRoot->m_pRight != nullptr) {
		BinaryTreeNode* temp = pRoot->m_pLeft;
		pRoot->m_pLeft = pRoot->m_pRight;
		pRoot->m_pRight = temp;
	}
	if (pRoot->m_pLeft != nullptr) MirrorBinarytree(pRoot->m_pLeft);
	if (pRoot->m_pRight != nullptr) MirrorBinarytree(pRoot->m_pRight);
}

//28.判断二叉树是否是对称二叉树
bool isSymmetrical(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2) {
	if (pRoot1 == nullptr&&pRoot2 == nullptr) return true;
	if (pRoot1 == nullptr || pRoot2 == nullptr) return false;
	if (pRoot1->m_nValue != pRoot2->m_nValue) return false;
	return isSymmetrical(pRoot1->m_pLeft, pRoot2->m_pRight) && isSymmetrical(pRoot1->m_pRight, pRoot2->m_pLeft);
}

bool isSymmetrical(BinaryTreeNode* pRoot) {
	return isSymmetrical(pRoot, pRoot);
}

//31.栈的压入、弹出序列
bool IsPopOrder(const int* pPush, const int* pPop, int nLength) {
	bool bPossible = false;
	if (pPush != nullptr&&pPop != nullptr&&nLength > 0) {
		stack<int> stackData;
		const int* pNextPush = pPush;
		const int* pNextPop = pPop;
		while (pNextPop - pPop < nLength) {
			while (stackData.empty() || stackData.top() != *pNextPop) {
				if(pNextPush-pPush==nLength) break;
				stackData.push(*pNextPush);
				pNextPush++;
			}
			if (stackData.top() != *pNextPop) break;
			stackData.pop();
			++pNextPop;
		}
		if (stackData.empty() && pNextPop - pPop == nLength)
			bPossible=true;
	}
	return bPossible;
}

//25(2).二叉树中和为某一值的路径
void FindPath(BinaryTreeNode* pRoot, int expectedSum
	, vector<int>& path, int& currentSum) {
	currentSum += pRoot->m_nValue;
	path.push_back(pRoot->m_nValue);
	if (pRoot->m_pLeft == nullptr&&pRoot->m_pRight == nullptr&&
		expectedSum == currentSum) {
		vector<int>::iterator itr = path.begin();
		for (; itr != path.end(); itr++)
			printf("%d\t", *itr);
		printf("\n");
	}
	if (currentSum < expectedSum) {
		if (pRoot->m_pLeft != nullptr) FindPath(pRoot->m_pLeft, expectedSum, path, currentSum);
		if (pRoot->m_pRight != nullptr) FindPath(pRoot->m_pRight, expectedSum, path, currentSum);
	}

	currentSum -= pRoot->m_nValue;
	path.pop_back();
}

void FindPath(BinaryTreeNode* pRoot, int expectedSum) {
	if (pRoot == nullptr) return;
	vector<int> path;
	int currentSum = 0;
	FindPath(pRoot, expectedSum, path, currentSum);
}

//26(2).复杂链表的复制
struct ComplexListNode {
	int m_nValue;
	ComplexListNode* m_pNext;
	ComplexListNode* m_pSibling;
};
//1.复制结点
void CloneNodes(ComplexListNode* pHead) {
	ComplexListNode* pNode = pHead;
	while (pNode != nullptr) {
		ComplexListNode* pTemp = new ComplexListNode();
		pTemp->m_nValue = pNode->m_nValue;
		pTemp->m_pNext = pNode->m_pNext;
		pTemp->m_pSibling = pNode->m_pSibling;

		pNode->m_pNext = pTemp;
		pNode = pTemp->m_pNext;
	}
}

//2.连接m_pSibling
void ConnectSiblingNodes(ComplexListNode* pHead) {
	ComplexListNode* pNode = pHead;
	while (pNode != nullptr) {
		ComplexListNode* pClonedNode = pNode->m_pNext;
		pClonedNode->m_pSibling = pNode->m_pSibling->m_pNext;
		pNode = pClonedNode->m_pNext;
	}
}
//3.分成两个链表
ComplexListNode* ReconnecteNodes(ComplexListNode* pHead) {
	ComplexListNode* pNode = pHead;
	ComplexListNode* pClonedHead = nullptr;
	ComplexListNode* pClonedNode = pClonedHead;

	if (pNode != nullptr) {
		pClonedNode=pClonedHead = pNode->m_pNext;
		pNode->m_pNext = pClonedNode->m_pNext;
		pNode = pNode->m_pNext;
	}
	while (pNode != nullptr) {
		pClonedNode->m_pNext = pNode->m_pNext;
		pClonedNode = pClonedNode->m_pNext;
		pNode->m_pNext = pClonedNode->m_pNext;
		pNode = pNode->m_pNext;
	}
	return pClonedHead;
}

int main() {
	char* str = "a";
	char* pattern = "ab*a";
	if (matchCore(str, pattern)) cout << "true";
	else cout << "false";
	system("pause");
	return 0;
}