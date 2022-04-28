#ifndef	BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE
#include <iostream>
using namespace std;
template <class Comparable>
class BinarySearchTree;
template <class Comparable>
class BinaryNode
{
	Comparable element;
	BinaryNode *left;
	BinaryNode *right;

	BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt ) : element( theElement ), left( lt ), right( rt ) { }

	friend class BinarySearchTree<Comparable>;
};


template <class Comparable>
class BinarySearchTree
{
public:
	explicit BinarySearchTree( const Comparable & notFound );
	BinarySearchTree( const BinarySearchTree & rhs );
	~BinarySearchTree( );
	const Comparable & findMin( ) const;
	const Comparable & findMax( ) const;
	const Comparable & find( const Comparable & x) const;
	bool isEmpty( ) const;
	void printTree( ) const;
	void makeEmpty( );
	void insert( const Comparable & x );
	void remove( const Comparable & x );
private:
	BinaryNode<Comparable> *root;
	const Comparable ITEM_NOT_FOUND;
	const Comparable & elementAt( BinaryNode<Comparable> *t ) const;
	void insert( const Comparable & x, BinaryNode<Comparable> * & t ) const;
	void remove( const Comparable & x, BinaryNode<Comparable> * & t ) const;
	BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * find( const Comparable & x, BinaryNode<Comparable> *t ) const;
	void makeEmpty( BinaryNode<Comparable> * & t ) const;
	void printTree( BinaryNode<Comparable> *t ) const;
};

#endif