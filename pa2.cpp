/*

  The following program solves the L-shape blocks problem

   Given
	  A 2^N x 2^N array (In this assignment, we restrict the value N as 1, 2 and 3 )
	   The location of the empty cell (x,y)
		  The legal (x,y) coordinates of the empty cell:

			  For a 2 x 2 block, the legal range is 0-1
			  For a 4 x 4 block, the legal range is 0-3
			  For a 8 x 8 block, the legal range is 0-7
	   You can assume all the input values are correct

	Output:

	  The empty cell (x,y) remains empty
	  All other cells are filled by non-overlapping L-shape blocks

	Output mode:
	  (0) Console output without normalization
	  (1) Console output with normalization

	   Author: Peter, Brian, Tommy
*/

#include <iostream>
using namespace std;

// Constants in global scope
const int MAX_WIDTH = 8;
const int LOCATEQUADRANT_NOT_IMPLEMENTED = 0;

// TODO:
// function locateQuadrant:
// @param x:  x coordinate of the empty cell
// @param y:  y coordinate of the empty cell
//
// If x < half width, y < half width, then return 1
// If x >= half width, y < half width, then return 2
// If x >= half width, y >= half width, then return 3
// If x < half width, y >= half width, then return 4
//
// @return: int
// The function returns after getting valid values for width, emptyXPos and emptyYPos
int locateQuadrant(int width, int x, int y)
{
	if(x < width/2 && y < width/2){
		return 1;
	}
	else if(x >= width/2 && y < width/2){
		return 2;
	}
	else if(x >= width/2 && y >= width/2){
		return 3;
	}
	else if(x < width/2 && y >= width/2){
		return 4;
	}
	else{
		return LOCATEQUADRANT_NOT_IMPLEMENTED;
	}
}

/**
	Given the puzzleMap (2D array from the recursive function),
	Generate the console output
 */
void visualizePuzzleByText(int width, char puzzleMap[][MAX_WIDTH])
{

	cout << "  ";
	for (int x = 0; x < width; x++)
		cout << x << " ";
	cout << endl;

	for (int y = 0; y < width; y++)
	{
		cout << y << ":";
		for (int x = 0; x < width; x++)
			cout << puzzleMap[x][y] << " ";
		cout << endl;
	}
}

/**
 * Initialize the whole puzzleMap using by a space character: ' '
 */
void initializePuzzleMap(int width, char puzzleMap[][MAX_WIDTH])
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < width; y++)
			puzzleMap[x][y] = ' ';
}


void increment_chars(char arr[][8], int width) {
	for (int i=0;i<width;i++){
		for (int j=0;j<width;j++){
	  		if(arr[i][j]!=' '){
      			arr[i][j]+=26;
			}
		}
	}
	return;
}

void replace_char(char arr[][8], int width, char target, char replacement) {
	for (int i=0;i<width;i++){
		for (int j=0;j<width;j++){
      		if (arr[i][j] == target){
        		arr[i][j] = replacement;
			}
		}
	}
	return;
}



// TODO:
// Normalize the whole puzzleMap. The space character ' ' will not be changed.
//

void normalizePuzzleMap(int width, char puzzleMap[][MAX_WIDTH])
{
	increment_chars(puzzleMap,width);
	char firstAlpha = 'A';
	for(int i=0;i<width;i++){
		for(int j=0;j<width;j++){
			if(puzzleMap[j][i]>firstAlpha){
				char temp = puzzleMap[j][i];
				replace_char(puzzleMap,width,temp,firstAlpha++);
			}
		}
	}
	return;
}

