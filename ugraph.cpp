#include<climits>
#include<algorithm>
#include<queue>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
#include<utility>
using namespace std;

#include "ugraph.h"
#include "item.h"
#include "priorityqueue.h"

Ugraph::Ugraph(int N){

	size = N;
	
	Adj.resize(size);
	distance.resize(size);
	parents.resize(size);
	colors.resize(size);
	stamps.resize(size);
	mst.resize(size);

	for (int i = 0; i < size; i++) {
	    parents[i] = i;
	    distance[i] = INT_MAX;
	    colors[i] = 'W';
	}

}//default

void Ugraph::addEdge(int u, int v){
	Adj[u].push_back(edge(v, 0));
	Adj[v].push_back(edge(u, 0));
}
void Ugraph::addEdge(int u, int v, int weight){
	Adj[u].push_back(edge(u, v, weight));
    Adj[v].push_back(edge(v, u, weight));
}

void Ugraph::printGraph(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < (int)Adj[i].size(); j++){
			int v = Adj[i][j].neighbor;
			cout << v << " " ;
		}//for j
		cout << endl;
	}
}//printGraph

void Ugraph::removeEdge(int u, int v) {
    //removes edge from u to v
    for (int i = 0; i < (int)Adj[u].size(); i++) {
        if (Adj[u][i].neighbor == v) {
            Adj[u][i].neighbor = Adj[u][(int)Adj[u].size() - 1].neighbor;
        }
    }
    //removes edge from v to u
    for (int i = 0; i < (int)Adj[v].size(); i++) {
        if (Adj[v][i].neighbor == u) {
            Adj[v][i].neighbor = Adj[v][(int)Adj[v].size() - 1].neighbor;
        }
    }
    Adj[u].resize(Adj[u].size() - 1);
    Adj[v].resize(Adj[v].size() - 1);
}

void Ugraph::bfs(int s){
	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
	}//for
	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while(!aq.empty()){
		int u = aq.front();
        aq.pop();
		cout << u << " ";
		for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(distance[v] == INT_MAX){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
			}
		}//for
	}//while
	cout << endl;
}//bfs

void Ugraph::dfs(){
	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}	
	int t = 0;

	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			//colors[i] = 'G';
			dfsVisit(i, t);
		}//if
	}//for
    cout << endl;
}//dfs

void Ugraph::dfsVisit(int u, int &t){
	colors[u] = 'G';
	stamps[u].d = t;
	t++;
    cout << u << " ";
	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(colors[v] == 'W'){
				parents[v] = u;
				colors[v] = 'G';
				dfsVisit(v, t);
			}
	}//for
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
}//dfsVisit

void Ugraph::runBFS(int s){
	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
	}//for
	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while(!aq.empty()){
		int u = aq.front();
		aq.pop();
		for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(distance[v] == INT_MAX){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
			}
		}//for
	}//while
}//bfs

bool Ugraph::distinctPaths(int u, int v) {

    vector<int> path;

    runBFS(u); //runs BFS on s, and sets all parent nodes.

	printPathWeight(v, path); //recursively backtracks from r setting edge weight to -1.

	bool res = bfsTwoPaths(u, v); //runs BFS while taking new weight into account.

	if (res) {

        for (int i = (int)path.size() - 1; i >= 0; i--) {
            cout << path[i] << " ";
        }
        cout << endl;

        path.clear();

        //printPath(v, path);

		for (int i = (int)path.size() - 1; i >= 0; i--) {
			cout << path[i] << " ";
		}
		cout << endl;
	}

	return res;
}

bool Ugraph::printPathWeight(int r, vector<int> &path) {

	int p = parents[r];

	if (p == r) {
        path.push_back(p);
		return true;
	}

	for (int i = 0; i < (int)Adj[p].size(); i++) {

		if (Adj[p][i].neighbor == r) {
			path.push_back(Adj[p][i].neighbor);
			Adj[p][i].w = -1;
			printPathWeight(p, path);
		}
	}
	return false;
}

//bool Ugraph::printPath(int r, vector<int> &path) {
//
//	int p = parents[r];
//
//	if (p == r) {
//		path.push_back(p);
//		return true;
//	}
//
//	for (int i = 0; i < (int)Adj[p].size(); i++) {
//
//		if ((Adj[p][i].neighbor == r) && (Adj[p][i].w != -1)) {
//			path.push_back(Adj[p][i].neighbor);
//			printPath(p, path);
//		}
//	}
//	return false;
//}

