#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <numeric>
#include <iomanip>


using namespace std;
void Degree_Centrality();
void Closeness_Centrality();
vector<int> shortest_distance(int src, vector <list<pair<int, int> > > adj_list);

void Betweenness_Centrality();
vector<list<int> > shortest_distance_for_Betweenness(int src, vector <list<pair<int, int> > > adj_list);

void rec_func(vector<list<int> >dess, int node, double *size, double *num, int input, int count);


int main()
{
	char Operation;
	while (1)
	{
		cout << "Please choose wanted operation:\n1- Degree Centrality\n2- Closeness Centrality\n3- Betweenness_Centrality\n4- Exit\n\n>>";
		cin >> Operation;
		if (Operation == '1')
		{
			Degree_Centrality();
		}
		else if (Operation == '2')
		{
			Closeness_Centrality();
		}

		else if (Operation == '3')
		{
			Betweenness_Centrality();
		}
		else if (Operation == '4')
		{
			exit(1);
		}
		else
		{
			cout << "Please Enter Number: 1 -> 4\n\n>>";
		}

	}
	return 0;
}

void Degree_Centrality()
{
	string line, Node, Edge, Src, Des, Weight;
	int i;
	map <string, int> n;
	ifstream myfile("input.txt");
	if (myfile.is_open())
	{
		getline(myfile, line);
		while (getline(myfile, line))
		{
			Src = line.substr(0, line.find(" "));
			i = line.find(" ");
			Des = line.substr(line.find(" ") + 1, line.find(" ", i + 1) - i - 1);
			n[Src] ++;
			n[Des] ++;
		}
		myfile.close();
	}
	map <string, int> ::iterator it;
	for (it = n.begin(); it != n.end(); it++)
	{
		cout << it->first << " : " << it->second << "\n";
	}
}

void Closeness_Centrality()
{
	string line, Node, Edge, Src, Des, Weight;
	int i, node, edge, src, des, weight;
	ifstream myfile("input.txt");
	if (myfile.is_open())
	{
		getline(myfile, line);
		Node = line.substr(0, line.find(" "));
		node = stoi(Node);
	}
	vector <list<pair<int, int> > > adj(node, list<pair<int, int> >());
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			Src = line.substr(0, line.find(" "));
			src = stoi(Src);
			i = line.find(" ");
			Des = line.substr(line.find(" ") + 1, line.find(" ", i + 1) - i - 1);
			des = stoi(Des);
			Weight = line.substr(line.find(" ", i + 1) + 1, line.length());
			weight = stoi(Weight);
			adj[src].push_back({ des,weight });
			adj[des].push_back({ src,weight });
		}
	}
	myfile.close();
	vector<int> dess(node);
	for (i = 0; i < node; i++)
	{
		dess = shortest_distance(i, adj);
		cout << i << " : " << fixed << setprecision(12) << (node - 1.0) / (accumulate(dess.begin(), dess.end(), 0)) << "\n";
	}
}

vector<int> shortest_distance(int src, vector <list<pair<int, int> > > adj_list)
{
	priority_queue<pair<int, pair<int, int> >,
		vector<pair<int, pair<int, int> > >,
		greater<pair<int, pair<int, int> > > >nodes_q;

	// Create d and p arrays
	int n = adj_list.size();
	vector<int> d(n, 10000000);
	vector<int> p(n, -1);

	nodes_q.push({ 0, {src, src} });

	while (!nodes_q.empty()) {
		pair<int, pair<int, int> > cur_p = nodes_q.top();
		nodes_q.pop();
		int cur_node = cur_p.second.first;
		int cur_prev_node = cur_p.second.second;
		int cur_dis = cur_p.first;

		if (d[cur_node] != 10000000)
			continue;

		d[cur_node] = cur_dis;
		p[cur_node] = cur_prev_node;

		// Add the nodes connected to current one
		for (list<pair<int, int> > ::iterator it = adj_list[cur_node].begin(); it != adj_list[cur_node].end(); it++)
		{
			int next_node = (*it).first;
			int weight = (*it).second;
			if (d[next_node] != 10000000)
				continue;
			nodes_q.push({ cur_dis + weight,
						  {next_node, cur_node} });
		}
	}

	return d;
}


