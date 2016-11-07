#include"Readin.h"

Point origin;
Rect selection;
bool selectObject = false;
int trackObject = 0;
string Read_ImgFilePath(string ConfigFileName)
{
	fstream fp;
	string ImgFilePath;
	fp.open(ConfigFileName, fstream::in);
	getline(fp, ImgFilePath);
return ImgFilePath;
}

static void onMouse(int event, int x, int y, int, void*)
{
	if (selectObject)
	{
		selection.x = MIN(x, origin.x);
		selection.y = MIN(y, origin.y);
		selection.width = std::abs(x - origin.x);
		selection.height = std::abs(y - origin.y);
	}
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		origin = Point(x, y);
		selection = Rect(x, y, 0, 0);
		selectObject = true;
		break;
	case EVENT_LBUTTONUP:
		selectObject = false;
		if (selection.width > 0 && selection.height > 0)
			trackObject = -1;
		break;
	}
}

void readImageSequenceFiles(string imgFilePath, vector <string> &imgNames)
{
	imgNames.clear();

	imgFilePath = imgFilePath + "/*.jpg";

	WIN32_FIND_DATA f;
	HANDLE h = FindFirstFile(imgFilePath.c_str(), &f);
	if (h != INVALID_HANDLE_VALUE)
	{
		do
		{
			imgNames.push_back(f.cFileName);
		} while (FindNextFile(h, &f));

	}
	FindClose(h);
}

Rect Read_objectbbox(Mat const &Init_Image)
{
	Mat tmp_Init_Image;
	tmp_Init_Image = Init_Image.clone();
	namedWindow("choose the object box", WINDOW_AUTOSIZE);
	while (trackObject == 0)
	{

		setMouseCallback("choose the object box", onMouse, 0);
		imshow("choose the object box", tmp_Init_Image);
		waitKey(1);
		if (true == selectObject)
		{
			while (true == selectObject)
			{
				tmp_Init_Image = Init_Image.clone();
				cv::rectangle(tmp_Init_Image, selection, cv::Scalar(255), 1);
				imshow("choose the object box", tmp_Init_Image);
				cv::waitKey(1);
			}
		}
	}
	return selection;
}

