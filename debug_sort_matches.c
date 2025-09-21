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
            i++;
        }
        dr = readdir(dir);
    }
    matches[i] = NULL;
    
    closedir(dir);
    return 1;
}

// Copy of sort_matches from minishell
void sort_matches(char **matches)
{
    int i = 0;
    char *temp;
    
    while (matches[i + 1])
    {
        if (strncmp(matches[i], matches[i + 1], 1000) > 0)
        {
            temp = matches[i];
            matches[i] = matches[i + 1];
            matches[i + 1] = temp;
            i = 0;
        }
        else
            i++;
    }
}

// Copy of add_sorted_matches from minishell
int add_sorted_matches(char **newargs, int *j, char **matches)
{
    int i = 0;
    
    while (matches[i])
    {
        newargs[*j] = strdup(matches[i]);
        if (!newargs[*j])
        {
            while (matches[i])
                free(matches[i++]);
            free(matches);
            return 0;
        }
        printf("  [%d] Added to newargs: '%s'\n", *j, newargs[*j]);
        (*j)++;
        free(matches[i]);
        i++;
    }
    return 1;
}

int main()
{
    char **matches;
    char **newargs;
    int count = 0;
    int i = 0;
    int j = 0;
    
    chdir("minishell_tester");
    
    printf("Testing full wildcard expansion process:\n");
    
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
    
    printf("\nBefore sorting:\n");
    i = 0;
    while (matches[i])
    {
        printf("  [%d] '%s'\n", i, matches[i]);
        i++;
    }
    
    sort_matches(matches);
    
    printf("\nAfter sorting:\n");
    i = 0;
    while (matches[i])
    {
        printf("  [%d] '%s'\n", i, matches[i]);
        i++;
    }
    
    // Allocate newargs and add sorted matches
    newargs = malloc(sizeof(char *) * (count + 1));
    if (!newargs)
    {
        printf("Failed to allocate newargs\n");
        return 1;
    }
    
    printf("\nAdding to newargs:\n");
    add_sorted_matches(newargs, &j, matches);
    newargs[j] = NULL;
    
    printf("\nFinal newargs:\n");
    i = 0;
    while (newargs[i])
    {
        printf("  [%d] '%s'\n", i, newargs[i]);
        free(newargs[i]);
        i++;
    }
    free(newargs);
    free(matches);
    
    return 0;
}
