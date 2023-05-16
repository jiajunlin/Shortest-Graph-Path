#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Edge
{
public:
	Edge(int v1 = 0, int v2 = 1, double w = 0.0) : fv{ v1 }, tv{ v2 }, weight{ w }
	{ }

	void print(ostream& out = cout) const
	{
		out << " Edge:(" << fv << ", " << tv << ", " << weight << ")";
	}

public:
	int fv; // from-vertex
	int tv; // to-vertex
	double weight;
};

// Define an output operator for Square
ostream& operator<< (ostream& out, const Edge& rhs)
{
	rhs.print(out);
	return out;
}
