#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <stdio.h>
#include <io.h>
#include <vector>
#include <iomanip>
#include <Windows.h>

using namespace std;

struct User
{
	int role;
	string login;
	string password;
};

struct Abonent
{
	string Surname_Of_Abonent;
	string Name_Of_Abonent;
	string PatronymicName_Of_Abonent;
	long int Number_Of_Abonent;
	string Name_Of_Tarif;
	int Year_Of_Connect;
};
char list_of_abonents[] = "List_of_abonents.txt";
char list_of_users[] = "List_of_users.txt";

vector <Abonent> vecAbonents; //объявление векторов
vector <User> vecUsers;

void read_users();//Чтение аккаунтов из файла
int enter();// Авторизация
void read_data();//Чтение данных из файла
void check_of_files();//Проверка на существование файла с аккаунтами
void menu_of_admin(int&);//Меню админа
void data(int&);//Меню данных и меню пользователя, т.к. пользователь может работать только с данными
void save();//Запись данных в файл
void create_abonents(int&);//создание новых абонентов
void out();//Вывод данных 
void sort();//Меню сортировки, различые виды сортировок
void kolxxxx();//Количество абонент
void table(int&);//Таблица 
void update_abonents(int&);//Редактировать абонентов
void delete_abonents(int&);//Удаление записи абонентов
void search_abonents();//Разные виды поиска абонентов
void users(int&);//Меню аккаунтов
void create_users();//Создание нового аккаунта
void out_users();//Вывести все аккаунты на консоль
void save_users();//Записать аккауты в файл
void delete_users();//Удалить аккаунт
void update_users();//Редактировать аккаунт
void sort_users();//Сортировка аккаунтов
string getpassword(const string);//Ввод, подтверждение пароль. Пароль выводится через *, можно стереть неправильно введенные символы
int proverka();//проверка на нечисловой ввод

void save_to_vecAbonents();// Сохранить изменения в вектор
void save_to_vecUsers();// Сохранить изменения в вектор

string currentLogin;

int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	while (true)
	{
		read_users();
		check_of_files();
		int i = enter();
		read_data();
		if (i == 1)
			menu_of_admin(i);
		else if (i == 0)
			data(i);
	}
	return 0;
}

void check_of_files()
{
	if (!_access(list_of_users, 0))//Проверяет на существование
	{
		cout << "\nФайл с пользователями существует\n";
		return;
	}
	else
	{
		cout << "\nФайл с пользователями не найден\n";
		return;
	}
}

void read_users()
{
	ifstream fin(list_of_users, ios::in);//	считать из открытого файла для чтения в созданный объект класса ifstream
	vecUsers.clear();
	User one;
	if (fin.is_open())//Если открыли файл
	{
		while (!fin.eof())
		{
			fin >> one.login
				>> one.password
				>> one.role;
			vecUsers.push_back(one);//Для добавления нового элемента в конец вектора
		}
		fin.close();
	}
	if (vecUsers.size() == 0) {
		one.login = "аноним";
		one.password = "123";
		one.role = 1;
		vecUsers.push_back(one);
		cout << "\nСоздаётся первый администратор";
		save_users();
	}
	cout << "\nКоличество считанных пользователей = " << vecUsers.size() << endl;
	return;
}

string getpassword(const string prompt)
{
	cout << prompt;
	string result;
	char c;
	while (true)
	{
		c = _getch();
		if (c == '\r')
			break;
		if (c == '\b')
		{
			cout << "\b \b";
			result.pop_back();//стирает один символ
			continue;

		}
		result.push_back(c);//прибавит 1 символ
		cout << "*";
	}
	return result;
}

