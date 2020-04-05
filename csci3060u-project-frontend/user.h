#include <fstream>
#include <iostream>
#include <cstdlib>
//#include <cstdio>
#include <iostream>
#include <string.h>
#include <string>
const char* accountFile = "accounts.txt";
const char* tempFile = "temp.txt";
const char* itemFile = "items.txt";

// Copies information from temporary file to the main file
void updateFile(std::string fileToUpdate, std::string temporaryFile){
	std::ifstream iFile;
	std::ofstream oFile;
	
	// open input file
	iFile.open(temporaryFile);
	if(iFile.is_open()){
		
		oFile.open(fileToUpdate);
		if(oFile.is_open()){
			std::string line;
			
			while(std::getline(iFile, line)){
				oFile << line << "\n";
			}
			
			oFile.close();
		} else {
			printf("ERROR: Input file not opened\n");
		}
		
		iFile.close();
	} else {
		printf("ERROR: Input file not opened\n");
	}
}

float round2Places(float var) 
{ 
    float value = (int)(var * 100 + .5); 
    return (float)value / 100; 
} 

struct User{
	std::string username_;
	std::string password_;
	std::string accountType_;
	float credit_;
	
	User(){
		
	}
	
	// constructor
	User(std::string username, std::string password, std::string accountType, float credit){
		username_ = username;
		password_ = password;
		accountType_ = accountType;
		credit_ = credit;
	}
	
	virtual ~User() = default;
	
	void createUser(std::string username, std::string type, double credit, std::string password){ printf("ERROR: No permission to use createUser");}
	
	std::string getType(){
		if (accountType_ == "admin"){
			return "AA";
		}
		else if (accountType_ == "buy-standard"){
			return "BS";
		}
		else if (accountType_ == "sell-standard"){
			return "SS";
		}
		else if (accountType_ == "full-standard"){
			return "FS";
		}
		return "_";
	}
	
	std::string getCreditString(){
		std::string sCredit = std::to_string(credit_);
		
		int decimalPos = sCredit.find('.');
		if (decimalPos == string::npos){
			sCredit += ".00";
		}
		else if (decimalPos == sCredit.length()-2){
			sCredit += "0";
		}
		else{
			sCredit = sCredit.substr(0, decimalPos + 3);
		}
		
		return sCredit;
	}
	
};

struct FullStandard : User{
	
	FullStandard(std::string username, std::string password, double credit)
	: User(username, password, "full-standard", credit)
	{
		// intentionally left blank
	}
	
	std::string bid(std::string seller, std::string itemName){
		std::ifstream iItemFile;
		std::ofstream oTempFile;
		bool advertisementFound = false;
		double currentBid;
		double newBid;
		std::string newBidString;
		
		iItemFile.open(itemFile);
		if(iItemFile.is_open()){
			std::string line;
			while(getline(iItemFile, line)){
				std::string info[5];
				
				info[0] = line.substr(0, 25);
				info[1] = line.substr(26, 15);
				info[2] = line.substr(42, 15);
				info[3] = line.substr(58, 3);
				info[4] = line.substr(62, 6);
				
				if(info[1].substr(0, seller.length()) == seller && info[0].substr(0, itemName.length()) == itemName){
					std::string bidValue = info[4].substr(info[4].find_first_not_of("0"));
					currentBid = std::stod(bidValue);
					advertisementFound = true;
				}
			}
			
			iItemFile.close();
			
			if(advertisementFound){
				std::cout << "Current bid: " << currentBid << "\n";
				std::cout << "Enter your bid: \n";
				std::cin >> newBidString;
				newBid = std::stod(newBidString);
				if(newBid <= currentBid * 1.05){
					printf("ERROR: new bid must be at least 5%% greater than the current highest bid for standard-buy accounts\n");
					return NULL;
				}
		
				iItemFile.open(itemFile);

				if(iItemFile.is_open()){
					oTempFile.open(tempFile);
					
					if(oTempFile.is_open()){

						while(getline(iItemFile, line)){
							std::string info[5];
							info[0] = line.substr(0, 25);
							info[1] = line.substr(26, 15);
							info[2] = line.substr(42, 15);
							info[3] = line.substr(58, 3);
							info[4] = line.substr(62, 6);
							
							std::string possibleItemName = info[0].substr(0, itemName.length());
							std::string possibleSellerName = info[1].substr(0, seller.length());
					//		std::cout << newBid << " " << (std::to_string(newBid)).length();
					//		std::cout << possibleItemName << "end\n" << possibleSellerName << "end\n" << newBid << "end\n";
					//		std::cout << (possibleItemName.compare(itemName)) << " " << possibleSellerName.compare(seller);
					
							if(possibleItemName.compare(itemName) == 0 && possibleSellerName.compare(seller) == 0){

								oTempFile << info[0] << " " << info[1] << " " << username_;
								for(int i = 0; i < 15 - username_.length(); i++){
									oTempFile << " ";
								}

								oTempFile << " " << info[3] << " ";
								for(int i = 0; i < 6 - newBidString.length(); i++){
									oTempFile << "0";
								}

								oTempFile << newBid << "\n";
							} else {

								oTempFile << line << "\n";
							}
						}
						
						iItemFile.close();
						oTempFile.close();
						updateFile(itemFile, tempFile);
						printf("Bid placed\n");
						
						return newBidString;
					} else {
						printf("ERROR: Temp file not opened\n");
					}				
				
				} else {
					printf("ERROR: Item file not opened\n");
				}
			} else {
				printf("ERROR: Auction not found\n");
			}
			
		} else {
			printf("ERROR: Item file not opened\n");
		}
		
		return "";
	}
	
