#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Copy of process_directory_entry from minishell
int process_directory_entry(struct dirent *dr, char *pattern)
{
    if (dr->d_name[0] == '.' && pattern[0] != '.')
        return 0;
    return matches_pattern(dr->d_name, pattern);
}

// Copy of collect_matches from minishell
int collect_matches(char **matches, char *pattern)
{
    DIR *dir;
    struct dirent *dr;
    int i = 0;
    
    dir = opendir(".");
    if (!dir)
        return 0;
    
    dr = readdir(dir);
    while (dr != NULL)
    {
        if (process_directory_entry(dr, pattern))
        {
            matches[i] = strdup(dr->d_name);
            printf("  [%d] Collected: '%s'\n", i, dr->d_name);
            i++;
        }
        dr = readdir(dir);
    }
    matches[i] = NULL;
    
    closedir(dir);
    return 1;
}

int main()
{
    char **matches;
    int count = 0;
    int i = 0;
    
    chdir("minishell_tester");
    
    printf("Testing collect_matches for pattern '*':\n");
    
    // Count matching files first
    DIR *dir = opendir(".");
    struct dirent *dr = readdir(dir);
    while (dr != NULL)
    {
        if (process_directory_entry(dr, "*"))
            count++;
        dr = readdir(dir);
    }
    closedir(dir);
    
    printf("Count of matching files: %d\n", count);
    
    // Allocate and collect matches
    matches = malloc(sizeof(char *) * (count + 1));
    if (!matches)
    {
        printf("Failed to allocate memory\n");
        return 1;
    }
    
    collect_matches(matches, "*");
    
    printf("\nFinal collected matches:\n");
    while (matches[i])
    {
        printf("  [%d] '%s'\n", i, matches[i]);
        free(matches[i]);
        i++;
    }
    free(matches);
    
    return 0;
}
