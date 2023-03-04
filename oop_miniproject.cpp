// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
// USERNAME : MITWPU.IN
// PASSWORD : MITWPU

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <vector>
using namespace std;

void redirect(string s)
{
    system("cls");
    for (int j = 0; j < 3; j++)
    {
        cout << s;
        for (int k = 0; k < 6; k++)
        {
            cout << ".";
            Sleep(100);
        }
        system("cls");
    }
}

class Employee
{
    string emp_id; // Employee ID
    string name;
    string qualification;
    string address;
    string email;
    string contact;

    struct salary
    {
        float basic_salary;
        float DA;
        float HRA;
        float PF;
        float other;
    } sal;

    void calculate();           // To calculate DF,PF,HRA etc.
    bool update(bool);          // To Update values
    bool input_rec();           // Input form
    bool check_id(string);      // Unique ID
    bool check_email(string);   // At least 1 @ aur 1.
    bool check_contact(string); // 10 digits
    bool check_salary(float);   // sal>0
    bool check_num(string);     //  To string all character digits check

    // MAIN FUNCTIONS
    void add_rec();
    void remove_rec(bool);
    void update_rec(bool);
    void file_sort(int);

public:
    Employee()
    {
        emp_id = "-";
        name = "-";
        qualification = "-";
        address = "-";
        email = "-";
        contact = "-";
        sal.basic_salary = 0;
        sal.DA = 0;
        sal.HRA = 0;
        sal.other = 0;
        sal.PF = 0;
    }

    void display_rec();        // Single record display
    void display_all_rec();    // call dis_rec for all
    void search_rec(bool);     // search
    void disp_sort(int, bool); // sorted display in ascending
    void display_table_rec();

    // FRIEND FUNCTIONS
    friend vector<Employee> bubble_sort(vector<Employee>, int);
    friend void admin();
    friend void update(Employee);
    friend void del(Employee);
    friend void sort_in_file(Employee);

    // FRIEND STREAM INSERTION EXTRACTION
    friend ostream &operator<<(ostream &out, const Employee &Emp) // operator to write
    {
        out << Emp.name << endl
            << Emp.emp_id << endl
            << Emp.qualification << endl
            << Emp.address << endl
            << Emp.email << endl
            << Emp.contact << endl
            << Emp.sal.basic_salary << endl;
    } // file<<Emp

    friend istream &operator>>(istream &in, Employee &Emp) // operator to read
    {
        in >> Emp.name >> Emp.emp_id >> Emp.qualification >> Emp.address >> Emp.email >> Emp.contact >> Emp.sal.basic_salary;
    } // file>>Emp
};

bool Employee::check_id(string id)
{
    ifstream file("Employee_data.txt");
    Employee temp;
    if (!file)
        return true;

    file >> temp;

    while (!file.eof())
    {
        if (id == temp.emp_id)
        {
            file.close();
            return false;
        }
        file >> temp;
    }

    file.close();
    return true;
}

bool Employee::check_num(string c)
{
    for (auto dig : c)
    {
        if (isdigit(dig) == 0)
            return false;
    }
    return true;
}

bool Employee::check_contact(string c)
{
    if (c.size() == 10 && check_num(c))
        return true;

    else
        return false;
}

bool Employee::check_email(string mail)
{
    bool found_at = false;
    bool found_dot = false;

    for (auto c : mail)
    {
        if (c == '@')
            found_at = true;

        if (c == '.')
            found_dot = true;
    }

    if (found_dot && found_at)
        return true;

    else
        return false;
}

bool Employee::check_salary(float sal)
{
    if (sal > 0)
        return true;
    else
        return false;
}

void Employee::calculate()
{
    sal.DA = float(0.97) * this->sal.basic_salary;
    sal.HRA = float(0.10) * this->sal.basic_salary;
    sal.PF = float(0.12) * this->sal.basic_salary;
    sal.other = float(0.1) * this->sal.basic_salary;
}

