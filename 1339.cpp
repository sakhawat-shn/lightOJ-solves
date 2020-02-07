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
    int mx,mx_num,left_,left_num,right_,right_num;
};

int val[100000];
info tree[4*100000];

info merge_node(info child,info child1)
{
    info root;
    root.left_=root.left_num=root.mx=root.mx_num=root.right_=root.right_num=0;
    root.left_=child.left_;
    root.left_num=child.left_num;
    root.right_=child1.right_;
    root.right_num=child1.right_num;
    if(child.left_==child1.left_)
    {
        root.left_num=child.left_num+child1.left_num;
    }
    if(child.right_==child1.right_)
    {
        root.right_num=child.right_num+child1.right_num;
    }
    int tmp_=0,tmp_num=0;
    if(child.right_==child1.left_)
    {
        tmp_=child.right_;
        tmp_num=child.right_num+child1.left_num;
    }
    root.mx=tmp_;
    root.mx_num=tmp_num;
    if(root.mx_num<root.left_num)
    {
        root.mx_num=root.left_num;
        root.mx=root.left_;
    }
    if(root.mx_num<root.right_num)
    {
        root.mx_num=root.right_num;
        root.mx=root.right_;
    }
    if(root.mx_num<child.mx_num)
    {
        root.mx_num=child.mx_num;
        root.mx=child.mx;
    }
    if(root.mx_num<child1.mx_num)
    {
        root.mx_num=child1.mx_num;
        root.mx=child1.mx;
    }
    return root;
}

void build(int att,int l,int r)
{

    if(l==r)
    {

        tree[att].left_=tree[att].right_=tree[att].mx=val[l];
        tree[att].left_num=tree[att].right_num=tree[att].mx_num=1;
        return ;
    }
    int mid=(l+r)/2;
    build(att*2,l,mid);
    build(att*2+1,mid+1,r);

    tree[att]=merge_node(tree[att*2],tree[att*2+1]);
}

void ext_dbug(info root)
{
    dbug(root.mx);
    dbug(root.mx_num);
    print(newline);
}


info query(int att,int L,int R,int l,int r)
{
    if(r<L||R<l) return tree[0];
    if(l<=L&&R<=r){ //ext_dbug(tree[att]);
            return tree[att];}
    int mid=(L+R)/2;
    info x=query(att*2,L,mid,l,r);
    info y=query(att*2+1,mid+1,R,l,r);
    //print("x=>");
    //ext_dbug(x);
    //print("y=>");
    //ext_dbug(y);
    return merge_node(x,y);
}

int main()
{
    int t;
    scan(t);
    for(int i=0;i<t;i++)
    {
        int n,c,q;
        scan(n);scan(c);scan(q);
        for(int j=0;j<n;j++)
        {
            scan(val[j]);
        }
        build(1,0,n-1);
        printf("Case %d:\n",i+1);
        int a,b;
        for(int j=0;j<q;j++)
        {
            scan(a);scan(b);
            info ans=query(1,0,n-1,a-1,b-1);
            print(ans.mx_num);
            print(newline);
        }
    }

    return 0;
}
