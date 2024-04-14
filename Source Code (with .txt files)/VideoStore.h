#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include "c_data_m.h"
#include "r_data_m.h"

using namespace std;

class Video {
public:
    int id;
    string title;
    string genre;
    string production;
    int numCopies;
};

class VideoStore {
private:
    list<Video> videos;
    int nextId = 0;

public:
    void loadVideoData(string filename);
    string getVideoTitle(int videoid);
    void saveVideoData(string filename);
    void insertVideo(string title, string genre, string production, int numCopies);
    bool rentVideo(int videoId);
    bool returnVideo(int videoId);
    void showVideoDetails(int videoId);
    void displayAllVideos();
    bool checkVideoInStore(int videoId);
};