int proverka()
{
	int prov;
	while (true)
	{
		cin >> prov;
		if (cin.good() == false)// Если ввод произошёл без ошибок, возвращает true.
		{
			cout << "Ошибка, попробуй снова!\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else return prov;
	}
}

int enter()
{
	cout << "\n ------------Авторизация------------" << endl;
	int flag = 10;
	char y;
	string password;
	bool find = true;
	int j;
	do {
		cout << "\n\tВведите логин: ";
		string login;
		cin >> login;
		int n = vecUsers.size();
		for (j = 0; j < n; j++)
		{
			if (vecUsers[j].login == login)
			{
				find = false;
				break;
			}
		}
		if (find)
		{
			cout << "\n Пользователя с таким логином нет! Хотите повторить? Введите y или Y \n";
			y = _getche();
			if (y != 'y' && y != 'Y') {
				exit(0);//завершение программы
			}
		}
	} while (find);
	do {
		cout << "У вас осталось " << flag << " попыток для введения пароля" << endl;
		password = getpassword("\n\tПожалуйста, введите ваш пароль:\n");
		if (vecUsers[j].password == password)
		{
			cout << "\nВы вошли!" << endl;
			break;
		}
		else
			cout << "\n\tНеверный пароль!\n\tПопробуйте ещё раз" << endl;
		flag--;
	} while (flag != 0);
	if (flag == 0) {
		cout << "Попытки закончились, войдите заново" << endl;
		enter();
	}
	currentLogin = vecUsers[j].login;
	return vecUsers[j].role;
}

void menu_of_admin(int& i)
{
	bool l = true;
	while (l)
	{
		cout << "\n\tРаботать с данными - 1\n\tС учётными записями пользователей - 2\n\tНАЗАД - 0\n\tВыход- другой символ\n";
		char c = _getch();
		switch (c)
		{
		case '1':
			data(i);
			break;
		case '2':
			users(i);
			break;
		case '0':
			l = false;
			break;
		default:
			exit(0);
		}
	}
}

/*ДАННЫЕ*/
void read_data()
{
	ifstream fine(list_of_abonents, ios::in);//	считать из открытого файла для чтения в созданный объект класса ifstream
	vecAbonents.clear();
	Abonent one;
	if (fine.is_open())//Если открыли файл
	{
		while (!fine.eof())//если прочитано до конца.
		{
			fine >> one.Surname_Of_Abonent
				>> one.Name_Of_Abonent
				>> one.PatronymicName_Of_Abonent
				>> one.Number_Of_Abonent
				>> one.Name_Of_Tarif
				>> one.Year_Of_Connect;
			vecAbonents.push_back(one);//Для добавления нового элемента в конец вектора
		}
		fine.close();
	}
	else
	{
		cout << "\nДобавьте запись в файл\n";
		return;
	}
	cout << "\nКоличество записей = " << vecAbonents.size() << endl;
	return;
}

void data(int& i)
{
	while (true)
	{
		cout << "--------------------Работа с данными----------------------------\n";
		cout << "\n\t Добавить/Создать - 1\n\t Просмотреть - 2\n\t Сортировка- 3\n\t Решениe задания - 4\n\t Редактирование - 5\n\t Удаление данных - 6\n\t Поиск - 7\n\t НАЗАД - 0\n";;
		char c = _getch();
		switch (c)
		{
		case '1': create_abonents(i);
			break;
		case '2': out();
			break;
		case '3': sort();
			break;
		case '4': kolxxxx();
			break;
		case '5': update_abonents(i);
			break;
		case '6': delete_abonents(i);
			break;
		case '7': search_abonents();
			break;
		case '0': char g;
			if (i == 1) return;
			else {
				cout << "Вы покидаете программу! Вы уверены?Y/N\n";
				g = _getche();
				if (g != 'Y' || g != 'y')
					exit(0);
			}
		}
	}
}

void save()
{
	cout << "\nХотите сохранить данные в главный файл? 1 - да, все остальные - нет\n";
	char q = _getche();
	if (q == '1')
	{
		ofstream fout(list_of_abonents, ios::out);
		int n = vecAbonents.size();
		for (int i = 0; i < n; i++) {
			fout << vecAbonents[i].Surname_Of_Abonent << " "
				<< vecAbonents[i].Name_Of_Abonent << " "
				<< vecAbonents[i].PatronymicName_Of_Abonent << " "
				<< vecAbonents[i].Number_Of_Abonent << " "
				<< vecAbonents[i].Name_Of_Tarif << " "
				<< vecAbonents[i].Year_Of_Connect;
			if (i < n - 1)
				fout << endl;
		}
		fout.close();
	}
	else
		return;
}

void create_abonents(int& i)
{
	if (i == 1)
	{
		int k = 0;
		cout << "\nСколько записей абонентов вы хотите добавить или создать?\n";
		int n = proverka();
		Abonent one;
		for (int i = 0; i < n; i++)
		{
			cout << "\n Введите фамилию абонента - ";
			cin >> one.Surname_Of_Abonent;
			cout << "\n Введите имя абонента - ";
			cin >> one.Name_Of_Abonent;
			cout << "\n Введите отчество абонента - ";
			cin >> one.PatronymicName_Of_Abonent;
			cout << "\n Введите номер абонента - ";
			cin >> one.Number_Of_Abonent;
			cout << "\n Имя тарифа - ";
			cin >> one.Name_Of_Tarif;
			cout << "\n Год подключения - ";
			one.Year_Of_Connect = proverka();
			vecAbonents.push_back(one);
		}
		save();
	}
	else return;
}

void out()
{
	int n = vecAbonents.size();

	puts("--------------------------------------------------------------------------------------------------------------");
	printf("№", "ФИО абонента", "Номер и Тариф", "Год подключения");
	puts("|------------------------------------------------------------------------------------------------------------|");
	if (vecAbonents.size() != 0)
		for (int i = 0; i < n; i++)
		{
			cout << "|" << setw(5) << i + 1 << "  |" << " " << vecAbonents[i].Surname_Of_Abonent << " "
				<< setw(5) << vecAbonents[i].Name_Of_Abonent << " "
				<< setw(5) << vecAbonents[i].PatronymicName_Of_Abonent << setw(14) << "|"
				<< setw(5) << vecAbonents[i].Number_Of_Abonent << " "
				<< setw(5) << vecAbonents[i].Name_Of_Tarif << setw(14) << "|"
				<< setw(13) << vecAbonents[i].Year_Of_Connect << "|" << endl
				<< "|-----------------------------------------------------------------------------------------------------------|\n";
		}
	else
		cout << "Записи отсутствуют, проверьте наличие файла\n";
}

void sort()
{
	char p;
	if (vecAbonents.size() != 0)
	{
		Abonent temp;
		int n = vecAbonents.size();
		cout << "\n Какого вида сортировку вы хотите?\n";
		cout << "\n\tПо Фамилии абонента - 1\n\tПо тарифу абонента - 2\n\tПо имени абонента - 3\n\tПо отчеству абонента - 4\n\tПо году подключения - 5\n\tНазад - 0\n";
		p = _getche();
		cout << "\n\t----- С О Р Т И Р О В К А -----\n";
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++)
				switch (p)
				{
				case '1':
				{if (vecAbonents[i].Surname_Of_Abonent.compare(vecAbonents[j].Surname_Of_Abonent) > 0)
				{
					temp = vecAbonents[i];
					vecAbonents[i] = vecAbonents[j];
					vecAbonents[j] = temp;
				}
				else if (vecAbonents[i].Surname_Of_Abonent.compare(vecAbonents[j].Surname_Of_Abonent) == 0) {
					if (vecAbonents[i].Year_Of_Connect > vecAbonents[j].Year_Of_Connect) {
						temp = vecAbonents[i];
						vecAbonents[i] = vecAbonents[j];
						vecAbonents[j] = temp;
					}
				}
				break; }
				case '2':
				{if (vecAbonents[i].Name_Of_Tarif.compare(vecAbonents[j].Name_Of_Tarif) > 0)
				{
					temp = vecAbonents[i];
					vecAbonents[i] = vecAbonents[j];
					vecAbonents[j] = temp;
				}
				break; }
				case '3':
				{if (vecAbonents[i].Name_Of_Abonent.compare(vecAbonents[j].Name_Of_Abonent) > 0)
				{
					temp = vecAbonents[i];
					vecAbonents[i] = vecAbonents[j];
					vecAbonents[j] = temp;
				}
				break; }
				case '4':
				{if (vecAbonents[i].PatronymicName_Of_Abonent.compare(vecAbonents[j].PatronymicName_Of_Abonent) > 0)
				{
					temp = vecAbonents[i];
					vecAbonents[i] = vecAbonents[j];
					vecAbonents[j] = temp;
				}
				break; }
				case '5':
				{if (vecAbonents[i].Year_Of_Connect > vecAbonents[j].Year_Of_Connect)
				{
					temp = vecAbonents[i];
					vecAbonents[i] = vecAbonents[j];
					vecAbonents[j] = temp;
				}
				break; }
				case '0': return;
				}
		out();
		save_to_vecAbonents();
		save();
	}
	else
		cout << "\nЗаписи отсутствуют, проверьте наличие файла\n";
}


