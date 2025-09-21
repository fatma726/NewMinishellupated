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

// Copy of count_matching_files from minishell
int count_matching_files(char *pattern)
{
    DIR *dir;
    struct dirent *dr;
    int count = 0;
    
    dir = opendir(".");
    if (!dir)
        return 0;
    
    dr = readdir(dir);
    while (dr != NULL)
    {
        if (process_directory_entry(dr, pattern))
        {
            printf("  [%d] Counting: '%s'\n", count, dr->d_name);
            count++;
        }
        dr = readdir(dir);
    }
    closedir(dir);
    return count;
}

int main()
{
    int count;
    
    chdir("minishell_tester");
    
    printf("Testing count_matching_files for pattern '*':\n");
    
    count = count_matching_files("*");
    
    printf("\nTotal count: %d\n", count);
    
    return 0;
}