// TODO:
// [The most important function in this program]
// The recursive function to fill up the character array: puzzleMap
// You need to figure out the parameters of the fillPuzzleRecursive function by yourself
//
void fillPuzzleRecursive(int width, char puzzleMap[][MAX_WIDTH], int tx,
                         int ty, int x, int y, char &nextChar, int quadrant = 0)
{
    // tx: top Left X coordinate
    // ty: top Left Y coordinate
    // x:  x coordinate of the empty cell
    // y:  y coordinate of the empty cell
    if (width == 2)
    {
        // The base case
        // Fill the three non-empty cells with the next character
        for(int i=0;i<2;i++)
        {
            for(int j=0;j<2;j++)
            {
                if((tx+i!=x||ty+j!=y)&&(puzzleMap[tx+i][ty+j]==' '))
                {
                    puzzleMap[tx+i][ty+j] = nextChar;
                }
            }
        }
    }
    else
    {
        // The general case
        // Divide the sub-rectangle into four equal quadrants
        int halfWidth = width/2;
        int midX = tx+halfWidth;
        int midY = ty+halfWidth;
        int quad = locateQuadrant(width,x-tx,y-ty);
		bool outRange = (x<tx) || (y<ty) || (x>tx+width) || (y>ty+width);
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				if(!outRange){
					if(locateQuadrant(width,midX-i-tx,midY-j-ty)!=quad){
						puzzleMap[midX-i][midY-j] = nextChar;
					}
				}
				else{
					if(locateQuadrant(width,midX-i-tx,midY-j-ty)!=quadrant){
						puzzleMap[midX-i][midY-j] = nextChar;
					}
				}
			} 
		}

        fillPuzzleRecursive(halfWidth, puzzleMap, tx, ty, x, y, ++nextChar,3); // top left
        fillPuzzleRecursive(halfWidth, puzzleMap, tx, midY, x, y, ++nextChar,2); // bottom left
        fillPuzzleRecursive(halfWidth, puzzleMap, midX, ty, x, y, ++nextChar,4); // top right
        fillPuzzleRecursive(halfWidth, puzzleMap, midX, midY, x, y, ++nextChar,1); // bottom right
    }


    return;
}


// TODO:
// function checkInput:
//
// @param width: the width of the square. Valid values: 2, 4, 8
// You can assume inputs are always integers.
// @param emptyXPos: the x-axis of the empty position.
// Valid range: [0, width-1].
// You can assume inputs are always integers.
// @param emptyYPos: the y-axis of the empty position.
// Valid range: [0, width-1].
// You can assume inputs are always integers.
//
//  Note: The pass-by-reference variables will be used in the main function.
// @return: void
// The function returns after getting valid values for width, emptyXPos and emptyYPos
void checkInput(int &width, int &emptyXPos, int &emptyYPos)
{
	do {
		cout << "Enter the width/height of the puzzle (2, 4, 8): ";
		cin >> width;
		cout << endl;
	} while(width != 2 && width != 4 && width != 8);
	do {
		cout << "Enter the x-coordinate of the empty cell (0-" << width - 1 << "): ";
		cin >> emptyXPos;
		cout << endl;
	} while(emptyXPos < 0 || emptyXPos > width - 1);
	do {
		cout << "Enter the y-coordinate of the empty cell (0-" << width - 1 << "): ";
		cin >> emptyYPos;
		cout << endl;
	} while(emptyXPos < 0 || emptyXPos > width - 1);
	return;
}

// You are NOT ALLOWED to modify the main function
int main()
{

	int width = 0;
	int emptyXPos = 0;
	int emptyYPos = 0;

	checkInput(width, emptyXPos, emptyYPos);

	// initialized with empty spaces..
	char puzzleMap[MAX_WIDTH][MAX_WIDTH];

	// initialize
	initializePuzzleMap(width, puzzleMap);

	int modeOfOperation = 0;
	do
	{
		cout
			<< "0: Exit directly (for testing checkInput function), 1: Output Quadrant of the empty cell,"
			<< endl
			<< "2: Output without normalization (for student's debug only), 3: Output with normalization"
			<< endl;
		cout << "Enter the output mode: ";
		cin >> modeOfOperation;
		cout << endl;
	} while (modeOfOperation < 0 || modeOfOperation > 3);

	if (modeOfOperation == 0)
	{
		return 0;
	}
	if (modeOfOperation == 1)
	{
		int quad = locateQuadrant(width, emptyXPos, emptyYPos);
		cout << "Quadrant for the empty cell: " << quad << endl;
		return 0;
	}
	char nextChar = 'A';

	// invoke the recursive call here...
	// Result: puzzleMap will be filled by characters
	fillPuzzleRecursive(width, puzzleMap, 0, 0, emptyXPos, emptyYPos, nextChar);

	int quad = locateQuadrant(width, emptyXPos, emptyYPos);
	cout << "Quadrant for the empty cell: " << quad << endl;
	if (modeOfOperation == 2)
	{
		visualizePuzzleByText(width, puzzleMap);
	}
	else
	{
		normalizePuzzleMap(width, puzzleMap);
		visualizePuzzleByText(width, puzzleMap);
	}
	return 0;
}
