#ifndef SVC_H
#define SVC_H

#include <iostream>
#include <vector>
#include <exception>
#include <iomanip>

//OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>



//Qt
#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QString>

class Converter : public QDialog
{
	Q_OBJECT
public:
	Converter(size_t windowsWidth, size_t windowsHeight);

	std::vector< std::vector< std::vector<bool> > > m_lattices;

public slots:
	void Convert();
	void openFile();

private:
	QString movieFileName;
	cv::VideoCapture movieCap;
	void ConvertFrameToGrey(cv::Mat& frame);
	size_t movieWindowWidth, movieWindowHeight;
	size_t mMovieWidth, mMovieHeight;
	size_t movieCapWidth, movieCapHeight;
	
	QPushButton *btnOpen;
	QPushButton *btnLaunchSamu;
	QLabel *label;
};

#endif
