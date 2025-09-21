#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

// Simplified version of the load_lst_loop function
char **debug_load_lst_loop(DIR *dir, bool hidden)
{
    struct dirent *dr;
    char **files;
    int count = 0;
    int i = 0;
    
    // First pass: count files
    rewinddir(dir);
    dr = readdir(dir);
    while (dr != NULL)
    {
        if (!hidden && dr->d_name[0] != '.')
            count++;
        if (hidden && dr->d_name[0] == '.' && strcmp(dr->d_name, ".") && strcmp(dr->d_name, ".."))
            count++;
        dr = readdir(dir);
    }
    
    printf("Count of files to include: %d\n", count);
    
    // Allocate array
    files = malloc(sizeof(char *) * (count + 1));
    if (!files)
        return NULL;
    
    // Second pass: collect files
    rewinddir(dir);
    dr = readdir(dir);
    while (dr != NULL)
    {
        if (!hidden && dr->d_name[0] != '.')
        {
            files[i] = strdup(dr->d_name);
            printf("  [%d] Added: '%s'\n", i, dr->d_name);
            i++;
        }
        if (hidden && dr->d_name[0] == '.' && strcmp(dr->d_name, ".") && strcmp(dr->d_name, ".."))
        {
            files[i] = strdup(dr->d_name);
            printf("  [%d] Added (hidden): '%s'\n", i, dr->d_name);
            i++;
        }
        dr = readdir(dir);
    }
    files[i] = NULL;
    
    return files;
}

int main()
{
    DIR *dir;
    char **files;
    int i = 0;
    
    chdir("minishell_tester");
    
    printf("Testing load_lst_loop logic (hidden=false):\n");
    
    dir = opendir(".");
    if (!dir)
    {
        printf("Failed to open directory\n");
        return 1;
    }
    
    files = debug_load_lst_loop(dir, false);
    
    printf("\nFinal file list:\n");
    while (files[i])
    {
        printf("  [%d] '%s'\n", i, files[i]);
        free(files[i]);
        i++;
    }
    free(files);
    
    closedir(dir);
    
    return 0;
}