void kolxxxx()
{
	int kol = 0, year;
	cout << "\n Введите год подключения\n";
	cin >> year;
	cout << "\n----------------- Абоненты --------------\n";
	cout << "|-------ФИО абонента---------|-----Год-------|\n";
	for (int i = 0; i < 0; kol++)
	{
		if (vecAbonents[i].Year_Of_Connect >= year) {
			cout << "|" << setw(5) << i + 1 << "  |" << " " << vecAbonents[i].Surname_Of_Abonent << " "
				<< setw(5) << vecAbonents[i].Name_Of_Abonent << " "
				<< setw(5) << vecAbonents[i].PatronymicName_Of_Abonent << setw(14) << "|"
				<< setw(5) << vecAbonents[i].Year_Of_Connect << setw(14) << "|" << endl;
		}
	}
	cout << "\nКоличество абонентов, подключенных с " << year << " года составляет " << kol << endl;

}

void update_abonents(int& i)
{
	if (i == 1)
	{
		if (vecAbonents.size() != 0)
		{
			int k;
			cout << "\n\tСписок текущих абонентов\n : ";
			out();
			cout << endl << "\n\tПожалуйста, выберите чьи данные хотите редактировать \n\tЛюбое другое число - выход из программы\n";
			k = proverka();
			int n = vecAbonents.size();
			if (k > n)
			{
				cout << "\nНеправильный ввод\n";
				return;
			}
			cout << "\nЧто вы хотите изменить? Выберите:\n фамилию абонента - 1 \n имя абонента - 2\n отчество абонента - 3\n тариф абонента - 4\n Назад - 0\n";
			char v;
			v = _getche();
			switch (v)
			{
			case '1': {

				cout << "\nВведите изменённую фамилию абонента\n";
				cin >> vecAbonents[k - 1].Surname_Of_Abonent;
				break;
			}
			case '2': {
				cout << "\nВведите изменённое имя абонента\n";
				cin >> vecAbonents[k - 1].Name_Of_Abonent;
				break;
			}
			case '3': {
				cout << "\nВведите изменённое отчество абонента\n";
				cin >> vecAbonents[k - 1].PatronymicName_Of_Abonent;
				break;
			}
			case '4': {
				cout << "\nВведите изменённый тариф абонента\n";
				cin >> vecAbonents[k - 1].Name_Of_Tarif;
				break;
			}
			case '0': return;
			default:
				break;
			}
			out();
			save_to_vecAbonents();
			save();
		}
		else
		{
			cout << "\nЗаписи отсутствуют, проверьте наличие файла\n";
			return;
		}
	}
}

