// main.cpp

#include <string>
#include <iostream>
#include "provided.h"
//#include "Scaffold.cpp"
//#include "Player.cpp"
//#include "Game.cpp"
using namespace std;

int main()
{
//	string name;
//	cout << "What's your name?  ";
//	getline(cin, name);
//	HumanPlayer hp(name);
//	SmartPlayer sp("Computer");
//	Game g1(4, 3, 3, &hp, &sp);
//	g1.play();
//	cout << endl << "This time I'll go first." << endl;
//	Game g2(4, 3, 3, &sp, &hp);
//	g2.play();
    Scaffold test(2, 3);
    test.display();
    cout << "emtpy1 " << test.numberEmpty() << endl;
    test.makeMove(2, RED);
    test.makeMove(3, BLACK);
    test.makeMove(2, RED);
    test.makeMove(2, BLACK);
    test.makeMove(1, RED);
    cout << "empty2 " << test.numberEmpty() << endl;
    test.display();
    test.undoMove();
    test.display();
    test.undoMove();
    test.display();
    test.undoMove();
    test.display();
    cout << "empty3 " << test.numberEmpty() << endl;


}
