#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <pthread.h>
#include <unistd.h>

const int height = 100;
const int width = 200;


int countNeighbours( int i, int j, bool board[][height])
{
	int count = 0;
	int xlo = -1;
	int xup = 1;

	int ylo = -1;
	int yup = 1;
	if (i == 0)
        xlo = 0;
	if (i == width-1)
		xup = 0;
	if (j == 0)
		ylo = 0;
	if (j == height-1)
		yup = 0;
	for (int x=xlo; x<=xup; ++x)
		for (int y=ylo; y<=yup; ++y)
			if (not ((x == 0) and (y == 0)))
				if (board[i+x][j+y])
					count = count + 1;
	return count;
}

bool lifeCheck(int i, int j, bool board[width][height]){
	int neighbours = countNeighbours(i,j,board);
	if (board[i][j]){
		//Any live cell with fewer than two live neighbours dies, as if caused by under-population.
		if (neighbours < 2)
			return false;
		//Any live cell with two or three live neighbours lives on to the next generation.
		if ((neighbours == 2)or(neighbours == 3))
			return true;
		//Any live cell with more than three live neighbours dies, as if by overcrowding.
		if (neighbours > 3)
			return false;
	}
	else{
		//Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
		if (neighbours == 3)
			return true;
		else
			return false;
	}
}

int runLifeChecks(bool board[][height]){
	bool oldBoard[width][height] = {};
	for (int j=0;j<height;++j){
			for (int i=0;i<width;++i){
				oldBoard[i][j] = board[i][j];
			}
		}
	for (int j=0;j<height;++j){
		for (int i=0;i<width;++i){
			board[i][j] = lifeCheck(i,j,oldBoard);
		}
	}
	return 0;
}

int draw(bool board[][height]){
	//std::cout << "\033[2J\033[1;1H";
	char screen[height*(2*width+1)];
        for (int j=0; j<height; ++j){
		for (int i=0; i<width; i+=2){
			if (board[i][j] == true){
				screen[j*(width+1)+i] = '[';
				screen[j*(width+1)+i+1] = ']';
			}
			else {
				screen[j*(width+1)+i] = ' ';
				screen[j*(width+1)+i+1] = ' ';
			}
		}
		screen[(j+1)*(width+1)-1] = '\n';
	}
	screen[height*(width+1)+1] = '\0';
	std::cout << screen;
	return 0;
}
bool randomBool() {
  return rand() % 2 == 1;
}


int main(){
   	using namespace std::literals; 
	int seed;
	int step;
	std::cout << "enter a seed number";
	std::cin >> seed;
	std::cout << "enter a time step";
        std::cin >> step;
	std::chrono::milliseconds step_duration (step);
	srand(seed);

	bool board[width][height] = {};
	for (int j=0; j<height; ++j){
		for (int i=0; i<width; ++i){
			if ((i == 3)and(j>=2 and j<=4)){
				board[i][j] = randomBool();
			}
			else
				board[i][j] = randomBool();
		}
		std::cout << std::endl;
	}
	//draw(board);
	std::cout <<std::endl;
	while (true){
		std::cout << "\033[2J\033[1;1H";
		runLifeChecks(board);
		draw(board);
		std::this_thread::sleep_for(step_duration);
	}
}
