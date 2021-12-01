package application;

public class CheckingAccount extends Account {
	
	private static final double overLimit = 100;
	public CheckingAccount(Data actData) {
		super(actData);
	}
	
	@Override
	
	protected boolean checkWithdraw(double amount) {
		return getBalance() +overLimit>= amount;
	}

}
