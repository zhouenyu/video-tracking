#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<Windows.h>


using namespace std;
using namespace cv;

string Read_ImgFilePath(string ConfigFileName);
static void onMouse(int event, int x, int y, int, void*);
Rect Read_objectbbox(Mat const &Init_Image);
void readImageSequenceFiles(string imgFilePath, vector <string> &imgNames);