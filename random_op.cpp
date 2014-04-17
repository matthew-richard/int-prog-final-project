
#include "random_op.h"
#include <cstdlib>

// constructor
Random_operation::Random_operation( unsigned int seed, int range )
{
   current_range = range;
   srand( seed );
   Randomize_next_op();
}

void Random_operation::Set_seed( unsigned int seed )
{
    srand( seed );
    Randomize_next_op();
}

void Random_operation::Randomize_next_op()
{
    int random_number;

    random_number = rand()%4;

    switch( random_number )
    {
	case 0:
        case 1:
	 	current_operation = 'G';	
		break;
        case 2:
	 	current_operation = 'D';	
		break;
        case 3:
	 	current_operation = 'I';	
    }

    random_number = rand()%current_range + 1;
    current_key = random_number;

}

char Random_operation::Get_op()
{
    return current_operation;
}

int Random_operation::Get_key()
{
    return current_key;
}
