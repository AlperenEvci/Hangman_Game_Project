#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <fstream>


using namespace std;

//Text Renklendirme 
void colorBinding() {
    srand(time(NULL));
    int colorIndex;
    colorIndex = rand() % 14 + 1;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorIndex);

}

//Koordinat seklinde yazdirma
void cursorMovement(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Animasyonlu cerceve
void gameBoxSleeped() { 
    colorBinding();
    int bar = 219;
    int bar2 = 178;
    for (int a = 0; a < 70; a++) {

        cursorMovement(a + 20, 0);
        cout << char(bar);
        Sleep(1);

    }
    for (int a = 0; a < 25; a++) {
        cursorMovement(90, a);
        cout << char(bar);
        Sleep(1);
    }
    for (int a = 0; a < 70; a++) {
        cursorMovement(90 - a, 25);
        cout << char(bar);
        Sleep(1);
    }
    for (int a = 0; a < 25; a++) {
        cursorMovement(20, 25 - a);
        cout << char(bar);
        Sleep(1);
    }
}

 //Animasyonsuz Cerceve
void gameBoxUnsleeped() {
    colorBinding();
    int bar = 219;
    for (int a = 0; a < 70; a++) {
        cursorMovement(a + 20, 0);
        cout << char(bar);
    }
    for (int a = 0; a < 25; a++) {
        cursorMovement(90, a);
        cout << char(bar);
    }
    for (int a = 0; a < 70; a++) {
        cursorMovement(90 - a, 25);
        cout << char(bar);
    }
    for (int a = 0; a < 25; a++) {
        cursorMovement(20, 25 - a);
        cout << char(bar);
    }
}

void newPage() {
    system("cls");

}

// Animasyonlu Text Yazdirma
void messageWiewer(string message) {
    gameBoxUnsleeped();
    for (int i = 0; i < size(message); i++) {
        cursorMovement(38 + i, 10);
        Sleep(1);
        cout << message[i];
    }
}

// Alternatif system(pause)
void contin() {
    char contin;
    cursorMovement(21, 24);
    cout << "Press Any Button...";
    contin = _getch();
}

void hideCursor()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Oyun Baslama Animasyonu
void gameLoading(void) {
    newPage();
    gameBoxUnsleeped();
    cursorMovement(32, 11);
    cout << "!!!!!Attention, this game has a save feauture.!!!!!";
    cursorMovement(34, 12);
    cout << "!!!!!Please press esc before exit the game.!!!!!";

    contin();

    
    char hangman[50][50] = { "   ______    ","   |    |    ","   |    O    ","   |   /|\\  ","   |   / \\  ","   |         ","   |         "," __|__       " };
    int j = 0;

    while (j < 1) {
        newPage();
        gameBoxUnsleeped();
        cursorMovement(48, 9);
        cout << "Game Starting !";
        for (int i = 0; i < 8; i++) {
            for (int k = 0; k < 14; k++) {
                cursorMovement(48 + k, 10 + i);
                cout << hangman[i][k];
                Sleep(20);
            }
            cout << endl;
            Sleep(10);
        }
        j++;
        cursorMovement(0, 26);
    }

}

struct Player {
    string name;
    int score;
};

//Puan Ekrani
void scoreBoard(int p1, string n1, int p2, string n2) {

    Player player1, player2;
    player1.score = p1;
    player2.score = p2;

    player1.name = n1;
    player2.name = n2;

    newPage();
    gameBoxUnsleeped();

    cursorMovement(75, 22);
    cout << player1.name << " : " << player1.score;

    cursorMovement(75, 23);
    cout << player2.name << " : " << player2.score;
}

//Kelimenin Gizlenmesi
void wordHider(string* word) {
    string flag, hidden;
    flag = *word;

    for (int i = 0; i < flag.length(); i++)
    {
        if (flag[i] >= 65 && flag[i] <= 90)
        {
            hidden = hidden + "_";
            continue;
        }

        hidden = hidden + " ";
    }
    *word = hidden;
}

// alinan harfin uzakliginin kontrolü
int guessCounter(char letter, string str) {
    if (int(letter) >= 65 && int(letter) <= 90) {
        int minDistance = INT_MAX;
        char closest = '\0';

        for (char let : str) {
            int distance = abs(let - letter);
            if (distance < minDistance) {
                minDistance = distance;
                closest = let;
            }
        }
        return (abs(closest - letter) - 1) / 5 + 1;
    }
    else {
        return 0;
    }

}

//Adamýn kademeli asilmasi
void hangedMan(int attempts) {
    int i;

    if (attempts == 10) {
        cursorMovement(30, 16);
        cout << "Man Is Alive ";
        cursorMovement(30, 17);
        cout << "Don't Worry !";
    }
    if (attempts == 9) {

        string hangedMan[6] = { "  |  ", "  |  ", "  |  ", "  |  ", "  |  ", "__|__" };

        for (i = 0; i < 6; i++)
        {
            cursorMovement(35, 10 + i + 2);
            cout << hangedMan[i];
        }
    }
    if (attempts == 8) {

        string hangedMan[7] = { "  ______    " ,"  |         " ,"  |         " ,"  |         " ,"  |         " ,"  |         ","__|__       " };

        for (i = 0; i < 7; i++)
        {
            cursorMovement(35, 10 + i + 1);
            cout << hangedMan[i];
        }
    }
    if (attempts == 7) {

        string hangedMan[7] = { "  ______    " ,"  |    |    " ,"  |         " ,"  |         " ,"  |         " ,"  |         ","__|__       " };

        for (i = 0; i < 7; i++)
        {
            cursorMovement(35, 10 + i + 1);
            cout << hangedMan[i];
        }
    }
    if (attempts == 6) {

        string hangedMan[7] = { "  ______    " ,"  |    |    " ,"  |    O    " ,"  |         " ,"  |         " ,"  |         ","__|__       " };

        for (i = 0; i < 7; i++)
        {
            cursorMovement(35, 10 + i + 1);
            cout << hangedMan[i];
        }
    }
    if (attempts == 5) {
        string hangedMan[7] = { "  ______    " ,"  |    |    " ,"  |    O    " ,"  |    |    " ,"  |         " ,"  |         ","__|__       " };

        for (i = 0; i < 7; i++)
        {
            cursorMovement(35, 10 + i + 1);
            cout << hangedMan[i];
        }
    }
    if (attempts == 4) {
        string hangedMan[7] = { "  ______    " ,"  |    |    " ,"  |    O    " ,"  |   /|    " ,"  |         " ,"  |         ","__|__       " };

        for (i = 0; i < 7; i++)
        {
            cursorMovement(35, 10 + i + 1);
            cout << hangedMan[i];
        }
    }
    if (attempts == 3) {
        string hangedMan[7] = { "  ______    " ,"  |    |    " ,"  |    O    " ,"  |   /|\\  " ,"  |         " ,"  |         ","__|__       " };

        for (i = 0; i < 7; i++)
        {
            cursorMovement(35, 10 + i + 1);
            cout << hangedMan[i];
        }
    }
    if (attempts == 2) {
        string hangedMan[7] = { "  ______    " ,"  |    |    " ,"  |    O    " ,"  |   /|\\  " ,"  |   /     " ,"  |         ","__|__       " };

        for (i = 0; i < 7; i++)
        {
            cursorMovement(35, 10 + i + 1);
            cout << hangedMan[i];
        }
    }
    if (attempts == 1) {
        string hangedMan[7] = { "  ______    " ,"  |    |    " ,"  |    O    " ,"  |   /|\\  " ,"  |   / \\  " ,"  |         ","__|__       " };

        for (i = 0; i < 7; i++)
        {
            cursorMovement(35, 10 + i + 1);
            cout << hangedMan[i];
        }
    }
}

//Oyun Kurallarý
void ruleBook() {  
    newPage();
    gameBoxUnsleeped();
    cursorMovement(42, 10);
    cout << "The Game Is A Two Player Game";
    cursorMovement(25, 11);
    cout << "One player types a word and the other player tries to guess it";
    cursorMovement(35, 12);
    cout << "Must find the word in the least mistake";
    cursorMovement(33, 13);
    cout << "For every mistake, the man hangs one more step";
    cursorMovement(34, 14);
    cout << "The first to reach 3 points in the game wins";
    contin();
}

//bitiris ekrani
void finisher() {
    string message;
    message = "      The Game Finished Here";
    newPage();
    gameBoxUnsleeped();
    messageWiewer(message);
    Sleep(1000);
    newPage();
    gameBoxUnsleeped();
    message = "         Thanks For Playing";
    messageWiewer(message);
    Sleep(1000);
}

//oyunun kayit fonsiyonu
void save(int p1, string n1, int p2, string n2, string unknownWord, string word, int attemptsLeft, string typedGuesses, string wrongGuesses, bool gameTurn) {
    Player player1;
    Player player2;

    player1.score = p1;
    player2.score = p2;

    player1.name = n1;
    player2.name = n2;

    ofstream myfile("hangmanSave.txt");
    myfile << player1.name << endl;
    myfile << player2.name << endl;
    myfile << player1.score << endl;
    myfile << player2.score << endl;
    myfile << unknownWord << endl;
    myfile << word << endl;
    myfile << attemptsLeft << endl;
    myfile << typedGuesses << endl;
    myfile << wrongGuesses << endl;
    myfile << gameTurn << endl;
    myfile.close();
}

//oyunun yukleme fonsiyonu
void load(int p1, string n1, int p2, string n2, string unknownWord, string word, int attemptsLeft, string typedGuesses, string wrongGuesses, bool gameTurn) {
    Player player1;
    Player player2;

    player1.score = p1;
    player2.score = p2;

    player1.name = n1;
    player2.name = n2;

    ifstream myfile("hangmanSave.txt");
    myfile >> player1.name;
    myfile >> player2.name;
    myfile >> player1.score;
    myfile >> player2.score;
    myfile >> unknownWord;
    myfile >> word;
    myfile >> attemptsLeft;
    myfile >> typedGuesses;
    myfile >> wrongGuesses;
    myfile >> gameTurn;
    myfile.close();
}

void gameLoop() {
    
    //kisa giris

    static string message = "     Welcome To HANGMAN Game !!";
    static string message2 = "Do You Want To Start The Game ?(Y/N)";
    bool gameTurn = true;

    gameBoxSleeped();
    newPage();
    messageWiewer(message);
    Sleep(1000);
    newPage();


retry:
    messageWiewer(message2);
    char letter;
    letter = _getch();
    letter = toupper(letter);

    if (letter == 'Y') {

    startMenu:
        
        //menu ekrani

        newPage();
        gameBoxUnsleeped();
        cursorMovement(50, 7);
        cout << "**HANGMAN**";
        string startMenuList[4] = { {"1.New Game"},{"2.Load Save"},{"3.How To Play"},{"4.Quit To Desktop"} };
        for (int i = 0; i < 4; i++) {
            cursorMovement(47, 12 + i);
            cout << startMenuList[i];
            Sleep(500);

        }
        char value;
        value = _getch();
        
        /////////////////// NEW GAME ////////////////////// NEW GAME /////////////////////// NEW GAME //////////////////////////////////// NEW GAME //////////////////////
        
        if (value == '1') {
        newGame2:
        game:
            gameLoading();
            ofstream myfile;
            myfile.open("hangmanSave.txt");


            int attemptsLeft;
            Player* player1 = new Player;
            Player* player2 = new Player;

            string* name1 = new string;
            string* name2 = new string;

            //kullanici verilerinin alinmasi


            newPage();
            gameBoxUnsleeped();
            cursorMovement(38, 8);
            cout << "Player 1 Pls Type Your Name : ";
            cin >> *name1;
            transform(name1->begin(), name1->end(), name1->begin(), ::toupper);
            player1->name = *name1;


            newPage();
            gameBoxUnsleeped();
            cursorMovement(38, 8);
            cout << "Player 2 Pls Type Your Name : ";
            cin >> *name2;
            transform(name2->begin(), name2->end(), name2->begin(), ::toupper);
            player2->name = *name2;


            player1->score = 0;
            player2->score = 0;


            int* p1;
            int* p2;

            string* n1;
            string* n2;

            n1 = &player1->name;
            n2 = &player2->name;

            p1 = &player1->score;
            p2 = &player2->score;

            newPage();
            do {
                //oyun dongusu baslangici

                string typedGuesses;
                string wrongGuesses;
                if (gameTurn == true) {
                    attemptsLeft = 10;
                    gameBoxUnsleeped();
                    cursorMovement(35, 8);
                    cout << player1->name << " Pls Type A Word : ";

                    string unknownWord, word;
                    cin >> word;
                    transform(word.begin(), word.end(), word.begin(), ::toupper);
                    unknownWord = word;

                    wordHider(&unknownWord);
                    int wrongLetterCount;
                    do {
                    ol:
                        scoreBoard(*p1, *n1, *p2, *n2);
                        hangedMan(attemptsLeft);

                        wrongLetterCount = 0;

                        cursorMovement(65, 16);
                        cout << unknownWord;

                        cursorMovement(38, 8);
                        cout << player2->name << " Pls Type a Letter : ";
                        cursorMovement(21, 24);
                        cout << "Press ESC to Stop The Game";
                        cursorMovement(38, 9);
                        cout << "Wrong Guesses : ";
                        for (int i = 0; i < wrongGuesses.length(); i++) {
                            cout << wrongGuesses[i] << " ";
                        }

                        char guess;
                        guess = _getch();
                        if (guess == 27) {
                            newPage();
                            gameBoxUnsleeped();


                        menu:
                            //oyun arasi kucuk menu
                            string menuList[3] = { "1.New Game","2.Continue","3.Exit" };
                            for (int i = 0; i < 3; i++) {
                                cursorMovement(50, 10 + i);
                                cout << menuList[i];
                            }
                            char menuValue;
                            menuValue = _getch();

                            if (menuValue == '1') {
                                goto game;
                            }
                            else if (menuValue == '2') {
                                goto ol;
                            }
                            else if (menuValue == '3') {
                                save(*p1, *n1, *p2, *n2, unknownWord, word, attemptsLeft, typedGuesses, wrongGuesses, gameTurn);
                                goto exitEnd;
                            }
                            else {
                                cursorMovement(45, 14);
                                cout << "Invalid Key!!";
                                goto menu;
                            }
                        }
                        else {
                            guess = toupper(guess);
                        }

                        newPage();
                        
                        //harf kontrol basamaklari 

                        for (int i = 0; i < (typedGuesses).length(); i++) {

                            if (guess == (typedGuesses)[i]) {
                                gameBoxUnsleeped();
                                cursorMovement(38, 11);
                                cout << "You Have Already Typed This Letter !";
                                contin();
                                goto ol;

                            }
                        }
                        for (int i = 0; i < word.length(); i++) {

                            if (guess == word[i]) {

                                unknownWord[i] = guess;
                                wrongLetterCount++;
                                typedGuesses = typedGuesses + guess;

                            }
                        }

                        if (wrongLetterCount == 0) {

                            wrongGuesses = wrongGuesses + guess;
                            typedGuesses = typedGuesses + wrongGuesses;

                            attemptsLeft -= guessCounter(guess, word);

                        }
                        //puanlama kismi

                        if (attemptsLeft < 1) {
                            newPage();
                            gameBoxUnsleeped();

                            cursorMovement(45, 10);
                            cout << player1->name << " Received A Score";
                            player1->score += 1;

                            contin();
                            scoreBoard(*p1, *n1, *p2, *n2);
                            goto exit;

                        }
                        if (unknownWord == word) {

                            newPage();
                            gameBoxUnsleeped();
                            cursorMovement(45, 10);
                            cout << player2->name << " Received A Score";
                            player2->score += 1;

                            contin();
                            scoreBoard(*p1, *n1, *p2, *n2);
                            goto exit;

                        }

                    } while (1);

                }

                if (gameTurn == false) {
                    attemptsLeft = 10;
                    gameBoxUnsleeped();
                    cursorMovement(35, 8);
                    cout << player2->name << " Pls Type A Word : ";

                    string unknownWord, word;
                    cin >> word;
                    transform(word.begin(), word.end(), word.begin(), ::toupper);
                    unknownWord = word;

                    wordHider(&unknownWord);

                    do {

                    ol2:
                        scoreBoard(*p1, *n1, *p2, *n2);
                        hangedMan(attemptsLeft);

                        int wrongLetterCount = 0;
                        cursorMovement(65, 16);
                        cout << unknownWord;

                        cursorMovement(38, 8);
                        cout << player1->name << " Pls Type a Letter : ";
                        cursorMovement(21, 24);
                        cout << "Press ESC to Stop The Game";
                        cursorMovement(38, 9);
                        cout << "Wrong Guesses : ";
                        for (int i = 0; i < wrongGuesses.length(); i++) {
                            cout << wrongGuesses[i] << " ";
                        }
                        char guess;
                        guess = _getch();
                        if (guess == 27) {
                            newPage();
                            gameBoxUnsleeped();
                        menu2:
                            string menuList[3] = { "1.New Game","2.Continue","3.Exit" };
                            for (int i = 0; i < 3; i++) {
                                cursorMovement(50, 10 + i);
                                cout << menuList[i];
                            }
                            char menuValue;
                            menuValue = _getch();
                            if (menuValue == '1') {
                                goto game;
                            }
                            else if (menuValue == '2') {
                                goto ol2;
                            }
                            else if (menuValue == '3') {
                                save(*p1, *n1, *p2, *n2, unknownWord, word, attemptsLeft, typedGuesses, wrongGuesses, gameTurn);
                                goto exitEnd;
                            }
                            else {
                                cursorMovement(45, 14);
                                cout << "Invalid Key!!";
                                goto menu2;
                            }
                        }
                        else {
                            guess = toupper(guess);
                        }


                        newPage();
                        gameBoxUnsleeped();

                        for (int i = 0; i < (typedGuesses).length(); i++) {

                            if (guess == (typedGuesses)[i]) {
                                gameBoxUnsleeped();
                                cursorMovement(38, 11);
                                cout << "You Have Already Typed This Letter !";
                                contin();
                                goto ol2;

                            }
                        }
                        for (int i = 0; i < word.length(); i++) {

                            if (guess == word[i]) {

                                unknownWord[i] = guess;
                                wrongLetterCount++;
                                typedGuesses = typedGuesses + guess;

                            }
                        }

                        if (wrongLetterCount == 0) {

                            wrongGuesses = wrongGuesses + guess;
                            typedGuesses = typedGuesses + wrongGuesses;

                            attemptsLeft -= guessCounter(guess, word);
                        }
                        if (attemptsLeft < 1) {
                            newPage();
                            gameBoxUnsleeped();
                            cursorMovement(45, 10);
                            cout << player2->name << " Received A Score";
                            player2->score += 1;

                            contin();
                            scoreBoard(*p1, *n1, *p2, *n2);
                            goto exit;

                        }
                        if (unknownWord == word) {

                            newPage();
                            gameBoxUnsleeped();
                            cursorMovement(45, 10);
                            cout << player1->name << " Received A Score";
                            player1->score += 1;

                            contin();
                            scoreBoard(*p1, *n1, *p2, *n2);
                            goto exit;
                        }

                    } while (1);

                }

            exit:
                if (player1->score == 3) {

                    newPage();
                    gameBoxUnsleeped();
                    cursorMovement(40, 11);
                    cout << player1->name << " Won The Game Congrats!!";
                    ofstream myfile("hangmanSave.txt");
                    myfile.close();
                    contin();
                    finisher();
                    contin();

                    char end;
                que:
                    newPage();
                    gameBoxUnsleeped();
                    cursorMovement(42, 10);
                    cout << "Do You Want To Play Again ?(Y/N)";
                    end = _getch();

                    if (end == 'y') {
                        goto game;
                    }
                    else if (end == 'n') {
                        break;
                    }
                    else {
                        cursorMovement(42, 10);
                        cout << "Invalid Key !!";
                        goto que;
                    }
                }
                if (player2->score == 3) {

                    newPage();
                    gameBoxUnsleeped();
                    cursorMovement(40, 11);
                    cout << player2->name << " Won The Game Congrats!!";
                    ofstream myfile("hangmanSave.txt");
                    myfile.close();
                    contin();
                    finisher();
                    contin();

                    char end;
                que2:
                    newPage();
                    gameBoxUnsleeped();
                    cursorMovement(40, 10);
                    cout << "Do You Want To Play Again ?(Y/N)";
                    end = _getch();

                    if (end == 'y') {
                        goto game;
                    }
                    else if (end == 'n') {
                        break;
                    }
                    else {
                        cursorMovement(40, 10);
                        cout << "Invalid Key !!";
                        goto que2;
                    }
                }
                gameTurn = !(gameTurn);
            } while (1);

            myfile.close();

            delete player1;
            delete player2;
            delete name1;
            delete name2;
        }
        /////////////////// CONTINUE ////////////////////// CONTINUE /////////////////////// CONTINUE //////////////////////////////////// CONTINUE //////////////////////
        else if (value == '2') {
            
            ifstream myfile;
            myfile.open("hangmanSave.txt");

            if (!(myfile.is_open())) {
                cursorMovement(47, 17);
                cout << "Save File Not Found" << endl;
                Sleep(1000);
                goto startMenu;
            }
            if (myfile.peek() == ifstream::traits_type::eof()) {
                cursorMovement(47, 17);
                cout << "File Empty." << endl;
                Sleep(1000);
                goto startMenu;
            }
            
            gameLoading();
            
            

            int attemptsLeft;
            Player* player1 = new Player;
            Player* player2 = new Player;

            string* name1 = new string;
            string* name2 = new string;

            string typedGuesses;
            string wrongGuesses;
            string unknownWord, word;

            int* p1;
            int* p2;

            string* n1;
            string* n2;

            myfile >> player1->name;
            myfile >> player2->name;
            myfile >> player1->score;
            myfile >> player2->score;
            myfile >> unknownWord;
            myfile >> word;
            myfile >> attemptsLeft;
            myfile >> typedGuesses;
            myfile >> wrongGuesses;
            myfile >> gameTurn;


            n1 = &player1->name;
            n2 = &player2->name;

            p1 = &player1->score;
            p2 = &player2->score;

            newPage();
            do {
                load(*p1, *n1, *p2, *n2, unknownWord, word, attemptsLeft, typedGuesses, wrongGuesses, gameTurn);
                if (gameTurn == true) {
                    
                    if (unknownWord == " ") {
                        attemptsLeft = 10;
                        word = " ";
                        gameBoxUnsleeped();
                        cursorMovement(35, 8);
                        cout << player1->name << " Pls Type A Word : ";
                        cin >> word;
                        transform(word.begin(), word.end(), word.begin(), ::toupper);
                        unknownWord = word;

                        wordHider(&unknownWord);
                        goto play;
                    }
                    else {
                        goto play;
                    }
                play:
                    int wrongLetterCount;
                    do {
                    dol:
                        scoreBoard(*p1, *n1, *p2, *n2);
                        hangedMan(attemptsLeft);

                        wrongLetterCount = 0;

                        cursorMovement(65, 16);
                        cout << unknownWord;

                        cursorMovement(38, 8);
                        cout << player2->name << " Pls Type a Letter : ";
                        cursorMovement(21, 24);
                        cout << "Press ESC to Stop The Game";
                        cursorMovement(38, 9);
                        cout << "Wrong Guesses : ";
                        for (int i = 0; i < wrongGuesses.length(); i++) {
                            cout << wrongGuesses[i] << " ";
                        }
                        

                        char guess;
                        guess = _getch();
                        if (guess == 27) {
                            newPage();
                            gameBoxUnsleeped();


                        menuD:
                            string menuList[4] = { "1.New Game","2.Continue","3.How To Play ","4.Exit" };
                            for (int i = 0; i < 4; i++) {
                                cursorMovement(50, 10 + i);
                                cout << menuList[i];
                            }
                            char menuValue;
                            menuValue = _getch();
                            if (menuValue == '1') {
                                goto newGame2;
                            }
                            else if (menuValue == '2') {
                                goto dol;
                            }
                            else if (menuValue == '3') {
                                ruleBook();
                                goto menuD;
                            }
                            else if (menuValue == '4') {
                                save(*p1, *n1, *p2, *n2, unknownWord, word, attemptsLeft, typedGuesses, wrongGuesses, gameTurn);
                                goto exitEnd;
                            }
                            else {
                                cursorMovement(45, 14);
                                cout << "Invalid Key!!";
                                goto menuD;
                            }
                        }
                        else {
                            guess = toupper(guess);
                        }

                        newPage();

                        for (int i = 0; i < (typedGuesses).length(); i++) {

                            if (guess == (typedGuesses)[i]) {
                                gameBoxUnsleeped();
                                cursorMovement(38, 11);
                                cout << "You Have Already Typed This Letter !";
                                contin();
                                goto dol;

                            }
                        }
                        for (int i = 0; i < word.length(); i++) {

                            if (guess == word[i]) {

                                unknownWord[i] = guess;
                                wrongLetterCount++;
                                typedGuesses = typedGuesses + guess;

                            }
                        }

                        if (wrongLetterCount == 0) {

                            wrongGuesses = wrongGuesses + guess;
                            typedGuesses = typedGuesses + wrongGuesses;

                            attemptsLeft -= guessCounter(guess, word);

                        }
                        if (attemptsLeft < 1) {
                            newPage();
                            gameBoxUnsleeped();

                            cursorMovement(45, 10);
                            cout << player1->name << " Received A Score";
                            player1->score += 1;

                            contin();
                            scoreBoard(*p1, *n1, *p2, *n2);
                            goto exit2;

                        }
                        if (unknownWord == word) {

                            newPage();
                            gameBoxUnsleeped();
                            cursorMovement(45, 10);
                            cout << player2->name << " Received A Score";
                            player2->score += 1;

                            contin();
                            scoreBoard(*p1, *n1, *p2, *n2);
                            goto exit2;

                        }

                    } while (1);

                }

                if (gameTurn == false) {

                    if (unknownWord == " ") {
                        word = " ";
                        attemptsLeft = 10;
                        gameBoxUnsleeped();
                        cursorMovement(35, 8);
                        cout << player1->name << " Pls Type A Word : ";

                        cin >> word;
                        transform(word.begin(), word.end(), word.begin(), ::toupper);
                        unknownWord = word;

                        wordHider(&unknownWord);
                        goto play2;
                    }
                    else {
                        goto play2;
                    }
                play2:
                    do {

                    dol2:
                        scoreBoard(*p1, *n1, *p2, *n2);
                        hangedMan(attemptsLeft);

                        int wrongLetterCount = 0;
                        cursorMovement(65, 16);
                        cout << unknownWord;

                        cursorMovement(38, 8);
                        cout << player1->name << " Pls Type a Letter : ";
                        cursorMovement(21, 24);
                        cout << "Press ESC to Stop The Game";
                        cursorMovement(38, 9);
                        cout << "Wrong Guesses : ";
                        for (int i = 0; i < wrongGuesses.length(); i++) {
                            cout << wrongGuesses[i] << " ";
                        }
                        char guess;
                        guess = _getch();
                        if (guess == 27) {
                            newPage();
                            gameBoxUnsleeped();
                        menu2D:
                            string menuList[4] = { "1.New Game","2.Continue","3.How To Play ","4.Exit" };
                            for (int i = 0; i < 4; i++) {
                                cursorMovement(50, 10 + i);
                                cout << menuList[i];
                            }
                            char menuValue;
                            menuValue = _getch();
                            if (menuValue == '1') {
                                goto game;
                            }
                            else if (menuValue == '2') {
                                goto dol2;
                            }
                            else if (menuValue == '3') {
                                ruleBook();
                                goto menu2D;
                            }
                            else if (menuValue == '4') {
                                save(*p1, *n1, *p2, *n2, unknownWord, word, attemptsLeft, typedGuesses, wrongGuesses, gameTurn);
                                goto exitEnd;
                            }
                            else {
                                cursorMovement(45, 14);
                                cout << "Invalid Key!!";
                                goto menu2D;
                            }
                        }
                        else {
                            guess = toupper(guess);
                        }


                        newPage();
                        gameBoxUnsleeped();

                        for (int i = 0; i < (typedGuesses).length(); i++) {

                            if (guess == (typedGuesses)[i]) {
                                gameBoxUnsleeped();
                                cursorMovement(38, 11);
                                cout << "You Have Already Typed This Letter !";
                                contin();
                                goto dol2;

                            }
                        }
                        for (int i = 0; i < word.length(); i++) {

                            if (guess == word[i]) {

                                unknownWord[i] = guess;
                                wrongLetterCount++;
                                typedGuesses = typedGuesses + guess;

                            }
                        }

                        if (wrongLetterCount == 0) {

                            wrongGuesses = wrongGuesses + guess;
                            typedGuesses = typedGuesses + wrongGuesses;

                            attemptsLeft -= guessCounter(guess, word);
                        }
                        if (attemptsLeft < 1) {
                            newPage();
                            gameBoxUnsleeped();
                            cursorMovement(45, 10);
                            cout << player2->name << " Received A Score";
                            player2->score += 1;

                            contin();
                            scoreBoard(*p1, *n1, *p2, *n2);
                            goto exit2;

                        }
                        if (unknownWord == word) {

                            newPage();
                            gameBoxUnsleeped();
                            cursorMovement(45, 10);
                            cout << player1->name << " Received A Score";
                            player1->score += 1;

                            contin();
                            scoreBoard(*p1, *n1, *p2, *n2);
                            goto exit2;
                        }

                    } while (1);

                }

            exit2:
                if (player1->score == 3) {

                    newPage();
                    gameBoxUnsleeped();
                    cursorMovement(40, 11);
                    cout << player1->name << " Won The Game Congrats!!";

                    ofstream myfile("hangmanSave.txt");
                    myfile.close();
                    contin();
                    finisher();
                    contin();

                    char end;
                queD:
                    newPage();
                    gameBoxUnsleeped();
                    cursorMovement(42, 10);
                    cout << "Do You Want To Play Again ?(Y/N)";
                    end = _getch();

                    if (end == 'y') {
                        goto game;
                    }
                    else if (end == 'n') {
                        break;
                    }
                    else {
                        cursorMovement(42, 10);
                        cout << "Invalid Key !!";
                        goto queD;
                    }
                }
                if (player2->score == 3) {

                    newPage();
                    gameBoxUnsleeped();
                    cursorMovement(40, 11);
                    cout << player2->name << " Won The Game Congrats!!";
                    ofstream myfile("hangmanSave.txt");
                    myfile.close();
                    contin();
                    finisher();
                    contin();

                    char end;
                que2D:
                    newPage();
                    gameBoxUnsleeped();
                    cursorMovement(40, 10);
                    cout << "Do You Want To Play Again ?(Y/N)";
                    end = _getch();

                    if (end == 'y') {
                        goto game;
                    }
                    else if (end == 'n') {
                        break;
                    }
                    else {
                        cursorMovement(40, 10);
                        cout << "Invalid Key !!";
                        goto que2D;
                    }
                }
                gameTurn = !(gameTurn);
                unknownWord = " ";
                word = " ";
                attemptsLeft = 10;
                typedGuesses = " ";
                wrongGuesses = " ";
                save(*p1, *n1, *p2, *n2, unknownWord, word, attemptsLeft, typedGuesses, wrongGuesses, gameTurn);
            } while (1);

            myfile.close();

            delete player1;
            delete player2;
            delete name1;
            delete name2;
        }
        /////////////////// RULEBOOK ////////////////////// RULEBOOK /////////////////////// RULEBOOK //////////////////////////////////// RULEBOOK //////////////////////
        else if (value == '3') {
            ruleBook();
            goto startMenu;
        }
        /////////////////// QUIT ////////////////////// QUIT /////////////////////// QUIT //////////////////////////////////// QUIT //////////////////////
        else if (value == '4') {
            goto exitEnd;
        }
        else {
            cursorMovement(50, 9);
            cout << "!!Invalid Key!!";
            goto startMenu;

        }
    }

    else if (letter == 'n') {

    exitEnd:
        finisher();
        abort;
    }
    else {
        cursorMovement(21, 23);
        cout << "Pls Type a Valid Key !!" << endl;
        goto retry;
    }
}

int main() {
    hideCursor();
    gameLoop();

    newPage();
    return 0;
}
