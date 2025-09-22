#include<iostream>
#include<string>
#include<conio.h>
using namespace std;

#define BOX 20;

class Slider{
public:
    int x, y;
    int dir;
    int width, height;

    void reset(){
        width = height = BOX;
        x = width / 2;
        y = height - 3;
    }
};

class Game{
public:
    Slider slider;

    Game(){
        slider.reset();
    }

    void draw(){
        cout << "\033[H";

        for(int i = 0; i < slider.height; i++){
            for(int j = 0; j < slider.width; j++){
                if(i == slider.y && j == slider.x) cout << "__";
                else cout << "  ";
            }
            cout << endl;
        }
    }
    
    void input(){
        if(_kbhit()){
            switch(tolower(_getch())){
                case 'a':
                    if(!(slider.x < 1)) slider.x += -1;
                    break;
                case 'd':
                    if(!(slider.x > slider.width - 2)) slider.x += 1;
                    break;
                case 'x':
                    exit(0);
            }
        }
    }
};

int main(){
    Game g;
    while(1){
        g.draw();
        g.input();
    }
    return 0;
}