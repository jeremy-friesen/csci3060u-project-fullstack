#include "bid.h"
#include <string>

//Contains the advertisement listings
struct Advertisement{
	
	std::string itemName; //stores item name
	std::string seller; //seller of item
	int daysRemaining; //days until advertisement ends
	double minimumBid; //lowest possible bid
	Bid highestBid; //current highest bid
	
	//initialize values
	Advertisement(std::string newItem, std::string newSeller, int numDays, double minBid){
		itemName = newItem;
		seller = newSeller;
		daysRemaining = numDays;
		minimumBid = minBid;
		Bid highestBid;
		
		//write the advertisement to file
	}
		
	/** Adds a new bid if the amount is high enough
	 * Bid newBid - the new bid being added
	 */
	void addBid(Bid newBid){
		if (newBid.amount > minimumBid && newBid.amount > highestBid.amount){
			highestBid = newBid;
			//write to file
		}
	}
};
