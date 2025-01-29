/*
 * Simulationsobjekt.cpp
 *
 *  Created on: 03.12.2024
 *      Author: annaroessel
 */

#include "Simulationsobjekt.h"

#include <iomanip>

Simulationsobjekt::Simulationsobjekt(const std::string& s) :
				p_sName(s)
{
}

Simulationsobjekt::~Simulationsobjekt()
{
	std::cout << "Simulationsobjekt \"" << p_sName << "\" mit ID " << p_iID << " wurde gelöscht." << std::endl;
}

void Simulationsobjekt::vAusgeben(std::ostream& out) const
{
	out<<std::resetiosflags(std::ios::right)<<std::setiosflags(std::ios::left);
	out<<std::setw(4) << p_iID;
	out<<std::setw(15)<< p_sName;
}

bool Simulationsobjekt::operator==(const Simulationsobjekt& simObj) const
{
	return (p_iID == simObj.p_iID);
}

std::string Simulationsobjekt::getName() const
{
	return p_sName;
}

int Simulationsobjekt::getID() const
{
	return p_iID;
}

void Simulationsobjekt::vEinlesen(istream& in)
{
	if (p_sName != "")
	{
		throw runtime_error("Error: Das Objekt existiert schon.");
	}
	in >> p_sName;
}
