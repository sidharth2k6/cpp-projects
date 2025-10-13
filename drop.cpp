#include<iostream>
#include<string>
#include<conio.h>
#include<time.h>
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

class Food{
public:
    int x, y;

    void generatefood(){
        x = (rand() % 20) + 1;
    }


};

class Game{
public:
    Slider slider;
    Food food;

    Game(){
        slider.reset();
        srand(time(NULL));
    }

    void draw1(){
        // cout << "\033[H" << "\033[?25l";
        cout << "\033[H";

        for(int i = 0; i < slider.height; i++){
            cout << "\033[1E" << "\033[2C";
            for(int j = 0; j < slider.width; j++){
                // if(j == 0 || j == 19){
                //     cout << " |";
                // }
                if(i == slider.y && j == slider.x) cout << "__";
                else cout << "  ";
            }
            // cout << endl;
        }
    }
    void draw(){
        system("cls");
        // cout << "\033[?25l";
        cout << "\033[2m"; //dim colour

        // upper border
        for (int i = 0; i < slider.width + 2; i++) cout << "//";
        cout << endl;

        // inside (main area)
        for (int i = 0; i < slider.height; i++) {

            for (int j = 0; j < slider.width + 2; j++) {
                if (j == 0 || j == slider.width + 1 ) {
                    cout << "//"; // left/right border
                }
                else cout << "  ";
            }
            cout << endl;
        }

        // bottom border
        for (int i = 0; i < slider.width + 2; i++) cout << "//";

        cout << "\033[0m";
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
    g.draw();
    while(1){
        g.draw1();
        // cout << "\033[H" << "\033[1E" << "\033[2C";
        // getchar();
        g.input();
    }
    return 0;
}