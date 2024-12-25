/*
 * Simulationsobjekt.h
 *
 *  Created on: 03.12.2024
 *      Author: annaroessel
 */

#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_

#include <string>
#include <iostream>

extern double dGlobaleZeit; //verweisen auf dGlobaleZeit in der main

class Simulationsobjekt {
public:
	Simulationsobjekt(const std::string& s);
	Simulationsobjekt(const Simulationsobjekt& simObj) = delete;
	virtual ~Simulationsobjekt();

	virtual void vAusgeben(std::ostream& out) const;
	virtual void vSimulieren() = 0; //Rein virtuelle Funktion, simuliert Weg oder Fahrzeug

	bool operator==(const Simulationsobjekt& simObj) const; //Operatorüberladung, vergleicht ID's miteinander

	std::string getName() const;


private:
	static int inline p_iMaxID = 0;


protected:
	std::string p_sName;
	const int p_iID = ++p_iMaxID;
	double p_dZeit = 0;

};

#endif /* SIMULATIONSOBJEKT_H_ */
