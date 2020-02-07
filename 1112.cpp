#include<bits/stdc++.h>
using namespace std;

//-----Typedef-----
typedef long long int LLD;
typedef pair<int, int> pi;
typedef pair<LLD, LLD> pll;
typedef vector<int> vi;
typedef vector<LLD> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
typedef vector<string> vstr;



//------fast I/O----
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

//-----constants----
#define ERR 1e-9
#define PI (acos(-1))
#define MAX 300005
const int INF = 0x3f3f3f3f;
const int MOD = (int)1e9+7;

//---mem set-----
#define memo(a,b) memset((a),(b),sizeof(a))
#define CLR(x) memset(x,0,sizeof(x))

//----function shortcut----
#define pb push_back
#define mkp make_pair
#define Sort(v) sort(v.begin(),v.end())
#define RSort(v) sort(v.rbegin(),v.rend())
#define CSort(v,C) sort(v.begin(),v.end(),C)
#define all(v) (v).begin(),(v).end()
#define sqr(x) ((x)*(x))
#define find_dist(a,b) sqrt(sqr(a.x-b.x)+sqr(a.y-b.y))
#define sz(a) int(a.size())
#define F first
#define S second
bool isVowel(char ch){ ch=toupper(ch); if(ch=='A'||ch=='U'||ch=='I'||ch=='O'||ch=='E') return true; return false;}
bool isConsonant(char ch){if (isalpha(ch) && !isVowel(ch)) return true; return false;}

//-----Template-----
template <class T> void dbug(T a) {cout<<"["<<a<<"]";}
template <class T> T gcd(T a, T b) {if(a < b) swap(a, b); while(b) {T t = b; b = a % b; a = t;} return a;}
template <class T> T big_mod(T n,T p,T m){if(p==0)return (T)1;T x=big_mod(n,p/2,m);x=(x*x)%m;if(p&1)x=(x*n)%m;return x;}
template <class T> T extract(string s, T ret) {stringstream ss(s); ss >> ret; return ret;}
template <class T> string tostring(T n) {stringstream ss; ss << n; return ss.str();}
template <class T> void print_vector(T &v){int sz=v.size();if(sz)cout<<v[0];for(int i = 1; i < sz; i++)cout << ' '<<v[i];cout<<"\n";}



//----direction-----
//int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1}; ///8 Direction
//int dx[4] = {0, 1, 0, -1};int dy[4] = {1, 0, -1, 0}; ///4 Direction
//int dx[]={2,1,-1,-2,-2,-1,1,2};int dy[]={1,2,2,1,-1,-2,-2,-1};///Knight Direction
//int dx[]={-1,-1,+0,+1,+1,+0};int dy[]={-1,+1,+2,+1,-1,-2}; ///Hexagonal Direction

//-----I/O------
char tcstr[300];
void scan(int &a){scanf("%d",&a);}
void scan(LLD &a){scanf("%lld",&a);}
void scan(char &a){scanf("%c",&a);}
void scan(double &a){scanf("%lf",&a);}
void scan(string &a){scanf("%s",tcstr);a=tcstr;}
void scanln(string &a){scanf("%[^\n]",tcstr);a=tcstr;}
#define newline '\n'
void print(int a){printf("%d",a);}
void print(LLD a){printf("%lld",a);}
void print(char a){printf("%c",a);}
void print(double a){printf("%lf",a);}
void print(string a){printf("%s",a.c_str());}
//-----I/O-------

LLD val[1000000];
LLD sum[1000000];

void build(int att,int l,int r)
{
    if(l==r)
    {
        sum[att]=val[l];
        return ;
    }
    int mid=(l+r)/2;
    build(att*2,l,mid);
    build(att*2+1,mid+1,r);
    sum[att]=sum[att*2]+sum[att*2+1];
}

void update(int att,int l,int r,int pos,LLD u)
{
    if(l==r)
    {
        sum[att]+=u;
        return ;
    }
    int mid=(l+r)/2;
    if(pos<=mid)
        update(att*2,l,mid,pos,u);
    else
        update(att*2+1,mid+1,r,pos,u);
    sum[att]=sum[att*2]+sum[att*2+1];
}

LLD get_i(int att,int l,int r,int pos)
{
    LLD ret;
    if(l==r)
    {
        ret=sum[att];
        sum[att]=0;
        return ret;
    }
    int mid=(l+r)/2;
    if(pos<=mid)
    {
        ret=get_i(att*2,l,mid,pos);
    }
    else
    {
        ret=get_i(att*2+1,mid+1,r,pos);
    }
    sum[att]=sum[att*2]+sum[att*2+1];
    return ret;
}

LLD query(int att,int L,int R,int l,int r)
{
    if(r<L||R<l) return 0;
    if(l<=L&&R<=r) return sum[att];
    int mid=(L+R)/2;
    int x=query(att*2,L,mid,l,r);
    int y=query(att*2+1,mid+1,R,l,r);
    return x+y;
}



int main()
{
    int t;
    scan(t);
    for(int i=0;i<t;i++)
    {
        int n,q;
        LLD tmp;
        scan(n);scan(q);
        for(int j=0;j<n;j++)
        {
            scan(tmp);
            val[j]=tmp;
        }
        build(1,0,n-1);
        printf("Case %d:\n",i+1);
        int a,b,c;
        for(int j=0;j<q;j++)
        {
            scan(a);
            if(a==1)
            {
                scan(b);
                print(get_i(1,0,n-1,b));
                print(newline);
            }
            else if(a==2)
            {
                scan(b);scan(tmp);
                update(1,0,n-1,b,tmp);
            }
            else
            {
                scan(b);scan(c);
                print(query(1,0,n-1,b,c));
                print(newline);
            }
        }
    }

    return 0;
}
