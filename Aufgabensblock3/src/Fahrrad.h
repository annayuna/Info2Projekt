/*
 * Fahrrad.h
 *
 *  Created on: 31.10.2024
 *      Author: annaroessel
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug {

public:
	Fahrrad();
	Fahrrad(const std::string& sName, const double dMaxGeschwindigkeit);
	virtual ~Fahrrad();

	double dGeschwindigkeit() const override;

	void vZeichnen(const Weg& aWeg) const override;

	void vEinlesen(std::istream& in) override;
};

#endif /* FAHRRAD_H_ */
