#include<string>
#include<iostream>
using namespace std;

#include "timestamp.h"
#ifndef GRAPH_H
#define GRAPH_H

struct edge{
    int source;//edge is from this node to neighbor
	int neighbor; // adjacent node
	int w; //keeps auxiliary information
	edge(){
	    source = 0;
		neighbor = 0;
		w = 0;
	};
	edge(int i, int j){
        source = 0;//dummy value
		neighbor = i;
		w = j;
	};
    edge(int from, int to, int aweight){
        source = from;//edge is from this node
        neighbor = to;//edge is to this node
        w = aweight;//weight of this edge
    };
//overloaded *less than* operator will allow to compare edges
    //bool operator<(edge y){ return (this->w < y.w) ? true : false; };
};

class Ugraph{
public:
	Ugraph(int N);
	void bfs(int s);
	void dfs();
	void dfsVisit(int u, int &t);
	void printGraph();
	void addEdge(int u, int v);
	void addEdge(int u, int v, int weight);
    void removeEdge(int u, int v);
    void runBFS(int s);

	//Problem 1
	bool sameCycle(int s, int r);
	bool sameCycleVisit(int s, int r);
	
    //Problem 2.
	int longestCycle(int s);
	int longestCycleVisit(int u, int curMaxLen);
	
    //Problem 3
	bool twoPaths(int s, int r);
	bool printPathWeight(int r, vector<int> &path);
	bool bfsTwoPaths(int s, int r);
	
    //Problem 4
	bool isOnPath(int s, int r, int q);//returns true if q is on the shortest path from s to r
	//bool printPath(int r, vector<int> &path);

	//proj 3, undirected graph
	//P1
	bool distinctPaths(int u, int v);
	void distinctPathsPrint(int s, int r);
    void bfsPrint(int s, int r);

	//P2
	void printBridges();
    void printBridgesVisit(int u, int &t, vector<int> &low);
    int min(int low, int disc);
	//P3
	void printCC();
    void printCCdfsVisit(int u, int curID, vector<int> &cc);

	//P4
	bool twoColoring();
	bool twoColoringVisit(int u);

	//project 5
	void dijkstra(int s);
	void printDistance();
	void printParents();
	void printPath(int u, int v);
	void printPathVisit(int u, int v);
	int lenghtShortestW(int u, int v);
	void kruskal();
	int findSet(int v);
	void combine(int x, int y);
	void printMST();
	int weightMST();


private:
	vector< vector<edge> > Adj; //adjacency lists of the graph
    vector< vector<edge> > mst;
	vector<int> distance; //for BFS and DFS
	vector<int> parents; //for BFS and DFS
	vector<char> colors; //for DFS
	vector<TimeStamp> stamps; //for DFS: stamps[v].d returns discovery time of v, and stamps[v].f finishing time.
    int size;
};

#endif
