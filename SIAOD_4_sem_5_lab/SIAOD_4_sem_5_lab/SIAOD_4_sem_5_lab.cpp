#include <iostream>
#include <string>
#include <fstream>

class HashTable{
private:
	const static int size = 20;
	std::string table[size];

	int hashFunc(std::string pushvalue) {
		int key = 0;
		for (int i = 0; i < (int)(pushvalue.length()); i++)
			key += pushvalue[i];
		return key % size;
	}

	int addString(std::string pushvalue){
		int res = 0;
		res = searchEmptyPlace(hashFunc(pushvalue), pushvalue);
		if ((res <= size) && (res >= 0))
			return res;
		return -1;
	}

	int searchEmptyPlace(int key, std::string pushvalue){
		std::string temp;
		temp = (char)-1;
		for (int i = 0; i < size; i++)
			if ((table[(key + i) % size] == "") || (table[(key + i) % size] == temp)){
				table[(key + i) % size] = pushvalue;
				return i;
			}
		return -1;
	}

public:

	void showTable() {
		std::string temp;
		temp = (char)-1;
		for (int i = 0; i < size; i++) {
			if (table[i] == temp) {
				std::cout << i + 1 << ". " << std::endl;
				continue;
			}
			std::cout << i + 1 << ". " << table[i] << std::endl;
		}
	}

	void readFile(const char* name)
	{
		int res;
		std::string pushvalue;
		std::ifstream fin(name);
		if (!fin.is_open())
			std::cout << "Ошибка файла: " << name << std::endl;
		while (getline(fin, pushvalue)){
			res = addString(pushvalue);
			if (res != -1)
				std::cout << "строка: " << pushvalue << " добавлена за " << res << " обходов" << std::endl;
			else
				std::cout << "ошибка добавления строки:" << pushvalue << std::endl;
		}
		std::cout << "Файл входных данных прочитан\n\n";
	}

	int deliteString(std::string pushvalue) {
		for (int i = 0; i < size; i++)
			if (table[(hashFunc(pushvalue) + i) % size] == pushvalue){
				table[(hashFunc(pushvalue) + i) % size] = (char) -1;
				return (hashFunc(pushvalue) + i) % size;
			}
		return -1;
	}

	int searchString(std::string pushvalue) {
		int res = -1;
		for (int i = 0; i < size; i++)
			if ((table[(hashFunc(pushvalue) + i) % size] == pushvalue)) {
				std::cout << "Строка найдена в элементе таблицы под номером " << (hashFunc(pushvalue) + i) % size + 1 << " За " << i << " проб" << std::endl;
				res = (hashFunc(pushvalue) + i) % size;
				return res;
			}
			else if (table[(hashFunc(pushvalue) + i) % size] == "") {
				break;
			}
		std::cout << "Строка не найдена" << std::endl;
		return res;
	}

	void addOneString(std::string pushvalue) {
		int res;
		res = addString(pushvalue);
		if (res != -1)
			std::cout << "строка: " << pushvalue << " добавлена за " << res << " обходов" << std::endl;
		else
			std::cout << "ошибка добавления строки:" << pushvalue << std::endl;
	}
};


int main()
{
	setlocale(LC_ALL, "Russian");
	int control = 0;
	std::string temp;
	HashTable table;

	do{
		switch (control){
		case 0:
			std::cout << "Выберите пункт:\n1 Добавить элементы из файла\n2 Посмотреть хэш-таблицу\n3 Удалить элемент\n4 Найти элемент\n5 Добавить один элемент\n9 Выйти из программы\n>> ";
			std::cin >> control;
			break;
		case 1:
			table.readFile("D:\\File\\Proect\\SIAOD_4_sem_5_lab\\input.txt");
			control = 0;
			std::cout << std::endl;
			break;
		case 2:
			table.showTable();
			control = 0;
			std::cout << std::endl;
			break;
		case 3:
			std::cout << "Введите строку: ";
			std::cin >> temp;
			table.deliteString(temp);
			control = 0;
			std::cout << std::endl;
			break;
		case 4:
			std::cout << "Введите строку: ";
			std::cin >> temp;
			table.searchString(temp);
			control = 0;
			std::cout << std::endl;
			break;
		case 5:
			std::cout << "Введите строку: ";
			std::cin >> temp;
			table.addOneString(temp);
			control = 0;
			std::cout << std::endl;
			break;
		default:
			control = 0;
		}


	} while (control != 9);
	return 0;
}