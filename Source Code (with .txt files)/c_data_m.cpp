#include "c_data_m.h"
#include "r_data_m.h"
#include <fstream>
#include <iostream> //file/headers

using namespace std;

c_data_m::c_data_m() { // calling constructor to start and read file, simultaneously adding them to queue
    readfile();
    customerid = 0;
}

void c_data_m::addcustomer(string name, string address) { // add customer using a queue
    c_data newcustomer;
    newcustomer.id = ++customerid;
    newcustomer.name = name;
    newcustomer.address = address;

    customerqueue.push(newcustomer); // details pushed into a queue to be popped later

    cout << "\t\t\t\t\t>> Customer ID is: " << newcustomer.id << endl;
    cout << "\t\t\t\t\t>> Customer Name is: " << newcustomer.name << endl;
    cout << "\t\t\t\t\t>> Customer Address is: " << newcustomer.address << endl;
}

int c_data_m::showcustomerdata(int id) { // show customer data using a queue by making a temporary queue using the existing queue
    queue<c_data> tempqueue = customerqueue; // then going to the front of the tempqueue and popping it so it reads the ids
    while (!tempqueue.empty()) {                // in numerical order
        c_data customer = tempqueue.front();
        tempqueue.pop();
        if (customer.id == id) {
            cout << "\t\t\t\t\t>> Customer Name is: " << customer.name << endl;
            cout << "\t\t\t\t\t>> Customer Address is: " << customer.address << endl;
            return id;
            break;
        }
    }
    
    cout << "\n\t\t\t\t\t\t******* ID does not exist!*******" << endl;
    return 0;
}

void c_data_m::addtofile() {    // adds everything in the queue to the file by popping em
    ofstream myfile("customerdata.txt");
    if (!myfile) {
        cout << "\t\t\t\t\tError opening the file." << endl;
        return;
    }
    myfile << "----------------------------------------------" << endl; // headers used for design on .txt file
    myfile << "ID | Name | Address" << endl;
    myfile << "----------------------------------------------" << endl;

    queue<c_data> tempqueue = customerqueue;                            // calling a temp queue to preserve customer queue
    while (!tempqueue.empty()) {                                        // if addtofile isn't called at end of program
        c_data customer = tempqueue.front();
        tempqueue.pop();

        myfile << customer.id << " | " << customer.name << " | " << customer.address << endl;
    }

    myfile.close();
}

void c_data_m::readfile() { // reads the pre-existing customerdata.txt file and popping them into queue
    ifstream file("customerdata.txt");
    if (!file) {
        cout << "\t\t\t\t\t******* Error opening the file. *******" << endl;
        return;
    }

    while (!customerqueue.empty()) { // clears the existing customer queue just in case (as readfile is called multiple times)
        customerqueue.pop();         // to ensure inter-class data transfer is completed properly
    }
    
    string line; // skips the header lines used for design
    getline(file, line); // do note, remember the lines of headers you use while ignoring them
    getline(file, line); // otherwise, your conversion goes wrong
    getline(file, line);

    while (getline(file, line)) {
        c_data customer;
        string delimiter = " | ";

        size_t pos = 0;                                 // most of the hard part comes from converting the string to
        pos = line.find(delimiter);                     // an int for the classes to use
        customer.id = stoi(line.substr(0, pos));
        ++customerid;
                                                        // if you wanna troubleshoot, you can use the try and catch
        line.erase(0, pos + delimiter.length());        // functions to pinpoint at what's wrong
        pos = line.find(delimiter);
        customer.name = line.substr(0, pos);

        line.erase(0, pos + delimiter.length());
        customer.address = line;

        customerqueue.push(customer);
    }

    file.close();
}
