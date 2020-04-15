#pragma once
//
// MergeSort Realization of SortingMachine using List
// author: Dr. Holly  
// updated by : Dr. H on 10/25/2019. Removed wrapper type requirements.
// This SortingMachine1 uses recursive MergeSort instead of exchangeSort.
// The MergeSort is implemented with 3 functions; mergeSort, split, and merge
// Edited by : Greg Bailey on (date edited here)


#include "List.hpp"

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class T, class TCallback>
class SortingMachine1
		//! SortingMachine1 is modeled by (
		//!      contents: FiniteMultiSet(T)
		//!      inserting: boolean
		//!   )
		//! exemplar self

		//! math operation IS_FIRST (
		//!          s: FiniteMultiSet(T),
		//!          x: T
		//!      ): boolean
		//!      definition
		//!          x is in s  and
		//!          for all y: Item where (y is in s)
		//!             (areOrdered (x, y))

		//! TCallback required to have an areOrdered operation:
		//! 
		//! Boolean areOrdered (T& lhs, T& rhs)
		//! restores lhs, rhs
		//!   areOrdered returns true iff the two items compared
		//!      are in order relative to each other.
		//!   lhs stands for left hand side
		//!   rhs stands for right hand side

{
public: // Standard Operations
	SortingMachine1 ();
   		//! replaces self
   		//! ensures: ({},true)
	~SortingMachine1 ();
	void clear (void);
		//! clears self
	void transferFrom (SortingMachine1& source);
		//! replaces self
		//! clears source
		//! ensures: self = #source
	SortingMachine1& operator = (SortingMachine1& rhs);
   		//! updates self
   		//! restores rhs
   		//! ensures: self = rhs

	// SortingMachine1 Specific Operations
	void add (T& x);
   		//! updates self.contents
   		//! clears x
   		//! requires: self.inserting
   		//! ensures: self.contents = #self.contents  union  {#x}  and
   		//!          self.inserting = true
	void changeToExtractionMode (void);
   		//! updates self.inserting
   		//! requires: self.inserting
   		//! ensures: self.inserting = false  and  self.contents = #self.contents
	void removeFirst (T& x);
   		//! updates self.contents
   		//! replaces x
   		//! requires: not self.inserting  and  |self.contents| > 0
   		//! ensures: IS_FIRST (#self.contents, x)  and
   		//!          self.contents = #self.contents \ {x}  and
   		//!          self.inserting = false
	int size (void);
   		//! restores self
   		//! ensures: size = |self.contents|
	bool isInInsertionMode (void);
   		//! restores self
   		//! ensures: isInInsertionMode = self.inserting

	friend ostream& operator<< (ostream& os, SortingMachine1& s);
		//! updates os
		//! restores s

private: // Representation
	typedef List1 <T> ListOfT;

	bool insertionMode;
	ListOfT itemKeeper;

private: // Local Operations
	 
    //Three functions students have to implement
    void split(ListOfT& l, ListOfT& l1, ListOfT& l2);
    void merge(ListOfT& l, ListOfT& l1, ListOfT& l2);
    void mergeSort(ListOfT& l);
    
    

private: // Disallowed SortingMachine1 Operations
	SortingMachine1 (const SortingMachine1& s);
	SortingMachine1* operator & (void) {return this;};
	const SortingMachine1* operator & (void) const {return this;};
};

//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------

// convention
// itemKeeper.left = <>
//

//----------------------------------------------------------------
// Local Operations
//----------------------------------------------------------------
template <class T, class TCallback>
void SortingMachine1<T, TCallback>::split(ListOfT& l, ListOfT& l1, ListOfT& l2)
//! clears l
//! replaces l1, l2
//! requires: |l| > 1
//! ensures: perms(#l, l1 * l2) and
//!          floor(|#l|/2) <= |l1| <= ceiling(|#l|/2) and
//!          floor(|#l|/2) <= |l2| <= ceiling(|#l|/2)
{
	T x;
	int i = 0;
	int z = l.rightLength();
	for (; i < z; i++) {
		l.removeRightFront(x);
		if ( i < z/2) {
			l1.addRightFront(x);
			l1.advance();
		} else {
			l2.addRightFront(x);
			l2.advance();
		} // end if/else
	} // end for
	l1.moveToStart();
	l2.moveToStart();
} // split

//----------------------------------------------------------------

