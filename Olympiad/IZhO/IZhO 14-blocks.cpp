/*
	Author: Nayeemul Islam Swad

	Idea:
		- Let dp[k][n] be the answer for if we partition the first n numbers
		  into k parts.

		- To evaluate dp[k][n], consider the rightmost part of the partition
		  of these first n numbers. Let s denote the starting position of the
		  rightmost part.

		  Let l[i] denote the rightmost number before i which is not less than
		  a[i], in other words, l[i] <= i and a[l[i]] > a[i].

		- Now, there are two cases concerning s:
		    - If s <= l[n], then the highest element in the rightmost part lies
		      inside [1, l[n]] since a[l[n]] >= a[n]. So, this partition produces
		      the same result if we just consider the numbers [1, l[n]] and drop
		      the numbers [l[n] + 1, n] from the rightmost part.

		      So, in this case, a candidate value for dp[k][n] is dp[k][l[n]].

		    - If s > l[n], then the hightest element in the rightmost part is
		      a[n]. So, in this case, the candidate value for dp[k][n] is
		      a[n] + dp[k - 1][s]. We can maintain all the values of dp[k - 1][...]
		      in a decreasing queue and query it to get the optimal s.
*/

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#endif

typedef long long ll;

typedef pair<int, int> pii;
#define x first
#define y second

const int N = int(1e5) + 10;
const int K = 105;
const int INF = int(1e9);

int n, k;
int a[N];
int l[N];
int dp[K][N];
int st[N], st_len;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> k;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

	for (int i = 1; i <= n; i++) {
		int at = i - 1;
		while (at > 0 && a[at] < a[i]) at = l[at];
		l[i] = at;
	}

	fill(&dp[0][0], &dp[K][0], INF);
	dp[0][0] = 0;

	for (int _k = 1; _k <= k; _k++) {
		st_len = 0;
		for (int i = 0; i < _k; i++) {
			while (st_len > 0 && dp[_k - 1][st[st_len - 1]] >= dp[_k - 1][i]) st_len--;
			st[st_len++] = i;
		}
		for (int i = _k; i <= n; i++) {
			int at = lower_bound(st, st + st_len, l[i]) - st;
			dp[_k][i] = min(a[i] + dp[_k - 1][st[at]], dp[_k][l[i]]);

			while (st_len > 0 && dp[_k - 1][st[st_len - 1]] >= dp[_k - 1][i]) st_len--;
			st[st_len++] = i;
		}
	}

	cout << dp[k][n] << endl;

	return 0;
}
