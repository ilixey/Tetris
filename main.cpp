#pragma once
#include "Tetris.cpp" // Подключение заг.файла класса 
#include <fstream>
#include <iostream>
#include <string>

class Roles {
protected:
	string login, password;
public:
	Roles() {};
	Roles(string log, string pass) {
		login = log;
		password = pass;
	}
	virtual string getPass() = 0;
	virtual string getLogin() = 0;
};

class User :public Roles {
public:
	User() {};
	User(string tmp, string tmp1) :Roles(tmp, tmp1) {
	}
	string getPass() {
		return password;
	}
	string getLogin() {
		return login;
	}
	void changePass(string tmp) {
		password = tmp;
	}
	void changeLogin(string tmp) {
		login = tmp;
	}
};

ostream& operator<<(ostream& os, User& users) {
	os << users.getLogin() << endl << users.getPass() << endl;
	return os;
}

istream& operator>>(istream& is, User& users) {
	string s;
	getline(is, s);
	users.changeLogin(s);
	getline(is, s);
	users.changePass(s);
	return is;
}

void createFiles() {
	ifstream check;
	ofstream of;
	check.open("users.txt");
	if (!check.is_open()) {
		of.open("users.txt");
		of << "0" << endl;
		of.close();
	}
	check.close();
}

void fillSize(int& nUsers) {
	ifstream check;
	check.open("users.txt");
	check.seekg(-3, ios::end);
	check >> nUsers;
	check.close();
}

void fillClasses(User*& users, int& nUsers) {
	ifstream fin;
	fin.open("users.txt");
	if (fin.peek() != EOF) {
		for (int i = 0; i < nUsers; i++) {
			fin >> users[i];
		}
	}
	fin.close();
}

void fillFiles(User*& users, int& nUsers) {
	ofstream fout;
	fout.open("users.txt");
	for (int i = 0; i < nUsers; i++) {
		fout << users[i];
	}
	fout << nUsers << endl;
	fout.close();
}

int chooseMainMenu() {
	int choose_menu = 0, keyboard_button = 0;
	while (true) {
		cout << "Стрелочками ВВЕРХ и ВНИЗ выберите пункт меню" << endl;
		choose_menu = (choose_menu + 3) % 3;
		if (choose_menu == 0) { cout << " -> Войти в аккаунт" << endl; }
		else cout << " Войти в аккаунт" << endl;

		if (choose_menu == 1) { cout << " -> Создать новый аккаунт" << endl; }
		else cout << " Создать новый аккаунт" << endl;

		if (choose_menu == 2) { cout << " -> Выйти из программы" << endl; }
		else { cout << " Выйти из программы" << endl; }

		keyboard_button = _getch();
		if (keyboard_button == 224) {
			keyboard_button = _getch();
			if (keyboard_button == 72) choose_menu--;
			if (keyboard_button == 80) choose_menu++;
		}
		if (keyboard_button == 13) { system("cls"); return choose_menu; }
		system("cls");
	}
}

string writePassword() {
	string str;
	while (true) {
		int key;
		key = _getch();
		if (key == 224) {
			key = _getch();
		}
		else
			if (key == 8) {
				if (str.length() != 0) {
					cout << '\b' << " " << '\b';
					str.erase(str.length() - 1);
				}
			}
			else
				if (key == 13 && str.length() != 0) break;
				else
					if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9')) {
						str = str + (char)key;
						cout << "*";
					}
	}
	return str;
}

string writeWords() {
	string str;
	while (true) {
		int key;
		key = _getch();
		if (key == 224) {
			key = _getch();
		}
		else
			if (key == 8) {
				if (str.length() != 0) {
					cout << '\b' << " " << '\b';
					str.erase(str.length() - 1);
				}
			}
			else
				if (key == 13 && str.length() != 0) break;
				else
					if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9')) {
						str = str + (char)key;
						cout << (char)key;
					}
	}
	return str;
}

void changeSizeUsers(User*& users, int& nUsers) {
	nUsers++;
	User* ptr = new User[nUsers];
	for (int i = 0; i < nUsers - 1; i++)
		ptr[i] = users[i];
	users = ptr;
	ptr = NULL;
	delete[]ptr;
}

int main() //Начало программы Тетрис
{
	setlocale(0, "");
	system("color 3F");
	Tetris tetris;
	createFiles();
	int nUsers = 0;
	fillSize(nUsers);
	User* users = new User[nUsers];
	fillClasses(users, nUsers);
	while (true) {
		int checks = 0;
		int choose = chooseMainMenu();
		if (choose == 0) {
			int check = 0;
			string log, pass;
			cout << "Введите Логин: ";
			log = writeWords();
			cout << endl;
			cout << "Введите Пароль: ";
			pass = writePassword();
			system("cls");
			if (check == 0) {
				for (int i = 0; i < nUsers; i++)
					if (users[i].getLogin() == log && users[i].getPass() == pass) {
						tetris.gameTitle(); // Вызов метода класса Tetris для показа титров начальных
						tetris.gameMenu();  // Вызов метода для меню
						check = 1;
						break;
					}

			}
			if (checks == 4 && check == 1) break;
			if (checks != 3) {
				cout << "Вы ввели неверный логин или пароль." << endl;
				cout << "Попробуйте еще раз." << endl;
				system("pause");
			}
			system("cls");

		}
		else
			if (choose == 1) {
				string log, pass;
				int check = 0;
				while (true) {
					cout << "Введите Логин: ";
					log = writeWords();
					for (int i = 0; i < nUsers; i++)
						if (users[i].getLogin() == log) {
							check = 1;
							break;
						}
					if (check == 0) break;
					system("cls");
					check = 0;
					cout << "Такой логин уже существует!" << endl;
				}
				cout << endl;
				cout << "Введите Пароль: ";
				pass = writePassword();
				User user(log, pass);
				changeSizeUsers(users, nUsers);
				users[nUsers - 1] = user;
				fillFiles(users, nUsers);
				system("cls");
			}
			else
				break;
	}
	fillFiles(users, nUsers);
	
};
