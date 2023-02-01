
#include "Task_data.h"

const string& Task_data::getTask_name() const
{
    return task_name;
}

void Task_data::setTask_name(const string& newTask_name)
{
    task_name = newTask_name;
}

const string& Task_data::getTask_description() const
{
    return task_description;
}

void Task_data::setTask_description(const string& newTask_description)
{
    task_description = newTask_description;
}

int Task_data::getTask_priority() const
{
    return task_priority;
}

void Task_data::setTask_priority(int newTask_priority)
{
    task_priority = newTask_priority;
}

const date_details& Task_data::getStart_date() const
{
    return start_date;
}

void Task_data::setStart_date(const date_details& newStart_date)
{
    start_date = newStart_date;
}

const date_details& Task_data::getDeadline_date() const
{
    return deadline_date;
}

void Task_data::setDeadline_date(const date_details& newDeadline_date)
{
    deadline_date = newDeadline_date;
}
Task_data Task_data::collect_data()
{
    Task_data add_task;
    cout << "Please, Enter Task Title : ";
    cin >> add_task.task_name; cout << endl;
    cout << "Please, Enter Task Describtion : " << endl;
    cin >> add_task.task_description;
    string txt = "start";
    collect_date(&add_task, txt);
    txt = "deadline";
    collect_date(&add_task, txt);
    cout << "Please, Enter Task Periority : ";
    cin >> add_task.task_priority; cout << endl;
    return add_task;
}
void Task_data::collect_date(Task_data* task, string txt)
{
    while (true)
    {
        tm date_d;
        time_t ttime = time(0);
        int x, y, z;
        cout << "Please, Enter task " << txt << " date :\nDay : ";
        cin >> date_d.tm_mday;
        cout << "\nMonth : ";
        cin >> date_d.tm_mon;
        cout << "\nYear : ";
        cin >> date_d.tm_year;
        tm* local_time = localtime(&ttime);
        x = local_time->tm_mday;
        y = 1 + local_time->tm_mon;
        z = 1900 + local_time->tm_year;
        if (date_d.tm_year >= z)
        {
            if (date_d.tm_mon == y)
            {
                if (date_d.tm_mday >= x)
                {
                    if (txt == "start")
                    {
                        task->start_date.day = date_d.tm_mday;
                        task->start_date.month = date_d.tm_mon;
                        task->start_date.year = date_d.tm_year;
                        break;
                    }
                    else
                    {
                        if (date_d.tm_mday >= task->start_date.day && date_d.tm_mon >= task->start_date.month)
                        {
                            task->deadline_date.day = date_d.tm_mday;
                            task->deadline_date.month = date_d.tm_mon;
                            task->deadline_date.year = date_d.tm_year;
                            break;
                        }
                        else
                        {
                            cout << "Invalid date .\n";
                            cout << "******************************" << endl;
                            continue;
                        }
                    }
                }
                else
                {
                    cout << "Invalid date .\n";
                    cout << "******************************" << endl;
                    continue;
                }
            }
            else if (date_d.tm_mon > y)
            {
                if (txt == "start")
                {
                    task->start_date.day = date_d.tm_mday;
                    task->start_date.month = date_d.tm_mon;
                    task->start_date.year = date_d.tm_year;
                    break;
                }
                else
                {
                    if (date_d.tm_mon >= task->start_date.month)
                    {
                        task->deadline_date.day = date_d.tm_mday;
                        task->deadline_date.month = date_d.tm_mon;
                        task->deadline_date.year = date_d.tm_year;
                        break;
                    }
                    else
                    {
                        cout << "Invalid date .\n";
                        cout << "******************************" << endl;
                        continue;
                    }

                }
            }
            else {
                cout << "Invalid date .\n";
                cout << "******************************" << endl;
                continue;
            }
        }
        else {
            cout << "Invalid date .\n";
            cout << "******************************" << endl;
            continue;
        }

    }

}
void Task_data::edit_task_display(Task_data arr_list[], int count)
{
    for (int i = 0; i < count; i++)
    {
        cout << "******************************" << endl;
        cout << "Task number : " << i + 1 << endl;
        cout << "Task name : " << arr_list[i].task_name << endl;
        cout << "Task description : " << arr_list[i].task_description << endl;
        cout << "Employee name : " << arr_list[i].task_emp_name << endl;
        cout << "Task start date : " << arr_list[i].start_date.day << " - " << arr_list[i].start_date.month << " - " << arr_list[i].start_date.year << endl;
        cout << "Task deadline date : " << arr_list[i].deadline_date.day << " - " << arr_list[i].deadline_date.month << " - " << arr_list[i].deadline_date.year << endl;
        cout << "Task priority : " << arr_list[i].task_priority << endl;
    }
}
void Task_data::edit_task(Task_data* arr_list[], Task_data arr[], int count)
{
    int task_no;
    edit_task_display(arr, count);
    cout << "******************************" << endl;
    cout << "Enter the task number you want to edit.\n";
    cout << "******************************" << endl << "Your Choice : ";
    cin >> task_no;
    assert((task_no - 1) < count);
    string choice;
    cout << endl << "******************************" << endl;
    cout << "1 - Edit a task name.\n2 - Edit a Describtion.\n3 - Edit an Employee name.\n4 - Edit start date.\n5 - Edit deadline date.\n6 - Edit a task priority.\n";
    cout << "******************************" << endl;
    cout << "Your choice is : ";
    cin >> choice;
    cout << endl << "******************************" << endl;
    if (choice == "1")
    {
        cout << "Enter the new task name : ";
        cin >> arr_list[(task_no - 1)]->task_name;
    }
    else if (choice == "2")
    {
        cout << "Enter the new task Describtion : " << endl;
        cin >> arr_list[(task_no - 1)]->task_description;
    }
    else if (choice == "3")
    {
        cout << "Enter the new Employee name : ";
        cin >> arr_list[(task_no - 1)]->task_emp_name;
    }
    else if (choice == "4")
    {
        int num1 = (task_no - 1);
        string txt = "start";
        edit_date(arr_list, txt, num1);
    }
    else if (choice == "5")
    {
        int num2 = (task_no - 1);
        string txt = "deadline";
        edit_date(arr_list, txt, num2);
    }
    else if (choice == "6")
    {
        cout << "Enter the new task priority : ";
        cin >> arr_list[(task_no - 1)]->task_priority;
        sorting_task(arr, count);
    }
    else
    {
        cout << "Invalid choice.\n";
        edit_task(arr_list, arr, count);
    }
}
void Task_data::edit_date(Task_data* arr_list[], string txt, int num)
{
    while (true)
    {
        tm date_d;
        time_t ttime = time(0);
        int x, y, z;
        cout << "Please, Enter task " << txt << " date :\nDay : ";
        cin >> date_d.tm_mday;
        cout << "\nMonth : ";
        cin >> date_d.tm_mon;
        cout << "\nYear : ";
        cin >> date_d.tm_year;
        tm* local_time = localtime(&ttime);
        x = local_time->tm_mday;
        y = 1 + local_time->tm_mon;
        z = 1900 + local_time->tm_year;
        if (date_d.tm_year >= z)
        {
            if (date_d.tm_mon == y)
            {
                if (date_d.tm_mday >= x)
                {
                    if (txt == "start")
                    {
                        if (date_d.tm_mday <= arr_list[num]->deadline_date.day && date_d.tm_mon <= arr_list[num]->deadline_date.month && date_d.tm_year <= arr_list[num]->deadline_date.year)
                        {
                            arr_list[num]->start_date.day = date_d.tm_mday;
                            arr_list[num]->start_date.month = date_d.tm_mon;
                            arr_list[num]->start_date.year = date_d.tm_year;
                            break;
                        }
                        else
                        {
                            cout << "Sorry, we can't complete because deadline before this date.\n";
                            continue;
                        }
                    }
                    else
                    {
                        if (date_d.tm_mday >= arr_list[num]->start_date.day && date_d.tm_mon >= arr_list[num]->start_date.month && date_d.tm_year >= arr_list[num]->start_date.year)
                        {
                            arr_list[num]->deadline_date.day = date_d.tm_mday;
                            arr_list[num]->deadline_date.month = date_d.tm_mon;
                            arr_list[num]->deadline_date.year = date_d.tm_year;
                            break;
                        }
                        else
                        {
                            cout << "Sorry, we can't complete because deadline before start date.\n";
                            continue;
                        }
                    }
                }
                else
                {
                    cout << "Invalid date .\n";
                    cout << "******************************" << endl;
                    continue;
                }
            }
            else if (date_d.tm_mon > y)
            {
                if (txt == "start")
                {
                    if (date_d.tm_mday <= arr_list[num]->deadline_date.day && date_d.tm_mon <= arr_list[num]->deadline_date.month && date_d.tm_year <= arr_list[num]->deadline_date.year)
                    {
                        arr_list[num]->start_date.day = date_d.tm_mday;
                        arr_list[num]->start_date.month = date_d.tm_mon;
                        arr_list[num]->start_date.year = date_d.tm_year;
                        break;
                    }
                    else
                    {
                        cout << "Sorry, we can't complete because deadline before this date.\n";
                        continue;
                    }
                }
                else
                {
                    if (date_d.tm_mday >= arr_list[num]->start_date.day && date_d.tm_mon >= arr_list[num]->start_date.month && date_d.tm_year >= arr_list[num]->start_date.year)
                    {
                        arr_list[num]->deadline_date.day = date_d.tm_mday;
                        arr_list[num]->deadline_date.month = date_d.tm_mon;
                        arr_list[num]->deadline_date.year = date_d.tm_year;
                        break;
                    }
                    else
                    {
                        cout << "Sorry, we can't complete because deadline before start date.\n";
                        continue;
                    }
                }
            }
            else {
                cout << "Invalid date .\n";
                cout << "******************************" << endl;
                continue;
            }
        }
        else {
            cout << "Invalid date .\n";
            cout << "******************************" << endl;
            continue;
        }

    }
}
int Task_data::partition(Task_data arr[], int start, int end)
{
    Task_data pivot = arr[start];

    int count_2 = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (arr[i].task_priority >= pivot.task_priority)
            count_2++;
    }
    // Giving pivot element its correct position
    int pivotIndex = start + count_2;
    swap(arr[pivotIndex], arr[start]);
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
    while (i < pivotIndex && j > pivotIndex)
    {
        while (arr[i].task_priority >= pivot.task_priority)
        {
            i++;
        }
        while (arr[j].task_priority < pivot.task_priority)
        {
            j--;
        }
        if (i < pivotIndex && j > pivotIndex)
        {
            swap(arr[i++], arr[j--]);
        }
    }
    return pivotIndex;
}
//quickSort array for sorting_task fun;
void Task_data::quickSort(Task_data arr[], int start, int end)
{
    // base case
    if (start >= end)
        return;
    // partitioning the array
    int p = partition(arr, start, end);
    // Sorting the left part
    quickSort(arr, start, p - 1);
    // Sorting the right part
    quickSort(arr, p + 1, end);
}
//sort task refrence this periority with dessnding order;
void Task_data::sorting_task(Task_data arr_list[], int count)
{
    quickSort(arr_list, 0, count - 1);
}
