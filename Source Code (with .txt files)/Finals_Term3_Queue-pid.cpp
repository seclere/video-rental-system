#include <iostream>
#include <string>
#include <ctype.h>
#include "c_data_m.h"
#include "r_data_m.h"
#include "VideoStore.h" // headers/libraries

using namespace std;

int main(){
    
	c_data_m c_data_adt; // creating objects for all the classes so they can be used
	r_data_m r_data_adt;
	VideoStore store; // Create a VideoStore object
    
    c_data_adt.readfile(); // reads the files of the program
    r_data_adt.readfile();
    
    string customername;
    string customeraddress;
    int choice, id;
	int option; // Variable to store the user's option
	int customerOption; // Variable to store the user's option in the customer maintenance menu
	int exit = 0; // Variable to keep track of whether the user wants to exit the program

	string filename = "videos.txt"; // Name of the text file to read/write the video data
	store.loadVideoData(filename); // Load the video data from the text file

	while(exit == 0){ // main menu interface
		system ("cls");
		system( "color 0b" ); 
		cout<<"\n\t\t\t\t\t     *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
		cout<<"\t\t\t\t\t     *-                                   -*"<<endl;
		cout<<"\t\t\t\t\t     *-  Welcome to Queuepids' Video Hub  -*\t"  <<endl;
		cout<<"\t\t\t\t\t     *-                                   -*"<<endl;
		cout<<"\t\t\t\t\t     *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl<<endl; 
		cout<<"\t\t\t\t\t********************| MENU |******************** "<<endl<<endl; 
		cout<<" \t\t\t\t\t\t [1] New Video"<<endl; 
		cout<<" \t\t\t\t\t\t [2] Rent a Video"<<endl;  
		cout<<" \t\t\t\t\t\t [3] Return a Video"<<endl;  
		cout<<" \t\t\t\t\t\t [4] Show Video Details"<<endl;  
		cout<<" \t\t\t\t\t\t [5] Display All Videos"<<endl;  
		cout<<" \t\t\t\t\t\t [6] Check Video Availability"<<endl;  
		cout<<" \t\t\t\t\t\t [7] Customer Maintenance"<<endl;  
		cout<<" \t\t\t\t\t\t [8] Exit the Program"<<endl<<endl;
		cout<<"\t\t\t\t\t********************| MENU |******************** "<<endl;
		cout<<"\n\n \t\t\t\t\t\t\t>> Enter Choice: ";
        cin>>option; 
		                    // switch cases to facilitate the program
        switch (option){
			// New Video option 
            case 1:{        // input details, send to classes, check if functions return true or false
            	system("cls");  // mostly same ballpark for all cases, most of the work is done on the .cpp files
            					
                string title, genre, production; 
                int numCopies;
				cout<<endl<<"\t\t\t\t\t********************||******************** "<<endl<<endl; 
				cout<< "\t\t\t\t\t\t      * NEW VIDEO *" << endl<<endl;
				cout<<"\t\t\t\t\t********************||******************** "<<endl<<endl; 
                cout << endl << "\t\t\t\t\t  >> Enter the Title of the new movie: ";
                cin.ignore();
                getline(cin,title);
                cout << endl << "\t\t\t\t\t  >> Enter the Genre of the new movie: ";
                getline(cin,genre);
                cout << endl << "\t\t\t\t\t  >> Enter the Production of the new movie: ";
                getline(cin,production);
                cout << endl << "\t\t\t\t\t  >> Enter the Number of Copies of the new movie: ";
                cin >> numCopies;
				
                store.insertVideo(title,genre,production,numCopies);
				system ("pause");
                break;
            }
            // Rent a Video option
            case 2:{
            	system("cls");
            	cout<<endl<<"\t\t\t\t\t********************||******************** "<<endl<<endl; 
				cout<<"\t\t\t\t\t              * RENT A VIDEO *" << endl<<endl;
				cout<<"\t\t\t\t\t********************||******************** "<<endl<<endl; 
                int id;
                
                bool end = true;
                char rentagain;
                
                do{
                cout << endl << "\t\t\t\t\t Enter the ID of the movie you want to rent: ";
                cin >> id;
				
                if(store.rentVideo(id)){
                    cout << endl << "\t\t\t\t\t!! The movie has been rented successfully. !!" << endl;	
                }
				else{
                    cout << endl << "\t\t\t\t\t!! The movie is not available !!" << endl;	
                }
                cout << "\t\t\t\t\tRent another video? Y/N: ";              // renting again without asking for customer id
                
                cin >> rentagain;
                switch(rentagain){
                	case 'N': case 'n':
                		{
                			end = false;
                    		break;
						}
					case 'Y': case 'y':
                		{
                			end = true;
                    		continue;
						}
					default:
                		{
                			cout << "\n\t\t\t\t\tWrong input.\n";
                			end = false;
                    		break;
						}
				}
                
                system ("pause");
            }while(end);
			break;
			}
            // Return a Video option
            case 3:{
            	system("cls");
            	cout<<endl<<"\t\t\t\t\t********************||******************** "<<endl<<endl; 
				cout<< "\t\t\t\t\t\t   * RETURN A VIDEO *" << endl<<endl;
				cout<<"\t\t\t\t\t********************||******************** "<<endl<<endl; 
                int id;

                cout << endl << "\t\t\t\t\t>> Enter the ID of the movie you want to return: ";
                cin >> id;
                
                
                if(store.returnVideo(id)){
                    cout << endl << "\t\t\t\t\t !! The movie has been returned successfully !!" << endl;	
                }
				else{
                    cout << endl << "\t\t\t\t\t !! The movie is not in our records !! " << endl;	
                }
                
                system ("pause");
                break;
            }
            // Show Video Details option
            case 4:{
            	system("cls");
                cout<<endl<<"\t\t\t\t\t********************||******************** "<<endl<<endl; 
				cout<< "\t\t\t\t\t\t * SHOW VIDEO DETAILS *" << endl<<endl;
				cout<<"\t\t\t\t\t********************||******************** "<<endl<<endl;
                int id;

                cout << endl << "\t\t\t\t\t>> Enter movie id: ";
                cin >> id;

                store.showVideoDetails(id);               
                system ("pause");
                break;
            }
            // Display All Videos Option
            case 5:{
            	system("cls");
            	cout<<endl<<"\t\t\t\t\t********************||******************** "<<endl<<endl; 
				cout<< "\t\t\t\t\t\t * DISPLAY ALL VIDEOS *" << endl<<endl;
				cout<<"\t\t\t\t\t********************||******************** "<<endl<<endl;
                store.displayAllVideos();
                
                break;
            }
            // Check Video Availability Option
            case 6:{
            	system("cls");
            	cout<<endl<<"\t\t\t\t\t********************||******************** "<<endl<<endl; 
				cout<< "\t\t\t\t\t\t * CHECK VIDEO AVAILABILITY *" << endl<<endl;
				cout<<"\t\t\t\t\t********************||******************** "<<endl<<endl;
                int id;

                cout << endl << "\t\t\t\t\t  >> Enter movie ID: ";
                cin >> id;

                if(store.checkVideoInStore(id)){
                    cout << endl << "\t\t\t\t\t >> The movie is available! "<<endl;	
                }
				else{
                    cout << endl << "\t\t\t\t\t >> The movie is not available. "<<endl;	
                }
                
                system ("pause");
                break;
            }
            // Customer Maintenance option
            case 7:{
            	
				do {
			system("cls");	// Displays Customer Maintenance Menu until return to main menu option is selected
			cout<< "\t\t\t\t\t===============================================" << endl;
			cout<< "\t\t\t\t\t\t  *  CUSTOMER MAINTENACE  *" << endl;
			cout<< "\t\t\t\t\t===============================================\n" << endl;	
			cout<<"\t\t\t\t\t********************|MENU|******************** "<<endl<<endl; 
			cout<< "\t\t\t\t\t[1]. Add New Customer" << endl;
			cout<< "\t\t\t\t\t[2]. Show Customer Details" << endl;
			cout<< "\t\t\t\t\t[3]. List of Videos Rented by a Customer" << endl;
			cout<< "\t\t\t\t\t[4]. Return to Main Menu" << endl<<endl;
			cout<<"\t\t\t\t\t********************|MENU|******************** "<<endl<<endl; 
			cout << "\n\t\t\t\t\t\t    Enter your choice: ";
                    cin >> choice;
            
                    switch (choice) {
                    	// Add New Customer option 
                        case 1:
                            cout << "\t\t\t\t\t>> Please input your name: ";
                            cin.ignore();
                            getline(cin, customername);
            
                            cout << "\t\t\t\t\t>> Please input your address: ";
                            cin.clear();
                            getline(cin, customeraddress);
            
                            c_data_adt.addcustomer(customername, customeraddress);
                            system ("pause");
                            break;
            			// Show Customer Details option
                        case 2:
                            cout << "\t\t\t\t\t>> Please input your id: ";
                            cin >> id;
                            c_data_adt.showcustomerdata(id);
                            system ("pause");
                            break;
            			// List of Customer Rented Videos option
                        case 3:
                            cout << "\t\t\t\t\t>> Input Customer id: ";
                            cin >> id;
                            r_data_adt.customerrentalview(id);
                            system ("pause");
                            break;
            			// Returns to main menu
                        case 4:
                            break;
        }
    } while (choice != 4);
				
				break;
            }
            // exit option
            case 8:{
            	system("cls");
            	    
                    c_data_adt.addtofile();
                    // r_data_adt.rentalinfosave(); // returned movies aren't deleted from .txt file if called directly here
                    store.saveVideoData(filename); // Save the updated video data to the text file
                    
				cout << " \t\t\t\t\t================================================= " << endl;
				cout << " \t\t\t\t\t        Thank you for shopping with us :]          " << endl;
				cout << " \t\t\t\t\t================================================= " << endl;
				
				exit++;
				system ("pause");

				break;
            }
        }
    }


    return 0;
}
