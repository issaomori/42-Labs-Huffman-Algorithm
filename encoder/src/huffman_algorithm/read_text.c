#include "encoder.h"

/**
 * It counts the number of characters in a file
 * 
 * @param argv The name of the file to be read.
 * 
 * @return The number of characters in the file.
 */
int	count_txt(char *argv)
{
	FILE *file = fopen(argv, "r");
	int	i = 0;

	if (!file)
		exit(1);
	while(fgetc(file) != -1)
		i++;
	fclose(file);
	return(i);
}

/**
 * It reads a file and stores it in a char array
 * 
 * @param argv the name of the file to be read
 * @param text The text to be encrypted.
 */
void	read_txt(char *argv, unsigned char* text)
{
	FILE *file = fopen(argv, "r");
	char c;
	int i = 0;
	if (file)
	{
		while(!feof(file))
		{
			c = fgetc(file);
			if (c != -1)
			{
				text[i] = c;
				i++;
			}
		}
	}
	else
		printf("Error to open read_txt\n");
}
