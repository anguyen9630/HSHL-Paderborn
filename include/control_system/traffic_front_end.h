#include <iostream>
using namespace std;
char Map[35][35];
int i,j;

void InitMap()
{
    for(i=0;i<35;i++)
        for(j=0;j<35;j++)
            Map[i][j]=' ';
    
    for(j=0;j<15;j++)
    {
        Map[14][j]='*';
        Map[14][j+18]='*';
        Map[16][j]='*';
        Map[16][j+18]='*';
        Map[18][j]='*';
        Map[18][j+18]='*';
    }
    
    for(i=0;i<15;i++)
    {
        Map[i][14]='*';
        Map[i][18]='*';
        Map[i][16]='*';
        Map[i+18][16]='*';
        Map[i+18][14]='*';
        Map[i+18][18]='*';
    }
    
    for(i=0;i<35;i++)
    {
        for(j=0;j<35;j++)
        {
            cout << Map[i][j];
            cout << ' ';
        }

        cout << '\n';
    }
}


