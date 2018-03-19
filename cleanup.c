

#define LOG_CLEANUP 0


void
free_dictionary(Dictionary *d)
{
	#if LOG_CLEANUP
		/**/
		printf("  Cleaning up dictionary %s\n", d->name);
		/**/
	#endif

	int i;
	for (i = 0; i < d->word_count; ++i)
	{
		free(d->words[i]);
	}
	#if LOG_CLEANUP
		/**/
		printf("    Freed %d values in words\n", i);
		/**/
	#endif


	free(d->words);
	#if LOG_CLEANUP
		/**/
		printf("    Freed words\n");
		printf("\n");
		/**/
	#endif
}


void
free_dictionary_collection(DictionaryCollection *dc)
{
	#if LOG_CLEANUP
		/**/
		printf("Cleaning up dictionary collection\n");
		/**/
	#endif

	int i;
	for (i = 0; i < dc->dictionary_count; ++i)
	{

		free_dictionary(&dc->dictionaries[i]);
	}

	free(dc->dictionaries);
	#if LOG_CLEANUP
		/**/
		printf("  Freed dictionaries\n");
		/**/
	#endif
}