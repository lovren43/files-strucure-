// testingFiles.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <list>
#include <iterator>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>
#include "string.h"
#include <stdlib.h>
#include <map>
using namespace std;
class PINDX {
    map<int, int> pin;
public:
    int byteOffset;
    string id = "\0";
    string buff = "\0";
    string s = "\0";
    int x;
    void deleteFromIndx(int k) {
        loadYoMap();
        pin.erase(k);
        writeToP();
    }
    void unpack() {
        s.erase();
        id.erase();
        int i = 0;
        while (buff[i] != '|') id += buff[i++];
        i++;
        while (buff[i] != '$') s += buff[i++];
        istringstream(s) >> byteOffset;
        istringstream(id) >> x;
    }
    void loadYoMap() {
        fstream y("sortedEmpIndex.txt", ios::in);
        pin.clear();
        y.seekg(0, ios::beg); buff.erase();
        while (getline(y, buff)) {
            unpack();
            pin[x] = byteOffset;
            pin.erase(0);
        }
        y.close();
    }
    void writeToP() {
        fstream y;
        y.open("sortedEmpIndex.txt", ios::out | ios::ate);
        for (auto ele : pin) {
            y << ele.first << "|" << ele.second << "$\n";
        }
        y.close();
    }
    void sortP() {
        loadYoMap();
        writeToP();
    }
    int binarysearch(int k) {
        sortP();
        map<int, int>::iterator it;
        it = pin.find(k);

        if (it == pin.end()) {
            cout << "Key-value pair not present in map\n";
            return -1;
        }
        else
            cout << "Key-value pair present : " << it->first << "->" << it->second << endl;

        // pin.clear();
        return it->second;
    }
};

class Employee {
private:
    string employee_id = "\0";
    string dept_id = "\0";
    string employee_name = "\0";
    string employee_position = "\0";
    string buffer = "\0";
    string byteOffset = "\0";
    int place;
    int recSize;
public:
    void unpack();
    void pack();
    void read();
    void readFile();
    void writeFile();
    void print();
    void erasing();
    void del(int);
    void getRecord(int);
};

// take the details from user
void Employee::read() {
    PINDX pIN;
    cout << "***Enter The Employee Details***" << endl;
    cout << "Employee ID: ";
    getline(cin >> ws, employee_id);
    cout << "Employee Name: ";
    getline(cin >> ws, employee_name);
    cout << "Deptartement ID: ";
    getline(cin >> ws, dept_id);
    cout << "Employee Position: ";
    getline(cin >> ws, employee_position);
    pack();
    writeFile();
    pIN.sortP();
}

// sperate the fields with delimiter
void Employee::pack() {
    buffer.erase();
    buffer += employee_id + "|" + employee_name + "|" + dept_id + "|" + employee_position + "$\n";
}

// write buffer to the file 
void Employee::writeFile() {
    fstream f, p;
    PINDX pIN;
    f.open("empData.txt", ios::out | ios::app);
    p.open("sortedEmpIndex.txt", ios::out | ios::app);
    recSize = buffer.length();
    int start = f.tellg();
    f << buffer.length() << buffer;
    f.seekg(0, ios::end);
    int end = f.tellg();
    pIN.id = employee_id;
    pIN.byteOffset = (end - start) - (buffer.length() + 3);
    p << pIN.id << '|' << pIN.byteOffset << "$\n";
    pIN.sortP();
    f.clear();
    f.close();
    p.close();
}

// read the whole file
void Employee::readFile() {
    PINDX p;
    p.sortP();
    fstream f;
    erasing();
    f.open("empData.txt", ios::in);
    while (!f.eof())
    {
        buffer.erase();
        getline(f, buffer);
        unpack();
        if (!f.fail() && buffer[0] != '*')
        {
            cout << "\n=============\n";
            print();
            cout << "=============\n";
        }
    }
    f.clear();
    f.close();
}

void Employee::getRecord(int id) {
    fstream f;
    PINDX pIN;
    int pos;
    pos = pIN.binarysearch(id);
    if (pos + 1) {
        f.open("empData.txt", ios::in);
        f.clear();
        f.seekg(pos);
        erasing();
        getline(f, buffer);
        if (buffer[0] != '*')
        {
            unpack();
            print();
        }
        else cout << "Record isn't exist\n";
        f.close();
    }

}


