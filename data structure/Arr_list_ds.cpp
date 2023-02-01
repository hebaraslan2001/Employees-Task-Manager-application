// include all liberaries we need;
#include "Arr_list_ds.h"
#include <assert.h>
#include <fstream>
#include <ctime>
#include <cstdlib>

// constructor;
Arr_list_ds::Arr_list_ds()
{
	count = count_draft = count_done = 0;
	choice = 0;
	size = size_draft = size_done = 15;
	arr_list = new Task_data[size];
	draft_list = new Task_data[size_draft];
	done_list = new Task_data[size_done];
	ifstream check("name.csv");
	for (int i = 0; !check.eof(); i++) {
		getline(check, username, ',');
		getline(check, password, '\n');
		P[username] = password;
	}
	check.close();

}

void Arr_list_ds::writetofile()
{
	ofstream writefile;
	writefile.open("name.csv", ios::app);
	writefile << username << "," << password << endl;
	writefile.close();
}

void Arr_list_ds::login()
{
	string user, pass;
	cout << " Enter user name :" << endl;
	cin >> username;
	if (P.find(username) != P.end())
	{
		cout << " Enter password :" << endl;
		cin >> password;
		while (true)
		{
			if (password._Equal(P[username]))
			{
				cout << "\nYou are being logged in!" << "\n";
				read_from_file(arr_list, "tasks");
				read_from_file(draft_list, "draft_tasks");
				read_from_file(done_list, "done_tasks");
				check_tasks();
				menu();
			}
			else
			{
				cout << "Wrong password \nReenter password : ";
				cin >> password;
				continue;

			}
		}
	}
	else
	{
		cin.clear();
		cout << "User name not found please, Create one and try again.\n";
		login_menu();
	}
}
void Arr_list_ds::registeration()
{
	string confirmation;
	cout << "Please enter your username : ";
	cin >> username;
	cout << "\nUsername is : \"" << username << "\"\nConfirm?\n1 - Yes\n2 - No" << endl;
	cin >> confirmation;
	if (confirmation._Equal("1"))
	{
		if (P.find(username) == P.end())
		{
			while (true)
			{
				cout << "Please enter the password : ";
				cin >> password;
				cout << "Please renter your password : ";
				cin >> password2;
				if (password == password2) {
					cin.clear();
					cout << "successful registration!" << endl;
					cin.clear();
					P[username] = password;
					writetofile();
					write_to_file("tasks");
					write_to_file("draft_tasks");
					write_to_file("done_tasks");
					login_menu();
					exit();
				}
				else
				{
					cin.clear();
					cout << "Sorry invalid password" << endl;
					continue;
				}
			}
		}
		else
		{
			cout << "Sorry, This user had taken !" << endl;
			registeration();
		}
	}
	else; {
		cout << "Sorry invalid input, Please try again" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		registeration();
	}
}

void Arr_list_ds::exit()
{
	std::exit(0);
}

void Arr_list_ds::login_menu()
{
	string log_num;
	cout << "-----------------------------------------------------------\n";
	cout << "----------------Welcome to our programm--------------------\n";
	cout << "---------------------------Menu----------------------------\n";
	cout << "Hello, Would you like to log in or register\n1 - Login\n2 - Register\n3 - Exit\nYour Choise : ";
	cin >> log_num;
	if (log_num._Equal("1"))
	{
		login();
	}
	else if (log_num._Equal("2"))
	{
		registeration();
	}
	else if (log_num._Equal("3"))
	{
		exit();
	}
	else
	{
		cin.clear();
		cout << "Invalid Choice please, try again\n";
		login_menu();
	}
}

// all option for user;
void Arr_list_ds::menu()
{
	string choice;
	cout << "******************************" << endl;
	cout << "Welcome To Our Programm" << endl;
	cout << "******************************" << endl;
	cout << "1 - Add a new task.\n2 - Display all tasks.\n3 - Display Completed\n4 - Display draft.\n5 - Finish a task.\n6 - Finish a task from draft.\n7 - Edit a task.\n8 - Edit a task from draft\n9 - Exit.\n";
	cout << "******************************" << endl;
	cout << "Your choice is : ";
	cin >> choice;
	cout << endl << "******************************" << endl;
	if (choice == "1")
	{
		add_task();
	}
	else if (choice == "2")
	{
		task_display(arr_list, count);
	}
	else if (choice == "3")
	{
		task_display(done_list, count_done);
	}
	else if (choice == "4")
	{
		task_display(draft_list, count_draft);
	}
	else if (choice == "5")
	{
		finish_task("array");
	}
	else if (choice == "6")
	{
		finish_task("draft");
	}
	else if (choice == "7")
	{
		arr_list->edit_task(&arr_list, arr_list, count);
	}
	else if (choice == "8")
	{
		arr_list->edit_task(&draft_list, draft_list, count_draft);
		//check_task();
	}
	else if (choice == "9")
	{
		write_to_file("tasks");
		write_to_file("draft_tasks");
		write_to_file("done_tasks");
		std::exit(EXIT_FAILURE);
	}
	else
	{
		cout << "Invalid choice please, enter number from 1 to 4.\n";
	}
	menu();
}

