#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>

using namespace std;
/*
enum class TaskStatus
{
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

using TasksInfo = map<TaskStatus, int>; */

class TeamTasks
{
public:
    // Get statistics on the task statuses of a specific developer
    const TasksInfo& GetPersonTasksInfo(const string& person) const
    {
        return MAIN.at(person);

        /*for (const auto& status : MAIN.at(person))
        {
        }*/
    }

    // Add a new task (with the NEW status) for a specific developer
    void AddNewTask(const string& person)
    {
        MAIN[person][TaskStatus::NEW] += 1;
    }

    // Update statuses for a given number of tasks of a specific developer
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count)
    {
        TasksInfo upgrade;
        TasksInfo updated;
        TasksInfo untouched;
        for (auto& c : MAIN[person])
        {

            if (c.first == TaskStatus::NEW)
            {
                if (c.second > 0) {
                    int new_status_count = c.second;
                    while (task_count > 0 && new_status_count > 0)
                    {
                        ++updated[TaskStatus::IN_PROGRESS];
                        ++upgrade[TaskStatus::IN_PROGRESS];
                        --new_status_count;
                        --task_count;
                    }

                    if (new_status_count > 0)
                    {
                        untouched[TaskStatus::NEW] += new_status_count;
                        upgrade[TaskStatus::NEW] += new_status_count;
                    }
                }
            }
            if (c.first == TaskStatus::IN_PROGRESS) 
            {
                if (c.second > 0) 
                {
                    int in_progress_status_count = c.second;
                    while (in_progress_status_count > 0 && task_count > 0) 
                    {
                        ++updated[TaskStatus::TESTING];
                        ++upgrade[TaskStatus::TESTING];
                        --in_progress_status_count;
                        --task_count;
                    }
                    if (in_progress_status_count > 0) 
                    {
                        untouched[TaskStatus::IN_PROGRESS] += in_progress_status_count;
                        upgrade[TaskStatus::IN_PROGRESS] += in_progress_status_count;
                    }
                }
            }
            if (c.first == TaskStatus::TESTING) 
            {
                if (c.second > 0) 
                {
                    int testing_status_count = c.second;
                    while (testing_status_count > 0 && task_count > 0) 
                    {
                        ++updated[TaskStatus::DONE];
                        ++upgrade[TaskStatus::DONE];
                        --testing_status_count;
                        --task_count;
                    }
                    if (testing_status_count > 0) 
                    {
                        untouched[TaskStatus::TESTING] += testing_status_count;
                        upgrade[TaskStatus::TESTING] += testing_status_count;
                    }
                }
            }
            if (c.first == TaskStatus::DONE) 
            {
                if (c.second > 0) 
                {
                    upgrade[TaskStatus::DONE] += c.second;
                }
            }
        }
        MAIN[person] = upgrade;
        return make_tuple(updated, untouched);
    }

private:
    map<string, TasksInfo> MAIN;
};

// We accept the dictionary by value in order to be able
//// to access the missing key using [] and get 0,
// without changing the original dictionary
void PrintTasksInfo(TasksInfo tasks_info)
{
        cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main()
{
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i)
    {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}
