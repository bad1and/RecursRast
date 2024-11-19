#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ncurses.h>

int field[30][20][35]; // z x y

int recursive_distance(int x1, int y1, int z1, int x, int y, int z) {
    if (x1 == x && y1 == y && z1 == z) {
        return 0;
    }
    int min_distance = 1e9;

    if (x1 < x) {
        min_distance = recursive_distance(x1 + 1, y1, z1, x, y, z) + 1;
    }
    if (x1 > x) {
        int temp = recursive_distance(x1 - 1, y1, z1, x, y, z) + 1;
        if (temp < min_distance) min_distance = temp;
    }
    if (y1 < y) {
        int temp = recursive_distance(x1, y1 + 1, z1, x, y, z) + 1;
        if (temp < min_distance) min_distance = temp;
    }
    if (y1 > y) {
        int temp = recursive_distance(x1, y1 - 1, z1, x, y, z) + 1;
        if (temp < min_distance) min_distance = temp;
    }
    if (z1 < z) {
        int temp = recursive_distance(x1, y1, z1 + 1, x, y, z) + 1;
        if (temp < min_distance) min_distance = temp;
    }
    if (z1 > z) {
        int temp = recursive_distance(x1, y1, z1 - 1, x, y, z) + 1;
        if (temp < min_distance) min_distance = temp;
    }

    return min_distance;
}

void calculate_field(int x1, int y1, int z1, int x2, int y2, int z2, int x, int y, int z) {
    for (int i = 0; i <= z; i++) {
        for (int j = 0; j <= x; j++) {
            for (int k = 0; k <= y; k++) {
                int d1 = recursive_distance(j, k, i, x1, y1, z1);
                int d2 = recursive_distance(j, k, i, x2, y2, z2);
                field[i][j][k] = d1 < d2 ? d1 : d2;
            }
        }
    }
}

void print_field(int z, int x, int y) {
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j <= y; j++) {
            printw("%3d", field[z][i][j]);
        }
        printw("\n");
    }
}

int main() {
    setlocale(LC_ALL, "");

    int x, y, z, x1, y1, z1, x2, y2, z2;

    initscr();
    cbreak();
    noecho();

    printw("Введите размеры пространства:\n");
    printw("X (1 - 20): ");
    refresh();
    scanw("%d", &x);
    printw("Y (1 - 35): ");
    refresh();
    scanw("%d", &y);
    printw("Z (1 - 30): ");
    refresh();
    scanw("%d", &z);

    if (x <= 0 || y <= 0 || z <= 0 || x > 20 || y > 35 || z > 30) {
        printw("Некорректные размеры.\n");
        refresh();
        endwin();
        return 1;
    }

    printw("Введите координаты первой точки:\n");
    printw("X (0 - %d): ", x);
    refresh();
    scanw("%d", &x1);
    printw("Y (0 - %d): ", y);
    refresh();
    scanw("%d", &y1);
    printw("Z (0 - %d): ", z);
    refresh();
    scanw("%d", &z1);

    printw("Введите координаты второй точки:\n");
    printw("X (0 - %d): ", x);
    refresh();
    scanw("%d", &x2);
    printw("Y (0 - %d): ", y);
    refresh();
    scanw("%d", &y2);
    printw("Z (0 - %d): ", z);
    refresh();
    scanw("%d", &z2);

    calculate_field(x1, y1, z1, x2, y2, z2, x, y, z);

    clear();
    for (int i = 0; i <= z; i++) {
        printw("%d) Срез Z = %d:\n", i + 1, i);
        print_field(i, x, y);
        printw("\n");
    }

    refresh();
    printw("Нажмите любую клавишу для выхода...");
    getch();
    endwin();

    return 0;
}
