#include<iostream>
#include<vector>
#include<algorithm>
#include<list>

using namespace std;


vector< vector<int> > combinations;
//字典序
void PushCombination(int N,int Right,int M,vector<int>& combination){
    if(combination.size()==M){
        combinations.push_back(combination);
        return;
    }
    else{
        for(int i = Right;i >= 1;i--){
            combination.push_back(i);
            PushCombination(N,i-1,M,combination);
            combination.pop_back();
        }
    }
}

void createcomination(int N,int M){
    vector<int> combination;
    PushCombination(N,N,M,combination);
}


void PrintResult(int NotOK,vector< vector<int> >combinations,vector< vector<int> >result){
    vector<int>::iterator lit;
    if(NotOK != combinations.size()){   //不是全都不满足--有解
        sort(result[0].rbegin(),result[0].rend());
        for (int i = 0; i < result[0].size() - 1; ++i) {           
            cout << result[0][i] << ' ';
        }
        cout << result[0].back();
    }
    else 
        cout << "No Solution";
}

int main(){
    int N,M,L; //N 玩家，M狼人，L总的说谎者，狼人至少一个说谎
    int WereWolf_Num,Lier_Num;
    cin >> N >> M >> L;
    WereWolf_Num = M;  //
    Lier_Num = L;      //同理
    int claim[200];
    int NotOK = 0;
    vector< vector<int> >result;
    vector<int> Guess(N+1,1);
    
    for(int i = 0; i < N;i++){
        cin >> claim[i+1];
    }

    createcomination(N,M);  //生成组合数

    vector< vector<int> >::iterator it;     //迭代器迭代--也可以用c++11的 类似python的迭代
    vector<int>::iterator lit;
    
    //迭代
    for(it = combinations.begin();it != combinations.end();it++){
        for(auto p :*it){ 
            Guess[p] = -1;  // 根据狼人的组合数，预先猜测狼人
        }
        for(int i = 1;i <= N;i++){
            if(claim[i] * Guess[abs(claim[i])] < 0){     //claim和guess相反，说明claim的人是说谎
                if(Guess[i] == -1)                  //第i个人claim，如果i是狼人，说明狼人说谎
                    WereWolf_Num--;                 //狼人数量减1
                Lier_Num--;                     //说谎者数量减1
            }
        }

        Guess.assign(N+1,1); //重新设置为1，这个主要是给后面一轮用的，人类为1，狼人为-1
        if( (Lier_Num != 0) || (WereWolf_Num == 0) || (WereWolf_Num ==M)){ //没有达到要求--
            //说谎人数不够，狼人全都说谎了--减到0，狼人没有说谎.
            Lier_Num = L;
            WereWolf_Num = M;
            NotOK++;                //记录不满足的个数
            continue;
        }else{
            result.push_back(*it);  //这组 组合数列 满足,存进去--表示狼人的位置
            Lier_Num = L;
            WereWolf_Num = M;
        }
    }
    /*
    if(NotOK != combinations.size()){   //不是全都不满足--有解
         
        sort(result[0].rbegin(),result[0].rend());
        for(lit = result[0].begin();(*lit) != result[0].back();lit++){
            cout << (*lit) << ' ';
        }
        cout << result[0].back();
    }
    else 
        cout << "No Solution";
    */
   PrintResult(NotOK,combinations,result);
}