// delete record
void Employee::del(int id) {
    fstream f;
    PINDX pIN;
    char delMark = '*', end;
    int pos;

    pos = pIN.binarysearch(id);
    if (pos + 1) {
        f.open("empData.txt", ios::in | ios::out);
        f.seekp(pos);
        f.put('*');
        f.close();
        pIN.deleteFromIndx(id);
    }
}


// erase all the strings
void Employee::erasing() {
    recSize = -1;
    employee_id.erase();
    employee_name.erase();
    employee_position.erase();
    dept_id.erase();
}

// remove delimiters 
void Employee::unpack() {
    int i = 0;
    erasing();
    while (buffer[i] != '|') employee_id += buffer[i++];
    i++;
    while (buffer[i] != '|') employee_name += buffer[i++];
    i++;
    while (buffer[i] != '|') dept_id += buffer[i++];
    i++;
    while (buffer[i] != '$') employee_position += buffer[i++];
    string s = employee_id.substr(0, 2);
    istringstream(s) >> recSize;
    employee_id = employee_id.substr(2);
}

void Employee::print() {
    cout << "Employee ID: " << employee_id << endl << "Employee Name: " << employee_name << endl
        << "Departement ID: " << dept_id << endl << "Position: " << employee_position << endl;
}
//////////////////////////////////////
/////////////////////////////////////
////////////////////////////////////
///////////////////////////////////

class Department {



public:
    struct SIndex
    {
        int byte;
        string name;
    };
    struct dept
    {
        string Dept_ID;  //primary key
        string Dept_Name; //secondary key
        string Dept_Manger;
    };
    struct PIndex
    {
        int byteoff;
        string ID;
    };
    int length[5];
    SIndex* SecondArray = new SIndex[5];
    dept d;
    int ByteOffset = 0;
    int countRec = 0;
    PIndex* PrmIndxArray = new PIndex[5];
    dept* departments = new dept[5];
    int counter[5];
    void add_Department()
    {

        fstream myfile;
        myfile.open("Department.txt", ios::out | ios::app);
        for (int i = 0; i < 5; i++)
        {

            int countRec = 0;
            cout << "Enter department ID: ";
            getline(cin, d.Dept_ID);
            countRec = countRec + d.Dept_ID.length() + 1;
            cout << "Enter department Name: ";
            getline(cin,d.Dept_Name);
            countRec = countRec + d.Dept_Name.length() + 1;
            cout << "Enter department Manager: ";
            getline(cin,d.Dept_Manger);
            countRec = countRec + d.Dept_Manger.length() + 4;
            myfile << countRec << "," << d.Dept_ID << "|" << d.Dept_Name << "|" << d.Dept_Manger << "#";
            counter[i] = countRec;
            departments[i] = d;
            ByteOffset = countRec - ByteOffset;
            PrmIndxArray[i].ID = d.Dept_ID;
            if (ByteOffset == countRec)
            {
                PrmIndxArray[i].byteoff = 00;
            }
            else
                PrmIndxArray[i].byteoff = counter[i - 1] + 1;


        }
        myfile.close();

        quickSort(PrmIndxArray, 0, 4);



    }

    void writePrimIndex()
    {
        fstream myfile;
        myfile.open("primaryIndex.txt", ios::out | ios::app);
        for (int i = 0; i < 5; i++) {
            myfile << PrmIndxArray[i].ID << "|" << PrmIndxArray[i].byteoff << "#";
        }

        myfile.close();
    }
    void readPrimaryIndex() {
        fstream primaryIndex;
        primaryIndex.open("primaryIndex.txt", ios::in);
        string word;
        char c;
        bool falg = 0;
        int counter = 0;
        int byteOf;
        while (true) {
            if (primaryIndex.fail()) {
                break;
            }
            primaryIndex >> c;
            if (c == '|') {
                PrmIndxArray[counter].ID = word;
                word = "";
            }
            else if (c == '#') {
                stringstream s(word);
                s >> byteOf;
                PrmIndxArray[counter].byteoff = byteOf;
                word = "";
                counter++;
            }
            else {
                word += c;
            }

        }
    }

