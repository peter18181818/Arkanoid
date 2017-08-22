#include <iostream>
#include <conio.h> // getch();
#include <windows.h> // system("pause") // system("cls")
#include <stdlib.h> // rand() // srand();
#include <time.h> // time()

using namespace std;

void cursor_return(int x, int y) // this function reduces screen blinking
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;

    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}

int main()
{
    srand(time(NULL)); // function for random drawing

    // variables declaration
    int width = 40;
    int height = 40;
    char wall_brick = 219;
    int wall_brick_X_coordinate[10000], wall_brick_Y_coordinate[10000];
    char player = 219;
    int player_X_coordinate, player_Y_coordinate;
    char frame_horizontal = 205, frame_vertical = 186;
    char frame_corner_A = 201, frame_corner_B = 187, frame_corner_C = 188, frame_corner_D = 200;
    int game_speed = 20;
    int key_ascii_no;
    int player_direction;
    char ball = 232;
    int ball_X_coordinate, ball_Y_coordinate;
    int ball_direction = rand()%(2-1+1)+1;
    int points = 0;
    int wall_brick_counter = 0;

    // dynamic allocation of two dimensional array
    char ** board = new char * [width];
    for (int i=0; i<width; i++)
        board[i] = new char[height];

    // filling up game board
    for (int i=1; i<height-1; i++)
    {
        for (int j=1; j<width-1; j++)
        {
            if ((i<(height/2-4)) && (i>2) && (j<width-4) && (j>4) && (i%2==0) && (j%2==0))
            {
                wall_brick_X_coordinate[j] = j;
                wall_brick_Y_coordinate[i] = i;
                board[wall_brick_X_coordinate[j]][wall_brick_Y_coordinate[i]] = 'w';
                wall_brick_counter++;
            }
            else
                board[j][i] = 'e'; // empty space
        }
    }

    ball_X_coordinate = (width/2);
    ball_Y_coordinate = height-6;

    player_X_coordinate = (width)/2;
    player_Y_coordinate = height-4;

    board[player_X_coordinate][player_Y_coordinate] = 'p'; // player
    board[player_X_coordinate-3][player_Y_coordinate] = 'p';
    board[player_X_coordinate-2][player_Y_coordinate] = 'p';
    board[player_X_coordinate-1][player_Y_coordinate] = 'p';

    board[player_X_coordinate+3][player_Y_coordinate] = 'p';
    board[player_X_coordinate+2][player_Y_coordinate] = 'p';
    board[player_X_coordinate+1][player_Y_coordinate] = 'p';

    // displaying start screen
    cout << "\n\n\n\n\n\t    ********** ARKANOID *********** \n\n\n\n " << endl;
    cout << "\t Control: Left and right arrow key on keyboard" << endl;
    cout << "\t Pause: P key on keyboard" << endl << endl;
    cout << "\t Speed of the game increases every 25 points" << endl;
    cout << "\t You lose if you dont catch the ball" << endl << endl;
    cout << "\t ";
    system("pause");
    system("cls"); // screen cleaning before game start

    while (true) // actual game starts *************************************************************************************************
    {
        cursor_return(0,0);

        // drawing game board
        cout << frame_corner_A; // left up corner
        for (int i=1; i<width-1; i++)
            cout << frame_horizontal << frame_horizontal; // upper frame
        cout << frame_corner_B; // right up corner

        for (int i=1; i<height-1; i++)
        {
            cout << endl << frame_vertical; // left frame
            for (int j=1; j<width-1; j++)
            {
                if (ball_X_coordinate == j && ball_Y_coordinate == i)
                {
                    cout << ball << " ";
                    continue;
                }
                if (board[j][i] == 'e')
                    cout << "  ";
                if (board[j][i] == 'w')
                    cout << wall_brick << wall_brick;
                if (board[j][i] == 'b')
                    cout << ball << " ";
                if (board[j][i] == 'p')
                    cout << player << player;
            }
            cout << frame_vertical; // right frame
        }
        cout << endl;

        cout << frame_corner_D; // left lower corner
        for (int i=1; i<width-1; i++)
            cout << frame_horizontal << frame_horizontal; // lower frame
        cout << frame_corner_C; // right lower corner
        cout << endl;

        // increasing game speed every 30 points
        if (points >= 25 ) game_speed = 10;
        if (points >= 50 ) game_speed = 5;
        if (points >= 75 ) game_speed = 1;

        Sleep(game_speed); // game delay/speed

        // player moving
        if(kbhit()) // function which read key pressed on keyboard
        {
            key_ascii_no = getch();
            if ((key_ascii_no == 80) || (key_ascii_no == 112)) // Pause
            {
                cout << "\n\t\t\t\t      PAUSE (press P to continue) " << endl; // pause
                getch();
                system("CLS"); // screen cleaning after pause
            }
            if (key_ascii_no == 224)
                key_ascii_no += getch();
            switch(key_ascii_no)
            {
            case 299: // left arrow on keyboard
                if ((key_ascii_no == 299) && (player_X_coordinate-4 > 0))
                {
                    player_direction=1;
                    break;
                }
            case 301: // right arrow on keyboard
                if ((key_ascii_no == 301) && (player_X_coordinate+5 < width))
                {
                    player_direction=2;
                    break;
                }
            }
        }

        if (player_direction == 1)
        {
            player_X_coordinate--; // move left
            board[player_X_coordinate][player_Y_coordinate] = 'p';
            board[player_X_coordinate-3][player_Y_coordinate] = 'p';
            board[player_X_coordinate-2][player_Y_coordinate] = 'p';
            board[player_X_coordinate-1][player_Y_coordinate] = 'p';

            board[player_X_coordinate+4][player_Y_coordinate] = 'e';
            player_direction = 0;
        }
        if (player_direction == 2)
        {
            player_X_coordinate++; // move right
            board[player_X_coordinate][player_Y_coordinate] = 'p';
            board[player_X_coordinate+3][player_Y_coordinate] = 'p';
            board[player_X_coordinate+2][player_Y_coordinate] = 'p';
            board[player_X_coordinate+1][player_Y_coordinate] = 'p';

            board[player_X_coordinate-4][player_Y_coordinate] = 'e';
            player_direction = 0;
        }

        // ball moving
        switch(ball_direction)
        {
        case 1: // move left up
        {
            ball_X_coordinate--;
            ball_Y_coordinate--;
            break;
        }
        case 2: // move right up
        {
            ball_X_coordinate++;
            ball_Y_coordinate--;
            break;
        }
        case 3: // move left down
        {
            ball_X_coordinate--;
            ball_Y_coordinate++;
            break;
        }
        case 4: // move right down
        {
            ball_X_coordinate++;
            ball_Y_coordinate++;
            break;
        }
        }

        if (((ball_direction == 2) && (ball_X_coordinate == width-1))||((ball_direction == 3) && (ball_Y_coordinate == height-1)))
        {
            ball_direction = 1; // move left up
        }
        else if (((ball_direction == 1) && (ball_Y_coordinate == 1)) || ((ball_direction == 4) && (ball_X_coordinate == width-1)))
        {
            ball_direction = 3; // move left down
        }
        else if (((ball_direction == 3) && (ball_X_coordinate == 1)) || ((ball_direction == 2) && (ball_Y_coordinate == 1)))
        {
            ball_direction = 4; // move right down
        }
        else if (((ball_direction == 4) && (ball_Y_coordinate == height-1)) || ((ball_direction == 1) && (ball_X_coordinate == 1)))
        {
            ball_direction = 2; // move right up
        }

        // ball and player collision
        if ((ball_X_coordinate <= player_X_coordinate+4) && (ball_X_coordinate >= player_X_coordinate-4) && (ball_Y_coordinate == player_Y_coordinate-1))
            ball_direction = rand()%(2-1+1)+1;

        // ball and wall brick collision
        if(board[ball_X_coordinate][ball_Y_coordinate] == 'w')
        {
            board[ball_X_coordinate][ball_Y_coordinate] = 'e';
            points++;

            if (ball_direction == 1 || ball_direction == 2)
            {
                ball_direction = rand()%(4-3+1)+3;
            }
            else if (ball_direction == 3 || ball_direction == 4)
            {
                ball_direction = rand()%(2-1+1)+1;
            }
        }

        // displaying points
        //cout << "\n\n\n\t\t      Dlugosc weza: " << dlugoscWeza << endl; // wypisuje dlugosc weza(punkty) na ekran
        cout << endl << "\tYour points: " << points << " max. " << wall_brick_counter << endl << endl;

        // game end
        if(ball_Y_coordinate > player_Y_coordinate+1) // game ends when player miss the ball
        {
            cout << "\t\t\t\t     GAME OVER" << endl << endl;
            break;
        }

        if (points == wall_brick_counter) // game ends when player hit all bricks
        {
            cout << "\t\t\t\t     YOU WON, GOOD JOB :)" << endl << endl;
            break;
        }


    } // actual game ends ***************************************************************************************************************


    for(int i=0; i<width; i++) // deleting two dimensional array (memory release)
        delete [] board[i];
    delete [] board;

    getch();
    return 0;
}
