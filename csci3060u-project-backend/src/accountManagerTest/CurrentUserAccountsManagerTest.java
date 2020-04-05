package accountManagerTest;
import lib.*;

import static org.junit.Assert.*;
import java.io.*;
import org.junit.Test;

public class CurrentUserAccountsManagerTest {
	CurrentUserAccountsManager cu = new CurrentUserAccountsManager("currentusers.txt");
	
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
	
	void initTest() throws IOException {
		FileOutputStream out = new FileOutputStream("currentusers.txt");
		String str = "Bobby123        FS 001000.00\n" + 
					 "Johnathan       AA 500000.00\n" +
					 "Kragg           SS 000005.00\n" +
					 "Joe             FS 050000.00\n";
		
		out.write(str.getBytes());
		out.close();
	}
	
	@Test
	public void testAddUser() throws Exception{
		initTest();
		CurrentUserAccountsManager.addUser("Steve          ", "AA", 800.00f);
		CurrentUserAccountsManager.addUser("Bobby123       ", "FS", 1000.00f);
		
		String str = readFile("currentusers.txt");
		
		boolean condition = (str.equals("Bobby123        FS 001000.00\n" + 
										"Johnathan       AA 500000.00\n" +
										"Kragg           SS 000005.00\n" +
										"Joe             FS 050000.00\n" +
										"Steve           AA 000800.00\n"));
		assert(condition);
	}

	@Test
	public void testDeleteUser() throws Exception{
		initTest();
		CurrentUserAccountsManager.deleteUser("Bobby123       ");
		CurrentUserAccountsManager.deleteUser("Kragg          ");
		CurrentUserAccountsManager.deleteUser("Steve          ");
		
		String str = readFile("currentusers.txt");
		
		boolean condition = (str.equals("Johnathan       AA 500000.00\n" +
										"Joe             FS 050000.00\n"));
		assert(condition);
	}

	@Test
	public void testAddCredit() throws Exception{
		initTest();
		CurrentUserAccountsManager.addCredit("Joe            ", 100.00f);
		CurrentUserAccountsManager.addCredit("Steve          ", 100.00f);
		
		String str = readFile("currentusers.txt");
		
		boolean condition = (str.equals("Bobby123        FS 001000.00\n" + 
										"Johnathan       AA 500000.00\n" +
										"Kragg           SS 000005.00\n" +
										"Joe             FS 050100.00\n"));
		
		assert(condition);
		
	}

	@Test
	public void testRefund() throws Exception{
		initTest();
		CurrentUserAccountsManager.refund("Joe            ", "Bobby123       ", 20.0f);
		CurrentUserAccountsManager.refund("Joe            ", "NotAUser       ", 100.0f);
		CurrentUserAccountsManager.refund("Kragg          ", "Johnathan      ", 6.0f);
		CurrentUserAccountsManager.refund("Kragg          ", "Johnathan      ", 500000.0f);
		String str = readFile("currentusers.txt");
		
		boolean condition = (str.equals("Bobby123        FS 001020.00\n" + 
										"Johnathan       AA 500000.00\n" +
										"Kragg           SS 000005.00\n" +
										"Joe             FS 049980.00\n"));
		assert(condition);
	}

}
