#include <iostream>
#include <vector>
#include <unistd.h>
#include <thread>
#include <time.h>


using namespace std;
bool gameOfLife(vector<vector<int>>& board, int& birthCounter, int& deathCounter) {
    int numRows = board.size();
    int numCols = board[0].size();
    
    vector<vector<int>> liveUpdate;
    vector<vector<int>> deadUpdate;
    
    for(int row = 0;row < numRows;row++){
        for(int col = 0;col < numCols;col++){
            int liveCellNeigh = 0;
            
            for(int itRow = row-1;itRow <= row+1;itRow++){
                for(int itCol = col-1;itCol <= col+1;itCol++){
                    if((itRow == row) && (itCol == col)){} //no self check (do nothing)
                    
                    else{
                        if((itRow > -1) && (itRow < numRows) && (itCol > -1) && (itCol < numCols)){ //inbound check
                            if(board[itRow][itCol] == 1){
                                liveCellNeigh++;
                            }
                        }
                    }
                }
                
            }
            //STARTING UPDATE CHECKS
            if((liveCellNeigh == 3) && (board[row][col] == 0)){ //Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
                liveUpdate.push_back(vector<int>({row,col}));
                birthCounter++;
            }
            
            else if((liveCellNeigh < 2) && (board[row][col] == 1)){ //Any live cell with fewer than two live neighbors dies as if caused by under-population.
                deadUpdate.push_back(vector<int>({row,col}));
                deathCounter++;
            }
            
            else if((liveCellNeigh > 3) && (board[row][col] == 1)){ //Any live cell with more than three live neighbors dies, as if by over-population.
                deadUpdate.push_back(vector<int>({row,col}));
                deathCounter++;
            }
        }
    }
    
    for(vector<int> coord : deadUpdate){
        board[coord[0]][coord[1]] = 0;
    }
    for(vector<int> coord : liveUpdate){
        board[coord[0]][coord[1]] = 1;
    }
    
    if((deadUpdate.size() == 0) && (liveUpdate.size() == 0)){
        cout << "Static stasis maintained after " << birthCounter << ((birthCounter > 1) ? " births, " : " birth ") << "and " << deathCounter << ((deathCounter > 1) ? " deaths." : " death.") << endl;
        return false;
    }
    return true;
}


int main()
{
    srand( time(NULL) ); //Randomize seed initialization
    int nRows;
    int nCols;
    cout << "<--WELCOME TO CONWAY'S GAME OF LIFE-->" << endl;
    cout << "How many rows of Earth?: ";
    cin >> nRows;
    
    cout << "How many columns of Earth?: ";
    cin >> nCols;
    cout << endl;
    
    int initialPop = 0;
    vector<vector<int>> start;
    vector<int> temp;
	for(int i = 0;i < nRows;i++){
	    for(int j = 0;j < nCols;j++){
        	int randNum = rand() % 2; // Generate a random number between 0 and 1
	        temp.push_back(randNum);
            if(randNum == 1){
                initialPop++;
            }
	    }
	    start.push_back(temp);
	    temp.clear();
	}
	


    vector<vector<int>> creator({{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0},{0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0
},{0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0},{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0},{0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0},{0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0},{0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0}});


    int everyOther = 0;
    vector<vector<int>> checkTemp = start; 
    int dCount = 0;
    int bCount = 0;
    
    while(true){
        for(vector<int> row : start){ 
            for(int num : row){
                cout << ((num == 1) ? "\u25A0 " : "  ");
            }
            cout << '\n'; //cleaner and faster than endl
        }

        if(!gameOfLife(start,bCount,dCount)){ 
            break;
        }
        
        if(everyOther % 2 == 1){
            if(checkTemp == start){
                cout << "Dynamic stasis maintained after " << bCount << ((bCount > 1) ? " births, " : " birth ") << "and " << dCount << ((dCount > 1) ? " deaths." : " death.") << endl;
                
                break;
            }
            checkTemp = start;
        }
        everyOther++;
        
        cout << "\n\n\n\n\n\n";
        usleep(100000);
    }
    cout << "Initial population: " << initialPop << endl;
    cout << "Final population: " << initialPop + bCount - dCount << endl;
    
}