#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef pair<int, int> pii;
#define sz(a) int((a).size())
#define all(c) (c).begin(), (c).end()
#define rall(x) x.rbegin(), x.rend()
#define ld long double
#define pb push_back
#define sza(x) ((int)x.size())
#define f(i,s,n) for(long long int i=s;i<n;i++)

class BPlusTreeNode;

class Node
{
public:
    int data_val;
    BPlusTreeNode *leftchild;

    Node()
    {
        leftchild = nullptr;
    }
};

class BPlusTreeNode
{
public:
    vector<Node *> val;
    bool isLeafNode;
    BPlusTreeNode *right_child;
    BPlusTreeNode *parent;

    BPlusTreeNode()
    {
        right_child = nullptr;
        parent = nullptr;
    }
};

bool compare(Node *a, Node *b)
{
    return a->data_val < b->data_val;
}

class BPlusTree
{
public:
    BPlusTreeNode *root;
    int d;
    int t;
    BPlusTree(int d, int t)
    {
        root = nullptr;
        this->d = d;
        this->t = t;
    }

    void insert(int data)
    {
        if (root == nullptr)
        {
            BPlusTreeNode *x = new BPlusTreeNode();
            x->isLeafNode = true;

            Node *n = new Node();
            n->data_val = data;
            x->val.push_back(n);
            root = x;
            return;
        }

        if (root->isLeafNode == true)
        {
            if (root->val.size() < 2 * d)
            {
                Node *n = new Node();
                n->data_val = data;
                root->val.push_back(n);
                sort(root->val.begin(), root->val.end(), compare);
            }
            else
            {
                Node *n = new Node();
                n->data_val = data;
                root->val.push_back(n);
                sort(root->val.begin(), root->val.end(), compare);

                BPlusTreeNode *right_node = new BPlusTreeNode();
                right_node->isLeafNode = true;

                for (int i = d; i < root->val.size(); i++)
                {
                    Node *n = new Node();
                    n->data_val = root->val[i]->data_val;
                    right_node->val.push_back(n);
                }

                for (int i = 0; i < d + 1; i++)
                {
                    root->val.pop_back();
                }

                BPlusTreeNode *new_root = new BPlusTreeNode();
                new_root->isLeafNode = false;

                n = new Node();
                n->data_val = right_node->val[0]->data_val;
                n->leftchild = root;

                new_root->val.push_back(n);
                new_root->right_child = right_node;

                root = new_root;
                root->val[0]->leftchild->parent = root;
                root->right_child->parent = root;
            }
            return;
        }

        BPlusTreeNode *curr = root;
        while (curr->isLeafNode == false)
        {
            int k = 0;
            for (int i = 0; i < curr->val.size(); i++)
            {
                if (curr->val[i]->data_val > data)
                {
                    k = 1;
                    curr = curr->val[i]->leftchild;
                    break;
                }
            }
            if (k == 0)
            {
                curr = curr->right_child;
            }
        }

        if (curr->val.size() < 2 * d)
        {
            Node *n = new Node();
            n->data_val = data;
            curr->val.push_back(n);
            sort(curr->val.begin(), curr->val.end(), compare);
            return;
        }

        Node *n = new Node();
        n->data_val = data;
        curr->val.push_back(n);
        sort(curr->val.begin(), curr->val.end(), compare);

        BPlusTreeNode *right_node = new BPlusTreeNode();
        right_node->isLeafNode = true;

        for (int i = d; i < curr->val.size(); i++)
        {
            Node *n = new Node();
            n->data_val = curr->val[i]->data_val;
            right_node->val.push_back(n);
        }

        for (int i = 0; i < d + 1; i++)
        {
            curr->val.pop_back();
        }

        n = new Node();
        n->data_val = right_node->val[0]->data_val;
        right_node->parent = curr->parent;

        n->leftchild = curr;
        if (n->data_val > curr->parent->val[curr->parent->val.size() - 1]->data_val)
        {
            curr->parent->val.push_back(n);
            curr->parent->right_child = right_node;
        }
        else
        {
            curr->parent->val.push_back(n);
            BPlusTreeNode *curr_parent = curr->parent;
            sort(curr_parent->val.begin(), curr_parent->val.end(), compare);
            int j = 0;
            for (j = 0; j < curr_parent->val.size(); j++)
            {
                if (curr_parent->val[j]->data_val == n->data_val)
                {
                    break;
                }
            }

            curr_parent->val[j + 1]->leftchild = right_node;
        }

        curr = curr->parent;
        if (curr == nullptr)
        {
            return;
        }

        while (curr->val.size() > 2 * t + 1)
        {

            if (curr == root || curr == nullptr)
            {
                break;
            }


            BPlusTreeNode *right_node = new BPlusTreeNode();
            right_node->isLeafNode = false;

            int up_val = curr->val[t]->data_val;
            for (int i = t + 1; i < curr->val.size(); i++)
            {
                Node *n = new Node();
                n->data_val = curr->val[i]->data_val;
                n->leftchild = curr->val[i]->leftchild;
                right_node->val.push_back(n);
            }

            right_node->parent = curr->parent;
            right_node->right_child = curr->right_child;
            curr->right_child = curr->val[t]->leftchild;
            for (int i = 0; i < t + 2; i++)
            {
                curr->val.pop_back();
            }

            for (int i = 0; i < right_node->val.size(); i++)
            {
                right_node->val[i]->leftchild->parent = right_node;
            }
            right_node->right_child->parent = right_node;

            Node *n = new Node();
            n->data_val = up_val;
            n->leftchild = curr;

            if (n->data_val > curr->parent->val[curr->parent->val.size() - 1]->data_val)
            {
                curr->parent->val.push_back(n);
                curr->parent->right_child = right_node;
            }
            else
            {
                curr->parent->val.push_back(n);
                BPlusTreeNode *curr_parent = curr->parent;
                sort(curr_parent->val.begin(), curr_parent->val.end(), compare);
                int j = 0;
                for (j = 0; j < curr_parent->val.size(); j++)
                {
                    if (curr_parent->val[j]->data_val == n->data_val)
                    {
                        break;
                    }
                }

                curr_parent->val[j + 1]->leftchild = right_node;
            }
            curr = curr->parent;
        }

        if (curr == root && curr->val.size() > 2 * t + 1)
        {
            BPlusTreeNode *right_node = new BPlusTreeNode();
            right_node->isLeafNode = false;

            int up_val = curr->val[t]->data_val;

            for (int i = t + 1; i < root->val.size(); i++)
            {
                Node *n = new Node();
                n->data_val = root->val[i]->data_val;
                n->leftchild = root->val[i]->leftchild;
                right_node->val.push_back(n);
            }

            right_node->right_child = curr->right_child;
            curr->right_child = curr->val[t]->leftchild;

            for (int i = 0; i < t + 2; i++)
            {
                root->val.pop_back();
            }
            for (int i = 0; i < right_node->val.size(); i++)
            {
                right_node->val[i]->leftchild->parent = right_node;
            }
            right_node->right_child->parent = right_node;

            BPlusTreeNode *new_root = new BPlusTreeNode();
            new_root->isLeafNode = false;

            n = new Node();
            n->data_val = up_val;
            n->leftchild = root;

            new_root->val.push_back(n);
            new_root->right_child = right_node;

            root = new_root;
            root->val[0]->leftchild->parent = root;
            root->right_child->parent = root;
        }
    }

