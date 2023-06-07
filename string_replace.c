#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linked list node structure
struct Node {
    char* data;
    struct Node* next;
};

// Function to convert linked list content to char**
char** convertLinkedListToCharDoublePointer(struct Node* head, int* count) {
    // Count the number of nodes in the linked list
    struct Node* current = head;
    *count = 0;
    while (current != NULL) {
        (*count)++;
        current = current->next;
    }

    // Allocate memory for char** array
    char** charArray = (char**)malloc(*count * sizeof(char*));

    // Iterate through each node and convert string to char*
    current = head;
    int i = 0;
    while (current != NULL) {
        // Allocate memory for the char* and copy the string
        charArray[i] = (char*)malloc((strlen(current->data) + 1) * sizeof(char));
        strcpy(charArray[i], current->data);

        current = current->next;
        i++;
    }

    return charArray;
}

// Function to free memory allocated for char** array
void freeCharDoublePointer(char** charArray, int count) {
    for (int i = 0; i < count; i++) {
        free(charArray[i]);
    }
    free(charArray);
}

// Main function for testing
int main() {
    // Example linked list
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));

    head->data = "Hello";
    head->next = second;

    second->data = "World";
    second->next = third;

    third->data = "!";
    third->next = NULL;

    // Convert linked list content to char**
    int count;
    char** charArray = convertLinkedListToCharDoublePointer(head, &count);

    // Print the converted char** array
    for (int i = 0; i < count; i++) {
        printf("%s\n", charArray[i]);
    }

    // Free memory allocated for char** array
    freeCharDoublePointer(charArray, count);

    // Free memory allocated for linked list
    free(head);
    free(second);
    free(third);

    return 0;
}
