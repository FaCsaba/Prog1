#include <iostream>
#include <string>
#include <vector>

using namespace std;

int add(int a, int b) {
    return a+b;
}

double add(double a, double b) {
    return a+b;
}

int test() { return 0; }
int test(int a) { return 0; }
float test(double a) { return 0.0f; }
int test(int a, double b) { return 0; }

// these generate compiler errors
// int test(int b) { return 0; }
// double test() { return 0.0f; }

float absolute(float a) {
    if (a < 0.0f) a = -a;
    return a;
}

int absolute(int a) {
    if (a < 0) a = -a;
    return a;
}

vector<int>& operator<<(vector<int>& a, int b) {
    a.push_back(b);
    return a;
}

void operator<<(ostream &a, vector<int> b) {
    for (int item : b)
    {
        a << item << endl;
    }
}

vector<int> operator<<(vector<int> a, vector<int> b) {
    vector<int> out;
    for (int a_item : a) {
        out << a_item;
    }
    for (int b_item : b) {
        out << b_item;
    }
    return out;
}

vector<int> operator+(vector<int> a, vector<int> b) {
    vector<int> out;
    for (int a_item : a) {
        out << a_item;
    }
    for (int b_item : b) {
        out << b_item;
    }
    return out;
}

void operator++(vector<int> v) {
    for (int i : v) {
        cout << i << " ";
    }
    cout << endl;
}

vector<int>& operator--(vector<int>& v) {
    for (int& i : v) {
        cout << --i << " ";
    }
    cout << endl;
    return v;
}

struct person {
    string name;
    int age;
};

ostream& operator<<(ostream &a, person& p) {
    a << p.name << " " << p.age << endl;
    return a;
}

// polymorphism on the level of the compiler
int main(void) {
    cout << add(1, 3) << " " << add(1.3, 4.5) << endl;
    cout << absolute(1) << " " << absolute(-1.1f) << endl;

    vector<int> v = {0,1,2};
    v.push_back(3);
    v.push_back(4);

    v << 5 << 6 << 7;

    // cout << v;

    vector<int> v2 = {6,7,8};
    vector<int> vo = v + v2;

    cout << v;
    ++--------v;

    person p;
    p.name = "John";
    p.age = 45;

    cout << p << p;


    return 0;
}