bool Employee::update(bool i)
{
    string choice;
    bool check_it;

    do
    {
        if (i == 0)
        {
            system("cls");
            cout << "\n\n\n\n\t\t\t\t\tUPDATE EMPLOYEE RECORD FOR " << this->emp_id;
            cout << "\n\t\t\t\t\t-------------------";

            cout << "\n\n\t\t\t\t\tEnter Updated Name: ";
            cin >> this->name;
        }

        if (i == 1)
        {
            system("cls");
            cout << "\n\n\n\n\t\t\t\t\tUPDATE EMPLOYEE RECORD FOR " << this->name;
            cout << "\n\t\t\t\t\t-------------------";

            cout << "\n\t\t\t\t\tEnter Updated Employee ID: ";
            cin >> this->emp_id;
            check_it = check_id(this->emp_id);

            if (check_it == false)
            {
                cout << "\n\t\t\t\t\tTHE EMPLOYEE ID SHOULD BE UNIQUE!!!!!";
                Sleep(1000);
                continue;
            }
        }

        cout << "\n\t\t\t\t\tEnter Updated Qualification: ";
        cin >> this->qualification;

        cout << "\n\t\t\t\t\tEnter Updated Address: ";
        cin >> this->address;

        cout << "\n\t\t\t\t\tEnter Updated E-mail ID: ";
        cin >> this->email;

        check_it = check_email(this->email);

        if (check_it == false)
        {
            cout << "\n\t\t\t\t\tTHE E-MAIL ID SHOULD HAVE AN '@' AND A '.' CHARACTER!!!!!";
            Sleep(1000);
            continue;
        }

        cout << "\n\t\t\t\t\tEnter Updated Contact number: ";
        cin >> this->contact;

        check_it = check_contact(this->contact);

        if (check_it == false)
        {
            cout << "\n\t\t\t\t\tTHE CONTACT NUMBER SHOULD HAVE ONLY 10 DIGITS!!!!!! ";
            Sleep(1000);
            continue;
        }

        cout << "\n\t\t\t\t\tEnter Updated Basic Salary: ";
        cin >> this->sal.basic_salary;

        check_it = check_salary(this->sal.basic_salary);

        if (check_it == false)
        {
            cout << "\n\t\t\t\t\tTHE SALARY SHOULD BE POSITIVE AND GREATER THAN 0 !!!!!! ";
            Sleep(1000);
            continue;
        }

    } while (check_it == false);

    system("cls");

    this->display_rec();
    cout << "\n\n\n\t\t\t\t\tARE YOU SURE YOU WANT TO UPDATE TO THIS RECORD? ";
    cin >> choice;
    if (choice == "NO" || choice == "no" || choice == "n" || choice == "N" || choice == "No")
    {
        cout << "\n\n\t\t\t\t\tRECORD NOT UPDATED!!!!";
        Sleep(1000);
        return false;
    }
    return true;
}

bool Employee::input_rec()
{
    bool check_it = false;

    system("cls");
    cout << "\n\n\n\n\t\t\t\t\tADD EMPLOYEE RECORD";
    cout << "\n\t\t\t\t\t-------------------";

    cout << "\n\n\t\t\t\t\tEnter Name: ";
    // cin.ignore();
    cin >> this->name;

    cout << "\n\t\t\t\t\tEnter Employee ID: ";
    // cin.ignore();
    cin >> this->emp_id;

    check_it = check_id(this->emp_id);

    if (check_it == false)
    {
        cout << "\n\t\t\t\t\tTHE EMPLOYEE ID SHOULD BE UNIQUE!!!!!";
        Sleep(1000);
        return false;
    }

    cout << "\n\t\t\t\t\tEnter Qualification: ";
    // cin.ignore();
    cin >> this->qualification;

    cout << "\n\t\t\t\t\tEnter Address: ";
    // cin.ignore();
    cin >> this->address;

    cout << "\n\t\t\t\t\tEnter E-mail ID: ";
    cin >> this->email;

    check_it = check_email(this->email);

    if (check_it == false)
    {
        cout << "\n\t\t\t\t\tTHE E-MAIL ID SHOULD HAVE AN '@' AND A '.' CHARACTER!!!!!";
        Sleep(1000);
        return false;
    }

    cout << "\n\t\t\t\t\tEnter contact number: ";
    cin >> this->contact;

    check_it = check_contact(this->contact);

    if (check_it == false)
    {
        cout << "\n\t\t\t\t\tTHE CONTACT NUMBER SHOULD HAVE ONLY 10 DIGITS!!!!!! ";
        Sleep(1000);
        return false;
    }

    cout << "\n\t\t\t\t\tEnter Basic Salary: ";
    cin >> this->sal.basic_salary;

    check_it = check_salary(this->sal.basic_salary);

    if (check_it == false)
    {
        cout << "\n\t\t\t\t\tTHE SALARY SHOULD BE POSITIVE AND GREATER THAN 0 !!!!!! ";
        Sleep(1000);
        return false;
    }

    return true;
}

void Employee::add_rec()
{
    bool f = false;
    string choice;

    do
    {
        f = this->input_rec();

        if (f == true)
            break;

        else
        {
            system("cls");
            cout << "\n\n\n\t\t\t\t\tDO YOU WANT TO ENTER AGAIN? ";

            cin >> choice;

            if (choice == "NO" || choice == "no" || choice == "n" || choice == "N" || choice == "No")
            {
                redirect("\n\n\n\n\n\n\n\n\t\t\t\t\tREDIRECTING TO ADMIN MENU");
                return;
            }
        }
    } while (1);

    system("cls");

    this->display_rec();
    cout << "\n\n\n\t\t\t\t\tARE YOU SURE YOU WANT TO ADD THIS RECORD? ";
    cin >> choice;
    if (choice == "NO" || choice == "no" || choice == "n" || choice == "N" || choice == "No")
    {
        cout << "\n\n\t\t\t\t\tRECORD NOT ADDED!!!!";
        Sleep(1000);
        return;
    }
    else
    {
        ofstream file;
        file.open("Employee_data.txt", ios::app);
        file << *this;
        file.close();

        cout << "\n\n\t\t\t\t\tRECORD ADDED SUCCESSFULLY!!!!";
        Sleep(500);
        return;
    }
}

