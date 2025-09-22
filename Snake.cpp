#include<iostream>
#include<conio.h>   //_getch(), _kbhit()
#include<windows.h> //Sleep()
#include<time.h>    //time()
using namespace std;

#define BOX 20

bool gameover = false;

//snake and food
int x = 0, y = 0;
int foodX, foodY;

//input and move
char head = '>';
int *playermove = &x;
int dir = 1;

//box
int width = BOX, height = BOX;


//tail
int prevX, prevY, ntail = 0;
int tailX[BOX * 5], tailY[BOX * 5];

int speedDelay = 150;
int score = 0;


void setup();
void draw();
void input();
void generateFood();
void logic();


int main(){
    srand(time(NULL));
    cout << "\033[?25l";

    setup();
    _getch();
    while(!gameover){
        //speedDelay code done in logic function under food collision section

        // if(ntail >= 5 && ntail < 10) speedDelay = 150;
        // else if(ntail >= 10 && ntail < 20) speedDelay = 100;
        // else if(ntail >= 20) speedDelay = 50;

        draw();
        input();
        logic();
        Sleep(speedDelay);
    }
    cout << "\n ------------ G A M E   O V E R ------------" << endl;
    _getch();
    return 0;
}

//---------------------F U N C T I O N   D E F I N I T I O N-----------------------------
void setup() {
    string msg1  = "T A P   A N Y   K E Y   T O   P L A Y";
    string msg2  = " Rules: ";
    string msg3  = "> Snake starts from beginning";
    string msg4  = "> Speed increases with points";
    string msg5  = "> Wall & body collision means GAMEOVER";
    string msg6  = "Controls: ";
    string msg7  = "> 'w' for UP.";
    string msg8  = "> 's' for DOWN.";
    string msg9  = "> 'a' for LEFT.";
    string msg10 = "> 'd' for RIGHT.";

    // get random location for food
    foodX = rand() % width;
    foodY = rand() % height;

    system("cls");
    cout << "\033[2m";

    // upper border
    for (int i = 0; i < width + 2; i++) cout << " #";
    cout << "\n";

    // inside (main area)       this code write with help of chat gpt
    for (int i = 0; i < height; i++) {
        int k = 0; // msg character index

        for (int j = 0; j < width + 2; j++) {
            if (j == 0 || j == width + 1) {
                cout << " #"; // left/right border
            }
            else {      //this logic is from chat gpt
                // choose message depending on row
                string msg = "";
                if (i == 3)  msg = msg1;
                if (i == 7)  msg = msg2;
                if (i == 8)  msg = msg3;
                if (i == 9)  msg = msg4;
                if (i == 10)  msg = msg5;
                if (i == 13) msg = msg6;
                if (i == 14) msg = msg7;
                if (i == 15) msg = msg8;
                if (i == 16) msg = msg9;
                if (i == 17) msg = msg10;

                // print characters from msg if this row has text
                if (!msg.empty() && j > 1 && k < msg.size()) {
                    cout << msg[k++];                       // first char
                    if (k < msg.size()) cout << msg[k++];   // second char if available
                    else cout << " ";                       // padding if odd length
                }
                else {
                    cout << "  "; // blank cell
                }
            }
        }
        cout << "\n";
    }

    // bottom border
    for (int i = 0; i < width + 2; i++) cout << " #";

    cout << "\033[0m";
}

void draw(){
    cout << "\033[H";
    //this function update inside the box content
    for(int i = 0; i < height; i++){
        cout << "\033[1E" << "\033[2C";

        for(int j = 0; j < width; j++){
            //head
            if(i == y && j == x){
                cout << "\033[1;31m" << " " << head << "\033[0m";
                cout << flush;
            }
            //food
            else if(i == foodY && j == foodX) cout << "\033[1;32m" << " *" << "\033[0m";
            //tail
            else{
                bool print = false;
                for(int k = 0; k < ntail; k++){
                    if(i == tailY[k] && j == tailX[k]){
                        cout << " o";
                        print = true;
                    }
                }
                //blank
                if(!print){
                    cout << "  ";
                }
                cout << flush;
            }
        }
    }
    //outside the box
    cout << "\033[2E";
    cout << " Food eaten: " << ntail << "\t\t\t  Score: " << score;
}
void input(){
    if(_kbhit()){
        switch(_getch()){
            case 'a':
                head = '<';
                playermove = &x;
                dir = -1;
                // x -= 1;
                break;
            case 's':
                head = 'v';
                playermove = &y;
                dir = 1;
                // y += 1;
                break;
            case 'd':
                head = '>';
                playermove = &x;
                dir = 1;
                // x += 1;
                break;
            case 'w':
                head = '^';
                playermove = &y;
                dir = -1;
                // y -= 1;
                break;
            case ' ':
                _getch();
                break;
            case 'x':
                gameover = true;
                break;
        }
    }
}

void generateFood(){
    //it privent to spawn food to snake head/body
    bool valid = false;
    while(!valid){
        
        foodX = rand() % width;
        foodY = rand() % height;

        valid = true;

        if(foodX == x && foodY == y) valid = false;

        for(int i = 0; i < ntail; i++){
            if(foodX == tailX[i] && foodY == tailY[i]){
                valid = false;
                break;
            }
        }
    }
}

void logic(){
    // prevX = tailX[0], prevY = tailY[0];
    // tailX[0] = x;
    // tailY[0] = y;

    // for(int i = 1; i <= ntail; i++){
    //     int tempX = tailX[i], tempY = tailY[i];
    //     tailX[i] = prevX;
    //     tailY[i] = prevY;
    //     prevX = tempX;
    //     prevY = tempY;
    // }

    //tail logic for axis swaping
    for(int i = ntail; i > 0; i--){
        tailX[i] = tailX[i-1];
        tailY[i] = tailY[i-1];
    }
    tailX[0] = x;
    tailY[0] = y;

    //auto move
    *playermove += dir;

    //wall collision
    if(x < 0 || x >= width || y < 0 || y >= height) gameover = true;

    //body collision
    for(int i = 0; i < ntail; i++){
        if(x == tailX[i] && y == tailY[i]) gameover = true;
    }

    //food collision
    if(x == foodX && y == foodY){
        generateFood();

        //it is really very smooth
        if(ntail <= 20) speedDelay -= 4;

        score += 10;
        ntail++;
    }
}