#define BSIZE (20)

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{

	int c;

	short count = 0, last = 0, longest = 0, size = BSIZE;

	char *buff = calloc(20, sizeof(char)), *rec = malloc(1);

	while ((c = getchar()) != EOF)
	{
		if (isalpha(c))
		{
			last = 1;

			if (++count == size - 1)
			{
				buff = (char*)realloc(buff, size * 2);
				size *= 2;
			}
			*(buff + count - 1) = (char)c;
		}
		else
		{
			if (last)
			{
				if (count > longest)
				{
					longest = count;

					rec = (char*)realloc(rec, count+1);
					strcpy(rec, buff);
				}

				if (size != BSIZE)
				{
					buff = (char*)realloc(buff, BSIZE);
					size = BSIZE;
				}
				memset(buff, 0, BSIZE);
				count = 0;
			}
			last = 0;
		}
	}
	printf("%d characters in longest word: %s\n", longest, rec);

	free(buff);
	free(rec);

	return 0;
}
