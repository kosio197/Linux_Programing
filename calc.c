#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 200

void read_line (char ** line) {
    char buffer[BUFFER_SIZE];
    buffer[0] = '\0';

	*line = (char*)malloc(BUFFER_SIZE);

	if (!line)
	{
		printf("Can't allocate memory");
		exit(1);
	}

	int current_size = BUFFER_SIZE;

	(*line)[0] = '\0';

	while(1) {
		void * c = fgets(buffer, BUFFER_SIZE, stdin);

		strcat(*line, buffer);

		if (c == NULL || feof(stdin)) {
			break;
		}

		if (buffer[strlen(buffer)-1] == '\n') {
			(*line)[strlen(*line)-1] = '\0';
			break;
		}

		char * new_line = (char*)realloc(*line, current_size * 2);

		if (!new_line)
		{
			printf("Can't allocate memory");
			exit(1);
		}

		current_size *= 2;
		*line = new_line;
	}
}

void convert_to_polish(char * input, char ** result) {
	char * stack = calloc(1, strlen(input));
	*result = calloc(1, strlen(input));
	char * res = *result;
	char current;

	int result_counter = 0;
	int stack_counter = -1;

	int i = 0;
	if (input[0] == '-') {
		res[result_counter] = '0';
		res[result_counter + 1] = ' ';
		result_counter += 2;
	}

	while (i < strlen(input)) {
		switch (input[i]) {
			case '(':
				stack_counter += 1;
				stack[stack_counter] = '(';

				if (input[i+1] == '-') {
					res[result_counter] = '0';
					res[result_counter + 1] = ' ';
					result_counter += 2;
				}
				break;
			case ')':
				current = stack[stack_counter];
				stack_counter -= 1;

				while (current != '(') {
					res[result_counter] = current;
					res[result_counter + 1] = ' ';
					result_counter += 2;

					current = stack[stack_counter];
					stack_counter -= 1;
				}
				break;
			case '+':
				if (stack_counter >= 0) {
					current = stack[stack_counter];
					stack_counter -= 1;

					while (current == '*' || current == '/' || current == '-' || current == '+') {
						res[result_counter] = current;
						res[result_counter + 1] = ' ';
						result_counter += 2;

						current = stack[stack_counter];
						stack_counter -= 1;
					}

					stack_counter += 1;
				}

				stack_counter += 1;
				stack[stack_counter] = '+';

				break;
			case '-':
				if (stack_counter >= 0) {
					current = stack[stack_counter];
					stack_counter -= 1;

					while (current == '*' || current == '/' || current == '+' || current == '-') {
						res[result_counter] = current;
						res[result_counter + 1] = ' ';
						result_counter += 2;

						current = stack[stack_counter];
						stack_counter -= 1;
					}

					stack_counter += 1;
				}

				stack_counter += 1;
				stack[stack_counter] = '-';

				break;
			case '*':
				if (stack_counter >= 0) {
					current = stack[stack_counter];
					stack_counter -= 1;

					while (current == '*' || current == '/') {
						res[result_counter] = current;
						res[result_counter + 1] = ' ';
						result_counter += 2;

						current = stack[stack_counter];
						stack_counter -= 1;
					}

					stack_counter += 1;
				}

				stack_counter += 1;
				stack[stack_counter] = '*';

				break;
			case '/':
				if (stack_counter >= 0) {
					current = stack[stack_counter];
					stack_counter -= 1;

					while (current == '*' || current == '/') {
						res[result_counter] = current;
						res[result_counter + 1] = ' ';
						result_counter += 2;

						current = stack[stack_counter];
						stack_counter -= 1;
					}

					stack_counter += 1;
				}

				stack_counter += 1;
				stack[stack_counter] = '/';
				break;
			case ' ':
				break;

			default:
				while (isdigit(input[i]) || input[i] == '.') {
					res[result_counter] = input[i];
					result_counter++;
					i++;
				}

				i--;
				res[result_counter] = ' ';
				result_counter += 1;
				break;
		}
		i += 1;
	}

	while (stack_counter >= 0) {
		res[result_counter] = stack[stack_counter];
		result_counter += 1;
		res[result_counter] = ' ';
		result_counter += 1;
		stack_counter -= 1;
	}
}

double calculate(char * polish) {
	double * stack = calloc(sizeof(double), strlen(polish));
	int stack_counter = -1;
	char * rem;

	char * token = strtok(polish, " ");

	while (token) {
		if (isdigit(token[0])) {
			stack_counter ++;
			double d = strtod(token, &rem);
			stack[stack_counter] = d;
		} else {
			char op = token[0];
			double op1 = stack[stack_counter];
			double op2 = stack[stack_counter - 1];

			switch (op) {
				case '+':
					stack[stack_counter - 1] = op1 + op2;
					break;
				case '-':
					stack[stack_counter - 1] = op2 - op1;
					break;
				case '*':
					stack[stack_counter - 1] = op1 * op2;
					break;
				case '/':
					stack[stack_counter - 1] = op2 / op1;
					break;
				default:
					break;
			}

			stack_counter -= 1;
		}
		token = strtok(NULL, " ");
	}

	return stack[0];
}

int main() {
	char * input;
	read_line(&input);

	char * res;
	convert_to_polish(input, &res);
	printf("%s\n", res);
	printf("result: %lf\n", calculate(res));

	free(res);
	free(input);

	return 0;
}


