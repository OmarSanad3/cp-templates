#include <bits/stdc++.h>

using namespace std;

#define cin2d(_$)for(auto&$:_$)for(auto&_:$)cin>>_;
#define cout2d(_$)for(auto&$:_$){for(auto &_:$)cout<<_<<" ";cout<<"\n";}
#define cout_map(_$) for(auto&[$,_]:_$)cout<<$<<" "<<_<<"\n";
#define cin(_$)for(auto&_:_$)cin >> _;
#define cout(_$){for(auto&_:_$)cout<<_ <<" ";cout<<"\n";}
#define all(_$) _$.begin(), _$.end()
#define unq(_$){sort(all(_$));_$.resize(unique(all(_$))-_$.begin());}
#define dg($$)  cout << #$$ << ": " << ($$) << "\n"
#define myCeil(N, M) ((N) / (M) + !!((N) % (M)))
#define sz(_$) (int)(_$.size())
typedef long long ll;
constexpr int MOD = 1e9 + 7; constexpr double EPS = 1e-9;

enum TYPE {MIN, MAX, SUM, GCD};
template <typename T, int Q_BASE, TYPE queryType> struct Sparse {
    T table[200002][22], arr[200002];                       /* Size of the arrays */
    T InitialElement = INT_MAX;

    T opr(T &a, T &b) {
        if (queryType == TYPE::MIN)
            return min(a, b);
        if (queryType == TYPE::MAX)
            return max(a, b);
        if (queryType == TYPE::GCD)
            return gcd(a, b);
        if (queryType == TYPE::SUM)
            return a + b;
        return a + b;
    }

    void preCalc(int n) {
        for (int i = 0; i < n; i++)
            Sparse::table[i][0] = Sparse::arr[i];
        for (int j = 1; j < __lg(n) + 1; j++)
            for (int i = 0; i + (1 << j) - 1 < n; i++)
                Sparse::table[i][j] = opr(Sparse::table[i][j - 1], Sparse::table[i + (1 << (j - 1))][j - 1]);
    }

    T getAns(int l, int r) {
        l -= Q_BASE, r -= Q_BASE;
        return queryType == TYPE::SUM ? getAns1(l, r) : getAns2(l, r);
    }
private:
    // get Ans in O(log)
    T getAns1(int l, int r) {
        T ans = InitialElement;
        int len = r - l + 1, idx = l;
        for (int bit = __lg(n) + 1; bit >= 0; bit--)
            if (len & (1 << bit))
                ans = opr(ans, Sparse::table[idx][bit]), idx += (1 << bit);
        return ans;
    }

    // get Ans in O(1)
    T getAns2(int l, int r) {
        int len = r - l + 1;
        int LG = __lg(len);
        return opr(Sparse::table[l][LG], Sparse::table[r - (1 << LG) + 1][LG]);
    }
};

Sparse < int, 0, TYPE::MIN> sp;

void SOLVE(int ts_ctr) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> sp.arr[i];

    sp.preCalc(n);

    int q, l, r;
    cin >> q;
    while (q--) {
        cin >> l >> r;
        cout << sp.getAns(l, r) << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#if !defined(ONLINE_JUDGE)
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    // cout << fixed << setprecision(10);
    int testcases = 1;
    // cin >> testcases;
    for (int test_ctr = 1; test_ctr <= testcases; test_ctr++)   SOLVE(test_ctr);
    /* cerr<<"Time Taken: "<<(float)clock()/CLOCKS_PER_SEC<<" Secs"<<"\n"; */
}