bool Ugraph::bfsTwoPaths(int s, int r) {

	for (int i = 0; i < size; i++) {
		distance[i] = INT_MAX;
		parents[i] = i;
	}//for

	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while(!aq.empty()){
		int u = aq.front();
		aq.pop();

		for (int i = 0; i < (int)Adj[u].size(); i++) {
			int v = Adj[u][i].neighbor;
			if ((distance[v] == INT_MAX) && (Adj[u][i].w != -1)){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
			}
		}//for
	}//while

	if (distance[r] != INT_MAX) {
		return true;
	}

	return false;
}

int Ugraph::longestCycle(int s) {

	for (int i = 0; i < size; i++) {
		parents[i] = i;
		colors[i] = 'W';
	}
	int curMaxLen = 0;

	int maxLen = longestCycleVisit(s, curMaxLen);

	return maxLen;
}

int Ugraph::longestCycleVisit(int u, int curMaxLen) {

	colors[u] = 'G';
	int len = distance[u]+1;

	for (int i = 0; i < (int)Adj[u].size(); i++) {

		int v = Adj[u][i].neighbor;

		if(colors[v] == 'W') {

			parents[v] = u;
			distance[v] = distance[u]+1;
			curMaxLen = longestCycleVisit(v, curMaxLen);
		}

		else if ((colors[v] == 'G') && (parents[v] == v)) {

			if (len > curMaxLen) {
				curMaxLen = len;
			}
		}
	}//for
	colors[u] = 'B';
	return curMaxLen;
}

bool Ugraph::sameCycle(int s, int r) {

	bfs(s);

	//twoPathsVisit(r);

	bool res = bfsTwoPaths(r, s);

	return res;
}

/*bool Ugraph::isOnPath(int s, int r, int q) {

	bfs(s);

	//bool res = backtrackParents(r, q);

	//return res;
}*/

void Ugraph::printBridges() {

	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}
	int t = 0;
	vector<int> low(size);
	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			//colors[i] = 'G';
			printBridgesVisit(i, t, low);
		}//if
	}//for
}

void Ugraph::printBridgesVisit(int u, int &t, vector<int> &low){
	colors[u] = 'G';
	stamps[u].d = t;
	low[u] = t;
	t++;

	for(int i = 0; i < (int)Adj[u].size(); i++){
		int v = Adj[u][i].neighbor;
		if(colors[v] == 'W'){
			parents[v] = u;
			colors[v] = 'G';
			printBridgesVisit(v, t, low);
			low[u] = min(low[u], low[v]);
			if (low[v] > stamps[u].d) {
				cout << u << " " << v << endl;
			}
		}

		else if(v != parents[u]) {
			low[u] = min(low[u], stamps[v].d);
		}
	}//for

	colors[u] = 'B';
	stamps[u].f = t;
	t++;
}//dfsVisit

int Ugraph::min(int low, int disc) {
	if(low < disc) {
		return low;
	}

	else {
		return disc;
	}
}

void Ugraph::printCC() {

	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}

	vector<int> ID;
	vector<int> cc(size, 0);

	int curID = 0;

	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			//colors[i] = 'G';
			printCCdfsVisit(i, curID, cc);
			ID.push_back(curID);
			curID++;

		}//if
	}//for

	for(int i = 0; i < (int)ID.size(); i++) {
		for(int j = 0; j < (int)cc.size(); j++) {

			if (cc[j] == ID[i]) {
				cout << j << " ";
			}
		}
		cout << endl;
	}
}

void Ugraph::printCCdfsVisit(int u, int curID, vector<int> &cc) {

	colors[u] = 'G';
	cc[u] = curID;
	for(int i = 0; i < (int)Adj[u].size(); i++){
		int v = Adj[u][i].neighbor;
		if(colors[v] == 'W'){
			parents[v] = u;
			printCCdfsVisit(v, curID, cc);
		}
	}//for
	//colors[u] = 'B';
}

bool Ugraph::twoColoring() {

	for (int i = 0; i < size; i++) {
		parents[i] = i;
		colors[i] = 'W';
	}

	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			//colors[i] = 'G';
			bool res = twoColoringVisit(0);
			if (!res) {
				return false;
			}
		}//if
	}//for
	return true;
}

