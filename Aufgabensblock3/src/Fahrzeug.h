/*
 * Fahrzeug.h
 *
 *  Created on: 29.10.2024
 *      Author: annaroessel
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include "Simulationsobjekt.h"
#include "Verhalten.h"

class Weg;

extern double dGlobaleZeit; //verweisen auf das dglobal in der main

class Fahrzeug : public Simulationsobjekt {
public:
	Fahrzeug(); // const; string wird nicht vom konstruktor geäandert
	Fahrzeug(const std::string& s, const double d = 0);
	Fahrzeug(const Fahrzeug& tFahrzeug) = delete;
	virtual ~Fahrzeug();

	virtual void vAusgeben(std::ostream& out) const override;
	static void vKopf();
	virtual void vSimulieren() override;
	//virtual double dTanken();
	virtual double dTanken(const double dMenge = std::numeric_limits<double>::infinity()); //bei default wird vollgetankt
	virtual double dGeschwindigkeit() const;
	bool operator<(const Fahrzeug& tFahrzeug) const;
	void operator=(const Fahrzeug& tFahrzeug);

	void vNeueStrecke(Weg& aWeg);
	void vNeueStrecke(Weg& aWeg, const double dStartZeit);

	double getAbschnittStrecke() const;
	bool getbLiegengeblieben() const;

	virtual void vZeichnen(const Weg& aWeg) const;

	virtual void vEinlesen(std::istream& in) override;


protected:
	const double p_dMaxGeschwindigkeit = 0;
	double p_dGesamtStrecke = 0;
	double p_dAbschnittStrecke = 0;
	double p_dGesamtZeit = 0;
	std::unique_ptr<Verhalten> p_pVerhalten = nullptr;
	bool p_bLiegengeblieben = false;


};

#endif /* FAHRZEUG_H_ */
