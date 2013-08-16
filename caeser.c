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

FILE *fencrypt(FILE *input, int offset)
{

}

int main(int argc, char *argv[])
{
	char *line = " Hello  World ";
	char *line2 = "JGNNQYQTNF";
	printf("%s\n", line);
	pencrypt(line, 2);
	printf("%s\n", line2);
	pdecrypt(line2, 2);	return 0;
}