void Employee::display_rec()
{
    this->calculate();
    cout << "\n\n\n\t\t\t\t\tEMPLOYEE DETAILS";
    cout << "\n\t\t\t\t\t-------------------------------------";
    cout << "\n\t\t\t\t\tEmployee ID: " << this->emp_id;
    cout << "\n\t\t\t\t\tName: " << this->name;
    cout << "\n\t\t\t\t\tQualification: " << this->qualification;
    cout << "\n\t\t\t\t\tAddress: " << this->address;
    cout << "\n\t\t\t\t\tE-Mail ID: " << this->email;
    cout << "\n\t\t\t\t\tContact Number: " << this->contact;
    cout << "\n\n\t\t\t\t\t------------------------";
    cout << "\n\t\t\t\t\tSALARY STRUCTURE";
    cout << "\n\t\t\t\t\t------------------------";
    cout << "\n\n\t\t\t\t\tBasic Pay: " << this->sal.basic_salary;
    cout << "\n\t\t\t\t\tDA: " << this->sal.DA;
    cout << "\n\t\t\t\t\tHRA: " << this->sal.HRA;
    cout << "\n\t\t\t\t\tPF: " << this->sal.PF;
    cout << "\n\t\t\t\t\tOther: " << this->sal.other;
    cout << "\n\t\t\t\t\tGross Salary: " << this->sal.basic_salary + this->sal.DA + this->sal.HRA;
    cout << "\n\t\t\t\t\tNet Salary: " << this->sal.basic_salary + this->sal.DA + this->sal.HRA - this->sal.PF - this->sal.other;
}

void Employee::display_all_rec()
{
    system("cls");
    cout << "\t\t\t\t\tDISPLAYING ALL RECORDS";
    cout << "\n\t\t\t\t\t-----------------------";
    ifstream file;
    file.open("Employee_data.txt");

    if (!file)
    {
        cout << "\n\n\t\t\t\t\tFILE IS NOT CREATED!!!!!";
        Sleep(1000);
        file.close();
        return;
    }

    file >> *this;
    while (!file.eof())
    {

        this->display_rec();
        file >> *this;
    }
    file.close();
    _getch();
}

void Employee::search_rec(bool i)
{
    system("cls");
    cout << "\n\n\n\n\t\t\t\t\tSEARCH EMPLOYEE RECORD";
    cout << "\n\t\t\t\t\t----------------------";

    ifstream file;
    file.open("Employee_data.txt");
    string search;
    bool found = false;

    if (!file)
    {
        cout << "\n\n\t\t\t\t\tNO RECORDS ARE PRESENT CURRENTLY!!!!";

        _getch();
        return;
    }

    else
    {
        if (i == 0)
        {
            cout << "\n\n\t\t\t\t\tENTER THE EMPLOYEE ID TO SEARCH FOR: ";
        }

        else if (i == 1)
        {
            cout << "\n\n\t\t\t\t\tENTER THE EMPLOYEE NAME TO SEARCH FOR: ";
        }

        cin >> search;

        file >> *this;
        while (!file.eof())
        {
            if (i == 0)
            {
                if (search == this->emp_id)
                    this->display_rec();
                found = true;
            }

            if (i == 1)
            {
                if (search == this->name)
                    this->display_rec();
                found = true;
            }

            file >> *this;
        }

        if (found == false && i == 1)
        {
            cout << "\n\n\t\t\t\t\tSORRY!!! NO SUCH EMPLOYEE NAME WAS FOUND ";
        }

        else if (found == false && i == 0)
        {
            cout << "\n\n\t\t\t\t\tSORRY!!! NO SUCH EMPLOYEE ID WAS FOUND ";
        }

        file.close();
        _getch();
        return;
    }
}

void Employee::remove_rec(bool i)
{
    system("cls");
    cout << "\n\n\n\n\t\t\t\t\tREMOVE EMPLOYEE RECORD";
    cout << "\n\t\t\t\t\t----------------------";

    ifstream file;
    file.open("Employee_data.txt");
    if (!file)
    {
        cout << "\n\n\t\t\t\t\tFILE IS NOT CREATED!!!!!";
        Sleep(1000);
        file.close();
        return;
    }

    string search;
    if (i == 0)
    {
        cout << "\n\n\t\t\t\t\tENTER THE EMPLOYEE ID TO DELETE: ";
    }

    if (i == 1)
    {
        cout << "\n\n\t\t\t\t\tENTER THE EMPLOYEE NAME TO DELETE: ";
    }
    cin >> search;

    ofstream temp("temp_file.txt");

    bool flag = false;

    file >> *this;
    while (!file.eof())
    {
        if (i == 0 && search != this->emp_id)
        {
            temp << *this;
        }

        if (i == 0 && search == this->emp_id)
        {
            flag = true;
        }

        if (i == 1 && search != this->name)
        {
            temp << *this;
        }

        if (i == 1 && search == this->name)
        {
            flag = true;
        }
        file >> *this;
    }

    file.close();
    temp.close();

    if (flag == false && i == 0)
    {
        cout << "\n\n\t\t\t\t\tNO SUCH EMPLOYEE ID WAS FOUND!!!!";
        (void)_getch();
        return;
    }

    else if (flag == false && i == 1)
    {
        cout << "\n\n\t\t\t\t\tNO SUCH EMPLOYEE NAME WAS FOUND!!!!";
        (void)_getch();
        return;
    }

    else
    {
        ofstream file1("Employee_data.txt");
        ifstream temp1("temp_file.txt");

        temp1 >> *this;
        while (!temp1.eof())
        {
            file1 << *this;
            temp1 >> *this;
        }
        file1.close();
        temp1.close();
        cout << "\n\n\t\t\t\t\tRECORD DELETED SUCCESSFULLY!!!!!";
        Sleep(500);
        return;
    }
}

