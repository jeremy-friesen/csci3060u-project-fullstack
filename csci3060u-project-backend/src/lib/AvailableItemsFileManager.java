package lib;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

//AvailableItemsFileManager.bid("someUs3r", "basketball", "newBidder", "15.00");
//AvailableItemsFileManager.advertise("username", "soccerball", "", "5", "55.00");
//AvailableItemsFileManager.decAuctionDays();

public class AvailableItemsFileManager {
	
	private static String filePath = "availableitems.txt";
	private static File file = new File(filePath);
	
	private static String outFilePath = "availableitems.txt";
	private static File outFile = new File(outFilePath);
	
	// updates bid on item in available items
	public static void bid(String seller, String itemName, String buyer, String bidAmount) throws Exception{
		BufferedReader br = new BufferedReader(new FileReader(file));
		StringBuffer sb = new StringBuffer();
		
		seller = seller.split("\\s+")[0];
		itemName = itemName.split("\\s+")[0];
		buyer = buyer.split("\\s+")[0];
		bidAmount = bidAmount.split("\\s+")[0];
		
		// read in and parse each line
		String st;
		int i = 0;
		while ((st = br.readLine()) != null) {
			String[] splitString = st.split("\\s+");
			String currentItemName = splitString[0];
			String currentSellerName = splitString[1];
			String currentDaysLeft = splitString[3];
			
			// if both seller name and item name match, return index
			if(seller.equals(currentSellerName) && itemName.equals(currentItemName)) {
				sb.append(addSpaces(currentItemName, 20)
						+ addSpaces(currentSellerName, 16)
						+ addSpaces(buyer, 16)
						+ formatDaysLeft(currentDaysLeft) + " "
						+ formatAmount(bidAmount)
						+ "\n");
			}else {
				sb.append(st + "\n");
			}
			i++;
		}
		br.close();
		
		FileOutputStream fileOut = new FileOutputStream(outFile);
        fileOut.write(sb.toString().getBytes());
        fileOut.close();
	}
	
	// adds new item to available items
	public static void advertise(String itemName, String sellerName, String buyerName, String daysLeft, String startingBid) {
		// generate new line
		String str = addSpaces(itemName, 20)
				+ addSpaces(sellerName, 16)
				+ addSpaces(buyerName, 16)
				+ formatDaysLeft(daysLeft) + " "
				+ formatAmount(startingBid) + "\n";
		
		// append new line to available items file
		try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outFilePath), StandardOpenOption.APPEND)) {
		    writer.write(str);
		} catch (IOException ioe) {
		    System.err.format("IOException: %s%n", ioe);
		}
	}
	
	// format string to add trailing spaces
	private static String addSpaces(String str, int numChars) {
		int len = str.length();
		//System.out.println("\"" + str + (new String(new char[numChars - len]).replace("\0", " ") + "\""));
		return str + (new String(new char[numChars - len]).replace("\0", " "));
	}
	
	// format amount to add preceding 0's
	private static String formatAmount(String str) {
		int len = str.length();
		return (new String(new char[6 - len]).replace("\0", "0")) + str;
	}
	
	// format daysLeft to add preceding 0's
	public static String formatDaysLeft(String str) {
		int len = str.length();
		String retStr = new String(new char[3 - len]).replace("\0", "0");
		return retStr + str;
	}
	
	// format daysLeft to parse int and add preceding 0's
	public static String formatDaysLeft(int daysLeft) {
		String str = String.valueOf(daysLeft);
		int len = str.length();
		return (new String(new char[3 - len]).replace("\0", "0")) + str;
	}
	
	// decrease daysLeft on each item
	public static void decAuctionDays() throws Exception{
		BufferedReader br = new BufferedReader(new FileReader(file));
		StringBuffer sb = new StringBuffer();
		
		// read in and parse each line
		String st;
		int i = 0;
		while ((st = br.readLine()) != null) {
			String[] splitString = st.split("\\s+");
			String itemName = splitString[0];
			String sellerName = splitString[1];
			String buyerName = splitString[2];
			String daysLeft = splitString[3];
			String currentBid = splitString[4];
			
			// subtract one from previous daysLeft and cast to string
			String newDaysLeft = formatDaysLeft(Integer.parseInt(daysLeft) - 1);

			// if daysLeft != 0, decrease daysLeft
			if(!daysLeft.equals(formatDaysLeft("0"))) {
				sb.append(addSpaces(itemName, 20) 
						+ addSpaces(sellerName, 16)
						+ addSpaces(buyerName, 16)
						+ newDaysLeft + " "
						+ formatAmount(currentBid)
						+ "\n");
			// else, leave at 0
			}else {
				sb.append(st + "\n");
			}
			i++;
		}
		br.close();
		
		// replace file with new StringBuffer
		FileOutputStream fileOut = new FileOutputStream(outFilePath);
        fileOut.write(sb.toString().getBytes());
        fileOut.close();
	}
	
	
	
}