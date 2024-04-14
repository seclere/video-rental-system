#pragma once

#include <stack>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct r_data {
    int customerID;
    int videoID;
};

class r_data_m {
private:
    stack<pair<int, int>> rentalstack;

public:
    r_data_m();
    void rentalinfoget(int customerid, int videoid);
    void rentalinfosave();
    void readfile();
    void rentalinfodelete(int customerID, int videoID);
    void customerrentalview(int customerID);
};