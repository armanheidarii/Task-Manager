#include <iostream>
#include "clui.h"
#include <string.h>
using namespace std;
#define max 500
#define min 2
char r[2];
struct task
{
    char *name = new char[max];
    char *desc = new char[max];
    int prior;
    char *deadline = new char[max];
};
void line(int n)
{
    for (int j = 0; j < n; j++)
        cout << '-';
    flush();
}
void invalied()
{
    clear_screen();
    change_color_rgb(240, 5, 30);
    cout << "your action is invalied" << endl
         << endl;
    reset_color();
    cout << "please try again..." << endl;
    delay(2500);
}
int len(char *a)
{
    int index = 0;
    for (int i = 0; a[i] != 0; i++)
    {
        index++;
    }
    return index;
}
void new_task(task *task, int i)
{
    clear_screen();
    cout << "please enter your task name:" << endl;
    cin.getline(r, min);
    cin.getline(task[i].name, max);
    for (int j = 0; len(task[i].name) > 100; j++)
    {
        invalied();
        clear_screen();
        cout << "please enter your task name:" << endl;
        cin.getline(task[i].name, max);
    }
    clear_screen();
    cout << "please enter your task describ:" << endl;
    cin.getline(task[i].desc, max);
    for (int j = 0; len(task[i].desc) > 400; j++)
    {
        invalied();
        clear_screen();
        cout << "please enter your task describ:" << endl;
        cin.getline(task[i].desc, max);
    }
    clear_screen();
    cout << "please enter your task priority:" << endl;
    cin >> task[i].prior;
    for (int j = 0; task[i].prior < 0 || task[i].prior > 10; j++)
    {
        invalied();
        clear_screen();
        cout << "please enter your task priority:" << endl;
        cin >> task[i].prior;
    }
    clear_screen();
    cout << "please enter your task deadline: (example: 2021/01/01)" << endl;
    cin.getline(r, min);
    cin.getline(task[i].deadline, max);
    for (int j = 0; len(task[i].deadline) > 10; j++)
    {
        invalied();
        clear_screen();
        cout << "please enter your task deadline: (example: 2021/01/01)" << endl;
        cin.getline(task[i].deadline, max);
    }
    clear_screen();
    cursor_to_pos(1, get_window_cols() / 2 - 2);
    change_color_rgb(0, 255, 0);
    cout << "Success" << endl;
    reset_color();
    restore_cursor();
    delay(2000);
    clear_screen();
}
void insertion_sort(task *a, int size)
{
    for (int i = 0; i < size; i++)
    {
        task x = a[i];
        int j = i;
        while (j > 0 && a[j - 1].prior < x.prior)
        {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = x;
    }
}
void swap(task *&s, task *&t)
{
    task *temp = s;
    s = t;
    t = temp;
}
void bublle_sort1(task *string, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (strcmp(string[j + 1].name, string[j].name) < 0)
                swap(string[j + 1], string[j]);
}
void bublle_sort2(task *string, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (strcmp(string[j + 1].desc, string[j].desc) < 0)
                swap(string[j + 1], string[j]);
}
void list(task *&task, int &i);
void delete_task(task *&task1, int &i, int a[], int n)
{
    task *task2 = task1;
    task1 = new task[max];
    for (int j = 0, k = 0, p = 0; j < i; j++, k++)
    {
        while (p < n)
            if (a[p] - 1 == j)
            {
                j++;
                p++;
            }
            else
                break;
        task1[k] = task2[j];
    }
    delete[] task2;
    for (int j = 0; j < n; j++)
        i--;
    list(task1, i);
}
void sort_menu(task *&task, int &i)
{
    int n;
    for (bool flag = true; flag == true;)
    {
        flag = false;
        clear_screen();
        cout << "please choose your sort: " << endl
             << endl
             << "1) sort by name" << endl
             << "2) sort by describ" << endl
             << "3) sort by priority";
        cursor_to_pos(get_window_rows() - 2, 1);
        line(get_window_cols());
        cout << "choose your action: ";
        cin >> n;
        if (n == 3)
            insertion_sort(task, i);
        else if (n == 2)
            bublle_sort2(task, i);
        else if (n == 1)
            bublle_sort1(task, i);
        else
        {
            invalied();
            flag = true;
        }
    }
    list(task, i);
    //have back
}
void bublle_sort(int a[], int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (a[j + 1] < a[j])
                swap(a[j + 1], a[j]);
}
void list(task *&task, int &i);
void menu_list(task *&task, int &i)
{
    char n, n2;
    line(35);
    cout << endl
         << endl
         << "Enter task number for show task" << endl
         << endl
         << "Press D for delete (example: D1)" << endl
         << endl
         << "Press S for sort menu" << endl
         << endl
         << "Press M for go back to main menu";
    cursor_to_pos(get_window_rows() - 2, 1);
    line(get_window_cols());
    cout << "choose your action: ";
    cin >> n;
    restore_cursor();
    if (n == 'D' || n == 'd')
    {
        int *a = new int[100];
        int j = 0, y = 0, flag = false, glag = true;
        for (cin >> a[j]; a[j] != 0;)
        {
            y++;
            if (a[j] <= 0 || a[j] > i || i < y)
                flag = true;
            j++;
            cin >> a[j];
        }
        for (int h = 0; glag == true && h < y; h++)
            for (int h2 = 1; h2 < (y - h); h2++)
                if (a[h] == a[h + h2])
                {
                    flag = true;
                    glag = false;
                    break;
                }
        if (flag)
        {
            invalied();
            list(task, i);
            return;
        }
        else
        {
            bublle_sort(a, y);
            delete_task(task, i, a, y);
            return;
        }
        //upgrade(kbhit)
    }
    else if (n == 'M' || n == 'm')
        return;
    else if ((n - 48) > 0 && (n - 48) <= i)
    {
        n -= 48;
        int s = n;
        if (i == 0)
        {
            list(task, i);
            return;
        }
        clear_screen();
        cout << s << ": " << endl
             << endl
             << "title: " << task[s - 1].name << endl
             << endl
             << "describ: " << task[s - 1].desc << endl
             << endl
             << "priority: " << task[s - 1].prior << endl
             << endl
             << "deadline: " << task[s - 1].deadline << endl
             << endl;
        line(35);
        cout << endl
             << endl;
        cout << "Enter D for delete" << endl
             << endl
             << "Enter C for change" << endl
             << endl
             << "Enter B for back";
        cursor_to_pos(get_window_rows() - 2, 1);
        line(get_window_cols());
        cout << "choose your action: ";
        cin >> n2;
        restore_cursor();
        if (n2 == 'D' || n2 == 'd')
        {
            int a[] = {n};
            delete_task(task, i, a, 1);
            return;
        }
        else if (n2 == 'C' || n2 == 'c')
        {
            for (bool flag = true; flag == true;)
            {
                flag = false;
                clear_screen();
                cout << "which one you want to change?" << endl
                     << endl
                     << "1) name" << endl
                     << "2) describ" << endl
                     << "3) priority" << endl
                     << "4) deadline";
                cursor_to_pos(get_window_rows() - 2, 1);
                line(get_window_cols());
                cout << "choose your action: ";
                cin >> n;
                restore_cursor();
                clear_screen();
                cout << "write new ";
                switch (n - 48)
                {
                case 1:
                    cout << "name: ";
                    cin.getline(r, min);
                    cin.getline(task[s - 1].name, max);
                    for (int j = 0; len(task[s - 1].name) > 100; j++)
                    {
                        invalied();
                        clear_screen();
                        cout << "write new name: ";
                        cin.getline(task[s - 1].name, max);
                    }
                    break;
                case 2:
                    cout << "describ: ";
                    cin.getline(r, min);
                    cin.getline(task[s - 1].desc, max);
                    for (int j = 0; len(task[s - 1].desc) > 400; j++)
                    {
                        invalied();
                        clear_screen();
                        cout << "write new describ: ";
                        cin.getline(task[s - 1].desc, max);
                    }
                    break;
                case 3:
                    cout << "priority: ";
                    cin >> task[s - 1].prior;
                    for (int j = 0; task[s - 1].prior < 0 || task[s - 1].prior > 10; j++)
                    {
                        invalied();
                        clear_screen();
                        cout << "write new priority: ";
                        cin >> task[s - 1].prior;
                    }
                    break;
                    //agar dar change kardan priority char d vared shavad run mikhorad
                case 4:
                    cout << "deadline: ";
                    cin.getline(r, min);
                    cin.getline(task[s - 1].deadline, max);
                    for (int j = 0; len(task[s - 1].deadline) > 10; j++)
                    {
                        invalied();
                        clear_screen();
                        cout << "write new deadline: ";
                        cin.getline(task[s - 1].deadline, max);
                    }
                    break;
                default:
                    invalied();
                    flag = true;
                }
                //have success
                //have back
            }
            //go list2
            list(task, i);
            return;
        }
        else if (n2 == 'B' || n2 == 'b')
        {
            list(task, i);
            return;
        }
        else
        {
            invalied();
            //go list2
            list(task, i);
            return;
        }
    }
    else if (n == 'S' || n == 's')
    {
        sort_menu(task, i);
        return;
    }
    else
    {
        invalied();
        list(task, i);
        return;
    }
    //baznevisi: varieble n bayad int tarif shavad na char chon agar list empty bashad 3 bar invalied neshoon midahad
    //dar in soorat bayad kol function menu_list baznevisi shavaad va s ha n shavad va n-=48 ha pak shavad va horoof code asci shavad dar soorat niaz n2 ham int shavad
    //function menu_list chand function shavad
}
void list(task *&task, int &i)
{
    clear_screen();
    if (i == 0)
    {
        change_color_rgb(240, 5, 30);
        cout << "list is empty!" << endl
             << endl;
        reset_color();
    }
    else
    {
        for (int j = 0; j < i; j++)
        {
            cout << j + 1 << ": " << endl;
            if (len(task[j].name) > get_window_cols())
                cout << "title: " << task[j].name[0] << len(task[j].name) - 2 << task[j].name[len(task[j].name) - 1] << endl;
            else
                cout << "title: " << task[j].name << endl;
            cout << "describ: " << task[j].desc << endl
                 << "priority: " << task[j].prior << endl
                 << "deadline: " << task[j].deadline << endl
                 << endl;
        }
    }
    menu_list(task, i);
    clear_screen();
}
int main()
{
    init_clui();
    save_cursor();
    cursor_to_pos(1, get_window_cols() / 2 - 11);
    cout << "welcome to my program :)";
    cursor_to_pos(4, get_window_cols() / 2 - 6);
    change_color_rgb(245, 255, 0);
    cout << "ITP Fall 99" << endl;
    reset_color();
    delay(4000);
    clear_screen();
    restore_cursor();
    char n;
    task *memory = new task[max];
    for (int i = 0, flag = false; true;)
    {
        if (flag == true)
            i++;
        flag = false;
        cursor_to_pos(1, get_window_cols() / 2 - 6);
        change_color_rgb(0, 240, 255);
        cout << "* main menu *";
        reset_color();
        restore_cursor();
        cout
            << endl
            << endl
            << "1) new task" << endl
            << "2) list" << endl
            << "0) exit" << endl;
        cursor_to_pos(get_window_rows() - 2, 1);
        line(get_window_cols());
        cout << "choose your action: ";
        cin >> n;
        restore_cursor();
        switch (n - 48)
        {
        case 1:
            flag = true;
            new_task(memory, i);
            break;
        case 2:
            list(memory, i);
            break;
        case 0:
            clear_screen();
            cursor_to_pos(get_window_rows() / 2 - 5, get_window_cols() / 2 - 8);
            cout << "Have a good day ";
            delay(2000);
            cursor_to_pos(get_window_rows() / 2 - 3, get_window_cols() / 2 - 13);
            cout << "or maybe have a good night ";
            delay(3000);
            cursor_to_pos(get_window_rows() / 2 - 1, get_window_cols() / 2 - 3);
            cout << "Bye :)" << endl;
            cursor_to_pos(get_window_rows(), get_window_cols() - 15);
            cout << "Create by Arman";
            delay(5000);
            exit(0);
        default:
            invalied();
            clear_screen();
        }
    }
    quit();
    return 0;
}
