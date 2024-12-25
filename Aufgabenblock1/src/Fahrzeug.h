/*
 * Fahrzeug.h
 *
 *  Created on: 29.10.2024
 *      Author: annaroessel
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include <string>

extern double dGlobaleZeit; //verweisen auf das dglobal in der main

class Fahrzeug {
public:
	Fahrzeug();
	Fahrzeug(const std::string& s); // const; string wird nicht vom konstructor geäandert
	Fahrzeug(const std::string& s, const double d);
	Fahrzeug(const Fahrzeug& tFahrzeug) = delete;
	virtual ~Fahrzeug();

	virtual void vAusgeben(std::ostream& out) const;
	static void vKopf();
	virtual void vSimulieren();
	virtual double dTanken(const double dMenge = std::numeric_limits<double>::infinity()); //bei default wird vollgetankt
	virtual double dGeschwindigkeit() const;
	bool operator<(const Fahrzeug& tFahrzeug) const;
	void operator=(const Fahrzeug& tFahrzeug);


private:
	static int inline p_iMaxID = 0;


protected:
	std::string p_sName;
	const int p_iID = ++p_iMaxID;
	const double p_dMaxGeschwindigkeit=0;
	double p_dGesamtStrecke=0;
	double p_dGesamtZeit=0;
	double p_dZeit=0;

};

#endif /* FAHRZEUG_H_ */