void delete_abonents(int& i)
{
	if (i == 1)
	{
		if (vecAbonents.size() != 0)
		{
			string tmp;
			out();
			cout << "\nКакую запись абонента вы хотите удалить?\n";
			int n = proverka();
			tmp = vecAbonents[n - 1].Surname_Of_Abonent;
			cout << "\nВы действительно хотите удалить запись? Y/N?\n";
			char c = _getche();
			if (c == 'y' || c == 'Y')
			{
				vecAbonents.erase(vecAbonents.begin() + n - 1);
			}
			out();
			save_to_vecAbonents();
			save();
			int m = vecAbonents.size();
			for (int i = 0; i < m; i++)
			{
				if (vecAbonents[i].Surname_Of_Abonent == tmp)
				{
					vecAbonents[i].Number_Of_Abonent--;
					save();
				}
			}
		}
		else {
			cout << "\nЗаписи отсутствуют, проверьте наличие файла\n";
			return;
		}
	}
}
void table(int& i) {
	cout << "|" << setw(5) << i + 1 << "  |" << " " << vecAbonents[i].Surname_Of_Abonent << " "
		<< setw(5) << vecAbonents[i].Name_Of_Abonent << " "
		<< setw(5) << vecAbonents[i].PatronymicName_Of_Abonent << setw(14) << "|"
		<< setw(5) << vecAbonents[i].Number_Of_Abonent << " "
		<< setw(5) << vecAbonents[i].Name_Of_Tarif << " "
		<< setw(5) << vecAbonents[i].Year_Of_Connect << setw(14) << "|" << endl
		<< "|-----------------------------------------------------------------------------------------------------------|\n";
}

