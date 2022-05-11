#include <bits/stdc++.h>
using namespace std;

typedef pair<long long,long long> P;

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

void make_tree(int i, int j, int dep, int x=1) {
    int mid = i + j >> 1;
    if (dep&1) sort(point+i, point+j+1, ycomp);
    else sort(point+i, point+j+1, xcomp);
    kdtree[x] = point[mid];
    kdtree[x].st = dep&1;
    ext[x] = 1;
    if (i <= mid-1) make_tree(i, mid-1, dep+1, lx);
    if (j >= mid+1) make_tree(mid+1, j, dep+1, rx);
    kdtree[x].xmn = min({kdtree[lx].xmn, kdtree[rx].xmn, kdtree[x].x});
    kdtree[x].xmx = max({kdtree[lx].xmx, kdtree[rx].xmx, kdtree[x].x});
    kdtree[x].ymn = min({kdtree[lx].ymn, kdtree[rx].ymn, kdtree[x].y});
    kdtree[x].ymx = max({kdtree[lx].ymx, kdtree[rx].ymx, kdtree[x].y});
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

int main(void) {
	int tc;
	scanf("%d\n",&tc);
	for(int t=0;t<tc;t++) {
		memset(isexist,0,sizeof(isexist));
		int n;
		scanf("%d\n",&n);
        vector<P> temp;
		for(int i=0;i<n;i++) {
			int x,y;
			scanf("%d %d\n",&x,&y);
			temp.push_back({x,y});
			save[i]=temp[i];
		}
		sort(temp.begin(),temp.end(),xcomp);
        vector<P> two;
		point[0]=temp[0];
		int cnt=1;
		for(int i=1;i<temp.size();i++) {
		    if (temp[i-1]!=temp[i]) {
		        point[cnt++]=temp[i];
		    }
            else {
                two.push_back(temp[i]);
            }
		}
		maketree(0,cnt-1,0);
		for(int i=0;i<n;i++) {
            if (!two.empty()&&*lower_bound(two.begin(),two.end(),save[i])==save[i]) {
                printf("0\n");
            }
            else {
			    ret=5e18; 
			    getans(1,save[i]);
			    printf("%lld\n",ret);
            }
		}
	}
}