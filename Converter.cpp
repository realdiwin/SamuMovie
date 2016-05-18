#include "Converter.h"

Converter::Converter(size_t windowsWidth, size_t windowsHeight) 
	: movieWindowWidth{windowsWidth}, movieWindowHeight{windowsHeight}
{
	//Declaring buttons
	btnOpen = new QPushButton(tr("Open the file"));
	btnLaunchSamu = new QPushButton(tr("Launch Samu"));

	//Connect the buttons with the slots
	connect(btnOpen, SIGNAL(clicked()), this, SLOT(openFile()));
	connect(btnLaunchSamu, SIGNAL(clicked()), this, SLOT(accept()));

	//Create the layout
	QGridLayout *converter_layout = new QGridLayout;
	
	//Adding the widgets
	converter_layout->addWidget(btnOpen, 1, 0);
	converter_layout->addWidget(btnLaunchSamu, 1, 1);

	label = new QLabel(this);
	label->setText("Please select an avi file with the button below!");
	label->setAlignment(Qt::AlignRight);
	converter_layout->addWidget(label, 0, 1);
	
	//Set the current layout
	setLayout(converter_layout);

	//Setting the window title
	setWindowTitle(tr("Samu Movie"));
	

	//Width: 640px
	//Height: 480px
	resize(640, 480);
	
}

void Converter::openFile()
{

	movieFileName = QFileDialog::getOpenFileName(this, QObject::tr("Select the Video"), "~/Videos/", QObject::tr("Avi files (*.avi)"));

	movieCap.open(movieFileName.toUtf8().constData());
	if ( !movieCap.isOpened() )
	{
		std::cerr << "//////////////////////////" << std::endl;
		std::cerr << "Can't open the video file!" << std::endl;
		std::cerr << "//////////////////////////" << std::endl;
		throw std::exception();
	}

	mMovieWidth = movieCap.get(CV_CAP_PROP_FRAME_WIDTH);
	mMovieHeight = movieCap.get(CV_CAP_PROP_FRAME_HEIGHT);

	movieCapWidth = (mMovieWidth / movieWindowWidth);
	movieCapHeight = (mMovieHeight / movieWindowHeight);

	Convert();
}

void Converter::Convert()
{
	cv::Mat temporaryFrame;

	std::vector< std::vector< std::vector<bool> > > temporaryFrames;

	size_t frame_number = 0;

	for (;;)
	{
		movieCap >> temporaryFrame;


		if (temporaryFrame.empty()) 
			break;

		temporaryFrames.push_back(
			std::vector< std::vector<bool> > (movieWindowHeight, std::vector<bool>(movieWindowWidth))
		);

		ConvertFrameToGrey(temporaryFrame);
		
		for (auto i = 0; i < temporaryFrame.rows; i += movieCapHeight)
		{
			for (auto j = 0; j < temporaryFrame.cols; j += movieCapWidth)
			{
				cv::Mat cell_mask = cv::Mat::zeros(temporaryFrame.rows, temporaryFrame.cols, CV_8U);

				cv::Rect cell_mask_region = cv::Rect(i, j, movieCapWidth, movieCapHeight);

				cell_mask(cell_mask_region) = 1;

				if ((cv::mean(temporaryFrame, cell_mask))[0] > 127)
				{
					temporaryFrames[frame_number][i / movieCapHeight][j / movieCapWidth] = false;
				}
				else
				{
					temporaryFrames[frame_number][i / movieCapHeight][j / movieCapWidth] = true;
				}
				
			}
		}
		
		std::cout 	<< "#Convert# Frame:[" 
					<< std::setfill('0') 
					<< std::setw(3) 
					<< frame_number 
					<< "]" 
					<< "\r"
					<< std::flush;
		frame_number++;
	}
	m_lattices = std::move(temporaryFrames);
	std::cout << std::endl;
	label->setText("We are ready to launch the samu!");
}

void Converter::ConvertFrameToGrey(cv::Mat& frame)
{
	cv::Mat _grey;

	cv::cvtColor(frame, _grey, CV_BGR2GRAY);

	frame = _grey;
}
