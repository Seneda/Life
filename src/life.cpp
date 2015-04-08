#include <iostream>

int draw(char board[][40]){
	for (int j=0; j<40;++j){
		for (int i=0; i<40; ++i)
			std::cout << board[i][j] << " ";
		std::cout << "\n";
	}
}

int main(){
	char board[40][40] = {};
	for (int i=0; i<40; ++i){
		for (int j=0; j<40; ++j){
			if (board[i-1][j-1] != 'X')
				board[i][j] = 'X';
			else 
				board[i][j] = ' ';

		}
	}
	draw(board);


}
