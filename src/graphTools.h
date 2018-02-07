#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <List>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <random>
#include <unordered_map>
#include <omp.h>
using namespace std;

bool stringEqual(string a, string b)
{
	int len = a.length();
	int len2 = b.length();
	if (len == len2)
	{
		for (int i = 0; i < len; i++)
			if (a[i] != b[i])
				return false;
	}
	else
		return false;
	return true;
}

float randomFloat(float a, float b)
{
	if (a < b)
		return (std::rand() / (float)(RAND_MAX + 1))*(b - a) + a;
	return a;
}

int randomInteger(int a, int b)
{
	std::random_device rd;    
	std::mt19937 rng(rd());    
	std::uniform_int_distribution<int> uni(a, b); 

	auto random_integer = uni(rng);
	return random_integer;
}

void swap(float* a, float* b)
{
	float temp = *a;
	*a = *b;
	*b = temp;
}

vector<float*> readNode(string filetype, string path)
{
	int n = 0;
	register char c;
	string word = "";
	vector<float*> nodes;
	ifstream File(path);

	if (stringEqual(filetype, "gml"))
	{
		while (File.get(c) && c != '[') {}
		while (true)
		{
			while (File.get(c) && c != 'n' && c != 'g') {}
			if (c == 'g')
				break;
			nodes.push_back(new float[10]);
			for (int i = 0; i < 9; i++)
			{
				while (File.get(c) && (47 > c || c > 58) && c != '-') {}
				word = c;
				while (File.get(c) && ((47 < c&&c < 58) || c == '.'))
					word += c;
				nodes[n][i] = stof(word);
			}
			nodes[n][1] = n;
			nodes[n][9] = -1;
			n++;
		}
	}

	File.close();
	return nodes;
}

vector<vector<float*>> readEdge(string filetype, string path)
{
	int n = 0;
	register char c;
	string word = "";
	ifstream File(path);

	if (stringEqual(filetype, "gml"))
	{
		while (File.get(c) && c != '[') {}
		while (true)
		{
			while (File.get(c) && c != 'n' && c != 'g') {}
			if (c == 'g')
				break;
			for (int i = 0; i < 9; i++)
			{
				while (File.get(c) && (47 > c || c > 58) && c != '-') {}
				word = c;
				while (File.get(c) && ((47 < c&&c < 58) || c == '.'))
					word += c;
			}
			n++;
		}
		vector<vector<float*>> edge(n);
		while (File.get(c))
		{
			while (File.get(c) && (47 > c || c > 58) && c != '-') {}
			if (c == '\n')
				break;
			word = c;
			while (File.get(c) && ((47 < c&&c < 58) || c == '.'))
				word += c;
			float id = stof(word);
			while (File.get(c) && (47 > c || c > 58) && c != '-') {}
			word = c;
			while (File.get(c) && ((47 < c&&c < 58) || c == '.'))
				word += c;
			float source = stof(word);
			while (File.get(c) && (47 > c || c > 58) && c != '-') {}
			word = c;
			while (File.get(c) && ((47 < c&&c < 58) || c == '.'))
				word += c;
			float target = stof(word);
			while (File.get(c) && (47 > c || c > 58) && c != '-') {}
			word = c;
			while (File.get(c) && ((47 < c&&c < 58) || c == '.'))
				word += c;
			float label = stof(word);
			while (File.get(c) && (47 > c || c > 58) && c != '-') {}
			word = c;
			while (File.get(c) && ((47 < c&&c < 58) || c == '.'))
				word += c;
			float value = stof(word);
			edge[source].push_back(new float[5]{ target,0,id,value, 1 });
			edge[target].push_back(new float[5]{ source,0,id,value, 0 });//its undirected and this is duplicated in saving
		}
		return edge;
	}
	File.close();
	vector<vector<float*>> temp;
	return temp;
}

