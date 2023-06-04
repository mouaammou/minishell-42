#include <stdio.h>
#include <string.h>

void replace_str(char *phrase, const char *oldstring, const char *newstring) {
    char *temp = NULL;
    int oldlen = strlen(oldstring);
    int newlen = strlen(newstring);
    int phraselen = strlen(phrase);

    // Replace all occurrences of oldstring with newstring
    while ((temp = strstr(phrase, oldstring)) != NULL) {
        int prefixlen = temp - phrase;
        int suffixlen = phraselen - (prefixlen + oldlen);
        char result[1000]; // Assuming the maximum length of the new phrase is 1000

        strncpy(result, phrase, prefixlen); // Copy the prefix
        result[prefixlen] = '\0';

        strcat(result, newstring); // Append the newstring
        strcat(result, temp + oldlen); // Append the suffix

        strcpy(phrase, result); // Copy the modified phrase back

        phraselen = strlen(phrase); // Update the length of the modified phrase
    }
}

char	*get_string_inside_quote(char* str) {
    char* start = strchr(str, '"');
    if (start == NULL) return NULL;  // no quotes found
    char* end = strchr(start+1, '"');
    if (end == NULL) return NULL;  // mismatched quotes
    size_t len = end - start - 1;
    char* result = malloc(len+1);
    if (result == NULL) return NULL;  // memory allocation error
    strncpy(result, start+1, len);
    result[len] = '\0';
    return result;
}

int main() {

    char* str = "asdfadsf";
	char* result = get_string_inside_quote(str);
	printf("%s\n", result);  // prints "fox jumps"
	free(result);  // remember to free the allocated memory

    return 0;
}
