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

struct Interval
{
    int low,high;
};
struct ITNode
{
    Interval i;
    int mx,mn;
    ITNode *left,*right;
    ITNode(Interval a)
    {
        i.high=a.high;
        i.low=a.low;
        mx=a.high;
        mn=a.low;
        left=right=NULL;
    }
};

ITNode *insrt(ITNode *root,Interval i)
{
    if(root==NULL)
        return new ITNode(i);
    int l=root->i.low;
    if(i.low<l)
    {
        root->left=insrt(root->left,i);
    }
    else
    {
        root->right=insrt(root->right,i);
    }
    if(root->mx<i.high)
    {
        root->mx=i.high;
    }
    if(root->mn>i.low)
    {
        root->mn=i.low;
    }
    return root;
}

bool doOVerlap(Interval i1,Interval i2)
{
    if(i1.low<=i2.high&&i2.low<=i1.high)
    {
        return true;
    }
    return false;
}

int overlapSearch(ITNode *root,Interval i)
{
    if(root==NULL) return 0;
    if(root->mn>i.high||root->mx<i.low) return 0;
    int ret=0;
    if(doOVerlap(root->i,i))
    {
        ret=1;
    }

    ret=ret+overlapSearch(root->left,i);

    return ret+overlapSearch(root->right,i);
}

void del(ITNode *cur)
{
    if(cur==NULL) return;
    del(cur->left);
    del(cur->right);
    delete(cur);
}

int main()
{
    int t;
    ITNode *root=NULL;
    scan(t);
    for(int i=0;i<t;i++)
    {
        int n,q,a,b;
        scan(n);scan(q);
        for(int j=0;j<n;j++)
        {
            scan(a);scan(b);
            root=insrt(root,{a,b});
        }
        printf("Case %d:\n",i+1);
        for(int j=0;j<q;j++)
        {
            scan(a);
            print(overlapSearch(root,{a,a}));
            print(newline);
        }
        del(root);
        root=NULL;
    }

    return 0;
}
