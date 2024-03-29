#include <stdio.h>
#include <stdlib.h>

int play(int l, int r, int w, int h, int y);
void draw(int score1, int score2, int ballX, int ballY, int rocket1, int rocket2, int w, int h);
int Req1(int rocket1, int h, char command);
int Req2(int rocket2, int h, char command);

void draw(int score1, int score2, int ballX, int ballY, int rocket1, int rocket2, int w, int h) {
    system("clear");
    printf("PLAYER 1: %d PLAYER 2: %d\n", score1, score2);
    for (int i = 0; i < w; i++) {
        printf("#");
    }
    printf("\n");
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (x == ballX && y == ballY) {
                printf("O");
            } else if (x == 0 || x == w - 1) {
                printf("#");
            } else if (x == (w / 2 - 1)) {
                printf("|");
            } else if (x == 1 && (y == rocket1 || y == rocket1 - 1 || y == rocket1 + 1)) {
                printf("|");
            } else if (x == w - 2 && (y == rocket2 || y == rocket2 - 1 || y == rocket2 + 1)) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    for (int i = 0; i < w; i++) {
        printf("#");
    }
    printf("\n");
}

int play(int l, int r, int w, int h, int y) {
    int const bXBaza = w / 2 - 1;
    int const bYBaza = (h - 1) / 2;
    int const lBaza = h / 2;
    int const rBaza = h / 2;
    int bX = bXBaza;
    int bY = bYBaza;
    int dbX = -1;
    int dbY = -1;
    int s1 = 0;
    int s2 = 0;
    while (s1 < 21 && s2 < 21) {
        draw(s1, s2, bX, bY, l, r, w, h);
        char command = getchar();
        l = Req1(l, h, command) == 2 ? l : l + Req1(l, h, command);
        r = Req2(r, h, command) == 2 ? r : r + Req2(r, h, command);
        if ((bX == 1 || bX == w - 2)) {
            if (bX == 1) {
                s2++;
            } else if (bX == w - 2 && (bX != r || bX != r + 1 || bX != r - 1)) {
                s1++;
            }
            bX = bXBaza + 1;
            bY = bYBaza + 1;
            l = lBaza;
            r = rBaza;
            dbX = -1;
            dbY = -1;
        } else if ((bX > 2 && bX < w - 3) && (bY == 0 || bY == h - 1)) {
            dbY *= (-1);
        } else if (bX == 2) {
            if (bY == l || bY == l + 1 || bY == l - 1 || bY == l + 2 || bY == l - 2) {
                dbX *= (-1);
            }
        } else if (bX == w - 3) {
            if (bY == r || bY == r + 1 || bY == r - 1 || bY == r + 2 || bY == r - 2) {
                dbX *= (-1);
            }
        }
        bX += dbX;
        bY += dbY;
        printf("\n");
    }
    if (s1 == 21) {
        y = 1;
    }
    if (s2 == 21) {
        y = 2;
    }
    return y;
}

int Req1(int rocket1, int h, char command) {
    int y;
    if ((command == 'A' || command == 'a') && rocket1 > 1) {
        y = -1;
    } else if ((command == 'Z' || command == 'z') && rocket1 < h - 2) {
        y = 1;
    } else if (command == ' ') {
        y = 0;
    } else {
        y = 2;
    }
    return y;
}

int Req2(int rocket2, int h, char command) {
    int y;
    if ((command == 'K' || command == 'k') && rocket2 > 1) {
        y = -1;
    } else if ((command == 'M' || command == 'm') && rocket2 < h - 2) {
        y = 1;
    } else if (command == ' ') {
        y = 0;
    } else {
        y = 2;
    }
    return y;
}

int main() {
    int w = 79;
    int h = 23;
    int y = 0;
    int g = play(h / 2, h / 2, w, h, y);
    system("clear");
    if (g == 1)
    {
        system("cat w1.txt");
    }
    if (g == 2) {
        system("cat w2.txt");
    }
}
