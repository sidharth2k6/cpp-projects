#include<iostream>
#include<string>
#include<time.h>
#include<windows.h>
#include<conio.h>
#include<vector>
using namespace std;

#define BOX 23

class Snake{
public:
    int x, y;
    char head;
    int *playermove;
    int dir;
    int ntail;
    vector<int> tailX, tailY;

    Snake(){
        reset();
    }

    void reset(){
        x = y = 0;
        ntail = 0;
        head = '>';
        dir = 1;
        playermove = &x;
        tailX.clear();
        tailY.clear();
    }

    void move(){
        int i;
        if(ntail > 0){
            for(i = ntail - 1; i > 0; i--){
                tailX[i] = tailX[i - 1];
                tailY[i] = tailY[i - 1];
            }
            tailX[0] = x;
            tailY[0] = y;
        }
        
        *playermove += dir;
    }

    bool colliedWithSelf(){
        int i;
        for(i = 0; i < ntail; i++){
            if(x == tailX[i] && y == tailY[i]) return true;
        }
        return false;
    }
    
    void grow(){
        ntail++;
        tailX.push_back(x);
        tailY.push_back(y);
    }
};

class Food{
public:
    int i;
    int x, y;
    int bonusX, bonusY;
    void generateFood(Snake &s){
        bool valid = false;
        while(!valid){
            x = rand() % BOX;
            y = rand() % BOX;
            valid = true;

            if(x == s.x && y == s.y) valid = false;
            for(i = 0; i < s.ntail; i++){
                if(x == s.tailX[i] && y == s.tailY[i]){
                    valid = false;
                    break;
                }
            }
        }
    }
    void generateBonusFood(Snake &s){
        bool valid = false;
        while(!valid){
            bonusX = rand() % BOX;
            bonusY = rand() % BOX;
            valid = true;

            if(bonusX == s.x && bonusY == s.y) valid = false;
            if(bonusX == x && bonusY == y) valid = false;
            for(i = 0; i < s.ntail; i++){
                if(bonusX == s.tailX[i] && bonusY == s.tailY[i]){
                    valid = false;
                    break;
                }
            }
        }
    }
};

class Game{
public:
    int width, height;
    int score, speeDelay;
    bool gameover;
    Snake snake;
    Food food;

    Game(){
        width = height = BOX;
        srand(time(NULL));
    }

    void setup(){
        snake.reset();
        food.generateFood(snake);
        score = 0;
        speeDelay = 150;
        gameover = false;
        // obtainHighscore();
    }

    // void obtainHighscore(){

    // }

