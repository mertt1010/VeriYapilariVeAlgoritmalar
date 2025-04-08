#include <iostream>
#include <cstddef>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
};

// Yeni bir düðüm oluþturduk
Node* createNode(int data) {
    Node* newNode = new Node();
    if (newNode) {
        newNode->data = data;
        newNode->left = newNode->right = nullptr;
    }
    return newNode;
}

// Ýkili arama aðacýna bir düðüm eklemek için kullanýlan fonksiy
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

// Ýkili arama aðacýndaki en küçük düðümü bulmak için kullanýlan fonksiyon
Node* findSmallestBST(Node* root) {
    if (root == nullptr || root->left == nullptr) {
        return root;
    }
    return findSmallestBST(root->left);
}

// Ýkili arama aðacýndaki en büyük düðümü bulmak için kullanýlan fonksiyon
Node* findLargestBST(Node* root) {
    if (root == nullptr || root->right == nullptr) {
        return root;
    }
    return findLargestBST(root->right);
}

// Ýkili arama aðacýnda bir düðümü aramak için kullanýlan fonksiyon
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

// Ýkili arama aðacýný sýralý olarak gezerek düðümleri ekrana yazdýran fonksiyon
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
        cout << "bst'nin en kücük dügüm: " << smallestNode->data << std::endl;
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
