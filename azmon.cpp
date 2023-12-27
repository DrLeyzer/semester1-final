#include <iostream>
#include <string.h>
#include <string>
#include <cstdlib> 
//#include <fstream>

using namespace std;

//ofstream books_db("booksdb.txt", ios::app);
//ofstream students_db("studentsdb.txt", ios::app);

const int phone_code = 123456;
string temp_bookname, line,temp_std_phonenum, temp_std_idnum, temp_input,temp_ketabdar_username, temp_password_ketabdar,temp_stdpass, temp_stdid, global_stdnumber, global_stdid;
int id_len, i, temp_code, temp_book_id, j, last_std_info_loc=0, last_book_loc=0,n, temp_booknum;
char temp_switchs;
bool temp_bool=false;

void db_reader(); //inactive
bool search_book(string name);
void clearScreen();
bool phone_valid(string num);
void ketabdar_panel();
void student_panel();
void entering_books();
bool id_valid(string num);
void available_book_list();
void unavailable_book_list();
void std_borrow_list(string student_id);
bool exit_check(string input);
void borrow_book();
void giving_book();
bool book_exist(int booknum);

class c_ketabdars {
private:
	const string username="user";
	const string password="pass";
public:
	bool login_ketabdar() {
		temp_bool = false;
		cout << "\nType 'exit' at any time to exit.\n";
		cout << "\nenter the ketabdar's username : ";
		while (true) {
			cin >> temp_input;
			if (exit_check(temp_input)) {
				clearScreen();
				cout << "Exit successfully committed.";
				return false;
			}
			else
				if (temp_input == username) {
					clearScreen();
					cout << "\nenter the password to enter the panel : ";
					while (true) {
						cin >> temp_password_ketabdar;
						if (exit_check(temp_password_ketabdar)) {
							cout << "Exit successfully committed.";
							return false;
						}
						else
							if (temp_password_ketabdar == password) {
								temp_bool = true;
								break;
							}
							else {
								cout << "\nwrong password, try again : ";
							}
					}
					break;
				}
				else {
					cout << "\nwrong username, try again : ";
				}
		}
		return temp_bool;
	}

}ketabdar;

