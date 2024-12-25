/*
 * Parken.h
 *
 *  Created on: 03.12.2024
 *      Author: annaroessel
 */

#ifndef PARKEN_H_
#define PARKEN_H_

#include "Verhalten.h"

class Parken : public Verhalten {
public:
	Parken(Weg& aWeg, const double dStartZeit);
	virtual ~Parken();

	double dStrecke(const Fahrzeug& aFzg, const double dZeitIntervall) const override;

private:
	const double p_dStartZeit = 0;
};

#endif /* PARKEN_H_ */
