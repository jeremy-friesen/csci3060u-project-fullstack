package test;

import static org.junit.jupiter.api.Assertions.*;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;

import org.junit.jupiter.api.Test;
import lib.*;


class MainTest {
	
	String[] lines = {
		"01 username        AA 000000.00", // create
		"02 Kragg           FS 000005.00", // delete
		"03 table               sellerName    030 080.00", // advertise
		"04 basketball          someUs3r        newBidder      012.50", // bid
		"05 Kragg           Johnathan       000010.00", // refund
		"06 Kragg           SS 000100.00", // addCredit
	};
		
	String[][] output = {
		{"currentusers.txt", 
			"Bobby123        FS 001020.00\n" + 
			"Johnathan       AA 500000.00\n" +
			"Kragg           SS 000005.00\n" +
			"username        AA 000000.00\n"
		},
		{"currentusers.txt", 
			"Bobby123        FS 001020.00\n" +
			"Johnathan       AA 500000.00\n"
		},
		{"availableitems.txt",
			"basketball          someUs3r        bidder          005 010.00\n" + 
			"sneakers            exampleUsername someBidder      020 005.00\n" +
			"table               sellerName                      030 080.00\n"
		},
		{"availableitems.txt",
			"basketball          someUs3r        newBidder       005 012.50\n" + 
			"sneakers            exampleUsername someBidder      020 005.00\n"
		},
		{"currentusers.txt", 
			"Bobby123        FS 001020.00\n" +
			"Johnathan       AA 499990.00\n" +
			"Kragg           SS 000015.00\n"
		},
		{"currentusers.txt", 
			"Bobby123        FS 001020.00\n" +
			"Johnathan       AA 500000.00\n" +
			"Kragg           SS 000105.00\n"
		},
	};
	
	void initFiles() throws IOException {
		FileOutputStream fileOut = new FileOutputStream("availableitems.txt");
		String str = "basketball          someUs3r        bidder          005 010.00\n" + 
					 "sneakers            exampleUsername someBidder      020 005.00\n";
        fileOut.write(str.getBytes());
        fileOut.close();
        
        fileOut = new FileOutputStream("currentusers.txt");
		str = "Bobby123        FS 001020.00\n" + 
			 "Johnathan       AA 500000.00\n" + 
			 "Kragg           SS 000005.00\n";
        fileOut.write(str.getBytes());
        fileOut.close();
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
	
	void assertFileContent(String fileName, String fileContent) throws IOException{
		String str = readFile(fileName);
		//System.out.println("File Content:\n" + str);
		//System.out.println("Test Content:\n" + fileContent);
		boolean condition = (str.equals(fileContent));
		assert(condition);
	}
	
	@Test
	void testParseCreate() throws Exception{
		initFiles();
		Main.parseLine(lines[0]);
		assertFileContent(output[0][0], output[0][1]);
	}
	
	@Test
	void testParseDelete() throws Exception{
		initFiles();
		Main.parseLine(lines[1]);
		assertFileContent(output[1][0], output[1][1]);
	}
	
	@Test
	void testParseAdvertise() throws Exception{
		initFiles();
		Main.parseLine(lines[2]);
		assertFileContent(output[2][0], output[2][1]);
	}
	
	// bid
	@Test
	void testParseBid() throws Exception{
		initFiles();
		Main.parseLine(lines[3]);
		assertFileContent(output[3][0], output[3][1]);
	}
	
	@Test
	void testParseRefund() throws Exception{
		initFiles();
		Main.parseLine(lines[4]);
		assertFileContent(output[4][0], output[4][1]);
	}
	
	@Test
	void testParseAddCredit() throws Exception{
		initFiles();
		Main.parseLine(lines[5]);
		assertFileContent(output[5][0], output[5][1]);
	}
	
	/*
	@Test
	void testParseLine() throws Exception {
		for(int i = 0; i < lines.length; i++) {
			initFiles();
			Main.parseLine(lines[i]);
			assertFileContent(output[i][0], output[i][1]);
		}
	}
	*/

}