void Arr_list_ds::check_tasks()
{
	time_t ttime = time(0);
	int x, y, z;
	tm* local_time = localtime(&ttime);
	x = local_time->tm_mday;
	y = 1 + local_time->tm_mon;
	z = 1900 + local_time->tm_year;
	for (int i = 0; i < count; i++)
	{
		if (arr_list[i].getDeadline_date().year >= z)
		{
			if (arr_list[i].getDeadline_date().month == y)
			{
				if (arr_list[i].getDeadline_date().day < x)
				{
					if (count_draft == size_draft)
						arr_expand();
					draft_list[count_draft] = arr_list[i];
					count_draft++;
					arr_delete_at(i, "array");
				}
			}
			else if (arr_list[i].getDeadline_date().month < y)
			{
				if (count_draft == size_draft)
					arr_expand();
				draft_list[count_draft] = arr_list[i];
				count_draft++;
				arr_delete_at(i, "array");
			}
		}
		else
		{
			if (count_draft == size_draft)
				arr_expand();
			draft_list[count_draft] = arr_list[i];
			count_draft++;
			arr_delete_at(i, "array");
		}
	}
}
//add a new task to list;
void Arr_list_ds::add_task()
{
	if (arr_full(count, size))
		arr_expand();
	Task_data new_task = arr_list->collect_data();
	arr_list[count] = new_task;
	count++;
	cout << "DONE" << endl;
	arr_list->sorting_task(arr_list, count);

}
//display all task in list to user;
void Arr_list_ds::task_display(Task_data arr_list[], int count)
{
	int choice;
	for (int i = 0; i < count; i++)
	{
		cout << "******************************" << endl;
		cout << "Task number : " << i + 1 << endl;
		cout << "Task name : " << arr_list[i].getTask_name() << endl;
		cout << "Task description : " << arr_list[i].getTask_description() << endl;
		cout << "Task start date : " << arr_list[i].getStart_date().day << " - " << arr_list[i].getStart_date().month << " - " << arr_list[i].getStart_date().year << endl;
		cout << "Task deadline date : " << arr_list[i].getDeadline_date().day << " - " << arr_list[i].getDeadline_date().month << " - " << arr_list[i].getDeadline_date().year << endl;
		cout << "Task priority : " << arr_list[i].getTask_priority() << endl;
		cout << "******************************" << endl;
	}
	cout << "1 - Go back.\n2 - Exit.\n";
	cout << "******************************" << endl;
	while (true)
	{
		cout << "Your choice : ";
		cin >> choice;
		if (choice == 1)
			menu();
		else if (choice == 2)
		{
			write_to_file("tasks");
			write_to_file("draft_tasks");
			write_to_file("done_tasks");

			std::exit(EXIT_FAILURE);
		}
		else
		{
			cout << "Invalid number please, enter 1 or 2 ." << endl;
			cout << "******************************";
		}

	}
}
//delete function from array when it done;
void Arr_list_ds::finish_task(string name)
{
	int task_no;

	if (name == "array")
	{
		arr_list->edit_task_display(arr_list, count);
		cout << "Enter the task number you have finished.";
		cout << endl << "******************************" << endl << "Your Choice : ";
		cin >> task_no; // make sure en el choice mawgod fel tasks msh akbar mn 3dadhom
		assert(task_no >= 0 && task_no <= count);
		done_list[count_done] = arr_list[(task_no - 1)];
		count_done++;
		arr_delete_at((task_no - 1), name);
		cout << "The task has been deleted successfully.";
		cout << endl << "******************************" << endl;
		reminder(count);
	}
	else
	{
		arr_list->edit_task_display(draft_list, count_draft);
		cout << "Enter the task number you have finished.";
		cout << endl << "******************************" << endl << "Your Choice : ";
		cin >> task_no; // make sure en el choice mawgod fel tasks msh akbar mn 3dadhom
		assert(task_no >= 0 && task_no <= count);
		done_list[count_done] = arr_list[(task_no - 1)];
		count_done++;
		arr_delete_at((task_no - 1), name);
		cout << "The task has been deleted successfully.";
		cout << endl << "******************************" << endl;
		reminder(count_draft);
	}


}
////take data from array and store it in main file;
void Arr_list_ds::read_from_file(Task_data arr_list[], string txt)
{

	string file_name = username + "_" + txt + ".csv";
	ifstream read_data_file(file_name);
	int temp_count = 0;
	while (!read_data_file.eof())
	{
		string a, b, c, d, e, f, g, h, i;
		date_details start, end;
		getline(read_data_file, a, ',');
		getline(read_data_file, b, ',');
		getline(read_data_file, c, ',');
		getline(read_data_file, d, ',');
		getline(read_data_file, e, ',');
		getline(read_data_file, f, ',');
		getline(read_data_file, g, ',');
		getline(read_data_file, h, ',');
		getline(read_data_file, i, '\n');
		arr_list[temp_count].setTask_name(a);
		arr_list[temp_count].setTask_description(b);
		start.day = atoi(c.c_str());
		start.month = atoi(d.c_str());
		start.year = atoi(e.c_str());
		end.day = atoi(f.c_str());
		end.month = atoi(g.c_str());
		end.year = atoi(h.c_str());
		arr_list[temp_count].setStart_date(start);
		arr_list[temp_count].setDeadline_date(end);
		arr_list[temp_count].setTask_priority(atoi(i.c_str()));
		if (txt == "tasks")
			count = (temp_count);
		else if (txt == "draft_tasks")
			count_draft = (temp_count);
		else
			count_done = (temp_count);
		temp_count++;
	}
	read_data_file.close();
}


