
#define WORDS_DIRECTORY "./Words"
#define TEST_DIRECTORY "./Test_Files/"

/* test stripping .txt and other extensions from filenames */
void test_strip_extension(void);
#define RUN_TEST_STRIP_EXTENSION 0

/* test reading a directory for a list of files */
void test_read_directory_tree(void);
#define RUN_TEST_READ_DIRECTORY_TREE 0

/* test creating dictionaries from a file */
void test_populate_dict_from_file(void);
#define RUN_TEST_POPULATE_DICT_FROM_FILE 0

/* test for replacing strings of characters in a string */
void test_replace_in_string(void);
#define RUN_TEST_REPLACE_IN_STRING 0

/* test the generation of random numbers */
void test_pick_word_from_dictionary(void);
#define TEST_PICK_WORD_FROM_DICTIONARY 0

/* test replacing placeholders in a sentence */
void test_replace_next_placeholder(void);
#define TEST_REPLACE_NEXT_PLACEHOLDER 1

/* test generating a sentence from scratch */
void test_generate_sentence(void);
#define TEST_GENERATE_SENTENCE 1


void
run_tests(void)
{
	#if RUN_TEST_STRIP_EXTENSION
	test_strip_extension();
	#endif

	#if RUN_TEST_READ_DIRECTORY_TREE
	test_read_directory_tree();
	#endif

	#if RUN_TEST_POPULATE_DICT_FROM_FILE
	test_populate_dict_from_file();
	#endif

	#if RUN_TEST_REPLACE_IN_STRING
	test_replace_in_string();
	#endif

	#if TEST_PICK_WORD_FROM_DICTIONARY
	test_pick_word_from_dictionary();
	#endif

	#if TEST_REPLACE_NEXT_PLACEHOLDER
	test_replace_next_placeholder();
	#endif

	#if TEST_GENERATE_SENTENCE
	test_generate_sentence();
	#endif
}


void
test_strip_extension(void)
{
	printf("Testing strip_extension\n");

	char filename[] = "example.exe";
	printf("  Filename is %s\n", filename);

	strip_extension(filename);
	printf("  Filename after strip is %s\n", filename);

	printf("\n");
}


void
test_read_directory_tree(void)
{
	printf("Testing reading directories\n");

	
	char directory[] = WORDS_DIRECTORY;
	printf("  Directory is %s\n", directory);

	DIR *d;
	struct dirent *dir;

	d = opendir(directory);

	if (d)
	{
		printf("  Files in directory:\n");
		while ((dir = readdir(d)) != NULL)
		{
			if (*dir->d_name != '.')
			{
				printf("    %s\n", dir->d_name);
			}
		}
		closedir(d);
		printf("\n");
	}

	printf("\n");
}


void
test_populate_dict_from_file(void)
{
	printf("Testing populate_dict_from_file\n");

	char directory[] = TEST_DIRECTORY;
	char filename[] = "test_file.txt";
	printf("  Directory is %s\n", directory);
	printf("  Filename is %s\n", filename);

	Dictionary dictionary;
	populate_dict_from_file(&dictionary, directory, filename);
	printf("  Dictionary name is %s\n", dictionary.name);
	printf("  Word count is %d\n", dictionary.word_count);

	list_words(dictionary);

	printf("\n");
}


void
test_replace_in_string(void)
{
	printf("Testing replace_in_string\n");

	char *original_string = "Hello, World!";
	char *string_to_replace = "llo";
	char *replacing_string_with = "nlon";
	printf("  Original string: %s\n", original_string);
	printf("  Replacing: %s\n", string_to_replace);
	printf("  With: %s\n", replacing_string_with);

	replace_in_string(&original_string, string_to_replace, replacing_string_with);
	printf("  New string: %s\n", original_string);

	printf("\n");
}


void
test_pick_word_from_dictionary(void)
{
	printf("Testing pick_word_from_dictionary\n");

	printf("  Creating dict from test_file.txt\n");
	char directory[] = TEST_DIRECTORY;
	char filename[] = "test_file.txt";
	Dictionary dictionary;
	populate_dict_from_file(&dictionary, directory, filename);

	printf("  Picking 10 random lines:\n");
	char *result;

	int i;
	for (i = 0; i < 10; ++i)
	{
		result = pick_word_from_dictionary(dictionary);
		printf("    Result %d: %s\n", i+1, result);
	}

	printf("\n");
}


void
test_replace_next_placeholder(void)
{
	printf("Testing replace_next_placeholder\n");

	printf("  Creating dict collection from Words/\n");
	DictionaryCollection dictionary_collection;
	populate_dictionaries(&dictionary_collection, "Words/");

	printf("  Setting test string to replace from\n");
	char *sentence = "Hello, %sentence% is the line picked.";
	printf("  Sentence is currently: %s\n", sentence);

	replace_next_placeholder(dictionary_collection, &sentence);
	printf("  Sentence is now: %s\n", sentence);

	/* Free memory from dictionary_collection */
	free_dictionary_collection(&dictionary_collection);

	printf("\n");
}


void
test_generate_sentence(void)
{
	printf("Testing generate_sentence\n");

	printf("  Creating dict collection from Words/\n");
	DictionaryCollection dictionary_collection;
	populate_dictionaries(&dictionary_collection, "Words/");

	printf("  Generating sentence\n");
	char *sentence = generate_sentence(dictionary_collection);
	printf("  Sentence is: %s\n", sentence);

	printf("\n");
}