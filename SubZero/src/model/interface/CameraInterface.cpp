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


	};

	/**
	 * Decode the data.
	 * @param	data	data to be decoded
	 * @return	decoded data in a ImgData format
   	 */
	ImgData* CameraInterface::decode(cv::Mat* data) {

	};


	/* ==========================================================================
	 * 							MANAGING DATA BUFFER
	 * ==========================================================================
	 * The data buffer will be managed automatically and privately by this class.
	 * These functions are defined and implemented in the root parent class i.e.
	 * in HwInterface.
	 */

	void CameraInterface::deleteFromBuffer(int startIdx, int endIdx);

	void CameraInterface::storeToBuffer(Data* data);

public:

	/* ==========================================================================
	 * 							CONSTRUCTOR AND DESTRUCTOR
	 * ==========================================================================
	 */

	CameraInterface::CameraInterface(int bufferSize, int pollFrequency, CameraPosition position) {
		camStream(this.position);
	};

	CameraInterface::~CameraInterface() {
		delete camStream;
	};

