#include <iostream>
#include <vector>
using namespace std;
class QueensProblem
{
    vector< vector <int> > chessTable;
    int numOfQueen = 0;
public:
    QueensProblem(int _numOfQueens);
    void solve();
private:
    bool setQueens(int colIndex);
    bool isPlaceValid(int rowIndex,int colIndex)const;
    void printQueens() const;
};

QueensProblem::QueensProblem(int _numOfQueens)
    :numOfQueen(_numOfQueens)
{
    chessTable.resize(numOfQueen);
    for(auto &chessRow: chessTable)
        chessRow.resize(numOfQueen);
}

void QueensProblem::solve()
{
    if(setQueens(0)){
        printQueens();
    }
    else{
        cout << "There is no solution...\n";
    }
}

bool QueensProblem::setQueens(int colIndex){
    if(colIndex == numOfQueen)
        return true;
    for(int rowIndex = 0;rowIndex < numOfQueen;++rowIndex){
        if(isPlaceValid(rowIndex,colIndex)){
            chessTable[rowIndex][colIndex] = 1;
            if(setQueens(colIndex+1)){
                return true;
            }
        }
        chessTable[rowIndex][colIndex] = 0;
    }
    return false;
}

bool QueensProblem::isPlaceValid(int rowIndex,int colIndex)const
{
    for(int i = 0; i < colIndex;i++)
        if(chessTable[rowIndex][i] == 1)
            return false;
    for(int i = rowIndex, j = colIndex;i >= 0 && j >= 0;i--,j--){
        if(chessTable[i][j] == 1)
            return false;
    }
    for(int i = rowIndex,j = colIndex;i < numOfQueen && j >= 0;i++,j--){
        if(chessTable[i][j] == 1)
            return false;
    }
}

void QueensProblem::printQueens()const
{
    for(size_t i = 0; i < chessTable.size();i++){
        for(size_t j = 0;j < chessTable.size();j++){
            if(chessTable[i][j] == 1){
                cout << " * ";
            }
            else{
                cout << " - ";
            }
        }
        cout << "\n";
    }
}


int main(){
    QueensProblem problem(100);
    problem.solve();
}