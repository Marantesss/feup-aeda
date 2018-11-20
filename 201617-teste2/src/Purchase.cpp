/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {
	Article *newArticle = new Article(this->client, barCode);
	newArticle->setPresent(present);
	newArticle->setDeliverHome(deliverHome);
	return newArticle;
}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {
	list< stack<Article*> >::iterator it;
	for (it = bags.begin(); it!= bags.end(); it++) {
		if (it->size() < 5) {
			it->push(article);
			return;
		}
	}
	stack<Article *> newBag;
	newBag.push(article);
	bags.push_back(newBag);
}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {
	vector<Article*> presents;
	list< stack<Article*> >::iterator it;
	stack<Article*> auxBag;
	for (it = bags.begin(); it!= bags.end(); it++) {
		while (!it->empty()) {
			if (it->top()->getPresent())
				presents.push_back(it->top());
			else
				auxBag.push(it->top());
			it->pop();
		}
		while(!auxBag.empty()) {
			it->push(auxBag.top());
			auxBag.pop();
		}
	}
	return presents;

}

