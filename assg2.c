#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct node
{
    int key;
    struct node* left, *right;
    float priority;
} node;
node* createNode(int key, float prior )
{
    node* temp=(node*)malloc(sizeof(node));
    temp->key=key;
    temp->priority=prior;
    temp->right=NULL;
    temp->left=NULL;
    return temp;
}
node* rotateRight(node* root)
{
    node* temp=root->left;
    root->left=temp->right;
    temp->right=root;
    return temp;
}
node* rotateLeft(node *root)
{
    node* temp=root->right;
    root->right=temp->left;
    temp->left=root;
    return temp;
}
node* treapInsert(node* root, int key, float prior)
{
    //node* ret;
    if(root==NULL)
    {
        root=createNode(key,prior);
        //ret=root;
    }
    else
    {
        if(root->key>key)
        {
            root->left=treapInsert(root->left,key,prior);
            if(root->priority>root->left->priority)
            {
                root=rotateRight(root);
            }
        }
        else
        {
            root->right=treapInsert(root->right,key,prior);
            if(root->priority>root->right->priority)
            {
                root=rotateLeft(root);
            }
        }
    }
    return root;
}
node* removeNode(node* root)
{
    node* create;
    if(root!=NULL)
    {
        if(root->left!=NULL)
        {
            if(root->right!=NULL)
            {
                if(root->left->priority>root->right->priority)
                {
                    create=createNode(root->right->key,root->right->priority);
                    create->left=root->left;
                    create->right=root->right;
                    free(root);
                    root=create;
                    root->right=removeNode(root->right);

                }
                else
                {
                    create=createNode(root->left->key,root->left->priority);
                    create->left=root->left;
                    create->right=root->right;
                    free(root);
                    root=create;
                    root->left=removeNode(root->left);
                }
            }
            else
            {
                create=createNode(root->left->key,root->left->priority);
                create->left=root->left;
                create->right=root->right;
                free(root);
                root=create;
                root->left=removeNode(root->left);
            }
        }
        else
        {
            if(root->right!=NULL)
            {
                create=createNode(root->right->key,root->right->priority);
                create->left=root->left;
                create->right=root->right;
                free(root);
                root=create;
                root->right=removeNode(root->right);
            }
            else
            {
                free(root);
                root=NULL;
            }
        }
    }
    return root;
}
node* treapDelete(node* root , int key, int* deleteDone)
{
    if(root!=NULL)
    {
        if(root->key==key)
        {
            *deleteDone=1;
            root=removeNode(root);
        }
        else
        {
            if(*deleteDone==0)
            {
                root->left=treapDelete(root->left,key,deleteDone);
            }
            if(*deleteDone==0)
            {
                root->right=treapDelete(root->right,key,deleteDone);
            }
        }
    }
    return root;
}
void inOrderTraversal(node* root)
{
    if(root!=NULL)
    {
        inOrderTraversal(root->left);
        printf("%d ",root->key);
        inOrderTraversal(root->right);
    }
}
int main()
{
    node* root=NULL;
    int i;
    float rndNum;
    int key;
    int deleteDone=0;
    printf("To insert press 1 ,to remove press 2 , to exit press 0\n");
    int operation;
    scanf("%d",&operation);
    while(operation!=0)
    {
        if(operation==1)
        {
            rndNum= rand();
            scanf("%d",&key);
            root=treapInsert(root,key,rndNum);
        }
        else if(operation==2)
        {
            deleteDone=0;
            scanf("%d",&key);
            root=treapDelete(root,key,&deleteDone);
        }
        inOrderTraversal(root);
        printf("\n");
        scanf("%d",&operation);
    }

    return 0;
}
