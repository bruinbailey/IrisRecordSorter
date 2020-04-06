// authors: Dr. H and Brandon Young
// compiled with g++ -std=c++1z List.hpp
// This is a List implementation based on Sequence<T>.
// List is represented as (<>,<>), with Sequence<T> left and right.

//DO NOT CHANGE THIS CODE!


#pragma once
#include <iostream>
#include "List.h"
#include <cstdio>
#include <cstring>

using namespace std;

template <class T>
List1<T>::List1() {}

template <class T>
List1<T>::~List1() {}

template <class T>
void List1<T>::clear() {
	left.clear();
	right.clear();
}//clear

template <class T>
void List1<T>::transferFrom(List1& source) {
	left.transferFrom(source.left);
	right.transferFrom(source.right);
}

template <class T>
List1<T>& List1<T>::operator = (List1& rhs) {
	left = rhs.left;
	right = rhs.right;
	return *this;
}

template <class T>
void List1<T>::moveToStart() {
	T temp;
	while (left.length() != 0) {
		left.remove(temp, left.length() - 1);
		right.add(temp, 0);
	}
}

template <class T>
void List1<T>::moveToFinish() {
	T temp;
	while (right.length() != 0) {
		right.remove(temp, 0);
		left.add(temp, left.length());
	}
}

template <class T>
void List1<T>::advance() {
	T temp;
	if (right.length() != 0) {
		right.remove(temp, 0);
		left.add(temp, left.length());
	}
}

template <class T>
void List1<T>::addRightFront(T& x) {
	right.add(x, 0);
}

template <class T>
void List1<T>::removeRightFront(T& x) {
	right.remove(x, 0);
}

template <class T>
T& List1<T>::rightFront() {
	T x;
	right.entry(x, 0);
	return x;
}

template <class T>
void List1<T>::replaceRightFront(T& x) {
	T temp = x;
	right.remove(x, 0);
	right.add(temp, 0);
}

template <class T>
void List1<T>::swapRights(List1& otherS) {
	Sequence<T> temp = right;
	right = otherS.right;
	otherS.right = temp;
}

template <class T>
int List1<T>::leftLength() {
	return left.length();
}

template <class T>
int List1<T>::rightLength() {
	return right.length();
}

template <class T>
void List1<T>::outputList() {
	cout << "(";
	left.outputSequence();
	cout << ", ";
	right.outputSequence();
	cout << ")"<<endl;
}
