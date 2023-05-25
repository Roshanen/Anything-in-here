#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int storeDynamicInt(char *line, int **array, int *size)
{
    char *strNumber = strtok(line, " \n");
    while (strNumber != NULL)
    {
        int number = atoi(strNumber);
        (*size)++;
        (*array) = realloc((*array), (*size) * sizeof(int));
        (*array)[(*size) - 1] = number;
        strNumber = strtok(NULL, " \n");
    }
}

int main()
{
    int *a = NULL;
    char input[100];
    int size = 0;
    int b;

    fgets(input, sizeof(input), stdin);

    storeDynamicInt(input, &a, &size);

    for (int i = 0; i < size; i++){
        printf("%d ", a[i]);
    }
    free(a);
    return 0;
}
