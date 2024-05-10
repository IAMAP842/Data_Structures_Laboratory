#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
    struct node *parent;
} treenode;

int isEmpty(treenode *t)
{
    if (t == NULL)
        return 1;
    else
        return 0;
}

treenode *insertNode(treenode *t, int val)
{
    if (t == NULL)
    {
        treenode *node = (treenode *)malloc(sizeof(treenode));
        node->data = val;
        node->lchild = node->rchild = node->parent = NULL;
        return node;
    }
    if (t->data > val)
    {
        t->lchild = insertNode(t->lchild, val);
        t->lchild->parent = t;
    }
    else if (t->data < val)
    {
        t->rchild = insertNode(t->rchild, val);
        t->rchild->parent = t;
    }
    return t;
}

int getCount(treenode *t)
{
    if (t == NULL)
        return 0;
    int cnt = 1;
    cnt += getCount(t->lchild);
    cnt += getCount(t->rchild);
    return cnt;
}

int inorder(treenode *t)
{
    if (isEmpty(t))
        return 0;
    inorder(t->lchild);
    printf("%d\t", t->data);
    inorder(t->rchild);
    return 1;
}

int postorder(treenode *t)
{
    if (isEmpty(t))
        return 0;
    postorder(t->lchild);
    postorder(t->rchild);
    printf("%d\t", t->data);
    return 1;
}

int preorder(treenode *t)
{
    if (isEmpty(t))
        return 0;
    printf("%d\t", t->data);
    preorder(t->lchild);
    preorder(t->rchild);
    return 1;
}

int height(treenode *t)
{
    if (t == NULL)
        return 0;
    int maxheight;
    int lheight = height(t->lchild);
    int rheight = height(t->rchild);
    return (lheight > rheight) ? lheight + 1 : rheight + 1;
}

void min(treenode *t)
{
    treenode *temp = t;
    while (temp->lchild != NULL)
        temp = temp->lchild;
    printf("The minimum element of the tree is %d\n", temp->data);
}

void max(treenode *t)
{
    treenode *temp = t;
    while (temp->rchild != NULL)
        temp = temp->rchild;
    printf("The maximum element of the tree is %d\n", temp->data);
}

int equal(treenode *t1, treenode *t2)
{
    if (t1 == NULL && t2 == NULL)
        return 1;
    else if (t1 != NULL && t2 != NULL)
        return ((t1->data == t2->data) && equal(t1->lchild, t2->lchild) && equal(t1->rchild, t2->rchild));
    else
        return 0;
}

treenode *insucc(treenode *t, int key)
{
    if (t == NULL)
        return NULL;
    if (key > t->data)
        return insucc(t->rchild, key);
    else if (key < t->data)
        return insucc(t->lchild, key);
    else
    {
        if (t->rchild != NULL)
        {
            t = t->rchild;
            while (t->lchild != NULL)
                t = t->lchild;
            return t;
        }
        else
        {
            while (t->data > t->parent->data)
                t = t->parent;
            return t->parent;
        }
    }
}

treenode *findMax(treenode *t)
{
    while (t->rchild != NULL)
        t = t->rchild;
    return t;
}

int deleteNode(treenode **t, int val)
{
    if ((*t) == NULL)
        return 0;
    if (val > (*t)->data)
        return deleteNode(&(*t)->rchild, val);
    else if (val < (*t)->data)
        return deleteNode(&(*t)->lchild, val);
    else
    {
        if ((*t)->lchild == NULL)
        {
            treenode *temp = *t;
            *t = (*t)->rchild;
            free(temp);
        }
        else if ((*t)->rchild == NULL)
        {
            treenode *temp = *t;
            *t = (*t)->lchild;
            free(temp);
        }
        else
        {
            treenode *temp = findMax((*t)->lchild);
            (*t)->data = temp->data;
            deleteNode(&(*t)->lchild, temp->data);
        }
        return 1;
    }
}

int search(int io[], int s, int e, int value)
{
    for (int i = s; i <= e; i++)
    {
        if (io[i] == value)
            return i;
        return -1;
    }
}

treenode *createtree(int io[], int s, int e, int pro[], int in)
{
    if (s > e)
        return NULL;
    treenode *root2 = NULL;
    insertNode(root2, pro[in++]);
    if (s == e)
        return root2;
    int index = search(io, s, e, root2->data);
    root2->lchild = createtree(io, s, index - 1, pro, in);
    root2->rchild = createtree(io, index + 1, e, pro, in);
    return root2;
}

treenode *getTreeInPre(int a[], int asize, int b[], int bsize)
{
    int pin = 0;
    return createtree(a, 0, asize - 1, b, pin);
}

int main()
{
    treenode *root = NULL;
    root = insertNode(root, 5);
    root = insertNode(root, 3);
    root = insertNode(root, 7);
    root = insertNode(root, 2);
    root = insertNode(root, 4);
    root = insertNode(root, 6);
    root = insertNode(root, 9);
    treenode *toor = NULL;
    toor = insertNode(toor, 5);
    toor = insertNode(toor, 3);
    toor = insertNode(toor, 2);
    toor = insertNode(toor, 1);
    printf("The no of nodes in tree is %d\n", getCount(root));
    printf("Inorder Traversal :\t");
    inorder(root);
    printf("\n");
    printf("Postorder Traversal :\t");
    postorder(root);
    printf("\n");
    printf("Preorder Traversal :\t");
    preorder(root);
    printf("\n                                       \n");
    printf("                                         \n");
    printf("\nHeight of tree is %d\n", height(root));
    min(root);
    max(root);
    printf("Inorder Traversal of 2nd Binary tree :\t");
    inorder(toor);
    if (equal(root, toor))
        printf("\nBoth are Equal Binary Trees.\n");
    else
        printf("\nboth are not equal.\n");
    printf("Insuccessor of the element 6 is %d.\n", insucc(root, 6)->data);
    printf("Deletion from BST : %d\n", deleteNode(&toor, 3));
    printf("After the Deletion :\n");
    inorder(toor);
    printf("\n                                       \n");
    printf("                                         \n");
    int inarr[] = {2, 3, 4, 5, 6, 7, 9};
    int prearr[] = {2, 4, 3, 6, 9, 7, 5};
    int postarr[] = {5, 3, 2, 4, 7, 6, 9};
    int n = sizeof(inarr) / sizeof(inarr[0]);
    treenode *root1 = getTreeInPre(inarr, n, prearr, n);
    inorder(root1);
    return 0;
}