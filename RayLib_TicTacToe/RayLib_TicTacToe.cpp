#include "raylib.h"
#include <string>
#include <iostream>
#include <vector>

enum Turn {
    X_TURN, O_TURN,
};
enum GameScreen {
    MENU, GAME, GAME_OVER,
};
enum Pos {
    POS_1 = 0, POS_2, POS_3,
    POS_4, POS_5, POS_6, 
    POS_7, POS_8, POS_9,
};
enum GameResult {
    X_WINS,TIE,O_WINS,CONTINUE,
};

//initialization
const int screenWidth = 512;
const int screenHeight = 562;

GameResult gameResult(const std::string& game);

int main(void)
{
    InitWindow(screenWidth, screenHeight, "TicTacToe");

    SetTargetFPS(120);
    SetWindowPosition(300, 300);
   
    Texture2D fieldTex = LoadTexture("./res/field_texture.png");
    Texture2D oTex = LoadTexture("./res/o_texture.png");
    Texture2D xTex = LoadTexture("./res/x_texture.png");

    Vector2 xoWinsMsgPos = { 45, 5 };
    Vector2 tieMsgPos = { 70, 5 };
    Vector2 xoTurnMsgPos = { 180, 10 };

    Font msgFont = LoadFont("./res/arialbd.ttf");
    SetTextureFilter(msgFont.texture, TEXTURE_FILTER_BILINEAR);

    Vector2 fieldPos = { 0, 50 };
    
    std::vector<Vector2> positions = {
        { 111, 144 }, { 223, 144 }, { 335, 144 },
        { 112, 255 }, { 223, 255 }, { 335, 255 },
        { 112, 366 }, { 223, 366 }, { 335, 366 },
    };
    //xTex or oTex width/height : 65/66
    std::vector<Rectangle> posHitbox = {
        { positions[POS_1].x, positions[POS_1].y, 65, 66},
        { positions[POS_2].x, positions[POS_2].y, 65, 66},
        { positions[POS_3].x, positions[POS_3].y, 65, 66},
        { positions[POS_4].x, positions[POS_4].y, 65, 66},
        { positions[POS_5].x, positions[POS_5].y, 65, 66},
        { positions[POS_6].x, positions[POS_6].y, 65, 66},
        { positions[POS_7].x, positions[POS_7].y, 65, 66},
        { positions[POS_8].x, positions[POS_8].y, 65, 66},
        { positions[POS_9].x, positions[POS_9].y, 65, 66},
    };

    std::string strField =
        "+++"
        "+++"
        "+++"
    ;

    Turn currTurn = X_TURN;

    while (!WindowShouldClose())   
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //Drawing Field
        DrawTextureEx(fieldTex, fieldPos, 0.0f, 1.0f, LIME);

        //Drawing X O
        for (int i = 0; i < strField.size(); ++i) {
            if (strField[i] != '+') {
                if (strField[i] == 'x')
                    DrawTextureEx(xTex, positions[i], 0.0f, 1.0f, WHITE);
                else
                    DrawTextureEx(oTex, positions[i], 0.0f, 1.0f, WHITE);
            }
        }
  
        GameResult isGame = gameResult(strField);
        if (isGame == CONTINUE) {
            //Drawing Turn : X or O
            DrawTextEx(msgFont, (currTurn == X_TURN) ? "x turn" : "o turn", xoTurnMsgPos, 60, 0.0f, BLACK);
        
            //Checking Collisions
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                for (int i = 0; i < strField.size(); ++i) 
                    if (CheckCollisionPointRec(GetMousePosition(), posHitbox[i]) and strField[i] == '+')
                        if (currTurn == X_TURN) {
                            strField[i] = 'x';
                            currTurn = O_TURN;
                        }
                        else {
                            strField[i] = 'o';
                            currTurn = X_TURN;
                        }
        }
        //Game Over
        else {
            if (isGame == X_WINS) {
                DrawTextEx(msgFont, "X Wins! Press R to Replay", xoWinsMsgPos, 40, 0.0f, BLACK);
                if (IsKeyPressed(KEY_R)) {
                    strField = "+++++++++";
                    currTurn = X_TURN;
                }
            }
            else if (isGame == O_WINS) {
                DrawTextEx(msgFont, "O Wins! Press R to Replay", xoWinsMsgPos, 40, 0.0f, BLACK);
                if (IsKeyPressed(KEY_R)) {
                    strField = "+++++++++";
                    currTurn = X_TURN;
                }
            }
            else {
                DrawTextEx(msgFont, "TIE! Press R to Replay", tieMsgPos, 40, 0.0f, BLACK);
                if (IsKeyPressed(KEY_R)) {
                    strField = "+++++++++";
                    currTurn = X_TURN;
                }
            }
        }

        EndDrawing();
    }
    CloseWindow(); 
    return 0;
}

GameResult gameResult(const std::string &game) {
    if (game.size() < 9)
        throw "Game filed size less than 9";

    if (game[0] == 'x' && game[1] == 'x' && game[2] == 'x')
        return X_WINS;
    if (game[3] == 'x' && game[4] == 'x' && game[5] == 'x')
        return X_WINS;
    if (game[6] == 'x' && game[7] == 'x' && game[8] == 'x')
        return X_WINS;
    if (game[0] == 'x' && game[3] == 'x' && game[6] == 'x')
        return X_WINS;
    if (game[1] == 'x' && game[4] == 'x' && game[7] == 'x')
        return X_WINS;
    if (game[2] == 'x' && game[5] == 'x' && game[8] == 'x')
        return X_WINS;
    if (game[0] == 'x' && game[4] == 'x' && game[8] == 'x')
        return X_WINS;
    if (game[2] == 'x' && game[4] == 'x' && game[6] == 'x')
        return X_WINS;

    if (game[0] == 'o' && game[1] == 'o' && game[2] == 'o')
        return O_WINS;
    if (game[3] == 'o' && game[4] == 'o' && game[5] == 'o')
        return O_WINS;
    if (game[6] == 'o' && game[7] == 'o' && game[8] == 'o')
        return O_WINS;
    if (game[0] == 'o' && game[3] == 'o' && game[6] == 'o')
        return O_WINS;
    if (game[1] == 'o' && game[4] == 'o' && game[7] == 'o')
        return O_WINS;
    if (game[2] == 'o' && game[5] == 'o' && game[8] == 'o')
        return O_WINS;
    if (game[0] == 'o' && game[4] == 'o' && game[8] == 'o')
        return O_WINS;
    if (game[2] == 'o' && game[4] == 'o' && game[6] == 'o')
        return O_WINS;

    for (const auto &e : game) {
        if (e == '+')
            return CONTINUE;
    }
    return TIE;
}
