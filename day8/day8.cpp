#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

class Animal {
    public:
        std::string name;
        unsigned int age;

        // static int num_of_obj; // at the level of the class

        void move() {
            std::cout << name << " moved." << std::endl;
        }

        void befriend(Animal b);

        Animal() { }

        Animal(std::string n) {
            name = n;
            age = 0;
        }

        // full constructor
        // this pointer to current object
        Animal(std::string name, unsigned int age) {
            this->name = name;
            this->age = age;
            // num_of_obj++;
        }
};

// std::ostream& operator<<(std::ostream& s, Animal& a) {
//     s << a.name << " " << a.age;
//     return s;
// }

// int Animal::num_of_obj = 0;

void Animal::befriend(Animal b) {
    std::cout << name << " and " << b.name << " are now friends. Isn't that nice?" << std::endl;
}

class Dog : public Animal {
    public:
        std::string color;
        std::string favorite_toy;

        void bark() {
            std::cout << "Vau Vau" << std::endl;
        }

        // full constructor
        Dog(std::string name, int age, std::string color, std::string fav_toy) {
            this->name = name;
            this->age = age;
            this->color = color;
            this->favorite_toy = fav_toy;
        }

        ~Dog() { }
};

std::string older_animal(Animal a, Animal b) {
    return a.age > b.age ? a.name : b.name;
}

std::string oldest(std::vector<Animal> animals) {
    assert(animals.size() > 0 && "Can't find oldest if there aren't any animals to find");
    Animal a = animals.front();
    for ( auto animal : animals ) {
        a = a.age > animal.age ? a : animal;
    }
    return a.name;
}

std::string youngest(std::vector<Animal> animals) {
    assert(animals.size() > 0 && "Can't find youngest if there aren't any animals to find");
    Animal a = animals.front();
    for ( auto animal : animals ) {
        a = a.age < animal.age ? a : animal;
    }
    return a.name;
}

int main(void) {
    Animal a("asdf");
    a.name = "Blocky";
    a.age = 10;


    // std::cout << a.name << " " << a.age << std::endl;
    a.move();

    Animal b("Cirmi", 7);

    // Cirmi gets copied and that is why we see b get destroyed twice
    // a.befriend(b);

    Animal c("Dinner");
    // std::cout << c.name << " " << c.age << std::endl;


    Animal d("Blöki", 3);
    // std::cout << d.name << " " << d.age << std::endl;

    Dog doug("Doug", 5, "", "");
    std::cout << older_animal(d, doug) << std::endl;

    std::vector<Animal> animals;
    animals.push_back(a);
    animals.push_back(b);
    animals.push_back(c);
    animals.push_back(d);
    animals.push_back(doug);


    for ( auto animal : animals ) {
        std::cout << animal.name << std::endl;
    }

    std::cout << oldest(animals) << " " << youngest(animals) << std::endl;

    return 0;
}