#include <stdio.h>

typedef struct TreeNodeStruct {
    int value;
    struct TreeNodeStruct *pLeft;
    struct TreeNodeStruct *pRight;
} TreeNode;

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
    flattenBT(root);
}


void createTree(TreeNode *cnode,int depth,int cdep,FILE *fp)
{
    int tmp;
    char strtmp[8];

    if(cdep<=depth) {
        cnode->pLeft=malloc(sizeof(TreeNode));
        fscanf(fp,"%s",&strtmp);
        tmp=atoi(strtmp);
        cnode->pLeft->pLeft=NULL;
        cnode->pLeft->pRight=NULL;
        if(tmp!=0)
            cnode->pLeft->value=tmp;
        else {
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
        else {
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

    while(in>1) {
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
    printtree(root);
    flatten(root);
    printf("flattened:\n");
    printtree(root);
    return 0;
}
