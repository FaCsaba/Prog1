// PUBLIC PRIVATE PROTECTED
#include <iostream>

class Animal {
    public:
        std::string name;
        int age;
        
        void setAge(int age) {
            this->age = age;
        }

    private:
        int weight;
};

class Termek {
    protected:
        int azon;
        int ar;
        std::string lejarat;
    

    public:
        Termek() { }

        Termek(int azon, int ar, std::string lejarat) {
            this->azon = azon;
            this->ar = ar;
            this->lejarat = lejarat;
        }
        int getAzon() {
            return azon;
        }

        void setAzon(int azon) {
            this->azon = azon;
        }

        int getAr() {
            return ar;
        }

        void setAr(int ar) {
            this->ar = ar;
        }

        std::string getLejarat() {
            return lejarat;
        }

        void setLejarat(std::string lejarat) {
            this->lejarat = lejarat;
        }

    ~Termek() { }
};

class Etel : public Termek {
    private:
        std::string osszetevok;
        double suly;
    public:
        std::string getOsszetevok() {
            return osszetevok;
        }

        void setOsszetevok(std::string osszetevok) {
            this->osszetevok = osszetevok;
        }

        int getSuly() {
            return suly;
        }

        void setSuly(int suly) {
            this->suly = suly;
        } 
    Etel() { }

    Etel(int azon, int ar, std::string, std::string osszetevok, double suly) {
        this->azon = azon;
        this->ar = ar;
        this->lejarat = lejarat;
        this->osszetevok = osszetevok;
        this->suly = suly;
    }
    
    ~Etel() { }
};

class Ital : public Termek {
    private:
        int mennyiseg;
        std::string szin;
    public:
        std::string getSzin() {
            return szin;
        }

        void setSzin(std::string szin) {
            this->szin = szin;
        }

        int getMennyiseg() {
            return mennyiseg;
        }

        void setMennyiseg(int mennyiseg) {
            this->mennyiseg = mennyiseg;
        } 
    Ital() { }

    Ital(int azon, int ar, std::string lejarat, int mennyiseg, std::string szin) {
        this->azon = azon;
        this->ar = ar;
        this->lejarat = lejarat;
        this->mennyiseg = mennyiseg;
        this->szin = szin;
    }

    ~Ital() { }
};

std::ostream& operator<<(std::ostream& os, Etel e) {
    os << e.getAzon() << " " << e.getAr() << " " << e.getLejarat() << " " << e.getOsszetevok() << " " << e.getSuly();
    return os;
}

int main(void) {
    Termek t(1, 10, "2023.04");
    Etel e(2, 20, "2025.01", "liszt", 1.3);
    Ital i(3, 15, "2024.06", 200, "kek");

    std::cout << e << std::endl;

    return 0;
}