#include <iostream>
#include <limits>
using namespace std;

struct Node {
    int id;
    Node* left;
    Node* right;
    Node(int v) : id(v), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int v, bool& added) {
        if (node == nullptr) {
            added = true;
            return new Node(v);
        }
        if (v < node->id)      node->left  = insert(node->left, v, added);
        else if (v > node->id) node->right = insert(node->right, v, added);
        return node;   // duplicates are ignored
    }

    bool search(Node* node, int v) const {
        if (node == nullptr) return false;
        if (v == node->id) return true;
        if (v < node->id) return search(node->left, v);
        return search(node->right, v);
    }

    Node* minNode(Node* node) const {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    Node* remove(Node* node, int v, bool& removed) {
        if (node == nullptr) return nullptr;
        if (v < node->id) {
            node->left = remove(node->left, v, removed);
        } else if (v > node->id) {
            node->right = remove(node->right, v, removed);
        } else {
            removed = true;
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* succ = minNode(node->right);   // inorder successor
            node->id = succ->id;
            bool dummy = false;
            node->right = remove(node->right, succ->id, dummy);
        }
        return node;
    }

    void inorder(Node* n) const {
        if (!n) return;
        inorder(n->left);
        cout << n->id << " ";
        inorder(n->right);
    }
    void preorder(Node* n) const {
        if (!n) return;
        cout << n->id << " ";
        preorder(n->left);
        preorder(n->right);
    }
    void postorder(Node* n) const {
        if (!n) return;
        postorder(n->left);
        postorder(n->right);
        cout << n->id << " ";
    }
    void destroy(Node* n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(int v) {
        bool added = false;
        root = insert(root, v, added);
        if (added) cout << v << " inserted.\n";
        else cout << v << " already exists.\n";
    }
    void insertQuiet(int v) {
        bool added = false;
        root = insert(root, v, added);
    }
    void search(int v) const {
        if (search(root, v)) cout << v << " FOUND in the BST.\n";
        else cout << v << " NOT found in the BST.\n";
    }
    void remove(int v) {
        bool removed = false;
        root = remove(root, v, removed);
        if (removed) cout << v << " deleted.\n";
        else cout << v << " not found. Nothing deleted.\n";
    }
    void traversals() const {
        if (!root) {
            cout << "Tree is empty.\n";
            return;
        }
        cout << "Inorder   : "; inorder(root);   cout << "\n";
        cout << "Preorder  : "; preorder(root);  cout << "\n";
        cout << "Postorder : "; postorder(root); cout << "\n";
    }
};

int main() {
    BST tree;

    // Given employee IDs
    int ids[] = {50, 30, 70, 20, 40, 60, 80};
    for (int id : ids) tree.insertQuiet(id);

    cout << "BST created with: 50 30 70 20 40 60 80\n";
    tree.traversals();

    int choice = 0, v;
    do {
        cout << "\n===== EMPLOYEE BST MENU =====\n";
        cout << "1. Insert ID\n";
        cout << "2. Search ID\n";
        cout << "3. Delete ID\n";
        cout << "4. Display traversals\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter a number between 1 and 5.\n";
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
            case 2:
            case 3:
                cout << "Enter employee ID: ";
                if (!(cin >> v)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid ID.\n";
                    break;
                }
                if (choice == 1) tree.insert(v);
                else if (choice == 2) tree.search(v);
                else tree.remove(v);
                break;
            case 4:
                tree.traversals();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Enter 1 to 5.\n";
        }
    } while (choice != 5);

    return 0;
}
