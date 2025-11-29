#include <stdio.h>
#include <string.h>

struct Book {
    int id;
    int popularity;
    int lastUsed;
};
int main() 
{
    int capacity,i, Q;
     
	printf("LIBRARY SHELF SYSTEM\n");
    printf("____________________\n");
    
    printf("\nEnter the capacity of the books which can be stored at once: ");
    scanf("%d", &capacity);
    
    printf("\nEnter the number of operations you want to perform: ");
    scanf("%d",&Q);
   
    struct Book shelf[80];   
    int size = 0;
    int time = 0;           
    
    while (Q--) 
	{
        char op[10];
        scanf("%s", op);
        if (strcmp(op, "ADD") == 0) 
		{
            int x, y;
            scanf("%d %d", &x, &y);

            int found = -1;

            for (i = 0; i < size; i++) 
			{
                if (shelf[i].id == x) 
				{
                    found = i;
                    break;
                }
            }
            if (found != -1) 
			{
                shelf[found].popularity = y;
                shelf[found].lastUsed = ++time;
            }
            else 
		      {
                if (size == capacity) 
				{
                    int lru = 0;
                    for (i = 1; i < size; i++)
                        if (shelf[i].lastUsed < shelf[lru].lastUsed)
                            lru = i;
                    for (i = lru; i < size - 1; i++)
                        shelf[i] = shelf[i + 1];

                    size--;
                }
                shelf[size].id = x;
                shelf[size].popularity = y;
                shelf[size].lastUsed = ++time;
                size++;
            }
        }
        else if (strcmp(op, "ACCESS") == 0) 
		  {
            int x;
            scanf("%d", &x);

            int found = -1;
            for (i = 0; i < size; i++) 
			{
                if (shelf[i].id == x) 
				{
                    found = i;
                    break;
                }
            }
            if (found == -1) 
			{
                printf("-1\n");
            } else {
                shelf[found].lastUsed = ++time;
                printf("%d\n", shelf[found].popularity);
            }
        }
    }
    return 0;
}

