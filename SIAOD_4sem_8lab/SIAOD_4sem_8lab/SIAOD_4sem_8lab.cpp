#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("in.txt");
ofstream fout("out.txt");

struct Edge // Сохранить график как структуру данных
{
	int start;
	int end;
	int length;
};

void editV(vector<int>& visited, int first, int end)
{
	int temp = visited[first], main = visited[end];
	if (main > temp)
		swap(main, temp);

	for (int i = 0; i < visited.size(); i++)
		if (visited[i] == temp)
			visited[i] = main;
}

bool compare(Edge a, Edge b)
{
	return a.length < b.length;
}

void Kruskal(vector<Edge>& arr, vector<int>& visited)
{
	int M, N;
	M = visited.size();
	N = arr.size();
	for (int i = 0; i < N; i++)
	{
		fin >> arr[i].start >> arr[i].end >> arr[i].length;
	}
	sort(arr.begin(), arr.end(), compare);
	int weight = 0;
	fout << "Рёбра, входящие в минимальное покрывающее дерево: \n";
	for (int i = 0; i < N; i++)
	{
		if (visited[arr[i].start] != visited[arr[i].end])
		{
			weight += arr[i].length;

			editV(visited, arr[i].start, arr[i].end);

			/*cout << "visited: ";
			for (int k = 0; k < m; k++)
				cout << visited[k] << " ";
			cout << endl;*/

			fout << "(" << arr[i].start << ", " << arr[i].end << ") (" << arr[i].length << ")" << endl;
		}
	}
	fout << endl << "Минимальный вес связующего дерева: ";
	fout << weight << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int M, N;
	fin >> M >> N;
	vector<Edge> arr(N);
	vector<int> visited(M);
	for (int i = 0; i < M; i++) {
		visited[i] = i;
	}
	Kruskal(arr, visited);
	fin.close();
	fout.close();
}