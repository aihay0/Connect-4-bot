#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

int po[100];
int power(int x,int y){
    if(y==0)
        return 1;
    if(po[y])
        return po[y];
    int z=power(x,y/2);
    z*=z;
    if(y%2)
        z*=x;
    return po[y]=z;
}
struct board{
    string str;
    bool turn;
    int movesplayed;
    int won;
    int height[7];
    int hash1,hash2,hash3;
    int canh;
    int scr;
    void resetboard(){
        this->str="..........................................";
        this->turn=0;
        this->movesplayed=0;
        this->won=0;
        this->hash1=0;
        this->hash2=0;
        this->hash3=0;
        this->canh=(1<<7)-1;
        this->scr=0;
        for(int i=0;i<7;i++)
            this->height[i]=0;
    }
    void domove(int col){
        col--;
        int row=this->height[col];
        int idx=row*7+col;
        this->height[col]++;
        if((this->height[col])==6)
            this->canh-=(1<<col);
        this->movesplayed++;
        this->str[idx]=(turn?'O':'X');
        int x=power(3,(row%2)*7+col)*((this->turn)+1);
        if(row<2)
            hash1+=x;
        else if(row<4)
            hash2+=x;
        else
            hash3+=x;
        int zz=0;
        for(int i=max(col-3,0);(this->won)==0&&i<=min(3,col);i++){
            if(str[row*7+i]==str[idx]&&str[row*7+i+1]==str[idx]&&str[row*7+i+2]==str[idx]&&str[row*7+i+3]==str[idx])
                this->won=(1-2*(this->turn))*(42-(this->movesplayed));
            if(str[row*7+i]==str[idx])
                zz++;
            if(str[row*7+i+1]==str[idx])
                zz++;
            if(str[row*7+i+2]==str[idx])
                zz++;
            if(str[row*7+i+3]==str[idx])
                zz++;
        }
        for(int i=max(row-3,0);(this->won)==0&&i<=min(2,row);i++){
            if(str[i*7+col]==str[idx]&&str[(i+1)*7+col]==str[idx]&&str[(i+2)*7+col]==str[idx]&&str[(i+3)*7+col]==str[idx])
                this->won=(1-2*(this->turn))*(42-(this->movesplayed));
            if(str[i*7+col]==str[idx])
                zz++;
            if(str[(i+1)*7+col]==str[idx])
                zz++;
            if(str[(i+2)*7+col]==str[idx])
                zz++;
            if(str[(i+3)*7+col]==str[idx])
                zz++;
        }
        for(int i=0;(this->won)==0&&i<4;i++){
            if(row-i>=0&&col-i>=0&&row-i+3<6&&col-i+3<7&&str[(row-i)*7+col-i]==str[idx]&&str[(row-i+1)*7+col-i+1]==str[idx]&&str[(row-i+2)*7+col-i+2]==str[idx]&&str[(row-i+3)*7+col-i+3]==str[idx])
                this->won=(1-2*(this->turn))*(42-(this->movesplayed));
            if(str[(row-i)*7+col-i]==str[idx])
                zz++;
            if(str[(row-i+1)*7+col-i+1]==str[idx])
                zz++;
            if(str[(row-i+2)*7+col-i+2]==str[idx])
                zz++;
            if(str[(row-i+3)*7+col-i+3]==str[idx])
                zz++;
            if(row-i>=0&&col+i-3>=0&&row-i+3<6&&col+i<7&&str[(row-i)*7+col+i]==str[idx]&&str[(row-i+1)*7+col+i-1]==str[idx]&&str[(row-i+2)*7+col+i-2]==str[idx]&&str[(row-i+3)*7+col+i-3]==str[idx])
                this->won=(1-2*(this->turn))*(42-(this->movesplayed));
            if(str[(row-i)*7+col-i]==str[idx])
                zz++;
            if(str[(row-i+1)*7+col-i-1]==str[idx])
                zz++;
            if(str[(row-i+2)*7+col-i-2]==str[idx])
                zz++;
            if(str[(row-i+3)*7+col-i-3]==str[idx])
                zz++;
        }
        if((this->turn))
            zz*=-1;
        this->scr+=0;
        this->turn=!(this->turn);
    }
    bool can(int x){
        x--;
        return ((((this->canh))>>x)&1);
    }
}curboard;
int MOD=10000019,MOD2=10000079;
int mp[10000100],mp2[10000100];
void printboard(board brd=curboard){
    //system("CLS");
    for(int i=5;i>=0;i--){
        for(int j=0;j<7;j++)
            cout<<brd.str[i*7+j]<<" ";
        cout<<"\n\n";
    }
    cout<<"1 2 3 4 5 6 7\n";
}
int tim,curtime,bestmove;
vector<int> v;
vector<int> v2;
int minimax(board brd=curboard,int depth=0,int alpha=-100000000,int beta=1000000000,int tard=0){
    if(brd.won||brd.movesplayed==42)
        return brd.won*10000;
    if(depth>tard||GetTickCount()-curtime>2000)
        return brd.scr*(brd.movesplayed<10);
    long long xx=brd.hash1*4782969ll%MOD*4782969ll%MOD+brd.hash2*4782969ll%MOD+brd.hash3;
    xx%=MOD;
    long long yy=brd.hash1*4782969ll%MOD2*4782969ll%MOD2+brd.hash2*4782969ll%MOD2+brd.hash3;
    yy%=MOD2;
    int &ret=mp[xx];
    if(ret&&mp2[yy]==ret&&depth>1&&abs(ret)>10000)
        return ret;
    if(brd.turn==0){
        int mx=-100000000,mxi=0;
        for(int i=0;i<v.size()&&depth;i++){
            if(!brd.can(v[i]))
                continue;
            board brd2=brd;
            brd2.domove(v[i]);
            if(brd2.won){
                bestmove=v[i];
                return ret=mp2[yy]=brd2.won*10000;
            }
        }
        for(int i=0;i<v.size();i++){
            if(!brd.can(v[i]))
                continue;
            board brd2=brd;
            brd2.domove(v[i]);
            int val=minimax(brd2,depth+1,alpha,beta,tard);
            if(mx<val){
                mx=val;
                mxi=v[i];
            }
            alpha=max(alpha,val);
            if(alpha>=beta)
                break;
        }
        if(depth==0){
            curboard.domove(mxi);
            printboard(curboard);
        }
        bestmove=mxi;
        return ret=mp2[yy]=mx;
    }
    else{
        int mx=100000000,mxi=0;
        for(int i=0;i<v.size()&&depth;i++){
            if(!brd.can(v[i]))
                continue;
            board brd2=brd;
            brd2.domove(v[i]);
            if(brd2.won){
                bestmove=v[i];
                return ret=mp2[yy]=brd2.won*10000;
            }
        }
        for(int i=0;i<v.size();i++){
            if(!brd.can(v[i]))
                continue;
            board brd2=brd;
            brd2.domove(v[i]);
            int val=minimax(brd2,depth+1,alpha,beta,tard);
            if(mx>val){
                mx=val;
                mxi=v[i];
            }
            beta=min(beta,val);
            if(alpha>=beta)
                break;
        }
        if(depth==0){
            curboard.domove(mxi);
            printboard(curboard);
        }
        bestmove=mxi;
        return ret=mp2[yy]=mx;
    }
}

int main()
{
    curboard.resetboard();
    v={4,5,3,7,1,6,2};
    while(!curboard.won&&curboard.movesplayed<42){
        printboard();
        if(curboard.turn){
            int x;
            cin>>x;
            curboard.domove(x);
            system("CLS");
            if(x!=4)
                v={5,3,7,1,4,6,2};
        }
        else if(curboard.movesplayed>1){
            int curdepth=8;
            curtime=GetTickCount();
            int x=0;
            while(GetTickCount()-curtime<2000){
                x=minimax(curboard,1,-100000000,100000000,curdepth+1);
                curdepth++;
            }
            curboard.domove(bestmove);
            system("CLS");
            cout<<"Current depth: "<<curdepth<<"\nCurrent evaluation: "<<x<<"\nMove played: "<<bestmove<<"\n";
        }
        else{
            curboard.domove(4);
            system("CLS");
        }
    }
    printboard();
    return 0;
}
