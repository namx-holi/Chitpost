
#define MAX_LINE_LENGTH 512
#define DEBUG 0


struct dictionary
{
	char name[32];
	int word_count;
	char **words;
};
typedef struct dictionary Dictionary;


Dictionary
create_dict_from_file(char *directory, char *filename)
{
	int lines_allocated = 4;
	int max_line_len = MAX_LINE_LENGTH;

	/* Allocate space for words */

	char **words = (char **)malloc(sizeof(char*)*lines_allocated);
	
	if (words == NULL)
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

			words = (char **)realloc(words, sizeof(char*)*new_size);
			if (words == NULL)
			{
				fprintf(stderr, "Out of memory.\n");
				exit(3);
			}

			lines_allocated = new_size;
		}

		/* Allocate space for next line */
		words[i] = malloc(sizeof(char*)*max_line_len);
		if (words[i] == NULL)
		{
			fprintf(stderr, "Out of memory (3).\n");
			exit(4);
		}

		if (fgets(words[i], max_line_len-1, fp) == NULL)
		{
			break;
		}

		/* Get rid of CR or LF at end of line */
		for (j=strlen(words[i])-1;
			j>=0 && (words[i][j]=='\n' ||
				words[i][j]=='\r');
			j--)
			;
		words[i][j+1]='\0';
	}

	/* Close file */
	fclose(fp);

	lines_allocated = i;

	char *name = basename(filename);
	strip_extension(name);

	Dictionary dictionary;

	strcpy(dictionary.name, name);
	dictionary.word_count = lines_allocated;
	dictionary.words = words;

	free(fullpath);

	return dictionary;
}


void
populate_dictionaries(Dictionary *dictionaries, char *directory)
{
	DIR *d;
	struct dirent *dir;

	d = opendir(directory);

	#if DEBUG
		/**/
		int count = 0;
		/**/
	#endif

	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (*dir->d_name != '.')
			{
				#if DEBUG
					/**/
					count++;
					printf("File number %d\n", count);

					printf("Attempting to create dict from %s\n", dir->d_name);
					/**/
				#endif

				/*Dictionary dictionary = create_dict_from_file(directory, dir->d_name);*/
				Dictionary dictionary = create_dict_from_file(directory, dir->d_name);
				dictionaries[0] = dictionary;

				#if DEBUG
					/**/
					printf("Created dict from %s\n\n", dir->d_name);
					/**/
				#endif
			}

		}
	}

	closedir(d);
}