#include<bits/stdc++.h>
using namespace std;
const int N = 30;
const int M = 30;
int puzzle[N][M];
int brri[N];
int brci[M];
int wrri[N];
int wrci[M];

int bri[N];
int bci[M];

int ip_col[M][N];
int ip_row[N][N];
int ncol,nrow;
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
            ++j;
        }
    }
    return;
}
void compress_data()
{
    for(int i=1;i<=nrow;++i)
    {
        for(int j=1;ip_row[i][j]!=0;++j)
        {
            cout << ip_row[i][j] << "\n";
        }
        cout << "\n";
    }
    for(int i=1;i<=ncol;++i)
    {
        for(int j=1;ip_col[i][j]!=0;++j)
        {
            cout << ip_col[i][j] << "\n";
        }
        cout << "\n";
    }
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
    /*for(int i=1;i<=nrow;++i)
    {
        cout << brri[i] << ' ' << wrri[i] << "\n";
    }
    for(int i=1;i<=ncol;++i)
    {
        cout << brci[i] << ' ' << wrci[i] << "\n";
    }*/
}
bool check_rule_bounding(char c,int i)
{
    if(c=='c')
    {
        if(bci[i] <= brci[i]) return true;
    }
    else
    {
        if(bri[i] <= brri[i]) return true;
    }
    return false;
}
bool set_coordinate(char c,int i,int j,int len)
{
    if(c=='c')
    {
        if(check_rule_bounding(c,j))
        {
            for(int k=i;k<=i+len;++k)
            {
                if(check_rule_bounding('r',k)==false)
                    return false;
            }
        }
        else return false;
        bci[j] += len;
        for(int k=i;k<=i+len;++k)
        {
            bri[k] += 1;
            puzzle[k][j] = 1;
        }
    }
    else if(c=='r')
    {
        if(check_rule_bounding(c,i))
        {
            for(int k=j;k<=j+len;++k)
            {
                if(check_rule_bounding('c',k)==false)
                    return false;
            }
        }
        else return false;
        bci[i] += len;
        for(int k=j;k<=j+len;++k)
        {
            bri[k] += 1;
            puzzle[i][k] = 1;
        }
    }
    return true;
}
void remove(char c,int i,int j,int len)
{
    // remove bci,bri,puzzle
    if(c=='c')
    {
        bci[j] -= len;
        for(int k=i;k<=i+len;++k)
        {
            bri[k] -= 1;
            puzzle[k][j] = 0;
        }
    }
    else if(c=='r')
    {
        bci[i] -= len;
        for(int k=j;k<=j+len;++k)
        {
            bri[k] -= 1;
            puzzle[i][k] = 0;
        }
    }
}
void PrintResult()
{
    for(int i=1;i<=nrow;++i)
    {
        for(int j=1;j<=ncol;++j)
        {
            cout << puzzle[i][j] << ' ';
        }
        cout << "\n";
    }
}
void genNonogram(int curCol)
{
    
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("NONOGRAM.INP","r",stdin);
    //freopen("NONOGRAM.OUT","w",stdout);
    memset(puzzle,0,sizeof(puzzle));
    memset(brri,0,sizeof(brri));
    memset(wrri,0,sizeof(wrri));
    memset(brci,0,sizeof(brci));
    memset(wrci,0,sizeof(wrci));
    memset(bri,0,sizeof(bri));
    memset(bci,0,sizeof(bci));
    memset(ip_col,0,sizeof(ip_col));
    memset(ip_row,0,sizeof(ip_row));
    extract_data();
    //compress_data();
    data_to_rc();
    genNonogram(1);
    return 0;
}