void Employee::update_rec(bool i)
{
    system("cls");
    cout << "\n\n\n\n\t\t\t\t\tUPDATE EMPLOYEE RECORD";
    cout << "\n\t\t\t\t\t----------------------";

    ifstream file;
    file.open("Employee_data.txt");
    if (!file)
    {
        cout << "\n\n\t\t\t\t\tFILE IS NOT CREATED!!!!!";
        Sleep(1000);
        file.close();
        return;
    }

    bool to_update;
    string search;
    if (i == 0)
    {
        cout << "\n\n\t\t\t\t\tENTER THE EMPLOYEE ID TO BE UPDATED: ";
    }

    if (i == 1)
    {
        cout << "\n\n\t\t\t\t\tENTER THE EMPLOYEE NAME TO BE UPDATED: ";
    }
    cin >> search;

    ofstream temp("temp_file.txt");

    bool flag = false;

    file >> *this;

    while (!file.eof())
    {

        if (i == 0 && search != this->emp_id)
        {
            temp << *this;
        }

        if (i == 0 && search == this->emp_id)
        {

            flag = true;

            to_update = this->update(0);

            if (to_update == true)
                temp << *this;

            else
            {
                file.close();
                temp.close();
                redirect("\n\n\n\n\n\n\n\n\t\t\t\t\tREDIRECTING TO UPDATE MENU");
                return;
            }
        }

        if (i == 1 && search != this->name)
        {
            temp << *this;
        }

        if (i == 1 && search == this->name)
        {
            flag = true;

            to_update = this->update(1);

            if (to_update == true)
                temp << *this;

            else
            {
                file.close();
                temp.close();

                system("cls");
                for (int j = 0; j < 3; j++)
                {
                    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\tREDIRECTING TO UPDATE MENU";
                    for (int k = 0; k < 6; k++)
                    {
                        cout << ".";
                        Sleep(100);
                    }
                    system("cls");
                }
                return;
            }
        }

        file >> *this;
    }
    file.close();
    temp.close();

    if (flag == false && i == 0)
    {
        cout << "\n\n\t\t\t\t\tNO SUCH EMPLOYEE ID WAS FOUND!!!!";
        (void)_getch();
        return;
    }

    else if (flag == false && i == 1)
    {
        cout << "\n\n\t\t\t\t\tNO SUCH EMPLOYEE NAME WAS FOUND!!!!";
        (void)_getch();
        return;
    }

    else
    {
        ofstream file1("Employee_data.txt");
        ifstream temp1("temp_file.txt");

        temp1 >> *this;
        while (!temp1.eof())
        {
            file1 << *this;
            temp1 >> *this;
        }
        file1.close();
        temp1.close();
        cout << "\n\n\t\t\t\t\tRECORD UPDATED SUCCESSFULLY!!!!!";
        Sleep(500);
        return;
    }
}

void Employee::disp_sort(int i, bool v_or_t)
{
    system("cls");
    cout << "\n\n\n\n\t\t\t\t\tDISPLAYING SORTED EMPLOYEE RECORD";
    cout << "\n\t\t\t\t\t-------------------------------";

    ifstream file;
    file.open("Employee_data.txt");
    if (!file)
    {
        cout << "\n\n\t\t\t\t\tFILE IS NOT CREATED!!!!!";
        Sleep(1000);
        file.close();
        return;
    }

    vector<Employee> arr;

    file >> *this;
    while (!file.eof())
    {
        arr.push_back(*this);
        file >> *this;
    }

    file.close();

    arr = bubble_sort(arr, i);

    if (v_or_t == 0)
    {
        for (auto elem : arr)
        {
            elem.display_rec();
        }
    }

    else
    {
        cout << "\n\n\n";
        cout << left << setw(17) << "NAME" << left << setw(15) << "EMPLOYEE ID" << left << setw(15) << "QUAL."
             << left << setw(20) << "ADDRESS" << left << setw(20) << "E-MAIL ID" << left << setw(15) << "CONTACT"
             << left << setw(13) << "BASIC SAL." << left << setw(6) << "DA" << left << setw(6) << "HRA"
             << left << setw(6) << "PF" << left << setw(6) << "OTHER" << left << setw(13) << "GROSS" << left << setw(8) << "NET"
             << "\n\n";

        for (auto elem : arr)
        {
            elem.calculate();

            cout << left << setw(17) << elem.name << left << setw(15) << elem.emp_id << left << setw(15) << elem.qualification
                 << left << setw(20) << elem.address << left << setw(20) << elem.email << left << setw(15) << elem.contact
                 << left << setw(13) << elem.sal.basic_salary << left << setw(6) << elem.sal.DA << left << setw(6) << elem.sal.HRA
                 << left << setw(6) << elem.sal.PF << left << setw(6) << elem.sal.other
                 << left << setw(13) << elem.sal.basic_salary + elem.sal.DA + elem.sal.HRA
                 << left << setw(8) << elem.sal.basic_salary + elem.sal.DA + elem.sal.HRA - elem.sal.PF - elem.sal.other << endl;
        }
    }

    (void)_getch();
}

