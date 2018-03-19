
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <dirent.h>
#include <time.h>

#include "helpers.h"
#include "dictionary.h"
#include "Test_Files/tests.h"


#define RUN_TESTS 1
#define RUN 0


void init_random(void);
void init_random_with_seed(int seed);



int
main(void)
{
	init_random();

	#if RUN_TESTS
	run_tests();
	#endif

	#if RUN
		/**/

		DictionaryCollection dictionary_collection;
		populate_dictionaries(&dictionary_collection, "Words/");

		list_dictionaries(dictionary_collection);
		/**/
	#endif

	return 0;
}


void
init_random(void)
{
	/* Init random with time as the seed */
	srand(time(NULL));
}


void
init_random_with_seed(int seed)
{
	/* Init random with seed */
	srand(seed);
}