void Betweenness_Centrality()
{
	string line, Node, Edge, Src, Des, Weight;
	int i, node, src, des, weight;

	ifstream myfile("input.txt");
	if (myfile.is_open())
	{
		getline(myfile, line);
		Node = line.substr(0, line.find(" "));
		node = stoi(Node);
	}
	vector <list<pair<int, int> > > adj(node, list<pair<int, int> >());
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			Src = line.substr(0, line.find(" "));
			src = stoi(Src);
			i = line.find(" ");
			Des = line.substr(line.find(" ") + 1, line.find(" ", i + 1) - i - 1);
			des = stoi(Des);
			Weight = line.substr(line.find(" ", i + 1) + 1, line.length());
			weight = stoi(Weight);
			adj[src].push_back({ des,weight });
			adj[des].push_back({ src,weight });
		}
	}
	myfile.close();
	vector<list<int> > dess(node);
	for (int input = 0; input < node; input++)
	{

		double output = 0;
		double c_of;

		for (int j = 0; j < node; j++) // from
		{

			dess = shortest_distance_for_Betweenness(j, adj); // get shortest paths from source to all next nodes
			double size = 0;
			double num = 0;

			for (int i = j + 1; i < node; i++) // to
			{

				size = 0;
				num = 0;
				rec_func(dess, i, &size, &num, input, 0);

				if (size == 0)//avoid div by zero
					output = 0;
				else
					output += num / size;


				c_of = output;// c of input from j to i  
			}
		}

		printf("%.7lf\n", c_of);


	}
}

 vector<list<int> > shortest_distance_for_Betweenness(int src, vector <list<pair<int, int> > > adj_list)
{
	priority_queue<pair<int, pair<int, int> >,
		vector<pair<int, pair<int, int> > >,
		greater<pair<int, pair<int, int> > > >nodes_q;

	// Create d and p arrays
	int n = adj_list.size();
	vector<int> d(n, 10000000);
	vector<list<int> > p(n, list<int>());
	nodes_q.push({ 0, {src, src} });

	while (!nodes_q.empty())
	{
		pair<int, pair<int, int> > cur_p = nodes_q.top();
		nodes_q.pop();

		pair<int, pair<int, int> > top;
		if (!nodes_q.empty())
		{
			top = nodes_q.top();

		}



		while ((!nodes_q.empty()) && (cur_p.first == top.first) && (cur_p.second.first == top.second.first))//you have the same dis and yous are in the same node
		{
			
				p[cur_p.second.first].push_back(nodes_q.top().second.second); // push parents
					nodes_q.pop();



			if (!nodes_q.empty())
			{
				top = nodes_q.top();

			}
		}

		int cur_node = cur_p.second.first;
		int cur_prev_node = cur_p.second.second;
		int cur_dis = cur_p.first;

		if (d[cur_node] != 10000000)
			continue;

		d[cur_node] = cur_dis;
		if (cur_prev_node != src)
			p[cur_node].push_back(cur_prev_node);

		// Add the nodes connected to current one
		for (list<pair<int, int> > ::iterator it = adj_list[cur_node].begin(); it != adj_list[cur_node].end(); it++)
		{
			int next_node = (*it).first;
			int weight = (*it).second;
			if (d[next_node] != 10000000)
				continue;
			nodes_q.push({ cur_dis + weight,
						  {next_node, cur_node} });
		}
	}

	return p;
}
void rec_func(vector<list<int> >dess, int node, double *size, double *num, int input,int count)
{


	if (dess[node].empty())
	{

		*(size) += 1;
		return;

	}
	for (std::list<int>::iterator iterator = dess[node].begin(); iterator != dess[node].end(); ++iterator)
	{
		if (*iterator == input)
		{
			if (dess[*iterator].size() == 0) // if the list is empty (there is no in between nodes ) so it is direct path 
				*(num) += 1;
			else
			    *(num) += dess[*iterator].size();
		}
		
		rec_func(dess, *iterator, size, num, input, count);

	}

}



