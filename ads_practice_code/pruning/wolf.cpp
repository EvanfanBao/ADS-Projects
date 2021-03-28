#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void backtrack(int n, int start, int m, vector<int>& path);

vector< vector<int> > res; // to store the combine

vector< vector<int> > combine(int n, int m) {
    vector<int> path;
    backtrack(n, n, m, path);
    return res;
} // compute the combine

void backtrack(int n, int start, int m, vector<int>& path) {
    if (path.size() == m) {
        res.push_back(path);
        return;
    }
    for (int i = start; i >= 1; --i) {
        path.push_back(i);
        backtrack(n, i-1, m, path);
        path.pop_back();
    }
}

int main() {
    int n, m, l; //N-玩家个数，M-狼的个数，L-说谎者个数
    int m_count, l_count; // 狼说谎者  与 总说谎者---从高位开始。狼说不能全满，也不能为0，总说谎必须最终为L
    cin >> n >> m >> l;     //读入数据
    m_count = m;
    l_count = l;

    vector<int> ass(n+1);   // vector的一个用法 n+1位向量--能用变量赋值
    vector< vector<int> > result; //真实的保存狼人的序列==就是从前面组合数里面取出来    
    vector<int> pre(n+1, 1);      //设置n+1为vector 全1，是预处理，保证一开始为1--然后根据狼人的序列设置为-1就行了

    int t;
    for (int i = 0; i < n; i++) { // 每个人的断言--仍然是从1开始，表示第一个人，对应
        cin >> t;
        ass[i+1] = t;
    }

    combine(n, m);          //生成组合数

    int count = 0;          //表示不符合要求的序列的个数--序列总个数为狼人的个数
    for (auto one: res) {   //迭代序列的总向量---所有的组合情况
        for (auto i: one) { //迭代序列向量本身--狼人的位置
            pre[i] = -1;    //设置狼人位置为-1
        }
        for (int i = 1; i <= n; i++) {
            if (ass[i] * pre[abs(ass[i])] < 0) {  //声明与实际相反--声明者说谎
                if (pre[i] == -1)                 //判断说谎者是否为狼人
                    m_count--;                    //记录狼人个数
                l_count--;                        //说谎者个数
            }

        }
        pre.assign(n + 1, 1);                    //每轮迭代后，重新初始化
        if ((l_count != 0) || (m_count == 0) || (m_count == m)) {   //判断约束条件，总说谎人数，与狼人人数
            l_count = l;                                            //重新初始化
            m_count = m;                                            //重新初始化
            count ++;                                               //不满足约束条件--增加一个
            continue;
        } else {                        
            result.push_back(one);     //将正确的结果进入
            l_count = l;                //重新初始化
            m_count = m;
        }
    }

    if (count != res.size()) {                      //不是所有的情况都不行
        int s = result[0].size();                   //输出--也可以就是狼的个数
        sort(result[0].rbegin(), result[0].rend()); //排序--result[0]就是字典序第一个--输出要从大到小
        for (int i = 0; i < s - 1; ++i) {           
            cout << result[0][i] << ' ';
        }
        cout << result[0][s - 1];
    }
    else {
        cout << "No Solution";
    }
}


