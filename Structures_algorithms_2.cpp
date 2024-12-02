#include <iostream>
#include <ctime>
#include <string>



using namespace std;

int hash_function(int r) {
	return ((r / 100000 + r / 10000 % 10) % 10 * 100 + (r / 1000 % 100 + r / 100 % 1000) % 10 * 10
							 + (r / 10 % 10000 + r % 10) % 10);
}



void indents() {
	for (int i = 0; i < 78; i++)
		cout << "-";
}



int input() {
	cout << "\nВведите шестизначный элемент: ";
	int r;
	cin >> r;

	if (r >= 100000 and r < 1000000)
		return r;
	else {
		cout << "ОШИБКА ВВОДА\n";
		input();
	}
}



int generation(bool show) {
	int r = (rand() % 9 + 1) * 100000 + rand() * rand() % 100000;

	if (show) cout << "\nСгенерированное значение: " << r << "\n";

	return r;
}



int setting_value(bool indent) {
	if (indent) cout << "\n";

	cout << "\nВыберите способ ввода:\n";
	cout << "- самостоятельно ввести       - нажмите 1\n";
	cout << "- автоматически сгенерировать - нажмите 2\n";
	cout << "--------------------------------------> ";

	int var;
	cin >> var;

	if (var == 1)
		return input();
	else if (var == 2)
		return generation(true);
	else
		setting_value(true);
}



void output_hash_table(int table[], int key_value[]) {
	cout << "\n\nХеш-таблица:\n";

	for (int i = 0; i < key_value[3]; i++) {
		if (i != 0 and i % 5 == 0)
			cout << endl;
		cout << i << ")\t" << table[i] << "\t";
	}
}



void add(int table[], int key_value[], int r, bool show) {
	int pos = hash_function(r);

	int message = 0;

	int n = 0;
	for (; n < key_value[5]; n++) {
		if (table[(pos + n * n) % key_value[3]] == 0 || table[(pos + n * n) % key_value[3]] == -1) {
			message = (pos + n * n) % key_value[3];
			table[message] = r;
			key_value[4] += n + 1;
			break;
		}
	}

	if (n == key_value[5]) {
		while (table[(pos + n) % key_value[3]] != 0 && table[(pos + n) % key_value[3]] != -1)
			n++;

		message = (pos + n) % key_value[3];
		table[message] = r;
		key_value[4] += n + 1;
	}

	if (show) {
		cout << "\n\nЭлемент `" << r << "` добален в индекс `" << message << "`";
	}
}



void end(int table[], int key_value[], bool show) {
	if (show) {
		output_hash_table(table, key_value);

		cout << "\n\n";
		system("pause");
		cin.get();
	}
}



void calc_parameters(int table[], int key_value[], bool show) {
	if (show) cout << "\n";

	output_hash_table(table, key_value);

	cout << "\n\nРассчитанные параметры:\n";
	cout << "- коэффициент заполнения таблицы = " << 1.0 * key_value[2] / key_value[3] << "\n";
	cout << "- среднее число шагов            = " << 1.0 * key_value[4] / key_value[6] << "\n";
	cout << "- количество элементов в таблице = " << key_value[2] << "\n";

	if (show) {
		cout << "\n";
		system("pause");
	}
}



void search(int table[], int key_value[], int r, bool show) {
	int pos = hash_function(r);

	int n = 0;
	for (; n < key_value[5]; n++) {
		if (table[(pos + n * n) % key_value[3]] == 0) {
			cout << "\nЭлемент `" << r << "` не найден в таблице";
			key_value[0] = key_value[1] = -1;
			break;
		}
		else if (table[(pos + n * n) % key_value[3]] == r) {
			cout << "\nЭлемент `" << r << "` найден в индексе `" << (pos + n * n) % key_value[3] << "`";
			key_value[0] = (pos + n * n) % key_value[3];
			key_value[1] = r;
			break;
		}
	}

	if (n == key_value[5]) {
		int transition = key_value[5] + key_value[3];

		for (; n < transition; n++)
			if (table[(pos + n) % key_value[3]] == 0) {
				cout << "\nЭлемент `" << r << "` не найден в таблице";
				key_value[0] = key_value[1] = -1;
				break;
			}
			else if (table[(pos + n) % key_value[3]] == r) {
				cout << "\nЭлемент `" << r << "` найден в индексе `" << (pos + n) % key_value[3] << "`";
				key_value[0] = (pos + n) % key_value[3];
				key_value[1] = r;
				break;
			}
	}

	if (n == key_value[5] + key_value[3]) {
		cout << "\nЭлемент `" << r << "` не найден в таблице";
		key_value[0] = key_value[1] = -1;
	}

	end(table, key_value, show);
}



