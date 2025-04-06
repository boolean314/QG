#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;

}TreeNode;


//创建结点
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 插入节点
TreeNode* insert(TreeNode* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    else {
        if (value < root->data) {
            root->left = insert(root->left, value);
        }
        else if (value > root->data) {
            root->right = insert(root->right, value);
        }


        return root;
    }

}
//查找结点
TreeNode* search(TreeNode* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }


    if (value < root->data) {
        return search(root->left, value);
    }
    else {
        return search(root->right, value);
    }
}
TreeNode* findMin(TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}
//找子树的最小节点
//删除结点
TreeNode* deleteNode(TreeNode* root, int value) {
    if (root == NULL)
        return root;

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    }
    else {

        // 情况1：只有一个子节点或没有子节点
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        // 情况2：有两个子节点
        TreeNode* temp = findMin(root->right); // 找右子树的最小值
        root->data = temp->data; // 用最小值替换当前节点
        root->right = deleteNode(root->right, temp->data); // 删除右子树的最小值
    }
    return root;
}
// 递归前序遍历
void preOrder(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// 递归中序遍历
void inOrder(TreeNode* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// 递归后序遍历
void postOrder(TreeNode* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

/* 非递归遍历实现 */
// 非递归前序遍历（使用栈）
void preOrderIterative(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* stack[MAX_SIZE];
    int top = -1;
    stack[++top] = root;

    printf("非递归前序遍历: ");
    while (top >= 0) {
        TreeNode* node = stack[top--];
        printf("%d ", node->data);

        // 右子节点先入栈（后出）
        if (node->right != NULL) {
            stack[++top] = node->right;
        }
        // 左子节点后入栈（先出）
        if (node->left != NULL) {
            stack[++top] = node->left;
        }
    }
    printf("\n");
}

// 非递归中序遍历（使用栈）
void inOrderIterative(TreeNode* root) {
    TreeNode* stack[100];
    int top = -1;
    TreeNode* current = root;

    printf("非递归中序遍历: ");
    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
}

// 非递归后序遍历（使用双栈）
void postOrderIterative(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* stack1[MAX_SIZE];
    TreeNode* stack2[MAX_SIZE];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;

    printf("非递归后序遍历: ");
    while (top1 >= 0) {
        TreeNode* node = stack1[top1--];
        stack2[++top2] = node;

        if (node->left != NULL) {
            stack1[++top1] = node->left;
        }
        if (node->right != NULL) {
            stack1[++top1] = node->right;
        }
    }

    while (top2 >= 0) {
        printf("%d ", stack2[top2--]->data);
    }
    printf("\n");
}
// 层序遍历（使用队列）
void levelOrder(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    printf("层序遍历: ");
    while (front < rear) {
        TreeNode* current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
    printf("\n");
}




int main()
{
    TreeNode* root = NULL;
    int values[] = { 5, 3, 7, 2, 4, 6, 8 };
    int n = sizeof(values) / sizeof(values[0]);

    printf("初始树元素: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        root = insert(root, values[i]);
    }
    printf("\n");

    // 测试查找
    printf("\n=== 查找测试 ===\n");
    int searchValues[] = { 5, 3, 9 };
    for (int i = 0; i < 3; i++) {
        TreeNode* result = search(root, searchValues[i]);
        if (result != NULL) {
            printf("%d 存在于树中\n", searchValues[i]);
        }
        else {
            printf("%d 不存在于树中\n", searchValues[i]);
        }
    }

    // 测试删除
    printf("\n=== 删除测试 ===\n");
    int deleteValues[] = { 3, 7, 5 }; // 测试删除叶子节点、单子节点和根节点
    for (int i = 0; i < 3; i++) {
        printf("删除 %d 前的中序遍历: ", deleteValues[i]);
        inOrder(root);
        printf("\n");

        root = deleteNode(root, deleteValues[i]);

        printf("删除 %d 后的中序遍历: ", deleteValues[i]);
        inOrder(root);
        printf("\n\n");
    }

    // 遍历测试
    printf("\n=== 遍历测试 ===\n");
    printf("递归前序遍历: ");
    preOrder(root);
    printf("\n");

    printf("递归中序遍历: ");
    inOrder(root);
    printf("\n");

    printf("递归后序遍历: ");
    postOrder(root);
    printf("\n");
    printf("=== 非递归遍历测试 ===\n");
    preOrderIterative(root);    // 应输出: 5 3 2 4 7 6 8
    inOrderIterative(root);     // 应输出: 2 3 4 5 6 7 8
    postOrderIterative(root);   // 应输出: 2 4 3 6 8 7 5


    return 0;
}