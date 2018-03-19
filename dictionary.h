
#define MAX_LINE_LENGTH 512
#define DEBUG 0


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

				#if DEBUG
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

				#if DEBUG
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