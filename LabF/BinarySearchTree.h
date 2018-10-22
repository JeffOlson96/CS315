#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
using namespace std;       

// BinarySearchTree class
// added to By Jeff Olson on 5/8/18


/*
In order to implement countKeys and countNodes effectively, they have to have access
to the root node, meaning they have to be part of the class. The Methods added to the
class include:

int countKeys(BinaryNode* & t): returns the number of keys in the tree rooted at t.
->nodes that are "active"

int countNodes(BinaryNode* & t): returns the number of nodes in the tree rooted at t.
->all nodes in the tree

void printTree(BinaryNode* & t) : prints the tree using inorder traversal and only 
"active" keys

void remove( const Comparable & x, BinaryNode* & t) was adjusted to not completely delete
just set "active" value to false.


*/

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

    //countNodes and countKey begin right here
  
  
    //counts number of keys that are active inside of the Tree
    int countKeys() {
        int count = 0;
        if (isEmpty())
            cout << "Empty tree" << endl;
        else {
            countKeys(root, count);
            return count;
        }
    }

    //counts Number of Nodes currently in the tree, ie size
    int countNodes () {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            countNodes(root);
    }


  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        bool is_active; // bool value in BinaryNode struct to allow for "lazy deletion"

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt, bool status )
          : element{ theElement }, left{ lt }, right{ rt }, is_active { status } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt, bool status )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt }, is_active{ status } { }
    };

    BinaryNode *root;
    int size = 0; // size is private variable for storing the size of the tree


    //counts Number of keys, only counts if key is active
    int countKeys(BinaryNode * & t, int & count) {
        //int count = 0;
        if (t != nullptr) {
            if (t->is_active == true) {
                count++;
                countKeys(t->left, count);
                countKeys(t->right, count);
                //return count;
            }
            else {
                countKeys(t->left, count);
                countKeys(t->right, count);
            }
        }    
    }



    //counts Number of nodes, is size of the tree
    int countNodes (BinaryNode * & t) {
        if (root != nullptr) {
            return size;
        }
        else
            return 0;
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr ) {
            t = new BinaryNode{ x, nullptr, nullptr, true };
            size++;
        }
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr ) {
            t = new BinaryNode{ std::move( x ), nullptr, nullptr, true };
            size++;
        }
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ;  // Duplicate; do nothing
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            oldNode->is_active = false;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr && t->is_active == true )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
        else if ( t != nullptr && t->is_active == false ) {
            printTree( t->left, out );
            //out << "element has been deleted" << endl;
            printTree( t->right, out );
        }
    }
};

#endif
