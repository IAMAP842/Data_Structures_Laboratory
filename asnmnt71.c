#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *lchild;
    struct node *rchild;
    struct node *parent;
} treenode;

int isEmpty(treenode *t) {
    return t == NULL ? 1 : 0;
}

treenode *insertNode(treenode *t, int val) {
    if (t == NULL) {
        treenode *newNode = (treenode *)malloc(sizeof(treenode));
        newNode->data = val;
        newNode->lchild = newNode->rchild = newNode->parent = NULL;
        return newNode;
    }

    if (val < t->data) {
        t->lchild = insertNode(t->lchild, val);
    } else if (val > t->data) {
        t->rchild = insertNode(t->rchild, val);
    }

    return t;
}

int getCount(treenode *t) {
    if (t == NULL) {
        return 0;
    }
    return 1 + getCount(t->lchild) + getCount(t->rchild);
}

int inorder(treenode *t) {
    if (t == NULL) {
        return 0;
    }
    inorder(t->lchild);
    printf("%d ", t->data);
    inorder(t->rchild);
    return 1;
}

int preorder(treenode *t) {
    if (t == NULL) {
        return 0;
    }
    printf("%d ", t->data);
    preorder(t->lchild);
    preorder(t->rchild);
    return 1;
}

int postorder(treenode *t) {
    if (t == NULL) {
        return 0;
    }
    postorder(t->lchild);
    postorder(t->rchild);
    printf("%d ", t->data);
    return 1;
}

int main() {
    treenode *root = NULL;
    int choice, val;

    while (1) {
        printf("\n1. Insert Node\n2. Check if BST is empty\n3. Get Node Count\n4. Inorder Traversal\n5. Preorder Traversal\n6. Postorder Traversal\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                root = insertNode(root, val);
                break;
            case 2:
                if (isEmpty(root)) {
                    printf("BST is empty.\n");
                } else {
                    printf("BST is not empty.\n");
                }
                break;
            case 3:
                printf("Node count: %d\n", getCount(root));
                break;
            case 4:
                if (inorder(root)) {
                    printf("\n");
                } else {
                    printf("BST is empty.\n");
                }
                break;
            case 5:
                if (preorder(root)) {
                    printf("\n");
                } else {
                    printf("BST is empty.\n");
                }
                break;
            case 6:
                if (postorder(root)) {
                    printf("\n");
                } else {
                    printf("BST is empty.\n");
                }
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}