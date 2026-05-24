
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;
using namespace sf;

const int GRID_SIZE = 10; // Размер поля NxN
const int CELL_SIZE = 50;  // Размер одной ячейки в пикселях
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;

// Типы ячеек
enum CellType {
    EMPTY,
    OBSTACLE,
    START,
    END,
    PATH,
    VISITED
};

// Структура для представления ячейки
struct Cell {
    int x, y;
    CellType type;
    int f, g, h; // Для алгоритма A*
    Cell* parent;

    Cell(int x, int y) : x(x), y(y), type(EMPTY), f(0), g(0), h(0), parent(nullptr) {}

    // Перезагрузка оператора == для сравнения ячеек
    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator>(const Cell& other) const {                                   // перегрузка оператора >, используемая в a_star_algorithm().
        return f > other.f;
    }
};

        // Функция для вычисления эвристики (манхэттенское расстояние)
int heuristic(const Cell& a, const Cell& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);                           // из практики 11.
}

// Функция для проверки, находится ли ячейка в пределах сетки
bool isValid(int x, int y) {
    return ( (x < GRID_SIZE) && (y < GRID_SIZE) && (x >= 0) && (y >= 0));       // заемняет условие из практики 11.
}

auto a_star_algorithm(const std::vector<std::vector<Cell>>& grid, Cell start, Cell end){
    std::priority_queue<Cell, vector<Cell>, greater<Cell>> open_list;           // куча проверяемых клеток.
    std::set<pair<int, int>> closed_list;                                       // множество проверенных клеток.
    
    auto sec_grid = grid;                                                       // копия для работы с константной сеткой.
    
    // seс_grid[start.x][start.y].g = 0;
    sec_grid[start.x][start.y].h = heuristic(start, end);                       // расчёт примерной стоимости пути из start в end.
    
    open_list.push(sec_grid[start.x][start.y]);                                 // добавляем с тартовую клетку в "открытый список".
    
    while (!open_list.empty()){                                                 // до тех пор, пока открытый список не опустел,
        Cell current = open_list.top();                                         // берём (наименьший) элемент из верха кучи...
        open_list.pop();                                                        // ...и удаляем его из открытого списка.
        
        if (current.x == end.x && current.y == end.y){                          // берём конечную точку.
            std::vector<Cell> path;                                             // создаём вектор клеток для пути, который вернём.
            
            Cell* cell = &(sec_grid[current.x][current.y]);                     // перебирая "родителей", воссоздаём путь.
            while (cell){
                path.emplace_back(*cell);
                cell = cell->parent;
            }
            reverse(path.begin(), path.end());

            return path;
        }
        closed_list.insert({current.x, current.y});
        
        for (auto [dx, dy] : vector<pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
            int nx = current.x + dx;                                    // перебираем клетки сверху, снизу, справа, слева от текущей.
            int ny = current.y + dy;

            if ( (isValid(nx, ny) == true) &&                           // если в клетку можно перейти...
                sec_grid[nx][ny].type != OBSTACLE &&                    // ...она не является препятствием...
                closed_list.find({nx, ny}) == closed_list.end()) {      // ...и не находится в закрытом списке.

                int g = current.g + 1;                                  // оцениваем g переход в неё (и другие такие клетки) в 1.
                sec_grid[nx][ny].g = g;
                sec_grid[nx][ny].h = heuristic(sec_grid[nx][ny], end);  // даём эвристическую оценку.
                sec_grid[nx][ny].f = sec_grid[nx][ny].g + sec_grid[nx][ny].h;   // рассчитываем f.
                sec_grid[nx][ny].parent = &(sec_grid[current.x][current.y]);    // устанавливаем "родителя".
                
                open_list.push(sec_grid[nx][ny]);                       // добавляем в открытый список.
            }
        }
    }
    return std::vector<Cell>{};                                         // если не получилось.
}

