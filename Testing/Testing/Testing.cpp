#pragma
#include <iostream>
#include <cstdlib>
/*
Напишите проограмму, которая нааходит множество фундаментальных циклов связного неориентированного графа.
Для представления графа в программе использовать списки смежности.
Данные о графе вводятся из файла.
Программа должна вывести для каждого цикла множество вершин, входящий в каждый из найденных циклов.
После завершения работы с динамическими структурами данных необходимо освободить занимаемую ими память.

*/

#include <time.h>
using namespace std;


#define Type int // Чтобы в списке можно 
#define type "%d" //было хранить разные типы данных

using namespace std;


class Node // Класс элемента списка
{

private:
	Type data; // данные данного элемента списка
	Node* next; // указатель на следующий элемент списка

public:

	Node(Type a, Node* b = NULL) // Создание последующего элемента списка
	{
		data = a;
		next = b;
	}

	Type get_data()
	{
		return data;
	}

	Node* get_next()
	{
		return next;
	}

	void _set_elem(Type a)
	{
		data = a;

	}

	void _set_next(Node* a)
	{
		next = a;
	}


	~Node()
	{
		delete(next);
	}
};


class NodeList
{

private:

	Node* Head = NULL; // указатель на первый элемент списка
	static int IDS; // индивидуальный
	int m_id;       // 				индификатор списка


public:

	NodeList()
	{

		m_id = IDS++;

		Head = NULL;  // В самом начале список ни на что не указывает
	}


	void AddNode(Type a) // добавить элемент в список
	{
		if (Head == NULL)
		{
			Node* new_node;
			new_node = new Node(a);
			if (new_node == NULL)
			{
				delete(new_node);
				cout << "error" << endl;
			}
			else
			{
				Head = new_node;
			}

		}

		else
		{

			Node* P = Head;
			while (P->get_next() != NULL)
			{


				P = P->get_next();

			}

			Node* new_node;

			new_node = new Node(a);
			if (new_node == NULL)
				cout << "Error" << endl;
			else
			{
				P->_set_next(new_node);
			}




		}
	}

	bool IsNodeExist(Type a) // проверить существует ли элемент в списке
	{
		if (Head == NULL)
		{

			return false;
		}
		else
		{
			Node* P = Head;
			while (P != NULL)
			{

				if (P->get_data() == a)
				{
					return true;
				}
				P = P->get_next();
			}
		}
		return false;

	}

	void AddNodeIn(Type a, int k = 1) // добавить элемент списка на k-ую позицию
	{
		if (Head == NULL)
		{
			cout << "is empty";
		}
		else if (k == 1)
		{
			Node* new_node;
			new_node = new Node(a, Head);
			if (new_node == NULL)
				cout << "Error" << endl;
			else
				Head = new_node;
			delete(new_node);
		}
		else
		{

			Node* P = MoveTo(k - 1);
			if (P == NULL)
			{
				cout << "Error 1" << endl;
			}
			else
			{

				Node* new_node;
				new_node = new Node(a, P->get_next());
				if (new_node == NULL)
					cout << "Error 2" << endl;
				else
					P->_set_next(new_node);
				delete(new_node);
			}

		}
	}

	Type RemoveNodeIn(int k = 1) // удалить элемент списка на k-ой позиции
	{
		if (Head == NULL)
		{
			cout << "It is empty";
		}
		else if (k == 1)
		{
			Type get = Head->get_data();
			Node* p;
			p = Head;
			Head = Head->get_next();

			delete(p);

			return get;
		}
		else if (k < 1)
		{

			cout << "Error 3" << endl;
			return 0;
		}
		else
		{
			k = k - 1;
			int i = 1;
			Node* P = Head;
			while (P != NULL && i < k)
			{
				P = P->get_next();
				i++;
			}
			if (i == k && P->get_next() != NULL)
			{

				if (P->get_next() == NULL)
				{

				}
				Type get = P->get_next()->get_data();
				P->_set_next(P->get_next()->get_next());



				free(P->get_next());
				delete(P);
				return get;
			}
			else
			{
				cout << "Error 4" << endl;
				return 0;
			}
		}
	}

	void Change(Type a, int k) // поменять k-ый элемент списка
	{
		RemoveNodeIn(k);
		AddNodeIn(a, k);

	}

	Type RemoveAndGet_Node() //лишнее
	{

		if (Head != NULL)
		{
			Type get = Head->get_data();
			Node* p = Head;
			Head = Head->get_next();
			delete p;
			//free(p);

			return get;
		}
		else
		{
			cout << "Error 5 - ";
			return 0;
		}


	}

