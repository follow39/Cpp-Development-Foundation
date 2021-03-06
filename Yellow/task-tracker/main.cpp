#include <iostream>
#include <map>
#include <set>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

using TasksInfo = map<TaskStatus, int>;

int TaskInfoSize(const TasksInfo& tasks) {
    int cnt = 0;
    for(const auto& [status, value] : tasks) {
        cnt += value;
    }
    return cnt;
}

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return team.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) {
        team[person][TaskStatus::NEW] += 1;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
            const string& person, int task_count) {
        if(team.count(person) == 0) {
            return {};
        }

        TasksInfo tasksListNew;
        TasksInfo tasksListOld = team[person];

        tasksListOld.erase(TaskStatus::DONE);

        if(task_count > TaskInfoSize(tasksListOld)) {
            task_count = TaskInfoSize(tasksListOld);
        }

        for(auto& [status, value] : tasksListOld) {
            TaskStatus newStatus = static_cast<TaskStatus>(static_cast<int>(status) + 1);
            if(task_count > value) {
                task_count -= value;
                tasksListNew[newStatus] += value;
                value = 0;
            } else {
                value -= task_count;
                tasksListNew[newStatus] += task_count;
                break;
            }
        }

        team[person][TaskStatus::NEW] = tasksListNew[TaskStatus::NEW] + tasksListOld[TaskStatus::NEW];
        team[person][TaskStatus::IN_PROGRESS] = tasksListNew[TaskStatus::IN_PROGRESS] + tasksListOld[TaskStatus::IN_PROGRESS];
        team[person][TaskStatus::TESTING] = tasksListNew[TaskStatus::TESTING] + tasksListOld[TaskStatus::TESTING];
        team[person][TaskStatus::DONE] += tasksListNew[TaskStatus::DONE];

        if(tasksListNew[TaskStatus::NEW] == 0) {
            tasksListNew.erase(TaskStatus::NEW);
        }
        if(tasksListNew[TaskStatus::IN_PROGRESS] == 0) {
            tasksListNew.erase(TaskStatus::IN_PROGRESS);
        }
        if(tasksListNew[TaskStatus::TESTING] == 0) {
            tasksListNew.erase(TaskStatus::TESTING);
        }
        if(tasksListNew[TaskStatus::DONE] == 0) {
            tasksListNew.erase(TaskStatus::DONE);
        }

        if(tasksListOld[TaskStatus::NEW] == 0) {
            tasksListOld.erase(TaskStatus::NEW);
        }
        if(tasksListOld[TaskStatus::IN_PROGRESS] == 0) {
            tasksListOld.erase(TaskStatus::IN_PROGRESS);
        }
        if(tasksListOld[TaskStatus::TESTING] == 0) {
            tasksListOld.erase(TaskStatus::TESTING);
        }
        if(tasksListOld[TaskStatus::DONE] == 0) {
            tasksListOld.erase(TaskStatus::DONE);
        }


        if(team[person][TaskStatus::NEW] == 0) {
            team[person].erase(TaskStatus::NEW);
        }
        if(team[person][TaskStatus::IN_PROGRESS] == 0) {
            team[person].erase(TaskStatus::IN_PROGRESS);
        }
        if(team[person][TaskStatus::TESTING] == 0) {
            team[person].erase(TaskStatus::TESTING);
        }
        if(team[person][TaskStatus::DONE] == 0) {
            team[person].erase(TaskStatus::DONE);
        }

        return tie(tasksListNew, tasksListOld);
    }
private:
    map<string, TasksInfo> team;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
                                           ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
                                           ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
                                           ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
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
