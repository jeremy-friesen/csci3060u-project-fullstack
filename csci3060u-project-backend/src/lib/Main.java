package lib;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;

public class Main {
	static String filePath = "dailytransactions.txt";
	static CurrentUserAccountsManager cu = new CurrentUserAccountsManager("currentusers.txt");
	
	public static void main(String[] args) throws Exception {
		/*if(args.length > 0) {
			System.out.println("setting filePath");
			filePath = args[0];
		}*/
		BufferedReader br = new BufferedReader(new FileReader(filePath));
		
		// read in and parse each line
		String st;
		while ((st = br.readLine()) != null) {
			parseLine(st);
		}
	}
	
	public static void parseLine(String line) throws Exception{
		// TODO
		String transactionType = line.substring(0, 2);
		String username;
		String accType;
		float credits;
		String seller;
		String buyer;
		String itemName;
		
		switch(transactionType){
			//add	
			case "01":
				username = line.substring(3, 18);
				accType = line.substring(19, 21);
				credits = Float.valueOf(line.substring(22, 31));
				
				CurrentUserAccountsManager.addUser(username, accType, credits);
				break;
			//delete
			case "02":
				username = line.substring(3, 18);
				accType = line.substring(19, 21);
				credits = Float.valueOf(line.substring(22, 31));
				
				CurrentUserAccountsManager.deleteUser(username);
				break;
			//advertise
			case "03":
				itemName = line.substring(3, 22);
				seller = line.substring(23, 36);
				String daysLeft = line.substring(37, 40);
				String startingBid = line.substring(42, 47);
				
				AvailableItemsFileManager.advertise(itemName, seller, "", daysLeft, startingBid);
				break;
			//bid	
			case "04":
				itemName = line.substring(3, 22);
				seller = line.substring(23, 38);
				buyer = line.substring(39, 54);
				String cred = line.substring(54, 60);
				
				AvailableItemsFileManager.bid(seller, itemName, buyer, cred);
				break;
			//refund	
			case "05":
				buyer = line.substring(3, 18);
				seller = line.substring(19, 34);
				credits = Float.valueOf(line.substring(34, 44));
				
				CurrentUserAccountsManager.refund(seller, buyer, credits);
				break;
			//addcredit
			case "06":
				username = line.substring(3, 18);
				accType = line.substring(19, 21);
				credits = Float.valueOf(line.substring(22, 31));
				
				CurrentUserAccountsManager.addCredit(username, credits);
		}
	}

}
