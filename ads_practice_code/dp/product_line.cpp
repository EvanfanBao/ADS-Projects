#include<iostream>

using namespace std;

const int N = 3;
//0 1 2 3 --- N-1
//三个stage，就是2个转移time
//Process[0][i] means the process time of line 0 in from stage i to i+1;
//0 <= i <= N-2 -- last but not least stage to the last 
void ProduceLine(int Process[][N-1],int Trans[][N-1]){
    int line;
    int i;
    int MinTime[2][N];
    MinTime[0][0] = 0;
    MinTime[1][0] = 0;
    for(i = 1; i <= N-1;i++)
        for(line = 0; line <= 1;line++)
            MinTime[line][i] = min(MinTime[line][i-1]+Process[line][i-1],MinTime[1-line][i-1]+Trans[1-line][i-1]);
    cout << MinTime[1][N-1];
}
int main(){
    int Process[2][N-1];int Trans[2][N-1];
    Process[0][0] = 5;Process[0][1] = 2;
    Process[1][0] = 1;Process[1][1]= 3;
    Trans[0][0] = 1;Trans[0][1] = 2;
    Trans[1][0] = 2;Trans[1][1] = 3;
    ProduceLine(Process,Trans);
}