void addition(int table[], int key_value[], int r, bool show) {
	search(table, key_value, r, false);

	if (key_value[1] == -1) {
		add(table, key_value, r, true);
		key_value[2]++;
		key_value[6]++;
	}

	end(table, key_value, show);
}



void removal(int table[], int key_value[], int r, bool show) {
	search(table, key_value, r, false);

	if (key_value[1] != -1) {
		table[key_value[0]] = -1;
		key_value[2]--;

		cout << "\n\nЭлемент `" << r << "` удален из индекса `" << key_value[0] << "`";
	}

	end(table, key_value, show);
}



void replacement(int table[], int key_value[]) {
	cout << "\n\nВыберите способ ввода:\n";
	cout << "- самостоятельно ввести       - нажмите 1\n";
	cout << "- автоматически сгенерировать - нажмите 2\n";
	cout << "--------------------------------------> ";

	int r1, r2;

	int var;
	cin >> var;

	if (var == 1) {
		r1 = input();
		r2 = input();
	}
	else {
		r1 = generation(true);
		r2 = generation(true);
	}

	removal(table, key_value, r1, false);

	cout << "\n";
	addition(table, key_value, r2, false);

	end(table, key_value, true);
}



void choice(int table[], int key_value[]) {
	cout << "\n\nВыберите количество элементов:\n";
	cout << "- ввести один элемент           - нажмите 1\n";
	cout << "- ввести n случайных элементов  - нажмите 2\n";
	cout << "----------------------------------------> ";

	int var;
	cin >> var;

	if (var == 1)
		addition(table, key_value, setting_value(false), true);

	else if (var == 2) {
		int size_n = key_value[3] - key_value[2];

		cout << "\nВведите n (от 1 до " << size_n << "): ";

		int n;
		cin >> n;

		if (n <= size_n) {
			for (int i = 0; i < n; i++) {
				addition(table, key_value, generation(false), false);
				if (i != n - 1) {
					cout << "\n";
					indents();
				}
			}

			end(table, key_value, true);
		}
	}

	else
		choice(table, key_value);
}



int main() {
	setlocale(LC_ALL, "Russian");

	srand(time(NULL));

	int size_sample = 45;
	int size_table = size_sample * 1.5;
	int* sample = new int[size_sample];
	int* table = new int[size_table];
	int transition = 50;
	int steps = 0;
	int number_placements = size_sample;

	int key_value[7]{ 0, 0, size_sample, size_table, steps, transition, number_placements };

	for (int i = 0; i < key_value[3]; i++)
		table[i] = 0;

	int i = 0;
	while (i < key_value[2]) {
		int r = generation(false);
		bool flag = true;

		for (int n = 0; n < i; n++) {
			if (sample[n] == r) {
				flag = false;
				break;
			}
		}

		if (flag) {
			sample[i] = r;
			i++;
		}
	}

	cout << "Последовательность сгенерированных ключей:\n";

	for (int i = 0; i < key_value[2]; i++) {
		int r = sample[i];

		if (i != 0 and i % 10 == 0)
			cout << endl;
		cout << r << "\t";

		add(table, key_value, r, false);
	}

	calc_parameters(table, key_value, false);

	while (true) {
		cout << "\n";		
		indents();

		cout << "\n\nВыберите действие:\n";
		cout << "- найти элемент        - нажмите 1\n";
		cout << "- добавить элемент     - нажмите 2\n";
		cout << "- удалить элемент      - нажмите 3\n";
		cout << "- заменить элемент     - нажмите 4\n";
		cout << "- рассчитать параметры - нажмите 5\n";
		cout << "- завершить программу  - нажмите 6\n";
		cout << "-------------------------------> ";		

		string var;
		getline(cin, var);

		cout << "\n";
		indents();

		if (var == "1") search(table, key_value, setting_value(true), true);
		else if (var == "2") choice(table, key_value);
		else if (var == "3") removal(table, key_value, setting_value(true), true);
		else if (var == "4") replacement(table, key_value);
		else if (var == "5") calc_parameters(table, key_value, true);
		else if (var == "6") break;
	}

	calc_parameters(table, key_value, false);



	delete[] sample;
	delete[] table;

	cout << "\n\n\n";
	system("pause");
}
