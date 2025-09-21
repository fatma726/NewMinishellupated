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

int main()
{
    DIR *dir;
    struct dirent *dr;
    
    dir = opendir(".");
    if (!dir)
        return 1;
    
    printf("Files matching '*':\n");
    dr = readdir(dir);
    while (dr != NULL)
    {
        if (process_directory_entry(dr, "*"))
        {
            printf("'%s'\n", dr->d_name);
        }
        dr = readdir(dir);
    }
    closedir(dir);
    return 0;
}
