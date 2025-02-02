/*
 * Verhalten.h
 *
 *  Created on: 03.12.2024
 *      Author: annaroessel
 */

#ifndef VERHALTEN_H_
#define VERHALTEN_H_

class Weg;
class Fahrzeug;

class Verhalten {
public:
	Verhalten(Weg& aWeg);
	virtual ~Verhalten();

	virtual double dStrecke(const Fahrzeug& aFzg, const double dZeitIntervall) const = 0; //berechnet Strecke

	const Weg& getWeg() const;

protected:

	Weg& p_pWeg;
};

#endif /* VERHALTEN_H_ */
