#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
using namespace std;

int width = 20;
int height = 20;
int x = width/2, y = height/2;
bool gameover = false;
int *playermove = &x;
int dir = 1;

void draw(){
    system("cls");
    for(int i = 0; i < width; i++){
        cout << " #";
        fflush(stdout);
    }
    cout << "\n";
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(j == 0 || j == width - 1){
                cout << " #";
                fflush(stdout);
                continue;
            }
            if(i == y && j == x){
                cout << " O";
                fflush(stdout);
            }
            else{
                cout << "  ";
                fflush(stdout);
            }
        }
        cout << "\n";
    }
    for(int i = 0; i < width; i++){
        cout << " #";
        fflush(stdout);
    }
}

void input(){
    if(_kbhit()){
        switch(_getch()){
            case 'a':
                playermove = &x;
                dir = -1;
                // x -= 1;
                break;
            case 's':
                playermove = &y;
                dir = 1;
                // y += 1;
                break;
            case 'd':
                playermove = &x;
                dir = 1;
                // x += 1;
                break;
            case 'w':
                playermove = &y;
                dir = -1;
                // y -= 1;
                break;
            case 'x':
                gameover = true;
                break;
        }
    }
    else{
        *playermove += dir;
    }
}

int main(){
    cout << "\033[?25l";
    while(!gameover){
        draw();
        input();
        Sleep(100);
    }
    return 0;
}