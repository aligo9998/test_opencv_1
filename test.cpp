#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

typedef struct pict_s
{
	Mat img;
	string Name;
} M;

vector <pict_s> session;

int check_exit(std::string s)
{
	if ((s == "q") ||
		(s == "exit") ||
		(s == "quit"))
	{
		return 1;
	}
	return 0;
}

int findimg(string NameImg)
{
	int i;
	for (i = 0; i < session.size(); i++)
	{
		if (session[i].Name == NameImg)
		{
			return i;
		}
	}
	return -1;
}

int main(int argc, char* argv[])
{
	string cmdline, scmd, tmp, ImageName, LoadFileName, SaveFileName;
	size_t pos = 0;
	int smooth_size, new_height, new_widht, i;
	pict_s image;

	cout << "Test" << endl;
	while (1)
	{
		getline(cin, cmdline);
		if (check_exit(cmdline))
		{
			cout << "Exit" << endl;
			session.clear();
			break;
		}

		pos = cmdline.find(" ");
		scmd = cmdline.substr(0, cmdline.find(" "));
		cmdline.erase(0, pos + 1);
		pos = cmdline.find(" ");
		//загрузка
		if ((scmd == "load") || (scmd == "ld"))
		{
			image.Name = cmdline.substr(0, cmdline.find(" "));
			cmdline.erase(0, pos + 1);
			LoadFileName = cmdline;
			image.img = imread(LoadFileName, IMREAD_COLOR);
			if (image.img.empty())
			{
				cout << "not found file = " << LoadFileName << endl;
			}
			else
			{
				cout << "load file = " << LoadFileName << " to picture name = " << image.Name << endl;
				session.push_back(image);
			}

		}
		//сохранение
		if ((scmd == "store") || (scmd == "s"))
		{
			ImageName = cmdline.substr(0, cmdline.find(" "));
			i = findimg(ImageName);
			if (i != -1)
			{
				cmdline.erase(0, pos + 1);
				SaveFileName = cmdline;
				if (imwrite(SaveFileName, session[i].img))
				{
					cout << "save image to " << SaveFileName << endl;
				}
				else
				{
					cout << "can not save image to " << SaveFileName << endl;
				}
			}
			else cout << "Error. Image name not found" << endl;

		}
		//сглаживание
		if (scmd == "blur")
		{
			ImageName = cmdline.substr(0, cmdline.find(" "));
			i = findimg(ImageName);
			if (i != -1)
			{
				cmdline.erase(0, pos + 1);
				image.Name = cmdline.substr(0, cmdline.find(" "));
				cmdline.erase(0, pos + 1);
				smooth_size = atoi(cmdline.c_str());
				GaussianBlur(session[i].img, image.img, Size(smooth_size, smooth_size), 0, 0);
				session.push_back(image);
				cout << "Blur " << image.Name << endl;
			}
			else cout << "Error. Image name not found" << endl;
		}
		//изменение размера
		if (scmd == "resize")
		{
			ImageName = cmdline.substr(0, cmdline.find(" "));
			i = findimg(ImageName);
			if (i != -1)
			{
				cmdline.erase(0, pos + 1);
				pos = cmdline.find(" ");
				ImageName = cmdline.substr(0, cmdline.find(" "));
				cmdline.erase(0, pos + 1);
				pos = cmdline.find(" ");
				tmp = cmdline.substr(0, cmdline.find(" "));
				cmdline.erase(0, pos + 1);
				new_widht = atoi(tmp.c_str());
				if (new_widht < 0) new_widht = 1;
				tmp = cmdline.substr(0, cmdline.find(" "));
				new_height = atoi(tmp.c_str());
				if (new_height < 0) new_height = 1;
				resize(session[i].img, image.img, Size(new_widht, new_height), 0, 0);
				image.Name = ImageName;
				session.push_back(image);
				cout << "Resize " << image.Name << " to " << new_widht << "  " << new_height << endl;
			}
			else cout << "Error. Image name not found" << endl;
		}

		if ((scmd == "help") || (scmd == "h"))
		{
			cout << "load, ld    - load jpg image <name> <filename>" << endl
				<< "store, s    - save jpg image <name> <filename>" << endl
				<< "blure       - smoothing image <name1> <name2> <size>" << endl
				<< "resize      - resize image <name1> <name2> <width> <height>" << endl
				<< "help,h      - help" << endl
				<< "quit,exit,q - exit" << endl;
		}
		pos = 0;
	}

	return 0;
}
