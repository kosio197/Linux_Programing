
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <string.h>


#define BUFFER_SIZE 200

void read_line(char ** line) {
    char buffer[BUFFER_SIZE];
    buffer[0] = '\0';

    *line = (char*) malloc(BUFFER_SIZE);

    if (!line) {
        printf("Can't allocate memory");
        exit(1);
    }

    int current_size = BUFFER_SIZE;

    (*line)[0] = '\0';

    while (1) {
        void * c = fgets(buffer, BUFFER_SIZE, stdin);

        strcat(*line, buffer);

        if (c == NULL || feof(stdin)) {
            break;
        }

        if (buffer[strlen(buffer) - 1] == '\n') {
            (*line)[strlen(*line) - 1] = '\0';
            break;
        }

        char * new_line = (char*) realloc(*line, current_size * 2);

        if (!new_line) {
            printf("Can't allocate memory");
            exit(1);
        }

        current_size *= 2;
        *line = new_line;
    }
}

int calculate(double *a, double *b, char* input) {
    int root = 0;
    char* atoken;
    double aa = 1;
    char*rem;

    if (input[0] == 'a') {
        atoken = strtok(input, "a");
    }
    else {
        atoken = strtok(input, "a");
        aa = strtod(atoken, &rem);
        atoken = strtok(NULL, "a");
    }

    char* btoken = strtok(atoken, "b");
    double bb = strtod(btoken, &rem);
    btoken = strtok(NULL, "b");
    double cc = strtod(btoken, &rem);

    double dis = bb * bb - (4 * aa * cc);
    if (dis < 0) {
        return 0;
    }
    else if (dis == 0) {
        *a = -bb / (2 * aa);
        *b = *a;
        return 1;
    }
    else {
        *a = (-bb - sqrt(dis)) / (2 * aa);
        *b = (-bb + sqrt(dis)) / (2 * aa);
        return 2;
    }




    return root;
}

int main(int argc, char** argv) {

    char * input;
    read_line(&input);
    // printf("%s\n", input);
    double x1, x2;
    int root = calculate(&x1, &x2, input);

    if (root == 1) {
        printf("x1 = x2 = %.3lf", x1);
    }
    else if (root == 2) {
        printf("x1 = %.3lf\nx2 = %.3lf", x1, x2);
    }
    else {
        printf("No real root");
    }

    free(input);
    return (EXIT_SUCCESS);
}

