#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *args[] = {"echo", "*", "|", "awk", "-v", "RS=\" \"", "'{print}'", "|", "sort", NULL};
    int pipe_idx = 3; // Position of first pipe
    char **temp;
    int i, j;
    
    printf("Original args:\n");
    i = 0;
    while (args[i])
    {
        printf("  [%d] '%s'\n", i, args[i]);
        i++;
    }
    
    printf("\npipe_idx = %d\n", pipe_idx);
    printf("Will copy args[0] to args[%d]\n", pipe_idx - 2);
    
    temp = malloc((pipe_idx + 1) * sizeof(char *));
    if (!temp)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    i = -1;
    while (++i < pipe_idx - 1)
    {
        temp[i] = malloc(strlen(args[i]) + 1);
        if (!temp[i])
        {
            printf("String allocation failed for args[%d]\n", i);
            return 1;
        }
        j = -1;
        while (args[i][++j])
            temp[i][j] = args[i][j];
        temp[i][j] = '\0';
    }
    temp[i] = NULL;
    
    printf("\nSplit args (before pipe):\n");
    i = 0;
    while (temp[i])
    {
        printf("  [%d] '%s'\n", i, temp[i]);
        i++;
    }
    
    // Clean up
    i = 0;
    while (temp[i])
    {
        free(temp[i]);
        i++;
    }
    free(temp);
    
    return 0;
}
