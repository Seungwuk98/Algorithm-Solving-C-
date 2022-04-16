#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using plib = tuple<ll, int, bool>;

const ll INF = 1LL<<60;
ll dist[101010];
vector<plib> graph[101010];
bool from_red[101010] = {0,};

int main()
{
	int n, b, r;
	cin >> n >> b >> r;
	while (b--){
		int x,y,z; cin >> x >> y >> z;
		graph[x].push_back({z,x,0});
		graph[y].push_back({z,y,0});
	}
	while (r--){
		int x,y,z; cin >> x >> y >> z;
		graph[x].push_back({z,y,1});
		graph[y].push_back({z,x,1});
	}
	
	priority_queue<plib,vector<plib>, greater<plib>> pq;
	fill(dist, dist+n+1, INF);
	dist[1] = 0;
	pq.push({0,1,0});

	while (!pq.empty()){
		ll currdist; int currnode; bool _;
		tie(currdist, currnode, _) = pq.top(); pq.pop();
		if (currdist != dist[currnode]) continue;
		
		for (int i=0; i<graph[currnode].size(); ++i){
			ll nextdist; int nextnode; bool red;
			tie(nextdist, nextnode, red) = graph[currnode][i];
			ll from_start = currdist + nextdist;
			if (dist[nextnode] == from_start){
				if (from_red[nextnode] && !red) from_red[nextnode] = 0;
			}

			if (dist[nextnode] > from_start){
				dist[nextnode] = from_start;
				from_red[nextnode] = red;
				pq.push({from_start, nextnode, 0});
			}
		}
	}
	int ret = 0;

	for (int i=1; i<=n; ++i){
		cout << from_red[i] << endl;
	}
	cout << ret;

} // namespace std;
