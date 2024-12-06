#include <iostream>
#include <fstream>

using namespace std;

//Change file names here if applicable
string inFileName = "input.txt";
string outFileName = "output.txt";

struct Node {
        int key;
        Node* left;
        Node* right;
        int height;
/*        Node() {
                key = -1;
                left = nullptr;
                right = nullptr;
                height = -1;
        }*/
        Node(int k) {
                key = k;
                left = nullptr;
                right = nullptr;
                height = 0;
        }
};

int getBalance(Node* node);
Node* rebalance(Node* node);
Node* insert(Node* node, int key);
Node* leftRotate(Node* x);
Node* rightRotate(Node* x);
void printLevel(Node* root);

int getBalance(Node* node) {
        int leftHeight = (node->left) ? node->left->height : -1;
        int rightHeight = (node->right) ? node->right->height : -1;
        return (leftHeight - rightHeight);
}

Node* rebalance(Node* node) {
        // node->height = max(height(node->left), height(node->right)) + 1;    

        int leftHeight = (node->left) ? node->left->height : -1;
        int rightHeight = (node->right) ? node->right->height : -1;
        node->height = max(leftHeight, rightHeight) + 1;

        int balance = getBalance(node);  //node->left - node->right

        if (balance > 1 && node->left && getBalance(node->left) > 0) { // left heavy outside
                return rightRotate(node);
        }
        else if (balance < -1 && node->right && getBalance(node->right) < 0) { // right heavy outside
                return leftRotate(node);
        }
        else if (balance > 1 && node->left && getBalance(node->left) < 0) { // left heavy inside:  left rotation first, right rotation 2nd, return top node
                node->left =  leftRotate(node->left);
                return rightRotate(node);
        }
        else if (balance < -1 && node->right && getBalance(node->right) > 0) { // right heavy inside: right rotation first, left rotation 2nd, return top node
                node->right = rightRotate(node->right);
                return leftRotate(node);
        }
        return node;
}

// non-tail recursive algorithm because of rebalance 
Node* insert(Node* node, int key) {
        // recursive code for inserting a node 
        // when insert happens set height to 0 for the node     

        if (node == nullptr) {
                return(new Node(key));
        }

        if (key < node->key) {
                node->left  = insert(node->left, key);
        } else {
                node->right = insert(node->right, key);
        }

        node = rebalance(node);  // update heights and rebalance

        return node;
}

Node* leftRotate(Node* x) {
        struct Node* y = x->right;
        Node* z = nullptr;
        if (y->left) {
                z = y->left;
        }
        x->right = z;
        y->left = x;
        // add more code to rotate to the left, update heights for x and y
        x = rebalance(x);
        y = rebalance(y);
        return y;
}

Node* rightRotate(Node* x) {
        struct Node* y = x->left;
        Node* z = nullptr;
        if (y->right) {
                z = y->right;
        }
        x->left = z;
        y->right = x;
        // add more code to rotate to the right, update heights for x and y  
        x = rebalance(x);  
        y = rebalance(y);
        return y;
}

ofstream& printLevel(Node* root, ofstream& outFile) {
        queue<Node*> currentLevel;
        queue<Node*> nextLevel;
        currentLevel.push(root);
        while (!currentLevel.empty()) {
                outFile << "k:" << currentLevel.front()->key << ",h:" << currentLevel.front()->height << ",b:" << getBalance(currentLevel.front());
                if (currentLevel.front()->left) {
                        nextLevel.push(currentLevel.front()->left);
                }
                if (currentLevel.front()->right) {
                        nextLevel.push(currentLevel.front()->right);
                }
                currentLevel.pop();
                if (currentLevel.empty()) {
                        currentLevel.swap(nextLevel);
                        outFile << endl;
                } else {
                        outFile << "\t";
                }
        }
        return outFile;
}

int main() {
        int newNum;
        Node* root = nullptr;

        ifstream inFile; 
        inFile.open(inFileName);

        while (inFile >> newNum) {
                root = insert(root, newNum);
        }

        inFile.close();

        ofstream outFile;
        outFile.open(outFileName);

        printLevel(root, outFile);

        outFile.close();
        return 0;
}
