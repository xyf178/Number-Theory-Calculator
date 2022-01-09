#include<bits/stdc++.h>
#include<windows.h>
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
int err=0;
struct Function{
    int l,r;
    int x[100009];
    int& operator[](int i){
        if(i<l){
            err=1;
            return x[0];
        }
        if(i>r){
            err=2;
            return x[r-l];
        }
        err=0;
        return x[i-l];
    }
    Function(int _l,int _r,string s){
        l=_l,r=_r;
        name=s;
    }
    Function(){}
    string name;
    void print(int _l,int _r){
        cout<<name<<"["<<_l<<","<<_r<<"]"<<endl;
        for(int i=_l;i<=_r;i++) cout<<name<<"["<<i<<"]"<<"="<<x[i-l]<<endl;
        cout<<endl;
    }
    bool errrrrr=0;
    void reset(){
        errrrrr=0;
        name="";
        l=r=0;
        memset(x,0,sizeof(x));
    }
};
Function a[20];
int cnt=0;
int find(string nm){
    for(int i=1;i<=cnt;i++){
        if(a[i].name==nm) return i;
    }
    return 0;
}
void init(){
    ifstream data("data");
    string nm;
    while(data>>nm){
        ifstream in(nm);
        if(!in) continue;
        if(find(nm)) continue;
        int l,r;
        in>>l>>r;
        a[++cnt]=Function(l,r,nm);
        for(int j=l;j<=r;j++) in>>a[cnt][j];
    }
}
Function operator *(Function _a,Function _b){
    Function _c;
    _c.l=max(_a.l,_b.l);
    _c.r=min(_a.r,_b.r);
    for(int i=_c.l;i<=_c.r;i++){
        _c[i]=_a[i]*_b[i];
    }
    return _c;
}
Function Dirichlet(Function _a,Function _b){
    loader l("Calculating");
    Function _c;
    _c.l=max(max(_a.l,_b.l),1ll);
    _c.r=min(_a.r,_b.r);
    for(int i=_c.l;i<=_c.r;i++){
        int stat=0;
        for(int d=1;d*d<=i;d++){
            l.load();
            if(i%d==0){
                _c[i]+=_a[d]*_b[i/d];
                if(err==1){
                    l.kill();
                    cout<<"Calculation aborted."<<endl;
                    _c.errrrrr=1;
                    return _c;
                }
                if(err==2){
                    stat=1;
                    break;
                }
                if(d*d!=i){
                    _c[i]+=_a[i/d]*_b[d];
                    if(err==1){
                        cout<<"Calculation aborted."<<endl;
                        _c.errrrrr=1;
                        return _c;
                    }
                    if(err==2){
                        stat=1;
                        break;
                    }
                }
            }
            if(stat){
                _c.r=i-1;
                break;
            }
        }
    }
    l.kill();
    return _c;
}
Function operator +(Function _a,Function _b){
    Function _c;
    _c.l=max(_a.l,_b.l);
    _c.r=min(_a.r,_b.r);
    for(int i=_c.l;i<=_c.r;i++){
        _c[i]=_a[i]+_b[i];
    }
    return _c;
}
Function operator -(Function _a,Function _b){
    Function _c;
    _c.l=max(_a.l,_b.l);
    _c.r=min(_a.r,_b.r);
    for(int i=_c.l;i<=_c.r;i++){
        _c[i]=_a[i]-_b[i];
    }
    return _c;
}
Function operator /(Function _a,Function _b){
    Function _c;
    _c.l=max(_a.l,_b.l);
    _c.r=min(_a.r,_b.r);
    for(int i=_c.l;i<=_c.r;i++){
        if(_b[i]==0){
            cout<<"Division by zero."<<endl;
            _c.errrrrr=1;
            return _c;
        }
        if(_a[i]%_b[i]!=0){
            cout<<"Remainder is not zero."<<endl;
            _c.errrrrr=1;
            return _c;
        }
        _c[i]=_a[i]/_b[i];
    }
    return _c;
}
Function call(Function _a,Function _b){//_c(i)=_a(_b(i))
    Function _c;
    _c.l=_b.l;
    _c.r=_b.r;
    for(int i=_c.l;i<=_c.r;i++){
        _c[i]=_a[_b[i]];
        if(err==1){
            cout<<"Calculation aborted."<<endl;
            _c.errrrrr=1;
            return _c;
        }
        if(err==2){
            _c.r=i-1;
            break;
        }
    }
    return _c;
}
Function sum(Function _a){
    Function _b;
    _b.l=_a.l;
    _b.r=_a.r;
    _b[_b.l]=_a[_a.l];
    for(int i=_b.l+1;i<=_b.r;i++){
        _b[i]=_b[i-1]+_a[i];
    }
    return _b;
}
bool operator ==(Function _a,Function _b){
    for(int i=max(_a.l,_b.l);i<=min(_a.r,_b.r);i++){
        if(_a[i]!=_b[i]){
            cout<<_a.name<<"["<<i<<"]="<<_a[i]<<" and "<<_b.name<<"["<<i<<"]="<<_b[i]<<endl;
            return 0;
        }
    }
    return 1;
}
signed main(){
    system("color 02");
    cout<<"Initializing..."<<endl;
    system(".\\sieve.exe");
    init();
    while(1){
        cout<<"Number Theory Calculator >> ";
        string op;
        cin>>op;
        for(int i=0;i<op.size();i++){
            op[i]=tolower(op[i]);
        }
        if(op=="exit"||op=="quit"||op=="q"){
            cout<<"Thanks for using."<<endl;
            system("color 07");
            system("pause");
            break;
        }
        else if(op=="print"){
            cout<<"Input your Function >> ";
            string q;
            cin>>q;
            int f=find(q);
            if(f){
                cout<<a[f].name<<" is on ["<<a[f].l<<","<<a[f].r<<"]"<<endl;
                cout<<"Input your left and right bound >> ";
                int l,r;
                cin>>l>>r;
                if(l<a[f].l){
                    cout<<"Left bound is too small."<<endl;
                    continue;
                }
                if(r>a[f].r){
                    cout<<"Right bound is too large."<<endl;
                    continue;
                }
                a[f].print(l,r);
            }
            else{
                cout<<"No such Function."<<endl;
            }
        }
        else if(op=="*"){
            cout<<"Input two Functions >> ";
            string _x,_y;
            cin>>_x>>_y;
            int x=find(_x),y=find(_y);
            if(x&&y){
                a[++cnt]=a[x]*a[y];
                if(!a[cnt].errrrrr){
                    cout<<"Name your new Function >> ";
                    string nm;
                    cin>>nm;
                    while(find(nm)){
                        cout<<"Name already used."<<endl;
                        cout<<"Input a new one >> ";
                        cin>>nm;
                    }
                    a[cnt].name=nm;
                }
                else a[cnt--].reset();
            }
            else{
                cout<<"No such Function."<<endl;
            }
        }
        else if(op=="+"){
            cout<<"Input two Functions >> ";
            string _x,_y;
            cin>>_x>>_y;
            int x=find(_x),y=find(_y);
            if(x&&y){
                a[++cnt]=a[x]+a[y];
                if(!a[cnt].errrrrr){
                    cout<<"Name your new Function >> ";
                    string nm;
                    cin>>nm;
                    while(find(nm)){
                        cout<<"Name already used."<<endl;
                        cout<<"Input a new one >> ";
                        cin>>nm;
                    }
                    a[cnt].name=nm;
                }
                else a[cnt--].reset();
            }
            else{
                cout<<"No such Function."<<endl;
            }
        }
        else if(op=="-"){
            cout<<"Input two Functions >> ";
            string _x,_y;
            cin>>_x>>_y;
            int x=find(_x),y=find(_y);
            if(x&&y){
                a[++cnt]=a[x]-a[y];
                if(!a[cnt].errrrrr){
                    cout<<"Name your new Function >> ";
                    string nm;
                    cin>>nm;
                    while(find(nm)){
                        cout<<"Name already used."<<endl;
                        cout<<"Input a new one >> ";
                        cin>>nm;
                    }
                    a[cnt].name=nm;
                }
                else a[cnt--].reset();
            }
            else{
                cout<<"No such Function."<<endl;
            }
        }
        else if(op=="/"){
            cout<<"Input two Functions >> ";
            string _x,_y;
            cin>>_x>>_y;
            int x=find(_x),y=find(_y);
            if(x&&y){
                a[++cnt]=a[x]/a[y];
                if(!a[cnt].errrrrr){
                    cout<<"Name your new Function >> ";
                    string nm;
                    cin>>nm;
                    while(find(nm)){
                        cout<<"Name already used."<<endl;
                        cout<<"Input a new one >> ";
                        cin>>nm;
                    }
                    a[cnt].name=nm;
                }
                else a[cnt--].reset();
            }
            else{
                cout<<"No such Function."<<endl;
            }
        }
        else if(op=="call"||op=="c"){
            cout<<"Input two Functions >> ";
            string _x,_y;
            cin>>_x>>_y;
            int x=find(_x),y=find(_y);
            if(x&&y){
                a[++cnt]=call(a[x],a[y]);
                if(!a[cnt].errrrrr){
                    cout<<"Name your new Function >> ";
                    string nm;
                    cin>>nm;
                    while(find(nm)){
                        cout<<"Name already used."<<endl;
                        cout<<"Input a new one >> ";
                        cin>>nm;
                    }
                    a[cnt].name=nm;
                }
                else a[cnt--].reset();
            }
            else{
                cout<<"No such Function."<<endl;
            }
        }
        else if(op=="dirichlet"||op=="d"){
            cout<<"Input two Functions >> ";
            string _x,_y;
            cin>>_x>>_y;
            int x=find(_x),y=find(_y);
            if(x&&y){
                a[++cnt]=Dirichlet(a[x],a[y]);
                if(!a[cnt].errrrrr){
                    cout<<"Name your new Function >> ";
                    string nm;
                    cin>>nm;
                    while(find(nm)){
                        cout<<"Name already used."<<endl;
                        cout<<"Input a new one >> ";
                        cin>>nm;
                    }
                    a[cnt].name=nm;
                }
                else a[cnt--].reset();
            }
            else{
                cout<<"No such Function."<<endl;
            }
        }
        else if(op=="=="||op=="="){
            cout<<"Input two Functions >> ";
            string _x,_y;
            cin>>_x>>_y;
            int x=find(_x),y=find(_y);
            if(x&&y){
                if(a[x]==a[y]) cout<<"Yes, They are the same."<<endl;
                else cout<<"No, they are different."<<endl;
            }
            else{
                cout<<"No such Function."<<endl;
            }
        }
        else if(op=="sum"||op=="s"){
            cout<<"Input your Function >> ";
            string q;
            cin>>q;
            int f=find(q);
            if(f){
                a[++cnt]=sum(a[f]);
                cout<<"Name your new Function >> ";
                string nm;
                cin>>nm;
                while(find(nm)){
                    cout<<"Name already used."<<endl;
                    cout<<"Input a new one >> ";
                    cin>>nm;
                }
                a[cnt].name=nm;
            }
            else{
                cout<<"No such Function."<<endl;
            }
        }
        else if(op=="list"||op=="l"){
            for(int i=1;i<=cnt;i++) cout<<a[i].name<<endl;
        }
        else if(op=="add"||op=="a"){
            string nm;
            cout<<"Input your Function >> ";
            cin>>nm;
            if(find(nm)) cout<<"Name already used."<<endl;
            else{
                ifstream fin(nm);
                if(!fin){
                    cout<<"No such file."<<endl;
                    continue;
                }
                ofstream dat;
                dat.open("data",ios::app);
                dat<<nm<<endl;
                dat.close();
                cnt++;
                a[cnt].name=nm;
                fin>>a[cnt].l>>a[cnt].r;
                for(int i=a[cnt].l;i<=a[cnt].r;i++) fin>>a[cnt][i];
                fin.close();
            }
        }
        else if(op=="save"){
            string nm;
            cout<<"Input your Function >> ";
            cin>>nm;
            int f=find(nm);
            if(f){
                loader l("Saving "+nm);
                ofstream fdat("data",ios::app);
                fdat<<nm<<endl;
                ofstream fout(nm);
                fout<<a[f].l<<" "<<a[f].r<<endl;
                for(int i=a[f].l;i<=a[f].r;i++){
                    fout<<a[f][i]<<endl;
                    l.load();
                }
                fout.close();
                cout<<"\nDone.\n";
            }
            else{
                cout<<"No such Function."<<endl;
            }
        }
        else if(op=="modify"||op=="m"){
            cout<<"Input your Function >> ";
            string nm;
            cin>>nm;
            int f=find(nm);
            if(f){
                cout<<"Input location >> ";
                int loc;
                cin>>loc;
                if(loc<a[f].l||loc>a[f].r){
                    cout<<"Over the bound."<<endl;
                    continue;
                }
                cout<<"Input new value >> ";
                int val;
                cin>>val;
                a[f][loc]=val;
            }
            else{
                cout<<"No such Function."<<endl;
            }
        }
        else if(op=="copy"||op=="c"){
            cout<<"Input your Function >> ";
            string nm;
            cin>>nm;
            int f=find(nm);
            if(f){
                a[++cnt]=a[f];
                cout<<"Name your new Function >> ";
                string nm;
                cin>>nm;
                while(find(nm)){
                    cout<<"Name already used."<<endl;
                    cout<<"Input a new one >> ";
                    cin>>nm;
                }
                a[cnt].name=nm;
            }
            else{
                cout<<"No such Function."<<endl;
            }
        }
        else if(op=="delete"||op=="d"){
            cout<<"Input your Function >> ";
            string nm;
            cin>>nm;
            int f=find(nm);
            if(f){
                a[f].reset();
                a[f].name="";
            }
            else{
                cout<<"No such Function."<<endl;
            }
        }
        else if(op=="exit"||op=="e"){
            break;
        }
        else if(op=="rename"||op=="r"){
            cout<<"Input your Function >> ";
            string nm;
            cin>>nm;
            int f=find(nm);
            if(f){
                cout<<"Input new name >> ";
                string nm;
                cin>>nm;
                while(find(nm)){
                    cout<<"Name already used."<<endl;
                    cout<<"Input a new one >> ";
                    cin>>nm;
                }
                a[f].name=nm;
            }
            else{
                cout<<"No such Function."<<endl;
            }
        }
        else if(op=="?"||op=="help"||op=="h"){
            cout<<"This is xyf's maths theory calculator."<<endl;
            cout<<"You can use the following commands:"<<endl;
            cout<<"+: Add two Functions."<<endl;
            cout<<"-: Subtract two Functions."<<endl;
            cout<<"*: Multiply two Functions."<<endl;
            cout<<"/: Divide two Functions."<<endl;
            cout<<"call/c: c(i)=a(b(i))"<<endl;
            cout<<"Dirichlet/d: Dirichlet product of two Functions."<<endl;
            cout<<"==/=: Check if two Functions are the same."<<endl;
            cout<<"sum/s: The prefix sum of the Function."<<endl;
            cout<<"list/l: List all the Functions."<<endl;
            cout<<"add/a: Add a new Function."<<endl;
            cout<<"save: Save a Function."<<endl;
            cout<<"?/help/h: Show this help."<<endl;
            cout<<"exit/quit/q: Exit the program."<<endl;
            cout<<"modify/m: Modify a value of a Function."<<endl;
            cout<<"copy/c: Copy a Function."<<endl;
            cout<<"rename/r: Rename a Function."<<endl;
            cout<<"Thanks for using."<<endl;
        }
        else{
            cout<<"Unknown command."<<endl;
        }
        if(cnt>=199){
            cout<<"You have too many Functions."<<endl;
            break;
        }
    }
    return 0;
}
