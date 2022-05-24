/*#include "q.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
using namespace std;
void load_queue(const char* filename, queue_pts& empl, queue_pts& unempl);
void show_queue(queue_pts& q_pt);
void main() {
	setlocale(LC_ALL, "rus");
	queue_pts employable;
	queue_pts unemployable;
	load_queue("data.txt", employable, unemployable);
	cout << "credit: \n";
	show_queue(employable);
	cout << "vklad: \n";
	show_queue(unemployable);
}

void load_queue(const char* filename, queue_pts& empl, queue_pts& unempl)
{
	ifstream f(filename);
	if (f.is_open()) {
		while (!f.eof())
		{
			char* man = new char[120];
			f.getline(man, 120);
			char* name = new char[50];
			char* initials = new char[7];
			char* sex = new char[5];
			int age;
			char* job = new char[20];
			int income;
			char* purpose = new char[20];

			sscanf_s(man, "%s %s %s %d %s %d %s", name, 50, initials, 4, sex, 5, &age, job, 20, &income, purpose, 20);
			if (!strcmp(purpose, "вклад")) {
				enqueue(unempl, name, age);
			}
			else
			{
				enqueue(empl, name, age);
			}
		}
		f.close();
	}
	else {
		cout << "can not read the file\n";
	}
}


void show_queue(queue_pts& q_pt)
{
	int i = 0;
	while (q_pt.length > 0) {
		person p;
		if (dequeue(q_pt, p)) {
			cout << ++i << ".\t" << p.name << "\t Age: " << p.age << endl;
		}
	}

}*/

#include <iostream>
#include <fstream>
#include "cgi.h"
#include "q.h"
#include <stdio.h>
using namespace std;

void show_content();
void show_menu();
void show_header();
void main() {
	cout << "Content-type: text/html; charset=Windows-1251\n\n";
	ifstream f("_index");
	if (f.is_open())
	{
		auto sz = 65536;
		auto buf = new char[sz];
		while (!f.eof()) {
			f.getline(buf, sz);
			if (strcmp(buf, "<!--#content#-->") == 0) {
				show_content();
			}
			else if (!strcmp(buf, "<!--#menu#-->"))
			{
				show_menu();
			}
			else if (!strcmp(buf, "<!--#header#-->"))
			{
				show_header();
			}
			cout << buf;
		}
		delete[] buf;
		f.close();
	}
	else {
		cout << "Не удалось вывести страницу";
	}
}
void show_header()
{
	cout << "ДЗ СО СКОБКАМИ";
}
void show_menu()
{
	ifstream f("menu");
	if (f.is_open())
	{
		auto sz = 1024;
		auto buf = new char[sz];
		while (!f.eof())
		{
			f.getline(buf, sz);
			char* name;
			char* addrr = strtok_s(buf, " ", &name);
			cout << "<div class='menu-item'>"
				"<a href='" << addrr << "'>" <<
				name << "</a>"
				"</div>";
		}
	}
	f.close();
}
void show_content()
{
#ifndef _DEBUG
	char* data = nullptr;
	get_form_data(data);
#else
	const char* data = "imya=Sergey&email=a%40b.ru";
#endif

	if (data && strlen(data) > 0)
	{
		//cout << "<div>" << data << "</div>";
		char* value = nullptr;
		get_param_value(value, "expression", data);

		queue_pts credit;
		queue_pts contribution;
		load_queue("data.txt", credit, contribution);
		cout << "credit: \n<br>";
		show_queue(credit);
		cout << "vklad: \n<br>";
		show_queue(contribution);


	}
	cout << "<form method='get' action='third.cgi'>";
	cout << "Распределить по вкладам и кредитам: <input type='text' name='expression' maxlength='50' size='50' value=\"Распределить?\"><br>";
	cout << "<input type='submit' value='Отправить' action='third.cgi'>";
	cout << "</form>";
	
	delete[] data;
}


void load_queue(const char* filename, queue_pts& empl, queue_pts& unempl)
{
	ifstream f(filename);
	if (f.is_open()) {
		while (!f.eof())
		{
			char* man = new char[120];
			f.getline(man, 120);
			char* name = new char[50];
			char* initials = new char[7];
			char* sex = new char[5];
			int age;
			char* job = new char[20];
			int income;
			char* purpose = new char[20];

			sscanf_s(man, "%s %s %s %d %s %d %s", name, 50, initials, 4, sex, 5, &age, job, 20, &income, purpose, 20);
			if (!strcmp(purpose, "вклад")) {
				enqueue(unempl, name, age);
			}
			else
			{
				enqueue(empl, name, age);
			}
		}
		f.close();
	}
	else {
		cout << "can not read the file\n<br>";
	}
}


void show_queue(queue_pts& q_pt)
{
	int i = 0;
	while (q_pt.length > 0) {
		person p;
		if (dequeue(q_pt, p)) {
			cout << "<div>"<<++i << ".\t" << p.name << "\t Age: " << p.age <<"</div>";
		}
	}

}