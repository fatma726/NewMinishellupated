#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Copy of the matches_pattern function from minishell
int matches_pattern(char *filename, char *pattern)
{
    int i = 0;
    int j = 0;
    
    while (pattern[j] && filename[i])
    {
        if (pattern[j] == '*')
        {
            j++;
            if (!pattern[j])
            {
                i = strlen(filename);
                return 1;
            }
            while (filename[i])
            {
                if (matches_pattern(filename + i, pattern + j))
                    return 1;
                i++;
            }
            return 0;
        }
        else if (pattern[j] == '?' || pattern[j] == filename[i])
        {
            i++;
            j++;
        }
        else
            return 0;
    }
    while (pattern[j] == '*')
        j++;
    return (!pattern[j] && !filename[i]);
}

int main()
{
    char *test_files[] = {
        "\"",
        "\"'",
        "'",
        "'\"",
        "README.md",
        "test.txt",
        NULL
    };
    
    printf("Testing pattern matching for '*':\n");
    
    for (int i = 0; test_files[i]; i++)
    {
        int result = matches_pattern(test_files[i], "*");
        printf("  '%s' -> %s\n", test_files[i], result ? "MATCH" : "NO MATCH");
    }
    
    return 0;
}