	void advertise(){
		std::string itemName;
		int duration;
		float minimumBid;
		
		// prompt user for info
		printf("Enter item name: ");
		std::cin >> itemName;
		
		printf("Enter minimum bid: ");
		std::cin >> minimumBid;
		
		printf("Enter auction duration: ");
		std::cin >> duration;
		
		// create a new advertisement
		Advertisement(itemName, username_, duration, minimumBid);
	}
	
};

struct BuyStandard : User{
	
	BuyStandard(std::string username, std::string password, double credit)
	: User(username, password, "buy-standard", credit)
	{
		// intentionally left blank
	}
	
	std::string bid(std::string seller, std::string itemName){
		std::ifstream iItemFile;
		std::ofstream oTempFile;
		bool advertisementFound = false;
		double currentBid;
		double newBid;
		std::string newBidString;
		
		iItemFile.open(itemFile);
		if(iItemFile.is_open()){
			std::string line;
			while(getline(iItemFile, line)){
				std::string info[5];
				
				info[0] = line.substr(0, 25);
				info[1] = line.substr(26, 15);
				info[2] = line.substr(42, 15);
				info[3] = line.substr(58, 3);
				info[4] = line.substr(62, 6);
				
				if(info[1].substr(0, seller.length()) == seller && info[0].substr(0, itemName.length()) == itemName){
					std::string bidValue = info[4].substr(info[4].find_first_not_of("0"));
					currentBid = std::stod(bidValue);
					advertisementFound = true;
				}
			}
			
			iItemFile.close();
			
			if(advertisementFound){
				std::cout << "Current bid: " << currentBid << "\n";
				std::cout << "Enter your bid: \n";
				std::cin >> newBidString;
				newBid = std::stod(newBidString);
				if(newBid <= currentBid * 1.05){
					printf("ERROR: new bid must be at least 5%% greater than the current highest bid for standard-buy accounts\n");
					return "";
				} 
		
				iItemFile.open(itemFile);

				if(iItemFile.is_open()){
					oTempFile.open(tempFile);
					
					if(oTempFile.is_open()){

						while(getline(iItemFile, line)){
							std::string info[5];
							info[0] = line.substr(0, 25);
							info[1] = line.substr(26, 15);
							info[2] = line.substr(42, 15);
							info[3] = line.substr(58, 3);
							info[4] = line.substr(62, 6);
							
							std::string possibleItemName = info[0].substr(0, itemName.length());
							std::string possibleSellerName = info[1].substr(0, seller.length());
					//		std::cout << newBid << " " << (std::to_string(newBid)).length();
					//		std::cout << possibleItemName << "end\n" << possibleSellerName << "end\n" << newBid << "end\n";
					//		std::cout << (possibleItemName.compare(itemName)) << " " << possibleSellerName.compare(seller);
					
							if(possibleItemName.compare(itemName) == 0 && possibleSellerName.compare(seller) == 0){

								oTempFile << info[0] << " " << info[1] << " " << username_;
								for(int i = 0; i < 15 - username_.length(); i++){
									oTempFile << " ";
								}

								oTempFile << " " << info[3] << " ";
								for(int i = 0; i < 6 - newBidString.length(); i++){
									oTempFile << "0";
								}

								oTempFile << newBid << "\n";
							} else {

								oTempFile << line << "\n";
							}
						}
						
						iItemFile.close();
						oTempFile.close();
						updateFile(itemFile, tempFile);
						printf("Bid placed\n");
						
						return newBidString;
						
					} else {
						printf("ERROR: Temp file not opened\n");
					}				
				
				} else {
					printf("ERROR: Item file not opened\n");
				}
			} else {
				printf("ERROR: Auction not found\n");
			}
			
		} else {
			printf("ERROR: Item file not opened\n");
		}
		
		return "";
	}
};

