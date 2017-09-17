#include "facedemo1.h"
#include <iostream>
#include <cstdint>
#include <fstream>


using namespace std;

std::string MODEL_DIR = "model/";

facedemo1::facedemo1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

facedemo1::~facedemo1()
{

}
bool GetFilenameUnderPath(string file_path, std::vector<string>& files) {
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(file_path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					GetFilenameUnderPath(p.assign(file_path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				char *ext = strrchr(fileinfo.name, '.');
				if (ext) {
					ext++;
					if (_stricmp(ext, "jpg") == 0 || _stricmp(ext, "png") == 0)
						files.push_back(p.assign(file_path).append("\\").append(fileinfo.name));
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	return true;
}
void BuildData() {
	std::vector<string> filenames;
	GetFilenameUnderPath(".\\images", filenames);
	std::cout << "Detected  " << filenames.size() << "  images...." << std::endl;
	SeetaFace sf;
	FeatureGroup feature_group(sf.GetFeatureDims(), &sf);
	float* feat = sf.NewFeatureBuffer();
	for (int i = 0; i<int(filenames.size()); i++) {
		if (sf.GetFeature(filenames[i], feat))
			feature_group.AddFeature(feat, filenames[i]);
		if ((i + 1) % 1 == 0)
			std::cout << (i + 1) << " / " << int(filenames.size()) << std::endl;
	}
	feature_group.SaveModel("test.index");

	std::cout << "Finished." << std::endl;
}
void facedemo1::BuildDataBaseClicked() {
	BuildData();
}
QString facedemo1::GetFileName() {
	this->image = new QImage();
	QString imgfilename = QFileDialog::getOpenFileName();
	return imgfilename;
}

void facedemo1::UpLoadImageButtonClicked() {

	ImageFaceDetection(GetFileName());
	QString imgfilename = "out.jpg";

	image->load(imgfilename);
	double myheight = (image->height()) * 431 / (image->width());
	QImage newimage = image->scaled(QSize(431, myheight));
	QGraphicsScene *scene = new QGraphicsScene;
	scene->addPixmap(QPixmap::fromImage(newimage));
	ui.base_image_view->setScene(scene);
	ui.base_image_view->resize(431 + 10, myheight + 10);
	ui.base_image_view->show();
}

void facedemo1::ShowStudentInfoClicked() {}
int facedemo1::ImageFaceDetection(QString filename) {
	// Initialize face detection model
	seeta::FaceDetection detector("model/seeta_fd_frontal_v1.0.bin");
	detector.SetMinFaceSize(40);
	detector.SetScoreThresh(2.f);
	detector.SetImagePyramidScaleFactor(0.8f);
	detector.SetWindowStep(4, 4);

	const string sfilename = filename.toStdString();
	const char* cfilename = sfilename.c_str();
	SeetaFace sf;
	// Initialize face alignment model 
	seeta::FaceAlignment point_detector("model/seeta_fa_v1.1.bin");
	seeta::FaceIdentification identific("model/seeta_fr_v1.0.bin");

	//load image
	IplImage *img_grayscale = NULL;

	img_grayscale = cvLoadImage(cfilename, 0);
	if (img_grayscale == NULL)
	{
		return 0;
	}
	IplImage *img_color = cvLoadImage(cfilename, 1);


	int pts_num = 5;
	int im_width = img_grayscale->width;
	int im_height = img_grayscale->height;
	unsigned char* data = new unsigned char[im_width * im_height];
	unsigned char* data_ptr = data;
	unsigned char* image_data_ptr = (unsigned char*)img_grayscale->imageData;
	int h = 0;
	for (h = 0; h < im_height; h++) {
		memcpy(data_ptr, image_data_ptr, im_width);
		data_ptr += im_width;
		image_data_ptr += img_grayscale->widthStep;
	}

	seeta::ImageData image_data;
	image_data.data = data;
	image_data.width = im_width;
	image_data.height = im_height;
	image_data.num_channels = 1;

	cv::Mat src_img = cv::imread(sfilename, 0);
	seeta::ImageData src_img_data(src_img.cols, src_img.rows, src_img.channels());
	src_img_data.data = src_img.data;

	//read pic color
	cv::Mat src_img_color = cv::imread(sfilename, 1);
	seeta::ImageData src_img_data_color(src_img_color.cols, src_img_color.rows, src_img_color.channels());
	src_img_data_color.data = src_img_color.data;
	// Detect faces
	std::vector<seeta::FaceInfo> faces = detector.Detect(image_data);
	int32_t face_num = static_cast<int32_t>(faces.size());

	if (face_num == 0)
	{
		delete[]data;
		cvReleaseImage(&img_grayscale);
		cvReleaseImage(&img_color);
		return 0;
	}
	float* feat[5];
	for (int i = 0; i<face_num; i++)
		feat[i] = sf.NewFeatureBuffer();



	for (int i = 0; i < face_num; i++) {
		seeta::FacialLandmark points[5];
		sf.point_detector->PointDetectLandmarks(src_img_data, faces[i], points);
		identific.ExtractFeatureWithCrop(src_img_data_color, points, feat[i]);
	}
	IplImage *copyimage = cvCloneImage(img_color);
	QImage image_test(filename);
	QImage newImage[5];
	for (int i = 0; i < face_num; i++) {
		newImage[i] = image_test.copy(faces[i].bbox.x, faces[i].bbox.y, faces[i].bbox.width, faces[i].bbox.height);
	}

	// Detect 5 facial landmarks
	for (int i = 0; i < face_num; i++) {
		seeta::FacialLandmark points[5];
		point_detector.PointDetectLandmarks(image_data, faces[i], points);
		cvRectangle(img_color, cvPoint(faces[i].bbox.x, faces[i].bbox.y), cvPoint(faces[i].bbox.x + faces[i].bbox.width - 1, faces[0].bbox.y + faces[0].bbox.height - 1), CV_RGB(255, 0, 0));
		for (int j = 0; j<pts_num; j++)
		{
			cvCircle(img_color, cvPoint(points[j].x, points[j].y), 2, CV_RGB(0, 255, 0), CV_FILLED);
		}

	}
	cvSaveImage("out.jpg", img_color);

	// Visualize the results


	QGraphicsView* view[5];
	view[0] = this->ui.graphicsView_3;
	view[1] = this->ui.graphicsView_2;
	view[2] = this->ui.graphicsView_4;
	view[3] = this->ui.graphicsView_5;
	view[4] = this->ui.graphicsView_6;

	for (int i = 0; i < face_num; i++) {
		//string imgfilename = "Roi" + to_string(i) + ".jpg";
		//QString qimgfilename = QString::fromStdString(imgfilename);
		//image->load(qimgfilename);
		
		double myheight = (newImage[i].height()) * 256 / (newImage[i].width());
		newImage[i].scaled(QSize(256, myheight));
		QGraphicsScene *scene = new QGraphicsScene;
		scene->addPixmap(QPixmap::fromImage(newImage[i]));
		view[i]->setScene(scene);
		view[i]->resize(256 + 10, myheight + 10);
		view[i]->show();

	}


	string pic_file;

	FeatureGroup feature_group("test.index", &sf);

	std::vector<Feature> result[5];
	if (face_num == 0) {
		std::cout << "Wrong Filename or Can't Detect Face.." << std::endl;
		return 0;
	}
	for (int i = 0; i < face_num; i++) {
		feature_group.FindTopK(10, feat[i], result[i]);

	}
	QLabel *lab[5];
	lab[0] = ui.label_3;
	lab[1] = ui.label_2;
	lab[2] = ui.label_4;
	lab[3] = ui.label_5;
	lab[4] = ui.label_6;
	for (int i = 0; i < face_num; i++) {
		lab[i]->setText(QString::fromStdString(result[i][0].filename));
	}


	// Release memory
	cvReleaseImage(&img_color);
	cvReleaseImage(&img_grayscale);
	delete[]data;
	return face_num;
}

Detector::Detector(const char* model_name) : seeta::FaceDetection(model_name) {
	this->SetMinFaceSize(40);
	this->SetScoreThresh(2.f);
	this->SetImagePyramidScaleFactor(0.8f);
	this->SetWindowStep(4, 4);
}

SeetaFace::SeetaFace() {
	this->detector = new Detector("D:/model/seeta_fd_frontal_v1.0.bin");
	this->point_detector = new seeta::FaceAlignment("D:/model/seeta_fa_v1.1.bin");
	this->face_recognizer = new seeta::FaceIdentification("D:/model/seeta_fr_v1.0.bin");
}

float* SeetaFace::NewFeatureBuffer() {
	return new float[this->face_recognizer->feature_size()];
}

bool SeetaFace::GetFeature(string filename, float* feat) {
	//如果有多张脸，输出第一张脸,返回true
	//如果没有脸，输出false
	//read pic greyscale
	cv::Mat src_img = cv::imread(filename, 0);
	seeta::ImageData src_img_data(src_img.cols, src_img.rows, src_img.channels());
	src_img_data.data = src_img.data;

	//read pic color
	cv::Mat src_img_color = cv::imread(filename, 1);
	seeta::ImageData src_img_data_color(src_img_color.cols, src_img_color.rows, src_img_color.channels());
	src_img_data_color.data = src_img_color.data;

	std::vector<seeta::FaceInfo> faces = this->detector->Detect(src_img_data);
	int32_t face_num = static_cast<int32_t>(faces.size());
	if (face_num == 0)
	{
		return false;
	}
	seeta::FacialLandmark points[5];
	this->point_detector->PointDetectLandmarks(src_img_data, faces[0], points);

	this->face_recognizer->ExtractFeatureWithCrop(src_img_data_color, points, feat);

	return true;
};

bool SeetaFace::GetFeature2(string filename, float* feat, std::vector<seeta::FaceInfo> faces) {
	//如果有多张脸，输出第一张脸,返回true
	//如果没有脸，输出false
	//read pic greyscale
	cv::Mat src_img = cv::imread(filename, 0);
	seeta::ImageData src_img_data(src_img.cols, src_img.rows, src_img.channels());
	src_img_data.data = src_img.data;

	//read pic color
	cv::Mat src_img_color = cv::imread(filename, 1);
	seeta::ImageData src_img_data_color(src_img_color.cols, src_img_color.rows, src_img_color.channels());
	src_img_data_color.data = src_img_color.data;

	int32_t face_num = static_cast<int32_t>(faces.size());
	if (face_num == 0)
	{
		return false;
	}
	seeta::FacialLandmark points[5];
	this->point_detector->PointDetectLandmarks(src_img_data, faces[0], points);

	this->face_recognizer->ExtractFeatureWithCrop(src_img_data_color, points, feat);

	return true;
};

int SeetaFace::GetFeatureDims() {
	return this->face_recognizer->feature_size();
}

float SeetaFace::FeatureCompare(float* feat1, float* feat2) {
	return this->face_recognizer->CalcSimilarity(feat1, feat2);
}

FeatureGroup::FeatureGroup(int feat_dims, SeetaFace* seeta_face) {
	this->feat_dims = feat_dims;
	this->seeta_face = seeta_face;
}

int FeatureGroup::GetFeatureDims() {
	return this->feat_dims;
}

bool FeatureGroup::AddFeature(float* feat, string filename) {
	Feature temp;
	float* new_feat = new float[this->feat_dims];
	memcpy(new_feat, feat, sizeof(new_feat)*this->feat_dims);
	temp.data = new_feat;
	temp.filename = filename;
	this->feats.push_back(temp);
	return true;
}

bool FeatureGroup::SaveModel(string model_file) {
	std::ofstream file;
	file.open(model_file);
	file << int(this->feats.size()) << std::endl;
	file << this->feat_dims << std::endl;
	for (int i = 0; i<int(this->feats.size()); i++) {
		file << this->feats[i].filename << std::endl;
		for (int j = 0; j<this->feat_dims; j++)
			file << this->feats[i].data[j] << " ";
		file << std::endl;
	}
	file.close();
	return true;
}

FeatureGroup::FeatureGroup(string model_file, SeetaFace* seeta_face) {
	std::ifstream file;
	file.open(model_file);
	int size;
	float* new_feat;
	char* buffer = new char[1000];
	file >> size;
	file >> this->feat_dims;
	for (int i = 0; i<size; i++) {
		Feature temp;
		file.getline(buffer, 1000);
		while (buffer[0] == '\0' || buffer[0] == ' ') {
			file.getline(buffer, 1000);
		}
		temp.filename = buffer;
		new_feat = new float[this->feat_dims];
		for (int j = 0; j<this->feat_dims; j++)
			file >> new_feat[j];
		temp.data = new_feat;
		this->feats.push_back(temp);
	}
	file.close();
	this->seeta_face = seeta_face;
}

FeatureGroup::~FeatureGroup() {
	for (int i = 0; i<int(this->feats.size()); i++)
		delete[](this->feats[i].data);
}

bool FeatureGroup::FindTopK(int k, float* feat, std::vector<Feature>& result) {
	std::cout << "Calculating Similarities..." << std::endl;
	for (int i = 0; i<int(this->feats.size()); i++) {
		this->feats[i].similarity_with_goal = this->seeta_face->FeatureCompare(this->feats[i].data, feat);
	}
	std::cout << "Finding TopK..." << std::endl;
	std::priority_queue<Feature> q;
	for (int i = 0; i<int(this->feats.size()); i++)
		q.push(this->feats[i]);
	for (int i = 0; i<k; i++) {
		if (q.empty()) return true;
		result.push_back(q.top());
		q.pop();
	}

	return 0;
}