    int countIndexNodes(BPlusTreeNode *node)
    {
        if (node == nullptr)
            return 0;

        if (node->isLeafNode == true)
            return 0;

        int k = 1;

        for (int i = 0; i < node->val.size(); i++)
        {
            k += countIndexNodes(node->val[i]->leftchild);
        }
        k += countIndexNodes(node->right_child);

        return k;
    }

    int countDataNodes(BPlusTreeNode *node)
    {
        if (node == nullptr)
            return 0;

        if (node->isLeafNode == true)
            return 1;

        int k = 0;
        for (int i = 0; i < node->val.size(); i++)
        {
            k += countDataNodes(node->val[i]->leftchild);
        }
        k += countDataNodes(node->right_child);

        return k;
    }

    void status()
    {
        if (root == nullptr)
            return;

        cout << countIndexNodes(root) << " " << countDataNodes(root) << " ";
        for (int i = 0; i < root->val.size(); i++)
        {
            cout << root->val[i]->data_val << " ";
        }
        cout << endl;

        return;
    }
};

int main()
{
    int d, t;
    cin >> d >> t;
    BPlusTree tree(d, t);
    int x;
    cin >> x;
    while (x != 3)
    {
        if (x == 1)
        {
            int val;
            cin >> val;
            tree.insert(val);
        }
        else if (x == 2)
        {
            tree.status();
        }
        else
        {
            return 0;
        }
        cin >> x;
    }
    return 0;
}