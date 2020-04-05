#include <string>

//Contains a single bid information
struct Bid{
	std::string buyer; //name of buyer
	std::string seller; //name of seller
	std::string itemName; //name of item
	double amount; //amount of bid

	//initialize
	Bid(std::string buyerName, std::string sellerName, std::string bidItem, double bidAmount){
		buyer = buyerName;
		seller = sellerName;
		itemName = bidItem;
		amount = bidAmount;
	}
	
	//default values
	Bid(){
		amount = 0;
	}
};