	Type GetNode(int k) // полкчить данные из k-го элемента списка
	{
		if (Head == NULL)
		{
			cout << "It is empty";
		}
		else if (k == 1)
		{
			Type get = Head->get_data();

			return get;
		}
		else if (k < 1)
		{

			cout << "Error 3" << endl;
			return 0;
		}
		else
		{
			k = k - 1;
			int i = 1;
			Node* P = Head;
			while (P != NULL && i < k)
			{
				P = P->get_next();
				i++;
			}
			if (i == k && P->get_next() != NULL)
			{

				if (P->get_next() == NULL)
				{

				}
				Type get = P->get_next()->get_data();



				return get;
			}
			else
			{
				cout << "Error12" << endl;
				return 0;
			}
		}

	}

	Node* isGet(int k) // полкчить данные из k-го элемента списка
	{
		if (Head == NULL)
		{
			return NULL;
		}
		else if (k == 1)
		{

			return Head->get_next();
		}
		else if (k < 1)
		{


			return NULL;
		}
		else
		{
			k = k - 1;
			int i = 1;
			Node* P = Head;
			while (P != NULL && i < k)
			{
				P = P->get_next();
				i++;
			}
			if (i == k && P->get_next() != NULL)
			{

				return P;
			}
			else
			{

				return NULL;
			}
		}

	}
	Type Get_Node() // получить данные первого элемента списка
	{

		if (Head != NULL)
		{
			Type get = Head->get_data();

			return get;
		}
		else
		{
			cout << "Error 6 - ";
			return 0;
		}


	}

	bool DeleteNode(int a)
	{

		int k = 1;

		Node* node = NULL;
		if (Head == NULL)
		{
			return false;
		}

		if (Head->get_data() == a && Head->get_next() == NULL)
		{
			Head = NULL;
			return false;
		}
		if (Head->get_data() == a)
		{
			Head = Head->get_next();
			return false;
		}
		Node* nodeF = node;
		do
		{
			node = node->get_next();

			if (node == NULL)
				return false;

			if (node->get_data() == a)
			{

				nodeF->_set_next(node->get_next());
				return true;
			}

			nodeF = node;
		} while (node != NULL);
		return true;
	}
	void Print() // напечатать список
	{

		if (Head != NULL)
		{

			Node* P = Head;
			while (P != NULL)
			{

				cout << P->get_data() << " ";
				P = P->get_next();
			}
			cout << endl;
			delete(P);
		}
		else
		{
			cout << "empty" << endl;
		}


	}

	Node* MoveTo(int k = 1) // полкчить элемент на k-ой позиции
	{
		if (k < 1)
			return NULL;
		if (Head != NULL)
		{
			int i = 1;
			Node* P = Head;
			while (P != NULL && i < k)
			{


				P = P->get_next();
				i++;
			}

			if (i == k)
				return P;
			else
				return NULL;
			delete(P);
		}
		else
		{
			return NULL;
		}


	}



	bool IsEmpty() // проверить, является ли список пустым
	{
		return Head == NULL;
	}


	void Delete() //Очистить список
	{
		while (MoveTo(1) != NULL)
		{
			RemoveNodeIn(1);
		}
		delete Head;
		Head = nullptr;
	}

	~NodeList()
	{
		Delete();
	}
};
int NodeList::IDS = 1;




class Adjacency_list //список смежности
{
private:

	static int IDS; // индивидуальный
	int m_id;

	NodeList** data; // массив указателей на списки
	int m;
public:
	Adjacency_list(int _m)
	{

		m_id = IDS++;
		m = _m;
		data = new NodeList * [m];
		int n;
		for (n = 0; n < m; n++)
		{
			data[n] = NULL; //обнуляем указатели
		}

	}

	NodeList* getList(int k)
	{
		return data[k];
	}


	int h(int key)
	{
		return key; // метод деления с остатком
	}

	void insertItem(int key, int a)//вставить элемент
	{
		int h = this->h(key);

		if (data[h] == NULL) //если списка нет, то создаем
		{

			NodeList* node_list;
			node_list = new NodeList;
			data[h] = node_list;
			data[h]->AddNode(a);

		}
		else
		{
			data[h]->AddNode(a); // метод добавляет элемент в список, возвращает количество проб

		}
	}

	void deleteItem(int key, int a)
	{
		int h = this->h(key);
		if (data[h] == NULL)
		{

		}
		else
		{
			data[h]->DeleteNode(a);

		}
	}





	void show()
	{
		int n;
		for (n = 0; n < m; n++)
		{
			cout << n + 1 << ") ";
			if (data[n] == NULL)
			{
				cout << "empty" << endl;
			}
			else
			{
				data[n]->Print();
			}
		}
	}


