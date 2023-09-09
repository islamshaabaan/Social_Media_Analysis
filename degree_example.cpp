#include <bits/stdc++.h>
using namespace std;



// To add an edge
void addEdge(vector <pair<int, int> > adj[], int u,int v, int wt)
{
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));

}

int main()
{
    int num_v,num_edge,v, u,w;
    cin >> num_v;
	cin >> num_edge;
    vector<pair<int, int> > adj[num_v];     // make V vectors and every one has a pair of (node , weight)
    vector<int>degree_sum(num_v,0);         // array to have the degree of every node

	for (int i = 0; i < num_edge; i++)
	{
		cin >> v;
		cin >> u;
        cin >> w;
        addEdge(adj,v,u,w);
        degree_sum[u]+=1;
        degree_sum[v]+=1;
	}
	for(int i = 0; i <num_v ; i++)
    {
        cout<<degree_sum[i]<<endl;
    }


/*
    addEdge( adj, 0, 1, 10); // 0 made path with 2 and weight 10
    addEdge( adj, 0, 4, 20);
    addEdge( adj, 1, 2, 30);
    addEdge( adj, 1, 3, 40);
    addEdge( adj, 1, 4, 50);
    addEdge( adj, 2, 3, 60);
    addEdge( adj, 3, 4, 70);
*/
    return 0;
}
