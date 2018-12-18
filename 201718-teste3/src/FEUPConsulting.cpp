/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
	BSTItrIn<Expertize> it(expertizes);
	// Percorre a BST
	while (!it.isAtEnd()) {
		// Encontrou
		if (it.retrieve().getCost() == cost && it.retrieve().getName() == expertizeAvailable) {
			it.retrieve().addConsultant(student);
			return;
		}
		it.advance();
	}
	// Nao Encontrou
	Expertize e(expertizeAvailable, cost);
	e.addConsultant(student);
	expertizes.insert(e);
	return;
}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
	BSTItrIn<Expertize> it(expertizes);
	// Percorre a BST
	while (!it.isAtEnd()) {
		// Custo e expertize do project e igual ao custo e nome da expertize
		if (it.retrieve().getCost() == project->getCost() && it.retrieve().getName() == project->getExpertize()) {
			vector<Student*> candidateConsultants = it.retrieve().getConsultants();
			for (unsigned i = 0; i < candidateConsultants.size(); i++) {
				// O Student nao tem nenhum projeto associado
				if (candidateConsultants[i]->getCurrentProject() == "")
					temp.push_back(candidateConsultants[i]);
			}
		}
		it.advance();
	}
	return temp;

}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
	// verifica se o project ja tem student associado
	if (project->getConsultant() != NULL)
		return false;

	// verifica se o student ja tem project
	if (student->getCurrentProject() != "")
		return false;

	// verifica se o student esta interessado em project
	vector<Student*> availableStudents = getCandidateStudents(project); // Students interessado
	for (unsigned i = 0; i < availableStudents.size(); i++) {
		if (availableStudents[i]->getName() == student->getName()) {
			student->addProject(project->getTitle());
			project->setConsultant(student);
			return true;
		}
	}
	return false;
}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
	students.insert(student);
}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	students.erase(student);		// Remove the student
	student->setEMail(newEMail);	// Change his EMail
	students.insert(student);		// Insert it back with the new email
}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
	for (unsigned int i = 0; i < candidates.size(); i++) {
		if (candidates[i].getPastProjects().size() >= (unsigned)min)
			activeStudents.push(candidates[i]);
	}
}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
	stack<Student> studentStack;
	studentStack.push(activeStudents.top());
	activeStudents.pop();
	if (studentStack.top().getPastProjects().size() == activeStudents.top().getPastProjects().size()) {
		activeStudents.push(studentStack.top());
		studentStack.pop();
		return 0;
	}
	else {
		activeStudents.push(studentStack.top());
		studentStack.pop();
		studentMaximus = activeStudents.top();
		return activeStudents.size();
	}

}
