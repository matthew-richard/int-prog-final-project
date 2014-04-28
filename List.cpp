/* 
 * Primitive list with new and delete
 *
 */

#include <iostream>

using std::ostream;
using std::endl;

/* ListNode Constructor */
template<typename T>
ListNode<T>::ListNode( const T &data )
	: content( data ), next( NULL )
{
  // Empty body
}

template<typename T>
T ListNode<T>::Get_data() const
{
	return content;
}


template<typename T>
List<T>::List()
{
	First_ptr = NULL;
    Last_ptr = NULL;
}

template<typename T>
List<T>::~List()
{
    ListNode<T> *pnode;

    while( First_ptr != NULL )
    {
	pnode = First_ptr;
	First_ptr = pnode->next;
	delete pnode;
    }
}

template<typename T>
void List<T>::Insert( const T &data ) 
{
    ListNode<T> *pnode = new ListNode<T>( data );
    if (Last_ptr == NULL) {
        First_ptr = pnode;
    } else { 
        Last_ptr->next = pnode;
    }
    pnode->next = NULL;
    Last_ptr = pnode;
}

template<typename T>
bool List<T>::Remove( T &data )
{
    ListNode<T> *pnode;

    if( First_ptr == NULL ) return false;
    else if (First_ptr == Last_ptr) {
        Last_ptr = NULL;
    }
    pnode = First_ptr;
    First_ptr = First_ptr->next;
    data = pnode->Get_data();
    delete pnode;
    return true;
}

template<typename T>
ostream& List<T>::Print(ostream& out) const
{
    ListNode<T> *pnode = First_ptr;

    if (pnode == NULL) { out << "None." << endl; }

    while( pnode != NULL )
    {
    out << pnode->Get_data() << endl;
    pnode = pnode->next;
    }

    return out;
}

template <typename T>
ostream& operator<<(ostream& out, List<T> &l) { l.Print(out); return out; }
