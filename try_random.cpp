
/* 
 * Checking random operation
 */

#include "random_op.h"

#include <iostream>
using std::cout;
using std::endl;

int main()
{

    Random_operation  Rand_op;

    for( int i=1; i <= 10; i++ )
    {
    	Rand_op.Randomize_next_op();

    	cout << "Random operation is: " << Rand_op.Get_op() << " and key is: " 
                                   	<< Rand_op.Get_key() << endl;
    }

    cout << endl;

    Rand_op.Set_seed(2);
    for( int i=1; i <= 10; i++ )
    {
    	Rand_op.Randomize_next_op();

    	cout << "Random operation is: " << Rand_op.Get_op() << " and key is: " 
                                   	<< Rand_op.Get_key() << endl;
    }

    cout << endl;

    Rand_op.Set_seed(1);
    for( int i=1; i <= 10; i++ )
    {
    	Rand_op.Randomize_next_op();

    	cout << "Random operation is: " << Rand_op.Get_op() << " and key is: " 
                                   	<< Rand_op.Get_key() << endl;
    }

    cout << endl;

    Random_operation  Rand_op2( 1, 1000);
    for( int i=1; i <= 10; i++ )
    {
    	Rand_op2.Randomize_next_op();

    	cout << "Random operation is: " << Rand_op2.Get_op() << " and key is: " 
                                   	<< Rand_op2.Get_key() << endl;
    }

    cout << endl;

    Random_operation  Rand_op3( 2 );
    for( int i=1; i <= 10; i++ )
    {
    	Rand_op3.Randomize_next_op();

    	cout << "Random operation is: " << Rand_op3.Get_op() << " and key is: " 
                                   	<< Rand_op3.Get_key() << endl;
    }
}