	~Adjacency_list()
	{
		delete[] data;

	}
};
int Adjacency_list::IDS = 0;



class Graph //список смежности
{
private:

	static int IDS; // индивидуальный
	int m_id;

	Adjacency_list* adjacency_list; // массив указателей на списки
	int m;
public:
	Graph(int _m = 0)
	{

		Stack = NULL;
		m_id = IDS++;
		m = _m;

		adjacency_list = new Adjacency_list(m);
	}




	void insertItem(int key, int a)//вставить элемент
	{
		adjacency_list->insertItem(key - 1, a);
	}

	void deleteItem(int key, int a)
	{

		adjacency_list->deleteItem(key - 1, a);

	}





	void show()
	{
		adjacency_list->show();
	}


	void Input(char* name)
	{
		FILE* f;
		fopen_s(&f, name, "r");

		if (f != 0)
		{

			int _m;
			fscanf_s(f, "%d", &_m);
			m = _m;
			while (!feof(f))
			{
				double a, b;
				fscanf_s(f, "%lf", &a);
				fscanf_s(f, "%lf", &b);
				this->insertItem(a, b);
			}
		}


	}

private:
	bool* Mark;
	int d;
	int* Stack;
	int StackNum;

public:
	void findFundCycles()
	{
		Mark = new bool[m];
		d = 0;

		Stack = new int[m];
		StackNum = 0;

		for (int k = 0; k < m; k++)
		{
			Mark[k] = false;
			Stack[k] = -1;
		}

		for (int k = 0; k < m; k++)
		{
			if (Mark[k] == false)
			{
				_findFundCycles(k);

			}
		}

	}

private:
	int num = 0;
	void _findFundCycles(int v)
	{

		Stack[StackNum] = v;
		StackNum += 1;

		Mark[v] = true; //посетили

	//	cout << v + 1;

		NodeList* list = adjacency_list->getList(v);
		int k = 1;
		Node* x = NULL;

		do
		{
			x = list->MoveTo(k);
			if (x == NULL)
				break;
			k++;

			if (x->get_data() != v)
			{

				// Пометить из которой пришли

				for (int z = 0; z < StackNum; z++)
				{
					//if (!Mark[v + 1])
					if (Stack[z] == x->get_data()) //-1
					{
						cout << x->get_data();

						cout << v + 1;
						//cout << Stack[z];

						for (int zk = StackNum - 1; Stack[zk] != x->get_data(); zk--)
						{

							cout << Stack[zk];
						}

						cout << x->get_data();
						cout << endl;
					}
				}

			}

		} while (x != NULL);

	}

	/*void _findFundCycles(int v) {
		for (int i = 0; i < )
	}

	void cycle(int v, int u) {
		num++;

	}*/

public:

	bool isEmpty()
	{
		if (m == 0)
			return  true;
		else
			return false;
	}

	int countNode()
	{
		return m;
	}

	bool isJoin(int a, int b)
	{
		NodeList* list = adjacency_list->getList(a - 1);
		int k = 1;
		Node* x = NULL;

		do
		{
			x = list->MoveTo(k);
			if (x == NULL)
				break;
			k++;

			if (x->get_data() == b - 1)
				return true;

		} while (x != NULL);


		list = adjacency_list->getList(b - 1);
		k = 1;
		do
		{
			x = list->MoveTo(k);
			if (x == NULL)
				break;
			k++;
			if (x->get_data() == a - 1)
				return true;

		} while (x != NULL);
		return false;
	}

	bool isJoinOneWay(int a, int b)
	{
		NodeList* list = adjacency_list->getList(a - 1);
		int k = 1;
		Node* x = NULL;

		do
		{
			x = list->MoveTo(k);
			if (x == NULL)
				break;
			k++;

			if (x->get_data() == b - 1)
				return true;

		} while (x != NULL);


		return false;
	}

	int countConnections()
	{
		int sum = 0;

		for (int k = 0; k < m - 1; k++)
		{
			for (int z = k + 1; z < m; z++)
			{
				if (isJoinOneWay(k, z))
				{
					sum++;
				}
				else
				{
					if (isJoinOneWay(z, k))
					{
						sum++;
					}
				}
			}


		}

		return sum;

	}

	~Graph()
	{
		delete(adjacency_list);
		delete[] Mark;
		delete[] Stack;
	}
};
int Graph::IDS = 0;


int main(int argc, char** argv) {


	char name[] = "Input.txt";
	Graph a(6);
	a.Input(name);
	a.show();
	a.findFundCycles();
	return 0;
}


