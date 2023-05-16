#include <iostream>
#include <fstream>    // for ifstream
using namespace std;
#include <cstdlib>   // for rand(), srand()
#include <ctime>     // for time()
#include <assert.h>
#include <math.h>    // for sqrt()
#include "List.h"
#include "Edge.h"


void traverse(int v, vector<bool>& vis, const vector<List<Edge>>& g) {
    vis[v] = true;

    //cout << "Visited vertex : " << v << endl;
    cout << "   " << v;

    for (auto& w : g[v]) {
        if (!vis[w.tv])
            traverse(w.tv, vis, g);
    }
}


void breadth_first(int v, vector<bool>& vis, const vector<List<Edge>>& g)
{
    List<int> q;
    vis[v] = true;
    q.push_back(v);

    while (!q.empty())
    {
        int current = q.front();
        cout << "   " << current;
        q.pop_front();

        for (auto it = g[current].begin(); it != g[current].end(); ++it)
        {
            int neighbor = (*it).tv;
            if (!vis[neighbor])
            {
                vis[neighbor] = true;
                q.push_back(neighbor);
            }
        }
    }
}

//part c
//basic implementation without computational efficiency
void pathing(int source, const vector<List<Edge>>& g)
{
    const double INF = 100000000; 
    vector<double> distances(g.size(), INF);
    distances[source] = 0.0; 
    vector<int> queue;
    queue.push_back(source);
    while (!queue.empty())
    {
        int current = queue.back();
        queue.pop_back(); 

        for (auto& edge : g[current])
        {
            if (distances[edge.tv] > distances[current] + edge.weight)
            {
                distances[edge.tv] = distances[current] + edge.weight; 
                queue.push_back(edge.tv); 
            }
        }
    }
    for (int i = 0; i < g.size(); ++i)
    {
        cout << "Minimal path weight from vertex " << source << " to vertex " << i << ": " << distances[i] << endl;
    }
}


void shortest(int s, const vector<List<Edge>>& g) 
{
    const double INF = 100000000.0;
    int n = g.size();

    // Initialize distance, parent, found, L, and LS arrays
    vector<double> distance(n, INF);
    vector<int> parent(n, -1);
    vector<bool> found(n, false);

    int k = 0;
    vector<int> L(n, 0);
    vector<List<Edge>> LS(n);

    // Start with the source vertex
    distance[s] = 0;

    // Add source vertex to L and update LS
    L[k++] = s;
    LS[0].push_back({ s, 0 });

    while (k != n)
    {
        //part b
        // Find vertex w with smallest distance from S
        int w = -1;
        double min_distance = INF;
        for (int i = 0; i < k; ++i)
        {
            if (!found[L[i]] && distance[L[i]] < min_distance) 
            {
                w = L[i];
                min_distance = distance[w];
            }
        }

        // Mark w as found
        found[w] = true;

        // Update LS for all adjacent vertices v
        for (auto& edge : g[w]) 
        {
            int v = edge.tv;
            //Part E
            if (!found[v])
            {
                int dist_to_v = distance[w] + edge.weight;
                if (dist_to_v < distance[v]) {
                    distance[v] = dist_to_v;
                    parent[v] = w;

                    
                    // Update LS[k] and L
                    int j = -1;
                    for (int i = 0; i <= k; ++i) 
                    {
                        if (i == k || dist_to_v < distance[LS[i].front().tv]) 
                        {
                            j = i;
                            break;
                        }
                    }
                    if (j == k) 
                    {
                        L[k++] = v;
                    }
                    else 
                    {
                        L[k++] = L[k - 1];
                        for (int i = k - 2; i >= j; --i) 
                        {
                            L[i + 1] = L[i];
                        }
                        L[j] = v;
                    }
                    LS[j].push_back({ v, dist_to_v });
                }
            }
        }
    }
    cout << endl; 
    // Print path from source to all vertices
    for (int i = 0; i < n; ++i) 
    {
        cout << "Minimum distance from vertex " << s << " to vertex " << i << " is " << distance[i] << endl;

        if (distance[i] != INF) 
        {
            cout << "Path: ";
            int v = i;
            while ((v != s) && (v != -1)) 
            {
                cout << v << " <- ";
                v = parent[v];
            }
            cout << s << endl;
        }
        else {
            cout << "No path found." << endl;
        }
    }
}

int main() {

    string filename = "input2.txt";

    ifstream infile(filename);   // create ifstream object to read from file
    if (!infile) {
        cerr << "Error opening file." << endl;
        exit(1);
    }

    cout << "Reading from file: " << filename << endl; 

    int nv = 0; // number of vertices
    int ne = 0; // number of edges
    infile >> nv >> ne; // input from file

    cout << "Input:  nv = " << nv << " , ne =  " << ne << endl;

    if ((nv < 0) || (nv > 10000) || (ne < 0) || (ne > 10000)) {
        cerr << "Input values out of range." << endl;
        exit(1);
    }

    vector<List<Edge>> g2(nv); //graph
    int cv1 = 0, cv2 = 0; // Edge from current vertex cv1 to cv2
    double wt = 0.0; // weight

    for (int ne1 = 0; ne1 < ne; ne1++)
    {
        infile >> cv1 >> cv2 >> wt; // input from file
        if ((cv1 < 0) || (cv1 > nv) || (cv2 < 0) || (cv2 > nv) || (wt < 0) || (wt > 10000.0)) {
            cerr << "Input values out of range." << endl;
            exit(1);
        }
        Edge nsq(cv1, cv2, wt);
        g2[cv1].push_back(nsq);
    }
    cout << endl << "Graph " << endl;
    for (int i = 0; i < nv; i++) {
        cout << i << " : ";
        g2[i].printList();
        //	cout << endl;
    }
    vector<bool> visited(nv, false);
    cout << endl << "Depth First traversal " << endl << "Order of vertices visited : ";
    for (int v = 0; v < nv; v++) {
        if (!visited[v])
            traverse(v, visited, g2);
    }
    cout << endl;

    vector<bool> visited1(nv, false);
    cout << endl << "Breadth First traversal " << endl << "Order of vertices visited : ";
    for (int v = 0; v < nv; v++) {
        if (!visited1[v])
            breadth_first(v, visited1, g2);
    }
    cout << endl;

    vector<bool> visited2(nv, false);
    //basic implementation
    cout << endl << "Basic implementation using Depth First:" << endl; 
    pathing(0, g2); 

    //Part A: reading from vertex 0 to all other vertexes
    shortest(0, g2); 


    for (int i = 0; i < nv; i++) {
        //	cout << i << " : Cleared ";
        g2[i].clear();
        cout << endl;
    }

    return 0;
}