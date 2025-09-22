#include<iostream>
#include<string>
using namespace std;

class ATM{
private:
    string AcHolder;
    double Balance;
    int pin;
public:
    ATM(string AcHolder, int pin, double Balance){
        this -> AcHolder = AcHolder;
        this -> Balance = Balance;
        this -> pin = pin;
    }

    int verifypin(int pin){
        return this -> pin == pin;
    }

    void Deposite(double Amount){
        if(Amount < 0){
            cout << "Invalid Amount!" << endl;
        }
        else{
            this -> Balance += Amount;
            cout << "Deposited " << Amount << " Successfully" << endl;
        }
    }

    void Widthraw(double Amount){
        if(Amount <= 0 || Amount > this -> Balance){
            cout << "Invalid Widthrawal Amount!" << endl;
        }
        else{
            this -> Balance -= Amount;
            cout << "Widthraw " << Amount << " Successfully" << endl;
        }
    }

    void CheckBalance(){
        cout << "Current Balance: " << this -> Balance << endl;
    }
};

int main(){
    ATM Myaccout("Sidharth chandra", 1234, 5000.0);

    int pin;
    cout << "Enter your Pin: ";
    cin >> pin;

    if(!Myaccout.verifypin(pin)){
        cout << "Worng Pin! Exiting..." << endl;
        return 0;
    }

    int choice;
    double amount;

    cout << "Welcome to City ATM" << endl;
    while(1){
        cout << "\n1. Check Balance" << endl;
        cout << "2. Deposite" << endl;
        cout << "3. Widthraw" << endl;
        cout << "4. Exit" << endl;
        cout << "\nEnter your Choice: ";
        cin >> choice;

        switch(choice){
            case 1: 
                Myaccout.CheckBalance();
                break;
            case 2:
                cout << "Enter amout to Deposite: ";
                cin >> amount;
                Myaccout.Deposite(amount);
                break;
            case 3:
                cout << "Enter amount to Widthraw: ";
                cin >> amount;
                Myaccout.Widthraw(amount);
                break;
            case 4:
                cout << "Thank you for using City ATM :) " << endl;
                exit(0);
            default:
                cout << "You entered wrong choice! " << endl;
        }
    }

    return 0;
}