// -*- Mode:c++;  -*-

#ifndef _BINARYTREE_H
#define _BINARY_TREE_H

#include <iostream>
#include <stack>
#include <queue>
using namespace std;


template <class T>
class BTItrIn;

template <class T>
class BTItrPre;

template <class T>
class BTItrPost;

template <class T>
class BTItrLevel;

template <class T>
class BinaryTree;

class Underflow { };

template <class T>
class BTNode {
  T element;
  BTNode *left, *right;
  
  friend class BinaryTree<T>;
  friend class BTItrIn<T>;
  friend class BTItrPre<T>;
  friend class BTItrPost<T>;
  friend class BTItrLevel<T>;
public:
  BTNode(const T &e, BTNode *esq = 0, BTNode *dir = 0) 
      : element(e), left(esq), right(dir) { }
};

template <class T>
class BinaryTree {
 public:
  BinaryTree() { root = 0; }
  BinaryTree(const BinaryTree &t);
  BinaryTree(const T&);
  BinaryTree(const T&elem, const BinaryTree & esq, const BinaryTree & dir); 
  ~BinaryTree() { makeEmpty(); }
  const BinaryTree &operator=(const BinaryTree & rhs);
  
  bool isEmpty () const
	{ return (root == 0) ? true : false; }
  T & getRoot () const
	{ if (root) return root->element; else throw Underflow(); } 
  
  void makeEmpty();
  void outputPreorder(ostream &out) const;
  
 private:
  BTNode<T> *root;

  void makeEmpty (BTNode<T> *r);
  BTNode<T> *copySubtree(const BTNode<T> *n) const;
  void outputPreorder(ostream &out, const BTNode<T> *n) const;

  friend class BTItrIn<T>;
  friend class BTItrPre<T>;
  friend class BTItrPost<T>;
  friend class BTItrLevel<T>;
};


template <class T>
BinaryTree<T>::BinaryTree(const T &v)
{
  root = new BTNode<T>(v);
}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &t)
{
  root = copySubtree(t.root);
}

template <class T>
BTNode<T> *BinaryTree<T>::copySubtree(const BTNode<T> *n) const
{
  if (n) {
    BTNode<T> *node = new BTNode<T>(n->element, copySubtree(n->left), 
				    copySubtree(n->right));
    return node;
  } else 
    return 0;
}

template <class T>
BinaryTree<T>::BinaryTree(const T&elem, const BinaryTree & esq, 
			  const BinaryTree & dir)
{
  root = new BTNode<T>(elem, copySubtree(esq.root), copySubtree(dir.root));
}

template <class T>
const BinaryTree<T> & BinaryTree<T>::operator=(const BinaryTree<T> & rhs)
{
  if (this != & rhs) {
    makeEmpty();
    root = copySubtree(rhs.root);
  }
  return *this;
}
  

template <class T>
void BinaryTree<T>::makeEmpty()
{
  makeEmpty(root); 
}


template <class T>
void BinaryTree<T>::makeEmpty(BTNode<T> *r)
{
  if (r) {
    makeEmpty(r->left);
    makeEmpty(r->right);
    delete r;
  }
}

template <class T>
void BinaryTree<T>::outputPreorder(ostream &out) const
{
  outputPreorder(out, root);

}

template <class T>
void BinaryTree<T>::outputPreorder(ostream &out, const BTNode<T> *r) const
{
  out << '(';
  if (r) {
    out <<  r->element << ' ';
    outputPreorder(out, r->left);
    out << ' ';
    outputPreorder(out, r->right);
  }
  out << ')';
}

// Para usar o operador <<
template <class T>
ostream &operator<<(ostream &out, const BinaryTree<T> &t)
{
  t.outputPreorder(out);
  return out;
}


// Iteradores

template <class T>
class BTItrPost {
public:
  BTItrPost(const BinaryTree<T> &bt);
  
  void advance();
  T &retrieve() { return itrStack.top()->element; }
  bool isAtEnd() {return itrStack.empty(); }

private:
  stack<BTNode<T> *> itrStack;
  stack<bool> visitStack;
  void slideDown(BTNode<T> *n);
};


template <class T>
BTItrPost<T>::BTItrPost (const BinaryTree<T> &bt)
{
  if (!bt.isEmpty())
    slideDown(bt.root);
}

template <class T>
void BTItrPost<T>::advance ()
{
  itrStack.pop();
  visitStack.pop();
  if ((!itrStack.empty()) && (visitStack.top() == false)) {
    visitStack.pop();
    visitStack.push(true);
    slideDown(itrStack.top()->right);
  }
}

template <class T>
void BTItrPost<T>::slideDown(BTNode<T> *n)
{ 
  while (n) {
    itrStack.push(n);
    if (n->left) {
      visitStack.push(false);
      n = n->left;
    } else if (n->right) {
      visitStack.push(true);
      n = n->right;
    } else {
      visitStack.push(true);
      break;
    }
  }
}


/////////////////////

template <class T>
class BTItrPre {
public:
  BTItrPre(const BinaryTree<T> &bt);
  
  void advance();
  T &retrieve() { return itrStack.top()->element; }
  bool isAtEnd() {return itrStack.empty(); }

private:
  stack<BTNode<T> *> itrStack;

};

template <class T>
BTItrPre<T>::BTItrPre (const BinaryTree<T> &bt)
{
  if (!bt.isEmpty())
    itrStack.push(bt.root);
}

template <class T>
void BTItrPre<T>::advance()
{
  BTNode<T> * actual = itrStack.top();
  BTNode<T> * seguinte = actual->left;
  if (seguinte)
    itrStack.push(seguinte);
  else {
    while (!itrStack.empty()) {
      actual = itrStack.top();
      itrStack.pop();
      seguinte = actual -> right;
      if (seguinte) {
	itrStack.push(seguinte);
	break;
      }
    }
  }
}


template <class T>
class BTItrIn {
public:
  BTItrIn(const BinaryTree<T> &bt);
  
  void advance();
  T &retrieve() { return itrStack.top()->element; }
  bool isAtEnd() {return itrStack.empty(); }

private:
  stack<BTNode<T> *> itrStack;

  void slideLeft(BTNode<T> *n);
};

template <class T>
BTItrIn<T>::BTItrIn (const BinaryTree<T> &bt)
{
  if (!bt.isEmpty())
    slideLeft(bt.root);
}

template <class T>
void BTItrIn<T>::slideLeft(BTNode<T> *n)
{
  while (n) {
    itrStack.push(n);
    n = n->left;
  }
}

template <class T>
void BTItrIn<T>::advance()
{
  BTNode<T> * actual = itrStack.top();
  itrStack.pop();
  BTNode<T> * seguinte = actual->right;
  if (seguinte)
    slideLeft(seguinte);
}


template <class T>
class BTItrLevel {
public:
  BTItrLevel(const BinaryTree<T> &bt);
  
  void advance();
  T &retrieve() { return itrQueue.front()->element; }
  bool isAtEnd() {return itrQueue.empty(); }

private:
  queue<BTNode<T> *> itrQueue;

};

template <class T>
BTItrLevel<T>::BTItrLevel (const BinaryTree<T> &bt)
{
  if (!bt.isEmpty())
    itrQueue.push(bt.root);
}

template <class T>
void BTItrLevel<T>::advance()
{
  BTNode<T> * actual = itrQueue.front();
  itrQueue.pop();
  BTNode<T> * seguinte = actual->left;
  if (seguinte)
    itrQueue.push(seguinte);
  seguinte = actual->right;
  if (seguinte)
    itrQueue.push(seguinte);
}



#endif

