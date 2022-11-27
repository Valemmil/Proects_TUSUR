#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

int n;
vector <vector<int>> v;//двойной массив вектор
vector<bool> color;
vector<int> steck;
ofstream os("out.txt");

auto fund(int to) {
    int i;
    for (i = 0; i < steck.size(); i++)
        if (steck[i] == to)
            break;
    if (steck.size() - i > 2) {
        for (i; i < steck.size(); i++)
            os << steck[i] + 1 << " ";
        os << to + 1 << endl;
    }
}

void dfs(int pos, int back = 0) //функция счёта длины 
{
    steck.push_back(pos);
    for (auto to : v[pos]) {
        if (color[to]) {
            if(to != back)
                fund(to);
            continue;
        }
        color[to] = 1;
        back = pos;
        dfs(to, back);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int n1, n2;
    int num;
    ifstream fin("input.txt");
    fin >> n >> num;
    os << "Количество вершин: ";
    os << n << endl;
    os << "Количество рёбер: ";
    os << num << endl << endl;

    v.resize(n);
    color.resize(n);
    for(int k = 0; k < num; k++) {
        fin >> n1 >> n2;
        n1--;
        n2--;
        v[n1].push_back(n2);
        v[n2].push_back(n1);
    }

    for (int i = 0; i < v.size(); i++)
        sort(v[i].begin(), v[i].end());

    os << "Фундаментальные циклы:\n";
    color[0] = 1;
    dfs(0);

    fin.close();
    os.close();
    return 0;
}