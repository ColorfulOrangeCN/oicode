#include <bits/stdc++.h>
using namespace std;

typedef long long inte;
const static int maxn = -1;
#define int long long

const int dp4y = 365 * 4 + 1, sty = 4713;
const int dp100y = dp4y * 25 - 1;
const int dp400y = dp100y * 4 + 1;

bool f = false;

pair<int, inte> calcy(inte r) {
	int y = 0;
	if (r % dp4y <= 366 && r % dp100y > 365 || r % dp400y <= 366)
		f = true;
	y += r / dp400y * 400;
	r %= dp400y;
	bool g = false, k = false;
	if (r >= dp100y + 1) {
		r -= dp100y + 1;
		y += 100;
		g = true;
		y += r / dp100y * 100;
		r %= dp100y;
	}
	if (g) {
		if (r >= dp4y - 1) {
			r -= dp4y - 1;
			y += 4;
			k = true;
			y += r / dp4y * 4;
			r %= dp4y;
		}
	} else {
		k = true;
		y += r / dp4y * 4;
		r %= dp4y;
	}
	if (k) {
		if (r >= 366) {
			++y;
			r -= 366;
			y += r / 365;
			r %= 365;
		}
	} else {
		y += r / 365;
		r %= 365;
	}
	
	return make_pair(y, r);
}

inline pair<int, inte> cyb(inte r) {
	int y = 0;
	if (r >= dp4y * 3) {
		y += 12;
		r -= dp4y * 3;
	}
	y += r / dp4y * 4;
	r %= dp4y;
	if (r >= 366) {
		++y;
		r -= 366;
		y += r / 365;
		r %= 365;
	}
	return make_pair(y, r);
}

const int dpm[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

pair<int, inte> calcm(inte r, bool up) {
	for (int i = 1; i <= 12; ++i) {
		const int v = dpm[i] + ((i == 2) && up);
		if (r >= v)
			r -= v;
		else
			return make_pair(i, r);
	}
}
void calc(inte r, bool del) {
	f = false;
	int br = r;
	int y = 0, m = 0, d = 0;
	bool bc = false;
	pair<int, inte> res;
	res = cyb(r);
	if (res.first >= 6312) {
		y = 6312;
		r -= 6312 / 4 * dp4y;
		f = false;
		res = calcy(r);
		r = res.second;
		y += res.first;
	} else {
		y += res.first;
		r = res.second;
	}
	if (y >= 4713) {
		y = y - 4712;
	} else {
	 	y = 4713 - y;
	 	bc = true;
	}
	if (!bc && (y >= 1582)) f = ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0);
	else if (bc) f = ((y - 1) % 4 == 0);
	else f = ((y % 4) == 0);
	res = calcm(r, f);
	m = res.first;
	d = res.second;
	++d;
	if (!bc && del && (y > 1582 || (y == 1582 && m > 10) || (y == 1582 && m == 10 && d >= 5))) {
		calc(br + 10, false);
		return;
	}
	cout << d << ' ' << m << ' ' << y << (bc ? " BC" : "") << endl;
}

signed main()
{
	//freopen("P7075_5.in", "r", stdin);
	//freopen("julian.out", "w", stdout);
	int T;
	cin >> T;
	while(T--) {
		inte q;
		cin >> q;
		calc(q, true);
	}
	return 0;
}