void Employee::file_sort(int i)
{

    ifstream file;
    file.open("Employee_data.txt");
    if (!file)
    {
        cout << "\n\n\t\t\t\t\tFILE IS NOT CREATED!!!!!";
        Sleep(1000);
        file.close();
        return;
    }

    vector<Employee> arr;

    file >> *this;
    while (!file.eof())
    {
        arr.push_back(*this);
        file >> *this;
    }

    file.close();
    arr = bubble_sort(arr, i);

    ofstream file1("Employee_data.txt");
    for (int j = 0; j < arr.size(); j++)
    {
        file1 << arr[j];
    }
    file1.close();

    redirect("\n\n\n\n\n\n\n\n\t\t\t\t\tSORTING");
    cout << "\n\n\n\n\n\n\n\n\t\t\tSORTING COMPLETE!!!!";
    Sleep(500);
}

void Employee::display_table_rec()
{
    system("cls");
    cout << "\t\t\t\t\tDISPLAYING ALL RECORDS";
    cout << "\n\t\t\t\t\t-----------------------";
    ifstream file;
    file.open("Employee_data.txt");

    if (!file)
    {
        cout << "\n\n\t\t\t\t\tFILE IS NOT CREATED!!!!!";
        Sleep(1000);
        file.close();
        return;
    }

    cout << "\n\n\n";
    cout << left << setw(17) << "NAME" << left << setw(15) << "EMPLOYEE ID" << left << setw(15) << "QUAL."
         << left << setw(20) << "ADDRESS" << left << setw(20) << "E-MAIL ID" << left << setw(15) << "CONTACT"
         << left << setw(13) << "BASIC SAL." << left << setw(6) << "DA" << left << setw(6) << "HRA"
         << left << setw(6) << "PF" << left << setw(6) << "OTHER" << left << setw(13) << "GROSS" << left << setw(8) << "NET"
         << "\n\n";

    file >> *this;
    while (!file.eof())
    {
        this->calculate();

        cout << left << setw(17) << this->name << left << setw(15) << this->emp_id << left << setw(15) << this->qualification
             << left << setw(20) << this->address << left << setw(20) << this->email << left << setw(15) << this->contact
             << left << setw(13) << this->sal.basic_salary << left << setw(6) << this->sal.DA << left << setw(6) << this->sal.HRA
             << left << setw(6) << this->sal.PF << left << setw(6) << this->sal.other
             << left << setw(13) << this->sal.basic_salary + this->sal.DA + this->sal.HRA
             << left << setw(8) << this->sal.basic_salary + this->sal.DA + this->sal.HRA - this->sal.PF - this->sal.other << endl;

        file >> *this;
    }
    file.close();
    _getch();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------

vector<Employee> bubble_sort(vector<Employee> arr, int i)
{
    Employee temp;
    bool flag;

    for (int j = 0; j < arr.size(); j++)
    {
        flag = false;
        for (int k = 0; k < arr.size() - 1; k++)
        {
            if (i == 0 && arr[k].emp_id > arr[k + 1].emp_id)
            {
                temp = arr[k];
                arr[k] = arr[k + 1];
                arr[k + 1] = temp;
                flag = true;
            }

            if (i == 1 && arr[k].name > arr[k + 1].name)
            {
                temp = arr[k];
                arr[k] = arr[k + 1];
                arr[k + 1] = temp;
                flag = true;
            }

            if (i == 2 && arr[k].sal.basic_salary > arr[k + 1].sal.basic_salary)
            {
                temp = arr[k];
                arr[k] = arr[k + 1];
                arr[k + 1] = temp;
                flag = true;
            }
        }

        if (flag == false)
            break;
    }
    return arr;
}

void search(Employee emp, string call)
{
    int choice;
    string ch;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t=======SEARCH MENU=======";
        cout << "\n\t\t\t\t\t\t1.) SEARCH BY NAME";
        cout << "\n\t\t\t\t\t\t2.) SEARCH BY ID";
        cout << "\n\t\t\t\t\t\t3.) BACK";
        cout << "\n\n\t\t\t\t\t\tENTER YOUR CHOICE (index of task/integer) : ";
        cin >> ch;

        if (ch.length() == 1 && isdigit(ch[0]) == true)
        {
            choice = int(ch[0]) - int('0');
            switch (choice)
            {
            case 1:
                emp.search_rec(1);
                break;

            case 2:
                emp.search_rec(0);
                break;

            case 3:
                redirect("\n\n\n\n\n\n\n\n\t\t\t\t\tREDIRECTING TO " + call + " MENU");
                return;

            default:
                cout << "\n\n\t\t\t\t\t\tWRONG CHOICE!!!!";
                Sleep(1000);
            }
        }

        else
        {
            cout << "\n\n\t\t\t\t\t\tPLEASE ENTER AN INTEGER BETWEEN 1 TO 3!!!!";
            Sleep(1000);
        }

    } while (1);
}

