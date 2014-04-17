#ifndef INC_ML_HASH
#define INC_ML_HASH

/* A simple multi-level hash for up to 8 levels */

/* Good results are limited to keys in the range 1..100000 */
/* returned hash value is in the range 1..5 */

int ML_hash( int level, int key );

#endif /* INC_ML_HASH */
