/*
 * Kreuzung.cpp
 *
 *  Created on: 25.01.2025
 *      Author: Anna
 */

#include <iostream>
#include <random>

#include "Kreuzung.h"
#include "PKW.h"


//using namespace std;

Kreuzung::~Kreuzung()
{
}

Kreuzung::Kreuzung(const Kreuzung& other)
	:Simulationsobjekt(other.p_sName), p_pWege(other.p_pWege), p_dTankstelle(other.p_dTankstelle)
{
}

Kreuzung::Kreuzung(const std::string& sName, const double dTankstelle):
		Simulationsobjekt(sName),
		p_dTankstelle(dTankstelle)
{
}

void Kreuzung::vVerbinde(std::shared_ptr<Kreuzung> aKreuzungStart, std::shared_ptr<Kreuzung> aKreuzungZiel,
			const double dLaenge, const std::string& sNameHinweg, const std::string& sNameRueckweg,
			const Tempolimit eTempolimit, const bool bUeberholverbot)
{
	std::shared_ptr<Weg> pHinweg = std::make_shared<Weg>(sNameHinweg, dLaenge, eTempolimit, bUeberholverbot, aKreuzungZiel);
	std::shared_ptr<Weg> pRueckweg = std::make_shared<Weg>(sNameRueckweg, dLaenge, eTempolimit, bUeberholverbot, aKreuzungStart);

	aKreuzungStart->p_pWege.push_back(pHinweg);
	aKreuzungZiel->p_pWege.push_back(pRueckweg);

	pHinweg->setRueckweg(pRueckweg);
	pRueckweg->setRueckweg(pHinweg);
}

void Kreuzung::vTanken(Fahrzeug* aFzg)
{
	if (aFzg == nullptr || p_dTankstelle <= 0)
	{
		return;
	}

	PKW* pkw = dynamic_cast<PKW*>(aFzg);
	if(pkw != nullptr)
	{
		double tankmenge = pkw->dTanken(std::numeric_limits<double>::infinity());
		std::cout << " Tanken: " << aFzg->getName() << " tankt " << tankmenge << " Liter." << std::endl;
		p_dTankstelle -= tankmenge;
		if(p_dTankstelle <= 0)
		{
			p_dTankstelle = 0;
		}
	}
}

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> pFzg, double dStartzeit)
{
	if(!p_pWege.empty())
	{
		vTanken(pFzg.get());
		p_pWege.front()->vAnnahme(std::move(pFzg), dStartzeit);
	}
}

void Kreuzung::vSimulieren()
{
	for (auto weg : p_pWege)
	{
		weg->vSimulieren();
		weg->vZeichnen();
	}
}

double Kreuzung::getTankstelle() const
{
	return p_dTankstelle;
}

std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& ankommenderWeg) const
{
	if (p_pWege.size() == 0)
	{
		std::cout << "Error, keine Wege vorhanden." << std::endl;
	}

    std::vector<std::shared_ptr<Weg>> moeglicheWege;
    for (auto &weg : p_pWege) {
        if (weg.get() != ankommenderWeg.getRueckweg().get()) {
            moeglicheWege.push_back(weg);
        }
    }

    if (moeglicheWege.empty()) {
    return ankommenderWeg.getRueckweg();
    }

    int zufaelligerIndex = rand() % moeglicheWege.size();
    return moeglicheWege[zufaelligerIndex];
}

/*void Kreuzung::vEinlesen(std::istream & in)
{
	Simulationsobjekt::vEinlesen(in);
	in >> p_dTankstelle;
}*/