void del(Employee emp)
{
    int choice;
    string ch;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t=======DELETE MENU=======";
        cout << "\n\t\t\t\t\t\t1.) DELETE BY NAME";
        cout << "\n\t\t\t\t\t\t2.) DELETE BY ID";
        cout << "\n\t\t\t\t\t\t3.) BACK";
        cout << "\n\n\t\t\t\t\t\tENTER YOUR CHOICE (index of task/integer) : ";
        cin >> ch;

        if (ch.length() == 1 && isdigit(ch[0]) == true)
        {
            choice = int(ch[0]) - int('0');
            switch (choice)
            {
            case 1:
                emp.remove_rec(1);
                break;

            case 2:
                emp.remove_rec(0);
                break;

            case 3:
                redirect("\n\n\n\n\n\n\n\n\t\t\t\t\tREDIRECTING TO ADMIN MENU");
                return;

            default:
                cout << "\n\n\t\t\t\t\t\tWRONG CHOICE!!!!";
                Sleep(1000);
            }
        }

        else
        {
            cout << "\n\n\t\t\t\t\t\tPLEASE ENTER AN INTEGER BETWEEN 1 TO 3!!!!";
            Sleep(1000);
        }

    } while (1);
}

void update(Employee emp)
{
    int choice;
    string ch;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t=======UPDATE MENU=======";
        cout << "\n\t\t\t\t\t\t1.) UPDATE BY NAME";
        cout << "\n\t\t\t\t\t\t2.) UPDATE BY ID";
        cout << "\n\t\t\t\t\t\t3.) BACK";
        cout << "\n\n\t\t\t\t\t\tENTER YOUR CHOICE (index of task/integer) : ";
        cin >> ch;

        if (ch.length() == 1 && isdigit(ch[0]) == true)
        {
            choice = int(ch[0]) - int('0');
            switch (choice)
            {
            case 1:
                emp.update_rec(1);
                break;

            case 2:
                emp.update_rec(0);
                break;

            case 3:
                redirect("\n\n\n\n\n\n\n\n\t\t\t\t\tREDIRECTING TO ADMIN MENU");
                return;

            default:
                cout << "\n\n\t\t\t\t\t\tWRONG CHOICE!!!!";
                Sleep(1000);
            }
        }
        else
        {
            cout << "\n\n\t\t\t\t\t\tPLEASE ENTER AN INTEGER BETWEEN 1 TO 3!!!!";
            Sleep(1000);
        }

    } while (1);
}

void display_sorted(Employee emp, string call)
{
    int choice;
    string ch;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t=======DISPLAY SORTED MENU=======";
        cout << "\n\t\t\t\t\t\t1.) DISPLAY SORTED BY NAME IN VERTICAL FORMAT";
        cout << "\n\t\t\t\t\t\t2.) DISPLAY SORTED BY NAME IN TABULAR FORMAT";
        cout << "\n\t\t\t\t\t\t3.) DISPLAY SORTED BY ID IN VERTICAL FORMAT";
        cout << "\n\t\t\t\t\t\t4.) DISPLAY SORTED BY ID IN TABULAR FORMAT";
        cout << "\n\t\t\t\t\t\t5.) DISPLAY SORTED BY SALARY IN VERTICAL FORMAT";
        cout << "\n\t\t\t\t\t\t6.) DISPLAY SORTED BY SALARY IN TABULAR FORMAT";
        cout << "\n\t\t\t\t\t\t7.) BACK";
        cout << "\n\n\t\t\t\t\t\tENTER YOUR CHOICE (index of task/integer) : ";
        cin >> ch;

        if (ch.length() == 1 && isdigit(ch[0]) == true)
        {
            choice = int(ch[0]) - int('0');
            switch (choice)
            {
            case 1:
                emp.disp_sort(1, 0);
                break;

            case 2:
                emp.disp_sort(1, 1);
                break;

            case 3:
                emp.disp_sort(0, 0);
                break;

            case 4:
                emp.disp_sort(0, 1);
                break;

            case 5:
                emp.disp_sort(2, 0);
                break;

            case 6:
                emp.disp_sort(2, 1);
                break;

            case 7:
                redirect("\n\n\n\n\n\n\n\n\t\t\t\t\tREDIRECTING TO " + call + " MENU");
                return;

            default:
                cout << "\n\n\t\t\t\t\t\tWRONG CHOICE!!!!";
                Sleep(1000);
            }
        }

        else
        {
            cout << "\n\n\t\t\t\t\t\tPLEASE ENTER AN INTEGER BETWEEN 1 TO 7!!!!";
            Sleep(1000);
        }

    } while (1);
}

void sort_in_file(Employee emp)
{
    int choice;
    string ch;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t=======DISPLAY SORTED MENU=======";
        cout << "\n\t\t\t\t\t\t1.) SORT IN FILE BY NAME";
        cout << "\n\t\t\t\t\t\t2.) SORT IN FILE BY ID";
        cout << "\n\t\t\t\t\t\t3.) SORT IN FILE BY SALARY";
        cout << "\n\t\t\t\t\t\t4.) BACK";
        cout << "\n\n\t\t\t\t\t\tENTER YOUR CHOICE (index of task/integer) : ";
        cin >> ch;

        if (ch.length() == 1 && isdigit(ch[0]) == true)
        {
            choice = int(ch[0]) - int('0');
            switch (choice)
            {
            case 1:
                emp.file_sort(1);
                break;

            case 2:
                emp.file_sort(0);
                break;

            case 3:
                emp.file_sort(2);
                break;

            case 4:
                redirect("\n\n\n\n\n\n\n\n\t\t\t\t\tREDIRECTING TO ADMIN MENU");
                return;

            default:
                cout << "\n\n\t\t\t\t\t\tWRONG CHOICE!!!!";
                Sleep(1000);
            }
        }

        else
        {
            cout << "\n\n\t\t\t\t\t\tPLEASE ENTER AN INTEGER BETWEEN 1 TO 4!!!!";
            Sleep(1000);
        }

    } while (1);
}

