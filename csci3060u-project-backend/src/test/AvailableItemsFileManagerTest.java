package test;

import lib.*;
import static org.junit.jupiter.api.Assertions.*;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;

import org.junit.jupiter.api.Test;

class AvailableItemsFileManagerTest {
		
	void initTest() throws IOException {
		FileOutputStream fileOut = new FileOutputStream("availableitems.txt");
		String str = "basketball          someUs3r        bidder          005 010.00\n" + 
					 "sneakers            exampleUsername someBidder      020 005.00\n";
        fileOut.write(str.getBytes());
        fileOut.close();
	}
	
	@Test
	void testBid() throws Exception{
		initTest();
		
		AvailableItemsFileManager.bid("someUs3r", "basketball", "newBidder", "15.00");
		String str = readFile("availableitems.txt");
		
		boolean condition = (str.equals("basketball          someUs3r        newBidder       005 015.00\n" + 
				"sneakers            exampleUsername someBidder      020 005.00\n"));
		
		assert(condition);
	}
	
	@Test
	void testAdvertise() throws Exception{
		initTest();
		
		AvailableItemsFileManager.advertise("PS4", "sellUser", "", "15", "4.00");
		AvailableItemsFileManager.advertise("Switch", "user", "", "23", "250.00");
		String str = readFile("availableitems.txt");

		boolean condition = (str.equals("basketball          someUs3r        bidder          005 010.00\n" + 
										"sneakers            exampleUsername someBidder      020 005.00\n" + 
										"PS4                 sellUser                        015 004.00\n" +
										"Switch              user                            023 250.00\n"));
		
		assert(condition);
	}
	
	@Test
	void testDecAuctionDays() throws Exception{
		initTest();
		
		AvailableItemsFileManager.advertise("newItem", "sellerName", "buyerName", "0", "100.00");
		AvailableItemsFileManager.decAuctionDays();
		
		String str = readFile("availableitems.txt");
		System.out.println(str);
		
		boolean condition = (str.equals("basketball          someUs3r        bidder          004 010.00\n" + 
										"sneakers            exampleUsername someBidder      019 005.00\n" +
										"newItem             sellerName      buyerName       000 100.00\n"));
		
		assert(condition);
	}
	
	String readFile(String filePath) throws IOException {
		File file = new File(filePath);
		BufferedReader br = new BufferedReader(new FileReader(file));
		
		String str = "";
		String st;
		while ((st = br.readLine()) != null) {
			str = str + st + "\n";
		}
		br.close();
		
		return str;
	}
}