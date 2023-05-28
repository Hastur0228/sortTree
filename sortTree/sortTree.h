#ifndef Hasturas
#define Hasturas

#include <iostream>
using namespace std;
//create stack
template<class T>
class Stack
{
private:
    T* stack;
    int top_p;
    int max_size;
    void doubleSpace();
public:
    Stack(int init_size = 10);
    ~Stack();
    bool isEmpty() const;
    void push(const T& x);
    T pop();
    T top() const;
};
//realize stack
template<class T>
Stack<T>::Stack(int init_size)
{
    stack = new T[init_size];
    max_size = init_size;
    top_p = -1;
}
template<class T>
Stack<T>::~Stack()
{
    delete[] stack;
}
template<class T>
bool Stack<T>::isEmpty() const
{
    return top_p == -1;
}
template<class T>
void Stack<T>::push(const T& x)
{
    if (top_p == max_size - 1)
        doubleSpace();
    stack[++top_p] = x;
}
template<class T>
T Stack<T>::pop()
{
    return stack[top_p--];
}
template<class T>
T Stack<T>::top() const
{
    return stack[top_p];
}
template<class T>
void Stack<T>::doubleSpace()
{
    T* tmp = stack;
    stack = new T[2 * max_size];
    for (int i = 0; i < max_size; ++i)
        stack[i] = tmp[i];
    max_size *= 2;
    delete[] tmp;
}

template<class KEY, class OTHER>
struct SET
{
    KEY key;
    OTHER other;
};

template<class KEY, class OTHER>
class sortTree {
private:
    struct BinaryNode
    {
        SET<KEY, OTHER> data;
        BinaryNode* left;
        BinaryNode* right;
        BinaryNode(const SET<KEY, OTHER>& thedata, BinaryNode* lt = 0, BinaryNode* rt = 0)
            :data(thedata), left(lt), right(rt) {}
        void operator=(const BinaryNode& D)
        {
            data = D.data;
            left = D.left;
            right = D.right;
        }
    };
    BinaryNode* root;

public:
    // ���캯��
    sortTree();
    // ��������
    ~sortTree();
    // ���÷ǵݹ�ķ�ʽʵ�ֲ��Һ���
    SET<KEY, OTHER>* find(const KEY& x) const
    {
        BinaryNode* currentnode;
        currentnode = root;

        while (currentnode != 0 && currentnode->data.key != x)
        {
            if (x < currentnode->data.key)
                currentnode = currentnode->left;
            else
                currentnode = currentnode->right;
        }
        return (SET<KEY, OTHER> *) currentnode;
    }
    void midOrder()const
    {
        Stack<BinaryNode*> s;
        BinaryNode* p = root;
        while (p != 0 || !s.isEmpty())
        {
            while (p != 0)
            {
                s.push(p);
                p = p->left;
            }
            if (!s.isEmpty())
            {
                p = s.pop();
                cout << "(" << p->data.key <<", "<<p->data.other<<") ";
                p = p->right;
            }
        }
    }
    // ���÷ǵݹ�ķ�ʽʵ�ֲ��뺯��
    void insert(const SET<KEY, OTHER>& data)
    {
        BinaryNode* p = root;//��ø���� 
        BinaryNode* q = new BinaryNode(data, 0, 0);//����һ��Ҫ������½ڵ� 
        q->left = q->right = 0; //�·���ڵ����ڵ�=�ҽڵ����0
        q->data = data;  //�������ݵ��ڵ�    
        BinaryNode* parent = p; //���ڱ��游�ڵ� 
        while (p != 0)  //ѭ�������ڵ�  
        {
            parent = p;  //����parentָ��root�ڵ� 
            if (p->data.key > data.key)   //����ڵ����ݴ��ڵ�ǰ�ڵ�
                p = p->left;//�����������С�� �ڵ�������ôָ����ڵ�  ��ô������Ҫ�ҵ�һ��0�ڵ� 
            else
                p = p->right;
        }
        //�����Ϊparent����ָ��0�ڵ�ĸ��ڵ� ,����parentָ��Ľڵ㲻��Ϊ��,���Ϊ����ô˵��������һ�ſյ�����
        if (parent == 0)
            root = q; //������Ľڵ���Ϊ���ڵ� 
        else if (parent->data.key > data.key)
            parent->left = q;   //<root���
        else
            parent->right = q;  //>root�Ҳ�
    }

