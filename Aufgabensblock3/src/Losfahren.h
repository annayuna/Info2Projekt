/*
 * Losfahren.h
 *
 *  Created on: 03.12.2024
 *      Author: annaroessel
 */

#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_

#include "Fahrausnahme.h"

class Losfahren : public Fahrausnahme {
public:
	Losfahren(Weg& aWeg, const Fahrzeug& aFzg);
	virtual ~Losfahren();

	void vBearbeiten() const override;
};

#endif /* LOSFAHREN_H_ */
