/*
 * CameraInterface.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: ahsueh1996
 */

#include "CameraInterface.h"

/* ==========================================================================
 * 				INTERACTING WITH DATA COMING IN (FROM Camera)
 * ==========================================================================
 * This interface class will be automatically polling and managing
 * the polling process privately within the interface at pollFrequency
 * using the functions below.
 */

/**
 * Poll raw data from the camera.
 * @return	data polled
 */

void CameraInterface::poll() {

	cv::Mat raw;
	camStream.read(raw);
	Data* decoded = this->decode(&raw);
	this->storeToBuffer(decoded);

};

/**
 * Decode the data.
 * @param	data	data to be decoded
 * @return	decoded data in a ImgData format
 */
ImgData* CameraInterface::decode(cv::Mat* data) {

	ImgData decoded = new ImgData("raw", data);
	return decoded;

};

/* ==========================================================================
 * 							CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */


CameraInterface::CameraInterface(int bufferSize, int pollFrequency) {

	this->bufferSize = bufferSize;
	this->pollFrequency = pollFrequency;
	this->camStream(0);

	// thread for reading and polling camera input
   readThreads.push_back(std::thread(&FPGAInterface::in, this));

}

CameraInterface::~CameraInterface() {

	// join readThread with main
	for(auto& t: readThreads) {t.join();}

	// clears the queue
	while ( ! decodedBuffer.empty()) {
		decodedBuffer.pop();
	}
	// not sure if the above also frees up memory used up by the "queue container"
	// whatever the container may be... delete it by following the pointer
	delete &(this->decodedBuffer);
	delete &(this->bufferSize);
	delete &(this->pollFrequency);
	delete position;
	delete camStream;

}