class c_students {
private:
	string fname[1000], lname[1000];
	string id[1000];
	string phone_num[1000];
	int student_loc[1000];
	string password[1000];
public:
	void student_signup() {
		for (i = 0; i < 1000; i++) {
			if (i == last_std_info_loc) {
				cout << "\nType 'exit' at any time to exit.\n";
				cout << "\nenter your first name : ";
				cin >> temp_input;
				if (exit_check(temp_input)) {
					clearScreen();
					cout << "Exit successfully committed.";
					student_panel();
				}
				else
					fname[i] = temp_input;
				clearScreen();
				cout << "\nType 'exit' at any time to exit.\n";
				cout << "\nenter your last name : ";
				cin >> temp_input;
				if (exit_check(temp_input)) {
					fname[i] = "\0";
					clearScreen();
					cout << "Exit successfully committed.";
					student_panel();
				}
				else
					lname[i] = temp_input;
				clearScreen();
				cout << "\nType 'exit' at any time to exit.\n";
				phone_taker_signup:
				cout << "\nenter the phone number : ";
				cin >> temp_input;
				if (exit_check(temp_input)) {
					fname[i] = "\0";
					lname[i] = "\0";
					clearScreen();
					cout << "Exit successfully committed.";
					student_panel();
				}
				else {
					if (phone_valid(temp_input)) {
						student.phone_num[i] = temp_input;
					}
					else {
						cout << "\ninvalid phone number!\n";
						goto phone_taker_signup;
					}
				}
				clearScreen();
				cout << "\nType 'exit' at any time to exit.\n";
				id_taker_signup:
				cout << "\nenter your identity number ( code melli ) : ";
				cin >> temp_input;
				if (exit_check(temp_input)) {
					fname[i] = "\0";
					lname[i] = "\0";
					phone_num[i] = "\0";
					clearScreen();
					cout << "Exit successfully committed.";
					student_panel();
				}
				else {
					if (id_valid(temp_input)) {
						id[i] = temp_input;
					}
					else {
						cout << "\ninvalid identity number!\n";
						goto id_taker_signup;
					}
				}
				clearScreen();
				cout << "\nType 'exit' at any time to exit.\n";
				std_passtaker:
				cout << "\nenter your password : ";
				cin >> temp_input;
				if (exit_check(temp_input)) {
					fname[i] = "\0";
					lname[i] = "\0";
					phone_num[i] = "\0";
					id[i] = "\0";
					clearScreen();
					cout << "Exit successfully committed.";
					student_panel();
				}
				else
					while(true) {
						ask_pass:
						cout << "\nyour password is : " << temp_input << " ? (y-yes / n-no) : ";
						cin >> temp_switchs;
						switch (temp_switchs) {
						case 'y':
							clearScreen();
							password[i] = temp_stdpass;
							break;
						case 'n':
							goto std_passtaker;
							break;
						default:
							cout << "\nwrong input!";
							goto ask_pass;
							break;
						}
						break; 
					}
				student_loc[i] = last_std_info_loc;
				//students_db << fname[i] << " " << lname[i] << " " << temp_std_phonenum << " " << id[i] << " " << password[i] << " loc : " << student_loc[i] << endl;
				last_std_info_loc = last_std_info_loc + 1;
				cout << "\ninformation has been taken successfully! moving to the panel.";
				break;
			}
		}
	}
	//completed
	bool student_id_existance() {
		clearScreen();
		cout << "\nType 'exit' at any time to exit.\n";
		cout << "\nenter your identity number : ";
		cin >> temp_input;
		if (exit_check(temp_input)) {
			clearScreen();
			cout << "Exit successfully committed.";
			student_panel();
		}
		else {
			temp_stdid = temp_input;
			for (i = 0; i < 1000; i++) {
				if (temp_stdid == id[i]) {
					temp_bool = true;
					global_stdid = id[i];
					global_stdnumber = phone_num[i];
					break;
				}
				else
					temp_bool = false;
			}
			return temp_bool;
		}
	}
	//completed
	bool student_login() {
		while (student_id_existance()) {
			cout << "\nenter your password : ";
			while (true) {
				cin >> temp_input;
				if (exit_check(temp_input)) {
					clearScreen();
					cout << "Exit successfully committed.";
					student_panel();
				}
				else {
					if (temp_stdpass == password[i])
						return true;
					else {
						cout << "\nwrong password, try again : ";
					}
				}
			}
		}
		clearScreen();
		cout << "\nType 'exit' at any time to exit.\n";
		cout << "\nthis identity number does not exist! enter 1 for try again and enter 2 for sign up : ";
		cin >> temp_input;
		if (exit_check(temp_input)) {
			clearScreen();
			cout << "Exit successfully committed.";
			student_panel();
		}
		else {
			while (true) {
				temp_switchs = temp_input[0];
				switch (temp_switchs) {
				case '1':
					student_login();
					clearScreen();
					break;
				case '2':
					clearScreen();
					student_signup();
					return false;
				default:
					cout << "\nwrong input! try again (1-try again / 2-signup) : ";
				}
			}
		}
	}
	//completed
	bool student_existance(string student_id) {
		for (i = 0; i < 1000; i++) {
			if (student_id == id[i]) {
				temp_bool = true;
				j = i;
				break;
			}
			else
				temp_bool = false;
		}
		return temp_bool;
	}
	//completed
	void changing_stdinfo(string student_id) {
		clearScreen();
		while (true) {
			cout << "\n1-first name\n2-last name\n3-phone number\n4-password\nwhat do you want to change (press 'e' for exit) : ";
			cin >> temp_switchs;
			clearScreen();
			switch (temp_switchs) {
			case '1':
				cout << "\nenter the new first name : ";
				cin >> fname[j];
				cout << "\nsuccesful!";
				clearScreen();
				break;
			case '2':
				cout << "\nenter the new last name : ";
				cin >> lname[j];
				cout << "\nsuccesful!";
				clearScreen();
				break;
			case '3':
				while (true) {
					cout << "\nenter the new phone number : ";
					cin >> temp_std_phonenum;
					if (phone_valid(temp_std_phonenum)) {
						student.phone_num[j] = temp_std_phonenum;
						break;
					}
					else {
						clearScreen();
						cout << "\ninvalid phone number!";
					}
				}
				cout << "\nsuccesful!";
				clearScreen();
				break;
			case '4':
				cout << "\nenter the new password : ";
				cin >> password[j];
				cout << "\nsuccesful!";
				clearScreen();
				break;
			case 'e':
				student_panel();
				break;
			default:
				cout << "\nwrong input!\n";
			}
			break;
		}
	}
	//completed
	void student_list() {
		cout << "\nstudents list : \n";
		for (i = 0; i < 1000; i++) {
			if (id[i]!="\0") {
				cout << "\nname : " << fname[i] << " " << lname[i] << " - phone number : " << phone_num[i] << " - identity number : " << id[i];
			}
			else
				break;
		}
	}
	//completed
	bool phone_num_validator(string student_id, string num) {
		for (i = 0; i < 1000; i++) {
			if (id[i] == student_id) {
				if (num == phone_num[i]) {
					temp_bool=true;
					break;
				}
				else {
					temp_bool = false;
					break;
				}
			}
			temp_bool = false;
		}
		return temp_bool;
	}
	//completed
}student;

