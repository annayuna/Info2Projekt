/*
 * Parken.cpp
 *
 *  Created on: 03.12.2024
 *      Author: annaroessel
 */

#include "Parken.h"
#include "Losfahren.h"

extern double dGlobaleZeit;

Parken::Parken(Weg& aWeg, double dStartZeit) :
		Verhalten(aWeg), p_dStartZeit(dStartZeit)
{
}

Parken::~Parken()
{
}


double Parken::dStrecke(const Fahrzeug& aFzg, const double dZeitIntervall) const
{
	// Exception, wenn p_dStartZeit erreicht wurde
	if (p_dStartZeit - 1e-10 <= dGlobaleZeit)
	{
		throw Losfahren(p_pWeg, aFzg);
	}

	// gefahrene Strecke ist bei Parken immer 0
	return 0.0;
}