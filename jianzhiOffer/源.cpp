#include <iostream>
#include <stack>
#include <queue>

using namespace std;

//1.��ֵ���������
//class CMyString {
//public:
//	CMyString(char *pData = nullptr);
//	CMyString(const CMyString& str);
//	CMyString& operator = (const CMyString& str);
//	~CMyString(void);
//private:
//	char* m_pData;
//};

//1.1��һ��ʵ�֣���覴�
/*
//��������Ϊ���ã�����a=b=c��������ֵ����
//����������Ҫ���ã�����������һ�ο������캯�����Ч�ʣ�ͬʱΪ�˲��ı䴫��ʵ������Ҫ����const
//this==&strʱ������Ҫִ���κβ���
CMyString& CMyString::operator=(const CMyString& str) {
	if (this == &str) return *this;

	delete[] m_pData;
	m_pData = nullptr;

	m_pData = new char[strlen(str.m_pData) + 1];
	strcpy(m_pData, str.m_pData);

	return *this;
}
*/
//1.2�ڶ���ʵ��
//CMyString& CMyString::operator=(const CMyString& str) {
//	if (this != &str) {
//		CMyString strTemp(str);
//		char* pTemp = strTemp.m_pData;
//		strTemp.m_pData = m_pData;
//		m_pData = pTemp;
//	}
//	return *this;
//}

//2.singletonģʽ/����ģʽ
//ֻ������һ��ʵ��
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

//3.�ҳ��������ظ�������
//��һ������Ϊn�����������е����ֶ���0~n-1֮��
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
//���޸���������,��ȷ���ҳ����е�����������ظ�����
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

//4.��ά�����еĲ���
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

//5.�滻�ո�
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

//6.��β��ͷ��ӡ����
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

//�������ı���
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
	BinaryTreeNode* h = pRoot;//��¼��һ�������Ľ��
	BinaryTreeNode* c = nullptr;//��¼ջ�����
	while (!stack1.empty()) {
		c = stack1.top();
		//c��������Ӳ�������û�б���������������������Һ���Ҳû�б�������
		if (c->m_pLeft != nullptr&&h != c->m_pRight&&c->m_pRight)
			stack1.push(c->m_pLeft);
		//c������Һ��Ӳ����Һ���û�б�������
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


//7.�������������ǰ������ؽ�������
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

//8.����������һ���ڵ�
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

//9.����ջʵ��һ������
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

//��������ʵ��һ��ջ
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


//15.��������1�ĸ���
int NumberOf1(int n) {
	int count = 0;
	while (n) {
		++count;
		n = n&(n - 1);
	}
	return count;
}

//17.��ӡ��1������nλ��
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

//18.��O(1)ʱ����ɾ������ڵ�
void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted) {
	//����β�ڵ�
	if (pToBeDeleted->m_pNext != nullptr) {
		ListNode* pNext = pToBeDeleted->m_pNext;
		pToBeDeleted->m_nValue = pNext->m_nValue;
		pToBeDeleted->m_pNext = pNext->m_pNext;

		delete pNext;
		pNext = nullptr;
	}
	//ֻ��һ���ڵ㣬ɾ��ͷ�ڵ㣨Ҳ��β�ڵ㣩
	else if (*pListHead == pToBeDeleted) {
		delete pToBeDeleted;
		pToBeDeleted = nullptr;
		*pListHead = nullptr;		
	}
	//�������ж���ڵ㣬ɾ��β�ڵ�
	else {
		ListNode* pNode = *pListHead;
		while (pNode->m_pNext != pToBeDeleted)
			pNode = pNode->m_pNext;
		pNode->m_pNext = nullptr;
		delete pToBeDeleted;
		pToBeDeleted = nullptr;
	}
}

//ɾ�����������е��ظ��ڵ�
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

//19.������ʽƥ��
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

//20.��ʾ��ֵ���ַ���
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

//21.��������˳��������λ��ż��ǰ��
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

//23.�����л�����ڽڵ�
//����ָ���������
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

//24.��ת����
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



int main() {
	char* str = "a";
	char* pattern = "ab*a";
	if (matchCore(str, pattern)) cout << "true";
	else cout << "false";
	system("pause");
	return 0;
}