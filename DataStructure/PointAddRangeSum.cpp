# include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

template <typename Monoid=ll> class SegmentTree {
    public:
    using Monoid_func = function<Monoid(Monoid, Monoid)>;
    ll size;
    std::vector<Monoid> segment;  // 1-indexed 葉ノードは size ~ 2*size-1
    Monoid Monoid_unit;
    Monoid_func Monoid_calc;

    SegmentTree(ll N, 
                Monoid Monoid_unit = 0,
                Monoid_func Monoid_calc = [](ll a, ll b){return a+b;}) 
            : size(1), Monoid_unit(Monoid_unit), Monoid_calc(Monoid_calc) {
        while(size < N) size <<= 1;
        segment.assign(size*2, Monoid_unit);
    }

    void set(ll k, Monoid a){
        segment[k+size] = a;
    }
    void build(){  // 全てのノードを再計算
        for(ll k=size-1; k>0; k--) segment[k] = Monoid_calc(segment[k*2], segment[k*2+1]);
    }
    void build(std::vector<Monoid> v){
        for(ll k=0; k<size; k++)segment[k+size]=v[k];
        build();
    }
    void update_replace(ll k, Monoid a){
        k += size;
        segment[k] = a;
        while(k >>= 1) segment[k] = Monoid_calc(segment[k*2], segment[k*2+1]);
    }
    void update_add(ll k, Monoid a){
        k += size;
        segment[k] = Monoid_calc(segment[k], a);
        while(k >>= 1) segment[k] = Monoid_calc(segment[k*2], segment[k*2+1]);
    }
    Monoid query(ll a, ll b){ // [a, b)の演算結果
        Monoid l=Monoid_unit, r=Monoid_unit;
        for(a+=size, b+=size; a<b; a>>=1, b>>=1){
            if(a % 2 == 1) l = Monoid_calc(l, segment[a++]);
            if(b % 2 == 1) r = Monoid_calc(segment[--b], r);
        }
        return Monoid_calc(l,r);
    }

    Monoid operator[](const ll &k) const{
        return segment[k+size];
    }
};

int main(){
    ll n,q;
    cin>>n>>q;
    SegmentTree<ll> st(n, 0, [](ll a, ll b){return a+b;});
    vector<ll> a;
    ll aa, p, l, r;
    REP(i,n){
        cin>>aa;
        a.push_back(aa);
    }
    st.build(a);
    REP(i,q){
        cin>>p>>l>>r;
        if(p==0) st.update_add(l,r);
        else cout<<st.query(l,r)<<endl;
    }
    return 0;
}