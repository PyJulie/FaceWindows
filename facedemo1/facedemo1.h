#pragma once

#include <QtWidgets/QMainWindow>
#include <qfiledialog.h>
#include <string>
#include <qdebug.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ui_facedemo1.h"
#include "face_detection.h"
#include "face_alignment.h"
#include "face_identification.h"
#include <fstream>
#include <io.h>
#include<queue>
#include<vector>
using namespace std;
class Detector : public seeta::FaceDetection {
public:
	Detector(const char * model_name);
};
class facedemo1 : public QMainWindow
{
	Q_OBJECT

public:
	facedemo1(QWidget *parent = 0);
	~facedemo1();
	QImage* image;
	int ImageFaceDetection(QString filename);
	QString GetFileName();
private:
	Ui::facedemo1Class ui;

	private slots:
	void UpLoadImageButtonClicked();
	void BuildDataBaseClicked();
	void ShowStudentInfoClicked();
};



class SeetaFace {
public:
	SeetaFace();
	Detector* detector;
	seeta::FaceAlignment* point_detector;
	seeta::FaceIdentification* face_recognizer;
	bool GetFeature(string filename, float* feat);
	bool GetFeature2(string filename, float* feat, std::vector<seeta::FaceInfo> faces);
	float* NewFeatureBuffer();
	float FeatureCompare(float* feat1, float* feat2);
	int GetFeatureDims();

};

struct Feature {
	string filename;
	float* data;
	float similarity_with_goal;
	friend bool operator< (Feature f1, Feature f2) {
		return f1.similarity_with_goal < f2.similarity_with_goal;
	}
};


class FeatureGroup {
public:
	FeatureGroup(int feat_dims, SeetaFace* seeta_face);
	FeatureGroup(string model_file, SeetaFace* seeta_face);
	std::vector<Feature> feats;
	bool AddFeature(float* feat, string filename);
	bool SaveModel(string model_file);
	int GetFeatureDims();
	bool FindTopK(int k, float* feat, std::vector<Feature>& result);
	~FeatureGroup();
private:
	int feat_dims;
	SeetaFace* seeta_face;
};

