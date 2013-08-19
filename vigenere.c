//   *** vigenére.c ***
//
//   William Falk-Wallace
//   
//   A set of methods to encrypt/decrypt according to a simple caeser cipher;
//   currently only works as expected for ascii (would work for others, but the
//   offset would be unexpected and decryption would require reusing these
//   methods, but should work fine - would require an additional offset of 65, 
//   modulo the size of the encoding scheme)
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//encrypt and print
int pencrypt(const char *plain, const char *k)
{
	//get string length and make non-const string copy
	int length = strlen(plain);
	int keylength = strlen(k);	
	char cipher[length];
	char key[keylength];
	strncpy(cipher, plain, length + 1);
	//doesnt account for spaces in key yet. that sticks it to ascii too
	strncpy(key, k, keylength + 1);

	//iterate over the original string
	int i, j; //j->cipher; i->plain
	for(i = j = 0; i < length; i++, j++) 
	{

		//encrypt character
		if(!isspace(cipher[i]))
			cipher[j] = (toupper(cipher[i]) - 65 + toupper(key[(i % keylength)]) - 65) % 26 + 65;
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

//decrypt and print
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

//file encrypt
FILE *fencrypt(char *input, char *output, int offset)
{
	//encrypt letter by letter; temp character p[laintext]
	char p;
	//input plaintext and output ciphertext files
	FILE *plain = fopen(input, "r");
	FILE *cipher = fopen(output, "w");

	//while there're more characters in the plaintext
	while((p = getc(plain)) != EOF)
	{
		//if the character's not a space
		if(!isspace(p))
			//make it uppercase, get rid of the ascii offset
			putc((toupper(p) - 65 + offset) % 26 + 65, cipher);

	}
	//close the files
	fclose(plain);
	fclose(cipher);
}
//file decrypt
FILE *fdecrypt(char *input, char *output, int offset)
{
	//decrypt letter by letter; temp character c[iphertext]
	char c;
	//input ciphertext and output plaintext files
	FILE *cipher = fopen(input, "r");
	FILE *plain = fopen(output, "w");

	//while there're more characters in the ciphertext
	while((c = getc(cipher)) != EOF)
	{
		//should be uppercase already, but just in case; 
		//spaces shouldn't matter though; get rid of the ascii offset
		putc((toupper(c) - 65 - offset) % 26 + 65, plain);
	}
	//close 'em up
	fclose(plain);
	fclose(cipher);
}

//Main/Test function
int main(int argc, char *argv[])
{

	pencrypt("Hello World", "go");
	//proper usage required
	// if (argc != 5) {
	// 	fprintf(stderr, "Usage: %s <e/d> <input-file> <output-file> <offset>\n", argv[0]);
	// 	exit(1);
	// }

	// //encrypt
	// if (toupper(*argv[1]) == 'E')
	// 	fencrypt(argv[2], argv[3], atoi(argv[4]));
	// //decrypt
	// else if (toupper(*argv[1]) == 'D')
	// 	fdecrypt(argv[2], argv[3], atoi(argv[4]));
	// //not e or d
	// else
	// 	die("Invlaid Option");
	// //done
	// return 0;
}