void grid_generator(std::vector<std::vector<Cell>>& grid){              // генератор поля.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    std::uniform_int_distribution<> dis_coord(0, GRID_SIZE - 1);
    
    for (int x = 0; x < GRID_SIZE; ++x) {
        for (int y = 0; y < GRID_SIZE; ++y) {
            grid[x][y].type = EMPTY;
        }
    }
    
    for (int x = 0; x < GRID_SIZE; ++x) {
        for (int y = 0; y < GRID_SIZE; ++y) {
            if (dis(gen) < 25) {
                grid[x][y].type = OBSTACLE;
            }
        }
    }
    
    int startX = dis_coord(gen);
    int startY = dis_coord(gen);
    
    int endX;
    int endY;
    
    do {
        endX = dis_coord(gen);
        endY = dis_coord(gen);
    } while (startX == endX && startY == endY);

    grid[startX][startY].type = START;
    grid[endX][endY].type = END;
}


int main(){
    
    std::vector<std::vector<Cell>> grid;

    for (int x = 0; x < 10; ++x) {
        std::vector<Cell> column;
        for (int y = 0; y < 10; ++y) {
            column.emplace_back(x, y);
        }
        grid.push_back(column);
    }
    
    grid[4][0].type = OBSTACLE;         // карта 12-го варианта.
    grid[0][1].type = OBSTACLE;
    grid[7][1].type = OBSTACLE;
    grid[0][2].type = START;
    grid[2][3].type = OBSTACLE;
    grid[5][3].type = OBSTACLE;
    grid[6][3].type = OBSTACLE;
    grid[3][4].type = OBSTACLE;
    grid[4][4].type = OBSTACLE;
    grid[8][4].type = OBSTACLE;
    grid[9][4].type = OBSTACLE;
    grid[5][6].type = OBSTACLE;
    grid[8][6].type = OBSTACLE;
    grid[0][7].type = OBSTACLE;
    grid[1][7].type = OBSTACLE;
    grid[5][7].type = OBSTACLE;
    grid[8][7].type = OBSTACLE;
    grid[9][7].type = OBSTACLE;
    grid[0][8].type = OBSTACLE;
    grid[2][8].type = OBSTACLE;
    grid[5][8].type = OBSTACLE;
    grid[6][8].type = OBSTACLE;
    grid[0][9].type = OBSTACLE;
    grid[8][9].type = OBSTACLE;
    grid[9][9].type = END;
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "bowery electric");
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Space) {                        // обработка пробела.
                    
                    for (int x = 0; x < GRID_SIZE; x++) {
                        for (int y = 0; y < GRID_SIZE; y++) {
                            if (grid[x][y].type == PATH) grid[x][y].type = EMPTY;
                        }
                    }
                    
                    Cell start(0,0);
                    Cell end(0,0);
                    
                    Cell* start_p = &start;
                    Cell* end_p = &end;
                    
                    for (int x = 0; x < GRID_SIZE; x++){
                        for (int y = 0; y < GRID_SIZE; y++){
                            if (grid[x][y].type == START){
                                start_p->x = x;
                                start_p->y = y;
                            }
                            else if (grid[x][y].type == END){
                                end_p->x = x;
                                end_p->y = y;
                            }
                        }
                    }
                    
//                    Cell start = grid[0][2];
//                    Cell end = grid[9][9];
    
                    auto path = a_star_algorithm(grid, start, end);
    
                    for (auto& coords : path) {
                        int px = coords.x;
                        int py = coords.y;
                        if (grid[px][py].type != START && grid[px][py].type != END) {
                            grid[px][py].type = PATH;
                        }
                    }
                }
    
                if (event.key.code == sf::Keyboard::R) {                            // обработка "R".
                    grid_generator(grid);
                }
            }

            window.clear(sf::Color(162, 170, 173));
        }


        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                RectangleShape cell(Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                cell.setPosition(i * CELL_SIZE, j * CELL_SIZE);

                switch (grid[i][j].type) {
                    case EMPTY: cell.setFillColor(Color::White); break;
                    case OBSTACLE: cell.setFillColor(Color::Black); break;
                    case START: cell.setFillColor(Color::Green); break;
                    case END: cell.setFillColor(Color::Red); break;
                    case PATH: cell.setFillColor(Color::Blue); break;
                    case VISITED: cell.setFillColor(Color::Cyan); break;
                }

                window.draw(cell);
            }
            
        }
        
        window.display();
    }
}
