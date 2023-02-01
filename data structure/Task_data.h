#pragma once

#include<iostream>
#include <assert.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;
struct date_details
{
    int day = 0, month = 0, year = 0;
};
class Task_data
{
private:
    string task_name = "task_name", task_description = "task_description", task_emp_name = "task_emp_name";
    int task_priority = 0;
    date_details start_date, deadline_date;
public:
    //Task_data();
    Task_data collect_data();
    void collect_date(Task_data* task, string txt);
    void edit_task_display(Task_data arr_list[], int count);
    void edit_task(Task_data* arr_list[], Task_data arr[], int count);
    void edit_date(Task_data* arr_list[], string txt, int num);
    int partition(Task_data arr[], int start, int end);
    void quickSort(Task_data arr[], int start, int end);
    void sorting_task(Task_data arr_list[], int count);
    const string& getTask_name() const;
    void setTask_name(const string& newTask_name);
    const string& getTask_description() const;
    void setTask_description(const string& newTask_description);
    int getTask_priority() const;
    void setTask_priority(int newTask_priority);
    const date_details& getStart_date() const;
    void setStart_date(const date_details& newStart_date);
    const date_details& getDeadline_date() const;
    void setDeadline_date(const date_details& newDeadline_date);

};


