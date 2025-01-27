/*
 * Fahren.cpp
 *
 *  Created on: 03.12.2024
 *      Author: annaroessel
 */

#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

Fahren::Fahren(Weg& aWeg) :
		Verhalten(aWeg)
{
}

Fahren::~Fahren()
{
}


double Fahren::dStrecke(const Fahrzeug& aFzg, const double dZeitIntervall) const
{

	double dVerbleibendeStrecke = p_pWeg.getLaenge() - aFzg.getAbschnittStrecke();
	if(dVerbleibendeStrecke < 1e-10)
	{
		throw Streckenende(p_pWeg, aFzg); // Exception, falls am Streckenende angekommen
	}
	// Distanz, die das Fahrzeug ohne Einschränkungen zurücklegen könnte
	double dFahrzeugStrecke = aFzg.dGeschwindigkeit() * dZeitIntervall;

	if(p_pWeg.getUeberholverbot())
	{
		double distToFzgInFront = -1; //damit, wenn er nichts findet, dass er später immer noch die comparison machen kann
		std::vector fzgPositions = p_pWeg.getFzgPositions();
		for(auto &fz : fzgPositions)
		{
			if(fz[0] == aFzg.getID())
			{
				continue; //geht dann direkt in die nächste Iteration über
			}
			double abstand = fz[1] - aFzg.getAbschnittStrecke();
			if(abstand > distToFzgInFront) distToFzgInFront = abstand;
		}

		if(distToFzgInFront > 0 && distToFzgInFront < dVerbleibendeStrecke && distToFzgInFront < dFahrzeugStrecke)
		{
			return distToFzgInFront - 0.5; //damit er nicht auffährt
		}
	}
	return (dVerbleibendeStrecke < dFahrzeugStrecke) ? dVerbleibendeStrecke : dFahrzeugStrecke;
}
