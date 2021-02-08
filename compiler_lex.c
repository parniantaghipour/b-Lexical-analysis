//parnain taghipour
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BSIZE 128 /* buffer size */
#define NONE -1
#define EOS '\0'

#define NUM 256
#define DIV 257
#define MOD 258
#define ID 259
#define DONE 260
#define MAXCHAR 1000

extern int tokenval; /*  value of token attribute */
extern int lineno;

char lexbuf[BSIZE];
int lineno = 1;
int tokenval = NONE;

struct entry
{
	char *lexptr;
	int token;
};

extern struct entry symtable[];

#define STRMAX 999
#define SYMMAX 100

char lexemes[STRMAX];
int lastchar = -1; /*  last used position in lexemes   */
struct entry symtable[SYMMAX];
int lastentry = -1;

int findID(char token[])
{
	if (strcmp(token, "array") == 0)
	{
		return 1;
	}
	else if (strcmp(token, "boolean") == 0)
	{
		return 2;
	}
	else if (strcmp(token, "char") == 0)
	{
		return 3;
	}
	else if (strcmp(token, "else") == 0)
	{
		return 4;
	}
	else if (strcmp(token, "false") == 0)
	{
		return 5;
	}
	else if (strcmp(token, "for") == 0)
	{
		return 6;
	}
	else if (strcmp(token, "function") == 0)
	{
		return 7;
	}
	else if (strcmp(token, "if") == 0)
	{
		return 8;
	}
	else if (strcmp(token, "integer") == 0)
	{
		return 9;
	}
	else if (strcmp(token, "print") == 0)
	{
		return 10;
	}
	else if (strcmp(token, "return") == 0)
	{
		return 11;
	}
	else if (strcmp(token, "string") == 0)
	{
		return 12;
	}
	else if (strcmp(token, "true") == 0)
	{
		return 13;
	}
	else if (strcmp(token, "void") == 0)
	{
		return 14;
	}
	else if (strcmp(token, "while") == 0)
	{
		return 15;
	}
	else
	{
		return -1;
	}
}

int insert(char *s, int tok) /*returns position of entry for s*/
{
	int len;
	len = strlen(s); /*  strlen computes length of s     */
	if (lastentry + 1 >= SYMMAX)
		printf("symbol table full");
	if (lastchar + len + 1 >= STRMAX)
		printf("lexemes array full");
	lastentry = lastentry + 1;
	symtable[lastentry].token = tok;
	symtable[lastentry].lexptr = &lexemes[lastchar + 1];
	lastchar = lastchar + len + 1;
	strcpy(symtable[lastentry].lexptr, s);
	// printf("/// name:%s  id:%d",symtable[las])
	return lastentry;
}

int findToken(char name[])
{
	for (int i = 0; i <= lastentry; i++)
	{
		if (strcmp(symtable[i].lexptr, name) == 0)
		{
			return symtable[i].token;
		}
	}
	return -1;
}

int Analysis(char line[])
{

	char word[BSIZE];
	static int x = 0;

	// skip-comments
	if (line[0] == '/' && line[1] == '/')
	{
		return -1;
	}

	//read-line
	for (int i = 0; i < strlen(line); i++)
	{
		if (isalpha(line[i]))
		{
			int count = 0;
			word[count] = line[i];
			while (isalpha(line[i + 1]) || isalnum(line[i + 1]))
			{
				count++;
				i++;
				word[count] = line[i];
			}
			word[count + 1] = '\0';
			int id = findID(word);

			//print
			if (id == -1)
			{
				int result = findToken(word);
				if (result == -1)
				{
					x++;
					insert(word, x);
					// printf("ID %d \n", x);
					printf("ID %d //%s \n", x , word);
				}
				else
				{
					// printf("ID %d \n", result);
					printf("ID %d //%s \n", result , word);
				}
			}
			else
			{
				printf("KEYWORD %d\n", id);
			}
		}
		else if (isalnum(line[i]))
		{
			int count = 0;
			word[count] = line[i];
			while (isalnum(line[i + 1]))
			{
				count++;
				i++;
				word[count] = line[i];
			}
			word[count + 1] = '\0';
			printf("%s NUM\n", word);
		}
		else if (line[i] == '"')
		{
			int skip = 1;
			while (skip == 1)
			{
				i++;
				if (line[i] == '"')
				{
					skip = 0;
				}
			}
			printf("STRING 100\n");
		}
		else if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			;
		else
		{
			printf("%c NONE\n", line[i]);
		}
	}
	return 0;
}

int init()
{
	FILE *fptr;
	char str[MAXCHAR];
	fptr = fopen("G:\\test.b", "r");
	while (fgets(str, MAXCHAR, fptr) != NULL)
		Analysis(str);
	fclose(fptr);
	return 0;
}

int main()
{
	init();
}
