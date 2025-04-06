#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;

}TreeNode;


//�������
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ����ڵ�
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
//���ҽ��
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
//����������С�ڵ�
//ɾ�����
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

        // ���1��ֻ��һ���ӽڵ��û���ӽڵ�
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

        // ���2���������ӽڵ�
        TreeNode* temp = findMin(root->right); // ������������Сֵ
        root->data = temp->data; // ����Сֵ�滻��ǰ�ڵ�
        root->right = deleteNode(root->right, temp->data); // ɾ������������Сֵ
    }
    return root;
}
// �ݹ�ǰ�����
void preOrder(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// �ݹ��������
void inOrder(TreeNode* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// �ݹ�������
void postOrder(TreeNode* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

/* �ǵݹ����ʵ�� */
// �ǵݹ�ǰ�������ʹ��ջ��
void preOrderIterative(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* stack[MAX_SIZE];
    int top = -1;
    stack[++top] = root;

    printf("�ǵݹ�ǰ�����: ");
    while (top >= 0) {
        TreeNode* node = stack[top--];
        printf("%d ", node->data);

        // ���ӽڵ�����ջ�������
        if (node->right != NULL) {
            stack[++top] = node->right;
        }
        // ���ӽڵ����ջ���ȳ���
        if (node->left != NULL) {
            stack[++top] = node->left;
        }
    }
    printf("\n");
}

// �ǵݹ����������ʹ��ջ��
void inOrderIterative(TreeNode* root) {
    TreeNode* stack[100];
    int top = -1;
    TreeNode* current = root;

    printf("�ǵݹ��������: ");
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

// �ǵݹ���������ʹ��˫ջ��
void postOrderIterative(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* stack1[MAX_SIZE];
    TreeNode* stack2[MAX_SIZE];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;

    printf("�ǵݹ�������: ");
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
// ���������ʹ�ö��У�
void levelOrder(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    printf("�������: ");
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

    printf("��ʼ��Ԫ��: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        root = insert(root, values[i]);
    }
    printf("\n");

    // ���Բ���
    printf("\n=== ���Ҳ��� ===\n");
    int searchValues[] = { 5, 3, 9 };
    for (int i = 0; i < 3; i++) {
        TreeNode* result = search(root, searchValues[i]);
        if (result != NULL) {
            printf("%d ����������\n", searchValues[i]);
        }
        else {
            printf("%d ������������\n", searchValues[i]);
        }
    }

    // ����ɾ��
    printf("\n=== ɾ������ ===\n");
    int deleteValues[] = { 3, 7, 5 }; // ����ɾ��Ҷ�ӽڵ㡢���ӽڵ�͸��ڵ�
    for (int i = 0; i < 3; i++) {
        printf("ɾ�� %d ǰ���������: ", deleteValues[i]);
        inOrder(root);
        printf("\n");

        root = deleteNode(root, deleteValues[i]);

        printf("ɾ�� %d ����������: ", deleteValues[i]);
        inOrder(root);
        printf("\n\n");
    }

    // ��������
    printf("\n=== �������� ===\n");
    printf("�ݹ�ǰ�����: ");
    preOrder(root);
    printf("\n");

    printf("�ݹ��������: ");
    inOrder(root);
    printf("\n");

    printf("�ݹ�������: ");
    postOrder(root);
    printf("\n");
    printf("=== �ǵݹ�������� ===\n");
    preOrderIterative(root);    // Ӧ���: 5 3 2 4 7 6 8
    inOrderIterative(root);     // Ӧ���: 2 3 4 5 6 7 8
    postOrderIterative(root);   // Ӧ���: 2 4 3 6 8 7 5


    return 0;
}