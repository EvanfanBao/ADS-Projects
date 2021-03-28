#include<iostream>
#include<vector>
#include<algorithm>
#include<list>

using namespace std;

//字典序---必然想到是利用组合数--也是深度优先--回溯法的重要体现
void PushCombination(int N,int Right,int M,vector<int>& combination,vector< vector<int> >& combinations){
    if(combination.size()==M){
        combinations.push_back(combination);
        return;
    }
    else{
        for(int i = Right;i >= 1;i--){
            combination.push_back(i);
            PushCombination(N,i-1,M,combination,combinations);
            combination.pop_back();
        }
    }
}

void createcomination(int N,int M,vector< vector<int> >& combinations){
    vector<int> combination;
    PushCombination(N,N,M,combination,combinations);
}

int SolvePro(int *claim,int *Guess,int N,int M,int L,vector< vector<int> >& result,vector< vector<int> >combinations){
    int WereWolf_Num(0),Lier_Num(0);
    WereWolf_Num = M;Lier_Num = L;
    vector< vector<int> >::iterator it;
    vector<int>::iterator lit;
    int NotOK = 0;
    for(it = combinations.begin();it != combinations.end();it++){
        for(lit = (*it).begin(); lit != (*it).end();lit++){ 
            Guess[*lit] = -1;  // 根据狼人的组合数，预先猜测狼人
        }
        for(int i = 1;i <= N;i++){
            if(claim[i] * Guess[abs(claim[i])] < 0){     //claim和guess相反，说明claim的人是说谎
                if(Guess[i] == -1)                  //第i个人claim，如果i是狼人，说明狼人说谎
                    WereWolf_Num--;                 //狼人说谎数量+1
                Lier_Num--;                     //说谎者数量+1
            }
        }
        for(int i = 1;i <= N;i++)Guess[i] = 1;  //清空
        if( (WereWolf_Num == 0) || (Lier_Num != 0) || (WereWolf_Num ==M)){ //没有达到要求--
            //说谎人数不够，狼人全都说谎了--减到0，狼人没有说谎.--重新来
            Lier_Num = L;
            WereWolf_Num = M;
            NotOK++;                //记录不满足的个数
            continue;
        }
        else{
            result.push_back(*it);  //这组 组合数列 满足,存进去--表示狼人的位置
            Lier_Num = L;
            WereWolf_Num = M;
        }
    }
    return NotOK;
}

void PrintResult(int NotOK,vector< vector<int> >combinations,vector< vector<int> >result){
    vector<int>::iterator lit;
    if(NotOK != combinations.size()){   //不是全都不满足--有解
        sort(result[0].rbegin(),result[0].rend());
        for(lit = result[0].begin();(*lit) != result[0].back();lit++){
            cout << (*lit) << ' ';
        }
        cout << result[0].back();
    }
    else 
        cout << "No Solution";
}
int main(){
    int N,M,L; //N 玩家，M狼人，L总的说谎者，狼人至少一个说谎
    cin >> N >> M >> L;
    int claim[110];
    vector< vector<int> >result;   //存满足要求的solution---狼人的位置组合
    int Guess[110] = {1};
    vector< vector<int> >combinations; //总的狼人的组合数
    createcomination(N,M,combinations);
    //读取数据
    for(int i = 0; i < N;i++){
        cin >> claim[i+1];
    }
    int NotOK(0);
    NotOK = SolvePro(claim,Guess,N,M,L,result,combinations);
    PrintResult(NotOK,combinations,result);

}