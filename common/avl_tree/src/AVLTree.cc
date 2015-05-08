#include <cstdlib>
#include <cstdio>
#include "AVLTree.h"
#include "AVLTreeNodeItem.h"

AVLTree::AVLTreeNode::AVLTreeNode()
  {
  iItem = NULL;
  iLeft = NULL;
  iRight = NULL;
  iDad = NULL;
  iBalance = 0;
  iRelativePos = 1;
  }
AVLTree::AVLTreeNode::~AVLTreeNode()
  {
  delete iItem; 
  }
  
void AVLTree::AVLTreeNode::Destroy()
  {
  delete iItem;
  if(iLeft) iLeft->Destroy();
  delete iLeft;
  if(iRight) iRight->Destroy();
  delete iRight;
  iItem = NULL;
  iLeft = NULL;
  iRight = NULL;
  }

void AVLTree::AVLTreeNode::PreOrder()
  {
  if(iItem) iItem->Printf();
  else printf("Don't exist item\n");
  if(iLeft) iLeft->PreOrder();
  if(iRight) iRight->PreOrder();
  }
    
void AVLTree::AVLTreeNode::InOrder()
  {
  if(iLeft) iLeft->InOrder();
//  printf("RelPos : %d (Balance : %d)-> ", iRelativePos, iBalance);
//  fflush(stdout);
  if(iItem) iItem->Printf();
  else printf("Don't exist item\n");
//  puts("");
  if(iRight) iRight->InOrder();
  }
  

void AVLTree::AVLTreeNode::PostOrder()
  {
  if(iLeft) iLeft->PostOrder();
  if(iRight) iRight->PostOrder();
  if(iItem) iItem->Printf();
  else printf("Don't exist item\n");
  }

AVLTree::AVLTree()
  {
  iRoot = NULL;
  iNumberOfElements = 0;
  }

AVLTree::~AVLTree()
  {
  RemoveAll();
  }

bool AVLTree::Add(AVLTreeNodeItem& aNodeItem)
  {
  AVLTreeNode *act = iRoot;
  AVLTreeNode *prev = NULL;
  if(act == NULL)
    {
    iRoot = new AVLTreeNode();
    iRoot->iItem = new AVLTreeNodeItem(aNodeItem);
    ++iNumberOfElements;
    return true; 
    }
  prev = act;
  while(act != NULL)
    {
    prev = act;
    if(aNodeItem < *(act->iItem))
      {
      ++(act->iRelativePos);
      act = act->iLeft;     
      }
    else if(aNodeItem > *(act->iItem))
      {
      act = act->iRight;
      }
    else
      {
      return false; // Later Exception
      }
    } // while (act != NULL)
    
  if(aNodeItem < *(prev->iItem))
    {
    prev->iLeft = new AVLTreeNode();
    prev->iLeft->iDad = prev;
    prev->iLeft->iItem = new AVLTreeNodeItem(aNodeItem);
//      prev->iLeft->iSerialNum = 1 + Count();
    Corrector(prev, false, AddNewItem);
    }
  else
    {
    prev->iRight = new AVLTreeNode();
    prev->iRight->iDad = prev;
    prev->iRight->iItem = new AVLTreeNodeItem(aNodeItem);
//      prev->iRight->iSerialNum = 1 + Count();
    Corrector(prev, true, AddNewItem);
    }
  ++iNumberOfElements;
  return true; // Success item addition 
  } 
  
bool AVLTree::Remove(AVLTreeNodeItem& aNodeItem)
  {
  AVLTreeNode* act = iRoot;
  AVLTreeNode* prev = NULL;
  AVLTreeNode* nextNode = NULL;
  
  while(act != NULL && *(act->iItem) != aNodeItem)
    {
    if(aNodeItem < *(act->iItem))
      {
      --(act->iRelativePos);
      act = act->iLeft;
      }
    else
      act = act->iRight;
    } // while (act != NULL && *(act->iItem) != aNodeItem)
  if(act == NULL)
    return false;
  
  if(act->iLeft != NULL && act->iRight != NULL)
    {
    nextNode = act->iRight;
    while(nextNode->iLeft != NULL)
      nextNode = nextNode->iLeft;
    act->iItem = nextNode->iItem; // maybe there will be memory leak!!! FIX IT
    act = nextNode;
    }
  if(act->iLeft == NULL)
    nextNode = act->iRight;
  else
    nextNode = act->iLeft;
  prev = act->iDad;
  if(nextNode != NULL)
    nextNode->iDad = prev;
  if(act == iRoot)
    {
    iRoot = nextNode;
    }
  else
    {
    if(act == prev->iLeft)
      {
      prev->iLeft = nextNode;
      Corrector(prev, false, DeleteItem);
      }
    else
      {
      prev->iRight = nextNode;
      Corrector(prev, true, DeleteItem);
      }
    }
    --iNumberOfElements;
    return true;
  }