template <class T, class TCallback>
void SortingMachine1<T, TCallback>::merge(ListOfT& l, ListOfT& l1, ListOfT& l2)
//! replaces l
//! clears l1, l2
//! ensures: sorted(q) and perms(l, #l1 * #l2)
{
	T rec1, rec2;
	int l1length = l1.rightLength();
	int l2length = l2.rightLength();

	while ( l1length > 0 && l2length > 0) {
		l1.removeRightFront(rec1);
		l2.removeRightFront(rec2);

		if (TCallback::areOrdered(rec1, rec2)) {
			l.addRightFront(rec1);
			l2.addRightFront(rec2);
			l1length--;
		} else {
			l.addRightFront(rec2);
			l1.addRightFront(rec1);
			l2length--;
		} // end if
		l.advance();

	} // end while

	while (l2length > 0) {
		l2.removeRightFront(rec2);
		l.addRightFront(rec2);
		l2length--;
		l.advance();
	} // end while

	while (l1length > 0) {
		l1.removeRightFront(rec1);
		l.addRightFront(rec1);
		l1length--;
		l.advance();
	}
} // merge

//----------------------------------------------------------------

template <class T, class TCallback>
void SortingMachine1<T, TCallback>::mergeSort (ListOfT& l)
//! updates l
//! ensures: sorted(l) and perms(l, #l)
//! decreasing: |l|
{
	if ( l.rightLength() > 1) {
		ListOfT L1, L2;
		split(l, L1, L2);
		mergeSort(L1);
		mergeSort(L2);
		merge(l, L1, L2);
	} // end if
} // mergeSort


//----------------------------------------------------------------
// Exported Operations
//----------------------------------------------------------------

template <class T, class TCallback>
SortingMachine1<T, TCallback>::SortingMachine1 ()
{
	insertionMode = true;
}	// SortingMachine1

//----------------------------------------------------------------

template <class T, class TCallback>
SortingMachine1<T, TCallback>::~SortingMachine1 ()
{
}	// ~SortingMachine1

//----------------------------------------------------------------

template <class T, class TCallback>
void SortingMachine1<T, TCallback>::clear(void)
{
	itemKeeper.clear();
	insertionMode = true;
}	// clear

//-----------------------------------------------------------------------

template <class T, class TCallback>
void SortingMachine1<T, TCallback>::transferFrom(SortingMachine1& source)
{
	insertionMode=source.insertionMode;
	source.insertionMode = true;
	itemKeeper.transferFrom(source.itemKeeper);
} // transferFrom

//-----------------------------------------------------------------------

template <class T, class TCallback>
SortingMachine1<T, TCallback>& 
SortingMachine1<T, TCallback>::operator = (SortingMachine1& rhs)
{
	insertionMode = rhs.insertionMode;
	itemKeeper = rhs.itemKeeper;
	return *this;
} // operator =

//----------------------------------------------------------------

template <class T, class TCallback>
void SortingMachine1<T, TCallback>::add (T& x)
{
	itemKeeper.addRightFront(x);
}	// add

//----------------------------------------------------------------

template <class T, class TCallback>
void SortingMachine1<T, TCallback>::changeToExtractionMode (void)
{
	mergeSort(itemKeeper);
	insertionMode = false;
}	// changeToExtractionMode

//----------------------------------------------------------------

template <class T, class TCallback>
void SortingMachine1<T, TCallback>::removeFirst (T& x)
{
	itemKeeper.removeRightFront(x);
}	// removeFirst

//----------------------------------------------------------------

template <class T, class TCallback>
int SortingMachine1<T, TCallback>::size (void)
{
   return itemKeeper.rightLength();
}	// size

//----------------------------------------------------------------

template <class T, class TCallback>
bool SortingMachine1<T, TCallback>::isInInsertionMode (void)
{
   return insertionMode;
}	// isInInsertionMode

//-----------------------------------------------------------------------

template <class T, class TCallback>
ostream& operator<<(ostream& os, SortingMachine1<T, TCallback>& sm)
{
#ifdef NDEBUG
	Boolean inInsertionPhase;
	SortingMachine1<T, TCallback> temp;

	inInsertionPhase = sm.isInInsertionMode();
	if (inInsertionPhase) {
		sm.changeToExtractionMode();
	}   // end if
	os << L"({";
	for (int k = 0, z = sm.size(), lastItem = z - 1; k < z; k++) {
		T x;

		sm.removeFirst(x);
		os << x;
		temp.add(x);
		if (k < lastItem) {
			os << L",";
		} // end if
	}	// end for
	os << L"},";
	os << inInsertionPhase << L")";

	sm.transferFrom(temp);
	if (!inInsertionPhase) {
		sm.changeToExtractionMode();
	}   // end if
#else
	os << sm.itemKeeper;
#endif
	return os;
} // operator<<
