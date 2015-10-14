#include <stdio.h>

//function
typedef struct TreeNodeStruct {
    int value;
    struct TreeNodeStruct *pLeft;
    struct TreeNodeStruct *pRight;
} TreeNode;

typedef struct StackNodeStruct {
    TreeNode *value;
    struct StackNodeStruct *up;
    struct StackNodeStruct *down;
} StackNode;

StackNode *stackTop;
StackNode *bottom;
TreeNode push(TreeNode *pushnode)
{
	if(stackTop!=NULL)
	{
		stackTop->up=malloc(sizeof(StackNode));
		stackTop->up->down=stackTop;
		stackTop=stackTop->up;
	}else
	{
		stackTop=malloc(sizeof(StackNode));
		stackTop->down=NULL;
		bottom=stackTop;
	}
	stackTop->value=pushnode;
}

TreeNode *pop()
{
	TreeNode *ret=stackTop->value;
	if(stackTop==NULL)
		return NULL;
	
	if(stackTop!=bottom)
	{
		stackTop=stackTop->down;
		free(stackTop->up);
	}else
	{
		free(stackTop);
		stackTop=NULL;
		bottom=NULL;
	}
	
	return ret;
}

void flatten(TreeNode *root)
{
    TreeNode *ptr=root;
	TreeNode *tmp;
	
	while(ptr!=NULL)
	{
		if(ptr!=NULL)
		{
			if(ptr->pRight!=NULL)
				push(ptr->pRight);
		
			if(ptr->pLeft!=NULL)
			{
				ptr->pRight=ptr->pLeft;
				ptr->pLeft=NULL;
			}else if(stackTop!=NULL)
			{
				tmp=pop();
				ptr->pRight=tmp;
			}
			ptr=ptr->pRight;
		}
	}
}

void createTree(TreeNode *cnode,int depth,int cdep,FILE *fp)
{
	int tmp;
	char strtmp[8];
	
	if(cdep<=depth)
	{
		cnode->pLeft=malloc(sizeof(TreeNode));
		fscanf(fp,"%s",&strtmp);
		tmp=atoi(strtmp);
		cnode->pLeft->pLeft=NULL;
		cnode->pLeft->pRight=NULL;
		if(tmp!=0)
			cnode->pLeft->value=tmp;
		else
		{
			free(cnode->pLeft);
			cnode->pLeft=NULL;
		}
		
		cnode->pRight=malloc(sizeof(TreeNode));
		fscanf(fp,"%s",&strtmp);
		tmp=atoi(strtmp);
		cnode->pRight->pLeft=NULL;
		cnode->pRight->pRight=NULL;
		if(tmp!=0)
			cnode->pRight->value=tmp;
		else
		{
			free(cnode->pRight);
			cnode->pRight=NULL;
		}
		
		createTree(cnode->pLeft,depth,cdep+1,fp);
		createTree(cnode->pRight,depth,cdep+1,fp);
	}
}

int intlog2(int in)
{
	int res=0;
	
	while(in>1)
	{
		in/=2;
		res++;
	}
	return res;
}

TreeNode *init_tree()
{
    TreeNode *root=malloc(sizeof(TreeNode));
	FILE *fp=fopen("testdata","r");
	int tmp,depth=0,cnt=0;
	char strtmp[8];
	
	while(fscanf(fp,"%s",&strtmp)==1)
		cnt++;
	fclose(fp);
	fp=fopen("testdata","r");
	depth=intlog2(cnt+1);
	/*init root*/
	fscanf(fp,"%s",&strtmp);
	tmp=atoi(strtmp);
	root->value=tmp;
	
	/*init tree*/
	createTree(root,depth,2,fp);
	
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
    stackTop=NULL;
	printtree(root);
    flatten(root);
    printf("flattened:\n");
    printtree(root);
    return 0;
}
