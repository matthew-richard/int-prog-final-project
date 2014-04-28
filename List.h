#ifndef LIST_H
#define LIST_H

/* 
 * Primitive list with new and delete
 *
 */

#include <iostream>

using std::ostream;

template <typename T>
class List;

template <typename T>
class ListNode
{
friend class List<T>;
public:
	/* Constructor */
	ListNode( const T &data ); 

    T Get_data() const;

private:
	T content;
	ListNode<T> *next;
};

template <typename T>
class List
{
template <typename U>
friend ostream& operator<<(ostream& out, List<U> &l);
public:
	/* Constructor & Destructor */
	List(); 
	~List();

	void Insert( const T &data );
	bool Remove( T &data );
	ostream& Print(ostream& out) const;
private:
	ListNode<T> *First_ptr;
    ListNode<T> *Last_ptr;
};

#include "List.cpp"

#endif
