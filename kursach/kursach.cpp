#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

const int FIELD_SIZE = 20;
const int INITIAL_RABBITS = 10;
const int INITIAL_WOLVES = 5;
const int INITIAL_FOXES = 3;

int rabbit_count = 0;

// Структура для представлення тварин
struct Animal {
    int type;  // 0 - кролик, 1 - вовк, 2 - вовчиця
    int points;
};

// Функція для генерації випадкових чисел
int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Функція для ініціалізації популяції тварин
void initializeAnimals(Animal island[FIELD_SIZE][FIELD_SIZE]) {
    // Ініціалізуємо всі комірки острова зі значеннями -1 (порожньо)
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            island[i][j].type = -1;
            island[i][j].points = 0;
        }
    }

    // Розміщуємо початкову кількість тварин на острові
    int count = 0;

    while (count < INITIAL_RABBITS) {
        int x = getRandomNumber(0, FIELD_SIZE - 1);
        int y = getRandomNumber(0, FIELD_SIZE - 1);

        if (island[x][y].type == -1) {
            island[x][y].type = 0;
            island[x][y].points = 1;
            count++;
            rabbit_count++;
        }
    }

    count = 0;

    while (count < INITIAL_WOLVES) {
        int x = getRandomNumber(0, FIELD_SIZE - 1);
        int y = getRandomNumber(0, FIELD_SIZE - 1);

        if (island[x][y].type == -1) {
            island[x][y].type = 1;
            island[x][y].points = 1;
            count++;
        }
    }

    count = 0;

    while (count < INITIAL_FOXES) {
        int x = getRandomNumber(0, FIELD_SIZE - 1);
        int y = getRandomNumber(0, FIELD_SIZE - 1);

        if (island[x][y].type == -1) {
            island[x][y].type = 2;
            island[x][y].points = 1;
            count++;
        }
    }
}

// Функція для руху кроликів
void moveRabbits(Animal island[FIELD_SIZE][FIELD_SIZE]) {
    int newX, newY;

    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (island[i][j].type == 0) {
                int direction = getRandomNumber(0, 8);

                switch (direction) {
                case 0:  // Вліво
                    newX = i - 1;
                    newY = j;
                    break;
                case 1:  // Вправо
                    newX = i + 1;
                    newY = j;
                    break;
                case 2:  // Вгору
                    newX = i;
                    newY = j - 1;
                    break;
                case 3:  // Вниз
                    newX = i;
                    newY = j + 1;
                    break;
                case 4:  // Вліво-вгору
                    newX = i - 1;
                    newY = j - 1;
                    break;
                case 5:  // Вліво-вниз
                    newX = i - 1;
                    newY = j + 1;
                    break;
                case 6:  // Вправо-вгору
                    newX = i + 1;
                    newY = j - 1;
                    break;
                case 7:  // Вправо-вниз
                    newX = i + 1;
                    newY = j + 1;
                    break;
                default:
                    newX = i;
                    newY = j;
                    break;
                }

                // Перевіряємо, чи нові координати є в межах острова і чи є ця клітинка порожньою
                if (newX >= 0 && newX < FIELD_SIZE && newY >= 0 && newY < FIELD_SIZE && island[newX][newY].type == -1) {
                    island[newX][newY].type = 0;
                    island[newX][newY].points = 1;
                    island[i][j].type = -1;
                    island[i][j].points = 0;
                }
            }
        }
    }
}

// Функція для переміщення вовчиць і вовків
void movePredators(Animal island[FIELD_SIZE][FIELD_SIZE]) {
    int newX, newY;

    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (island[i][j].type == 1 || island[i][j].type == 2) {
                int direction = getRandomNumber(0, 8);

                switch (direction) {
                case 0:  // Вліво
                    newX = i - 1;
                    newY = j;
                    break;
                case 1:  // Вправо
                    newX = i + 1;
                    newY = j;
                    break;
                case 2:  // Вгору
                    newX = i;
                    newY = j - 1;
                    break;
                case 3:  // Вниз
                    newX = i;
                    newY = j + 1;
                    break;
                case 4:  // Вліво-вгору
                    newX = i - 1;
                    newY = j - 1;
                    break;
                case 5:  // Вліво-вниз
                    newX = i - 1;
                    newY = j + 1;
                    break;
                case 6:  // Вправо-вгору
                    newX = i + 1;
                    newY = j - 1;
                    break;
                case 7:  // Вправо-вниз
                    newX = i + 1;
                    newY = j + 1;
                    break;
                default:
                    newX = i;
                    newY = j;
                    break;
                }

                // Перевіряємо, чи нові координати є в межах острова
                if (newX >= 0 && newX < FIELD_SIZE && newY >= 0 && newY < FIELD_SIZE) {
                    // Якщо в сусідній клітинці є кролик, то вовк чи вовчиця йде в ту сторону
                    if (island[newX][newY].type == 0) {
                        island[newX][newY].type = island[i][j].type;
                        island[newX][newY].points = island[i][j].points + 1;
                        island[i][j].type = -1;
                        island[i][j].points = 0;
                        rabbit_count--;
                    }
                    // Якщо вовк і вовчиця знаходяться в одній клітинці і там немає кролика, вони додають нового нащадка
                    else if (island[newX][newY].type == 1 || island[newX][newY].type == 2) {
                        int offspringType = getRandomNumber(1, 2);  // Випадково вибираємо тип нащадка: 1 - вовк, 2 - вовчиця
                        int offspringX, offspringY;

                        // Шукаємо порожню клітинку навколо
                        bool foundEmptyCell = false;
                        for (int k = -1; k <= 1; k++) {
                            for (int l = -1; l <= 1; l++) {
                                offspringX = newX + k;
                                offspringY = newY + l;

                                if (offspringX >= 0 && offspringX < FIELD_SIZE && offspringY >= 0 && offspringY < FIELD_SIZE && island[offspringX][offspringY].type == -1) {
                                    foundEmptyCell = true;
                                    break;
                                }
                            }

                            if (foundEmptyCell) {
                                break;
                            }
                        }

                        // Додаємо нащадка
                        if (foundEmptyCell) {
                            island[offspringX][offspringY].type = offspringType;
                            island[offspringX][offspringY].points = 1;
                        }
                    }
                }
            }
        }
    }
}

// Функція для оновлення популяції
void updatePopulation(Animal island[FIELD_SIZE][FIELD_SIZE]) {
    moveRabbits(island);
    movePredators(island);
}

// Функція для виводу стану популяції на екран
void printPopulation(Animal island[FIELD_SIZE][FIELD_SIZE]) {
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (island[i][j].type == -1) {
                std::cout << "- ";
            }
            else {
                std::cout << island[i][j].type << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Ribbit count: " << rabbit_count;
}

int main() {
    srand(time(NULL));  // Ініціалізація генератора випадкових чисел

    Animal island[FIELD_SIZE][FIELD_SIZE];

    initializeAnimals(island);
    printPopulation(island);

    while (true) {
        system("cls");

        if (rabbit_count <= 0)
        {
            std::cout << "All rabbits died" << std::endl;
            system("pause");
            return 0;
        }

        updatePopulation(island);
        printPopulation(island);
        Sleep(700);
    }

    return 0;
}
