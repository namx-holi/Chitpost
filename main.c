
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <dirent.h>
#include <time.h>

#include "helpers.h"
#include "dictionary.h"
#include "cleanup.h"
#include "Test_Files/tests.h"


#define LOG_MAIN 0

#define RUN_TESTS 0
#define RUN 1

#define USE_SEED 0
#define SEED 123456


void init_random(void);
void init_random_with_seed(int seed);


int
main(int argc, char const *argv[])
{
	#if USE_SEED
	init_random_with_seed(SEED);
	#else
	init_random();
	#endif

	#if RUN_TESTS
	run_tests();
	#endif

	#if RUN
		/**/

		DictionaryCollection dictionary_collection;
		populate_dictionaries(&dictionary_collection, "Words/");

		#if LOG_MAIN
			/**/
			list_dictionaries(dictionary_collection);
			/**/
		#endif

		char str_post_count[2];
		int post_count = 1;

		switch(argc)
		{
			case 1:
				post_count = 1;
				break;

			case 2:
				if (strlen(argv[1]) > 2)
				{
					fprintf(stderr, "Max post count is 99.\n");
					exit(1);
				}

				strncpy(str_post_count, argv[1], 2);
				post_count = atoi(str_post_count);
				break;

			default:
				fprintf(stderr, "Too many arguments.\n");
				exit(2);
		}

		char *sentence;
		if (post_count > 1)
		{
			int i;
			for (i = 0; i < post_count; ++i)
			{
				sentence = generate_sentence(dictionary_collection);
				printf("%d) %s\n", i+1, sentence);
			}
		}
		else
		{
			sentence = generate_sentence(dictionary_collection);
			printf("%s\n", sentence);
		}

		/* Free memory from dictionary_collection */
		free_dictionary_collection(&dictionary_collection);

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