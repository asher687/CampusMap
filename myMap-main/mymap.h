#pragma once

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template<typename keyType, typename valueType>
class mymap {
 private:
    struct NODE {
        keyType key;
        valueType value;
        NODE* left;
        NODE* right;
        int nL;
        int nR;
        bool isThreaded;
    };
    NODE* root;
    int size;
    //
    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    //
    struct iterator {
     private:
        NODE* curr;  // points to current in-order node for begin/end

     public:
        iterator(NODE* node) {  // sets the current node
            curr = node;
        }

        keyType operator *() {  // () operator for access to the key
            return curr -> key;
        }

        bool operator ==(const iterator& rhs) {  //  = operator for comparing cur node with other
            if (curr == NULL && rhs.curr == NULL) {
              return this == &rhs;
            }
            return curr == rhs.curr;
        }

        bool operator !=(const iterator& rhs) {  // =! operator for comparing cur with another node
            if (curr == NULL && rhs.curr == NULL) {
              return this == &rhs;
            }
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }

        //
        // operator++:
        //
        // This function should advance curr to the next in-order node.
        // O(logN)
        //
        iterator operator++() {
          // if the node is threaded
          if (curr->isThreaded) {
            curr = curr->right;
          }
          // if the node is not  threaded
          else if(!curr->isThreaded) {
            curr = curr->right;
            NODE* cur = curr;
            NODE* prev = NULL;
            while (cur != NULL) {
              prev = cur;
              cur = cur->left;
            }
            // curr holds the left most node
            curr = prev;
          }
            return iterator(curr);
        }
    };

 public:
    //
    // default constructor:
    //
    // Creates an empty mymap.
    // Time complexity: O(1)
    //
    mymap() {
    this->root = NULL;
    this->size = 0;
    }

    //
    //
    // deleteTree: deletes every node in the tree
    // In-Order fashion | Left, Action, Right
    //
    //
    void deleteTree(NODE*& node) {

      // nothing to delete
      if (node == NULL) {
       return;
       }

      deleteTree(node->left);
      NODE* nodeNew = (node->isThreaded) ? NULL : node->right;
      deleteTree(nodeNew);

      delete node;
    }

    //
    //
    // copy_helper: copies every node onto this tree
    // Pre-Order fashion | Action, Left, Right
    //
    //
    void copy_helper(NODE* other) {
      if (other == NULL) {
       return;
      }
      else {
      put(other->key, other->value);

      copy_helper(other->left);  // left

      other = (other->isThreaded) ? NULL : other->right;

      copy_helper(other);  // right
      }
    }

