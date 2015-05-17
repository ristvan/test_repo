#ifndef __AVLTREE_H
#define __AVLTREE_H


enum TTypeOfRotation
{
    SimpleLeftRotation,
    SimpleRightRotation,
    DoubleLeftRotation,
    DoubleRoghtRotation
};

enum TTypeOfModification
{
    AddNewItem,
    DeleteItem
};

class AVLTreeNodeItem;

class AVLTree
{
private:

    class AVLTreeNode
    {
    public:
        AVLTreeNodeItem *iItem;
        AVLTreeNode *iDad;
        AVLTreeNode *iLeft;
        AVLTreeNode *iRight;

        void Destroy(); // Destroy Every Item under this Node
        AVLTreeNode();
        ~AVLTreeNode();
        void PreOrder();
        void InOrder();
        void PostOrder();
//        AVLTreeNodeItem* InOrder(const int aIndex);
        char iBalance;
        int iRelativePos; // in AVL array-like type
    };
    
    AVLTreeNode *iRoot;
    int iNumberOfElements;
  
public:
    AVLTree();
    ~AVLTree();
    bool Add(AVLTreeNodeItem& aNodeItem);
    bool Remove(AVLTreeNodeItem& aNodeItem);
    void RemoveAll();
    int Count(void) const { return iNumberOfElements; }
    void PreOrder();
    void InOrder();
    void PostOrder();
    AVLTreeNodeItem& At(const int iIndex);
    AVLTreeNodeItem& At(const int iIndex) const;
    AVLTreeNodeItem& operator[](const int iIndex);
    AVLTreeNodeItem& operator[](const int iIndex) const;

private:
    void Corrector(AVLTreeNode *aNode, bool right, TTypeOfModification aMod);
//    int NewBalance(TTypeOfRotation aRotation, TTypeOfNode aNode, int aOldBalance);
};

#endif //__AVLTREE_H
