#include <stdio.h>
#include <stdlib.h>

typedef struct character
{
	char c;
	character * previous = NULL;
	character * next = NULL;
} C;

void deleteCharacter(C * target)
{
	if(target->next != NULL) target->previous->next = target->next;
	else target->previous->next = NULL;
}

void insertCharacter(C * from, C * target)
{
	target->previous = from;
	target->next = from->next;
	from->next = target;
}

int main()
{
	// preparation
	C head;
	head.c = '#';
	C * cursor = &head;
	cursor->previous = NULL;
	// actual content
	char content[2000];
	gets(content);
	char * i = content;
	while(*i != '\0' && *i != '\n')
	{
		//printf("processing: %c\n", *i);
		if(*i == '/')
		{
			switch(*(i+1))
			{
				case 'b': // backspace
				
					if(cursor->previous != NULL)

					{
						//printf("delete: %c\n", cursor->c);
						cursor = cursor->previous;
						deleteCharacter(cursor->next);
					}
					
					i += 9;
					break;
				case 'l': // left
					//printf("cursor left move.\n");
					cursor = (cursor->previous == NULL ? cursor : cursor->previous);
					i += 4;
					break;
				case 'r': // right
					//printf("cursor right move.\n");
					cursor = (cursor->next == NULL ? cursor : cursor->next);
					i += 5;
					break;
				case 'n': // newline
					//printf("newline.\n");
					C * n = (C *)calloc(1, sizeof(C));
					n->c = '\n';
					insertCharacter(cursor, n);
					cursor = n;
					i += 7;
					break;
				
			}
		}
		// normal input
		else
		{
			//printf("input: %c\n", *i);
			C * n = (C *)calloc(1, sizeof(C));
			
	 		n->c = *i;
			insertCharacter(cursor, n);
			cursor = n;
		}
		i++;
	}
	// print
	C * output = &head;
	while(output->next != NULL)
	{
		printf("%c", output->next->c);
		output = (output->next == NULL ? NULL : output->next);
	}
	return 0;
}