void search_abonents()
{
	if (vecAbonents.size() != 0)
	{
		out();
		cout << "\nПо какой колонке вести поиск?\n\tФамилия абонента - 1\n\tТариф - 2 \n\t Имя абонента  - 3\n\tНАЗАД - 0\n";
		int q = _getche(), n = 0;
		if (q == '0')
			return;
		int m = vecAbonents.size();
		string search;
		cout << "\nКакую строку хотите найти? : ";
		cin >> search;
		cout << "\n---------------Результаты поиска------------\n";
		puts("--------------------------------------------------------------------------------------------------------------");
		cout<<("№", "ФИО абонента", "Номер и Тариф", "Год подключения");
		puts("|------------------------------------------------------------------------------------------------------------|");		
		for (int i = 0; i < m; i++)
		{
			switch (q)
			{
			case '1':
				if (vecAbonents.at(i).Surname_Of_Abonent.find(search) != string::npos)
					/*Если функция find найдет совпадение, то она вернет нам позицию первого символа
					совпадаемого слова. npos - это несуществующая позиция (-1)*/
				{
					table(i);
					n++;
				}
				break;
			case '2':
				if (vecAbonents.at(i).Name_Of_Tarif.find(search) != string::npos)
				{
					table(i);
					n++;
				}
				break;
			case '3':
				if (vecAbonents.at(i).Name_Of_Abonent.find(search) != string::npos)
				{
					table(i);
					n++;
				}
				break;
			}
		}
		if (n != 0)
			cout << "\n\tНайдено " << n << " совпадений\n";
		else
			cout << "\n\tСовпадений не найдено!\n";
	}
	else
	{
		cout << "\nЗаписи отсутствуют, проверьте наличие файла\n";
		return;
	}
}

/*ПОЛЬЗОВАТЕЛИ*/
void users(int& i)
{
	if (i == 1)
	{
		while (true)
		{
			cout << "\n\tДобавить/Создать-1\n\tПросмотреть - 2\n\tРедактирование - 3\n\tУдаление - 4\n\tСортировать - 5\n\tНАЗАД - 0\n";
			char c = _getch();
			switch (c)
			{
			case'1': create_users();
				break;
			case'2': out_users();
				break;
			case'3': update_users();
				break;
			case'4': delete_users();
				break;
			case'5': sort_users();
				break;
			case '0':
				return;
			}
		}
	}
	else cout << "\nВы не имеете доступа\n";
}

void create_users()
{
	User new_user;
	bool b = true;
	while (b) {
		cout << "\nВид:\n\tПользователь - 0\n\tАдмин - 1\n";
		char c = _getche(); //возвращает очередной символ, считанный с консоли, и выводит этот символ на экран.
		if (c == '0' || c == '1') {
			new_user.role = atoi(&c);
			b = false;
		}
		else cout << "Ошибка, попробуйте снова" << endl;
	}
	string name;
	cout << "\nЛогин - ";
	cin >> name;
	new_user.login = name;
	new_user.password = string(getpassword("\nПароль - "));
	string password = string(getpassword("\nПодтвердите пароль - "));
	while (password != new_user.password)
	{
		new_user.password = string(getpassword("\nНеверный пароль, попробуйте снова- "));
		password = string(getpassword("\nПодтвердите пароль - "));
	}
	vecUsers.push_back(new_user);
	save_users();
}

void out_users()
{
	if (vecUsers.size() != 0)
	{
		cout << "\n\tСписок учётных записей\n";
		int n = vecUsers.size();
		for (int i = 0; i < n; i++)
			cout << i + 1 << ") " << vecUsers[i].login << " , роль - " << vecUsers[i].role << endl;
	}
	else
		cout << "\nПользователи отсутствуют, проверьте наличие файла\n";
}

void save_users()
{
	cout << "\nХотите сохранить данные в главный файл? 1 - да,все остальные - нет\n";
	char q = _getche();
	if (q == '1')
	{
		ofstream fout(list_of_users, ios::out);
		if (fout.is_open()) {
		}
		int n = vecUsers.size();
		for (int i = 0; i < n; i++) {
			fout << vecUsers[i].login << " "
				<< vecUsers[i].password << " "
				<< vecUsers[i].role;
			if (i < n - 1)
				fout << endl;
		}
		fout.close();
	}
	else
		return;
}

