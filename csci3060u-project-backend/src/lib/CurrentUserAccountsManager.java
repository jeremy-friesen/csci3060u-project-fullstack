package lib;
import java.io.*;
//import java.util.*;


public class CurrentUserAccountsManager {
	static String mainUserAccount;
	
	public CurrentUserAccountsManager(String mainAcc){
		mainUserAccount = mainAcc;
	}
	
	public static int addUser(String user, String accType, float credits){
		
		try{
			FileInputStream in = new FileInputStream(mainUserAccount);
			BufferedReader reader = new BufferedReader(new InputStreamReader(in));
			
			// iterate through file
			String line = reader.readLine();
			while(line != null){
				String []accData = new String[3];
				
				// get data
				accData[0] = line.substring(0, 15);
				accData[1] = line.substring(16, 18);
				accData[2] = line.substring(19, 28);
				
				// if user found, return user found error
				if(accData[0].equals(user)){
					System.out.println("ERROR: User already exists");
					reader.close();
					return(-1);
				}
				line = reader.readLine();
			}
			reader.close();
			
			FileWriter fw = new FileWriter(new File(mainUserAccount), true);
			BufferedWriter bw = new BufferedWriter(fw);
			
			String creditStr = String.format("%.2f", credits);
			
			while(creditStr.length() < 9){
				creditStr = "0" + creditStr;
			}

			// write user info into account file
			bw.write(user + " " + accType + " " + creditStr +"\n");
			bw.close();
		} catch (Exception e){
			System.out.println(e.getStackTrace());
			return(-1);
		}
		return(0);
	}
	
	public static int deleteUser(String user){
		try{
			FileInputStream in = new FileInputStream(mainUserAccount);
			BufferedReader reader = new BufferedReader(new InputStreamReader(in));
			String newData = "";
			// iterate through file
			String line = reader.readLine();

			while(line != null){
				String []accData = new String[3];
				
				// get data
				accData[0] = line.substring(0, 15);
				accData[1] = line.substring(16, 18);
				accData[2] = line.substring(19, 28);
				
				// if not user, write the line back into file
				if(!accData[0].equals(user)){
				//	System.out.println("User not found");
					newData += accData[0] + " " + accData[1] + " " + accData[2] +"\n";
				}/* else{
					System.out.println("User found");
				}*/
				line = reader.readLine();
			}
			FileWriter fw = new FileWriter(new File(mainUserAccount), false);
			BufferedWriter bw = new BufferedWriter(fw);
			fw.write(newData);
			reader.close();
			bw.close();
		} catch (Exception e){
			System.out.println(e.getStackTrace());
			return(-1);
		}
		return(0);
	}
	
	public static int addCredit(String user,float amount){
		try{
			FileInputStream in = new FileInputStream(mainUserAccount);
			BufferedReader reader = new BufferedReader(new InputStreamReader(in));
			String newData = "";
			
			// iterate through file
			String line = reader.readLine();
			while(line != null){
				String []accData = new String[3];
				
				// get data
				accData[0] = line.substring(0, 15);
				accData[1] = line.substring(16, 18);
				accData[2] = line.substring(19, 28);
				
				// if user is found, add the credits to his account
				if(accData[0].equals(user)){
					if(Float.valueOf(accData[2]) + amount >= 1000000){
						System.out.println("ERROR: Buyer cannot have over 999999.99 credits");
						reader.close();
						return(-1);
					}
					accData[2] = "" + String.format("%.2f", Float.valueOf(accData[2]) + amount);
					
					while(accData[2].length() < 9){
						accData[2] = "0" + accData[2];
					}
					
					newData += accData[0] + " " + accData[1] + " " + accData[2] +"\n";
				} else {
					newData += line + "\n";
				}
				line = reader.readLine();
			}
			
			FileWriter fw = new FileWriter(new File(mainUserAccount), false);
			BufferedWriter bw = new BufferedWriter(fw);
			
			bw.write(newData);
			
			bw.close();
			reader.close();
			return(0);
		} catch (Exception e){
			System.out.println(e.getStackTrace());
			return(-1);
		}
	}
	
	public static int refund(String seller, String buyer, float amount){
		try{
			FileInputStream in = new FileInputStream(mainUserAccount);
			BufferedReader reader = new BufferedReader(new InputStreamReader(in));
			boolean sellerFound = false;
			boolean buyerFound = false;
			String newData = "";
			
			// iterate through file
			String line = reader.readLine();
			while(line != null){
				String []accData = new String[3];
				
				// get data
				accData[0] = line.substring(0, 15);
				accData[1] = line.substring(16, 18);
				accData[2] = line.substring(19, 28);
				
				// if buyer found, add amount into his account
				if(accData[0].equals(buyer)){
					if(Float.valueOf(accData[2]) + amount >= 1000000){
						System.out.println("ERROR: Buyer cannot have over 999999.99 credits");
						reader.close();
						return(-1);
					}
					accData[2] = "" + String.format("%.2f", Float.valueOf(accData[2]) + amount);
					while(accData[2].length() < 9){
						accData[2] = "0" + accData[2];
					}
					buyerFound = true;
				} else 
				
				// if seller found, subtract amount from his account
				if(accData[0].equals(seller)){
					if(Float.valueOf(accData[2]) - amount < 0){
						System.out.println("ERROR: Seller cannot have negative credits");
						reader.close();
						return(-1);
					}
					accData[2] = "" + String.format("%.2f", Float.valueOf(accData[2]) - amount);
					while(accData[2].length() < 9){
						accData[2] = "0" + accData[2];
					}
					sellerFound = true;
				}
				
				newData += accData[0] + " " + accData[1] + " " + accData[2] +"\n";
				line = reader.readLine();
			}
			
			if(sellerFound && buyerFound){
				FileWriter fw = new FileWriter(new File(mainUserAccount), false);
				BufferedWriter bw = new BufferedWriter(fw);
				bw.write(newData);
				bw.close();
			} else {
				System.out.println("ERROR: Buyer and/or Seller not found");
			}
			reader.close();
		} catch (Exception e){
			System.out.println(e.getStackTrace());
			return(-1);
		}
		return(0);
	}
}
