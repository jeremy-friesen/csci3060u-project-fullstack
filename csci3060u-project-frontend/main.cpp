/*
main
Program call prompts the user for the actions that want to take
*/

#include <cstdio> //Printf scanf
#include <string>
#include <iostream>
//Import major file components
//#include "bid.h"
#include "advertisement.h"
#include "user.h"

using namespace std;

int main(int argc, char *argv[]){
	
	const char* dtf;
	
	if (argc > 1){
		dtf = argv[1];
	}
	else{
		dtf = "dailyTransactions.dt";
	}
	
	
	cout << "Please login to the system\n";
	bool isLoggedIn = false;
	bool hasAdvertised = false;
	//Calls login class
	User * current;
	string transactions = "";
	
	
	while(1){
		//We would also have a check here to see if the user is null to make sure a user with permissions is logged in
		//If not we would call the login function
		string input; //user's input
		cin >> input;
		
		if(input == "exit"){
			exit(0);
		}
		
		if(input == "login"){
			
			if (isLoggedIn){
				cout << "ERROR: Already logged in\n";
			}
			else{
				//check if account exists
				std::ifstream iAccFile;
				iAccFile.open(accountFile);
				
				if(iAccFile.is_open()){
					string username;
					string password;
					cout << "Enter username:\n";
					cin >> username;
					cout << "Enter password:\n";
					cin >> password;
				
					string line = "";
					bool accountFound = false;
					// read each line of account file
					while(getline(iAccFile, line)){
						
						std::string info[4];
						int infoIndex = 0;
						
						char *linechar = new char[line.length() + 1];
						strcpy(linechar, line.c_str());
						
						char* tokens = strtok(linechar, " \n\r");
						
						// store each account information
						while(tokens != NULL){
							//cout << info[infoIndex] + "\n";
							info[infoIndex++] = tokens;
							tokens = strtok(NULL, " \n\r");
						}
						
						//cout << username + " " + password + "\n";
						//cout <<info[0] + " " + info[3] + "\n";
						
						if(username.compare(info[0]) == 0 && password.compare(info[3]) == 0){
							cout << "Login successful\n";
							accountFound = true;
							isLoggedIn = true;
							
							if (info[1] == "AA"){
								Admin * adminUser = new Admin(info[0], info[3], std::stod(info[2]));
								current = adminUser;
							}else if (info[1] == "FS"){
								FullStandard * fullStandUser = new FullStandard(info[0], info[3], std::stod(info[2]));
								current = fullStandUser;
							}else if (info[1] == "SS"){
								SellStandard * sellStandUser = new SellStandard(info[0], info[3], std::stod(info[2]));
								current = sellStandUser;
							}else if (info[1] == "BS"){
								BuyStandard * buyStandUser = new BuyStandard(info[0], info[3], std::stod(info[2]));
								current = buyStandUser;
							}
							break;
						}
					}
					
					if (!accountFound){
						cout << "ERROR: Entered username and password combination does not exist\n";
					}
					
					// close files
					iAccFile.close();
					
				} else {
					cout << "ERROR: There are no registered users";
				}	
			}
		}
		
		if (isLoggedIn){
			if(input == "bid"){
				if(current->accountType_ == "admin"){
					Admin * adminAccount = dynamic_cast<Admin*>(current);
					cout << "Enter item name:\n";
					string itemName;
					getline(cin, itemName); //buffer
					getline(cin, itemName);
					
					cout << "Enter seller's username:\n";
					string seller;
					cin >> seller;
					
					string bidPlaced = adminAccount->bid(seller, itemName);
					
					if (!(bidPlaced == "")){
						transactions += "04 " + itemName + " " + seller + " " + current->username_ + " " + bidPlaced + "\n";	
					}
					
				} else if(current->accountType_ == "full-standard"){
					FullStandard * fsAccount = dynamic_cast<FullStandard*>(current);
					cout << "Enter item name:\n";
					string itemName;
					cin >> itemName;
					
					cout << "Enter seller's username:\n";
					string seller;
					cin >> seller;
					
					string bidPlaced = fsAccount->bid(seller, itemName);
					
					if (!(bidPlaced == "")){
						transactions += "04 " + itemName + " " + seller + " " + current->username_ + " " + bidPlaced + "\n";	
					}
					
				} else if(current->accountType_ == "buy-standard"){
					BuyStandard * bsAccount = dynamic_cast<BuyStandard*>(current);
					cout << "Enter item name:\n";
					string itemName;
					cin >> itemName;
					
					cout << "Enter seller's username:\n";
					string seller;
					cin >> seller;
					
					string bidPlaced = bsAccount->bid(seller, itemName);
					
					if (!(bidPlaced == "")){
						transactions += "04 " + itemName + " " + seller + " " + current->username_ + " " + bidPlaced + "\n";	
					}
					
				} else if(current->accountType_ == "sell-standard"){
					printf("ERROR: standard sell accounts cannot bid\n");
				}
			}
			else if(input == "create"){
				if(current->accountType_ == "admin"){
					//Calls create function
					Admin * adminAccount = dynamic_cast<Admin*>(current);
					cout << "Enter username for new user:\n";
					string newUsername;
					cin >> newUsername;
				
					cout << "Enter password for new user:\n";
					string newPassword;
					cin >> newPassword;
					
					cout << "Enter account type for new user:\n";
					string newType;
					cin >> newType;
				
					cout << "Enter credit for new user:\n";
					double newCredit;
					cin >> newCredit;
					
					//create new user
					adminAccount->createUser(newUsername, newType, newCredit, newPassword);
					
					//add transaction
					transactions += "01 " + current->username_ + " " + current->getType() + " " + current->getCreditString() + "\n";
					
				} else {
					cout << "ERROR: Cannot create user with a non-admin account\n";
				}
			}
			else if(input == "logout"){
				//Calls logout function
				//delete current;
				transactions += "00 " + current->username_ + " " + current->getType() + " " + current->getCreditString() + "\n";
				
				current = NULL;
				isLoggedIn = false;
				hasAdvertised = false; //reset advertisement restriction
				cout << "Logout Successful\n";
				
				//output daily transactions
				ofstream oDTF;
				oDTF.open(dtf);
				
				if (oDTF.is_open()){
					oDTF << transactions;
				}
				else{
					cout << "ERROR: Cannot list transactions\n";
				}
				
				oDTF.close();
				
				cout << "Transactions Listed\n";
			}
			else if(input == "addcredit"){
				//Calls addcredit function
				if (current->accountType_ != "admin"){
					Admin * adminAccount = dynamic_cast<Admin*>(current);
					
					cout << "Enter Amount:\n";
					double amountToAdd;
					cin >> amountToAdd;
					
					adminAccount->addCredit(amountToAdd, current->username_);
				}
				else{
					Admin * adminAccount = dynamic_cast<Admin*>(current);
					
					cout << "Enter amount:\n";
					float amountToAdd;
					cin >> amountToAdd;
					cout << "Enter user to add credit to:\n";
					string userToAdd;
					cin >> userToAdd;
					
					adminAccount->addCredit(amountToAdd, userToAdd);
				}
				
				transactions += "06 " + current->username_ + " " + current->getType() + " " + current->getCreditString() + "\n";
			}
			
			else if(input == "advertise"){
				//Cannot have advertised and can't be a buy standard account

				if(!hasAdvertised and current->accountType_!= "buy-standard"){
					//Needed Variables
					string seller = current->username_;
					string adItem = "";
					string sMinBid;
					int duration;
					bool validAction = true;

					cout << "Enter item name:\n";
					
					getline(cin, adItem); //buffer
					getline(cin, adItem);
					
					cout << "Enter minimum bid:\n";

					cin >> sMinBid;
					
					cout << "Enter auction duration:\n";
					cin >> duration;
					
					//error check
					if(adItem.length() >= 25){ 
						cout << "ERROR: item name cannot exceed 25 characters\n";
						validAction = false;
					}
					
					
					if(stod(sMinBid)>=1000){
						cout << "ERROR: item price cannot exceed 999.99\n";
						validAction = false;
					}
					
					if(duration >= 100){
						cout << "ERROR: auction cannot exceed 100 days\n";
						validAction = false;
					}
						
					if (validAction){
						int decimalPos = sMinBid.find('.');
						if (decimalPos == string::npos){
							sMinBid += ".00";
						}
						else if (decimalPos == sMinBid.length()-2){
							sMinBid += "0";
						}
						else{
							sMinBid = sMinBid.substr(0, decimalPos + 3);
						}
						
						//Correcting the formatting
						string currentHighestBid = ""; //No current highest bid though
						string sDuration = to_string(duration);
						
						while(adItem.length() < 25) adItem = adItem + " ";
						if(duration > 9 and duration != 100) sDuration = "0" + sDuration;
						else sDuration = "00" + sDuration;
						while(sMinBid.length()<6) sMinBid = "0" + sMinBid;
						while(seller.length() < 15) seller = seller + " ";
						while(currentHighestBid.length() < 15) currentHighestBid = currentHighestBid + " ";
						
						//Recording to file
						//Open file stream in append mode
						ofstream adAppend;
						adAppend.open("items.txt", ofstream::out | ofstream::app);
						if (adAppend.is_open()){
							adAppend << adItem;
							adAppend << " ";
							adAppend << seller;
							adAppend << " ";
							adAppend << currentHighestBid;
							adAppend << " ";
							adAppend << sDuration;
							adAppend << " ";
							adAppend << sMinBid;
							adAppend << "\n";
							
							cout << "Item Listed Successfully\n";
							hasAdvertised = true;
							adAppend.close();
							
							transactions += "03 " + adItem + " " + seller + " " + sDuration + " " + sMinBid + "\n";
						}
						else{
							cout << "ERROR: Cannot output ad to file\n";
						}
					}
		        }

				else if (hasAdvertised){
					cout << "ERROR: Cannot advertise more than once per session\n";

				}
				else{
					cout << "ERROR: buy-standard account type cannot advertise\n";
				}
			}
			
			else if(input == "delete"){
				if (current->accountType_ == "admin"){
					
					Admin * adminAccount = dynamic_cast<Admin*>(current);
					
					cout << "Enter user to be deleted:\n";
					string userToDelete;
					cin >> userToDelete;
					adminAccount->deleteUser(userToDelete);
					
					transactions += "02 " + current->username_ + " " + current->getType() + " " + current->getCreditString() + "\n";
				}
				else{
					cout << "ERROR: Cannot delete user with a non-admin account\n";
				}
			}
			else if(input == "refund"){
				if(current->accountType_ == "admin"){
					Admin * adminAccount = dynamic_cast<Admin*>(current);
					cout << "Enter buyer:\n";
					string buyer;
					cin >> buyer;
					
					cout << "Enter seller:\n";
					string seller;
					cin >> seller;
					
					cout << "Enter Amount of Credit:\n";
					double credit;
					cin >> credit;
					
					transactions += "05 " + buyer + " " + seller + " " + to_string((int)credit) + "\n";
					
					adminAccount->refund(seller, buyer, credit);
				} else {
					cout << "ERROR: Must be an admin to refund\n";
				}
			}
			else if(input != "login"){
				cout << "ERROR: Not a command\n";
			}
		}
		else{
			if (input != "login"){
				cout << "ERROR: User is not logged in\n";
			}
		}
	}	
}