
#include "Task_data.h"

// class to store tasks and use all it's functions;
class Arr_list_ds
{
private:
	Task_data* arr_list;
	Task_data* draft_list;
	Task_data* done_list;
	int count_draft, size_draft;
	int count, size;
	int count_done, size_done;
	int choice = 0;
	string username, password, password2;
	unordered_map <string, string > P;
public:
	Arr_list_ds();
	void menu();
	void check_tasks();
	void writetofile();
	void login();
	void registeration();
	void exit();
	void login_menu();
	void add_task();
	void task_display(Task_data arr_list[], int count);
	void finish_task(string name);
	void read_from_file(Task_data arr_list[], string txt);
	void write_to_file(string txt);
	void reminder(int count);
	void arr_expand();
	void arr_delete_at(int pos, string name);
	int arr_lenth();
	bool arr_empty(int count);
	bool arr_full(int count, int size);
	~Arr_list_ds();

};