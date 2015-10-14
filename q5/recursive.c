#include <stdio.h>
#include <string.h>

typedef struct ListNodeStruct {
    int value;
    struct ListNodeStruct *next;
} ListNode;

ListNode *head=NULL;
ListNode *tail=NULL;

typedef struct StackNodeStruct {
    ListNode *value;
    struct StackNodeStruct *up;
    struct StackNodeStruct *down;
} StackNode;

StackNode *stackTop;
StackNode *bottom;
ListNode push(ListNode *pushnode)
{
    if(stackTop!=NULL) {
        stackTop->up=malloc(sizeof(StackNode));
        stackTop->up->down=stackTop;
        stackTop=stackTop->up;
    } else {
        stackTop=malloc(sizeof(StackNode));
        stackTop->down=NULL;
        bottom=stackTop;
    }
    stackTop->value=pushnode;
}

ListNode *pop()
{
    ListNode *ret=stackTop->value;
    if(stackTop==NULL)
        return NULL;

    if(stackTop!=bottom) {
        stackTop=stackTop->down;
        free(stackTop->up);
    } else {
        free(stackTop);
        stackTop=NULL;
        bottom=NULL;
    }

    return ret;
}

int searchStack(ListNode *target)
{
    StackNode *cnode=stackTop;
    if(stackTop==NULL)
        return 0;

    while(cnode!=bottom) {
        if(cnode->value==target)
            return 1;
        cnode=cnode->down;
    }
    if(cnode->value==target)
        return 1;
    else
        return 0;
}

void clearStack()
{
    StackNode *cnode=stackTop->down;
    while(cnode!=bottom) {
        free(cnode->up);
        cnode=cnode->down;
    }
    free(cnode->up);
    free(cnode);
    stackTop=NULL;
    bottom=NULL;
}

ListNode *detectCycle(ListNode *head)
{
    ListNode *cnode=head->next;
    while(cnode!=NULL) {
        if(cnode==head)
            return head;

        if(searchStack(cnode)==0)
            push(cnode);
        else
            break;

        cnode=cnode->next;
    }
    if(cnode==NULL)
        return NULL;

    clearStack();
    return detectCycle(head->next);
}

void init_list()
{
    FILE *fp=fopen("testdata","r");
    char buf[256];
    char *sbuf;
    int tmp;
    ListNode *cnode=NULL;

    fgets(buf,256,fp);
    sbuf=strtok(buf, " ");

    while(sbuf!=NULL) {
        tmp=atoi(sbuf);
        sbuf=strtok(NULL, " ");

        if(head==NULL) {
            head=malloc(sizeof(ListNode));
            head->value=tmp;
            head->next=NULL;
            cnode=head;
            tail=head;
        } else {
            cnode->next=malloc(sizeof(ListNode));
            cnode->next->value=tmp;
            cnode->next->next=NULL;
            cnode=cnode->next;
            tail=cnode;
        }
    }
    fgets(buf,256,fp);
    tmp=atoi(buf);
    cnode=head;
    while(cnode!=NULL && cnode!=tail) {
        if(cnode->value==tmp) {
            tail->next=cnode;
            break;
        } else {
            cnode=cnode->next;
        }
    }
}

void printlist()
{
    ListNode *cnode=head;
    while(cnode!=tail) {
        printf("%d ",cnode->value);
        cnode=cnode->next;
    }
    printf("%d ",cnode->value);
    cnode=cnode->next;

    printf("\n");
    printf("tail connect to %d\n",cnode->value);
}

int main()
{
    ListNode *result;
    init_list();
    //printlist();
    result=detectCycle(head);
    if(result!=NULL) {
        printf("cycle start at: %d\n",result->value);
    } else {
        printf("cycle not found\n");
    }
    return 0;
}
