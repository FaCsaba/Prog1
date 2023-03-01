#include <iostream>
#include <string>

void inc(int* a) {
    (*a)++;
}

void change(int* a) {
    *a = 3;
}

int main() {
    struct {
        int birth_year;
        std::string name;
    } person1, person2;
    person1.birth_year = 2000;
    person1.name = "Bela";

    person2 = person1;

    std::cout << person1.name << " " << person1.birth_year << std::endl;

    std::cout << person2.name << " " << person2.birth_year << std::endl;

    person1.name = "John";

    std::cout << person1.name << " " << person1.birth_year << std::endl;

    std::cout << person2.name << " " << person2.birth_year << std::endl;

    struct Car {
        std::string brand;
        std::string t;
        short int year;
    };

    Car swift;
    swift.brand = "Suzuki";
    swift.t = "Swift";
    swift.year = 2002;

    Car civic;
    swift.brand = "Honda";
    swift.t = "Civic";
    swift.year = 2009;

    if (swift.year > civic.year) {
        std::cout << "The " << swift.t << " is younger" << std::endl;
    } else {
        std::cout << "The " << civic.t << " is younger" << std::endl;    
    }

    std::string st = "orange";
    std::string& fruit = st;

    std::cout << st << " " << fruit << std::endl;
    st = "kiwi";
    std::cout << st << " " << fruit << std::endl;

    std::cout << &st << " " << &fruit << std::endl;

    // they use the same memory address

    std::cout << &civic << " " << &civic.brand << " " << &civic.t << " " << &civic.year << std::endl;

    int a = 10;

    int *p = &a;

    int *c = (int *) a;

    std::cout << a << " " << &a << " " << p << " " << &p << std::endl;
    (*p)++;
    std::cout << *p << std::endl;
    std::cout << sizeof(p) << std::endl;

    // it doesn't point at anything
    int *prt = NULL;

    if (prt) {
        // the pointer is not null
        std::cout << "The pointer isn't null" << std::endl;
    } else {
        std::cout << "It is null" << std::endl;
    }

    int arr[] = {1, 2, 3, 4, 5};
    int *arr_ptr;

    arr_ptr = arr;

    std::cout << arr << " " << &arr[0] << std::endl;
    std::cout << arr_ptr << std::endl;

    for (int i = 0; i < 5; i++) {
        std::cout << arr_ptr << " " << *arr_ptr << std::endl;
        arr_ptr++;
    }

    arr_ptr = &arr[4];
    for (int i = 5; i > 0; i--) {
        std::cout << arr_ptr << " " << *arr_ptr << std::endl;
        arr_ptr--;
    }

    arr_ptr = arr;
    std::cout << std::endl;

    while (arr_ptr <= &arr[4]) {
        std::cout << arr_ptr << " " << *arr_ptr << std::endl;
        arr_ptr++;
    }

    *(arr+4) = 500;

    std::cout << arr[4] << std::endl;

    for (int i = 0; i<5; i++) {
        *(arr+i) = 1;
        // arr++;
        std::cout << *(arr+i) << std::endl;
    }

    int* ptr_arr[5];
    for (int i = 0; i < 5; i++) {
        ptr_arr[i] = &arr[i];
        std::cout << *ptr_arr[i] << " " << ptr_arr[i] << std::endl;
    }

    char *s = "Hello, World!";
    char *names[3] = {"Bela", "Katrina", "James"};
    for (int i = 0; i < 3; i++)
    {
        std::cout << *(names+i) << std::endl;
    }
    
    int z = 1;
    int *z_ptr = &z;
    int **z_p_ptr = &z_ptr;

    std::cout << z << " " << *z_ptr << " " << **z_p_ptr << std::endl;

    // *p++, *(p++) | dereference p, and pointer increment
    // *++p, *(++p) | pointer increment, and dereference p
    // ++*p, ++(*p) | deference p, and increment value
    // (*p)++       | dereference p, and increment value after

    int arr_2[5] = {1, 2, 3, 4, 5};
    std::swap(*arr_2, *(arr_2+4));

    for (int i = 0; i < 5; i++) {

    }

    int b = 10;
    int *b_ptr = &b;
    std::cout << b << " " << b_ptr << std::endl;
    (*b_ptr)++;
    std::cout << b << " " << b_ptr << std::endl;


    int arr_3[5] = {1, 2, 3, 4, 5};
    int arr_4[5];

    int *arr_ptr_asdf = arr_3;

    for(int i = 0; i < 5; i++) {
        *(arr_4+i) = *arr_ptr_asdf++;
        std::cout << arr_4[i] << std::endl;
    }


    // homework2
    int tomb[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // indexing is forbidden
    // bubble sort
}