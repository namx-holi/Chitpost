
#define MAX_LINE_LENGTH 512
#define LOG_DICTIONARY 0


struct dictionary
{
	char name[32];
	int word_count;
	char **words;
};
typedef struct dictionary Dictionary;

struct dictionary_collection
{
	int dictionary_count;
	Dictionary *dictionaries;
};
typedef struct dictionary_collection DictionaryCollection;


void
list_words(Dictionary dictionary)
{
	printf("  In dictionary %s:\n", dictionary.name);

	int i;
	for(i = 0; i < dictionary.word_count; ++i)
	{
		printf("    Line %d: %s\n", i+1, dictionary.words[i]);
	}
}


void
list_dictionaries(DictionaryCollection dc)
{
	printf("  In dictionary collection:\n");

	int i;
	for (i = 0; i < dc.dictionary_count; ++i)
	{
		printf("    Dictionary %d: %s\n", i+1, dc.dictionaries[i].name);
	}
}


void
populate_dict_from_file(Dictionary *d, char *directory, char *filename)
{
	int lines_allocated = 4;
	int max_line_len = MAX_LINE_LENGTH;

	/* Allocate space for words */

	d->words = (char **)malloc(sizeof(char*)*lines_allocated);
	if (d->words == NULL)
	{
		fprintf(stderr, "Out of memory (1).\n");
		exit(1);
	}

	/* Allocate space for fullpath and copy the path into it */
	char *fullpath = malloc(strlen(directory) + strlen(filename) + 1);
	strcpy(fullpath, directory);
	strcat(fullpath, filename);

	/* Open the file */
	FILE *fp = fopen(fullpath, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error opening file.\n");
		exit(2);
	}

	int i;
	for (i = 0; 1; i++)
	{
		int j;

		/* Have we gone over our line allocation? */
		if (i >= lines_allocated)
		{
			int new_size;

			/* Double our allocation and re-allocate */
			new_size = lines_allocated*2;

			d->words = (char **)realloc(d->words, sizeof(char*)*new_size);
			if (d->words == NULL)
			{
				fprintf(stderr, "Out of memory.\n");
				exit(3);
			}

			lines_allocated = new_size;
		}

		/* Allocate space for next line */
		d->words[i] = malloc(sizeof(char*)*max_line_len);
		if (d->words[i] == NULL)
		{
			fprintf(stderr, "Out of memory (3).\n");
			exit(4);
		}

		if (fgets(d->words[i], max_line_len-1, fp) == NULL)
		{
			break;
		}

		/* Get rid of CR or LF at end of line */
		for (j=strlen(d->words[i])-1;
			j>=0 && (d->words[i][j]=='\n' ||
				d->words[i][j]=='\r');
			j--)
			;
		d->words[i][j+1]='\0';
	}

	/* Close file */
	fclose(fp);

	lines_allocated = i;

	char *name = basename(filename);
	strip_extension(name);

	strcpy(d->name, name);
	d->word_count = lines_allocated;

	free(fullpath);
}


void
populate_dictionaries(DictionaryCollection *dc, char *directory)
{
	DIR *d;
	struct dirent *dir;

	d = opendir(directory);

	int opened_file_count = 0;

	dc->dictionaries = (Dictionary *)malloc(sizeof(Dictionary)*0);
	if (dc->dictionaries == NULL)
	{
		fprintf(stderr, "Out of memory (1).\n");
		exit(1);
	}

	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (*dir->d_name != '.')
			{
				++opened_file_count;

				#if LOG_DICTIONARY
					/**/
					printf("File number %d\n", opened_file_count);
					printf("Attempting to create dict from %s\n", dir->d_name);
					/**/
				#endif

				Dictionary dictionary;
				populate_dict_from_file(&dictionary, directory, dir->d_name);
				
				/* Make sure size of dc is appropriate */
				dc->dictionaries = (Dictionary *)realloc(dc->dictionaries, sizeof(Dictionary)*opened_file_count);
				if (dc->dictionaries == NULL)
				{
					fprintf(stderr, "Out of memory.\n");
					exit(3);
				}

				dc->dictionaries[opened_file_count-1] = dictionary;

				#if LOG_DICTIONARY
					/**/
					printf("Created dict from %s\n\n", dir->d_name);
					/**/
				#endif
			}
		}
	}

	dc->dictionary_count = opened_file_count;
	closedir(d);
}


char *
pick_word_from_dictionary(Dictionary dictionary)
{
	int index = rand_int(dictionary.word_count);

	return dictionary.words[index];
}


Dictionary
find_dict(DictionaryCollection dc, char *dict_name)
{
	int i;
	for (i = 0; i < dc.dictionary_count; ++i)
	{
		if (strcmp(dc.dictionaries[i].name, dict_name) == 0)
		{
			return dc.dictionaries[i];
		}
	}
	return dc.dictionaries[0];
}


int
replace_next_placeholder(DictionaryCollection dc, char **sentence)
{
	static char temp[4096];
	static char replace_str[4096];
	static char dict_name[4096];

	char *placeholder_start;
	char *placeholder_end;

	strcpy(temp, *sentence);

	/* Look for mem loc of opening % */
	if (!(placeholder_start = strstr(temp, "%")))
	{
		return 0;
	}

	/* Look for mem loc of closing % */
	if (!(placeholder_end = strstr(placeholder_start+1, "%")))
	{
		return 0;
	}

	/* copy the string we are replacing into replace_str */
	strncpy(replace_str, placeholder_start, 1+placeholder_end-placeholder_start);
	replace_str[1+placeholder_end-placeholder_start] = '\0';

	if (strcmp(replace_str, "%nul%") == 0)
	{
		replace_in_string(sentence, replace_str, "");
		#if LOG_DICTIONARY
			/**/
			printf("[LOG_DICTIONARY] Sentence is now: %s\n", *sentence);
			/**/
		#endif

		return 1;
	}

	/* copy the name of the dictionary to open into dict_name */
	strncpy(dict_name, placeholder_start+1, placeholder_end-placeholder_start-1);
	dict_name[placeholder_end-placeholder_start-1] = '\0';

	/* pick a word from dictionary named */
	char *with_str;
	with_str = pick_word_from_dictionary(find_dict(dc, dict_name));

	replace_in_string(sentence, replace_str, with_str);
	#if LOG_DICTIONARY
		/**/
		printf("[LOG_DICTIONARY] Sentence is now: %s\n", *sentence);
		/**/
	#endif

	return 1;
}


char *
generate_sentence(DictionaryCollection dc)
{
	/* Base sentence is always from base.txt */
	char *sentence;
	sentence = pick_word_from_dictionary(find_dict(dc, "base"));

	int replaced = 1;

	int count = 0;
	while (replaced == 1)
	{
		replaced = replace_next_placeholder(dc, &sentence);
		count++;

		if (count > 1000)
		{
			printf("too many\n");
			return sentence;
		}
	}

	replace_all(&sentence, "||", " ");
	replace_all(&sentence, "|", "");

	return sentence;
}