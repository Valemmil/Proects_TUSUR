#include <iostream>
#include <string>
#include <fstream>

class HashTable 
{
private:
	const static int size = 30;
	std::string table[size];

	int addString(std::string pushvalue)
	{
		int key = 0, res = 0;
		for (int i = 0; i < (int)(pushvalue.length()); i++)
		    key += pushvalue[i];
		key %= size;
		res = searchEmptyPlace(key, pushvalue);
		if ((res <= size) && (res > 0))
		    return res;
		return -1;
	}
		
	int searchEmptyPlace(int key, std::string pushvalue)
	{
		for (int i = 0; i < size; i++)
		    if (table[(key + i) % size] == "")
		    {
		        table[(key + i) % size] = pushvalue;
		        return i;
		    }
		return 0;
	}

public:
	
	void readFile(const char* name)
	{
		int res;
		std::string pushvalue;
		std::ifstream fin(name);
		if (!fin.is_open()) 
		    std::cout << "Ошибка файла: " << name << std::endl;
		while (getline(fin, pushvalue))
		{
		    res = addString(pushvalue);
		    if (res != -1)
		        std::cout << "строка: " << pushvalue << " добавлена за " << res << " обходов" << std::endl;
		     else
		        std::cout << "ошибка добавления строки:" << pushvalue << std::endl;
		}
		std::cout << "Файл входных данных прочитан\n\n";
	}


};


int main() 
{
	setlocale(LC_ALL, "Russian");
    int control = 1;
    HashTable table;

    do
    {
        switch (control)
        {
        case 0:
            std::cout << "Выберите пункт:\n1 Добавить элементы из файла\n2 Удалить элемент\n3 Найти элемент\n9 Выйти из программы\n>> " << std::endl;
			std::cin >> control;
			break;
        case 1:
            table.readFile("input.txt");
			control = 0;
            break;
        default:
            control = 0;
        }


    } while (control != 9);
	return 0;
}

//#include <iostream>
//#include <string>
//#include <fstream>
//
//
////using namespace std;
//
//class Hes_table
//{
//
//private:
//    const static int Hes_size = 30;
//    static std::string* table[Hes_size];
//
//    int addString(std::string pushvalue)
//    {
//        int key = 0, res = 0;
//        for (int i = 0; i < (int)(pushvalue.length()); i++)
//            key += pushvalue[i];
//        key %= Hes_size;
//        res = searchEmptyPlace(key, pushvalue);
//        if ((res <= Hes_size) && (res > 0))
//            return res;
//        return -1;
//    }
//
//    int searchEmptyPlace(int key, std::string pushvalue)
//    {
//        for (int i = 0; i < Hes_size; i++)
//            if (table[(key + i) % Hes_size] == nullptr)
//            {
//                table[(key + i) % Hes_size] = &pushvalue;
//                return i;
//            }
//        return 0;
//    }
//
//public:
//
//    void readFile(const char* name)
//    {
//        int res;
//        std::string pushvalue;
//        std::ifstream fin(name);
//        //if (!fin.is_open()) 
//            //std::cout << "Ошибка файла: " << name << std::endl;
//        while (getline(fin, pushvalue))
//        {
//            res = addstring(pushvalue);
//            if (res != -1)
//                //std::cout << "строка: " << pushvalue << " добавлена за " << res << " обходов" << std::endl;
//           // else
//                //std::cout << "ошибка добавления строки:" << pushvalue << std::endl;
//        }
//        //std::cout << "Файл входных данных прочитан\n\n";
//    }
//};
//
//
//int main()
//{
//    //setlocale(LC_ALL, "Russian");
//    int control = 0;
//    Hes_table* table = new Hes_table();
//
//    
//    /* do
//     {
//         switch (control)
//         {
//         case 0:
//             std::cout << "Выберите пункт:\n1 Добавить элементы из файла\n2 Удалить элемент\n3 Найти элемент\n9 Выйти из программы" << std::endl;
//             break;
//         case 1:
//             table.readFile("input.txt");
//             break;
//         default:
//             control = 0;
//             break;
//         }
//     } while (control != 9);
//     return 0;*/
//}