struct SellStandard : User{
	
	SellStandard(std::string username, std::string password, double credit)
	: User(username, password, "sell-standard", credit)
	{
		// intentionally left blank
	}
	
	void advertise(){
		std::string itemName;
		int duration;
		float minimumBid;
		
		// prompt user for info
		printf("Enter item name: ");
		std::cin >> itemName;
		
		printf("Enter minimum bid: ");
		std::cin >> minimumBid;
		
		printf("Enter auction duration: ");
		std::cin >> duration;
		
		// create a new advertisement
		Advertisement(itemName, username_, duration, minimumBid);
	}
};

struct Admin : User{
	
	Admin(std::string username, std::string password, double credit)
	: User(username, password, "admin", credit)
	{
		// intentionally left blank
	}
	
	void deleteUser(std::string userToDelete){
		
		//check for valid input
		if (userToDelete == username_){
			std::cout << "ERROR: Cannot delete the current user\n";
			return;
		}
		
		
		// remove the user on account file
		// open files
		std::ifstream iAccFile;
		std::ofstream oAccFile;
		
		iAccFile.open(accountFile);
		
		if(iAccFile.is_open()){
			std:: string line;
			std:: string accounts = "";
			bool accountFound = false;
			// read each line of account file
			while(std::getline(iAccFile, line)){
				
				std::string info[4];
				int infoIndex = 0;
				
				char *linechar = new char[line.length() + 1];
				strcpy(linechar, line.c_str());
				
				char* tokens = strtok(linechar, " ");
				
				// store each account information
				while(tokens != NULL){
					info[infoIndex++] = tokens;
					tokens = strtok(NULL, " ");
				}
				
				// 
				if(info[0] == userToDelete){
					printf("User deleted\n");
					accountFound = true;
				} else {
					// idk how c++ file i/o works so im assuming it just writes over each line I read with the same thing
					// NOTE: if this duplicates the account info, then delete this
					accounts += line;
					accounts += "\n";
				}
			}
			if(!accountFound){
				std::cout << "ERROR: That user does not exist\n";
			}
			oAccFile.open(accountFile);
			oAccFile << accounts;
			// close files
			oAccFile.close();
			iAccFile.close();
			
		} else {
			printf("cannot find file");
		}
	}
	
	std::string bid(std::string seller, std::string itemName){
		std::ifstream iItemFile;
		std::ofstream oTempFile;
		bool advertisementFound = false;
		double currentBid;
		double newBid;
		std::string newBidString;
		
		iItemFile.open(itemFile);
		if(iItemFile.is_open()){
			std::string line;
			while(getline(iItemFile, line)){
				std::string info[5];
				
				info[0] = line.substr(0, 25);
				info[1] = line.substr(26, 15);
				info[2] = line.substr(42, 15);
				info[3] = line.substr(58, 3);
				info[4] = line.substr(62, 6);
				
				if(info[1].substr(0, seller.length()) == seller && info[0].substr(0, itemName.length()) == itemName){
					std::string bidValue = info[4].substr(info[4].find_first_not_of("0"));
					currentBid = std::stod(bidValue);
					advertisementFound = true;
				}
			}
			
			iItemFile.close();
			
			if(advertisementFound){
				std::cout << "Current bid: " << currentBid << "\n";
				std::cout << "Enter your bid: \n";
				std::cin >> newBidString;
				newBid = std::stod(newBidString);
				if(newBid <= currentBid){
					printf("ERROR: new bid must be greater than highest current bid\n");
					return "";
				}
		
				iItemFile.open(itemFile);

				if(iItemFile.is_open()){
					oTempFile.open(tempFile);
					
					if(oTempFile.is_open()){

						while(getline(iItemFile, line)){
							std::string info[5];
							info[0] = line.substr(0, 25);
							info[1] = line.substr(26, 15);
							info[2] = line.substr(42, 15);
							info[3] = line.substr(58, 3);
							info[4] = line.substr(62, 6);
							
							std::string possibleItemName = info[0].substr(0, itemName.length());
							std::string possibleSellerName = info[1].substr(0, seller.length());
					//		std::cout << newBid << " " << (std::to_string(newBid)).length();
					//		std::cout << possibleItemName << "end\n" << possibleSellerName << "end\n" << newBid << "end\n";
					//		std::cout << (possibleItemName.compare(itemName)) << " " << possibleSellerName.compare(seller);
					
							if(possibleItemName.compare(itemName) == 0 && possibleSellerName.compare(seller) == 0){
								oTempFile << info[0] << " " << info[1] << " " << username_;
								for(int i = 0; i < 15 - username_.length(); i++){
									oTempFile << " ";
								}
								oTempFile << " " << info[3] << " ";
								for(int i = 0; i < 6 - newBidString.length(); i++){
									oTempFile << "0";
								}
								oTempFile << newBid << "\n";
							} else {
								oTempFile << line << "\n";
							}
						}
						
						iItemFile.close();
						oTempFile.close();
						updateFile(itemFile, tempFile);
						printf("Bid placed\n");
						
						return newBidString;
						
					} else {
						printf("ERROR: Temp file not opened\n");
					}				
				
				} else {
					printf("ERROR: Item file not opened\n");
				}
			} else {
				printf("ERROR: Auction not found\n");
			}
			
		} else {
			printf("ERROR: Item file not opened\n");
		}
		
		return "";
	}
	
