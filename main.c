
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

		/* The dictionary array size needs to be dynamic */
		Dictionary dictionaries[10];
		populate_dictionaries(dictionaries, "Words/");

		list_words(dictionaries[0]);
		/**/
	#endif

	return 0;
}