void AVLTree::RemoveAll()
  {
  if(iRoot)
    {
    iRoot->Destroy();
    iRoot = NULL;
    iNumberOfElements = 0;
    }
  }
 
void AVLTree::PreOrder()
  {
  if(iRoot) iRoot->PreOrder();
  printf("\n");
  }

void AVLTree::InOrder()
  {
  if(iRoot) iRoot->InOrder();
  printf("\n");
  }

void AVLTree::PostOrder()
  {
  if(iRoot) iRoot->PostOrder();
  printf("\n");
  }

AVLTreeNodeItem& AVLTree::At(const int iIndex)
  {
  int position = iIndex + 1;
  AVLTreeNode *act = iRoot;
  while(position != act->iRelativePos)
    {
    if(position < act->iRelativePos)
      act = act->iLeft;
    else
      {
      position -= act->iRelativePos;
      act = act->iRight;
      }
    }
  return *(act->iItem);
  }

AVLTreeNodeItem& AVLTree::At(const int iIndex) const
  {
  int position = iIndex + 1;
  AVLTreeNode *act = iRoot;
  while(position != act->iRelativePos)
    {
    if(position < act->iRelativePos)
      act = act->iLeft;
    else
      {
      position -= act->iRelativePos;
      act = act->iRight;
      }
    }
  return *(act->iItem);
  }
  
AVLTreeNodeItem& AVLTree::operator[](const int iIndex)
  {
  return At(iIndex);
  }

AVLTreeNodeItem& AVLTree::operator[](const int iIndex) const
  {
  return At(iIndex);
  }

