/*
Author: Shubin Jacob.
NetID: sxj148030
*/

#include<stdio.h>
#define max(a,b) ((a)<(b)?(b):(a));
#define min(a,b) ((a)>(b)?(b):(a));

struct node{
	int val;
	struct node *RC;
	struct node *LC;
        struct node *parent;
}*root,*tmpParent;

int getMaxDepth(struct node *n)
{
	int lengthLC,lengthRC,maxLen;
        if (n == NULL)
	{
                return 0;
        }
	else
	{
                lengthLC = getMaxDepth(n->LC);
                lengthRC = getMaxDepth(n->RC);
                maxLen = max(lengthLC,lengthRC);
                return (1+maxLen);
	}

}


struct node* getMaxPredecessor(struct node *n)
{
        if (n->LC == NULL){
                return NULL;
        }
        n = n->LC;
        while(n->RC != NULL)
        {
                n = n->RC;
        }
        return n;

}

struct node* getMinSuccessor(struct node *n)
{
        if (n->RC == NULL)
                return NULL;
        n = n->RC;
        while(n->LC != NULL)
        {
                n = n->LC;
        }
        return n;

}

void rotateNode(struct node *n,int rightRotation,int singleRotation)
{
	struct node* tmp;
        struct node* tmp1;
        struct node* tmp2;
	if (rightRotation == 0)
	{
		if (singleRotation == 1)
		{
			printf("\nGoing for single left rotation...\n");

			//To avoid looping.
			tmp=n->RC->LC;
			
			n->RC->parent = n->parent;
			if (n->parent !=NULL)		
                                if (n->parent->RC == n)
                                        n->parent->RC = n->RC;
                                else
                                        n->parent->LC = n->RC;
			else
				root = n->RC;
			n->parent = n->RC;
			if (tmp != NULL)
				tmp->parent = n;

			n->RC->LC=n;
			n->RC=tmp;
					
		
		}
		else
		{
                        printf("\nGoing for double left rotation...\n");			
			tmp = n->RC->LC->LC;
			tmp1 = n->RC->LC->RC;
			tmp2 = n->RC->LC; 
                        if (n->parent !=NULL)
			{
				// Check node is RC or LC.
				if (n->parent->RC == n)
					n->parent->RC = tmp2;
				else
					n->parent->LC = tmp2; 
			}
			else
				root = tmp2;
			n->RC->LC->parent = n->parent;
			n->RC->parent= tmp2;
			tmp2->RC = n->RC;

			n->parent =n->RC->LC;
                        if (tmp != NULL)
                                tmp->parent = n;
			if (tmp1 != NULL)
				tmp1->parent = n->RC;
			tmp2->LC=n;	
			n->RC->LC=tmp1;
			n->RC = tmp;
		}
	}
	else
	{
                if (singleRotation == 1)
                {
                        printf("\nGoing for single Right rotation...\n");

                        //To avoid looping.
                        tmp=n->LC->RC;

                        n->LC->parent = n->parent;
                        if (n->parent !=NULL)
                                if (n->parent->RC == n)
                                        n->parent->RC = n->LC;
                                else
                                        n->parent->LC = n->LC;

                        else
                                root = n->LC;
                        n->parent = n->LC;
                        if (tmp != NULL)
                                tmp->parent = n;

                        n->LC->RC=n;
                        n->LC=tmp;


                }
                else
                {
                        printf("\nGoing for double Right rotation...\n");
                        tmp = n->LC->RC->RC;
                        tmp1 = n->LC->RC->LC;
                        tmp2 = n->LC->RC;
                        if (n->parent !=NULL)
				// Check node is RC or LC.	
                                if (n->parent->RC == n)
                                        n->parent->RC = tmp2;
                                else
                                        n->parent->LC = tmp2;
                        else
                                root = tmp2;
                        n->LC->RC->parent = n->parent;
                        n->LC->parent= tmp2;
                        tmp2->LC = n->LC;

                        n->parent =n->LC->RC;
                        if (tmp != NULL)
                                tmp->parent = n;
                        if (tmp1 != NULL)
                                tmp1->parent = n->LC;
                        tmp2->RC=n;
                        n->LC->RC=tmp1;
                        n->LC = tmp;
		}

	}
}
void balanceAVL(struct node *n)
{

	if (n != NULL)
	{
		int pathLong,pathShort,pathRC,pathLC,pathRC1,pathLC1;
		int rightRotation=0;
		int singleRotation=0;
		pathRC = getMaxDepth(n->RC);
		pathLC = getMaxDepth(n->LC);
		pathLong=max(pathRC,pathLC);
		pathShort = min(pathRC,pathLC);

		if (pathLong - pathShort >1)
		{
			if (pathLong == pathLC)
			{
				rightRotation=1;
				tmpParent = n->LC;
				pathRC1 = getMaxDepth(n->LC->RC);
				pathLC1 = getMaxDepth(n->LC->LC);
				if ((pathLC1 > pathRC1) ||(pathLC1 == pathRC1))
					singleRotation = 1;
			}
			else
			{
				rightRotation=0;
                                tmpParent = n->RC;
                                pathRC1 = getMaxDepth(n->RC->RC);
                                pathLC1 = getMaxDepth(n->RC->LC);
                                if ((pathRC1 > pathLC1)||(pathLC1 == pathRC1))
                                        singleRotation = 1;
			}
			rotateNode(n,rightRotation,singleRotation);
		}
		else 
		{
			printf("\nThe AVL is balanced at Node : %d\n",n->val);
			if (n->parent != NULL)
			{
				tmpParent=n->parent;
				balanceAVL(n->parent);
			}
		}
	}
}

