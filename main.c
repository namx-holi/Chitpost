
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <libgen.h>
#include <dirent.h>

#include "helpers.h"
#include "dictionary.h"
#include "Test_Files/tests.h"


#define RUN_TESTS 0
#define RUN 1


int
main(void)
{
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