void writeGraph(string filetype, string path, vector<float*> nodes, vector<vector<float*>> edge)
{
	ofstream OutPut;
	int n = nodes.size();
	OutPut.open(path);
	if (stringEqual(filetype, "gml"))
	{
		OutPut << "graph" << endl;
		OutPut << "[" << endl;
		OutPut << "  Creator \"HSJ\"" << endl;
		OutPut << "  directed 0" << endl;
		for each (float* var in nodes)
		{
			OutPut << "  node" << endl;
			OutPut << "  [" << endl;
			OutPut << "    id " << var[0] << endl;
			OutPut << "    label \"" << var[1] << "\"" << endl;
			OutPut << "    graphics" << endl;
			OutPut << "    [" << endl;
			OutPut << "      x " << var[2] << endl;
			OutPut << "      y " << var[3] << endl;
			OutPut << "      z " << var[4] << endl;
			OutPut << "      w " << var[5] << endl;
			OutPut << "      h " << var[6] << endl;
			OutPut << "      d " << var[7] << endl;
			OutPut << "      fill \"#" << (int)var[8] << "\"" << endl;
			OutPut << "    ]" << endl;
			OutPut << "  ]" << endl;
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < edge[i].size(); j++)
				if ((int)edge[i][j][4] == 1)
				{
					OutPut << "  edge" << endl;
					OutPut << "  [" << endl;
					OutPut << "    id " << edge[i][j][2] << "" << endl;
					OutPut << "    source " << i << "" << endl;
					OutPut << "    target " << edge[i][j][0] << "" << endl;
					OutPut << "    label \"" << edge[i][j][1] << "\"" << endl;
					OutPut << "    value " << edge[i][j][3] << "" << endl;
					OutPut << "  ]" << endl;
				}
		OutPut << "]" << endl;
	}

	OutPut.close();
}

void swapEdge(float* a, float* b)
{
	swap(a[0], b[0]);
	swap(a[1], b[1]);
	swap(a[2], b[2]);
	swap(a[3], b[3]);
	swap(a[4], b[4]);
}

void orderNodesEdgeBaseOnLableInc(vector<vector<float*>> edge,int processor)
{
	int n = edge.size();
	omp_set_num_threads(processor);
#pragma omp parallel for  shared(edge) schedule(dynamic)
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < edge[i].size(); j++)
		{
			for (int z = j + 1; z < edge[i].size(); z++)
			{
				if (edge[i][j][1] > edge[i][z][1])
				{
					swap(edge[i][j][0], edge[i][z][0]);
					swap(edge[i][j][1], edge[i][z][1]);
					swap(edge[i][j][2], edge[i][z][2]);
					swap(edge[i][j][3], edge[i][z][3]);
					swap(edge[i][j][4], edge[i][z][4]);
				}
			}
		}
	}
}

void orderNodesEdgeBaseOnLableDec(vector<vector<float*>> edge, int processor)
{
	int n = edge.size();
	omp_set_num_threads(processor);
#pragma omp parallel for  shared(edge) schedule(dynamic)
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < edge[i].size(); j++)
		{
			for (int z = j + 1; z < edge[i].size(); z++)
			{
				if (edge[i][j][1] < edge[i][z][1])
				{
					swap(edge[i][j][0], edge[i][z][0]);
					swap(edge[i][j][1], edge[i][z][1]);
					swap(edge[i][j][2], edge[i][z][2]);
					swap(edge[i][j][3], edge[i][z][3]);
					swap(edge[i][j][4], edge[i][z][4]);
				}
			}
		}
	}
}

void listPermutation(int* vec, int size)
{
	for (int i = 0; i < size; i++)
		swap(vec[i], vec[randomInteger(i, size - 1)]);
}

