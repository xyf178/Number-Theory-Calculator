#include<bits/stdc++.h>
using namespace std;
#define int long long
char next(char p){
    if(p=='-') return '\\';
    if(p=='\\') return '/';
    if(p=='/') return '-';
}
struct loader{
    clock_t cstart;
    char progress='-';
    loader(string p){
        cout<<p<<"... -";
        cstart=clock();
    }
    void load(){
        if(clock()-cstart>=150){
            cout<<"\b"<<next(progress);
            cstart=clock();
            progress=next(progress);
        }
    }
    void kill(){
        cout<<"\b\b"<<"Done."<<endl;
    }
};
void fast(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
void file(string name){
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}
bool np[100009];
int prime[100009],cnt;
void primesieve(){
    loader l("Sieving primes");
    cnt=0;
    np[1]=1;
    for(int i=2;i<=100000;i++){
        if(!np[i]) prime[++cnt]=i;
        l.load();
        for(int j=1;j<=cnt;j++){
            l.load();
            if(i*prime[j]>100000) break;
            else np[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
    ofstream fout("prime");
    fout<<"1 100000"<<endl;
    for(int i=1;i<=100000;i++){
        fout<<!np[i]<<endl;
        l.load();
    }
    fout.close();
    l.kill();
}
int miu[100009];
int primemiu[100009],cntmiu;
bool npmiu[100009];
void getmiu(){
    loader l("Sieving miu");
    miu[1]=1;
    for(int i=2;i<=100000;i++){
        if(!npmiu[i]) primemiu[++cntmiu]=i,miu[i]=-1;
        l.load();
        for(int j=1;j<=cntmiu;j++){
            l.load();
            if(i*primemiu[j]>100000) break;
            npmiu[i*primemiu[j]]=1;
            if(i%primemiu[j]==0){
                miu[i*primemiu[j]]=0;
                break;
            }
            else miu[i*primemiu[j]]=-miu[i];
        }
    }
    ofstream fout("miu");
    fout<<"1 100000"<<endl;
    for(int i=1;i<=100000;i++){
        l.load();
        fout<<miu[i]<<endl;
    }
    fout.close();
    l.kill();
}
int phi[100009];
int primephi[100009],cntphi;
bool npphi[100009];
void getphi(){
    loader l("Sieving phi");
    phi[1]=1;
    for(int i=2;i<=100000;i++){
        if(!npphi[i]) primephi[++cntphi]=i,phi[i]=i-1;
        l.load();
        for(int j=1;j<=cntphi&&i*primephi[j]<=100000;j++){
            l.load();
            npphi[i*primephi[j]]=1;
            if(i%primephi[j]==0){
                phi[i*primephi[j]]=phi[i]*primephi[j];
                break;
            }
            else phi[i*primephi[j]]=phi[i]*(primephi[j]-1);
        }
    }
    ofstream fout("phi");
    fout<<"1 100000"<<endl;
    for(int i=1;i<=100000;i++){
        l.load();
        fout<<phi[i]<<endl;
    }
    fout.close();
    l.kill();
}
void onesieve(){
    loader l("Printing ones");
    ofstream fout("1");
    fout<<"1 100000"<<endl;
    for(int i=1;i<=100000;i++){
        l.load();
        fout<<1<<endl;
    }
    fout.close();
    l.kill();
}
void idsieve(){
    loader l("Printing ids");
    ofstream fout("id");
    fout<<"1 100000"<<endl;
    for(int i=1;i<=100000;i++){
        l.load();
        fout<<i<<endl;
    }
    fout.close();
    l.kill();
}
void eq1sieve(){
    loader l("Printing eq1");
    ofstream fout("eq1");
    fout<<"1 100000"<<endl;
    for(int i=1;i<=100000;i++){
        l.load();
        fout<<(i==1)<<endl;
    }
    fout.close();
    l.kill();
}
signed main(){
    // fast();
//	file("");
    primesieve();
    getmiu();
    getphi();
    onesieve();
    idsieve();
    eq1sieve();
    return 0;
}