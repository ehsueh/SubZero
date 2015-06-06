/*
 * StateTester.cpp
 *
 *  Created on: May 30, 2015
 *      Author: james
 */
/*
 * Class to test state functions
 * @author James
 *
 */
#include "StateTester.h"

ImgData* StateTester::generateImgData(std::string id, std::string msg){
	cv::Mat *m = new cv::Mat(10, 10, 2);
	ImgData *d = new ImgData(id, m);
	d->setMsg(msg);
	return d;
}

std::vector<ImgData*> StateTester::generateImgVector(int i){
	std::vector<ImgData*> vec;
	if (i == 1){
		vec.push_back(generateImgData("First", "msg1"));
		vec.push_back(generateImgData("Second", "msg2"));
		vec.push_back(generateImgData("Third", "msg3"));
	}else if (i == 2){
		vec.push_back(generateImgData("1", "one"));
		vec.push_back(generateImgData("2", "two"));
		vec.push_back(generateImgData("3", "three"));
		vec.push_back(generateImgData("4", "four"));
		vec.push_back(generateImgData("5", "five"));
		vec.push_back(generateImgData("6", "six"));
		vec.push_back(generateImgData("7", "seven"));
		vec.push_back(generateImgData("8", "eight"));
		vec.push_back(generateImgData("9", "nine"));
		vec.push_back(generateImgData("10", "ten"));
	}
	else{

	}
	return vec;
}


FPGAData* StateTester::generateFPGAData(std::string id, std::string msg){
	FPGAData *d = new FPGAData(id, 1, 2, 3);
	d->setMsg(msg);
	return d;
}
std::vector<FPGAData*> StateTester::generateFPGAVector(int i){
	std::vector<FPGAData*> vec;
	if (i == 1){
		vec.push_back(generateFPGAData("First", "msg1"));
		vec.push_back(generateFPGAData("Second", "msg2"));
	}else if (i == 2){
		vec.push_back(generateFPGAData("1", "one"));
		vec.push_back(generateFPGAData("2", "two"));
		vec.push_back(generateFPGAData("3", "three"));
		vec.push_back(generateFPGAData("4", "four"));
	}
	else{

	}
	return vec;
}



/**
 * Test the basic State; make sure it can be created and an image stored
 */
bool StateTester::testImgBasics(){
	CameraState cs;

	cs.setState(generateImgVector(1));
	return cs.getState("First")->getMsg().compare("msg1") == 0;
}

/**
 * Tests if State is discarding older frames if its longer than its' specified length
 * Tests the above for both constructors
 */
bool StateTester::testImgSize(){
	CameraState CS;
	CS.setState(generateImgVector(1));
	for (int i = 0; i < 10; i++){
		CS.setState(generateImgVector(2));
	}
	CS.getState("First", 10);
	CS.getState("1", 9);
	CS.getState("First", 11);
	//===================================================

	CameraState cs(8);

	cs.setState(generateImgVector(1));
	for (int i = 0; i < 7; i++){
		cs.setState(generateImgVector(2));
	}

	//Logger::trace(cs.getState("First", 7)->getMsg());
	cs.setState(generateImgVector(2));
	//Logger::trace(cs.getState("First", 8)->getMsg());
	cs.setState(generateImgVector(2));

	return cs.getState("First", 9) == 0;
}

bool StateTester::testFPGABasics(){
	FPGAState fs;
	fs.setState(generateFPGAVector(1));

	return fs.getState("First")->getMsg().compare("msg1") == 0;
}

bool StateTester::testFPGASize(){
	FPGAState FS;
	FS.setState(generateFPGAVector(1));
	for (int i = 0; i < 10; i++){
		FS.setState(generateFPGAVector(2));
	}
	/*
	std::cout<<FS.getState("First", 10);
	std::cout<<" ";
	std::cout<<FS.getState("1", 9);
	std::cout<<" ";
	std::cout<<FS.getState("First", 11) << std::endl;*/
	//===================================================

	FPGAState fs(8);

	fs.setState(generateFPGAVector(1));
	for (int i = 0; i < 7; i++){
		fs.setState(generateFPGAVector(2));
	}

	//Logger::trace(fs.getState("First", 7)->getMsg());
	fs.setState(generateFPGAVector(2));
	//Logger::trace(fs.getState("First", 8)->getMsg());
	fs.setState(generateFPGAVector(2));

	return fs.getState("First", 9) == 0;
}

void StateTester::run(){
	StateTester st;
	Logger::trace("===========Starting Image State Testing===========");

	//========================================================================
	Logger::trace("-----Testing basics-----");
	if (st.testImgBasics())
		Logger::trace("Basics passed");
	else
		Logger::trace("Basics test FAILED");

	//========================================================================
	Logger::trace("-----Testing size-----");
	if (st.testImgSize())
		Logger::trace("Size passed");
	else
		Logger::trace("Size test FAILED");


	Logger::trace("============End Image State Testing===============");
	//===============================================================================================
	//									FPGA State testing
	//===============================================================================================
	Logger::trace("===========Starting FPGA State Testing===========");

	//========================================================================
	Logger::trace("-----Testing basics-----");
	if (st.testFPGABasics())
		Logger::trace("Basics passed");
	else
		Logger::trace("Basics test FAILED");

	//========================================================================
	Logger::trace("-----Testing size-----");
	if (st.testFPGASize())
		Logger::trace("Size passed");
	else
		Logger::trace("Size test FAILED");


	Logger::trace("============End FPGA State Testing===============");

}

