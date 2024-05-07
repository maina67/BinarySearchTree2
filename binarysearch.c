// Jesse Maina Kanyi SCT221-0246/2022
// Titus Gicheha     SCT221-0216/2022
#include <stdio.h>
#include <stdlib.h>

// Define a structure for the binary tree node
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Function to create a new node with the given data
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Function to insert a new node with the given data into the binary tree
Node* insert(Node* node, int data) {
    if (node == NULL) return newNode(data);
    if (data < node->data) node->left  = insert(node->left, data);
    else if (data > node->data) node->right = insert(node->right, data);
    return node;
}

// Function to find the node with the minimum value in a given binary tree
Node* minValue(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) current = current->left;
    return current;
}

// Function to delete a node with the given data from the binary tree
Node* deleteNode(Node* root, int data) {
    if (root == NULL) return root;
    if (data < root->data) root->left = deleteNode(root->left, data);
    else if(data > root->data) root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = minValue(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to calculate the height of a binary tree
int height(Node* node) {
    if (node == NULL)
        return 0;

    int lheight = height(node->left);
    int rheight = height(node->right);

    return (lheight > rheight) ? (lheight + 1) : (rheight + 1);
}


// Function to print nodes at a given level in the binary tree
void printLevel(Node* root, int level) {
    if (root == NULL) return;
    if (level == 1) printf("%d ", root->data);
    else if (level > 1) {
        printLevel(root->left, level-1);
        printLevel(root->right, level-1);
    }
}

// Function to print the level order traversal of a binary tree
void printOrder(Node* root) {
    int h = height(root);
    int i;
    for (i=1; i<=h; i++) printLevel(root, i);
}

// Main function
int main() {
    Node *root = NULL;
    // Inserting nodes into the binary tree
    root = insert(root, 35);
    insert(root, 15);
    insert(root, 20);
    insert(root, 30);
    insert(root, 25);
    insert(root, 45);
    insert(root, 55);
    insert(root, 10);
    insert(root, 5);

    // Printing the height of the binary tree
    printf("Height of tree is: %d \n", height(root));

    // Printing the level order traversal of the binary tree
    printf("Traversing the binary tree in level order: \n");
    printOrder(root);

    // Deleting a node with value 20 from the binary tree
    printf("\nDelete 25 \n");
    root = deleteNode(root, 25);

    // Printing the level order traversal of the binary tree after deletion
    printf("Traversing the binary tree in level order: \n");
    printOrder(root);

    return 0;
}
