#include "r_data_m.h"
#include "c_data_m.h"
#include "VideoStore.h" //file/headers

using namespace std;

r_data_m::r_data_m() { // calling constructor to start and read file, simultaneously adding them to queue
    readfile();
}

void r_data_m::rentalinfoget(int customerid, int videoid) {
    rentalstack.push(make_pair(customerid, videoid));
    cout << "\t\t\t\t ******* Renting: Customer ID - " << customerid << ", Video ID - " << videoid << " ******* " << endl << endl;
    rentalinfosave();                                           
}                                                           // something in the rental code prevents the "save at end of program"
                                                            // clause from functioning properly, so it's called here
void r_data_m::rentalinfosave() {
    ofstream myfile("rental.txt");                          // adds everything in the queue to the file by popping em
    if (!myfile) {
        cout << ">> Error opening the file." << endl;
        return;
    }
    myfile << "----------------------------------------------" << endl; // headers used for design on .txt file
    myfile << "         Customer ID | Movie ID" << endl;
    myfile << "----------------------------------------------" << endl;

    stack<pair<int, int>> tempstack(rentalstack);                       // calling a temp stack to preserve rental queue
    while (!tempstack.empty()) {                                        // if rentalinfosave isn't called at end of program
        pair<int, int> rental = tempstack.top();
        tempstack.pop();                         

        myfile << rental.first << " | " << rental.second << endl;
    }

    myfile.close();
}

void r_data_m::readfile() {     // file reading function
    ifstream file("rental.txt");
    if (!file) {
        cout << " \t\t\t\t\t******* Error opening the file. ******* " << endl;
        return;
    }
    
    while (!rentalstack.empty()) { // clears the existing rental stack just in case (as readfile is called multiple times)
        rentalstack.pop();         // to ensure inter-class data transfer is completed properly
    }

    string line;                    // skips the header lines used for design
    getline(file, line);
    getline(file, line);
    getline(file, line);

    while (getline(file, line)) {               // a pair container is used for the stack stl as the adt only uses
        pair<int, int> rental;                  // two data, and they're both int. the rest of the data are called
        string delimiter = " | ";               // from their respective classes, like the names.
                                                // only ids are saved in the rental file
        size_t pos = 0;
        pos = line.find(delimiter);
        rental.first = stoi(line.substr(0, pos));

        line.erase(0, pos + delimiter.length());
        pos = line.find(delimiter);
        rental.second = stoi(line.substr(0, pos));

        rentalstack.push(rental);
    }

    file.close();
}

void r_data_m::rentalinfodelete(int customerID, int videoID) { // rental function, deletes on .txt file
    stack<pair<int, int>> tempstack;
    while (!rentalstack.empty()) {                             // create temporary stack so rentalstack can be recreated after
        pair<int, int> rental = rentalstack.top();
        rentalstack.pop();

        if ((rental.first == customerID) && (rental.second == videoID)) {
            cout << "\t\t\t\t\tReturned: Customer ID - " << rental.first << ", Video ID - " << rental.second << endl;
            continue;
        }
            tempstack.push(rental);                         // theoretically, only pushing the non-matching ones to the stack should work
        }

    while (!tempstack.empty()) {
        pair<int, int> rental = tempstack.top();
        tempstack.pop();
        rentalstack.push(rental);
    }

    rentalinfosave();                                       // called immediately just to make sure the rental.txt saves properly
}

void r_data_m::customerrentalview(int customerID) {         // inter-class function to check for customer id, movie title, and more
    c_data_m c_data_access;                                 // provides access to the different class files
    VideoStore v_data_access;
    bool rented = false;
    
    c_data_access.readfile();
    v_data_access.loadVideoData("videos.txt");
    cout << "\t\t\t\t\tChecking for Account Number " << customerID << "..." << endl;
    if(c_data_access.showcustomerdata(customerID)==customerID){ // checks to see if customer id inputted exists on customerdata.txt
    
    stack<pair<int, int>> tempstack;
    while (!rentalstack.empty()) {                              // temp stack to not damage the actual stack
        pair<int, int> rental = rentalstack.top();
        rentalstack.pop();

        if (rental.first == customerID) {                       // checks to see if customer id matches with any of the rental ids
            cout << "\n\t\t\t\t\t>> Video ID: " << rental.second << endl;
            string movieTitle = v_data_access.getVideoTitle(rental.second); // obtains videotitle from video adt and prints it
            cout << "\t\t\t\t\t>> Movie Title: " << movieTitle << endl;
            rented = true;
        } else {
            tempstack.push(rental);
        }
    }

    while (!tempstack.empty()) {                                // bringing the popped back to life
        pair<int, int> rental = tempstack.top();
        tempstack.pop();
        rentalstack.push(rental);
    }
    }
    
    else
        cout << "\t\t\t\t\t\t******* ID Error! *******" << endl;
    if(!rented)
        cout << "\t\t\t\t\t\t******* No Movies Rented! *******" << endl;
}
