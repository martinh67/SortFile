/* so that scanf can be used without warnings */
#define _CRT_SECURE_NO_WARNINGS

/* in order to use scanf, printf, fopen, FILE, feof, fclose */
#include <stdio.h>

/* in order to use strlen and strcmp */
#include <string.h>

/* in order to use malloc and free */
#include <stdlib.h>

/* function prototype for reading unsorted input file */
int read_file(const char *filename, char* array[]);

/* function prototype for bubble sort*/
void bubble_sort(char* array[], int array_size);

/* function prototype for the swap_terms function */
void swap_terms(char** x, char** y);

/* function prototype for the write_file function */
int write_file(const char *file_name, char* array[], int array_size);

/* function prototype for the dellocate_memory function */
void deallocate_memory(char* array[], int array_size);

/* start of the main function that takes a file in, sorts the data alphabetically and gives an output file */
int main(int arg_c, char *arg_v[])
{
	/* declare the variables required */
	char file_name[260];
	char* array[1000];
	int array_size, can_read = 0, can_write = 0;

	/* information regarding the program */
	printf("You will be asked to enter both an input and output file in order to sort the words within it\n");
	printf("\nPlease include the file path and extension within the name of the file\n");

	do
	{
		/* ask the user to input a file */
		printf("\nFirst enter an input file path, name and extension: ");
		scanf("%s", file_name);

		/* start to read the file */
		if (-1 == (array_size = read_file(file_name, array))) {

			/* give error message if the file could not be found */
			printf("\nSorry, the file %s could not be opened\n", file_name);

			/* introduce a wait */
			getchar();

			/* set the can_read variable to 0 */
			can_read = 0;
		}
		else {
			/* set the can_read variable to 1 */
			can_read = 1;
		}

	} while (can_read == 0);

	/* sort the strings in the file */
	bubble_sort(array, array_size);

	/* inform the user that this was successful*/
	printf("\nThe data within %s was sorted successfully\n", file_name);

	/* inform the user about the difference in the write file aspect */
	printf("\nIn this next part a file will be created if it does not already exist\n");
	printf("\nThe file path and extension must be included in order for the program to work\n");

	do
	{
		/* ask the user to output a file */
		printf("\nNext enter an output file path, name and extension: ");
		scanf("%s", file_name);

		/* start to write the file */
		if (-1 == (array_size = write_file(file_name, array, array_size))) {

			/* give error message if the file could not be found */
			printf("\nSorry, the file %s could not be opened\n", file_name);

			/* introduce a wait */
			getchar();

			/* set the can_write variable to 0 */
			can_write = 0;
		}
		else {
			/* set the can_write variable to 1 */
			can_write = 1;
		}

	} while (can_write == 0);
	/* introduce a wait */
	getchar();
	
	/* call dellocate memory function */
	deallocate_memory(array, array_size);

	/* inform user that the file has been saved */
	printf("\nThe file %s has been successfuly saved\n", file_name);

	return 0;
}

int read_file(const char *file_name, char* array[]) {

	/* initialise and declare variables required */
	char buffer[512]; 
	int i = 0, length;
	FILE * file_in;

	/* open the file to be read from */
	file_in = fopen(file_name, "r");
	
	/* check if the file was able to be opened */
	if (!file_in)

		/* return an error to the main function */
		return -1;

	/* if the file was opened without an error */
	else
	{
		while (!feof(file_in)) {

			/* read the first line of the input file */
			fscanf(file_in, "%s", buffer);

			/* find the length of the string */
			length = strlen(buffer);

			/* allocate memory for the string */
			array[i] = (char*)malloc(length + 1);

			/* copy the string to the array */
			strcpy(array[i], buffer);

			/* increment the counter */
			++i;
		}
	}

	/* close the input file */
	fclose(file_in);
	
	/* return */
	return i;
}

void bubble_sort(char* array[], int array_size) {
	int i, compare;
	for (--array_size; array_size > 0; --array_size)
		for (i = 0; i < array_size; ++i) {
			/* compare two strings in the file */
			compare = strcmp(array[i], array[i + 1]);
			/* if the strings are > 0 they are in the wrong order*/
			if (compare > 0)
				/* call the swap function */
				swap_terms(&array[i], &array[i + 1]);
		}
}

/* function to write to the output file */
int write_file(const char *file_name, char* array[], int array_size) {

	/* initalise the variables required */
	int i;
	FILE * file_out;
	
	/* open the output file */
	file_out = fopen(file_name, "a+");

	/* check if the file was able to be opened*/
	if (!file_out)

		/* return an error to the main function */
		return -1;

	/* if the file was opened without an error */
	else
	{
		for (i = 0; i < array_size - 1; ++i)
			/* take a new line after each string */
			fprintf(file_out, "%s\n", array[i]);

		fprintf(file_out, "%s", array[array_size - 1]);

		/* close the output file */
		fclose(file_out);

		/* return success code to the main function */
		return 0;
	}
}

/* function called within bubble_sort to swap terms */
void swap_terms(char** x, char** y) {
	char *hold = *x;
	*x = *y;
	*y = hold;
}

/* function to deallocate memory */
void deallocate_memory(char* array[], int array_size) {
	int i;
	for (i = 0; i < array_size; ++i)
		free(array[i]);
}