void insertNode(struct node *n,int num)
{
	struct node *tmp = (struct node *)malloc(sizeof(struct node));
	tmp->val = num;
	tmp->RC=NULL;
	tmp->LC=NULL;
        tmp->parent=NULL;
	if (n == NULL)
	{
		if(root != NULL)
		{
			printf("\nInserting :%d\n",tmp->val);
			tmp->parent = tmpParent;
			if (tmpParent->val < num)
				tmpParent->RC = tmp;
			else
				tmpParent->LC = tmp;
			printf("\nGoing for balanacing..\n");
			balanceAVL(tmpParent);
		}
		else
			root = tmp;
		return;
	}

	if (num < n->val)
	{
		tmpParent= n;
		insertNode(n->LC,num);
	}
	else if (num > n->val)
	{
                tmpParent= n;
                insertNode(n->RC,num);
	}

}

void deleteNode(struct node *n, int num)
{
        int minSuccessor = 0;
        if (root==NULL)
        {
                printf("\nEmpty tree!\n");
                return;
        }
        if (n->val == num)
        {
                struct node *temp = getMaxPredecessor(n);
                //struct node *temp = getMinSuccessor(n);
                if (temp == NULL)
                {
                        temp = getMinSuccessor(n);
			minSuccessor = 1;
                        //temp = getMaxPredecessor(n);
                }
                else
                        minSuccessor = 0;

                //Giving value to node's parent.
                if (n->parent == NULL)
                        printf("\n Deleted node is root! \n");
                else if(n->parent->RC !=NULL && n->parent->RC == n)
                {
                        n->parent->RC=temp;

                }
                else if(n->parent->LC!=NULL && n->parent->LC == n)
                {
                        n->parent->LC=temp;
                }
                if (temp == NULL)
                {
                        printf("\nNode is without a successor!\n");
                }
                else
                {
                        if (minSuccessor == 1)
                        {
                                if (n->LC != NULL)
                                {
                                        temp->LC= n->LC;
                                        n->LC->parent = temp;
                                }
                                if (temp->RC != NULL && n->RC != temp)
                                {
                                        temp->parent->LC = temp->RC;
                                        temp->RC->parent = temp->parent;
                                }
                                if (temp->RC == NULL && n->RC != temp)
                                {
                                        temp->parent->LC = NULL;
                                }
                                if (n->RC != temp)
                                        temp->RC= n->RC;

                        }
                        else
                        {
                                if (n->RC != NULL)
                                {
                                        temp->RC= n->RC;
                                        n->RC->parent = temp;
                                }
                                if (temp->LC != NULL && n->LC != temp)
                                {
                                        temp->parent->RC = temp->LC;
                                        temp->LC->parent = temp->parent;
                                }
                                if (temp->LC == NULL && n->LC != temp)
                                {
                                        temp->parent->RC = NULL;
                                }
                                if (n->LC != temp)
                                        temp->LC= n->LC;
                        }

                        temp->parent = n->parent;

                        if (n->RC != temp && n->RC != NULL)
                        {
                               temp->RC = n->RC;
                                n->RC->parent = temp;
                        }
                        if (n->LC != temp && n->LC != NULL)
                        {
                               temp->LC = n->LC;
                                n->LC->parent = temp;
                        }

                        if (root == n)
                        {
                                root = temp;
                        }
                }
                free(n);
		if (temp == NULL)
			balanceAVL(n->parent);
		else
			balanceAVL(temp);
                return;
        }

        else if (n->val > num )
        {
                if (n->LC == NULL)
                {
                        printf("\nNode not present!\n");
                        return;
                }
                else
                        deleteNode(n->LC,num);
        }
        else
        {
                if (n->RC == NULL)
                {
                        printf("\nNode not present!\n");
                        return;
                }
                else
                        deleteNode(n->RC,num);
        }

}

void printAVL(struct node *n)
{

    if (n == NULL)
        {
                return;
        }

    printf("\n%d\n ",n->val);

    if (n->LC != NULL)
        {
                  printf("%d",n->LC->val);
        }
    else
        {
                 printf("-");
        }
    if (n->RC != NULL)
        {
                  printf("\t%d",n->RC->val);
        }

    else
        {
                 printf("\t-");
        }

  printAVL(n->LC);
  printAVL(n->RC);
  tmpParent = root;

}

void main()
{
  char b='y';
  int a,i,n;
  int c[]={15,20,24,10,13,7,30,36,25};
  root = NULL;
  tmpParent = NULL;
  n = sizeof(c)/sizeof(c[0]);


  for(i = 0; i<n; i++)
  {
	printf("Node to be inserted:%d \n",c[i]);
        tmpParent = root;
        insertNode(tmpParent,c[i]);
  }
/*
  while(b=='y')
  {
     tmpParent = root;
     printf("\nEnter the node to be added of the BST: ");
     scanf("%d",&a);
     insertNode(tmpParent,a);
     tmpParent = root;
     printAVL(tmpParent);
     printf("Do you want to add another node from the BST: ");
     scanf("%s",&b);
  }
*/

  tmpParent = root;
  printf("\nThe intial AVL is: \n");
  printAVL(tmpParent);

  b = 'y';
  while(b=='y')
  {
     tmpParent = root;
     printf("\nEnter the node to be deleted of the BST: ");
     scanf("%d",&a);
     deleteNode(tmpParent,a);
     printf("Do you want to delete another node from the BST: ");
     scanf("%s",&b);
  }
  tmpParent = root;
  printf("\nAVL after delete operation: \n");
  printAVL(tmpParent);

}
