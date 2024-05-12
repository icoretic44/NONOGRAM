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
    for(int i=1;i<=nrow;++i)
    {
        cout << brri[i] << ' ' << wrri[i] << "\n";
    }
    for(int i=1;i<=ncol;++i)
    {
        cout << brci[i] << ' ' << wrci[i] << "\n";
    }
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
}
bool set_coordinate(char c,int i,int j,int len)
{
    if(c=='c')
    {
        if(check_rule_bounding(c,j))
        {
            for(int k=i;k<=len;++k)
            {
                if(check_rule_bounding("r",k)==false)
                    return false;
            }
        }
        else return false;
        bci[j] += len;
        for(int k=i;k<=len;++k)
        {
            bri[k] += 1;
        }
    }
    else if(c=='r')
    {
        if(check_rule_bounding(c,i))
        {
            for(int k=j;k<=len;++k)
            {
                if(check_rule_bounding("c",k)==false)
                    return false;
            }
        }
        else return false;
        bci[i] += len;
        for(int k=j;k<=len;++k)
        {
            bri[k] += 1;
        }
    }
}
//void solveNONO()
//{
//   for(int i=1;i<=ncol;++i)
//    {
//        for(int j=1;ip_col[i][j]!=0;++j)
//        {
//
//        }
//    }
//    return;
//}
//void backtracking(int x,int y,int len)
//{
////    x = 1;
////    y = i;
////    len = ip_col[i][j] - x + 1;
//    if(x+len-1 <= nrow && y<=ncol)
//    {
//        if(set_coordinate("c",x,y,len)==true)
//        {
//            backtracking(x+1,y,len);
//        }
//    }
//}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("NONOGRAM.INP","r",stdin);
    freopen("NONOGRAM.OUT","w",stdout);
    extract_data();
    compress_data();
    data_to_rc();
    return 0;
}