void AVLTree::Corrector(AVLTreeNode *aNode, bool right, TTypeOfModification aMod)
  {
  char LNewP[] = {1,0}; 
  char LNewQ[] = {-1,0};
  char RNewP[] = {0,-1};
  char RNewQ[] = {0,1};
  char DNewP[] = {0,0,-1};
  char DNewQ[] = {1,0,0};  
  AVLTreeNode *sentinel = new AVLTreeNode();
  AVLTreeNode *dad, *q, *r;
  sentinel->iLeft = iRoot;
  iRoot->iDad = sentinel;
  char actBalance;
  char inc = (aMod == AddNewItem) ? 1 : -1;
  
  while(aNode != sentinel)
    {
    actBalance = aNode->iBalance;
    if (right)
      aNode->iBalance += inc;
    else
      aNode->iBalance -= inc;
    
    if(aNode->iBalance == 0 && aMod == AddNewItem || actBalance == 0 && aMod == DeleteItem)
      break;
    dad = aNode->iDad;
    right = aNode == dad->iRight;
    if(aNode->iBalance == 2)
      {
      q = aNode->iRight;
      if(q->iBalance >= 0)
        {
        aNode->iBalance = LNewP[q->iBalance];
        q->iBalance = LNewP[q->iBalance];
        q->iRelativePos += aNode->iRelativePos;   /************************************/
        aNode->iRight = q->iLeft;                 /* Simple Left Rotation             */ 
        q->iLeft = aNode;                         /*      aNode                Q      */
        q->iDad = aNode->iDad;                    /*       / \                / \     */
        aNode->iDad = q;                          /*      a   Q     =>     aNode c    */
        if(aNode->iRight != NULL)                 /*         / \           /   \      */
          aNode->iRight->iDad = aNode;            /*        b   c         a     b     */
        if(aNode == dad->iLeft)                   /*                                  */
          dad->iLeft = q;                         /************************************/
        else
          dad->iRight = q;
        aNode = q;
        if(q->iBalance == 0 && aMod == AddNewItem ||
           q->iBalance == -1 && aMod == DeleteItem)
          break;
        }
      else // if (q->iBalance >= 0)
        {
        r = q->iLeft;
        aNode->iBalance = DNewP[r->iBalance+1];
        q->iBalance = DNewQ[r->iBalance+1];
        q->iRelativePos -= r->iRelativePos;
        r->iRelativePos += aNode->iRelativePos;   /******************************************/
        q->iLeft = r->iRight;                     /* Double Left Rotation                   */
        aNode->iRight = r->iLeft;                 /*                                        */
        r->iLeft = aNode;                         /*     aNode                     R        */
        r->iRight = q;                            /*     /   \                    / \       */
        r->iDad = aNode->iDad;                    /*    a     Q      =>       aNode  Q      */
        aNode->iDad = r;                          /*         / \              / \   / \     */
        q->iDad = r;                              /*        R   d            a   b c   d    */
        if (aNode->iRight != NULL)                /*       / \                              */
          aNode->iRight->iDad = aNode;            /*      b   c                             */
        if (q->iLeft != NULL)                     /******************************************/
          q->iLeft->iDad = q;
        r->iBalance = 0;
        if (aNode == dad->iLeft)
          dad->iLeft = aNode;
        else
          dad->iRight = aNode;
        aNode = r;
        if (aMod == AddNewItem)
          break;
        }
      }
    else // if (aNode->iBalance == 2)
      if(aNode->iBalance == -2)
        {
        q = aNode->iLeft;
        if(q->iBalance <= 0)
          {
          aNode->iBalance = RNewP[q->iBalance+1];
          q->iBalance = RNewQ[q->iBalance+1];
          aNode->iRelativePos -= q->iRelativePos; /***********************************/
          aNode->iLeft = q->iRight;               /*  Simple Right Rotation          */
          q->iRight = aNode;                      /*                                 */
          q->iDad = aNode->iDad;                  /*     aNode             Q         */
          aNode->iDad = q;                        /*     /   \            / \        */
          if(aNode->iLeft != NULL)                /*    Q     c          a aNode     */
            aNode->iLeft->iDad = aNode;           /*   / \                  / \      */
          if(aNode == dad->iLeft)                 /*  a   b                b   c     */
            dad->iLeft = q;                       /*                                 */
          else                                    /***********************************/
            dad->iRight = q;
          aNode = q;
          if(q->iBalance == 0 && aMod == AddNewItem ||
             q->iBalance == 1 && aMod == DeleteItem)
            break;
          }
        else // if(q->iBalance <= 0)
          {
          r = q->iRight;
          aNode->iBalance = DNewQ[r->iBalance+1];
          q->iBalance = DNewP[r->iBalance+1];
          aNode->iRelativePos -= q->iRelativePos + r->iRelativePos;
          r->iRelativePos += q->iRelativePos; 
          aNode->iLeft = r->iRight;               /* Double Right Rotation            */
          q->iRight = r->iLeft;                   /*                                  */
          r->iLeft = q;                           /*       aNode           R          */
          r->iRight = aNode;                      /*       /   \          / \         */
          r->iDad = aNode->iDad;                  /*      Q     d        Q  aNode     */
          q->iDad = r;                            /*     / \            / \   / \     */
          aNode->iDad = r;                        /*    a   R          a   b c   d    */
          if(q->iRight != NULL)                   /*       / \                        */
            q->iRight->iDad = q;                  /*      b   c                       */
          if(aNode->iLeft != NULL)                /*                                  */
            aNode->iLeft->iDad = aNode;           /************************************/
          r->iBalance = 0;
          if(aNode == dad->iLeft)
            dad->iLeft = r;
          else
            dad->iRight = r;
          aNode = r;
          if(aMod == AddNewItem)
            break; 
          }
        }
    aNode = dad;
    } // while (aNode != sentinel)
    iRoot = sentinel->iLeft;
    if(iRoot != NULL)
      iRoot->iDad = NULL;
 
    delete sentinel;
  } 

