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
                i = (int)strlen(filename);
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

void sort_matches(char **matches)
{
    int i;
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
}

int main()
{
    DIR *dir;
    struct dirent *dr;
    char **matches;
    int count = 0;
    int i = 0;
    
    // Count matching files
    dir = opendir(".");
    if (!dir)
        return 1;
    
    dr = readdir(dir);
    while (dr != NULL)
    {
        if (process_directory_entry(dr, "*"))
            count++;
        dr = readdir(dir);
    }
    closedir(dir);
    
    // Allocate and collect matches
    matches = malloc(sizeof(char *) * (count + 1));
    if (!matches)
        return 1;
    
    dir = opendir(".");
    if (!dir)
        return 1;
    
    i = 0;
    dr = readdir(dir);
    while (dr != NULL)
    {
        if (process_directory_entry(dr, "*"))
        {
            matches[i] = strdup(dr->d_name);
            if (!matches[i])
                return 1;
            i++;
        }
        dr = readdir(dir);
    }
    closedir(dir);
    matches[i] = NULL;
    
    // Sort matches
    sort_matches(matches);
    
    // Print sorted matches
    printf("Sorted files matching '*':\n");
    i = 0;
    while (matches[i])
    {
        printf("'%s'\n", matches[i]);
        free(matches[i]);
        i++;
    }
    free(matches);
    return 0;
}
