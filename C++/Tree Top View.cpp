// Problem statement : https://www.hackerrank.com/challenges/tree-top-view/problem
#include<bits/stdc++.h>

using namespace std;

class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

class Solution {
    public:
  		Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            } else {
                Node* cur;
                if(data <= root->data) {
                    cur = insert(root->left, data);
                    root->left = cur;
                } else {
                    cur = insert(root->right, data);
                    root->right = cur;
               }

               return root;
           }
        }

/*
class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

*/

    void topView(Node * root) {
        if(root==NULL)   return;

        map<int,vector<int>> m;
        queue<pair<Node*,int>> que;
        que.push(make_pair(root,0));

        while(!que.empty())
        {
            pair<Node*,int> temp = que.front();
            que.pop();

            Node* node=temp.first;
            int hd=temp.second;

            m[hd].push_back(node->data);
            if(node->left != NULL)
                que.push(make_pair(node->left,hd-1));
            if(node->right!= NULL)
                que.push(make_pair(node->right,hd+1));
        }

        map<int,vector<int>>::iterator it;
        for(it=m.begin(); it!=m.end(); it++)
        {
            cout<<it->second[0]<<" ";
        }
    }

}; //End of Solution

int main() {
  
    Solution myTree;
    Node* root = NULL;
    
    int t;
    int data;

    std::cin >> t;

    while(t-- > 0) {
        std::cin >> data;
        root = myTree.insert(root, data);
    }
  
	myTree.topView(root);
    return 0;
}
