#include <iostream>
#include <string>

class Car {
    private:

    public:
        std::string marka;
        std::string tipus;
        int evjarat;
        Car() {};
        Car(std::string x, std::string y, int z) {
            marka = x;
            tipus = y;
            evjarat = z;
            std::cout << "Constructor has been called" << std::endl;
        };

        ~Car() {
            std::cout << "It's over. Isn't it. Isn't it over." << std::endl;
        }
};

class Writer {
    public:
        void greet() {
            std::cout << "Hello world" << std::endl;
        }
        void greet2();
};

void Writer::greet2() {
    std::cout << "Hello world" << std::endl;
}

int main(void) {

    Car car1 = Car("Opel", "Astra", 2018);

    Writer w;
    w.greet();

    return 0;
}

// szorgalmi
/**
 * Karakter osztaly
 * x, y coordinate
 * is_blocked
 * move()
 * 
 * Gyumolcs osztaly
 * x, y coordinate
 * 
 * Rago osztaly
 * x, y coords
 * continue for 3 iteration
 * 
 * 
 * walking on a grid
 * how many iterations can it find the 5 hidden fruits
 * 
 * 
 * 2. 
 * 
 * 10 car in a vec
 * autok rendezese marka tipus evjarat ar szerint
 * 
 * 3.
 * titkositott e.c-vel
 * 4.
 * un titkositas 
*/