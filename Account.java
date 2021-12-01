package application;

public abstract class Account {
	
	private Data actData;
	
	public Account(Data actData) {
		this.actData = actData;
	}
	
	public Data getData() {
		return actData;
	}
	
	public void deposit(int amount) {
		
		upBalance(getBalance()+amount);
	}
	
	public boolean withdraw(double amount) {
		if (checkWithdraw(amount)) {
			upBalance(getBalance()-amount);
			return true;
		}
		else {
			return false;
		}

	}
	
	protected boolean checkWithdraw(double amount) {
		return getBalance()>= amount;
	}
	public double getBalance() {
		return actData.getBalance();
	}
	
	private void upBalance(double newBalance) {
		actData = new Data(actData.getId(), actData.getName(), actData.getEmail(), newBalance );
	}

	protected abstract Account get(int id);

}
