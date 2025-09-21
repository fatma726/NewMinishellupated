#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// Simple pattern matching function (simplified version)
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
    
    chdir("minishell_tester");
    
    printf("Testing wildcard expansion for pattern '*':\n");
    printf("Files in current directory:\n");
    system("ls -la");
    printf("\nMatching files:\n");
    
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
                printf("  MATCH: '%s'\n", dr->d_name);
            }
        }
        dr = readdir(dir);
    }
    closedir(dir);
    
    return 0;
}