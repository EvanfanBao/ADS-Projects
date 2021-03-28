#include <iostream>
#include <vector>

using namespace std;
class QueenProblem{
public:
    QueenProblem(int _number);
    vector< vector<int> > chessboard;
    int number;
    void Solve();
private:
    bool IsValid(int row, int col);
    bool SetQueens(int row);
    void printQueens() const;
};

void QueenProblem:: Solve(){
    // start from 0 row
    if(SetQueens(0)){
        printQueens();
    }
    else cout << "There is no solution...\n";
}
void QueenProblem::printQueens() const {
    for(size_t i = 0;i < chessboard.size();i++)
        for(size_t j = 0;j < chessboard.size();j++)
            if(chessboard[i][j] == 1)
                cout << " * ";
            else cout << " - ";
        cout << "\n";
}

QueenProblem::QueenProblem(int _number):number(_number){
    chessboard.resize(number);
    // 初始化棋盘
    for(auto i:chessboard)
        i.resize(number);
};


// 设置第i行的queen---
bool QueenProblem::SetQueens(int row){
    if(row == number) return true;  //已经设置了N个queen了 第N+1为真
    
    for(int col = 0;col < number;++col){
        if(IsValid(row,col)){
            chessboard[row][col] = 1;
            if(SetQueens(row+1))
                return true;
            chessboard[row][col] = 0;
        }   
    }
    return false;
}

bool QueenProblem::IsValid(int row, int col){
    // 前面的不能和当前的在同一列---这个在slide中的gametree中是直接没有的
    for(int i = 0; i < row;i++){
        if(chessboard[i][col] == 1)return false;
    }
    for(int i = row,j = col;i >= 0 && j >= 0;i--,j--){
        if(chessboard[i][j] == 1)
            return false;
    }
    for(int i = row,j = col;i < number && j >= 0;i++,j--){
        if(chessboard[i][j] == 1)
            return false;
    }
    return true;
}

int main(){
    int n = 4;
    QueenProblem qp(4);
    qp.Solve();
}