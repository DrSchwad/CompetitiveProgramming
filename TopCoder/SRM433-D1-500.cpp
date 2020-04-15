/*
	Author: Nayeemul Islam Swad
	
	Idea: 
		- 
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = int(1e5) + 10;

class SettingTents {
public:
	int countSites(int N, int M) {
		vector<int> sq_root(100 * 100 + 1, -1);
		for (int i = 0; i <= 100; i++) sq_root[i * i] = i;

		vector<tuple<pii, pii, pii>> v;
		for (int dx1 = 0; dx1 <= 100; dx1++) {
			for (int dy1 = -100; dy1 <= 100; dy1++) {
				for (int dx2 = 0; dx2 <= 100; dx2++) {
					int dy2_sq = dx1 * dx1 + dy1 * dy1 - dx2 * dx2;
					if (dy2_sq < 0 || dy2_sq > 10000 || sq_root[dy2_sq] == -1) continue;
					int dy2 = sq_root[dy2_sq];

					int dx3 = dx1 + dx2;
					int dy3 = dy1 + dy2;
					if (dy1 * dx2 > dy2 * dx1 &&
						dy1 * dx3 > dy3 * dx1 &&
						dy3 * dx2 > dy2 * dx3 &&
						make_pair(dx2, dy2) > make_pair(0, 0)) {
						v.push_back(make_tuple(make_pair(dx1, dy1), make_pair(dx2, dy2), make_pair(dx3, dy3)));
					}

					if (dy2 == 0) continue;
					dy2 = -dy2;

					dx3 = dx1 + dx2;
					dy3 = dy1 + dy2;
					if (dy1 * dx2 > dy2 * dx1 &&
						dy1 * dx3 > dy3 * dx1 &&
						dy3 * dx2 > dy2 * dx3 &&
						make_pair(dx2, dy2) > make_pair(0, 0)) {
						v.push_back(make_tuple(make_pair(dx1, dy1), make_pair(dx2, dy2), make_pair(dx3, dy3)));
					}
				}
			}
		}

		int ans = 0;

		for (auto pt : v) {
			int lx = max(-get<0>(pt).x, max(-get<1>(pt).x, -get<2>(pt).x));
			lx = min(lx, N + 1); lx = max(lx, 0);
			int rx = min(N - get<0>(pt).x, min(N - get<1>(pt).x, N - get<2>(pt).x));
			rx = max(rx, -1); rx = min(rx, N);
			int ly = max(-get<0>(pt).y, max(-get<1>(pt).y, -get<2>(pt).y));
			ly = min(ly, M + 1); ly = max(ly, 0);
			int ry = min(M - get<0>(pt).y, min(M - get<1>(pt).y, M - get<2>(pt).y));
			ry = max(ry, -1); ry = min(ry, M);

			ans += max(0, rx - lx + 1) * max(0, ry - ly + 1);
		}

		return ans;
	}
};