void delete_users()
{
	if (vecUsers.size() != 0)
	{
		int m = vecUsers.size();
		out_users();
		cout << "\nКакой аккаунт вы хотите удалить?\n";
		int n = proverka();
		if (currentLogin.compare(vecUsers[n - 1].login) == 0)
		{
			cout << "\nВы не можете удалить свой аккаунт!\n";
			return;
		}
		if (vecUsers[n - 1].role == 1)
		{
			string password = getpassword("\nВы хотите удалить аккаунт администратора.Для удаления введите пароль - ");
			while (password.compare(vecUsers[n - 1].password) != 0)
				password = getpassword("\n\tНеправильный пароль, попробуйте ещё раз:");
		}
		cout << "\nВы уверены, что хотите удалить этот аккаунт? Y/N?\n";
		char c = _getche();
		if (c == 'y' || c == 'Y')
		{
			vecUsers.erase(vecUsers.begin() + n - 1);
		}
		else
			return;
		out_users();
		cout << "Хотите сохранить изменнения в ваш вектор?Y/N\n";
		save_to_vecUsers();
		save_users();
	}
	else
		cout << "\nПользователи отсутствуют, проверьте наличие файла\n";
}

void update_users()
{
	if (vecUsers.size() != 0)
	{
		int n;
		char vib;
		cout << "\n\tПожалуйста, выберите одну запись:";
		out_users();
		cout << endl << "\tЛюбое другое число - НАЗАД\n";
		n = proverka();
		int m = vecUsers.size();
		if (n > m)
			return;
		cout << "\nЧто вы хотите изменить?Выберите: \n логин - 1 \n пароль - 2 \n роль - 3\n Назад - 0\n";
		cin >> vib;
		switch (vib)
		{
		case '1': {
			cout << "\nВведите новый логин\n";
			cin >> vecUsers[n - 1].login;
			break;
		}
		case '2': {
			string password = string(getpassword("\n\tПожалуйста введите старый пароль: "));
			while (password != vecUsers[n - 1].password)
				password = string(getpassword("\n\tНеверный старый пароль, попробуйте снова: "));
			vecUsers[n - 1].password = string(getpassword("\nВведите новый пароль: "));
			password = string(getpassword("\nПодтвердите пароль: "));
			while (password != vecUsers[n - 1].password)
			{
				vecUsers[n - 1].password = string(getpassword("\nПароли не совпадают, попробуйте снова - "));
				password = string(getpassword("\nConfirm password - "));
			}
			break;
		}
		case '3': {
			bool b = true;
			while (b)
			{
				cout << "\nВид:\n\tПользователь - 0\n\tАдмин - 1\n";
				char c = _getche(); //возвращает очередной символ, считанный с консоли, и выводит этот символ на экран.
				if (c == '0' || c == '1')
				{
					vecUsers[n - 1].role = atoi(&c);
					b = false;
				}
			}
			break;
		}
		case '0': return;
		default: break;
		}
		out_users();
		save_to_vecUsers();
		save_users();
	}
	else
		cout << "\nПользователи отсутствуют, проверьте наличие файла\n";

}

void sort_users()
{
	if (vecUsers.size() != 0)
	{
		cout << "\n\t----- С О Р Т И Р О В К А -----\n";
		int n = vecUsers.size();
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++)
				if (vecUsers[i].login > vecUsers[j].login)
				{
					User temp = vecUsers[i];
					vecUsers[i] = vecUsers[j];
					vecUsers[j] = temp;
				}
		out_users();
		save_to_vecUsers();
		save_users();
	}
	else
		cout << "\nПользователи отсутсвуют, проверьте наличие файла\n";
}

void save_to_vecUsers()
{
	cout << "Хотите сохранить изменнения в ваш вектор?Y/N\n";
	char t;
	cin >> t;
	if (t == 'Y' || t == 'y')
		cout << "Без изменений\n";
	else
		read_users();
}

void save_to_vecAbonents()
{
	cout << "Хотите сохранить изменнения в ваш вектор?Y/N\n";
	char t;
	cin >> t;
	if (t == 'Y' || t == 'y')
		cout << "Без изменений\n";
	else
		read_data();
}
