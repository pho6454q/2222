package application;

public final class Data {
	private final int id;
	private final String name;
	private final String email;
	
	private double balance;
	
	Data(int id, String name, String email, double balance) {
		this.id = id;
		this.name = name;
		this.email =email;
		this.balance = balance;
		
	}
	
	public static int getId() {
		return id;
	}
	public String getName() {
		return name;
	}
	public String getEmail() {
		return email;
	}
	public double getBalance() {
		return balance;
	}

}
