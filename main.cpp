//
//  main.cpp
//  Hash_code
//
//  Created by Lily Zhai on 2/20/20.
//  Copyright © 2020 Mengyun Zhai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include "xcode_redirect.hpp"
using namespace std;

class  settingup {
public:
    void get_info();
    void readinfo(ifstream &myfile);
    void calculate_days();
    void calc_each_lib(ofstream &myfile);
    void print();
    
private:
    int numbooks;
    int numlibraries;
    int numdays_remain;
    vector<int> score;
    
    int p_lib;

    struct library {
        int ID;
        int sign_up;
        int ship_speed;
        int books_contain;
        vector<int> books;
        int total_sum;
    };
    
    vector<library> main_lib;
    
    class libCompare {
    public:
        bool operator()(const library &L1, const library &L2)const {
            if (L1.sign_up < L2.sign_up) {
                return true;
            }
            else if (L1.sign_up > L2.sign_up) {
                return false;
            }
            else {
                if (L1.ship_speed > L2.ship_speed) {
                    return true;
                }
                else if (L1.ship_speed < L2.ship_speed) {
                    return false;
                }
                else if (L1.total_sum > L2.total_sum){
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    };
};


void settingup::get_info() {
    string name;
    cin >> name;
    
    ifstream myfile;
    myfile.open(name);
    if (myfile.is_open()) {
        readinfo(myfile);
        myfile.close();
    }
    else {
        cout <<"unable to open" << '\n';
        exit(1);
    }
}

void settingup::readinfo(ifstream &myfile) {
    int temp_score = 0;

    
    cin >> numbooks >> numlibraries >> numdays_remain;
    
    for (int i = 0; i < numbooks; ++i) {
        cin >> temp_score;
        score[i] = temp_score;
    }
    
    for (int j = 0; j < numlibraries; ++j) {
        int temp, temp2, temp3;
        cin >> temp >> temp2 >> temp3;
        library lib;
        lib.ID = j;
        lib.sign_up = temp2;
        lib.books_contain = temp;
        lib.ship_speed = temp3;
        lib.total_sum = 0;
        
        for (int i = 0; i < lib.books_contain; ++i) {
            int temp_num;
            cin >> temp_num;
            lib.books[i] = temp_num;
            lib.total_sum += score[temp_num];
        }
        
        main_lib.push_back(lib);
    }
    
    libCompare cmp;
    std::sort(main_lib.begin(), main_lib.end(), cmp);
}

void settingup::calculate_days() {
    int i = 0;
    int temp = numdays_remain;
    while (temp >= 0) {
        temp -= main_lib[i].sign_up;
        ++i;
    }
    p_lib = i;
}

void settingup::calc_each_lib(ofstream &myfile) {
    int temp_days = numdays_remain;
    
    for (int i = 0; i < p_lib; ++i) {
        temp_days -= main_lib[i].sign_up;
        int book_scanned = main_lib[i].ship_speed * (temp_days);
        myfile << main_lib[i].ID << ' ' << book_scanned;
    }
}



void settingup::print() {
    ofstream myfile;
    myfile.open ("result.txt");
    myfile << p_lib << '\n';
    calc_each_lib(myfile);
    myfile.close();
}





int main(int argc, const char * argv[]) {
    std::ios_base::sync_with_stdio(false);
//    xcode_redirect(argc, argv);
    
    
    
    return 0;
}
