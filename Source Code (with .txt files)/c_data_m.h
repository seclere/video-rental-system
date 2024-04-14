#pragma once

#include <queue>
#include <fstream>
#include <iostream>

using namespace std;

struct c_data {
    int id;
    string name;
    string address;
};

class c_data_m {
private:
    int customerid;
    queue<c_data> customerqueue;

public:
    c_data_m();
    void addcustomer(string name, string address);
    int showcustomerdata(int id);
    void addtofile();
    void readfile();
};