class c_books {
public:
	string book_name[10000];
	int book_loc[10000];
	int book_id[10000];
	bool available[10000] = { false };
	string who_borrows_id[10000];
	string who_borrows_num[10000];
}book;

int main()
{
	//db_reader();
	clearScreen();
	cout << "\n1-ketabdar penel\n2-students panel\nenter your choice : ";
main_panel:
	cin >> temp_switchs;
	switch (temp_switchs) {
	case '1':
		clearScreen();
		ketabdar_panel();
		break;
	case '2':
		clearScreen();
		student_panel();
		break;
	default:
		cout << "\nwrong input! try again : ";
		goto main_panel;
		break;
	}
}
//completed
void student_panel() {
	clearScreen();
	while (true) {
		cout << "\n1-log in\n2-sign up\n3-main menu\nEnter your choice : ";
		cin >> temp_switchs;
		switch (temp_switchs) {
		case '1':
			if (student.student_login()) {
			student_panel_actions:
				clearScreen();
				cout << "\n1-borrow a book\n2-giving  a books\n3-changing personal information\n4-logout\nEnter your choice :  : ";
				cin >> temp_switchs;

				switch (temp_switchs) {
				case '1':
					clearScreen();
					borrow_book();
					cout << "\nsuccesful! moving back to panel...";
					break;
				case '2':
					clearScreen();
					std_borrow_list(global_stdid);
					giving_book();
					cout << "\nsuccesful! moving back to panel...";
					break;
				case '3':
					clearScreen();
					cout << "\nenter the security code that u recived on your phone number (" << global_stdnumber.substr(0, global_stdnumber.length() - 4) << ") : ";
				code_recived:
					cin >> temp_code;
					if (temp_code == phone_code) {
						student.changing_stdinfo(temp_stdid);
						cout << "\nsuccesful! moving back to panel...";
					}
					else {
						cout << "\ninvalid code, try again : ";
						goto code_recived;
					}
					break;
				case '4':
					clearScreen();
					main();
					return;
				default:
					clearScreen();
					cout << "\nwrong input! try again : ";
					goto student_panel_actions;
				}
			}
			break;
		case '2':
			clearScreen();
			student.student_signup();
			break;
		case '3':
			main();
			break;
		default:
			cout << "\nwrong input!\n";
		}
	}
}
//completed
void ketabdar_panel() {
		if (ketabdar.login_ketabdar()) {
		ketabdar_panel:
			clearScreen();
		ketabdar_panel2:
			cout << "\n1-enter book list\n2-list of the books\n3-student list\n4-new student signup\n5-log out\nenter your choice : ";
			cin >> temp_switchs;
			switch (temp_switchs) {
			case '1':
				clearScreen();
				entering_books();
				clearScreen();
				cout << "\nsuccesful! moving back to panel...";
				goto ketabdar_panel;
				break;
			case '2':
				clearScreen();
				available_book_list();
				unavailable_book_list();
				cout << "\n\n moving back to panel...";
				goto ketabdar_panel2;
				break;
			case '3':
				clearScreen();
				student.student_list();
				cout << "\n\n moving back to panel...";
				goto ketabdar_panel2;
				break;
			case '4':
				clearScreen();
				student.student_signup();
				cout << "\nsuccesful! moving back to panel...";
				goto ketabdar_panel;
				break;
			case '5':
				main();
				break;
			default:
				cout << "\nwrong input!\n";
				goto ketabdar_panel;
					break;
			}
			goto ketabdar_panel;
		}
}
//completed
void borrow_book() {
	clearScreen();
borrow:
	cout << "\nType 'exit' at any time to exit.\n";
	cout << "\nare you looking for specific book ? (y-search by name / n-book list) : ";
	cin >> temp_input;
	if (exit_check(temp_input)) {
		clearScreen();
		cout << "Exit successfully committed.";
		student_panel();
	}
	else {
		temp_switchs=temp_input[0];
		switch (temp_switchs) {
		case 'n':
			available_book_list();
			cout << "\n\nenter the book id that you want to borrow : ";
		book_id_checker:
			cin >> temp_booknum;
			if (book_exist(temp_booknum)) {
				for (i = 0; i < last_book_loc; i++) {
					if (book.book_id[i] == temp_booknum) {
						borrow2:
						book.available[i] = false;
						book.who_borrows_id[i] = global_stdid;
						book.who_borrows_num[i] = global_stdnumber;
						clearScreen();
						cout << "\nnow you can borrow your book  by giving book id to ketabdar.\n";
					}
				}
			}
			else {
				cout << "\nwrong book id! try again : ";
				goto book_id_checker;
			}
		case 'y':
			cout << "\nenter the book title that you are looking for : ";
			cin >> temp_bookname;
			if (search_book(temp_bookname)) {
				clearScreen();
				cout << "\nthe book is available!\nname : " << book.book_name[i] << " - book id : " << book.book_id[i]<<"\ndo you want to borrow that ? (y-yes / n-no) : ";
				book_exist:
				cin >> temp_switchs;
				switch (temp_switchs)
				{
				case 'y':
					goto borrow2;
					break;
				case 'n':
					cout << "\nmoving back to the panel...";
					student_panel();
					break;
				default:
					cout << "\nwrong input! try again : ";
					goto book_exist;
					break;
				}
			}
			else {
				cout << "\nthis book does not exist in this library at the time, do you want to check available books list ? (y-yes / n-no) : ";
				book_not_exist:
				cin >> temp_switchs;
				switch (temp_switchs)
				{
				case 'y':
					goto borrow;
					break;
				case 'n':
					student_panel();
					break;
				default:
					cout << "\nwrong input! try again : ";
					goto book_not_exist;
					break;
				}
			}
			break;
		default:
			break;
		}
	}
}
//completed
bool id_valid(string num) {
	if (strlen(num.c_str()) == 10) {
		return true;
	}
	else
		return false;
}
//completed
bool phone_valid(string num) {
	if (strlen(num.c_str()) == 11)
		return true;
	else
		return false;
}
//completed
bool book_exist(int booknum) {
	for (i = 0; i < 10000; i++) {
		if (book.book_id[i]== booknum) {
			temp_bool = true;
			break;
		}
		else
			temp_bool = false;
	}
	return temp_bool;
}
//completed
void entering_books() {
	cout << "\nEnter the number of books: ";
	cin >> n;
	clearScreen();
	for (int j = 0; j < n; j++) {
		cout << "\nType 'exit' at any time to exit.\n";
		int i = last_book_loc;
		cout << "\nEnter the book title: ";
		cin >> book.book_name[i];
		if (exit_check(book.book_name[i])) {
			clearScreen();
			cout << "Exit successfully committed.";
			break;
		}
		cout << "\nEnter the book ID: ";
		cin >> temp_book_id;
		while (book_exist(temp_book_id)) {
			cout << "\nThis book ID already exists. Enter a different ID: ";
			cin >> temp_book_id;
		}
		book.book_id[i] = temp_book_id;
		book.available[i] = true;
		book.book_loc[i] = i;
		last_book_loc++;
		clearScreen();
		cout << "\nSuccessful!";
	}
}
//completed
void available_book_list() {
	cout << "\navailable books : \n";
	for (i = 0; i < last_book_loc; i++) {
		if (book.available[i]) {
			cout << "\n" << book.book_name[i] << " - book id : " << book.book_id[i] << " - book loc : " << book.book_loc[i];
		}
	}
}
//completed
void unavailable_book_list() {
	cout << "\nunavailable books : \n";
	for (i = 0; i < last_book_loc; i++) {
		if (!book.available[i]&&book.book_id[i]) {
			cout << "\n" << book.book_name[i] << " - book id : " << book.book_id[i] << " - book loc : " << book.book_loc[i] << " - student who borrow this : " << book.who_borrows_id[i] << " - and its phone numbed is : " << book.who_borrows_num[i];
		}
	}
}
//completed
void std_borrow_list(string student_id) {
	cout << "\nyour borrow list is : \n";
	for (i = 0; i < last_book_loc; i++) {
		if (student_id == book.who_borrows_id[i]) {
			cout << "\n" << book.book_name[i] << " - book id : " << book.book_id[i];
		}
	}
}
//completed
bool exit_check(string input) {
	if (input == "exit") {
		return true;
	}
	else
		return false;
}
//completed
void giving_book() {
	cout << "\n\nenter the book id that you want to give : ";
book_id_checkerr:
	cin >> temp_booknum;
	if (book_exist(temp_booknum)) {
		clearScreen();
		for (i = 0; i < last_book_loc; i++) {
			if (book.book_id[i] == temp_booknum) {
				book.available[i] = true;
				cout << "\nsuccusful!\nnow you can give your book to ketabdar.";
			}
		}
	}
	else {
		cout << "\nwrong book id! try again : ";
		goto book_id_checkerr;
	}
}
//completed
void clearScreen() {
	system("cls");
}
//completed
bool search_book(string name) {
	temp_bool = false;
	for (i = 0; i < last_book_loc; i++) {
		if (name == book.book_name[i]&&book.available[i]) {
			temp_bool = true;
			break;
		}
		else 
			temp_bool = false;
	}
	return temp_bool;
}
//completed
