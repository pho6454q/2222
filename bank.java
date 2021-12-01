package application;

import java.util.HashMap;
import java.util.Map;

public class bank {
	
	private Map<Double, Account> accounts = new HashMap<> ();
	
	public bank() {
		accounts.put((double) 1000, new CheckingAccount(new Data(1000, "Phu Hoang", "phoang1@ivytech.edu", 500)));
		
		accounts.put((double) 1000, new SavingAccount(new Data(2000, "Nhi Hoang", "LinhNhi@ivytech.edu", 600)));
	
	}
	
	public CheckError<Data> getAccountById(int id){
		
		Account account = accounts.get(id);
		
		if (account != null) {
			return CheckError.success(account.getData());
		}else {
			return CheckError.fail("invalid account number: "+id);
		}
	}
	
	public CheckError<Data> deposit(Data actData, int balance){
		Account account = accounts.get(Data.getId());
		account.deposit(balance);
		
		return CheckError.success(account.getData());
	}
	
	public CheckError<Data> withdraw(Data actData, int balance){
		Account account = accounts.get(Data.getId());
		boolean ok = account.withdraw(balance);
		
		if (ok) {
			return CheckError.success(account.getData());
		}else {
			return CheckError.fail("withdraw failed: " + balance + "/n available balance: "+ account.getBalance());
		}
	}
}
