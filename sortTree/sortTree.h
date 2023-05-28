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
    // 构造函数
    sortTree();
    // 析构函数
    ~sortTree();
    // 请用非递归的方式实现查找函数
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
    // 请用非递归的方式实现插入函数
    void insert(const SET<KEY, OTHER>& data)
    {
        BinaryNode* p = root;//获得根结点 
        BinaryNode* q = new BinaryNode(data, 0, 0);//分配一个要插入的新节点 
        q->left = q->right = 0; //新分配节点的左节点=右节点等于0
        q->data = data;  //保存数据到节点    
        BinaryNode* parent = p; //用于保存父节点 
        while (p != 0)  //循环搜索节点  
        {
            parent = p;  //首先parent指向root节点 
            if (p->data.key > data.key)   //如果节点数据大于当前节点
                p = p->left;//如果插入数据小于 节点数据那么指向左节点  我么最终是要找到一个0节点 
            else
                p = p->right;
        }
        //如果因为parent总是指向0节点的父节点 ,所以parent指向的节点不会为空,如果为空那么说明该树是一颗空的树。
        if (parent == 0)
            root = q; //将分配的节点作为根节点 
        else if (parent->data.key > data.key)
            parent->left = q;   //<root左插
        else
            parent->right = q;  //>root右插
    }

    // 请用非递归的方式实现删除函数
    void remove(const KEY& dData)
    {
        BinaryNode* parent = 0;//父指针用来表示 是否是根节点  
        BinaryNode* currentnode;
        currentnode = root;
        while (currentnode != 0)
        {//循环查找
            if (dData < currentnode->data.key)  //如果删除节点小于根节点数据
            {
                parent = currentnode;   //保存前一个节点的指针 
                currentnode = currentnode->left;  //dData小于root数据 那么查找左子树 
            }
            else if (dData > currentnode->data.key)
            {
                parent = currentnode;
                currentnode = currentnode->right; //大于root数据那么查找右节点
            }
            else     //这里找到了节点 如果即不大于 节点数据 也不小于节点数据 并且节点不是0那就说明了 节点查找到了 ,揭晓来我们就需要判断节点并删除了。
            {
                if (currentnode->left == 0 && currentnode->right == 0)  //是叶子节点  1、根节点    2、非根节点
                {
                    if (parent == 0)  //因为parent是0说明没有根节点   否则parent是不可能为0的
                    {
                        delete root;//直接删除根节点 
                        root = 0;
                        return; //直接返回
                    }
                    else    //如果是非根节点的叶子节点  
                    {
                        (parent->left == currentnode) ? (parent->left = 0) : (parent->right = 0);  //判断删除节点是parent的left还是right  
                        delete currentnode;
                        return;//对于叶子节点可以直接返回
                    }
                }
                else if (currentnode->left == 0 && currentnode->right != 0)  //待删除节点只有右有孩子 情况和上面类似 
                {
                    if (parent == 0)  //如果在是根节点 并且有右孩子的情况下 
                    {
                        root = root->right;//只有右孩子 那么指针移动到右孩子
                        return;
                    }
                    else
                    {
                        (parent->left == currentnode) ? (parent->left = currentnode->right) : (parent->right = currentnode->right); //令parent的left或者right指向 root的left
                        delete currentnode;
                        return;
                    }
                }
                else  if (currentnode->left != 0 && currentnode->right == 0)  //待删除节点只有左孩子 情况和上面类似 
                {
                    if (parent == 0)  //如果在是根节点 并且有右孩子的情况下 
                    {
                        root = root->left;//待删除节点只有左孩子 那么指针移动到左孩子
                        return;
                    }
                    else
                    {
                        (parent->left == currentnode) ? (parent->left = currentnode->left) : (parent->right = currentnode->left); //令parent的left或者right指向 root的left
                        delete currentnode;
                        return;
                    }
                }
                else  //最后一种  删除节点既有做孩子又有右孩子
                {
                    BinaryNode* p = currentnode->left;//定义一个p保存当前删除节点 我们利用这个节点左孩子找到最右下节点  。
                    while (p->right != 0)
                    {
                        parent = p;  //保存右下节点的父节点指针
                        p = p->right;//从待删除节点

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
    // 如果有需要添加的其他函数，请在此处声明并实现。
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
    // 在此实现析构函数
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