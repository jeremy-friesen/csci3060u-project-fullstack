package lib;

import java.io.BufferedReader;
import java.io.FileReader;

public class Main {
	static String filePath = "dailytransactions.txt";
	CurrentUserAccountsManager cu;
	
	public static void main(String[] args) {
		try {
			BufferedReader br = new BufferedReader(new FileReader(filePath));
			
			// read in and parse each line
			String st;
			while ((st = br.readLine()) != null) {
				parseLine(st);
			}
		}catch (Exception e){
			System.out.println("Exception:" + e);
		}
	}
	
	public static void parseLine(String line){
		// TODO
		String transactionType = line.substring(0, 2);
		switch(transactionType){
			//add	
			case "01":
				String username = line.substring(3, 18);
				String accType = line.substring(19, 22);
				float credits = Float.valueOf(line.substring(23, 32));
				
				cu.addUser(username, "placeholderPassword", accType, credits);
				break;
			//delete
			case "02":
				String username = line.substring(3, 18);
				String accType = line.substring(19, 22);
				float credits = Float.valueOf(line.substring(23, 32));
				
				cu.deleteUser(username);
				break;
			//advertise
			case "03":
				String itemName = line.substring(3, 22);
				String seller = line.substring(23, 38);
				int duration = Integer.parseInt(line.substring(39, 42));
				float minBid = Float.valueOf(line.substring(43, 49));
				
				AvailableItemsFileManager.advertise(seller, itemName, minBid, duration);
				break;
			//bid	
			case "04":
				String itemName = line.substring(3, 22);
				String seller = line.substring(23, 38);
				String buyer = line.substring(39, 54);
				float credits = Float.valueOf(line.substring(55, 61));
				
				AvailableItemsFileManager.bid(seller, itemName, buyer, credit);
				break;
			//refund	
			case "05":
				String buyer = line.substring(3, 18);
				String seller = line.substring(19, 34);
				float credits = Float.valueOf(line.substring(35, 44));
				
				cu.refund(seller, buyer, credits);
				break;
			//addcredit
			case "06":
				String username = line.substring(3, 18);
				String accType = line.substring(19, 22);
				float credits = Float.valueOf(line.substring(23, 32));
				
				cu.addCredit(username, credits);
		}
	}

}
