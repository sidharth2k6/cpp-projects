#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Student{
private:
    string name;

public:
    void input(){
        // cin.ignore();
        cout << "enter name: ";
        getline(cin, this->name);
    }

    void output(){
        cout << "name: " << this->name << endl;
    }
};

int main(){

    vector<Student> students;

    int choice = 1, i = 0;
    while(choice){
        Student s;
        s.input();

        students.push_back(s);

        cout << "press 1 for new student, 0 for exit.";
        cin >> choice;
        getchar();
    }

    cout << "\nStudents: " << endl;
    for(Student data : students){
        data.output();
    }
    return 0;
}