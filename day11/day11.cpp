#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Animal {
    public:
        std::string name;
        int age;
};

void operator>>(std::istream &i, Animal &a) {
    i >> a.name >> a.age;
}

int input(void) {
    int x, y;
    int sum;

    std::cout << "Give me an integer: ";
    std::cin >> x;
    std::cout << "Give me another integer: ";
    std::cin >> y;
    
    sum = x + y;
    std::cout << "Sum of those two: " << sum << std::endl;

    Animal a;
    std::cin >> a;
    std::cout << a.name << " " << a.age << std::endl;

    return 0;
}

// int harder_input(void) {
//     // prompt the user to input an int
//     // prompt input for that amount of animals
//     std::vector<Animal> animals;
//     int animal_amount;
//     std::cout << "How many animals: ";
//     std::cin >> animal_amount;
//     for (int i = 0; i < animal_amount; i++) {
//         Animal temp;
//         std::cin >> temp;
//         animals.push_back(temp);
//     }

//     for (int i = 0; i < animal_amount; i++)
//     {
//         std::cout << animals[i].name << " " << animals[i].age << std::endl;
//     }
    
//     return 0;
// }

int reading_and_writing_stuff(void) {

    /**
     * ofstream - creates, writes
     * ifstream - reads
     * fstream - creates, reads, writes
    */

   std::ofstream file1("temp"); // creates temp and opens file

    file1 << "We input something" << std::endl;
    file1 << "We input something" << std::endl;
    file1 << "We input something" << std::endl;

    file1.close();

    std::ifstream file2("temp");
    std::string text;
    while (getline(file2, text)) {
        std::cout << text << std::endl;
    }

    file2.close();

    return 0;
}

int feladat() {
    // ask for users name
    // write that to file
    // read from there

    std::string name;
    std::cout << "What is your name: ";
    std::cin >> name;

    std::ofstream file1("temp");
    file1 << name;
    file1.close();
    
    std::ifstream file2("temp");
    std::string text;
    getline(file2, text);
    file2.close();
    
    std::cout << text;

    std::fstream f;
    f.open("temp");
    f >> text;
    f.close();
    return 0;
}

int main(void) {
     /**
     * ios::app Append
     * ios::in input
     * ios::out output
     * ios trunc Truncate
    */
    std::vector<Animal> animals;
    int animal_amount;
    std::cout << "How many animals: ";
    std::cin >> animal_amount;
    for (int i = 0; i < animal_amount; i++) {
        Animal temp;
        std::cin >> temp;
        animals.push_back(temp);
    }

    for (int i = 0; i < animal_amount; i++)
    {
        std::cout << animals[i].name << " " << animals[i].age << std::endl;
    }

    std::ofstream f("animals.txt");
    for (int i = 0; i < animal_amount; i++) {
        f << animals[i].name << std::endl;
        f << animals[i].age << std::endl;
    }

    f.close();

    std::ifstream f2("animals.txt");
    std::vector<Animal> another_animals;
    for (int i = 0; i < animal_amount; i++) {
        Animal temp;
        f2 >> temp.name;
        f2 >> temp.age;
        another_animals.push_back(temp);
    }

    for (int i = 0; i < animal_amount; i++)
    {
        std::cout << another_animals[i].name << " " << another_animals[i].age << std::endl;
    }

    return 0;
}

