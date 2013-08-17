#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



//encrypt and print
int pencrypt(const char *plain, int offset)
{
	//get string length and make non-const string copy
	int length = strlen(plain);
	char cipher[length];
	strncpy(cipher, plain, length + 1);

	//iterate over the original string
	int i, j;
	for(i = j = 0; i < length; i++, j++) 
	{
		//encrypt character
		if(!isspace(cipher[i]))
			cipher[j] = (toupper(cipher[i]) - 65 + offset) % 26 + 65;
		//or step-back the ciphertext index if it's a space
		else
			j--;
	}
	//null-terminate the potentially shorter ciphertext string
	cipher[j] = '\0';
	//print it
	printf("%s\n", cipher);
	//successful return
	return 0;
}

//encrypt and print
int pdecrypt(const char *cipher, int offset)
{
	//get string length and make non-const string copy
	int length = strlen(cipher);
	char plain[length];
	strncpy(plain, cipher, length + 1);

	//iterate over the original string
	int i, j;
	for(i = j = 0; i < length; i++, j++) 
	{
		//encrypt character
		if(!isspace(plain[i]))
			plain[j] = (plain[i] - 65 - offset) % 26 + 65;
		//or step-back the plaintext index if it's a space
		else
			j--;
	}
	//print it
	printf("%s\n", plain);
	//successful return
	return 0;
}

FILE *fencrypt(char *input, char *output, int offset)
{
	char p;
	FILE *plain = fopen(input, "r");
	FILE *cipher = fopen(output, "w");

	while((p = getc(plain)) != EOF)
	{
		if(!isspace(p))
			putc((toupper(p) - 65 + offset) % 26 + 65, cipher);

	}
	fclose(plain);
	fclose(cipher);
}

FILE *fdecrypt(char *input, char *output, int offset)
{
	char c;
	FILE *cipher = fopen(input, "r");
	FILE *plain = fopen(output, "w");

	while((c = getc(cipher)) != EOF)
	{
		if(!isspace(c))
			putc((toupper(c) - 65 - offset) % 26 + 65, plain);
	}
	fclose(plain);
	fclose(cipher);
}

void die(const char *s)
{
	perror(s);
	exit(1);
}

int main(int argc, char *argv[])
{
	if (argc != 5) {
		fprintf(stderr, "Usage: %s <e/d> <input-file> <output-file> <offset>\n", argv[0]);
		exit(1);
	}

	if (*argv[1] == 'e')
		fencrypt(argv[2], argv[3], atoi(argv[4]));
	else if (*argv[1] == 'd')
		fdecrypt(argv[2], argv[3], atoi(argv[4]));
	else
		die("Invlaid Option");

	return 0;
}