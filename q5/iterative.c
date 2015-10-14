#include <stdio.h>
#include <string.h>

typedef struct ListNodeStruct {
    int value;
    struct ListNodeStruct *next;
} ListNode;

ListNode *head=NULL;
ListNode *tail=NULL;

ListNode *detectCycle(ListNode *head)
{
    ListNode *sp,*fp;
    sp=head;
    fp=head;

    while(sp!=NULL && fp!=NULL && fp->next!=NULL) {
        sp=sp->next;
        fp=fp->next->next;
        if(fp==sp) {
            return sp;
        }
    }
    return NULL;
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
        printf("cycle detected at: %d\n",result->value);
    } else {
        printf("cycle not found\n");
    }
    return 0;
}
