#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <map>

#include "Kreuzung.h"

class Simulation
{
public:

	// Einlesefunktion
	void vEinlesen(std::istream& in, bool bMitGrafik = false);

	// Simuliert alles
	void vSimulieren(double dDauer, double dZeitschritt);

private:

	// Hilfsfunktionen
	void vKreuzungEinlesen(std::istream& in);
	void vStrasseEinlesen(std::istream& in);
	void vPKWEinlesen(std::istream& in);
	void vFahrradEinlesen(std::istream& in);

	std::map<std::string,std::shared_ptr<Kreuzung>> p_pKreuzungen;

	// vSimulieren benötigt diese Info
	bool p_bMitGrafik = false;
};

#endif /* SIMULATION_H_ */
