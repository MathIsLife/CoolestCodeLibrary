#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

// sum [(x + kn) / m] for 0 <= k < m
inline ll aux (ll x, ll n, ll m) {
  ll g = __gcd(n, m);
  return g * (x / g) + (m * n - m - n + g) / 2;
}

// sum [(x + kn) / m] for 0 <= k < lim < m
ll get (ll x, ll n, ll m, ll lim) {
  if (!lim) return 0;
  ll ret = lim * (x / m) + lim * (lim - 1) * (n / m) / 2; 
  n %= m, x %= m; if (!n) return ret;
  ll p = (x + (lim - 1) * n) / m;
  return ret + p * lim - get(m - x + n - 1, m, n, p);
}

// sum [(x + kn) / m] for 0 <= k < lim in O(lg max(n, m))
// m > 0, lim >= 0
inline ll floorAPsum (ll x, ll n, ll m, ll lim) {
  ll ret = 0;
  if (x < 0) {
    ll q = x / m; x %= m;
    if (x) x += m, --q;
    ret += q * lim;
  } if (n < 0) {
    ll q = n / m; n %= m;
    if (n) n += m, --q;
    ret += lim * (lim - 1) * q / 2;
  }
  ll tmp = aux(x, n, m), tot = lim / m;
  ret += tmp * tot + tot * (tot - 1) * n * m / 2 + tot * n * (lim - tot * m);
  return ret + get(x, n, m, lim % m);
}

inline ll floor (ll x, ll y) {
  if (x % y == 0) return x / y;
  return x > 0 ? x / y : x / y - 1;
}

inline ll ceiling (ll x, ll y) {
  if (x % y == 0) return x / y;
  return x > 0 ? x / y + 1 : x / y;
}

// find x, y such that ax + by = gcd(a, b)
ll extEuclidean (ll a, ll b, ll &x, ll &y) {
  ll _x = y = 0, _y = x = 1;
  while (b) {
    ll q = a / b, t = b; 
    b = a % b, a = t;
    t = _x; _x = x - q * _x; x = t;
    t = _y; _y = y - q * _y; y = t;
  }
  return a;
}

ll a, b, c, d, e, x[2], y[2], z[2];

int main() {
  cin >> a >> b >> c >> d >> e;
  cin >> x[0] >> x[1] >> y[0] >> y[1] >> z[0] >> z[1];
  ll ans = 0;
  for (ll it = z[0]; it <= z[1]; ++it) {
    ll f = e - c * it, g = __gcd(b, d), X, Y, Z, W;
    // f = aX + bY + dW = aX + gZ
    ll h = extEuclidean(a, g, X, Z);
    if (f % h) continue; X *= f / h, Z *= f / h;
    // general solution: {X + k * g / h, Z - k * a / h}
    ll lt = ceiling(x[0] - X, g / h), rt = floor(x[1] - X, g / h);
    swap(lt, rt); lt = -lt, rt = -rt; rt -= lt;
    // st, st + jump, ..., st + rt * jump
    ll jump = a / h, st = Z + lt * jump; 
    extEuclidean(b, d, Y, W);
    ans = (ans + floorAPsum(y[1] - Y * st + (d / g), -Y * jump, d / g, rt + 1)) % MOD;
    ans = (ans - floorAPsum(y[0] - Y * st + (d / g) - 1, -Y * jump, d / g, rt + 1)) % MOD;
  }
  ans += MOD, ans %= MOD; cout << ans << '\n';
  return 0;
}

