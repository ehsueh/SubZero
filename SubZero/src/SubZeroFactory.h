/*
 * SubZeroFactory.h
 *
 *  Created on: May 25, 2015
 *      Author: carl
 */

#ifndef SUBZEROFACTORY_H_
#define SUBZEROFACTORY_H_

#include "SubZero.h"
#include "util/PropertyReader.h"
#include "util/Logger.h"

//jon says to move inside class
enum SubType {GUI, SIM, AUT};

class SubZeroFactory {
private:
    Logger* logger =  new Logger("SubZeroFactory");

public:
	SubZeroFactory();
	virtual ~SubZeroFactory();

    SubZero* makeSubZero(SubType subType, PropertyReader* settings);


};

#endif /* SUBZEROFACTORY_H_ */
