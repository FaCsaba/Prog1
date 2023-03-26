#include <vector>
#include <iostream>
#include <assert.h>
#include <random>
#include <ctime>
#include <thread>

enum Object {
    FRUIT,
    BUBBLEGUM,
    EMPTY
};


class Pos {
    public:
        int x, y;
        Pos() {x, y = 0, 0;}
        Pos(int _x, int _y) {
            x = _x; 
            y = _y;
        }
};

bool operator==(Pos pos1, Pos pos2) {
    return pos1.x == pos2.x && pos1.y == pos2.y;
}

class Character {
    public:
        Pos pos = Pos(0, 0);
        bool is_blocked;
        void move(int width, int height) {
            if (!is_blocked)
                pos = Pos((pos.x+1) % width, pos.x+1 >= width ? pos.y+1 : pos.y);
        }
}; 

template<typename T>
std::vector<T> flatten(std::vector<std::vector<T>> const &vec)
{
    std::vector<T> flattened;
    for (auto const &v: vec) {
        flattened.insert(flattened.end(), v.begin(), v.end());
    }
    return flattened;
}

class Board {
    public:
        Pos size;
        int fruit_collected = 0;
        int iteration = 0;
        int blocked_for = 0;
        Character character;
        std::vector<std::vector<Object>> objects;

        Board(int width, int height, int num_of_gum) {
            size.x = width;
            size.y = height;
            int fruit_to_place = 5;
            int gum_to_place = num_of_gum;
            for ( int y = 0; y < height; y++ ) {
                std::vector<Object> row;
                for ( int x = 0; x < width; x++ ) {
                    if (fruit_to_place > 0) {
                        row.push_back(Object::FRUIT);
                        fruit_to_place--;
                    } else if (gum_to_place > 0) {
                        row.push_back(Object::BUBBLEGUM);
                        gum_to_place--;
                    } else {
                        row.push_back(Object::EMPTY);
                    }
                }
                objects.push_back(row);
            }
            shuffle_objs();
        }

        void game_loop() {
            while(fruit_collected < 5) {
                print();
                int curr_x = character.pos.x;
                int curr_y = character.pos.y;
                switch (objects[curr_y][curr_x])
                {
                case Object::EMPTY:
                    break;
                
                case Object::BUBBLEGUM:
                    character.is_blocked = true;
                    blocked_for = 3;
                    break;
                
                case Object::FRUIT:
                    fruit_collected++;
                    if (fruit_collected >= 5) {break;}
                    break;

                default:
                    assert(0 && "Unreachable");
                    break;
                };
                objects[curr_y][curr_x] = Object::EMPTY;
                if (blocked_for > 0) {
                    blocked_for--;
                } else {
                    character.is_blocked = false;
                }
                character.move(size.x, size.y);
                iteration++;
                
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(200ms);
            }
            print();
            std::cout << "Won the game in " << iteration << " iterations!";
        }
    private:
        void print() {
            std::cout << (char) 27 << "[2J" << (char) 27 << "[1;1H";
            std::cout << "Fruit collected: " << fruit_collected << "; Iteration: " << iteration << std::endl;
            int x = 0; 
            int y = 0;
            for ( auto col : objects ) {
                for ( auto obj : col) {
                    if (character.pos == Pos(x, y)) {
                        std::cout << "🧍";
                    } else {
                        switch (obj)
                        {
                        case Object::EMPTY:
                            std::cout << "x ";
                            break;
                        
                        case Object::BUBBLEGUM:
                            std::cout << "🍬 ";
                            break;
                        case Object::FRUIT:
                            std::cout << "🍎 ";
                            break;
                        };
                    }
                    x++;
                }
                std::cout << "\n";
                x = 0;
                y++;
            }
        }
        int check_amount_of_object(Object o) {
            int ret = 0;
            for ( std::vector<Object> rows : objects ) {
                for ( Object col : rows) {
                    if (col == o) ret++;
                }
            }
            return ret;
        }
        void shuffle_objs() {
            std::vector<Object> objs = flatten(objects);
            for (int k = 0; k < objs.size(); k++) {
                int r = k + rand() % (objs.size() - k);
                std::swap(objs[k], objs[r]);
            }
            for ( int y = 0; y < size.y; y++ ) {
                for ( int x = 0; x < size.x; x++ ) {
                    objects[y][x] = objs[y*size.x+x];
                }
            }
        }
};

int main(void) {
    std::srand((unsigned) time(0));
    Board b = Board(10, 10, 5);
    b.game_loop();
    return 0;
}