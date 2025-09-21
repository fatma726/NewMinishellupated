#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

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
                break;
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

int process_directory_entry(struct dirent *dr, char *pattern)
{
    if (dr->d_name[0] == '.' && pattern[0] != '.')
        return 0;
    return matches_pattern(dr->d_name, pattern);
}

int main()
{
    DIR *dir;
    struct dirent *dr;
    char *pattern = "*";
    int count = 0;
    char **matches;
    int i = 0;
    
    // Count matching files first
    dir = opendir(".");
    if (!dir)
    {
        printf("Failed to open directory\n");
        return 1;
    }
    
    dr = readdir(dir);
    while (dr != NULL)
    {
        if (process_directory_entry(dr, pattern))
            count++;
        dr = readdir(dir);
    }
    closedir(dir);
    
    printf("Count of matching files: %d\n", count);
    
    // Allocate and collect matches
    matches = malloc(sizeof(char *) * (count + 1));
    if (!matches)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    dir = opendir(".");
    if (!dir)
    {
        printf("Failed to open directory\n");
        free(matches);
        return 1;
    }
    
    dr = readdir(dir);
    while (dr != NULL)
    {
        if (process_directory_entry(dr, pattern))
        {
            matches[i] = strdup(dr->d_name);
            if (!matches[i])
            {
                printf("String duplication failed\n");
                closedir(dir);
                free(matches);
                return 1;
            }
            i++;
        }
        dr = readdir(dir);
    }
    matches[i] = NULL;
    closedir(dir);
    
    printf("Collected matches (before sorting):\n");
    i = 0;
    while (matches[i])
    {
        printf("  [%d] '%s'\n", i, matches[i]);
        i++;
    }
    
    // Sort matches
    int j;
    char *temp;
    i = 0;
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
    
    printf("\nCollected matches (after sorting):\n");
    i = 0;
    while (matches[i])
    {
        printf("  [%d] '%s'\n", i, matches[i]);
        i++;
    }
    
    // Clean up
    i = 0;
    while (matches[i])
    {
        free(matches[i]);
        i++;
    }
    free(matches);
    
    return 0;
}
