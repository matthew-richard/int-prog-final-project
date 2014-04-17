
/* 
 * Simple hash use
 */

#include "ML_hash.h"

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

int main()
{
	int i, j, level, h;
        int total_dup, max_dup, current_dup;

	int results[100001];

	total_dup = 0;
	max_dup = 0;

	for( i=1; i <= 100000; i++ )
	{
		results[i] = 0;
		cout << "[" << setw(6) << i << "] : ";
		for( level = 1; level <= 8; level++ )
		{
			h = ML_hash( level, i );
			results[i] = results[i]*10 + h;
			cout << h << " ";
		}
		cout << " result " << results[i] << endl;
	}

	cout << "checking for duplicates" << endl;
	for( i=1; i <= 100000; i++ )
	{
	   current_dup = 0;
	   for( j=0; j < i; j++ )
	   {
		if( results[i] == results[j] ) 
		{
			total_dup++;
			current_dup++;
		}
           }
	   if( current_dup > max_dup ) max_dup = current_dup;
	}
		   
	cout << "End with " << total_dup << " duplicates, maximum duplicates is " 
	     << max_dup << endl;
	
}

