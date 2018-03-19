

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
