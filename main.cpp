#include <SFML/Graphics.hpp>

void menu();

int main(){
    system("chcp 1251 > Null");
    srand(time(0));

    menu();//вызов меню

    return 0;
}