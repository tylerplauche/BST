#ifndef BST_H
#define BST_H

#include "BSTInterface.h"
#include <string>

using namespace std;

template<typename T>
class BST : public BSTInterface<T>
{
private:
  struct Node
  {
    T data_;
    Node* left_;
    Node* right_;
    Node(const T& d) : data_(d), left_(NULL), right_(NULL){}
  };
  Node* root_;
public:
  BST() {this->root_ = NULL;}
  ~BST() {clearTree();}

	/** Return true if node added to BST, else false */
	virtual bool addNode(const T& data)
  {
    return insert(this->root_, data); 
  }

	/** Return true if node removed from BST, else false */
	virtual bool removeNode(const T& data)
  {
    return remove(this->root_, data);
  }

	/** Return true if BST cleared of all nodes, else false */
	virtual bool clearTree()
  {
    return deleteTree(this->root_);
  }

	/** Return a level order traversal of a BST as a string */
	virtual string toString() const
  {
    stringstream out;
    if (root_ == NULL) 
    {
      out << " empty";
    }
    else
    {
      int level = -1;
      do
      {
        out << endl << "  " << ++level + 1 << ":";
      } while (outLevel(root_, level, out));
    }
    return out.str();
  } // end toString()

  friend ostream& operator<< (ostream& os, const BST<T>& bst)
  {

  } 

  bool Find(const T& data)
  {
    return search(root_, data);
  }
  bool search(Node*& node, const T& data)
  {
    if (node == NULL)
    {
      return false;
    }
    if (node->data_ == data)
    {
      return true;
    }
    if (data < node->data_)
    {
      return search(node->left_, data);
    }
    if (data > node->data_)
    {
      return search(node->right_, data);
    }
    return false;
  }
  bool insert(Node*& node, const T& data)
  {
    if (node == NULL)
    {
      node = new Node(data);
      return true;
    }
    if (data == node->data_)
    {
      return false;
    }
    if (data < node->data_)
    {
      return insert(node->left_, data);
    }
    if (data > node->data_)
    {
      return insert(node->right_, data);
    }
    return false;
  }
  bool remove(Node*& node, const T& data)
  {
    if (node == NULL)
    {
      return false;
    }
    if (data < node->data_)
    {
      return remove(node->left_, data);
    }
    else if (data > node->data_)
    {
      return remove(node->right_, data);
    }
    else
    {
      Node* temp = InOrderPredecessor(data);
      Node* temp2 = node;

      node->data_ = temp->data_;
      temp->data_ = temp2->data_;

    }


    return remove(node->left_, data);
  }

  bool outLevel(Node* root, int level, stringstream& out) const
  {
    if (root == NULL)
    {
      return false;
    }
    if (level == 0)
    {
      out << " " << root->data_;
    
      if ((root->left_ != NULL) || (root->right_ != NULL))
      {
        return true;
      }
      return false;
    }
    if ((level == 1) && !root->left_ && root->right_)
    {
      out << " _";
    }
    bool left = outLevel(root->left_, level - 1, out);
    bool right = outLevel(root->right_, level - 1, out);
    if ((level == 1) && root->left_ && !root->right_)
    {
      out << " _";
    }
    return left || right;
  } // end outLevel()

  bool deleteTree(Node*& node)
  {
    if (node == NULL)
    {
      return true;
    }
    
    if(node->right_ != NULL)
    {
      deleteTree(node->right_);
    }
    
    if(node->left_ != NULL)
    {
      deleteTree(node->left_);
    }
    
    delete node;

    return true;
  }
  
  Node* InOrderPredecessor(const T& data)
  {
    Node* inOrderPredecessor = NULL;
    Node* current = root_;

    if(root_ == NULL)
    {
      return NULL;
    }
    while(current->left_->data_ != data && current->right_->data_ != data)
    {
      if(current->data_ > data)
      {
        current= current->left_;
      }
      else
      {
        inOrderPredecessor = current;
        current = current->right_;
      }
    }
    if(current->left_)
    {
      inOrderPredecessor = findMaximum(current->left_);
    }
    return inOrderPredecessor;
  }
  Node* findMaximum(Node* node)
  {
    while(node->right_)
    {
      node = node->right_;
    }
    return node;
  }

  int FindSize()
  {
    return TreeSize(this->root_);
  }

  int TreeSize(Node* node)
  {
    if (node == NULL)
    {
      return 0;
    }
    else
    {
      return(TreeSize(node->left_) + 1 + TreeSize(node->right_));
    }
  }
};
#endif //BST_H
