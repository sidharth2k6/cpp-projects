#include<iostream>
using namespace std;

int main(){
    double total_salary;
    double ta, da, hra, net_salary, pf, cash_in_hand;

    cout << "Enter your Total salary: ";
    cin >> total_salary;

    ta = (total_salary * 10) / 100;
    da = (total_salary * 20) / 100;
    hra = (total_salary * 30) / 100;

    net_salary = total_salary + ta + da + hra;

    pf = (net_salary * 10) / 100;

    cash_in_hand = net_salary - pf;

    cout << "\nTotal salary = " << total_salary << endl;
    cout << "Net salary = " << net_salary << endl;
    cout << "Cash in hand = " << cash_in_hand << endl;

    return 0;
}