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

int main()
{
    DIR *dir;
    struct dirent *dr;
    int count = 0;
    
    chdir("minishell_tester");
    
    printf("Testing specific files with quotes:\n");
    
    dir = opendir(".");
    if (!dir)
    {
        printf("Failed to open directory\n");
        return 1;
    }
    
    dr = readdir(dir);
    while (dr != NULL)
    {
        if (dr->d_name[0] != '.')  // Skip hidden files
        {
            if (matches_pattern(dr->d_name, "*"))
            {
                printf("  [%d] '%s' (len=%zu)\n", count, dr->d_name, strlen(dr->d_name));
                
                // Check for specific problematic files
                if (strcmp(dr->d_name, "\"") == 0)
                    printf("    -> This is the double quote file\n");
                else if (strcmp(dr->d_name, "'") == 0)
                    printf("    -> This is the single quote file\n");
                else if (strcmp(dr->d_name, "\"'") == 0)
                    printf("    -> This is the double-single quote file\n");
                else if (strcmp(dr->d_name, "'\"") == 0)
                    printf("    -> This is the single-double quote file\n");
                
                count++;
            }
        }
        dr = readdir(dir);
    }
    
    printf("\nTotal matching files: %d\n", count);
    
    closedir(dir);
    
    return 0;
}