    //
    // copy constructor:
    //
    // Constructs a new mymap which is a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap(const mymap& other) {
      this->root = NULL;
      this->size = 0;
      copy_helper(other.root);
    }

    //
    // operator=:
    //
    // Clears "this" mymap and then makes a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap& operator=(const mymap& other) {
      // delete this mymap
      deleteTree(this->root);
      this->size = 0;

      // if other mymap is empty just return an empty mymap
      if (other.root == NULL) {
       return *this;
      }

      // create first node for tree copy and start copying
      //this->root = new NODE();
      this->root = NULL;

      copy_helper(other.root);

        return *this;
    }

    //     // clear:
    //     //
    //     // Frees the memory associated with the mymap; can be used for testing.
    //     // Time complexity: O(n), where n is total number of nodes in threaded,
    //     // self-balancing BST.
    //     //
    void clear() {
      deleteTree(this->root);
      size = 0;
    }

    //
    // destructor:
    //
    // Frees the memory associated with the mymap.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    ~mymap() {
      if(this->size != 0) {
        deleteTree(this->root);
       }
    }

    // Helper function to search for a specific node in a tree
    NODE* findNode(NODE* i) {
      NODE* cur = root;
      NODE* notFound = NULL;

      while (cur != NULL) {
        if (cur == i) {  // node found
          return cur;
       }
        if (cur->key > i->key) {
          cur = cur->left;
       }
        else if (cur->key < i->key) {
         cur = (cur->isThreaded) ? NULL : cur->right;
       }
     }
     return notFound;
  }

    // Helper function to create and add a new node, given a key and a value
    NODE* addNode(keyType key, valueType value) {
      NODE* newNode = new NODE();

      newNode->key = key;

      newNode->value = value;

      newNode->nL = 0;

      newNode->nR = 0;

      newNode->left = NULL;

      newNode->right = NULL;

      newNode->isThreaded = true;

      return newNode;
    }

    // Helper function to search a tree (traversal)
    void search(NODE*& cur, NODE*& prev, keyType& key, vector<NODE*>& V, bool& foundKey, NODE*& foundNode) {

      while (cur != NULL) {
        prev = cur;

        if (cur->key == key) {
           foundKey = true;

           foundNode = cur;

           return;
        }
        if (cur->key > key) {
          V.push_back(cur);

          cur = cur->left;
        }
        else if (cur->key < key) {
          V.push_back(cur);

          cur = (cur->isThreaded) ? NULL : cur->right;
        }
      }
    return;
    }

    // Helper function to insert a node, given the kye the node is inserted left or right of the tree
    void insertNode(NODE*& prev, NODE*& newNode, bool& nodeInserted) {
      // INSERT Root ?
		  if (prev == NULL) {
        newNode->isThreaded = true;
        newNode->nL = 0;
        newNode->nR = 0;
        newNode->right = NULL;

        this->root = newNode;
        nodeInserted = true;
        return;
      }

      // INSERT LEFT
      else if (prev->key > newNode->key) {
        newNode->right = prev;

        newNode->isThreaded = true;
        newNode->left = NULL;
        newNode->nL = 0;
        newNode->nR = 0;
        prev->left = newNode;
        nodeInserted = true;
      }

      // INSERT RIGHT
      else if (prev->key < newNode->key) {
        newNode->right = prev->right;

        prev->isThreaded = false;
        newNode->isThreaded = true;
        newNode->nL = 0;
        newNode->nR = 0;
        newNode->left = NULL;
        prev->right = newNode;
        nodeInserted = true;
      }
    }

    // Helper function to check whether the tree is balanced or not, returns either tru or false
    bool isBalanced(vector<NODE*>& V, vector<NODE*>& nodesToFix, int& x) {
    int index = 0;  // represents the current node in V through the loop

    for(NODE*& i : V) {

      // if condition doesnt hold save this node and the previous
      // the previous can be the root or this can be the root.
      if ((max(i->nL, i->nR)) > (2 * min(i->nL, i->nR) + 1)) {
        nodesToFix.push_back(i);

       if (index > 0) {
          // problematic node is not root, so save the previous node too.
          nodesToFix.push_back(V[index-1]);

          // is the problematic node a left or right child? 1 - left / 2 - right
          // [0] child problem , [1] parent of problem
          if (nodesToFix[1]->left == nodesToFix[0]) {
            x = 1;
          }
          else if (nodesToFix[1]->right == nodesToFix[0]) {
          x = 2;
          }
        }

        return false;
      }
      index++;
    }
    return true;
    }

    //
    // balanceTree: given an inorder vector of nodes, will make a tree starting
    // with the middle node
    //
    NODE* balanceTree(vector<NODE*>& tree, int left, int right ) {

      int mid = (left + right) / 2;
      // cout << "left: " << left << " right: " << right << " Mid: " << mid << endl;

      // end of left side of vector
      if (mid-1 == left){
        // cout << "mid-1 == left" << endl;
        tree[left]->isThreaded = true;
        tree[left]->right = tree[mid];
        tree[left]->left = NULL;
        tree[left]->nL = 0;
        tree[left]->nR = 0;
        tree[mid]->left = tree[left];
        tree[mid]->nL = 1;

        // cout << "Assinged left a child" << endl;

      }

      // no left child
      if (left > mid-1) {
        // cout << "left > mid-1" << endl;
        tree[mid]->left = NULL;
        tree[mid]->nL = 0;

        // cout << "Set left child to NULL" << endl;
      }

      // assign left child to another subtree root
      else if (mid-1 > left) {
        tree[mid]->left = balanceTree(tree, left, mid-1);
        tree[mid]->nL = tree[mid]->left->nR + tree[mid]->left->nL + 1;
      }

      // end of right side of vector
      if (mid+1 == right){
        tree[right]->nR = 0;
        tree[right]->nL = 0;
        tree[right]->isThreaded = true;
        tree[right]->left = NULL;

        tree[mid]->right = tree[right];
        tree[mid]->isThreaded = false;
        tree[mid]->nR = 1;

      }

      // no right child
      if (mid+1 > right) {
        tree[mid]->right = NULL;
        tree[mid]->isThreaded = true;
        tree[mid]->nR = 0;
      }

      // assign right child to other subtree root
      else if (mid+1 < right) {
        tree[mid]->right = balanceTree(tree, mid+1, right);
        tree[mid]->nR = tree[mid]->right->nR + tree[mid]->right->nL + 1;
        tree[mid]->isThreaded = false;
      }

      return tree[mid];
    }
    // Helper function to properly update the node count in the balanced tree (nL and nR)
    void updateNodeCount(NODE*& newNode, vector<NODE*>& V) {
        for (auto& i : V) {

          NODE* foundNode = findNode(i);

          if (newNode->key < foundNode->key) {
            foundNode->nL++;
          }
          else if (newNode->key > foundNode->key) {
            foundNode->nR++;
          }

        }
    }

    //
    // put:
    //
    // Inserts the key/value into the threaded, self-balancing BST based on
    // the key.
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-tree that needs to be re-balanced.
    // Space complexity: O(1)
    //
    void put(keyType key, valueType value) {
      vector<NODE*> V;
      bool nodeInserted = false;
      bool foundKey = false;
      NODE* foundNode = NULL;
      vector<NODE*> nodesToFix;
      int x = 0;

			NODE* cur = this->root;
			NODE* prev = NULL;

      // 1) Look for given key
      search(cur, prev, key, V, foundKey, foundNode);

      // CASE 1 : Found key
      if (foundKey == true) {
       // 2) return value
       foundNode->value = value;
        return;
      }

      // CASE 2 : Did not find key
      else if (foundKey == false) {

        // 2) make new node
        NODE* newNode = addNode(key, value);

        // 3) Insert Node
        insertNode(prev, newNode, nodeInserted);

        // cout << "Node inserted: " << newNode->key << " with value: " << newNode->value << endl;

        if (nodeInserted == true) {
          // 4) Now update nL and nR for nodes travled
          updateNodeCount(newNode, V);

          // 5) check if traveled nodes are balanced
          if (isBalanced(V, nodesToFix, x) == false) {

            vector<NODE*> treeListToBalance;

            // 6) create an IN-Order vector of NODES starting at the problematic node, going down
            vectorNODE(nodesToFix[0], treeListToBalance);

            // cout << "IN-Order tree to be Balanced: " << endl;
            //print_Node_Vector(treeListToBalance);

            int left = 0;
            int right = treeListToBalance.size()-1;

            // 7) balance
            NODE* aNode = balanceTree(treeListToBalance, left, right);  //  balancing act ---------------------------------------------------------------------------

            // 8) Place balanced sub tree back into parent
            // if problem was at root

            if (nodesToFix.size() == 1) {
              this->root = aNode;
            }

            // make the parent of the old problematic node point to the root of the new tree
            else if (nodesToFix.size() == 2) {
              if (x == 1) {
                nodesToFix[1]->left = aNode;
              }

              else if (x == 2) {
                nodesToFix[1]->right = aNode;
              }
            }

          }

          size++;
        }
      }
//             // print new balanced WHOLE tree
//             string theString;
//             inToStringPreOrder(this->root, theString);
//             cout << "WHOLE Balanced Tree: " << endl;
//             cout << theString << endl;
      return;
    }

    //
    // contains:
    // Returns true if the key is in mymap, return false if not.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    bool contains(keyType key) {
    NODE* cur = root;
    while (cur != NULL) {
      if (cur->key == key) {
         return true;
      }
      if (cur->key > key) {
        cur = cur->left;
      }
      else if (cur->key < key) {
        cur = (cur->isThreaded) ? NULL : cur->right;
      }
    }
        return false;
    }

    //
    // get:
    //
    // Returns the value for the given key; if the key is not found, the
    // default value, valueType(), is returned (but not added to mymap).
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    valueType get(keyType key) {
    NODE* cur = root;
    while (cur != NULL) {
      if (cur->key == key) {
         return cur->value;
      }
      if (cur->key > key) {
        cur = cur->left;
      }
      else if (cur->key < key) {
        //cur = cur->right;
        cur = (cur->isThreaded) ? NULL : cur->right;  // isThreaded updated ----------------------------------------------------------------
      }
    }
        return valueType();
    }

    //
    // operator[]:
    //
    // Returns the value for the given key; if the key is not found,
    // the default value, valueType(), is returned (and the resulting new
    // key/value pair is inserted into the map).
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-trees that need to be re-balanced.
    // Space complexity: O(1)
    //
    valueType operator[](keyType key) {
    vector<NODE*> V;
    bool foundKey = false;
    NODE* cur = root;
    NODE* prev = NULL;
    NODE* foundNode = NULL;
    bool isNodeInserted = false;
    vector<NODE*> nodesToFix;
    int x = 0;

    // 1) functiion that searches tree for key,
    // * updates boolean foundKey = true if found
    // * and updates pointer to last node visited (prev)
    search(cur, prev, key, V, foundKey, foundNode);
    if(foundKey == true) {
      return foundNode->value;
    }

    // make new node if key is not in the tree
    if (foundKey == false) {
      NODE* newNode = addNode(key, valueType());

      // left or right add ?
      insertNode(prev, newNode, isNodeInserted);

      // Add to vector of traveled nodes
      V.push_back(newNode);

      // Now update the left and right subtree sizes for each node traveled
      if (isNodeInserted == true) {
        updateNodeCount(newNode, V);

        // 5) check if traveled nodes are balanced
        if (isBalanced(V, nodesToFix, x) == false) {

          vector<NODE*> treeListToBalance;

          // 6) create an IN-Order vector of NODES starting at the problematic node, going down
          vectorNODE(nodesToFix[0], treeListToBalance);

          int left = 0;
          int right = treeListToBalance.size()-1;

          // 7) balance
          NODE* aNode = balanceTree(treeListToBalance, left, right);  //  balancing act ---------------------------------------------------------------------------

          // 8) Place balanced sub tree back into parent
          // if problem was at root
          if (nodesToFix.size() == 1) {
            this->root = aNode;
          }

          // make the parent of the old problematic node point to the root of the new tree
          else if (nodesToFix.size() == 2) {
            if (x == 1) {
              nodesToFix[1]->left = aNode;
            }

            else if (x == 2) {
              nodesToFix[1]->right = aNode;
            }
          }

         }

        // increment size of tree
        this->size++;
       } // node is inserted action over
      } // if key is not found action over
    return valueType();
    }

    //
    // Size:
    //
    // Returns the # of key/value pairs in the mymap, 0 if empty.
    // O(1)
    //
    int Size() {
        return this->size;
    }

    //
    // begin:
    //
    // returns an iterator to the first in order NODE.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    iterator begin() {
    NODE* cur = root;
    NODE* prev = NULL;
    while (cur != NULL) {
      prev = cur;
      cur = cur->left;
    }
        return iterator(prev);
    }

    //
    // end:
    //
    // returns an iterator to the last in order NODE.
    // this function is given to you.
    //
    // Time Complexity: O(1)
    //
    iterator end() {
        return iterator(NULL);
    }

    //
    //
    // toStringHelper: will simply print the tree in order fashion onto an output stream
    //
    //
    void toStringHelper(NODE* node, ostream& theString) {
      if (node == NULL) {
        return;
       }
      toStringHelper(node->left, theString);

      stringstream ssK;

      ssK << node->key;

      string theKey;

      ssK >> theKey;

      stringstream ssV;

      ssV << node->value;

      string theVal;

      ssV >> theVal;

      theString << "key: " << theKey << " " << "value: " << theVal << "\n";

      node = (node->isThreaded) ? NULL : node->right;

      toStringHelper(node, theString);
}

    //
    // toString:
    //
    // Returns a string of the entire mymap, in order.
    // Format for 8/80, 15/150, 20/200:
    // "key: 8 value: 80\nkey: 15 value: 150\nkey: 20 value: 200\n
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string toString() {
    stringstream theString;

    toStringHelper(this->root, theString);

        return theString.str();
    }

    // helper function to put tree into vector of keytype
    void vectorPair(NODE* node, vector<pair<keyType,valueType>>& treeList) {
      if (node == NULL) {
        return;
       }
      vectorPair(node->left, treeList);
      treeList.emplace_back(node->key, node->value);
      node = (node->isThreaded) ? NULL : node->right;
      vectorPair(node, treeList);
}

    //
    //
    // print out vector
    //
    //
    void printVector(vector<pair<keyType,valueType>>& treeList) {
      for(auto& i : treeList) {
        cout << "Key: " << i.first << " Value: " << i.second << endl;
       }
       return;
    }

    //
    // toVector:
    //
    // Returns a vector of the entire map, in order.  For 8/80, 15/150, 20/200:
    // {{8, 80}, {15, 150}, {20, 200}}
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    vector<pair<keyType, valueType> > toVector() {
      vector<pair<keyType,valueType>> treeList;

      vectorPair(this->root, treeList);

      printVector(treeList);

      return treeList;//{};  // TODO: Update this return.
    }

    //
    //
    // // helper function to put tree into vector of nodes
    //
    //
    void vectorNODE(NODE* node, vector<NODE*>& treeList) {
      if (node == NULL) {
        return;
       }
      vectorNODE(node->left, treeList);

      treeList.emplace_back(node);

      node = (node->isThreaded) ? NULL : node->right;

      vectorNODE(node, treeList);
}
    //
    //
    // printVector: Helper function that prints the vector of pairs
    //
    //
    void print_Node_Vector(vector<NODE*>& treeList) {
      for(auto& i : treeList) {
        cout << "Key: " << i->key << " Value: " << i->value << endl;
       }
       return;
    }

    //
    // to_Node_Vector:
    //
    // Returns a vector of the entire map, in order.  For 8/80, 15/150, 20/200:
    // {{8, 80}, {15, 150}, {20, 200}}
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    vector<NODE*> to_Node_Vector() {
      vector<NODE*> treeList;

      vectorNODE(this->root, treeList);

      print_Node_Vector(treeList);

      return treeList;
    }

    //
    //
    // intoStringPlease: takes a node and puts its contents into a string
    // returns that string
    //
    //
    string intoStringPlease(NODE* node){
    string theString;
    stringstream SS;
    SS << node->key;
    string keySS;
    SS >> keySS;

       theString = "key: " + keySS + ", nL: " + to_string(node->nL) + ", nR: " + to_string(node->nR) + "\n" ;

      return theString;
    }

    //
    //
    // IntoStringPreOrder: will update the string parameter with the tree contents
    //  this is done in preOrder fashion
    //
    //
    void inToStringPreOrder(NODE* other, string& theString) {
      if (other == NULL) {
       return;
      }
      else {
      theString += intoStringPlease(other);

      inToStringPreOrder(other->left, theString);  // left

      other = (other->isThreaded) ? NULL : other->right;

      inToStringPreOrder(other, theString);  // right
      }
    }

    //
    // checkBalance:
    //
    // Returns a string of mymap that verifies that the tree is properly
    // balanced.
    // returns a string in this format (in pre-order):
    // "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string checkBalance() {
      string theString;
      inToStringPreOrder(this->root, theString);

        return theString;
    }
};