    void quickSort(PIndex PrmIndxArray[], int left, int right)
    {
        int i = left, j = right;
        PIndex tmp;
        string pivot = PrmIndxArray[(left + right) / 2].ID;
        while (i <= j) {
            while (PrmIndxArray[i].ID < pivot)
                i++;
            while (PrmIndxArray[j].ID > pivot)
                j--;
            if (i <= j) {
                tmp = PrmIndxArray[i];
                PrmIndxArray[i] = PrmIndxArray[j];
                PrmIndxArray[j] = tmp;
                i++;
                j--;
            }
        }
        if (left < j)
            quickSort(PrmIndxArray, left, j);
        if (i < right)
            quickSort(PrmIndxArray, i, right);
    }

    void writeSecondaryIndex()
    {
        fstream myfile;
        myfile.open("SecondaryIndex.txt", ios::out | ios::app);
        myfile << d.Dept_Name << "|" << d.Dept_ID << endl;
        myfile.close();
    }
    void deleteDepartment()
    {
        string id;
        fstream myfile;
        myfile.open("Department.txt", ios::out | ios::in);
        cout << "Enter The ID u want to delete : ";
        cin >> id;
        for (int i = 0; i < 5; i++) {
            if (PrmIndxArray[i].ID == id)
            {
                myfile.seekp(PrmIndxArray[i + 1].byteoff, ios::beg);
                myfile.write("*", 2);
            }
        }
        myfile.close();

    }
    int SearchDepartment(PIndex PrmIndxArray[], int l, int r, string id)
    {

        fstream myfile;
        myfile.open("Department.txt", ios::out | ios::app);

        getline(cin, id);
        int mid = l + (r - l) / 2;
        if ((PrmIndxArray[mid]).ID == id)
        {
            return PrmIndxArray[mid].byteoff;

        }
        else if ((PrmIndxArray[mid]).ID < id)
        {
            SearchDepartment(PrmIndxArray, mid + 1, r, id);
        }
        else if ((PrmIndxArray[mid]).ID > id)
        {
            SearchDepartment(PrmIndxArray, l, mid - 1, id);
        }
        else
            return -1;

    }
    int SearchSeconderyIndex()
    {
        fstream file;
        file.open("SecondaryIndex.txt", ios::out | ios::app);
        file.seekg(0, ios::beg);
        if (file.tellg() == 0) {
            return -1;
        }
    }
    void writeLinkedList()
    {
        fstream file;
       
        bool flag = false;
        file.open("linkedList.txt", ios::out | ios::app);
        for (int i = 0; i < 5; ++i) {
           
            for (int j = 1; j < 5; ++j) {
                if (departments[i].Dept_Name == departments[j].Dept_Name)
                {
                    length[j] = PrmIndxArray[i].ID.length() + 5;
                    file << PrmIndxArray[j].ID << "|" << PrmIndxArray[j].byteoff << "|" << length << '#';
                    flag = true;
                }
              
            }
            if (flag == false) {
                file << PrmIndxArray[i].ID << "|" << PrmIndxArray[i].byteoff << "|" << -1 << '#';

            }
        }


    }
    void writeSecondry()
    {
        fstream file;
        file.open("SecondaryIndex.txt", ios::out | ios::app);
        for (int i = 0; i < 5; ++i) {
            file << SecondArray[i].name << "|" << length[i];
        }

    }

};
string* splitQuery(string query) {
    string *splitedQuery=new string[8];
    string word = "";
    int counter = 0;
    for (auto x : query)
    {
        if (x == ' ')
        {
            splitedQuery[counter]=word;
            counter++;
            word = "";
        }
        else {
            word = word + x;
        }
    }
    splitedQuery[counter]=word;
    return splitedQuery;
}
string getSearchValue(string searchValue) {
    string value = "";
    for (auto i : searchValue) {
        if (i == '\'') {
            continue;
        }
        else {
            value += i;
        }
    }
    return value;
}
string* getDeptResult(int byteOf) {
    fstream deptDataF;
    deptDataF.open("Department.txt", ios::in);
    string* result = new string[3];
    deptDataF.seekg(byteOf);
    char c;
    int counter = 0;
    string word;
    while (true) {
        deptDataF >> c;
        if (c == '#') {
            break;
        }
        else if (c == ',') {
            word = "";
        }
        else if (c == '|') {
            result[counter] = word;
            counter++;
            word = "";
        }
        else {
            word += c;
        }
    }
    return result;
}
int main()
{
    Department department;
    Employee emp;
    int choice = 0;
    string schoice;
    //department.add_Department();
    //department.writeLinkedList();

    
    /*sIndex s1;
    s1.byteoff = 0;
    s1.Dept_Name = "is";
    list<PIndex>sec;
    list<sIndex>l;*/

    
    /*cout << "FDFd" << endl;
    string q;
    getline(cin, q);
    string* s = splitQuery(q);
    for (int i = 0; i < 6; i++) {
        cout << s[i] << endl;
    }*/
    while (true) {
        cout << "1- Add New Employee" << endl;
        cout << "2- Add New Department" << endl;
        cout << "3- Delete Emplyee (ID)" << endl;
        cout << "4- Delete Department (ID)" << endl;
        cout << "5- Print Employee (ID)" << endl;
        cout << "6- Print Employee (Dept_ID)" << endl;
        cout << "7- Print Department (ID)" << endl;
        cout << "8- Print Department (Name)" << endl;
        cout << "9- Write query" << endl;
        cout << "10- Exit" << endl;
        getline(cin, schoice);
        stringstream s(schoice);
        s >> choice;
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 1) {
            emp.read();
            continue;
        }
        if (choice == 2) {
            //cout << "Please Enter Department ID, Name, Manager";
           // cin >> department.dept.Dept_ID >> department.dept.Dept_Name >> department.dept.Dept_Manger;
            department.add_Department();
            department.writePrimIndex();
            department.writeSecondaryIndex();
            department.writeLinkedList();
            continue;
        }
        if (choice == 3) {
            cout << "Enter the employee id" << endl;
            string sId;
            getline(cin, sId);
            int id;
            istringstream(sId) >> id;
            emp.del(id);
            continue;
        }
        if (choice == 4) {
            department.deleteDepartment();
                continue;
        }
        if (choice == 5) {
            cout << "Enter the employee id" << endl;
            string sId;
            getline(cin, sId);
            int id;
            istringstream(sId) >> id;
            emp.getRecord(id);
            continue;
        }
        if (choice == 6) {

        }
        if (choice == 7) {

        }
        if (choice == 8) {

        }
        if (choice == 9) {
            fstream empPrimaryF;
            fstream empDataF;
            fstream empSecondryF;
            fstream deptDataF;
            fstream deptPrimaryF;
            fstream deptSecondryF;
            deptDataF.open("Department.txt", ios::in);
            deptPrimaryF.open("primaryIndex.txt", ios::in);
            deptSecondryF.open("SecondaryIndex.txt", ios::in);
            string query;
            cout << "Please Enter The Query" << endl;
            getline(cin,query);
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string* splitedQuery = splitQuery(query);
            string searchValue = getSearchValue(splitedQuery[7]);
            if (splitedQuery[3] == "Department" && splitedQuery[5] == "Dept_ID") {
                Department d;
                d.writePrimIndex();
                int byteOF=d.SearchDepartment(d.PrmIndxArray,0,4,searchValue);
                string* result = getDeptResult(byteOF);
                if (splitedQuery[1] == "all" || splitedQuery[1] == "*") {
                    cout << result[0] << " " << result[1] << result[2] << endl;
                    continue;
                }
                else if (splitedQuery[1] == "Dept_Name") {
                    cout << result[1] << endl;
                    continue;
                }
                else if (splitedQuery[1] == "Dept_Manger") {
                    cout << result[2] << endl;
                    continue; 
                }
            }
            else if (splitedQuery[3] == "Department" && splitedQuery[5] == "Dept_Name") {
                
                if (splitedQuery[1] == "all" || splitedQuery[1] == "*") {
                      
                     
                }
                else if (splitedQuery[1] == "Dept_ID") {

                }
                else if (splitedQuery[1] == "Dept_Manger") {

                }
            }
            else if (splitedQuery[3] == "Employee" && splitedQuery[5] == "Employee_ID") {
                Employee emp;
                int intSearchValue;
                stringstream convert(searchValue);
                convert >> intSearchValue;
                emp.getRecord(intSearchValue);
                
            }
            else if (splitedQuery[3] == "Employee" && splitedQuery[5] == "Dept_ID") {
                if (splitedQuery[1] == "all" || splitedQuery[1] == "*") {

                }
                else if (splitedQuery[1] == "Employee_Name") {

                }
                else if (splitedQuery[1] == "Employee_Position") {

                }
                else if (splitedQuery[1] == "Employee_ID") {

                }
            }

            continue;


        }
        if (choice == 10) {
            break;
        }
        else {
            cout << "Error" << endl;
            break;
        }
    }

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
