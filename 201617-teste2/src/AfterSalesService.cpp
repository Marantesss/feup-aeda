/*
 * AfterSalesService.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include <algorithm>
#include "AfterSalesService.h"

using namespace std;

int AfterSalesService::tableOrdinal = 0;

AfterSalesService::AfterSalesService(int toWrapQS) : toWrapQueueSize(toWrapQS) {
}

vector<Article*> AfterSalesService::getPresentsTable() const {
	return presentsTable;
}

queue<Article*> AfterSalesService::getToWrap() const {
	return toWrap;
}

queue<Article*> AfterSalesService::getToDeliver() const {
	return toDeliver;
}

/**
 *  Place presents on the presents table, assigning them a relative present number and a sequential number.
 *  Assumes all given presents are from the same client.
 */
void AfterSalesService::dropPresentsOnTable(vector<Article*> presents) {
	for(vector<Article*>::size_type i = 0; i<presents.size(); i++) {
		presents[i]->setPresentNumber(i+1);
		presents[i]->setArrivalNumber(++tableOrdinal);
		presentsTable.push_back(presents[i]);
	}
}

/**
 * Remove from the table all articles of a given client.
 */
vector<Article*> AfterSalesService::pickPresentsFromTable(long client) {
	vector<Article*> clientPresents;
	vector<Article*>::iterator it;
	for(it = presentsTable.begin(); it != presentsTable.end(); it++) {
		if ((*it)->getClient() == client) { // porque it é um "pointer" para um pointer
			clientPresents.push_back(*it);
			it = presentsTable.erase(it) - 1; // Há uma forma melhor de fazer isto?
		}
	}
	return clientPresents;
}

/**
 * Sort the first 10 articles in the presents table:
 *   (i) give priority to articles that are NOT to be delivered at home (client is waiting);
 *  (ii) if two articles have (relative) present numbers differing more than 2,
 *       the one with lower present number should have priority (clients should not wait too much);
 * (iii) else, maintain article order in the table.
 */
bool comparePresents (Article *a1, Article *a2) {
	if (!a1->getDeliverHome() && !a2->getDeliverHome()) {
		if ((a1->getArrivalNumber() - a2->getArrivalNumber()) > 2)
			return true;
		else if (a1->getArrivalNumber() > a2->getArrivalNumber())
			return true;
		else
			return false;
	}
	else if (a1->getArrivalNumber() > a2->getArrivalNumber())
		return true;
	else
		return false;
}



void AfterSalesService::sortArticles() {
	sort(presentsTable.begin(), presentsTable.begin()+10, comparePresents);
	vector<Article*>::iterator it;
	for (it = presentsTable.begin(); it != presentsTable.end(); it++) {
		if ((*it)->getDeliverHome()) {
			presentsTable.push_back(*it);
			presentsTable.erase(it);
		}
	}
}

/**
 * Move the first presents in the table to the queue of presents to wrap, taking into account the size of the queue.
 */
void AfterSalesService::enqueueArticles() {
	vector<Article*>::iterator it;
	int newPresents = toWrapQueueSize - toWrap.size();
	if (newPresents) {
		for (int i = 0; i < newPresents; i++) {
			toWrap.push(presentsTable[0]);
			presentsTable.erase(presentsTable.begin());
		}
	}
}

/**
 * Process the first present to wrap. If it is an article to deliver home, the article is placed in the toDeliver queue.
 */
Article* AfterSalesService::wrapNext() {
	Article *wrappedPresent = presentsTable[0];
	presentsTable.erase(presentsTable.begin());
	if (wrappedPresent->getDeliverHome()) {
		toDeliver.push(wrappedPresent);
		return NULL;
	} else
		return wrappedPresent;
}

