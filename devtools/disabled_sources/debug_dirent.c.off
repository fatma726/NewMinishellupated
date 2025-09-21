#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main()
{
    DIR *dir;
    struct dirent *dr;
    
    chdir("minishell_tester");
    
    printf("Testing directory reading...\n");
    
    dir = opendir(".");
    if (!dir)
    {
        printf("Failed to open directory\n");
        return 1;
    }
    
    printf("All files in directory:\n");
    dr = readdir(dir);
    while (dr != NULL)
    {
        printf("  '%s' (starts with .: %s)\n", dr->d_name, dr->d_name[0] == '.' ? "YES" : "NO");
        dr = readdir(dir);
    }
    
    closedir(dir);
    
    // Test the logic from get_file_list
    printf("\nTesting get_file_list logic (hidden=false):\n");
    dir = opendir(".");
    dr = readdir(dir);
    
    // Skip hidden files (this is the logic from get_file_list)
    while (!0 && dr && dr->d_name[0] == '.')  // hidden = false
    {
        printf("  SKIPPING: '%s'\n", dr->d_name);
        dr = readdir(dir);
    }
    
    printf("First non-hidden file: '%s'\n", dr ? dr->d_name : "NULL");
    
    closedir(dir);
    
    return 0;
}