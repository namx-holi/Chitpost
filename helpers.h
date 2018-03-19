

void
strip_extension(char *filename)
{
	char *end = filename + strlen(filename);

	while (end > filename && *end != '.' && *end != '\\' && *end != '/')
	{
		--end;
	}

	if (end > filename)
	{
		*end = '\0';
	}
}


char *
replace_in_string(char *str, char *replace_str, char *with_str)
{
	static char temp[4096];
	static char buffer[4096];
	char *p;

	strcpy(temp, str);

	/* Is replace_str even in temp? */
	if (!(p = strstr(temp, replace_str)))
	{
		return temp;
	}

	/* Copy characters from temp start to replace_str */
	strncpy(buffer, temp, p-temp);
	buffer[p-temp] = '\0';

	sprintf(buffer + (p - temp), "%s%s", with_str, p+strlen(replace_str));
	sprintf(str, "%s", buffer);

	return str;
}


int
rand_int(int max_num)
{
	/*
	Generates random int x that fits
	0 <= x < max_num
	*/

	unsigned int
		num_bins = (unsigned int) max_num,
		num_rand = (unsigned int) RAND_MAX,
		bin_size = num_rand / num_bins,
		defect   = num_rand % num_bins;

	int x;

	do {
		x = rand();
	} while (num_rand - defect <= (unsigned int)x);

	return x/bin_size;
}