bool Ugraph::twoColoringVisit(int u) {

	colors[u] = 'G';

	for (int i = 0; i < (int)Adj[u].size(); i++) {

		int v = Adj[u][i].neighbor;

		if(colors[v] == 'W') {
			parents[v] = u;
			distance[v] = distance[u]+1;
			bool res = twoColoringVisit(v);

			if (!res) {
				return false;
			}
		}

		else if (colors[v] == 'G') {
			int cycleLen = (distance[u] - distance[v]) + 1;
			if (cycleLen % 2 != 0) {

				return false;
			}
		}
	}//for
	colors[u] = 'B';
	return true;
}

//project 5

// Dijkstra's Algorithm

void Ugraph::dijkstra(int s) {
	PriorityQueue PQ;

    for (int i = 0; i < size; i++) {
        parents[i] = i;
        distance[i] = INT_MAX;
    }
    distance[s] = 0;

    for (int i = 0; i < size; i++) {
        PQ.push(i, distance[i]);
    }

    while (!PQ.empty()) {
    	int u = PQ.getMin().key;
    	PQ.pop();

    	for (int i = 0; i < (int)Adj[u].size(); i++) {
    		int v = Adj[u][i].neighbor;
    		int weight = Adj[u][i].w;

    		if (PQ.isKey(v)) {
    			int sum = distance[u] + weight;

				if (sum < distance[v]) {
					distance[v] = sum;
					parents[v] = u;
					PQ.updatePriority(v, distance[v]);
				}
    		}
    	}
    }
}

void Ugraph::printDistance() {
	for (int i = 0; i < size; i++) {
		cout << distance[i] << " ";
	}
	cout << endl;
}

void Ugraph::printParents() {
	for (int i = 0; i < size; i++) {
		cout << parents[i] << " ";
	}
	cout << endl;
}

void Ugraph::printPath(int u, int v) {

	printPathVisit(u, v);
}

void Ugraph::printPathVisit(int u, int v) {

	int p = parents[v];

	if (v == u) {
		cout << u << " ";
		return;
	}

	printPathVisit(u, p);

	cout << v << " ";
}

int Ugraph::lenghtShortestW(int u, int v) {
	dijkstra(u);
	printPath(u, v);
	cout << endl;
	return distance[v];
}

// Kruskal's Algorithm

bool lessThan(const edge &x, const edge &y){ return (x.w < y.w) ? true : false; }

void Ugraph::kruskal() {

	vector<edge> edgesAll;

	if (mst.size() > 0) {

		mst.clear();
		mst.resize(size);
	}

	for (int i = 0; i < size; i++) {

		parents[i] = i;
		distance[i] = 0;
	}

	for (int i = 0; i < (int) Adj.size(); i++) {
		for (int j = 0; j < (int) Adj[i].size(); j++) {

			int u = Adj[i][j].source;
			int v = Adj[i][j].neighbor;
			int w = Adj[i][j].w;

			if (u < v) {
				edgesAll.push_back(edge(u, v, w));
			}
		}
	}

	sort(edgesAll.begin(), edgesAll.end(), lessThan);

	int e = 0;
	int i = 0;
	while (e < size - 1 && i < (int)edgesAll.size()) {

		int u = edgesAll[i].source;
		int v = edgesAll[i].neighbor;
		int rep_u = findSet(u);
		int rep_v = findSet(v);
		int w = edgesAll[i].w;

		if (rep_u != rep_v) {
			mst[u].push_back(edge(u, v, w));
			mst[v].push_back(edge(v, u, w));
			combine(rep_u, rep_v);
			e++;
		}
		i++;
	}
}

int Ugraph::findSet(int v) {

	if (parents[v] != v) {
		parents[v] = findSet(parents[v]);
	}
	return parents[v];
}

void Ugraph::combine(int x, int y) {

	if (distance[x] > distance[y]) {
		parents[y] = x;
	}
	else {
		parents[x] = y;
	}
	if (distance[x] == distance[y]) {
		distance[y]++;
	}
}

void Ugraph::printMST() {

	for (int i = 0; i < (int)mst.size(); i++) {
		for (int j = 0; j < (int)mst[i].size(); j++) {
			cout << mst[i][j].neighbor << " ";
		}
		cout << endl;
	}
}

int Ugraph::weightMST() {

	int weight = 0;
	for (int i = 0; i < (int)mst.size(); i++) {
		for (int j = 0; j < (int)mst[i].size(); j++) {
			weight += mst[i][j].w;
		}
	}
	return weight/2;
}