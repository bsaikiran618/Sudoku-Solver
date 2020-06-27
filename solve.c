/*
Author: Sai Kiran B
	the grid is represented as a 2D array.
	empty cells are represented using -1.
	non-empty cells are represented using
	the same number as on the grid.
*/

#include <stdio.h>
#include <string.h>
struct result
{
	short arr[9];
	short len;
};

struct result getPossibilities(short grid[][9], short x, short y)
{
	short possibilities[9];
	for(short i=0;i<9;i++) possibilities[i] = i+1;
	
	//traversing the row
	for(short i=0;i<9;i++)
		if(grid[x][i] != -1)
			possibilities[grid[x][i]-1] = -1;
	//traversing the column
	for(short i=0;i<9;i++)
		if(grid[i][y] != -1)
			possibilities[grid[i][y]-1] = -1;
	//traversing the grid.
	short grid_start_x = (x/3)*3;
	short grid_start_y = (y/3)*3;

	for(short i=grid_start_x;i<grid_start_x+3;i++)
		for(short j=grid_start_y;j<grid_start_y+3;j++)
			if(grid[i][j] != -1)
				possibilities[grid[i][j]-1] = -1;
	short temp_poss[9];
	short index = 0;
	memset(temp_poss, -1 , 9*sizeof(short));


	for(short i=0;i<9;i++)
		if(possibilities[i]!=-1)
			temp_poss[index++] = possibilities[i];
	struct result res;
	memcpy(res.arr, temp_poss,index*sizeof(short));
	res.len = index;
	return res;
}
short solve(short grid[][9], short x, short y)
{
	//search for the next empty cell.
	for(short i=x;i<9;i++)
	{
		for(short j=y;j<9;j++)
		{
			if(grid[i][j]==-1)
			{
				//this is an empty cell.
				//get the possible values for this cell.
				struct result res = getPossibilities(grid, i,j);
				//if the possibilities are zero for this cell then return 0.
				if(res.len == 0) 
				{
					return 0;//failure.
				}
				//else there are some possibilities so try one and solve the remaining cells.
				for(short k=0;k<res.len;k++)
				{
					grid[i][j] = res.arr[k];
					if(solve(grid,x,y)) return 1;
				}
				grid[i][j] = -1;
				return 0; //traversed through all possiblilities but none was able to solve the grid.
			}
		}
	}
	return 1;
}
int main(int argc, char *argv[])
{
	short grid[9][9];
	puts("\nEnter the values in the grid (use 0 for empty cells and digits for non-empty cells):");
	for(short i=0;i<9;i++)
	{
		for(short j=0;j<9;j++)
		{
			scanf("%hi", &grid[i][j]);
			if(grid[i][j] == 0)grid[i][j] = -1;
		}
	}
	short res = solve(grid,0,0);
	printf("The given puzzle is %s\n\n", (res==1?"SOLVABLE":"UNSOLVABLE"));
	for(short i=0;i<9;i++)
	{
		for(short j=0;j<9;j++)
		{
			if(j!=0) putchar('|');
			if(grid[i][j]==-1)putchar(' ');
			else printf("%hi",grid[i][j]);
		}
		printf("\n");
	}
	return 0;
}
