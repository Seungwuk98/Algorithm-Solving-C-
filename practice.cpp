#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;


struct P{
	long long first, second;
	int i;
	bool operator < (const P &other) const {
		if (first != other.first) return first < other.first;
		return second < other.second;
	}

	bool operator == (const P &other) const {
		return first == other.first && second == other.second;
	}

	bool operator != (const P &other) const {
		return !operator==(other);
	}
};

struct Node {
	P pt;
	bool st; 
	long long sx,ex,sy,ey; 
};

Node kdtree[513040];
int n;
bool isexist[513040]; 
P point[142857];
long long ret;
P save[142857];

long long square(long long a) {
	return a*a;
}

bool xcomp(P a,P b) { 
	if (a.first==b.first)
	return a.second<b.second;
	return a.first<b.first;
}

bool ycomp(P a,P b) { 
	if (a.second==b.second)
	return a.first<b.first;
	return a.second<b.second;
}

void maketree(int l,int r,int ind) {
	isexist[ind]=true;
	if (ind==1) {
		kdtree[ind].st=false; 
	}
	else {
		kdtree[ind].st=!kdtree[ind/2].st; 
	}
	if (kdtree[ind].st) {
		sort(point+l,point+r+1,ycomp); 
	}
	else {
		sort(point+l,point+r+1,xcomp);
	}
	int mid=(l+r)/2;
	kdtree[ind].pt=point[mid];  
    kdtree[ind].sx = kdtree[ind].ex = point[mid].first;
    kdtree[ind].sy = kdtree[ind].ey = point[mid].second;
	if (l<=mid-1)   
	    maketree(l,mid-1,ind*2);
	if (mid+1<=r)    
	    maketree(mid+1,r,ind*2+1);
    if (isexist[ind*2]) {
        kdtree[ind].sx = min(kdtree[ind].sx, kdtree[ind*2].sx);
        kdtree[ind].ex = max(kdtree[ind].ex, kdtree[ind*2].ex);
        kdtree[ind].sy = min(kdtree[ind].sy, kdtree[ind*2].sy);
        kdtree[ind].ey = max(kdtree[ind].ey, kdtree[ind*2].ey);
    }
    if (isexist[ind*2+1]) {
        kdtree[ind].sx = min(kdtree[ind].sx, kdtree[ind*2+1].sx);
        kdtree[ind].ex = max(kdtree[ind].ex, kdtree[ind*2+1].ex);
        kdtree[ind].sy = min(kdtree[ind].sy, kdtree[ind*2+1].sy);
        kdtree[ind].ey = max(kdtree[ind].ey, kdtree[ind*2+1].ey);
    }
}

void getans(int ind,P now) {
	if (now!=kdtree[ind].pt) {
		ret=min(ret,square(kdtree[ind].pt.first-now.first)+square(kdtree[ind].pt.second-now.second));
	}
	
	if (kdtree[ind].st) { 
		if (now.second<kdtree[ind].pt.second) {
			if (isexist[ind*2]) { 
				getans(ind*2,now);
			}
			if (isexist[ind*2+1]&&square(kdtree[ind*2+1].sy-now.second)<ret) {
                getans(ind*2+1,now);
			}
		}
		else { 
			if (isexist[ind*2+1]) {
				getans(ind*2+1,now);
			}
			if (isexist[ind*2]&&square(kdtree[ind*2].ey-now.second)<ret) {
				getans(ind*2,now);
			}
		}
	}
	else {
		if (now.first<kdtree[ind].pt.first) {
			if (isexist[ind*2]) {
				getans(ind*2,now);
			}
			if (isexist[ind*2+1]&&square(kdtree[ind*2+1].sx-now.first)<ret) {
				getans(ind*2+1,now);
			}
		}
		else {
			if (isexist[ind*2+1]) {
				getans(ind*2+1,now);
			}
			if (isexist[ind*2]&&square(kdtree[ind*2].ex-now.first)<ret) {
				getans(ind*2,now);
			}
		}
	}
}
int main()
{
	fastio
    int T; cin >> T;
    while (T--) {
        cin >> n;
        memset(isexist, 0, sizeof(isexist));
        for (int i=0; i<n; ++i) {
            cin >> point[i].first >> point[i].second;
            point[i].i = i;
        }
        sort(point, point+n, xcomp);
        int t = 1;
        for (int i=1; i<n; ++i) if (point[i-1] != point[i]) {
			swap(point[t++], point[i]);
		}
        maketree(0, t-1, 1);
        vector<long long> ans(n);
        for (int i=0; i<t; ++i) {
            ret = 5e18;
            getans(1, point[i]);
            ans[point[i].i] = ret;
        }
        for (int i=0; i<n; ++i) cout << ans[i] << '\n';
    }
} // namespace std;