    // ���÷ǵݹ�ķ�ʽʵ��ɾ������
    void remove(const KEY& dData)
    {
        BinaryNode* parent = 0;//��ָ��������ʾ �Ƿ��Ǹ��ڵ�  
        BinaryNode* currentnode;
        currentnode = root;
        while (currentnode != 0)
        {//ѭ������
            if (dData < currentnode->data.key)  //���ɾ���ڵ�С�ڸ��ڵ�����
            {
                parent = currentnode;   //����ǰһ���ڵ��ָ�� 
                currentnode = currentnode->left;  //dDataС��root���� ��ô���������� 
            }
            else if (dData > currentnode->data.key)
            {
                parent = currentnode;
                currentnode = currentnode->right; //����root������ô�����ҽڵ�
            }
            else     //�����ҵ��˽ڵ� ����������� �ڵ����� Ҳ��С�ڽڵ����� ���ҽڵ㲻��0�Ǿ�˵���� �ڵ���ҵ��� ,���������Ǿ���Ҫ�жϽڵ㲢ɾ���ˡ�
            {
                if (currentnode->left == 0 && currentnode->right == 0)  //��Ҷ�ӽڵ�  1�����ڵ�    2���Ǹ��ڵ�
                {
                    if (parent == 0)  //��Ϊparent��0˵��û�и��ڵ�   ����parent�ǲ�����Ϊ0��
                    {
                        delete root;//ֱ��ɾ�����ڵ� 
                        root = 0;
                        return; //ֱ�ӷ���
                    }
                    else    //����ǷǸ��ڵ��Ҷ�ӽڵ�  
                    {
                        (parent->left == currentnode) ? (parent->left = 0) : (parent->right = 0);  //�ж�ɾ���ڵ���parent��left����right  
                        delete currentnode;
                        return;//����Ҷ�ӽڵ����ֱ�ӷ���
                    }
                }
                else if (currentnode->left == 0 && currentnode->right != 0)  //��ɾ���ڵ�ֻ�����к��� ������������� 
                {
                    if (parent == 0)  //������Ǹ��ڵ� �������Һ��ӵ������ 
                    {
                        root = root->right;//ֻ���Һ��� ��ôָ���ƶ����Һ���
                        return;
                    }
                    else
                    {
                        (parent->left == currentnode) ? (parent->left = currentnode->right) : (parent->right = currentnode->right); //��parent��left����rightָ�� root��left
                        delete currentnode;
                        return;
                    }
                }
                else  if (currentnode->left != 0 && currentnode->right == 0)  //��ɾ���ڵ�ֻ������ ������������� 
                {
                    if (parent == 0)  //������Ǹ��ڵ� �������Һ��ӵ������ 
                    {
                        root = root->left;//��ɾ���ڵ�ֻ������ ��ôָ���ƶ�������
                        return;
                    }
                    else
                    {
                        (parent->left == currentnode) ? (parent->left = currentnode->left) : (parent->right = currentnode->left); //��parent��left����rightָ�� root��left
                        delete currentnode;
                        return;
                    }
                }
                else  //���һ��  ɾ���ڵ���������������Һ���
                {
                    BinaryNode* p = currentnode->left;//����һ��p���浱ǰɾ���ڵ� ������������ڵ������ҵ������½ڵ�  ��
                    while (p->right != 0)
                    {
                        parent = p;  //�������½ڵ�ĸ��ڵ�ָ��
                        p = p->right;//�Ӵ�ɾ���ڵ�

                    }
                    currentnode->data = p->data;
                    parent->right = p->left;
                    delete p;
                    return;
                }
            }
        }
    }
private:

    void destroy(BinaryNode* currentroot);
    // �������Ҫ��ӵ��������������ڴ˴�������ʵ�֡�
};

template<class KEY, class OTHER>
sortTree<KEY, OTHER>::sortTree()
{
    root = 0;
}

template<class KEY, class OTHER>
sortTree<KEY, OTHER>::~sortTree()
{
    destroy(root);
    // �ڴ�ʵ����������
}

template<class KEY, class OTHER>
void sortTree<KEY, OTHER>::destroy(BinaryNode* currentroot)
{
    if (currentroot)
    {
        destroy(currentroot->left);
        destroy(currentroot->right);
        delete currentroot;
        currentroot = 0;
    }
}

#endif//Hasturas