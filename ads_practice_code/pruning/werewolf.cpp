#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// N players, M werewolves, L liars.
// at least one, not all werewolves are lying

int wolf_lier = 0;
int lier = 0;
int N = 0,M = 0,L = 0;

vector<int> human;

bool Solve(vector<int>& claim, vector<int>& werewolf,int level);
bool check(bool NoLie,int player,int level,vector<int>& werewolf);
bool IntroSolve(vector<int>& claim,vector<int>& werewolf);

int main(){
    int value;
    bool Find;
    vector<int> claim,werewolf;
    cin >> N >> M >> L;
    for(int i = 0; i < N;i++){
        cin >> value;
        claim.push_back(value);
    }

    Find = IntroSolve(claim,werewolf);
    //cout << human.size();
    //多个的处理我真不会
    if(Find){
        for(int i = 0; i < werewolf.size();i++)
            cout << werewolf[i] << ' ';
    }
    else cout << "No Solution";
}

bool IntroSolve(vector<int>& claim,vector<int>& werewolf){
    bool found = false;
    werewolf.push_back(1); //first one is werewolf
    found = Solve(claim,werewolf,0);
    if(!found){
        werewolf.clear();
        human.push_back(1);  //first is human
        found = Solve(claim,werewolf,0);
    }
    return found;
}

bool Solve(vector<int>& claim, vector<int>& werewolf,int level){
    bool OK = false, FindSolution = false;bool add_w_l = false,add_w=false,add_h=false;
    vector<int>::iterator it;
    if(level == N && wolf_lier >= 1 && wolf_lier < M && lier == L,werewolf.size() == M)  
        return true;
    //true claim[level] = true
    OK = check(true,claim[level],level,werewolf);
    if(OK && claim[level] < 0){
        it = find(werewolf.begin(),werewolf.end(),claim[level]*(-1));
        if(it == werewolf.end())  // 前面没有人声明他是狼
        {
            werewolf.push_back(claim[level]*(-1));
            add_w = true;
        }

        FindSolution = Solve(claim,werewolf,level+1);
        if(!FindSolution){
            if(add_w == true)werewolf.pop_back();
            add_w = false;
        }
    }
    else if(OK && claim[level] > 0){
        it = find(human.begin(),human.end(),claim[level]);
        if(it == human.end())  // 还没人声明，就先加上去
        {
            human.push_back(claim[level]);
            add_h = true;
        }
        FindSolution = Solve(claim,werewolf,level+1);
        if(!FindSolution){
            if(add_h == true)
                human.pop_back();
            add_h = false;
        }
    }

    //false claim[level] = false -- liar
    
    if(!FindSolution){
        OK = check(false,claim[level],level,werewolf);
        if(OK && claim[level] > 0){
            lier++;
            //find if it is wolf lier
            it = find(werewolf.begin(),werewolf.end(),level+1);
            if(it != werewolf.end()) {wolf_lier++;add_w_l = true;}
            ////////////
            it = find(werewolf.begin(),werewolf.end(),claim[level]);
            if(it == werewolf.end())  // 前面没有人声明他是狼
            {
                werewolf.push_back(claim[level]);
                add_w = true;
            }

            FindSolution = Solve(claim,werewolf,level+1);
            if(!FindSolution)
            {   
                lier--;
                if(add_w_l==true)wolf_lier--;
                add_w_l = false;
                if(add_w == true)werewolf.pop_back();
                add_w = false;
            }
        }
        else if(OK && claim[level] < 0){
            lier++;
            it = find(werewolf.begin(),werewolf.end(),level+1);
            if(it != werewolf.end()) {wolf_lier++;add_w_l = true;}

            it = find(human.begin(),human.end(),claim[level]*(-1));
            if(it == human.end())  // 还没人声明，就先加上去
            {
                human.push_back(claim[level]*(-1));
                add_h = true;
            }
            FindSolution = Solve(claim,werewolf,level+1);
            if(!FindSolution){
                lier--;
                if(add_w_l==true)
                wolf_lier--;
                add_w_l = false;
                if(add_h == true)
                    human.pop_back();
                    add_h = false;
                }
        }
    }
    return FindSolution;
}

bool check(bool NoLie,int player,int level,vector<int>& werewolf){
    bool ret = false;
    int wolf_lier_tmp = wolf_lier_tmp;
    vector<int>::iterator it;
    vector<int>::iterator humit;
    if(NoLie){  // true claim
        if(player < 0){ //wolf
            it = find(werewolf.begin(),werewolf.end(),player*-1);
            humit = find(human.begin(),human.end(),player*(-1));
            if(humit != human.end())return false;  //contradict to previous claim
            if(it != werewolf.end())return true;  // accord with previous claim, no modification 
            else return (werewolf.size() + 1) <= M;  //see if can add one wolf  
        }
        else if(player > 0){
            it = find(werewolf.begin(),werewolf.end(),player);
            if(it != werewolf.end()) return false; //human, contradiction   
            else return true;               
        }
    }
    else if(!NoLie){  // false claim
        it = find(werewolf.begin(),werewolf.end(),level+1);
        if(it != werewolf.end()) wolf_lier_tmp++; // if the claimer is wolf
        ret = (lier + 1 <= L) && (wolf_lier_tmp < M); // wolf_lie +1 .. .lier +1
        if(player > 0){ //wolf
            it = find(werewolf.begin(),werewolf.end(),player);
            humit = find(human.begin(),human.end(),player);
            if(humit != human.end())return false;  //contradict to previous claim
            if(it != werewolf.end())return true;  // accord with previous claim, no modification 
            else return (werewolf.size() + 1) <= M;  //see if can add one wolf  
        }
        else if(player < 0){
            it = find(werewolf.begin(),werewolf.end(),player*-1);
            if(it != werewolf.end())return false; // contradict
            else return true;
        }
    }
    return ret;
}



