void Arr_list_ds::write_to_file(string txt)
{
	ofstream data_file(username + "_" + txt + ".csv");
	int count_num;
	if (txt == "tasks")
		count_num = count;
	else if (txt == "draft_tasks")
		count_num = count_draft;
	else
		count_num = count_done;
	for (int i = 0; i < count_num; i++)
	{
		if (txt == "tasks")
		{
			if (!arr_empty(count))
				data_file << arr_list[i].getTask_name() << "," << arr_list[i].getTask_description() << "," << arr_list[i].getStart_date().day << "," << arr_list[i].getStart_date().month << "," << arr_list[i].getStart_date().year << "," << arr_list[i].getDeadline_date().day << "," << arr_list[i].getDeadline_date().month << "," << arr_list[i].getDeadline_date().year << "," << arr_list[i].getTask_priority() << endl;
		}
		else if (txt == "draft_tasks")
		{
			if (!arr_empty(count_draft))
				data_file << draft_list[i].getTask_name() << "," << draft_list[i].getTask_description() << "," << draft_list[i].getStart_date().day << "," << draft_list[i].getStart_date().month << "," << draft_list[i].getStart_date().year << "," << draft_list[i].getDeadline_date().day << "," << draft_list[i].getDeadline_date().month << "," << draft_list[i].getDeadline_date().year << "," << draft_list[i].getTask_priority() << endl;
		}
		else
		{
			if (!arr_empty(count_done))
				data_file << done_list[i].getTask_name() << "," << done_list[i].getTask_description() << "," << done_list[i].getStart_date().day << "," << done_list[i].getStart_date().month << "," << done_list[i].getStart_date().year << "," << done_list[i].getDeadline_date().day << "," << done_list[i].getDeadline_date().month << "," << done_list[i].getDeadline_date().year << "," << done_list[i].getTask_priority() << endl;
		}
	}
	data_file.close();
}

//notify user for new task;
void Arr_list_ds::reminder(int count)
{
	if (arr_empty(count))
	{
		cout << "Congratulation You Finish All Tasks :) !!!!!!!! ";
		cout << endl << "******************************" << endl;
		menu();
	}
	else
	{
		cout << "You did well the Next Task Is : " << arr_list[0].getTask_name();
		cout << endl << "******************************" << endl;
		menu();
	}
}

//add a new places in array;
void Arr_list_ds::arr_expand()
{
	if (arr_full(count, size))
	{
		size += 1;
		Task_data* temp_arr = new Task_data[size];
		for (int i = 0; i < count; i++)
			temp_arr[i] = arr_list[i];
		delete[] arr_list;
		arr_list = temp_arr;
	}
	else if (arr_full(count_draft, size_draft))
	{
		size_draft += 1;
		Task_data* temp_arr = new Task_data[size_draft];
		for (int i = 0; i < count_draft; i++)
			temp_arr[i] = draft_list[i];
		delete[] draft_list;
		draft_list = temp_arr;
	}
	else if (arr_full(count_done, size_done))
	{
		size_done += 1;
		Task_data* temp_arr = new Task_data[size_done];
		for (int i = 0; i < count_done; i++)
			temp_arr[i] = done_list[i];
		delete[] done_list;
		done_list = temp_arr;
	}

}
//delete task from spesific place;
void Arr_list_ds::arr_delete_at(int pos, string name)
{
	if (name == "array")
	{
		assert(pos >= 0 && pos < count);
		for (int i = pos; i <= (count - 1); i++)
			arr_list[i] = arr_list[i + 1];
		count--;
	}
	else
	{
		assert(pos >= 0 && pos < count_draft);
		for (int i = pos; i <= (count_draft - 1); i++)
			draft_list[i] = draft_list[i + 1];
		count_draft--;
	}
}

//return the number of element in array;
int Arr_list_ds::arr_lenth()
{
	return count;
}

//check if array empty;
bool Arr_list_ds::arr_empty(int count)
{
	return (count == 0);
}
//check if array full;
bool Arr_list_ds::arr_full(int count, int size)
{
	return (count == size);
}

//destructor of array;
Arr_list_ds::~Arr_list_ds()
{
	delete[] arr_list;
	delete[] draft_list;
	delete[] done_list;
}