#include <iostream>
#include <ctime>
#include <string>



using namespace std;

int hash_function(int r) {
	return ((r / 100000 + r / 10000 % 10) % 10 * 100 + (r / 1000 % 100 + r / 100 % 1000) % 10 * 10 + (r / 10 % 10000 + r % 10) % 10);
}



int input() {
	cout << "\nВведите шестизначный элемент: ";
	int r;
	cin >> r;

	if ((r / 100000) != 0 and (r / 1000000) == 0)
		return r;
	else {
		cout << "ОШИБКА ВВОДА\n";
		input();
	}
}



int generation() {
	int r = rand() * rand() % 1000000;

	if (r / 100000 == 0)
		generation();
	else {
		cout << "\nСгенерированное значение: " << r << endl;
		return r;
	}
}



int setting_value() {
	cout << "\n\nВыберите способ задания значения элемента:\n";
	cout << "- самостоятельно ввести       - нажмите 1\n";
	cout << "- автоматически сгенерировать - нажмите 2\n";
	cout << "* примечание: при неправильном выборе \n  значение будет сгенерировано автоматически\n";
	cout << "--------------------------------------> ";

	int var;
	cin >> var;

	if (var == 1)
		return input();
	else
		return generation();
}



void output_hash_table(int table[], int size_table) {
	cout << "\n\nХеш-таблица:\n";

	for (int i = 0; i < size_table; i++) {
		if (i != 0 and i % 5 == 0)
			cout << endl;
		cout << i << ")\t" << table[i] << "\t";
	}
}



void add(int table[], int key_value[], int transition, int r, bool show) {
	int pos = hash_function(r);

	int message = 0;

	int n = 0;
	for (; n < transition; n++) {
		if (table[(pos + n * n) % key_value[3]] == 0 || table[(pos + n * n) % key_value[3]] == -1) {
			message = (pos + n * n) % key_value[3];
			table[message] = r;
			key_value[4] = key_value[4] + n + 1;
			break;
		}
	}

	if (n == transition) {
		while (table[(pos + n * n) % key_value[3]] != 0 && table[(pos + n * n) % key_value[3]] != -1)
			n++;

		message = (pos + n) % key_value[3];
		table[message] = r;
		key_value[4] = key_value[4] + n + 1;
	}

	if (show) {
		cout << "\n\nЭлемент `" << r << "` добален в индекс `" << message << "`";
	}
}



void end(int table[], int key_value[], bool show) {
	if (show) {
		output_hash_table(table, key_value[3]);

		cout << "\n\nДля продолжения что-нибудь введите: ";
		int s;
		cin >> s;

		cin.get();
	}
}



void calc_parameters(int key_value[]) {
	cout << "\n\nРассчитанные параметры:\n";
	cout << "- коэффициент заполнения таблицы = " << 1.0 * key_value[2] / key_value[3] << "\n";
	cout << "- среднее число шагов            = " << 1.0 * key_value[4] / key_value[2] << "\n";
}



void search(int table[], int key_value[], int transition, int r, bool show) {
	int pos = hash_function(r);

	int n = 0;
	for (; n < transition; n++) {
		if (table[(pos + n * n) % key_value[3]] == 0) {
			cout << "\nЭлемента в таблице нет";
			key_value[0] = -1;
			key_value[1] = -1;
			break;
		}
		else if (table[(pos + n * n) % key_value[3]] == r) {
			cout << "\nЭлемент найден: " << (pos + n * n) % key_value[3] << ") " << r;
			key_value[0] = (pos + n * n) % key_value[3];
			key_value[1] = r;
			break;
		}
	}

	if (n == transition) {
		transition = transition + key_value[3];

		for (; n < transition; n++)
			if (table[(pos + n) % key_value[3]] == 0) {
				cout << "\nЭлемента в таблице нет";
				key_value[0] = -1;
				key_value[1] = -1;
				break;
			}
			else if (table[(pos + n) % key_value[3]] == r) {
				cout << "\nЭлемент найден: " << (pos + n) % key_value[3] << ")" << r;
				key_value[0] = (pos + n) % key_value[3];
				key_value[1] = r;
				break;
			}
	}

	if (n == transition) {
		cout << "\nЭлемента в таблице нет";
		key_value[0] = -1;
		key_value[1] = -1;
	}

	end(table, key_value, show);
}



void addition(int table[], int key_value[], int transition, int r, bool show) {
	search(table, key_value, transition, r, false);

	if (key_value[1] == -1) {
		add(table, key_value, transition, r, true);
		key_value[2]++;
	}

	end(table, key_value, show);
}



void removal(int table[], int key_value[], int transition, int r, bool show) {
	search(table, key_value, transition, r, false);

	if (key_value[1] != -1) {
		table[key_value[0]] = -1;
		key_value[2]--;

		cout << "\n\nЭлемент `" << r << "` удален из индкеса `" << key_value[0] << "`";
	}

	end(table, key_value, show);
}



void replacement(int table[], int key_value[], int transition) {
	cout << "\nУДАЛЯЕМЫЙ ЭЛЕМЕНТ";
	int r = setting_value();
	removal(table, key_value, transition, r, false);

	cout << "\n\nДОБАВЛЯЕМЫЙ ЭЛЕМЕНТ";
	r = setting_value();
	addition(table, key_value, transition, r, false);

	end(table, key_value, true);
}



int main() {
	setlocale(LC_ALL, "Russian");

	srand(time(NULL));

	int size_sample = 45;
	int size_table = size_sample * 1.5;
	int* sample = new int[size_sample];
	int* table = new int[size_table];
	int transition = 500;
	int steps = 0;

	int key_value[5]{ 0, 0, size_sample, size_table, steps };

	for (int i = 0; i < key_value[3]; i++)
		table[i] = 0;

	int i = 0;
	while (i < key_value[2]) {
		int r = rand() * rand() % 1000000;
		bool flag = true;

		if (r / 100000 == 0)
			continue;

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

		add(table, key_value, transition, r, false);
	}

	output_hash_table(table, key_value[3]);
	calc_parameters(key_value);

	while (true) {
		cout << "\n\n\nВыберите действие:\n";
		cout << "- найти элемент       - нажмите 1\n";
		cout << "- добавить элемент    - нажмите 2\n";
		cout << "- удалить элемент     - нажмите 3\n";
		cout << "- заменить элемент    - нажмите 4\n";
		cout << "- завершить программу - нажмите 5\n";
		cout << "------------------------------> ";

		string var;
		getline(cin, var);

		if (var == "1") search(table, key_value, transition, setting_value(), true);
		else if (var == "2") addition(table, key_value, transition, setting_value(), true);
		else if (var == "3") removal(table, key_value, transition, setting_value(), true);
		else if (var == "4") replacement(table, key_value, transition);
		else if (var == "5") break;
	}

	cout << endl;
	output_hash_table(table, key_value[3]);
	cout << "\n\nКоличество элементов в таблице: " << key_value[2];
	calc_parameters(key_value);



	delete[] sample;
	delete[] table;

	cout << "\n\n\n";
	system("pause");
}