void edgeLalbelFillEdgeBetweenness(vector<vector<float*>> edge, int depth,int processor)
{
	float a = 0;
	int front = 0, end = 0, little = 0;
	int i, j;
	int n = edge.size();

	float* local = new float[processor*n];
	float* distance = new float[processor*n];
	float* x = new float[processor*n];

	omp_set_num_threads(processor);
	int t = 0;
#pragma omp parallel for   shared(edge) private(t,front,end,a,i,j,little) schedule(dynamic)
	for (int node = 0; node < n; node++)
	{
		t = omp_get_thread_num();
		front = 0;
		end = 0;
		for (j = 0; j < n; j++)
		{
			x[t*n+j] = -1;
			distance[t*n + j] = 1000;
			local[t*n + j] = 0;
		}
		x[t*n + 0] = node;
		distance[t*n + node] = 0;
		while (front <= end&&distance[t*n + (int)x[t*n + front]] <= depth)
		{
			a = x[t*n + front];
			for each (float* neighbor in edge[(int)a])
				if (distance[t*n + (int)neighbor[0]] == 1000)
				{
					distance[t*n + (int)neighbor[0]] = distance[t*n + (int)a] + 1;
					end++;
					x[t*n + end] = neighbor[0];
				}
			front++;
		}
		front--;
		for (j = front; j != 0; j--)
		{
			a = x[t*n + j];
			little = 0;
			for each (float* neighbor in edge[(int)a])
				if (distance[t*n + (int)neighbor[0]] < distance[t*n + (int)a])
					little++;
			local[t*n + (int)a]++;
			for each (float* neighbor in edge[(int)a])
			{
				if (little != 0 && distance[t*n + (int)neighbor[0]] < distance[t*n + (int)a])
				{
#pragma omp atomic
					neighbor[1] += local[t*n + (int)a] / little;
					local[t*n + (int)neighbor[0]] += local[t*n + (int)a] / little;
					for each (float* var in edge[(int)neighbor[0]])
						if (var[0] == a)
						{
#pragma omp atomic
							var[1] += local[t*n + (int)a] / little;
							break;
						}
				}
			}
		}
	}
	delete local;
	delete distance;
	delete x;
}

void cdLPA()
{

}

float modularityCalculator(vector<vector<float*>> edge, vector<float*> nodes)
{
	float modularity = 0;
	int m = 0;
	for (int i = 0; i < edge.size(); i++)
		m += edge[i].size();
	for (int i = 0; i < nodes.size(); i++)
		for (int j = 0; j < nodes.size(); j++)
		{
			bool haveedge = false;
			for each (float* neighbor in edge[i])
				if (neighbor[0] == j)
				{
					haveedge = true;
					break;
				}
			if (nodes[i][1] == nodes[j][1])
			{
				if (haveedge)
					modularity += (1 - ((edge[i].size()*edge[j].size()) / (float)m));
				else
					modularity += -(((int)(edge[i].size())*(int)(edge[j].size())) / (float)m);
			}
		}
	modularity = modularity / (float)m;
	return modularity;
}

void edgeClustringCoefficiency(vector<vector<float*>> edge)
{
	int n = edge.size();
	for (int nodei = 0; nodei < n; nodei++)
	{
		int nodeiSize = 0, nodejSize = 0;
		nodeiSize = edge[nodei].size();
		int k = 0;
		for each (float* var in edge[nodei])
		{
			if (var[4] == 1)
			{
				int nodej = var[0];
				nodejSize = edge[nodej].size();
				for each (float* var2 in edge[nodej])
					for each (float* var3 in edge[var2[0]])
						if (var3[0] == nodei)
						{
							k++;
							break;
						}
			}
			k++;
			if (nodeiSize == 1 || nodejSize == 1)
				var[1] = 1000000;
			else if (nodeiSize < nodejSize)
				var[1] = k / (float)(nodeiSize - 1);
			else
				var[1] = k / (float)(nodejSize - 1);
			k = 0;
		}
	}
}

void correctGraphCommunityLable(vector<float*> nodes)
{
	unordered_map<int, int> p;
	int n = nodes.size();
	int k = 1;
	for (int i = 0; i < n; i++)
	{
		if (p[(int)nodes[i][1]] == 0)
		{
			p[(int)nodes[i][1]] = k;
			nodes[i][1] = p[(int)nodes[i][1]];
			k++;
		}
		else
			nodes[i][1] = p[(int)nodes[i][1]];
	}
}

