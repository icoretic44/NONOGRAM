#include <bits/stdc++.h>
using namespace std;
const int N = 30;
const int M = 30;
vector<regex> pattern_col;
vector<regex> pattern_row;

int config[N];
vector<vector<string>> sequence_col(M);
vector<vector<string>> sequence_row(N);
vector<vector<string>> config_col(M);
vector<vector<string>> config_row(N);
vector<string> puzzle_row(N);
vector<string> puzzle_col(N);
int brri[N];
int brci[M];
int wrri[N];
int wrci[M];

int bci[M];
int bri[N];

int numblock_col[M];
int numblock_row[N];
int ncol,nrow;

int ip_col[N][N];
int ip_row[N][N];
void extract_data()
{
    cin >> nrow >> ncol;
    for(int i=1;i<=nrow;++i)
    {
        string c;
        int j = 1;
        while(cin >> c && c!="*")
        {
            int x = stoi(c);
            ip_row[i][j] = x;
            numblock_row[i]++;
            ++j;
        }
    }
    for(int i=1;i<=ncol;++i)
    {
        string c;
        int j = 1;
        while(cin >> c && c!="*")
        {
            int x = stoi(c);
            ip_col[i][j] = x;
            numblock_col[i]++;
            ++j;
        }
    }
    return;
}
void data_to_rc()
{
    for(int i=1;i<=nrow;++i)
    {
        int s = 0;
        for(int j=1;ip_row[i][j]!=0;++j)
        {
            s += ip_row[i][j];
        }
        brri[i] = s;
        wrri[i] = ncol - s;
    }
    for(int i=1;i<=ncol;++i)
    {
        int s = 0;
        for(int j=1;ip_col[i][j]!=0;++j)
        {
            s += ip_col[i][j];
        }
        brci[i] = s;
        wrci[i] = nrow - s;
    }
}
void export_to_sequence(int numcell,int j,char x)
{
    string s = "";
    for(int i=1;i<=numcell;++i)
    {
        s += to_string(config[i]);
    }
    if(x=='c')sequence_col[j].push_back(s);
    else sequence_row[j].push_back(s);
    return;
}
void generate_conf(int idx,int numcell,int k,int j,char x)
{
    if(k==0)
    {
        export_to_sequence(numcell,j,x);
        return;
    }
    for(int i=idx;i<=numcell;++i)
    {
        if(config[i]==0 && config[i-1]==0)
        {
            config[i] = 1;
            generate_conf(i+2,numcell,k-1,j,x);
            config[i] = 0;
        }
    }
    return;
} // generate all configuration of column as binary
// with black block is dedicated by 1 and white cell is dedicated by 0
// asume black block like a cell
void convert_config(int n,int (*ip)[M],
                    vector<vector<string>> &sequence,
                    vector<vector<string>> &config_)
{
    for(int i=1;i<=n;++i)
    {
        vector<int> f;
        for(int j=1;ip[i][j]!=0;++j)
        {
            f.push_back(ip[i][j]);
        }
        for(auto x:sequence[i])
        {
            int o = 0;
            string s = "";
            for(auto c:x)
            {
                if(c=='1')
                {
                    for(int z=1;z<=f[o];++z)
                    {
                        s += '1';
                    }
                    ++o;
                }
                else s+= '0';
            }
            config_[i].push_back(s);
        }
    }
}
void setup()
{
    for(int i=1;i<=ncol;++i)
    {
        int numcell = ncol - brci[i] + numblock_col[i];
        generate_conf(1,numcell,numblock_col[i],i,'c');
    }
    for(int i=1;i<=nrow;++i)
    {
        int numcell = ncol - brci[i] + numblock_row[i];
        generate_conf(1,numcell,numblock_row[i],i,'r');
    }
}
void set_constraint(int n,int (*ip)[M],vector<regex> &pattern_)
{
    for(int i=1;i<=n;++i)
    {
        string c = "[0?]*";
        for(int j=1;ip[i][j]!=0;++j)
        {
            string h = "{" + to_string(ip[i][j]) + "}";
            c = c + "[1?]" + h + "[0?]+";
        }
        c.pop_back();
        c += "*";
        regex pattern(c);
        pattern_.push_back(pattern);
        //cout << c << ' ' << (int)pattern_.size() << "\n";
    }
    //cout << "\n";
}
bool check_rule(char x,int i,string s)
{
    i--;
    if(x=='c')
    {
        regex pattern = pattern_col[i];
        return regex_match(s,pattern);
    }
    else
    {
        regex pattern = pattern_row[i];
        return regex_match(s,pattern);
    }
}
void add_puzzle(string s,int curCol)
{
    for(int i=0;i<nrow;++i)
        puzzle_col[curCol][i] = s[i];
    for(int i=1;i<=nrow;++i)
        puzzle_row[i][curCol-1] = s[i-1];
}
void remove_puzzle(int curCol)
{
    for(int i=0;i<nrow;++i)
        puzzle_col[curCol][i] = '?';
    for(int i=1;i<=nrow;++i)
        puzzle_row[i][curCol-1] = '?';
}
void printResult()
{
    for(int i=1;i<=nrow;++i)
    {
        cout << puzzle_row[i] << "\n";
    }
}
void genNonogram(int curCol)
{
    if(curCol==ncol+1)
    {
        printResult();
        exit(0);
    }
    for(auto x:config_col[curCol])
    {
        if(check_rule('c',curCol,x))
        {
            //cout << x << "\n";
            add_puzzle(x,curCol);
            bool flag = true;
            for(int i=1;i<=nrow;++i)
            {
                if(check_rule('r',i,puzzle_row[i])==false)
                {
//                    cout << "This is false " << i << ' ' << x << "\n";
//                    printResult();
                    flag = false;
                    remove_puzzle(curCol);
                    break;
                }
            }
            if(flag) genNonogram(curCol+1);
        }
    }
    if(curCol==1) cout << "No solution!" << "\n";
    return;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("NONOGRAM.INP","r",stdin);
    freopen("NONOGRAM.OUT","w",stdout);
    memset(brri,0,sizeof(brri));
    memset(wrri,0,sizeof(wrri));
    memset(brci,0,sizeof(brci));
    memset(wrci,0,sizeof(wrci));
    memset(bri,0,sizeof(bri));
    memset(bci,0,sizeof(bci));
    memset(ip_col,0,sizeof(ip_col));
    memset(ip_row,0,sizeof(ip_row));
    memset(numblock_col,0,sizeof(numblock_col));
    extract_data();
    data_to_rc();
    setup();
    convert_config(ncol,ip_col,sequence_col,config_col);
    convert_config(nrow,ip_row,sequence_row,config_row);
    set_constraint(ncol,ip_col,pattern_col);
    set_constraint(nrow,ip_row,pattern_row);
    for(int i=1;i<=ncol;++i)
    {
        for(int j=1;j<=nrow;++j)
        {
            puzzle_col[i] += '?';
        }
    }
    for(int i=1;i<=nrow;++i)
    {
        for(int j=1;j<=ncol;++j)
        {
            puzzle_row[i] += '?';
        }
    }
    genNonogram(1);
    return 0;
}
