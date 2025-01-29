/*
 * PKW.h
 *
 *  Created on: 02.12.2024
 *      Author: annaroessel
 */

#ifndef PKW_H_
#define PKW_H_

#include "Fahrzeug.h"

#include <limits>

class PKW : public Fahrzeug
{
public:

	PKW(const std::string& sName, const double dMaxGeschwindigkeit, const double dVerbrauch, const double p_dTankvolumen = 55.0);
	virtual ~PKW();

	// PKW tankt voll oder dMenge
	// return: getankte Menge
	//double dTanken() override;
	double dTanken(const double dMenge) override;

	// Berechnung der Geschwindigkeit
	double dGeschwindigkeit() const override;

	void vSimulieren() override;

	void vAusgeben(std::ostream& out) const override;

	void vZeichnen(const Weg& aWeg) const override;

private:
	const double p_dVerbrauch = 0.0;
	const double p_dTankvolumen = 55.0;
	double p_dTankinhalt = p_dTankvolumen / 2;

};

#endif /* PKW_H_ */
