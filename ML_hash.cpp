
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

int ML_hash( int level, int key )
{
	unsigned long h, a, b, c;

	int prime[11] = {0, 17, 19, 23, 27, 31, 37, 41, 43, 47, 53 };

	int range = 5;

	if( level < 1 || level > 8 )
	{
		cout << endl << "Hash: " << level 
                     << " is not a valid hash level - should be 1..8" << endl;

		exit( -1 );
	}
	a = prime[level];
	b = prime[level+1];
	c = prime[level+2];
	h = (a*a*key+b*b*key+c*key)%100001;
	h = (h%range)+1;

	return h;
}
