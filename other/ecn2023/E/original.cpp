#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

int t;

#define int long long

void build(int nod,int st,int dr,vector<int>&arb_max,vector<int>&arb_sum,vector<int>&v1,vector<int>&v2,int &k1,int &k2)
{
	if (st == dr)
	{
		arb_max[nod] = v1[k1];
		k1++;
		arb_sum[nod] = v2[k2];
		k2++;
		//cout << "aici" << nod << endl;
	}
	else
	{
		int mid = (st + dr) / 2;
		build(2 * nod, st, mid, arb_max,arb_sum,v1,v2,k1,k2);
		build(2 * nod + 1, mid + 1, dr, arb_max, arb_sum, v1, v2, k1, k2);
		
		arb_max[nod] = max(arb_max[2 * nod], arb_max[2 * nod + 1]);
		arb_sum[nod] = arb_sum[2 * nod] + arb_sum[2 * nod + 1];
	}
}

void query_sum(int nod, int st, int dr, vector<int>&arb,int stt,int drr,int &sol)
{
	if (stt <= st && dr <= drr)
		sol += arb[nod];
	else
	{
		int mid = (st + dr) / 2;
		if (stt <= mid)
			query_sum(2 * nod, st, mid, arb, stt, drr, sol);

		if (drr > mid)
			query_sum(2 * nod + 1, mid + 1, dr, arb, stt, drr, sol);
	}
}


void query_max(int nod, int st, int dr, vector<int>&arb, int stt, int drr, int& sol)
{
	if (stt <= st && dr <= drr)
		sol = max(sol,arb[nod]);
	else
	{
		int mid = (st + dr) / 2;
		if (stt <= mid)
			query_max(2 * nod, st, mid, arb, stt, drr, sol);

		if (drr > mid)
			query_max(2 * nod + 1, mid + 1, dr, arb, stt, drr, sol);
	}
}

int32_t main()
{
	cin >> t;
	while (t--)
	{
		int n, k;
		cin >> n >> k;
		vector<int>a(n);
		for (int& i : a)
			cin >> i;

		vector<int>v1(a), v2(a);

		for (int i = 0; i < n; i++)
		{
			v1[i] += i;
			v2[n - i - 1] += i;
		}


		vector<int>arb_max(4 * n);
		vector<int>arb_sum(4 * n);

	
		int k1, k2;
		k1 = k2 = 0;
		build(1,1,n,arb_max,arb_sum,v1,v2,k1,k2);

		
		int minim = 1e9;
		for (int i = 0; i < n - k + 1; i++)
		{
			int maxim = 0;
			query_max(1, 1, n, arb_max, i + 1, i + k, maxim);

			maxim -= i;
			maxim *= k;


			int sum = 0;
			query_sum(1, 1, n, arb_sum, i + 1, i + k, sum);
			//cout << sum << " ";
			sum = sum - (n - k - i) * k;
			
			minim = min(maxim - sum, minim);
		}
		cout << minim<<endl;
	}
	
}