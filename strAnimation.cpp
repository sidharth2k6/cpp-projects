#include<iostream>
#include<windows.h>
using namespace std;

int main(){
    string s = "hello world";
    //97 for charactor "a"
    system("cls");
    int i, j, k;
    for (i = 0; i < s.length(); i++){
        
        for (j = 'a'; j < 'z'; j++){
            for(k = 0; k < i; k++){
                cout << s[k];
            }
            if(s[i] == (char)j){
                cout << s[i] << endl;
                break;
            }
            cout << (char)j << endl;
        }
    }
    return 0;
}