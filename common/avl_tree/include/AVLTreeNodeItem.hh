#ifndef __AVLTREENODEITEM_H
#define __AVLTREENODEITEM_H

#include <cstdio>

class AVLTreeNodeItem
{
private:
    int i;
public:
    AVLTreeNodeItem(int aI)
    {
        i = aI;
    }
    
    bool operator==(const AVLTreeNodeItem& aOther)
    {
        return i == aOther.i;
    }

    bool operator!=(const AVLTreeNodeItem& aOther)
    {
        return i != aOther.i;
    }

     
    bool operator<(const AVLTreeNodeItem& aOther)
    {
        return i < aOther.i;
    }

    bool operator>(const AVLTreeNodeItem& aOther)
    {
        return i > aOther.i;
    }
  
    void Printf()
    {
        printf("%d,",i); fflush(stdout);
    }
};

#endif //__AVLTREENODEITEM_H
