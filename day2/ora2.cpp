#include <iostream>

int main(void) {
    char cstring[] = "Hello, World!";
    std::string st = "cpp string";

    // std namespace;
    std::cout << st << std::endl;

    using namespace std;
    cout << st << std::endl;

    // type casting
    // implicit
    int num = 50;
    double d2 = num;

    cout << d2 << endl;

    d2 = 1.6111;
    num = d2;

    cout << num << endl;

    int z = 20;
    double zs;

    zs = (double) z;

    // IF
    if (true) {
        cout << "It's true, baby" << endl;
    } else {
        cout << "Well, this is awkward" << endl;
    }

    // turnery operator
    int cif = 9 > 10 ? 1 : 0;

    int x1 = 1;
    int x2 = 10;

    string eredmeny;

    eredmeny = (x1 == x2) ? "egyenlő" : (x1 > x2) ? "nagyobb" : "kisseb";

    cout << eredmeny << endl;

    int dow = 3; // Day of the week
    switch (dow) {
        case 6:
            cout << "Weekend" << endl;
            break;
        
        case 7:
            cout << "Still the weekend" << endl;

        default:
            cout << "Almost the weekend" << endl;
    }

    int i = 0;
    while (i < 10) { // forward testing loop
        cout << i << endl;
        i++;
    }

    do { // back testing loop, at least once it will loop
        i++;
        cout << i << endl;
    } while (i < 10);

    // initialize the loop variable; exit condition; loop variable change
    // forward testing loop
    for (int i = 0; i < 10; i++) {
        cout << i << endl;
    }

    int nums[] = {1,2,3,4,5};

    for (int i = 0; i < 5; i++) {
        ;
    }

    for (int s : nums) { // is this cpp specific?
        cout << s << endl;
    }

    char characters[2][4] = {
        {'a', 'b', 'c', 'd'},
        {'e', 'f', 'g', 'h'}
    };

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 4; j++) {
            cout << characters[i][j] << endl;
        }
    }    
    
    int numbers[3][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9,  10, 11, 12}
    };

    for(int i = 0; i < 3; i++) {
        int sum = 0;
        for(int j = 0; j < 4; j++) {
            sum += numbers[i][j];    
        }
        cout << (sum / 4) << endl;
    }

    // homework
    // 1 2 3 4
    // 5 6 7 8
    // 9 10 11 12
    // soronkenti maximum
    // tombonkenti maximum
    // ciklus 100 csokken 3mal oszthato
    // ciklus 300 novekvo 2 hatvanyok

    // soronkenti max
    for (int i = 0; i < sizeof(numbers)/sizeof(int); i++) {

    }

    return 0;
}