	void advertise(){
		std::string itemName;
		int duration;
		float minimumBid;
		
		// prompt user for info
		printf("Enter item name: ");
		std::cin >> itemName;
		
		printf("Enter minimum bid: ");
		std::cin >> minimumBid;
		
		printf("Enter auction duration: ");
		std::cin >> duration;
		
		// create a new advertisement
		Advertisement(itemName, username_, duration, minimumBid);
	}
	
	void createUser(std::string username, std::string type, float credit, std::string password){
		
		//check if input is valid
		if (username.length() > 15){
			std::cout << "ERROR: Username must be less than or equal to 15 characters\n";
			return;
		}
		if (!(credit < 1000 && credit >= 0)){
			std::cout << "ERROR: Credit must be between 0 and 999,999\n";
			return;
		}
		
		std::ifstream iAccFile;
		std::ofstream oTempFile;
		
		iAccFile.open(accountFile);
		
		if(iAccFile.is_open()){
			std::string line;
			bool isUsernameTaken = false;
			
			// Checks to see if username is taken
			while(std::getline(iAccFile, line)){
				std::string info[4];
				int infoIndex = 0;
				
				char *linechar = new char[line.length() + 1];
				strcpy(linechar, line.c_str());
				
				char* tokens = strtok(linechar, " ");
				
				// store each account information
				while(tokens != NULL){
					info[infoIndex++] = tokens;
					tokens = strtok(NULL, " ");
				}
				
				if(info[0] == username){
					isUsernameTaken = true;
				}
			}
			iAccFile.close();
			// if username isnt taken, then add it to account file
			if(!isUsernameTaken){
				iAccFile.open(accountFile);
				if(iAccFile.is_open()){
					
					oTempFile.open(tempFile);
					if(oTempFile.is_open()){
						// copying original account info
						while(std::getline(iAccFile, line)){
							oTempFile << line << "\n";
						}
						
						if(type == "admin"){
							oTempFile << username << " AA " << credit << " " << password << "\n";
							oTempFile.close();
							updateFile(accountFile, tempFile);
							printf("Account Successfully Created\n");
						} else if(type == "full-standard"){
							oTempFile << username << " FS " << credit << " " << password << "\n";
							oTempFile.close();
							updateFile(accountFile, tempFile);
							printf("Account Successfully Created\n");
						} else if(type == "buy-standard"){
							oTempFile << username << " BS " << credit << " " << password << "\n";
							oTempFile.close();
							updateFile(accountFile, tempFile);
							printf("Account Successfully Created\n");
						} else if(type == "sell-standard"){
							oTempFile << username << " SS " << credit << " " << password << "\n";
							oTempFile.close();
							updateFile(accountFile, tempFile);
							printf("Account Successfully Created\n");
						} else {
							printf("ERROR: Account type must be admin, buy-standard, or sell-standard\n");
						}
					} else {
						printf("ERROR: Temp file not opened \n");
					}
				}
			} else {
				printf("ERROR: Username already taken\n");
			}
		} else {
			printf("ERROR: Account file not opened\n");
		}
	}
	
