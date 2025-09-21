#include "include/minishell.h"
#include "bonus/include/bonus.h"

int main()
{
    char *args[] = {"echo", "*", NULL};
    char **result;
    int i = 0;
    
    // Change to the minishell_tester directory
    chdir("minishell_tester");
    
    result = expand_wildcard_if_bonus(args, NULL, NULL);
    
    printf("Original args:\n");
    i = 0;
    while (args[i])
    {
        printf("  %d: '%s'\n", i, args[i]);
        i++;
    }
    
    printf("\nExpanded args:\n");
    i = 0;
    while (result[i])
    {
        printf("  %d: '%s'\n", i, result[i]);
        i++;
    }
    
    return 0;
}
