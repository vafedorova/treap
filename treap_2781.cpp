#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    public:
    static int nodes_count;
    int key, priority;
    int node_num;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
    Node(int k, int p): key(k), priority(p), node_num(++nodes_count) {}
    void split(int x, Node*& first, Node*& second);
};

int Node::nodes_count = 0;

Node* merge(Node* first, Node* second)
{
    if (!first)
        return second;
    if (!second)
        return first;
    if (first->priority < second->priority)
    {
        first->right = merge(first->right, second);
        first->right->parent = first;
        return first;
    }
    second->left = merge(first, second->left);
    second->left->parent = second;
    return second;
}

void Node::split(int x, Node*& first, Node*& second)
{
    if (key < x)
    {
        first = this;
        if (right) {
            right->split(x, first->right, second);
        }
        else
            second = nullptr;
        first->parent = nullptr;
    }
    else
    {
        second = this;
        if (left) {
            left->split(x, first, second->left);
        }
        else
            first = nullptr;
        second->parent = nullptr;
    }
}

void print_treap(const Node *root) {
    if (root == nullptr) {
        return;
    }
    print_treap(root->left);
    cout << "(" << root->key << ", " << root->priority << "):  parent = " << (root->parent ? root->parent->key : 0);
    print_treap(root->right);
}

Node *add1(Node *root, Node *new_node) {
    if (root == nullptr) {
        root = new_node;
        return root;
    }
    Node *first = nullptr;
    Node *second = nullptr;
    root->split(new_node->key, first, second);
    root = merge(merge(first, new_node), second);
    return root;
}

Node *add(Node *root, Node *new_node) {
    if (root == nullptr) {
        root = new_node;
        return root;
    }
    if (root->priority > new_node->priority) {
        Node *first = nullptr;
        Node *second = nullptr;
        root->split(new_node->key, first, second);
        if (first != nullptr)
            first->parent = new_node;
        if (second != nullptr)
            second->parent = new_node;
        new_node->left = first;
        new_node->right = second;
        return new_node;
    }
    if (new_node->key < root->key) {
        root->left = add(root->left, new_node);
    } else {
        root->right = add(root->right, new_node);
    }
    if (root->right == new_node || root->left == new_node) {
        new_node->parent = root;
    }
    return root;
}


int main() {
    Node *root = nullptr;
    int n;
    cin >> n;
    vector<Node *> all_nodes(n);
    all_nodes.reserve(n);
    int a, b;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        all_nodes[i] = new Node(a, b);
        root = add(root, all_nodes[i]);
    }
    cout << "YES\n"; 
    for (const Node *node: all_nodes) {
        cout << (node->parent == nullptr ? 0 : node->parent->node_num) << " " << (node->left == nullptr ? 0 : node->left->node_num) << " "
                                                                      << (node->right == nullptr ? 0 : node->right->node_num) << "\n";
    }
    return 0;
}