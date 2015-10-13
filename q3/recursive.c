#include <stdio.h>

typedef struct TreeNodeStruct {
    int value;
    struct TreeNodeStruct *pLeft;
    struct TreeNodeStruct *pRight;
} TreeNode;

/*void flatten(TreeNode *root)
{
	TreeNode *mostRighOfLeft=root;
	if(root!=NULL)
	{
		flatten(root->pLeft);
		flatten(root->pRight);
		if(root->pLeft!=NULL)
		{
			while(mostRighOfLeft->pRight!=NULL)
			{
				mostRighOfLeft=mostRighOfLeft->pRight;
			}
			mostRighOfLeft->pLeft=root->pLeft;
			root->pLeft=root->pRight;
		}
	}
}*/

TreeNode *flattenBT(TreeNode *root)
{
    if(root==NULL)
        return NULL;
    TreeNode *leftTail = flattenBT(root->pLeft);
    TreeNode *rightTail = flattenBT(root->pRight);

    if(root->pLeft) {
        TreeNode *temp = root->pRight;
        root->pRight = root->pLeft;
        root->pLeft = NULL;
        leftTail->pRight = temp;
    }

    if(rightTail!=NULL) return rightTail;
    if(leftTail!=NULL) return leftTail;
    return root;
}

void flatten(TreeNode *root)
{
    TreeNode *rightTail = flattenBT(root);
}


TreeNode *init_tree()
{
    TreeNode *cnode;
    TreeNode *root=malloc(sizeof(TreeNode));
    root->value=1;
    root->pLeft=malloc(sizeof(TreeNode));
    root->pLeft->value=2;
    root->pRight=malloc(sizeof(TreeNode));
    root->pRight->value=5;

    cnode=root->pLeft;
    cnode->pLeft=malloc(sizeof(TreeNode));
    cnode->pLeft->value=3;
    cnode->pRight=malloc(sizeof(TreeNode));
    cnode->pRight->value=4;

    cnode=root->pRight;
    cnode->pLeft=NULL;
    cnode->pRight=malloc(sizeof(TreeNode));
    cnode->pRight->value=6;

    return root;
}

void printtree(TreeNode *root)
{
    TreeNode *cnode=root;
    while(cnode!=NULL) {
        printf("%d\n",cnode->value);
        cnode=cnode->pRight;
    }
}

int main()
{
    TreeNode *root=init_tree();

    flatten(root);
    printtree(root);
    return 0;
}
