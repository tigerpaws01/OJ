#include <stdio.h>
#include <string.h>
#define LEN 105

void rev_substr(char *str, int len)
{
    int i = 0, j = len - 1;
    while(i < j)
    {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++, j--;
    }

}

void rev_sentence(char *str)
{
    int i = 0, j = 0, len = strlen(str);
    rev_substr(str, len);
    for(; i <= len; i++){
        if(str[i] == ' ' || str[i] == '\0')
        {
            // Count the number of whitespaces
            int w = 1;
            while(str[i+w] == ' ') w++;
            strcpy(str + i + 1, str + i + w);

            rev_substr(str+j, i-j);
            j = i+1;
        }
    }

}

int main()
{
    char str[LEN];
    while(fgets(str, LEN, stdin) != NULL)
    {
        // Cut out redundant whitespace AND newline char(fgets also receives the newline char)
        int strStart = 0, strEnd = strlen(str) - 1;

        while(str[strStart] == ' ') strStart++;
        while(str[strEnd] == ' ' || str[strEnd] == '\n') str[strEnd--] = '\0';

        rev_sentence(str+strStart);
        printf("%s\n", str+strStart);
    }

}
