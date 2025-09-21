#include <stdio.h>
#include <string.h>

int matches_pattern(char *filename, char *pattern);

static int	handle_wildcard(char *filename, char *pattern, int *i, int *j)
{
	(*j)++;
	if (!pattern[*j])
	{
		*i = (int)strlen(filename);
		return (1);
	}
	while (filename[*i])
	{
		if (matches_pattern(filename + *i, pattern + *j))
			return (1);
		(*i)++;
	}
	return (0);
}

static int	handle_character(char *filename, char *pattern, int *i, int *j)
{
	if (pattern[*j] == '?' || pattern[*j] == filename[*i])
	{
		(*i)++;
		(*j)++;
		return (1);
	}
	return (0);
}

int	matches_pattern(char *filename, char *pattern)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pattern[j] && filename[i])
	{
		if (pattern[j] == '*')
		{
			if (!handle_wildcard(filename, pattern, &i, &j))
				return (0);
		}
		else if (!handle_character(filename, pattern, &i, &j))
			return (0);
	}
	while (pattern[j] == '*')
		j++;
	return (!pattern[j] && !filename[i]);
}

int main()
{
    printf("Testing pattern matching:\n");
    printf("matches_pattern('README.md', '*.md'): %d\n", matches_pattern("README.md", "*.md"));
    printf("matches_pattern('test.c', '*.md'): %d\n", matches_pattern("test.c", "*.md"));
    printf("matches_pattern('builtins', 'built*'): %d\n", matches_pattern("builtins", "built*"));
    printf("matches_pattern('test', 'built*'): %d\n", matches_pattern("test", "built*"));
    return 0;
}
