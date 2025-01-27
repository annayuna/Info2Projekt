/*
 * Kreuzung.cpp
 *
 *  Created on: 27.01.2025
 *      Author: Anna
 */
/*
#include <iostream>
#include <random>

#include "Kreuzung.h"
#include "Fahrzeug.h"

using namespace std;

Kreuzung::~Kreuzung()
{
}

Kreuzung::Kreuzung()
{
}

Kreuzung::Kreuzung(const std::string& sName, const double dTankstelle):
		Simulationsobjekt(sName),
		p_dTankstelle(dTankstelle)
{
}

void Kreuzung::vVerbinde(shared_ptr<Kreuzung> aKreuzungStart, shared_ptr<Kreuzung> aKreuzungZiel,
			const double dLaenge, const string& sNameHinweg, const string& sNameRueckweg,
			const Tempolimit eTempolimit, const bool bUeberholverbot)
{
	shared_ptr<Weg> pHinweg = make_shared<Weg>(sNameHinweg, dLaenge, eTempolimit, bUeberholverbot, aKreuzungZiel);
	shared_ptr<Weg> pRueckweg = make_shared<Weg>(sNameRueckweg, dLaenge, eTempolimit, bUeberholverbot, aKreuzungStart);

	aKreuzungStart->p_pWege.push_back(pHinweg);
	aKreuzungZiel->p_pWege.push_back(pRueckweg);

	pHinweg->setRueckweg(pRueckweg);
	pRueckweg->setRueckweg(pHinweg);
}

void Kreuzung::vTanken(Fahrzeug& aFzg)
{
	if (p_dTankstelle > 0)
	{
		p_dTankstelle -= aFzg.dTanken();
	}
}

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> pFzg, double dStartzeit)
{
	Kreuzung::vTanken(*pFzg);
	p_pWege.front()->vAnnahme(move(pFzg), dStartzeit);
}

void Kreuzung::vSimulieren()
{
	for (auto weg : p_pWege)
	{
		weg->vSimulieren();
		weg->vZeichnen();
	}
}

shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& aWeg) const
{
	if (p_pWege.size() == 0)
	{
		cout << "Error, keine Wege vorhanden." << endl;
	}

	// nur ein Weg an der Kreuzung
	if (p_pWege.size() == 1)
	{
		return p_pWege.front();
	}

	// Zufallszahl (iIndex) zwischen 0 und (size - 2) generieren
	static std::mt19937 device(time(NULL));
	std::uniform_int_distribution<int> dist(0, p_pWege.size()-2);
	int iIndex = dist(device);

	// Die Zufallszahl soll der Index des Weges sein
	// Der Rückweg vom vorgegebenen Weg wird hierbei ignoriert.
	list<shared_ptr<Weg>>::const_iterator it = p_pWege.begin();
	if (*it == aWeg.getRueckweg()) { it++; }
	for(int i=0; i<iIndex; i++)
	{
		it++;
		if (*it == aWeg.getRueckweg()) { it++; }
	}

	return *it;
}

double Kreuzung::getTankstelle() const
{
	return p_dTankstelle;
}

void Kreuzung::vEinlesen(istream & in)
{
	Simulationsobjekt::vEinlesen(in);
	in >> p_dTankstelle;
}

*/






