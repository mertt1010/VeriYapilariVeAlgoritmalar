#include <iostream>
#include <cstddef>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
};

// Yeni bir d���m olu�turduk
Node* createNode(int data) {
    Node* newNode = new Node();
    if (newNode) {
        newNode->data = data;
        newNode->left = newNode->right = nullptr;
    }
    return newNode;
}

// �kili arama a�ac�na bir d���m eklemek i�in kullan�lan fonksiy
Node* addBST(Node* root, int data) {
    if (root == nullptr) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = addBST(root->left, data);
    } else if (data > root->data) {
        root->right = addBST(root->right, data);
    }
    return root;
}

// �kili arama a�ac�ndaki en k���k d���m� bulmak i�in kullan�lan fonksiyon
Node* findSmallestBST(Node* root) {
    if (root == nullptr || root->left == nullptr) {
        return root;
    }
    return findSmallestBST(root->left);
}

// �kili arama a�ac�ndaki en b�y�k d���m� bulmak i�in kullan�lan fonksiyon
Node* findLargestBST(Node* root) {
    if (root == nullptr || root->right == nullptr) {
        return root;
    }
    return findLargestBST(root->right);
}

// �kili arama a�ac�nda bir d���m� aramak i�in kullan�lan fonksiyon
Node* searchBST(Node* root, int targetKey) {
    if (root == nullptr || root->data == targetKey) {
        return root;
    }
    if (targetKey < root->data) {
        return searchBST(root->left, targetKey);
    } else {
        return searchBST(root->right, targetKey);
    }
}

// �kili arama a�ac�n� s�ral� olarak gezerek d���mleri ekrana yazd�ran fonksiyon
void inorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}


int main() {
    Node* root = nullptr;
    root = addBST(root, 50);
    addBST(root, 8);
    addBST(root, 6);
    addBST(root, 4);
    addBST(root, 7);
    addBST(root, 12);
    addBST(root, 15);
    
    cout << "list: ";
    inorderTraversal(root);
    cout << std::endl;
    
    Node* smallestNode = findSmallestBST(root);
    if (smallestNode != nullptr) {
        cout << "bst'nin en k�c�k d�g�m: " << smallestNode->data << std::endl;
    }
    
    Node* largestNode = findLargestBST(root);
    if (largestNode != nullptr) {
        cout << "bst'nin en buyuk dugum: " << largestNode->data << std::endl;
    }
    
    int key = 15;
    Node* searchResult = searchBST(root, key);
    if (searchResult != nullptr) {
        cout << key << " bst'de var." << std::endl;
    } else {
        cout << key << " bst'de bulunmuyor." << std::endl;
    }
    
    return 0;
}