	void refund(std::string seller, std::string buyer, float amount){
		if(amount > 0.0){
			std::ifstream iAccFile;
			std::ofstream oTempFile;
			
			iAccFile.open(accountFile);
			
			if(iAccFile.is_open()){
				std::string line;
				bool sellerFound = false;
				bool buyerFound = false;
				bool negativeCreditError = false;
				bool tooMuchCreditError = false;
				while(std::getline(iAccFile, line)){
					std::string info[4];
					int infoIndex = 0;
					
					char *linechar = new char[line.length() + 1];
					strcpy(linechar, line.c_str());
					
					char* tokens = strtok(linechar, " ");
					
					// store each account information
					while(tokens != NULL){
						info[infoIndex++] = tokens;
						tokens = strtok(NULL, " ");
					}
					
					if(info[0] == seller){
						sellerFound = true;
						if(std::stoi(info[2]) - amount < 0.0){
							negativeCreditError = true;
						}
					} else if (info[0] == buyer){
						buyerFound = true;
						if(std::stoi(info[2]) + amount > 999.99){
							tooMuchCreditError = true;
						}
					}
				}
				
				iAccFile.close();
				
				if(sellerFound && buyerFound){
					
					if(tooMuchCreditError && negativeCreditError){
						printf("ERROR: Buyer will exceed maximum credit and Seller does not have enough credit\n");
					} else if(negativeCreditError){
						printf("ERROR: Seller does not have enough credit\n");
					} else if(tooMuchCreditError){
						printf("ERROR: Buyer will exceed maximum credit\n");
					} else {
						iAccFile.open(accountFile);
						if(iAccFile.is_open()){
							oTempFile.open(tempFile);
							
							if(oTempFile.is_open()){
								
								while(getline(iAccFile, line)){
									std::string info[4];
									int infoIndex = 0;
						
									char *linechar = new char[line.length() + 1];
									strcpy(linechar, line.c_str());
						
									char* tokens = strtok(linechar, " ");
						
									// store each account information
									while(tokens != NULL){
										info[infoIndex++] = tokens;
										tokens = strtok(NULL, " ");
									}
										
									if(info[0] == seller){
										oTempFile << info[0] << " " << info[1] << " " << (std::stoi(info[2]) - amount) << " " << info[3] << "\n";
									} else if (info[0] == buyer){
										oTempFile << info[0] << " " << info[1] << " " << (std::stoi(info[2]) + amount) << " " << info[3] << "\n";
									} else {
										oTempFile << line << "\n";
									}
								}
								oTempFile.close();
								iAccFile.close();
								updateFile(accountFile, tempFile);
								printf("Refund successful\n");
								
							} else {
								
								printf("ERROR: Temp file not found\n");
							}
						} else {
							printf("ERROR: Account file not opened\n");
						}
					}
				} else if(sellerFound && !buyerFound){
					printf("ERROR: Buyer is not a current user\n");
				} else if(!sellerFound && buyerFound){
					printf("ERROR: Seller is not a current user\n");
				} else{
					printf("ERROR: Seller and Buyer are not current users\n");
				}
			} else {
				printf("ERROR: Account file not opened\n");
			}
		} else {
			printf("ERROR: Amount of credit cannot be negative");
		}
	}
	
	void addCredit(float amount, std::string username){
		
		//check if action is valid
		if (amount >= 1000){
			std::cout << "ERROR: amount entered is greater than the maximum allowed\n";
			return;
		}
		if (amount <= 0){
			std::cout << "ERROR: amount entered is not greater than 0\n";
			return;
		}
		
		// open files
		std::ifstream iAccFile;
		std::ofstream oTempFile;
		
		iAccFile.close();
		iAccFile.open(accountFile);
		oTempFile.open(tempFile);
		bool accFound = false;
		
		if(iAccFile.is_open()){
			std::string line;

			// read each line of account file
			while(getline(iAccFile, line)){
				std::string info[4];
				int infoIndex = 0;
				
				char *linechar = new char[line.length() + 1];
				strcpy(linechar, line.c_str());
				
				char* tokens = strtok(linechar, " ");
				
				// store each account information
				while(tokens != NULL){
					info[infoIndex++] = tokens;
					tokens = strtok(NULL, " ");
				}
				
				// if it finds the user, change their credits accordingly
				if(info[0] == username){
					float newCredit = (std::stof(info[2]) + amount);
					oTempFile << info[0] << " " << info[1] << " " << round2Places(newCredit) << " " << info[3] << "\n";
					accFound = true;
					std::cout << "Amount Added\nUser Balance Readjusted\n";
				} 
				else {
					oTempFile << line << "\n";
				}
			}
			
			if (!accFound){
				std::cout << "ERROR: that user does not exist\n";
			}
			
			// close files
			oTempFile.close();
			iAccFile.close();
			
			updateFile(accountFile, tempFile);
			
		} else {
			printf("cannot find file");
		}
	}
};