bool password()
{
    system("cls");

    string username = "MITWPU.IN";
    string password = "MITWPU";
    string ent_username;
    string enter_password;

    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t**********LOGIN**********";
    cout << "\n\n\t\t\t\t\tUSERNAME: ";
    cin >> ent_username;

    char ch;
    size_t i;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t**********LOGIN**********";
        cout << "\n\n\t\t\t\t\tUSERNAME: " << ent_username;
        cout << "\n\n\t\t\t\t\tENTER PASSWORD: ";
        for (i = 0; i < enter_password.length(); i++)
        {
            cout << "*";
        }

        ch = _getch();

        if (int(ch) == 13) // ASCII value for enter key
            break;

        else
            enter_password.append(1, ch);

    } while (1);
    system("cls");
    if (username == ent_username && password == enter_password)
        return true;
    else
        return false;
}

void vdisplay_all_rec(Employee emp, string call)
{
    int choice;
    string ch;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t=======DISPLAY MENU=======";
        cout << "\n\t\t\t\t\t\t1.) DISPLAY RECORDS IN LINEAR FORMAT";
        cout << "\n\t\t\t\t\t\t2.) DISPLAY RECORDS IN TABULAR FORMAT";
        cout << "\n\t\t\t\t\t\t3.) BACK";
        cout << "\n\n\t\t\t\t\t\tENTER YOUR CHOICE (index of task/integer) : ";
        cin >> ch;

        if (ch.length() == 1 && isdigit(ch[0]) == true)
        {
            choice = int(ch[0]) - int('0');
            switch (choice)
            {
            case 1:
                emp.display_all_rec();
                break;

            case 2:
                emp.display_table_rec();
                break;

            case 3:
                redirect("\n\n\n\n\n\n\n\n\t\t\t\t\tREDIRECTING TO " + call + " MENU");
                return;

            default:
                cout << "\n\n\t\t\t\t\t\tWRONG CHOICE!!!!";
                Sleep(1000);
            }
        }

        else
        {
            cout << "\n\n\t\t\t\t\t\tPLEASE ENTER AN INTEGER BETWEEN 1 TO 3!!!!";
            Sleep(1000);
        }

    } while (1);
}

