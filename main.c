#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ncurses.h>


int field[30][20][35];

// вычисление расстояния между двумя точками
int recursive_distance(int x1, int y1, int z1, int x, int y, int z) {
    // если точки совпали
    if (x1 == x && y1 == y && z1 == z) {
        return 0;
    }
    // расстояние для сравнения
    int disnatce = 1000000;

    // перемещение по осям
    if (x1 < x) { // вправо
        disnatce = recursive_distance(x1 + 1, y1, z1, x, y, z) + 1;
    }
    if (x1 > x) { // влево
        int temp = recursive_distance(x1 - 1, y1, z1, x, y, z) + 1;
        if (temp < disnatce) disnatce = temp;
    }
    if (y1 < y) { // вниз
        int temp = recursive_distance(x1, y1 + 1, z1, x, y, z) + 1;
        if (temp < disnatce) disnatce = temp;
    }
    if (y1 > y) { // вверх
        int temp = recursive_distance(x1, y1 - 1, z1, x, y, z) + 1;
        if (temp < disnatce) disnatce = temp;
    }
    if (z1 < z) { // вперёд
        int temp = recursive_distance(x1, y1, z1 + 1, x, y, z) + 1;
        if (temp < disnatce) disnatce = temp;
    }
    if (z1 > z) { // назад
        int temp = recursive_distance(x1, y1, z1 - 1, x, y, z) + 1;
        if (temp < disnatce) disnatce = temp;
    }

    return disnatce;//ответ
}

// заполнение массива
void calculate_field(int x1, int y1, int z1, int x2, int y2, int z2, int x, int y, int z) {
    for (int i = 0; i <= z; i++) {
        for (int j = 0; j <= x; j++) {
            for (int k = 0; k <= y; k++) {

                int d1 = recursive_distance(j, k, i, x1, y1, z1);
                int d2 = recursive_distance(j, k, i, x2, y2, z2);
                // минимальное из двух полученных расст-й
                if (d1 < d2) {
                    field[i][j][k] = d1;
                } else {
                    field[i][j][k] = d2;
                }

            }
        }
    }
}

// вывод на уровнях z
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

    printw("Введите размеры пространства:\n");
    printw("X (1 - 20): ");
    scanw("%d", &x);
    printw("Y (1 - 35): ");
    scanw("%d", &y);
    printw("Z (1 - 30): ");
    scanw("%d", &z);


    if (x <= 0 || y <= 0 || z <= 0 || x > 20 || y > 35 || z > 30) {
        printw("Некорректные размеры.\n");
        endwin();
        return 1;
    }


    printw("Введите координаты первой точки:\n");
    printw("X (0 - %d): ", x);
    scanw("%d", &x1);
    printw("Y (0 - %d): ", y);
    scanw("%d", &y1);
    printw("Z (0 - %d): ", z);
    scanw("%d", &z1);


    printw("Введите координаты второй точки:\n");
    printw("X (0 - %d): ", x);
    scanw("%d", &x2);
    printw("Y (0 - %d): ", y);
    scanw("%d", &y2);
    printw("Z (0 - %d): ", z);
    scanw("%d", &z2);


    clear();


    calculate_field(x1, y1, z1, x2, y2, z2, x, y, z);

    // срезы
    for (int i = 0; i <= z; i++) {
        printw("%d) Срез Z = %d:\n", i + 1, i);
        print_field(i, x, y);
        printw("\n");
    }


    printw("Нажмите любую клавишу для выхода...");
    getch();

    return 0;
}
