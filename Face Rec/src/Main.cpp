#include <iostream>
#include <stdlib.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main() {
	CascadeClassifier faceDetection;
	if(!faceDetection.load("dependencies/opencv/data/haarcascades/haarcascade_frontalface_default.xml")) {
		std::cout << "Face Detection failed to load!" << std::endl;
		exit(0);
	}
	char path[100];
	std::cout << "Enter the path to the image for face detection : " << std::endl;;
	std::cin.getline(path, 100);

	Mat img = imread(path, CV_LOAD_IMAGE_UNCHANGED);
	bool empty = img.empty();
	std::cout << (empty ? "The image you chose is corrupt!" : "The image was found!...\n Processing...") << std::endl;
	if (!empty) {
		std::vector<Rect> faces;
		faceDetection.detectMultiScale(img, faces);
		for (int i = 0; i < faces.size(); ++i) {
			Point pt1(faces[i].x, faces[i].y);
			std::cout << faces[i].height << std::endl;
			Point pt2(faces[i].x + faces[i].height, faces[i].y + faces[i].width);
			rectangle(img, pt1, pt2, Scalar(0, 0, 255), 2, 8, 0); //BGR
		}
		imwrite("storage/output.jpg", img);
		std::cout << "Face detection was successful - output will be in the storage directory!" << std::endl;
	}
	return 0;
}