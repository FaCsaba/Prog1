#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

int divisible_by_3_and_5(int a, int b) {
    for (int i = a+1; i < b; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            return i;
        }
    }
    return 0;
}

std::vector<int> flat_bigger_than_25(std::vector<std::vector<int>> v) {
    std::vector<int> flat;
    for (auto inner_vec : v) {
        for (auto num : inner_vec) {
            if (num > 25)
                flat.push_back(num);
        }
    }
    return flat;
}

void sort_3(int& a, int& b, int& c) {
    if (a > b) {
        std::swap(a, b);
    }
    if (a > c) {
        std::swap(a, c);
    }
    if (b > c) {
        std::swap(b, c);
    }
}

double average_str_len(std::vector<std::string> strings) {
    int sum = 0;
    for (auto str : strings) {
        sum += str.length();
    }

    return sum / 5;
}

void task4() {
    int a;
    std::cin >> a;
    std::vector<std::string> strings; 
    for (int i = 0; i < 5; i++) {
        std::string temp;
        std::cin >> temp;
        strings.push_back(temp);
    }
    double avg_len = average_str_len(strings);
    std::cout << "These are shorter than " << a + avg_len << std::endl;
    for (auto str : strings) {
        if (str.length() < a+avg_len) {
            std::cout << str << std::endl;
        }
    }
}

enum Quality {
    A,
    B
};

class Banan {
    public:
        int weight;
        Quality quality;
        bool is_bio;

    Banan(int w, Quality q, bool b) : weight(w), quality(q), is_bio(b) {};
};

int sum_a_quality_bio_banana(std::vector<Banan> bananas) {
    int weight_sum = 0;
    for (Banan b : bananas) {
        if (b.is_bio && b.quality == Quality::A) {
            weight_sum += b.weight;
        }
    }
    return weight_sum;
}

int main(void) {

    // 1. task
    // The smallest divisible number by both 3 and 5 between 1 and 16 is 15
    std::cout << "Task 1:" << std::endl;
    std::cout << divisible_by_3_and_5(1, 16) << std::endl;

    // 2. task
    std::cout << "Task 2:" << std::endl;
    std::vector<std::vector<int>> v;
    v = {
            {0, 45, 2432, 33, 99},
            {1, 2, 43, 87, 23},
            {24, 53, 23, 543, 22},
            {25, 1, 2, 3, 4},
            {33, 43, 123, 3, 432}
        };
    std::vector<int> v2 = flat_bigger_than_25(v);
    for (auto n : v2) {
        std::cout << n << ", ";
    }

    // 3. task
    std::cout << "Task 3: " << std::endl;
    int a, b, c;
    a = 122;
    b = 22;
    c = 2;
    sort_3(a, b, c);
    std::cout << "a: " << a << " b: " << b << " c: " << c << std::endl;
    std::cout << std::endl;

    // 4. task
    std::cout << "Task 4: " << std::endl;
    task4();

    // 5. task
    std::cout << "Task 5: " << std::endl;
    std::vector<Banan> bananas = {
        Banan(1, Quality::A, true), 
        Banan(7, Quality::A, true), 
        Banan(1, Quality::A, false), 
        Banan(1, Quality::B, true), 
        Banan(1, Quality::B, false)
    };
    std::cout << "Sum of A quality Bananas: " << sum_a_quality_bio_banana(bananas) << std::endl;

    // 6. task
    std::ifstream inp("./zh/sorok.txt");
    std::string sorok((std::istreambuf_iterator<char>(inp)), std::istreambuf_iterator<char>());
    std::map<char, int> freq;

    for (std::string::iterator i = sorok.begin(); i != sorok.end(); ++i) {
        char nextChar = tolower(*i);
        if (freq.count(nextChar)) {
            freq.insert_or_assign(nextChar, freq.at(nextChar)+1);
            continue;
        }
        freq.insert_or_assign(nextChar, 1);
    }
    
    inp.close();

    std::vector<std::pair<char, int>> pairs;
    for (auto itr = freq.begin(); itr != freq.end(); itr++) 
        pairs.push_back(*itr);
    
    sort(pairs.begin(), pairs.end(),
        [=](std::pair<char, int>& a, std::pair<char, int>& b) {
            return a.second > b.second;
        }
    );

    std::ofstream outf("./zh/gyakori.txt");
    // The most frequent character is ' ' (space)
    outf << pairs[0].first << ": " << pairs[0].second << std::endl;
    outf << 'a' << ": " << freq.at('a') << std::endl;
    outf << 'b' << ": " << freq.at('b') << std::endl;

    return 0;
}