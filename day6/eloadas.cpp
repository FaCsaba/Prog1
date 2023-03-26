#include <iostream>
#include <string>

using namespace std;

class Worker {
    public:
        float pay = 6000;
        void print_pay() {cout << pay << endl;}
    protected:
        int id;
};

class Programmer : public Worker {
    public:
        float bonus = 5000;
        void print_id() {cout << id << endl;}
        int get_id() {return id;}
        void set_id(int id_new) { id = id_new; }
};

class A {
    protected:
        int a;
    public:
        void set_a(int n) {
            a = n;
        }
};

class B {
    protected:
        int b;
    public:
        void set_b(int n) {
            b = n;
        }

};

class C : public A, public B {
    public:
        void print() {
            cout << a << " " << b << endl;
        }
};

class Os {
    public:
        virtual void print() {
            cout << "Hi from Ancient class print" << endl;
        }

        void show() {
            cout << "Hi from Ancient class show" << endl;
        }
};

class Ch : public Os {
    public:
        void print() {
            cout << "Hi from Child class print" << endl;
        }

        void show() {
            cout << "Hi from Child class show" << endl;
        }

};

class AbstractClass {
    public:
        virtual void pure_virtual() = 0;
        void print() {
            cout << "No hi from Abstract, cuz it won't compile" << endl;
        }
};

class ChOfAb : public AbstractClass {
    public:
        void pure_virtual() {
            cout << "asdf" << endl;
        }
};

int main(void) {

    Programmer p1;
    cout << p1.pay << " " << p1.bonus << " " << p1.get_id()  << endl;
    p1.print_pay();
    p1.set_id(69);
    p1.print_id();

    C c;
    c.print();

    Os* osptr;
    Ch ch;
    osptr = &ch;

    osptr->print();
    osptr->show();

    // AbstractClass ac;
    ChOfAb chab;
    chab.pure_virtual();



    return 0;
}