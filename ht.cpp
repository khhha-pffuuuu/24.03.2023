#include <iostream>
#include <vector>
#include <queue>


using namespace std;

struct Edge {
	int src, dir, weight;
};

void printPath(vector<int> parent, int vertex, int source) {
	if (vertex < 0) {
		return;
	}

	printPath(parent, parent[vertex], source);
	if (vertex != source) {
		cout << " -> ";
	}
	cout << vertex;
}

void printPath1(vector< vector<int> > path, int v, int u)
{
	if (path[v][u] == v) {
		return;
	}
	printPath1(path, v, path[v][u]);
	cout << path[v][u] << " -> ";
}

void printSolution(vector<vector<int>> cost, vector<vector<int>> path)
{
	int n = cost.size();
	for (int v = 0; v < n; v++)
	{
		for (int u = 0; u < n; u++)
		{
			if (u != v && path[v][u] != -1)
			{
				cout << "Самый короткий путь " << v << " —> " << u << " : ["
					<< v << " -> ";
				printPath1(path, v, u);
				cout << u << "]" << endl;
			}
		}
	}
}




void BellmanFord(vector <Edge> edges, int src, int n) {
	vector <int> distance(n, INT_MAX);
	distance[src] = 0;

	vector <int> parent(n, -1);

	int u, v, w, k = n;

	while (k--) {
		for (int i = 0; i < edges.size(); i++) {
			u = edges[i].src;
			v = edges[i].dir;
			w = edges[i].weight;

			if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
				distance[v] = distance[u] + w;

				parent[v] = u;
			}
		}
	}

	for (int i = 0; i < edges.size(); i++) {
		u = edges[i].src;
		v = edges[i].dir;
		w = edges[i].weight;

		if (distance[u] != INT_MAX && distance[u] + w < distance[v])
		{
			cout << "Найден цикл отрицательных весов";
			return;
		}
	}

	for (int i = 0; i < distance.size(); i++) {
		if (i != src && distance[i] != INT_MAX) {
			cout << distance[i] << " - вес. Путь: ";
			printPath(parent, i, src);
			cout << endl;
		}
	}
}

void Dijkstra(vector< vector<int> > edges, int src, int n) {
	vector <int> dist(n, INT_MAX);
	dist[src] = 0;

	priority_queue < pair<int, int> > q;
	q.push(make_pair(src, 0));

	vector <int> parent(n, -1);

	int u, v, w, l;

	while (!q.empty()) {
		u = q.top().first;
		l = -q.top().second;
		q.pop();
		if (l > dist[u]) continue;
		for (int i = 0; i < n; i++) {
			v = i;
			w = edges[u][i];
			if (dist[v] > dist[u] + w && dist[u] != INT_MAX) {
				dist[v] = dist[u] + w;
				q.push(make_pair(v, -dist[v]));

				parent[v] = u;
			}
		}
	}

	for (int i = 0; i < dist.size(); i++) {
		if (i != src && dist[i] != INT_MAX) {
			cout << dist[i] << " - вес. Путь: ";
			printPath(parent, i, src);
			cout << endl;
		}
	}
}



void Floyd(vector< vector<int> > edges, int n) {
	vector < vector<int> > cost(n, vector<int>(n));
	vector < vector<int> > path(n, vector<int>(n));
	for (int v = 0; v < n; v++)
	{
		for (int u = 0; u < n; u++)
		{
			cost[v][u] = edges[v][u];

			if (v == u) {
				path[v][u] = 0;
			}
			else if (cost[v][u] != INT_MAX) {
				path[v][u] = v;
			}
			else {
				path[v][u] = -1;
			}
		}
	}

	for (int k = 0; k < n; k++) {
		for (int v = 0; v < n; v++) {
			for (int u = 0; u < n; u++) {
				if (cost[v][k] != INT_MAX && cost[k][u] != INT_MAX
					&& cost[v][k] + cost[k][u] < cost[v][u]) {
					cost[v][u] = cost[v][k] + cost[k][u];
					path[v][u] = path[k][u];
				}
			}
			if (cost[v][v] < 0) {
				cout << "Найден цикл отрицательных весов";
				return;
			}
		}
	}


	printSolution(cost, path);
}



int main()
{
	setlocale(LC_ALL, "rus");

	cout << "Бэллман-Форд:" << endl;

	int n = 5;
	vector <Edge> edges1 = {
		{0, 1, 1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2},
		{1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, 3}
	};

	for (int i = 0; i < n; i++) {
		BellmanFord(edges1, i, n);
	}


	cout << endl << "Дейкстра:" << endl;

	n = 3;
	vector< vector<int> > edges2 = {
		{0, 1, 1},
		{4, 0, 1},
		{2, 1, 0}
	};

	for (int i = 0; i < n; i++) {
		Dijkstra(edges2, i, n);
	}

	cout << endl << "Флойд:" << endl;

	Floyd(edges2, n);
}
