#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to check if a word is a valid number
int is_number(char *word) {
    int i;
    for (i = 0; word[i] != '\0'; i++) {
        if (word[i] < '0' || word[i] > '9') {
            return 0;
        }
    }
    return 1;
}

// Function to convert a word to an integer
int word_to_int(char *word) {
    int num = 0;
    int i;
    for (i = 0; word[i] != '\0'; i++) {
        num = num * 10 + (word[i] - '0');
    }
    return num;
}

// Function to evaluate the expression
int evaluate_expression(char **words, int num_words) {
    int stack[100];
    int top = -1;
    int i;

    for (i = 0; i < num_words; i++) {
        if (strcmp(words[i], "add") == 0) {
            stack[top - 1] = stack[top - 1] + stack[top];
            top--;
        } else if (strcmp(words[i], "sub") == 0) {
            stack[top - 1] = stack[top - 1] - stack[top];
            top--;
        } else if (strcmp(words[i], "mul") == 0) {
            stack[top - 1] = stack[top - 1] * stack[top];
            top--;
        } else if (strcmp(words[i], "rem") == 0) {
            stack[top - 1] = stack[top - 1] % stack[top];
            top--;
        } else if (strcmp(words[i], "pow") == 0) {
            stack[top - 1] = pow(stack[top - 1], stack[top]);
            top--;
        } else if (is_number(words[i])) {
            stack[++top] = word_to_int(words[i]);
        } else {
            printf("expression evaluation stopped invalid words present\n");
            return -1;
        }
    }

    if (top != 0) {
        printf("expression is not complete or invalid\n");
        return -1;
    }

    return stack[0];
}

int main() {
    char expression[100];
    char *words[20];
    int num_words = 0;
    int result;

    fgets(expression, 100, stdin);

    // Tokenize the expression into words
    words[num_words] = strtok(expression, " ");
    while (words[num_words] != NULL) {
        num_words++;
        words[num_words] = strtok(NULL, " ");
    }

    // Evaluate the expression
    result = evaluate_expression(words, num_words);

    if (result != -1) {
        printf("%d\n", result);
    }

    return 0;
}