    void draw(){    //this function update inside the box content
        cout << "\033[H"; //reset cursor position
        
        for(int i = 0; i < height; i++){
            cout << "\033[1E" << "\033[2C";

            for(int j = 0; j < width; j++){
                //head
                if(i == snake.y && j == snake.x){
                    cout << "\033[1;31m" << " " << snake.head << "\033[0m";
                    cout << flush;
                }
                //food
                else if(i == food.y && j == food.x) cout << "\033[1;32m" << " *" << "\033[0m";
                else if(i == food.bonusY && j == food.bonusX && snake.ntail % 11 == 10) cout << "\033[1;32m" << " B" << "\033[0m";
                //tail
                else{
                    bool print = false;
                    for(int k = 0; k < snake.ntail; k++){
                        if(i == snake.tailY[k] && j == snake.tailX[k]){
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
        cout << " Score: " << score << "    -----   -----   -----    " << "Length: " << snake.ntail + 1;
    }

    void boxprint(){
        system("cls");
        cout << "\033[?25l";
        cout << "\033[2m"; //dim colour

        // upper border
        for (int i = 0; i < width + 2; i++) cout << " #";
        cout << "\n";

        // inside (main area)
        for (int i = 0; i < height; i++) {
            int k = 0; // msg character index

            for (int j = 0; j < width + 2; j++) {
                if (j == 0 || j == width + 1 || i == 1) {
                    cout << " #"; // left/right border
                }
                else if(i == 16 || i == 18) cout << " -";
                else{
                    WelcomeMessage(i, j, k);
                }
            }
            cout << "\n";
        }

        // bottom border
        for (int i = 0; i < width + 2; i++) cout << " #";

        cout << "\033[0m";

        char ch;
        while(true){
            ch = _getch();
            if(ch == 's' || ch == 'S') {run(); break;}
            if(ch == 'x' || ch == 'X') exit(0);
        }
    }

    void WelcomeMessage(int &i, int &j, int &k){
        string msg1  = "          WELCOME TO SNAKE GAME";
        string msg2  = " Rules: ";
        string msg3  = " 1. Control snake with W A S D keys.";
        string msg4  = " 2. Eat * to grow and gain score.";
        string msg5  = " 3. Don't hit walls or yourself.";
        string msg6  = " 4. Press SPACE to Pause/Resume.";
        string msg7  = " 5. Press X anytime to Exit.";
        string msg8  = "   Press S to Start Game or X to Exit.";

        // choose message depending on row
        string msg = "";
        if (i == 0)  msg = msg1;
        if (i == 6)  msg = msg2;
        if (i == 7)  msg = msg3;
        if (i == 8)  msg = msg4;
        if (i == 9)  msg = msg5;
        if (i == 10)  msg = msg6;
        if (i == 11)  msg = msg7;
        if (i == 17)  msg = msg8;

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

    void gameOverScreen() {
        cout << "\n\033[31m                   GAME OVER! \n\033[0m";
        cout << " Final Score: " << score << "\n Final Length: " << snake.ntail + 1 << "\n";
        cout << "\n\033[34m Press R to Restart or X to Exit.\033[0m";

        // savescore();

        while(true) {
            char c = _getch();
            if(c == 'r' || c == 'R') { boxprint(); break; }
            if(c == 'x' || c == 'X') { break; }
        }
    }

    void pauseMessage(){
        cout << "\033[" << height + 5 << ";1H";
        cout << "\033[1;34m";
        cout << " ---- PAUSED ---- Press SPACE again to continue...";
        cout << "\033[0m";
    }

    void clearPauseMessage(){
        cout << "\033[" << height + 5 << ";1H";
        cout << "\033[2K";
    }

    void input(){
        if(_kbhit()){
            switch(tolower(_getch())){
                case 'a':{
                    if(snake.head != '>'){
                        snake.head = '<';
                        snake.playermove = &snake.x;
                        snake.dir = -1;
                    }
                    break;
                }
                case 's':{
                    if(snake.head != '^'){
                        snake.head = 'v';
                        snake.playermove = &snake.y;
                        snake.dir = 1;
                    }
                    break;
                }
                case 'd':{
                    if(snake.head != '<'){
                        snake.head = '>';
                        snake.playermove = &snake.x;
                        snake.dir = 1;
                    }
                    break;
                }
                case 'w':{
                    if(snake.head != 'v'){
                        snake.head = '^';
                        snake.playermove = &snake.y;
                        snake.dir = -1;
                    }
                    break;
                }
                case 'x': gameover = true; break;
                case ' ':{
                    pauseMessage();
                    while(true){
                        char ch = _getch();
                        if(ch == ' ') {clearPauseMessage(); break;}
                        if(ch == 'x' || ch == 'X') {gameover = true; break;}
                    }
                    break;
                }
            }
        }
    }

    void logic(){
        snake.move();

        //wall collision
        if(snake.x < 0 || snake.x >= width || snake.y < 0 || snake.y >= height) gameover = true;

        //body collision
        if(snake.colliedWithSelf()) gameover = true;

        //food collision
        if(snake.x == food.x && snake.y == food.y){
            food.generateFood(snake);
            snake.grow();
            score += 10;
            if(snake.ntail % 11 == 10) food.generateBonusFood(snake);
            if(speeDelay > 30) speeDelay -= 4;
        }
        if(snake.x == food.bonusX && snake.y == food.bonusY){
            snake.grow();
            score += 30;
        }
    }

    void run(){
        setup();
        while(!gameover){
            draw();
            input();
            logic();
            Sleep(speeDelay);
        }
        gameOverScreen();
    }
};

int main(){
    Game g;
    g.boxprint();
    return 0;
}