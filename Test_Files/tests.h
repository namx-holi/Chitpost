
#define WORDS_DIRECTORY "/home/namu/Documents/C/Chitpost2/Words"
#define TEST_DIRECTORY "/home/namu/Documents/C/Chitpost2/Test_Files/"

/* test stripping .txt and other extensions from filenames */
void test_strip_extension(void);
#define RUN_TEST_STRIP_EXTENSION 0

/* test reading a directory for a list of files */
void test_read_directory_tree(void);
#define RUN_TEST_READ_DIRECTORY_TREE 0

/* test creating dictionaries from a file */
void test_create_dict_from_file(void);
#define RUN_TEST_CREATE_DICT_FROM_FILE 0

/* test for replacing strings of characters in a string */
void test_replace_in_string(void);
#define RUN_TEST_REPLACE_IN_STRING 1


void
run_tests(void)
{
	#if RUN_TEST_STRIP_EXTENSION
	test_strip_extension();
	#endif

	#if RUN_TEST_READ_DIRECTORY_TREE
	test_create_dict_from_file();
	#endif

	#if RUN_TEST_CREATE_DICT_FROM_FILE
	test_read_directory_tree();
	#endif

	#if RUN_TEST_REPLACE_IN_STRING
	test_replace_in_string();
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
test_create_dict_from_file(void)
{
	printf("Testing create_dict_from_file\n");

	char directory[] = TEST_DIRECTORY;
	char filename[] = "test_file.txt";
	printf("  Directory is %s\n", directory);
	printf("  Filename is %s\n", filename);

	Dictionary dictionary = create_dict_from_file(directory, filename);
	printf("  Dictionary name is %s\n", dictionary.name);
	printf("  Word count is %d\n", dictionary.word_count);

	list_words(dictionary);

	printf("\n");
}


void
test_replace_in_string(void)
{
	printf("Testing replace_in_string\n");

	char original_string[] = "Hello, World!";
	char string_to_replace[] = "llo";
	char replacing_string_with[] = "nlon";
	printf("  Original string: %s\n", original_string);
	printf("  Replacing: %s\n", string_to_replace);
	printf("  With: %s\n", replacing_string_with);

	char *new_string = replace_in_string(original_string, string_to_replace, replacing_string_with);
	printf("  New string: %s\n", new_string);

	printf("\n");
}