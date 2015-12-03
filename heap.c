/* AN IMPLEMENTATION OF HEAP IN AN ARRAY.*/

#include <stdio.h>
#define MEMORY_MAX 1000 //Size of array.
#define MAGIC_NUMBER 8688 //Used to check validity of starting position in case of  Delete Function.
#define JUMP 4//This for the size of header.

int Memory[MEMORY_MAX];

//Declaring the functions.
void CreateHeader(int , int , int , int );
int Allocate(int );
void DeleteData(int );
void DisplayStatus();

void CreateHeader(int Index, int Next, int Previous, int Occupied) //Creates a header useful to keep track of starting positions .
{
	Memory[Index] = Next;
	Memory[Index + 1] = Previous;
	Memory[Index + 2] = Occupied;
	Memory[Index + 3] = MAGIC_NUMBER;
}

// According to first fit algorithm.
int Allocate(int Spaces)//Accomodates the space required at a particular postion the array and creates header for it.
{
	int Index = 0;
	while (Index < MEMORY_MAX)
	{
		if (Memory[Index] == -1)
		{
			printf("There is no space to allocate.\n");
			break;
		}
		else 
		{
			if (((Memory[Index] - Memory[Memory[Index]] - (2 * JUMP) + 2) >= Spaces + JUMP) && (Memory[Index + 2] == 0))
			//Checking if space between two adjacent blocks is enough for allocation of required size and its header and also creates header(if true).
			{
				
				CreateHeader(Index + Spaces + JUMP, Memory[Index], 0, 0);
				Memory[Memory[Index]] = Index + Spaces + JUMP;
				Memory[Index] = Index + Spaces + JUMP + 1;
				Memory[Index + 2] = 1;
				break;
			}
			else if (((Memory[Index] - Memory[Memory[Index]] - (2 * JUMP) + 2) >= Spaces) && (Memory[Index + 2] == 0))
			//If not enough sets the current block as occupied but header is not created.
			{
				Memory[Index + 2] = 1;
				break;
			}
			else if (((Memory[Index] - Memory[Memory[Index]] - (2 * JUMP) + 2) < Spaces) || (Memory[Index + 2] != 0))
			//Points to the next block of Memory.
			{
				Index = Memory[Index] - 1;
			}
		}
	}
	return Index;
}

void DeleteData(int StartingPosition)//Deleting the conrents of Memory block based on the input given and validation with magic number.
{
	
	if (Memory[StartingPosition + 3] == MAGIC_NUMBER)//Checking the validity of starting position given.
	{
		if ((Memory[Memory[StartingPosition] + 1]) == 0)
		{
			int Temporary = Memory[StartingPosition];
			Memory[StartingPosition] = Memory[Memory[StartingPosition]-1];
			Memory[Memory[Memory[StartingPosition]-1]] = Memory[Memory[StartingPosition]];
			Memory[Temporary] = 0;
			Memory[Temporary + 1] = 0;
			Memory[Temporary + 2] = 0;
			Memory[Temporary + 3] = 0;
			Memory[StartingPosition + 2] = 0;
		}
		else if ((Memory[Memory[StartingPosition + 1] + 2]) == 0)
		{
			Memory[Memory[StartingPosition + 1]] = Memory[StartingPosition];
			Memory[Memory[StartingPosition]] = Memory[StartingPosition + 1];
			Memory[StartingPosition] = 0;
			Memory[StartingPosition + 1] = 0;
			Memory[StartingPosition + 2] = 0;
			Memory[StartingPosition + 3] = 0;
		}
		else 
		{
			Memory[StartingPosition + 2] = 0;
		}
	}
	else 
	{
		printf("Wrong starting position\n");
	}

}

void DisplayStatus()//Displays the status occupancy of positions of the array.
{
	char String[] = "occupied", c1, c2;
	int Index = 0;
	while (Memory[Index] != -1)
	{
		if (Memory[Index + 2] == 0)
		{
			c1 = 'u';
			c2 = 'n';
		}
		else 
		{
			c1 = '\0';
			c2 = '\0';
		}
		printf("Memory of array from [%d , %d] is %c%c%s\n", Index + 1, Memory[Index] - 1, c1, c2, String);
		Index = Memory[Index] - 1;
	}
	printf("Memory of array from [%d , %d] is occupied.\n",998,1000);
}

int main(void)//Takes the user's choice and proceeds accordingly.
{

	int Choice;
	int StartingPosition , Spaces;
	CreateHeader(0, 998, -1, 0);//Initial Headers.
	CreateHeader(997, -1, 0, 1);//Initial Headers.

	while (1)
	{
		printf("Press 1 To Allocate Data\n");
		printf("Press 2 To Remove Data\n");
		printf("Press 3 To Display The Status Of Array\n");
		printf("Press 4 To Exit\n");
		scanf("%d", &Choice);
		
		if (Choice == 4)//Termination of program.
		{
			break;
		}
		else
		{
			switch (Choice)
			{
			case 1://Takes number of spaces and checks for availibility of space.
				 	printf("Input the number of spaces: ");
					scanf("%d", &Spaces);
					printf("Starting position of your allocated space is %d\n", Allocate(Spaces)+1);
					break;
			case 2://Takes the starting position and clears the data stored in it.
					printf("Input the starting position to remove: ");
					scanf("%d", &StartingPosition);
					DeleteData(StartingPosition);
					break;
			case 3://Dsplays the occupancy of array.
					DisplayStatus();
					break;
			default://Invalid prompt.
					 printf("Invalid choice.\n");
			}
		}
	}
}
