#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void reset()
{
  printf("\x1B[37m");
}

void red()
{
  printf("\033[0;31m");
}

void green()
{
  printf("\033[0;32m");
}

int main()
{
	int fd = open("dict2.txt", O_RDONLY);
	int i = 0;
	int j = 0;
	int letters = 0;
	int i_read = 1;
	int wrong = 0;
	char c = 'a';
	char *str;
	srand(time(NULL));
	int r = 0;
	int newlines = 0;
	int points = 0;
	int total_q = 0;
	int dict_size;

	while(i_read)
	{
		i_read = read(fd, &c, 1);
		if (c == '\n')
			newlines++;
	}
	dict_size = newlines;
	lseek(fd, 0, SEEK_SET);
	printf("\nDictionary size: %d\n\n", dict_size);

	printf("How many questions do you want?\n");
	scanf("%d", &total_q);

	while(i < total_q)
	{
		newlines = 0;
		r = rand() % dict_size; 
		while(newlines < r)
		{
			read(fd, &c, 1);
			if (c == '\n')
				newlines++;
		}

		c = 'a';
		while(c != ':')
		{
			read(fd, &c, 1);
			if (c != ':')
				printf("%c", c);
		}
		printf(": \n");

		c = 'a';
		letters = 0;
		read(fd, &c, 1);
		while(c != '\n')
		{
			read(fd, &c, 1);
			letters++;
		}
		str = malloc(sizeof(char) * (letters + 1));
		lseek(fd, -letters, SEEK_CUR);
		read(fd, str, letters);
		str[letters] = '\0';

		c = 'a';
		j = 0;
		i_read = 1;
		wrong = 0;
		while(i_read > 0 && j < letters)
		{
			i_read = read(0, &c, 1);
			if (c != str[j])
			{
				wrong = 1;
				break;
			}
			if (c == '\n')
				break;
			j++;
		}
		while(i_read > 0 && c != '\n')
			i_read = read(0, &c, 1);			
		if (wrong)
		{
			red();
			printf("x \u2192 %s\n\n", str);
			reset();
		}
		else
		{
			green();
			printf("\xE2\x9C\x93\n\n");
			reset();
			points++;
		}
		lseek(fd, 0, SEEK_SET);
		i++;
	}
	printf("\nSCORE: %d / %d\n", points, i);
	free(str);
	close(fd);
}