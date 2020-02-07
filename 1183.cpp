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

LLD seg[400010] = {0};
LLD lazy[400010] = {0};

void build (int at, int L, int R)
{
    if (L == R)
    {
        seg[at] =0;
        lazy[at] =-1;
        return;
    }
    int mid = (L+R) /2;
    build (2*at, L, mid);
    build (2*at+1, mid+1, R);
    seg[at] = seg[2*at] + seg[2*at+1];
    lazy[at]=-1;
}


void update (int at, int L, int R, int l, int r, LLD value)
{
    if (lazy[at] != -1)
    {
        seg[at] = (lazy[at] * (R-L+1) );
        if(L != R)
        {
            lazy[2*at] = lazy[at];
            lazy[2*at+1] = lazy[at];
        }
        lazy[at] = -1;
    }
    if (L > r || R < l) return;
    if (L >= l && R <= r)
    {
        seg[at] = (value * (R-L+1));
        if (L != R)
        {
            lazy[2*at] = value;
            lazy[2*at+1] = value;
        }
        return;
    }

    int mid = (L+R) /2;
    update (2*at, L, mid, l, r, value);
    update (2*at+1, mid+1, R, l, r, value);
    seg[at] = seg[2*at] + seg[2*at+1];
}

LLD query (int at, int L, int R, int l, int r)
{
    if (lazy[at] != -1)
    {
        seg[at] = (lazy[at] * (R-L+1));
        if(L != R)
        {
            lazy[2*at] = lazy[at];
            lazy[2*at+1] = lazy[at];
        }
        lazy[at] = -1;
    }
    if (L > r || R < l) return 0;

    if (L >= l && R <= r) return seg[at];
    int mid = (L+R) /2;
    LLD x = query (2*at, L, mid, l, r);
    LLD y = query (2*at+1, mid+1, R, l, r);
    return (x + y);
}

int main()
{
    int t;
    scan(t);
    for(int i=0;i<t;i++)
    {
        int n,q,timer=0;
        scan(n);scan(q);
        build(1,0,n-1);
        printf("Case %d:\n",i+1);
        for(int j=0;j<q;j++)
        {
            int a,b;
            LLD c,sum,diff,tgcd;
            scan(a);
            if(a==1)
            {
                scan(a);scan(b);scan(c);
                update(1,0,n-1,a,b,c);
            }
            else
            {
                scan(a);scan(b);
                diff=((LLD)b-(LLD)a)+1;
                sum=query(1,0,n-1,a,b);
                //dbug(query(1,0,n-1,a,b,0,0));
                tgcd=gcd(sum,diff);
                if(diff/tgcd==1)
                {
                    print(sum/tgcd);
                }
                else
                {
                    printf("%lld/%lld",sum/tgcd,diff/tgcd);
                }
                //dbug(sum);dbug(diff);
                print(newline);
            }
        }
    }

    return 0;
}