vector<float*> readNodeCommunity(string filetype, string path,int startIndexInFile)
{
	int n = 0;
	register char c;
	string word = "";
	vector<float*> nodes;
	ifstream File(path);
	if (stringEqual(filetype, "gml"))
	{
		///////////////////////////////not implemented
		while (File.get(c) && c != '[') {}
		while (true)
		{
			while (File.get(c) && c != 'n' && c != 'g') {}
			if (c == 'g')
				break;
			nodes.push_back(new float[10]);
			for (int i = 0; i < 9; i++)
			{
				while (File.get(c) && (47 > c || c > 58) && c != '-') {}
				word = c;
				while (File.get(c) && ((47 < c&&c < 58) || c == '.'))
					word += c;
				nodes[n][i] = stof(word);
			}
			nodes[n][1] = n;
			nodes[n][9] = -1;
			n++;
		}
	}
	else if (stringEqual(filetype, "csv"))
	{
		float node = 0;
		File.get(c);
		word = "";
		while (((47 < c&&c < 58)))
		{
			word += c;
			File.get(c);
			if (c == '\t'||c==' ')
			{
				node = stof(word) - startIndexInFile;
				File.get(c);
				word = "";
				while (((47 < c&&c < 58)))
				{
					word += c;
					File.get(c);
				}
				nodes.push_back(new float[2]{ node,stof(word) });
				word = "";
				File.get(c);
				File.get(c);
			}
		}
	}
	File.close();
	return nodes;
}

void prepareForLPA(vector<float*> nodes, vector<vector<float*>> edge)
{
	int n = nodes.size();
	for (int i = 0; i < n; i++)
		nodes[i][1] = i;
}

bool checkLPA_Stop_Criterion(vector<float*> nodes, vector<vector<float*>> edge)
{
	int n = nodes.size();
	bool finish = true;
	for (int i = 0; i < n; i++)
	{
		int node = nodes[i][0];
		vector<int*> labels;
		for each (float* var in edge[node])
		{
			bool flag = true;
			int j = 0;
			for (; j < labels.size(); j++)
				if (labels[j][0] == nodes[(int)var[0]][1])
				{
					flag = false;
					labels[j][1] += 1;
					break;
				}
			if (flag)
				labels.push_back(new int[2]{ ((int)(nodes[(int)var[0]][1])) ,1 });
		}
		int max = 0;
		vector<int> maxl;
		for (int j = 1; j < labels.size(); j++)
			if (labels[max][1] < labels[j][1])
				max = j;
		for (int j = 0; j < labels.size(); j++)
			if (labels[max][1] == labels[j][1])
				maxl.push_back(j);
		bool f = false;
		for (int j = 0; j < maxl.size(); j++)
			if (nodes[node][1] == labels[maxl[j]][0])
			{
				f = true;
				break;
			}
		if (!f)
			finish = false;
	}
	return finish;
}

float NMI(vector<float*> nodes, vector<float*> community)
{
	correctGraphCommunityLable(nodes);
	float nmi = 0, up = 0, down = 0;
	int n = nodes.size();
	int countGuess = 0, countGold = 0;
	float* NRow;
	float* NCol;
	for (int i = 0; i < n; i++)
	{
		if (nodes[i][1] > countGuess)
			countGuess = floor(nodes[i][1]);
		if (community[i][1] > countGold)
			countGold = floor(community[i][1]);
	}
	NRow = new float[countGold] {0};
	NCol = new float[countGuess] {0};
	float** matrix = new float*[countGold];
	for (int i = 0; i < countGold; i++)
	{
		matrix[i] = new float[countGuess];
		for (int j = 0; j < countGuess; j++)
			matrix[i][j] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		matrix[(int)(community[i][1]) - 1][(int)(nodes[i][1]) - 1]++;
		NRow[(int)(community[i][1]) - 1]++;
		NCol[(int)(nodes[i][1]) - 1]++;
	}
	for (int i = 0; i < countGold; i++)
		if (NRow[i] != 0)
			down += NRow[i] * log2(NRow[i] / (float)(n));
	for (int i = 0; i < countGuess; i++)
		if (NCol[i] != 0)
			down += NCol[i] * log2(NCol[i] / (float)(n));
	for (int i = 0; i < countGold; i++)
		for (int j = 0; j < countGuess; j++)
			if (matrix[i][j] != 0)
				up += matrix[i][j] * log2((matrix[i][j] * (float)(n) / ((NRow[i] * NCol[j]))));
	up *= (float)-2;
	nmi = up / down;
	delete NRow;
	delete NCol;
	delete matrix;
	return nmi;
}