void admin()
{
    system("cls");
    bool get = password();
    if (get == false)
    {
        redirect("\n\n\n\n\n\n\n\n\t\t\t\t\tWRONG DETAILS!!!!!\n\t\t\t\t\tREDIRECTING TO MAIN MENU");
        return;
    }

    else
    {
        redirect("\n\n\n\n\n\n\n\n\t\t\t\t\tCORRECT DETAILS!!!!!\n\t\t\t\t\tREDIRECTING TO ADMIN MENU");
    }

    int choice;
    string ch;
    string c;
    bool flag = false;
    Employee emp;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t=======ADMIN MENU=======";
        cout << "\n\t\t\t\t\t\t1.) ADD RECORD";
        cout << "\n\t\t\t\t\t\t2.) ADD MULTIPLE RECORDS";
        cout << "\n\t\t\t\t\t\t3.) DISPLAY ALL RECORDS";
        cout << "\n\t\t\t\t\t\t4.) SEARCH RECORD";
        cout << "\n\t\t\t\t\t\t5.) DELETE RECORD";
        cout << "\n\t\t\t\t\t\t6.) UPDATE RECORD";
        cout << "\n\t\t\t\t\t\t7.) DISPLAY SORTED RECORDS";
        cout << "\n\t\t\t\t\t\t8.) SORT RECORDS IN FILE";
        cout << "\n\t\t\t\t\t\t9.) RETURN TO MAIN MENU";
        cout << "\n\n\t\t\t\t\t\tENTER YOUR CHOICE (index of task/integer) : ";
        cin >> ch;

        if (ch.length() == 1 && isdigit(ch[0]) == true)
        {
            choice = int(ch[0]) - int('0');
            switch (choice)
            {
            case 1:
                emp.add_rec();
                break;

            case 2:
                do
                {
                    emp.add_rec();
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\tDO YOU WANT TO ENTER MORE RECORDS ? ";
                    cin >> c;

                    if (c == "NO" || c == "no" || c == "0" || c == "n" || c == "N")
                        flag = true;
                } while (flag != true);
                break;

            case 3:
                vdisplay_all_rec(emp, string("ADMIN"));
                break;

            case 4:
                search(emp, string("ADMIN"));
                break;

            case 5:
                del(emp);
                break;

            case 6:
                update(emp);
                break;

            case 7:
                display_sorted(emp, string("ADMIN"));
                break;

            case 8:
                sort_in_file(emp);
                break;

            case 9:
                redirect("\n\n\n\n\n\n\n\n\t\t\t\t\tREDIRECTING TO MAIN MENU");
                return;

            default:
                cout << "\n\n\t\t\t\t\t\tWRONG CHOICE!!!!";
                Sleep(1000);
            }
        }

        else
        {
            cout << "\n\n\t\t\t\t\t\tPLEASE ENTER AN INTEGER BETWEEN 1 TO 9!!!!";
            Sleep(1000);
        }
    } while (1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void viewer()
{

    redirect("\n\n\n\n\n\n\n\n\n\t\t\t\t\tREDIRECTING TO VIEWER MENU");

    int choice;
    string ch;
    Employee emp;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t=======VIEWER MENU=======";
        cout << "\n\t\t\t\t\t\t1.) DISPLAY ALL RECORDS";
        cout << "\n\t\t\t\t\t\t2.) SEARCH RECORD";
        cout << "\n\t\t\t\t\t\t3.) DISPLAY SORTED RECORDS";
        cout << "\n\t\t\t\t\t\t4.) RETURN TO MAIN MENU";
        cout << "\n\n\t\t\t\t\t\tENTER YOUR CHOICE (index of task/integer) : ";
        cin >> ch;

        if (ch.length() == 1 && isdigit(ch[0]) == true)
        {
            choice = int(ch[0]) - int('0');
            switch (choice)
            {
            case 1:
                vdisplay_all_rec(emp, string("VIEWER"));
                break;

            case 2:
                search(emp, string("VIEWER"));
                break;

            case 3:
                display_sorted(emp, string("VIEWER"));
                break;

            case 4:
                redirect("\n\n\n\n\n\n\n\n\n\t\t\t\t\tREDIRECTING TO MAIN MENU");
                return;

            default:
                cout << "\n\n\t\t\t\t\t\tWRONG CHOICE!!!!";
                Sleep(1000);
            }
        }

        else
        {
            cout << "\n\n\t\t\t\t\t\tPLEASE ENTER AN INTEGER BETWEEN 1 TO 4!!!!";
        }

    } while (1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void start2()
{
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\t\t";
    for (int i = 0; i < 81; i++)
    {
        cout << "-";
        Sleep(10);
    }

    for (int i = 0; i < 9; i++)
    {
        cout << "\n\t\t|";

        if (i == 2)
        {
            cout << "\t\t       SUBMITTED BY:-\t\t\t\t\t\t|";
            Sleep(100);
        }

        else if (i == 3)
        {
            cout << "\t\t       PE07\t DEVANSHU MEHTA\t\t\t\t\t|";
            Sleep(100);
        }

        else if (i == 4)
        {
            cout << "\t\t       PE14\t HUSSAIN RANGWALA\t\t\t\t|";
            Sleep(100);
        }

        else if (i == 5)
        {
            cout << "\t\t       PE16\t KEVAL PAMBHAR\t\t\t\t\t|";
            Sleep(100);
        }

        else if (i == 6)
        {
            cout << "\t\t       PE35\t VIREN KADAM\t\t\t\t\t|";
            Sleep(100);
        }

        else
        {
            for (int j = 0; j < 10; j++)
            {
                cout << "\t";
            }

            // cout << "        ";
            cout << "|";
            Sleep(100);
        }
    }
    cout << "\n\t\t";
    for (int i = 0; i < 81; i++)
    {
        cout << "-";
        Sleep(10);
    }
    Sleep(500);
    exit(0);
}

void start1()
{
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\t\t";
    for (int i = 0; i < 81; i++)
    {
        cout << "-";
        Sleep(10);
    }

    for (int i = 0; i < 5; i++)
    {
        cout << "\n\t\t|";

        if (i == 2)
        {
            cout << "\t\t       WELCOME TO EMPLOYEE MANAGEMENT SYSTEM\t\t\t|";
            Sleep(100);
        }
        else
        {
            for (int j = 0; j < 10; j++)
            {
                cout << "\t";
            }

            // cout << "        ";
            cout << "|";
            Sleep(100);
        }
    }
    cout << "\n\t\t";
    for (int i = 0; i < 81; i++)
    {
        cout << "-";
        Sleep(10);
    }
    Sleep(500);
}

void exit_it()
{
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\t\t";
    for (int i = 0; i < 81; i++)
    {
        cout << "-";
        Sleep(10);
    }

    for (int i = 0; i < 5; i++)
    {
        cout << "\n\t\t|";

        if (i == 2)
        {
            cout << "\t\t\t  !!!!! THANKS FOR USING !!!!!    \t\t\t|";
            Sleep(100);
        }
        else
        {
            for (int j = 0; j < 10; j++)
            {
                cout << "\t";
            }

            // cout << "        ";
            cout << "|";
            Sleep(100);
        }
    }
    cout << "\n\t\t";
    for (int i = 0; i < 81; i++)
    {
        cout << "-";
        Sleep(10);
    }
    Sleep(500);
    start2();
}

int main()
{
    string choice;

    start1();

    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t=======MAIN MENU=======";
        cout << "\n\t\t\t\t\t\t1.) ADMIN";  // Change and Display
        cout << "\n\t\t\t\t\t\t2.) VIEWER"; // Display
        cout << "\n\t\t\t\t\t\t3.) EXIT";
        cout << "\n\n\t\t\t\t\t\tENTER YOUR CHOICE: ";
        cin >> choice;

        if (choice == "ADMIN" || choice == "admin" || choice == "1")
        {
            admin();
        }

        else if (choice == "VIEWER" || choice == "viewer" || choice == "2")
        {
            viewer();
        }

        else if (choice == "EXIT" || choice == "exit" || choice == "3")
        {
            exit_it();
        }

        else
        {
            cout << "WRONG CHOICE!!!!";
        }

    } while (1);

    return 0;
}
