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
		if (pTemp->m_pLeft != nullptr) stack1.push(pTemp->m_pLeft);
		if (pTemp->m_pRight != nullptr) stack1.push(pTemp->m_pRight);
	}
}

void InOrderNonRecur(BinaryTreeNode* pRoot) {
	stack<BinaryTreeNode*> stack1;
	BinaryTreeNode* cur = pRoot;
	while (!stack1.empty() || pRoot != nullptr) {
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
		if (cur->m_pRight != nullptr) stack1.push(cur->m_pRight);
		if (cur->m_pLeft != nullptr) stack1.push(cur->m_pLeft);
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

int main() {
	char string[10] = "12345 679";
	ReplaceBlank(string, 10);
	cout << string;
	system("pause");
	return 0;
}