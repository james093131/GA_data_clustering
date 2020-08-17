#include "function.h"
void create(vector<vector<int> > &P,int pop,int category,int ind)//隨機起始種類
{
    for(int i=0;i<pop;i++)
    {
        for(int j=0;j<ind;j++)
        {
            int a=rand()%category;
            P[i][j]=a;
        }
        
    }
}
void Vector_copy(vector<vector<double> > clean_data,vector<vector<double> > &inf,int ind ,int item)
{
    for(int i=0;i<ind;i++)
    {
        for(int j=0;j<item;j++)
        {
            inf[i][j]=clean_data[i][j];
        }
    }
}
void SSE_Category_Data_Sum(vector<vector<double> > inf,vector<vector<double> > &sum,vector<int> P,int ind,int item,int category)
{
    vector<int> k(category);
    for(int i=0;i<ind;i++)
    {
        k[P[i]]++;
    }
    for(int i=0;i<ind;i++)
    {
        for(int j=0;j<item-1;j++)
        {
            sum[P[i]][j] += inf[i][j];
        }
    }
    for(int i=0;i<category;i++)
    {
        for(int j=0;j<item-1;j++)
        {
            sum[i][j]=sum[i][j]/k[i];
        }
    }
}
void SSE_Formula(vector<vector<double> > inf,vector<vector<double> > sum,vector<int> P,vector<double>&fit,int i,int ind,int item)
{
    fit[i]=0;
    for(int j=0;j<ind;j++)
    {
        for(int k=0;k<item-1;k++)
        {
            fit[i]+=pow(inf[j][k]-sum[P[j]][k],2);
        }
    }
}
vector<vector<int> >  tournament(vector<double> fit,vector<vector<int> > P,int pop,int ind,vector<int> Best_P)
{
    vector <int> choose(pop);
    vector<vector<int> > temp;
    temp.resize(pop);
    for(int k=0;k<pop;k++) temp[k].resize(ind);
    int i=0;
    for(int k=0;k<ind;k++)
        {
            temp[i][k] = Best_P[k];
        }
    i++;
    while(i<pop){
        int c1=rand()%(pop);
        int c2=rand()%(pop);
        int chc;
        if(fit[c1]>fit[c2]){
            chc=c2;
        }
        else{
             chc=c1;
        }
        for(int k=0;k<ind;k++)
        {
            temp[i][k] = P[chc][k];
        }
        
        i++;
    }
    return temp;
}
void mutation(vector<int>P,int ind,int category)//隨機選取一點做調換
{
    int c=rand()%ind;
    int a=rand()%category;
    // while(a==P[c])
    // {
    //     a=rand()%category;
    // }
    P[c]=a;
    
    
}
void crossover(vector<vector<int> > &P,int pop,int ind,int category)
{
    int i=0;
    while(i<pop){
        int c1=rand()%ind;
        int c2=rand()%ind;
        int c3=rand()%ind;
        int c4=rand()%ind;
        int c5=rand()%ind;
        int c6=rand()%ind;
        while(c2>c1)
        {
            c2=rand()%ind;
        }
        float t1 = (float) rand() / (RAND_MAX + 1.0);
        for(int k=0;k<ind;k++)
        {
            if(t1<CR){
                if(k>c1||k<c2||k==c3||k==c4||k==c5||k==c6)
                {
                    int temp=P[i][k];
                    P[i][k]=P[i+1][k];
                    P[i+1][k]=temp;
                } 
                else{
                    
                    P[i][k]=P[i][k];
                    P[i+1][k]=P[i+1][k];
                }
            }
           
        }
        float x = (float) rand() / (RAND_MAX + 1.0);
        float y = (float) rand() / (RAND_MAX + 1.0);
        if(x<MR)
        {
            mutation(P[i],ind,category);
        }
        if(y<MR)
        {
             mutation(P[i+1],ind,category);
        }
         i+=2;
    }
}
void Find_best(vector<double> fit,vector<vector<int> > P,vector<int> &Best_P,int ind,int item,int pop,double &best_fit)
{
    double best=100000;
    int best_index;
    for(int i=0;i<pop;i++)
    {
        if(best>fit[i])
        {
            best=fit[i];
            best_index=i;
        }
    }
    best_fit=best;
    for(int i=0;i<ind;i++)
    {
        Best_P[i]=P[best_index][i];
    }
}
void finaloutput(int iteration,int pop,int run,int avgbestvalue,int best,vector<int>result,double START,double END)
{
    fstream file;//寫檔
	file.open("GA_Clustering.txt",ios::app);
    cout<<endl;
    cout<<"Run : "<<run<<endl;
    cout<<"Population : "<<pop<<endl;
    cout<<"Iteration: "<<iteration<<endl;
    cout<<"AVG_SSE : "<<avgbestvalue<<endl;
    cout<<"Execution Time :"<<(END - START) / CLOCKS_PER_SEC<<"(s)"<<endl;
    cout<<"Best_SSE : "<<best<<endl;
    file<<endl;
    file<<"Run : "<<run<<endl;
    file<<"Population : "<<pop<<endl;
    file<<"Iteration: "<<iteration<<endl;
    file<<"AVG_SSE : "<<avgbestvalue<<endl;
    file<<"Execution Time :"<<(END - START) / CLOCKS_PER_SEC<<"(s)"<<endl;
    file<<"Best_SSE : "<<best<<endl;
    file<<"Category_Result : "<<endl;
    for(int i=0;i<result.size();i++)
    {
        cout<<result[i]<<' ';
        file<<result[i]<<' ';
        if(i==49||i==99)
        {
            cout<<endl;
            file<<endl;
        }
            
    }
}