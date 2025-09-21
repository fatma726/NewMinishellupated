#include "include/minishell.h"
#include "bonus/include/bonus.h"
#include <stdio.h>

int main()
{
    char *args[] = {"echo", "*", NULL};
    char **result;
    int i = 0;
    
    // Change to the minishell_tester directory
    chdir("minishell_tester");
    
    printf("Testing wildcard expansion...\n");
    printf("Current directory: ");
    system("pwd");
    printf("\nFiles in current directory:\n");
    system("ls -la");
    printf("\n");
    
    printf("Original args:\n");
    i = 0;
    while (args[i])
    {
        printf("  %d: '%s'\n", i, args[i]);
        i++;
    }
    
    result = expand_wildcard_if_bonus(args, NULL, NULL);
    
    printf("\nExpanded args:\n");
    i = 0;
    while (result[i])
    {
        printf("  %d: '%s'\n", i, result[i]);
        i++;
    }
    
    // Test count_matching_files directly
    printf("\nTesting count_matching_files('*'): %d\n", count_matching_files("*"));
    
    return 0;
}