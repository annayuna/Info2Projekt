/*
 * Weg.cpp
 *
 *  Created on: 03.12.2024
 *      Author: annaroessel
 */

#include "Weg.h"
#include "Fahrausnahme.h"
#include <iomanip>

Weg::Weg(const std::string& s, const double l, const Tempolimit t) :
		Simulationsobjekt(s), p_dLaenge(l), p_eTempolimit(t)
{
}

Weg::~Weg()
{
}

void Weg::vSimulieren()
{
	p_pFahrzeuge.vAktualisieren();
	for(const auto& fahrzeug : p_pFahrzeuge)
	{
		try
		{
			fahrzeug -> vSimulieren();
		}
		catch (const Fahrausnahme& aFahrausnahme)
		{
			aFahrausnahme.vBearbeiten();
		}
	}
	p_pFahrzeuge.vAktualisieren();
}

double Weg::getTempolimit() const
{
	return (double) p_eTempolimit;
}

void Weg::vKopf()
{
	std::cout<<std::resetiosflags(std::ios::right)<<std::setiosflags(std::ios::left);
	std::cout<<std::setw(4)<<"ID";
	std::cout<<std::setw(15)<<"Name";
	std::cout<<std::setw(10)<<"|   Laenge";
	std::cout<<std::setw(9)<<"  Fahrzeuge" << std::endl;
	std::cout << "-----------------------------------------------------------------------------------------------------" << std::endl;
}

void Weg::vAusgeben(std::ostream& out) const
{
	Simulationsobjekt::vAusgeben(out);
	std::cout<<std::resetiosflags(std::ios::left)<<std::setiosflags(std::ios::right);
	out << 	": " << std::setw(8) << std::fixed << std::setprecision(2) << p_dLaenge << "  ( ";
	std::cout<<std::resetiosflags(std::ios::right)<<std::setiosflags(std::ios::left);
	for (const auto& fahrzeug : p_pFahrzeuge)
	{
		out << fahrzeug -> getName() << " ";
	}
	out << ")";
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFzg) //Aufnahme von fahrzeugen
{
	pFzg->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(std::move(pFzg));
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> aFzg, const double dStartZeit) //Aufnahme von parkenden Fzg
{
	aFzg->vNeueStrecke(*this, dStartZeit);
	p_pFahrzeuge.push_front(std::move(aFzg));
}

double Weg::getLaenge() const
{
	return p_dLaenge;
}

void Weg::vZeichnen() const
{
	for(const auto& fahrzeug : p_pFahrzeuge)
	{
		fahrzeug -> vZeichnen(*this);
	}
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& aFzg) //ist eigentlich nur dafür um das Fzg aus der Liste zu entfernen, welches wir von der Fahrausnahme bekommen (genauer: Streckende)
{
	for (std::list<std::unique_ptr<Fahrzeug>>::iterator it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		if(*it == nullptr) // Damit die Aufgaben noch funktionieren, bei denen Fahrzeuge kein Verhalten hatten
		{
			continue;
		}
		if(**it == aFzg)
		{
			std::unique_ptr<Fahrzeug> aFzgTemp = std::move(*it);
			p_pFahrzeuge.erase(it);
			return aFzgTemp;
		}
	}
	std::cout << "Error: Fahrzeug konnte nicht übergeben werden." << std::endl;
	return nullptr;
}





