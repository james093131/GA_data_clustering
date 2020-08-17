#include "read.h"

int  readfile(vector<string> &s)//讀檔 以讀一行一行的方式來讀取
{
    ifstream file;
    file.open("bezdekIris.data",ios::in);
    int i=0;
    while (!file.eof())
    {   
        string str;
        getline(file, str);
        s.push_back(str);
    i++;
    }
    return i;
}

int getinf(vector<string> s)//用,分割看有幾項
{
    int k=1;
    for(int i=0;i<s[0].size();i++)
    {
        if(s[0][i]==',')
            k++;
        
    }
    return k;
}
void arrangereadfile(vector<vector<string> > &aftsplit ,vector<string> temp,int ind,int item)//資料整理成 2D-vector型式
{
    int split=0;
    for(int i=0;i<ind;i++)
    {
        int k=0;
        split=0;
        while(k<item)
        {
            string s;
            while(temp[i][split]!=',' && split<temp[i].size())
            {
            s.push_back(temp[i][split]);
            split++;
            }
            split++;
            aftsplit[i][k]=s;
            k++;
        }
        
    }
}
vector<string>  make_category(vector<vector<string> > &aftsplit,int ind,int item)//將種類進行分類儲存到vector中
{
    vector<string> check;
    check.push_back(aftsplit[0][item-1]);
    for(int i=1;i<ind;i++)
    {
        int k=0;
        while(k<check.size())
        {
            if(k==check.size()-1 && aftsplit[i][item-1]!=check[k])
            {
                check.push_back(aftsplit[i][item-1]);
            }
            k++;
        }
    }
    return check;
}
void make_clean_data(vector<vector<double> > &clean,vector<vector<string> > aftsplit,vector<string> category,int ind,int item)//將所有資料以double方式儲存
{
    for(int i=0;i<ind;i++)
    {
        for(int j=0;j<item;j++)
        {
            if(j==item-1)
            {
                int k=0;
                while(k<category.size())
                {
                    if(aftsplit[i][j]==category[k])
                    {
                        clean[i][j]=k;
                        break;
                    }
                    k++;
                }
            }
            else{
                clean[i][j]=stod(aftsplit[i][j]);
            }
        }
    }
}