#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

int nextPrime( int n );


// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTable
{
  public:
    explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
      { makeEmpty( ); }
    
    bool contains( const HashedObj & x, int chose )
    {
        if (isActive( findPos( x , chose) )) {
            NumberSearchProbes += 1; // in findpos, each section checks 3 times
            return true;
        }
        else
            return false;
    }
    
    /*
    bool contains( const HashedObj & x ) const
    {
        auto & whichArr = array[ myhash( x ) ];
        return find( begin( whichArr ), end( whichArr ), x ) != end( whichArr );
    }
    */

    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : array )
            entry.info = EMPTY;
    }

    void printHashTable () {
        //cout << array.size() << endl;
        for (auto & entry : array) {
            cout << "info"<< entry.element << endl;

        }
    }

    bool insert( const HashedObj & x, int chose )
    {
        while (currentSize/array.size() < 0.5) {
                // Insert x as active
            int currentPos = findPos( x, chose );
            if( isActive( currentPos ) ) {
                NumberInsertProbes += 1;
                return false;
            }

            if( array[ currentPos ].info != DELETED ) {
                NumberInsertProbes += 1;
                ++currentSize;
            }

            array[ currentPos ].element = x;
            array[ currentPos ].info = ACTIVE;
            NumberInsertProbes += 2; //two insert probes right here

                // Rehash; see Section 5.5
            if( currentSize > array.size( ) / 2 ) {
                rehash( chose );
            }

            return true;
        }
    }
    
    bool insert( HashedObj && x, int chose )
    {
            // Insert x as active
        while (currentSize/array.size() < 0.5) {
            int currentPos = findPos( x, chose );
            if( isActive( currentPos ) ) {
                NumberSearchProbes += 1;
                return false;
            }

            if( array[ currentPos ].info != DELETED ) {
                ++currentSize;
                NumberSearchProbes += 1;
            }

            array[ currentPos ] = std::move( x );
            array[ currentPos ].info = ACTIVE;
            NumberInsertProbes += 2; //two insert probes right here

            // Rehash; see Section 5.5
            if( currentSize > array.size( ) / 2 ) {
                rehash( chose );
            }

            return true;
        }
    }

    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        return true;
    }

    int GetNumberSearchProbes() {
        return NumberSearchProbes;
    }

    int GetNumberInsertProbes() {
        return NumberInsertProbes;
    }

    void ResetProbeCounters() {
        NumberInsertProbes = 0;
        NumberSearchProbes = 0;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };
    
    //int NumberOfKeys;
    int NumberSearchProbes = 0;
    int NumberInsertProbes = 0;
    

  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
          : element{ e }, info{ i } { }
        
        HashEntry( HashedObj && e, EntryType i = EMPTY )
          : element{ std::move( e ) }, info{ i } { }
    };
    
    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }

    int findPos( const HashedObj & x, int chose) const
    {
        int offset, currentPos;
        if (chose == 1) {
            //quadratic hashing
            offset = 1;
            currentPos = myhash( x );

            while( array[ currentPos ].info != EMPTY &&
                array[ currentPos ].element != x )
            {
                currentPos += offset;  // Compute ith probe
                offset += 2;
                if( currentPos >= array.size( ) )
                    currentPos -= array.size( );
            }

            return currentPos;
        }
        if (chose == 2) {
            // double hashing
            static hash<HashedObj> dhf;
            offset = 71 - (dhf(x) % 71);
            currentPos = myhash( x );
            while( array[ currentPos ].info != EMPTY &&
                array[ currentPos ].element != x )
            {
                currentPos += offset;  // Compute ith double probe
                if( currentPos >= array.size( ) )
                    currentPos -= array.size( );
            }
            return currentPos;

        }
        if (chose == 3) {
            // linear hashing
            offset = 1;
            currentPos = myhash( x );

            while( array[ currentPos ].info != EMPTY &&
                array[ currentPos ].element != x )
            {
                offset++;
                currentPos += offset;  // Compute ith probe
                if( currentPos >= array.size( ) )
                    currentPos -= array.size( );
            }
            return currentPos;
        }
    }

    void rehash( int chose )
    {
        vector<HashEntry> oldArray = array;

            // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( auto & entry : array )
            entry.info = EMPTY;

            // Copy table over
        currentSize = 0;
        for( auto & entry : oldArray )
            if( entry.info == ACTIVE )
                insert( std::move( entry.element ), chose );
    }

    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % array.size( );
    }
};

#endif
