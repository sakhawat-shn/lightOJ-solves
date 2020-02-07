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

struct info
{
    LLD prop;
    int zero,one,tow;
};

info tree[500000];

void merge_node(int root,int child)
{
    tree[root].one=tree[child].one+tree[child+1].one;
    tree[root].tow=tree[child].tow+tree[child+1].tow;
    tree[root].zero=tree[child].zero+tree[child+1].zero;
}

void update_node(int root)
{
    int tmp=tree[root].tow;
    tree[root].tow=tree[root].one;
    tree[root].one=tree[root].zero;
    tree[root].zero=tmp;
    tree[root].prop++;
}

void init(int node, int b, int e)
{
    if (b == e) {
        tree[node].zero=1;
        tree[node].one=tree[node].tow=0;
        tree[node].prop=0;
        return;
    }
    int Left = node * 2;
    int Right = node * 2 + 1;
    int mid = (b + e) / 2;
    init(Left, b, mid);
    init(Right, mid + 1, e);
    merge_node(node,node*2);
    tree[node].prop=0;
}

void update(int node, int b, int e, int i, int j)
{
    if (i > e || j < b)
        return;
    if (b >= i && e <= j)
    {
        update_node(node);
        return;
    }
    int Left = node * 2;
    int Right = (node * 2) + 1;
    int mid = (b + e) / 2;
    update(Left, b, mid, i, j);
    update(Right, mid + 1, e, i, j);
    merge_node(node,Left);
}

int how_many(int node,LLD carry)
{
    LLD x=carry%3;
    if(x==0)
    {
        return tree[node].zero;
    }
    else if(x==1)
    {
        return tree[node].tow;
    }
    else
    {
        return tree[node].one;
    }
}


int query(int node, int b, int e, int i, int j, LLD carry = 0)
{
    if (i > e || j < b)
        return 0;

    if (b >= i && e <= j)
        return how_many(node,carry);

    int Left = node*2;
    int Right = (node*2) + 1;
    int mid = (b + e)/2;

    int p1 = query(Left, b, mid, i, j, carry + tree[node].prop);
    int p2 = query(Right, mid + 1, e, i, j, carry + tree[node].prop);

    return p1 + p2;
}


int main()
{
    int t;
    scan(t);
    for(int i=0; i<t; i++)
    {
        int n,q;
        scan(n);
        scan(q);
        printf("Case %d:\n",i+1);
        init(1,0,n-1);
        int a,b,c;
        for(int j=0; j<q; j++)
        {
            scan(a);
            scan(b);
            scan(c);
            if(a==0)
            {
                update(1,0,n-1,b,c);
            }
            else
            {
                print(query(1,0,n-1,b,c,0));
                print(newline);
            }
        }
    }


    return 0;
}
