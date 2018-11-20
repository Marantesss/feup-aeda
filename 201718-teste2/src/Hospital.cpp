/*
 * Hospital.cpp
 */

#include "Hospital.h"
//
#include <algorithm>


Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const {
	unsigned numPatients = 0;
	// DUVIDA: PORQUE RAZAO TEMOS QUE USAR O AUX
	list<Doctor> aux = doctors;
	list<Doctor>::iterator it;
	for (it = aux.begin(); it != aux.end(); it++) {
		if (it->getMedicalSpecialty() == medicalSpecialty) {
			numPatients += it->getPatients().size();
		}
	}
	return numPatients;
}

bool compareDoctors(const Doctor &d1, const Doctor &d2) {
	if (d1.getPatients().size() < d2.getPatients().size()) // Caso base
		return true;
	else if (d1.getPatients().size() == d2.getPatients().size()) { // empate de +acientes
		if (d1.getMedicalSpecialty() < d2.getMedicalSpecialty()) {
			return true;
		}
		else if (d1.getMedicalSpecialty() == d2.getMedicalSpecialty()) {	// empate de especialidade
			if (d1.getCode() < d2.getCode()) { // codigo desempata
				return true;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

void Hospital::sortDoctors() {
	// using default comparison (operator <):
	// std::sort (myvector.begin(), myvector.begin()+4);

	// using function as comp
	// std::sort (myvector.begin()+4, myvector.end(), myfunction);
	this->doctors.sort(compareDoctors);
}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
	list<Doctor> aux = doctors;
	list<Doctor>::iterator it;
	int DoctorsWithSameSpecialty = 0;
	for (it = aux.begin(); it != aux.end(); it++) {
		if (it->getMedicalSpecialty() == medicalSpecialty1) {
			DoctorsWithSameSpecialty++;
		}
	}
	if (DoctorsWithSameSpecialty < 3) {
		Doctor newDoctor(codM1, medicalSpecialty1);
		doctors.push_back(newDoctor);
		return true;
	}
	else return false;
}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {
	queue<Patient> p1;
	list<Doctor>::iterator it;
	// DUVIDA: AQUI JÁ NAO É PRECISO AUX
	for (it = doctors.begin(); it != doctors.end(); it++) {
		if (it->getCode() == codM1) {
			p1 = it->getPatients();
			doctors.erase(it);
			return p1;
		}
	}
	throw DoctorInexistent();
	// return p1;
}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {
	list<Doctor>::iterator it;
	list<Doctor>::iterator it_lessBusy;
	bool found = false;
	// DUVIDA: AQUI JÁ NAO É PRECISO AUX
	for (it = doctors.begin(); it != doctors.end(); it++) {
		if (it->getMedicalSpecialty() == medicalSpecialty1 && it_lessBusy->getPatients().size() > it->getPatients().size()) {
			it_lessBusy = it;
			found = true;
		}
	}
	if (found) {
		Patient p(cod1, medicalSpecialty1);
		it_lessBusy->addPatient(p);
	}
	return false;
}



void Hospital::processPatient(unsigned codM1) {
	list<Doctor>::iterator it;
	list<stack<Patient> >::iterator it_tray;
	Patient removedPatient(0,"");
	for (it = doctors.begin(); it != doctors.end(); it++) {
		if (it->getCode() == codM1) {
			removedPatient = it->removeNextPatient();
			for(it_tray = letterTray.begin(); it_tray != letterTray.end(); it_tray++) {
				if(it_tray->size() < trayCapacity) {
					it_tray->push(removedPatient);
					return;
				}
			}
			stack<Patient> newTray;
			newTray.push(removedPatient);
			addTrays(newTray);
		}
	}
}


unsigned Hospital::removePatients(unsigned codP1) {
	unsigned int contador = 0;
	for (auto iterator = letterTray.begin(); iterator != letterTray.end(); iterator++) {
		if (!iterator->empty()) {
			if (iterator->top().getCode() == codP1) {
				iterator->pop();
				contador++;
			}
		}
		if (iterator->empty())
			iterator = letterTray.erase(iterator);
	}
	return contador;
}



