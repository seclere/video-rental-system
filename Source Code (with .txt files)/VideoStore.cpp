#include "VideoStore.h"
#include "r_data_m.h"
#include <fstream>
#include <iostream>
#include <ctype.h>

using namespace std;

// Function for loading video data from a file
void VideoStore::loadVideoData (string filename){
    // Opens the file with the given filename
    ifstream file (filename);

      // Checks if the file is open
      if (file.is_open ())
      {
          string line;
          
          // Reads the file line by line
          while (getline (file, line))
          {
    	  
    	  // Creates a new Video object and sets its properties.
    	  Video video;
    	  video.id = ++nextId;
    	  video.title = line;
    
    	  getline (file, line);
    	  video.genre = line;
    
    	  getline (file, line);
    	  video.production = line;
    
    	  getline (file, line);
    	  video.numCopies = stoi (line);
    
          // Adds the video to the list of videos.
    	  videos.push_back (video);
    	}
            
          // Closes the file
          file.close ();
        }
}

// Function for getting the title of a video using its ID
string VideoStore::getVideoTitle (int videoid){
  
  // Iterates through the list of videos.
  for (auto it = videos.begin (); it != videos.end (); it++)
    {
      // Checks if the ID of the current video matches the given ID.
      if (it->id == videoid)
      {
          // If it matches, return the title of the video
          return it->title;
      }
    }
 
  // If no video with the given ID is found, return an empty string.  
  return "";
}

// Function for saving video data to a file
void VideoStore::saveVideoData (string filename){
  
  // Opens the file with the given filename.
  ofstream file (filename);
    
  // Checks if the file is open.    
  if (file.is_open ())
    {
      // Iterates through the list of videos.
      for (auto it = videos.begin (); it != videos.end (); it++)
      {
          // Writes the properties of the current video to the file.
    	  file << it->title << endl;
    	  file << it->genre << endl;
    	  file << it->production << endl;
    	  file << it->numCopies << endl;

      }
        
      // Closes the file.    
      file.close ();
    }
}

// Inserts a new video into the store with the given title, genre, production, and number of copies
void VideoStore::insertVideo(string title, string genre, string production, int numCopies) {
    Video video;
    video.id = ++nextId;
    video.title = title;
    video.genre = genre;
    video.production = production;
    video.numCopies = numCopies;

    videos.push_back(video);

    cout << "\t\t\t\t\t ******* New video added successfully! *******" << endl;
    cout << "\t\t\t\t\t >> Video ID: " << videos.back().id << endl;
    cout << "\t\t\t\t\t >> Title: " << videos.back().title << endl;
    cout << "\t\t\t\t\t >> Genre: " << videos.back().genre << endl;
    cout << "\t\t\t\t\t >> Production: " << videos.back().production << endl;
    cout << "\t\t\t\t\t >> Number of copies: " << videos.back().numCopies << endl;
}

// Rents a video with the given ID to a customer
bool VideoStore::rentVideo(int videoId) {
    int id;
    bool found = false;

    c_data_m c_data_access;
    r_data_m r_data_access;
    c_data_access.readfile();

    // Iterate over the videos container
    for (auto it = videos.begin(); it != videos.end(); it++) {
        // If the video with the given ID is found
        if (it->id == videoId) {
            // If there are available copies of the video
            if (it->numCopies > 0) {
                // Prompt the user to input a customer ID
                cout << "\t\t\t\t\t >> Input Customer ID: ";
                cin.clear();
                cin >> id;
                cout << endl << "\n\n\t\t\t\t\t********************||******************** " << endl << endl;
                cout << "\t\t\t\t\t\t   Details of Renting: " << endl << endl;
                cout << "\t\t\t\t\t********************||******************** " << endl << endl;
                // If the customer ID is valid
                if (c_data_access.showcustomerdata(id) == id) {
                    // Decrement the number of copies and update the rental information
                    it->numCopies--;
                    cout << "\t\t\t\t\t>> Video ID: " << it->id << endl;
                    cout << "\t\t\t\t\t>> Movie Title: " << it->title << endl;
                    cout << "\t\t\t\t\t>> Number of Copies: " << it->numCopies << endl;
                    r_data_access.rentalinfoget(id, it->id);
                    found = true;
                }
            } else {
                found = false;
            }
        }
    }

    return found;
}

// Function for returning a video by its ID
bool VideoStore::returnVideo (int videoId){
    
    bool found = false;

    r_data_m r_data_access;
    c_data_m c_data_access;
    c_data_access.readfile ();

    int id;

    cout << "\t\t\t\t\t >> Input Customer ID: ";
    cin.clear ();
    cin >> id;
    c_data_access.showcustomerdata (id);

    // Iterates through the list of videos
    for (auto it = videos.begin (); it != videos.end (); it++)
    {
        // Checks if the iD of the current video matches the given id
        if (it->id == videoId)
        {
            // If it matches, set the found flag to true, increment the number of copies, and delete the rental information
            found = true;
            it->numCopies++;
            r_data_access.rentalinfodelete (id, it->id);
        }
    }

    // Return the value of the found flag
    return found;
}


// Function for showing the details of a video by its ID
void VideoStore::showVideoDetails (int videoId){

    bool found = false;

    // Iterates through the list of videos
    for (auto it = videos.begin (); it != videos.end (); it++)
    {
        // Checks if the id of the current video matches the given id
        if (it->id == videoId)
        {
            // If it matches, set the found flag to true and print the details of the video
            found = true;
            cout << "\t\t\t\t\t >> Video ID: " << it->id << endl;
            cout << "\t\t\t\t\t >> Title: " << it->title << endl;
            cout << "\t\t\t\t\t >> Genre: " << it->genre << endl;
            cout << "\t\t\t\t\t >> Production: " << it->production << endl;
            cout << "\t\t\t\t\t >> Number of copies: " << it->numCopies << endl;
            
        }
    }

    // If no video with the given id is found, print a message indicating that the movie is not available
    if (!found)
    {
        cout << endl << " ******* This movie is not available! *******" << endl;
    }
}

// Function to display all the videos
void VideoStore::displayAllVideos (){

  videos.sort ([](const Video & a, const Video & b)
	       {
	       return a.id < b.id;}
  );

  for (auto it = videos.begin (); it != videos.end (); it++)
    {
      cout << endl << "\t\t\t\t\t >> Video ID: " << it->id << endl;
      cout << "\t\t\t\t\t >> Title: " << it->title << endl;
      cout << "\t\t\t\t\t >> Genre: " << it->genre << endl;
      cout << "\t\t\t\t\t >> Production: " << it->production << endl;
      cout << "\t\t\t\t\t >> Number of Copies: " << it->numCopies << endl;
    
            if(it->id % 5 == 0){
            	cout << "\n\t\t\t\t\t >> Press any key to enter next page: \n";
            	system ("pause");
            	system ("cls");
        	}
    }
	
	system ("pause");
    system ("cls");
    
}

// Function to check if a specific video is available in the store
bool VideoStore::checkVideoInStore (int videoId){
  bool found = false;		// Variable to keep track of whether the video was found

  for (auto it = videos.begin (); it != videos.end (); it++)
    {
      if (it->id == videoId)
	{
	  found = true;
	  cout << "\t\t\t\t\t >> Video ID: " << it->id << endl;
      cout << "\t\t\t\t\t >> Title: " << it->title << endl;
      cout << "\t\t\t\t\t >> Number of Copies: " << it->numCopies << endl;
	}
    }

  return found;
}

