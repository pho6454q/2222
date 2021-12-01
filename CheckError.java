package application;

public class CheckError<T> {
	
	private T data;
	private String errorMessage;
	
	private CheckError(T data) {
		this.data = data;
	}
	
	private CheckError(String errorMessage) {
		this.errorMessage= errorMessage;
	}
	
	public T getData() {
		return data;
	}
	
	public String getErrorMessage() {
		return errorMessage;
	}
	
	public boolean isSuccess() {
		return data != null;
	}
	
	public static <E> CheckError<E> success(E data){
		return new CheckError<E>(data);
		
	}
	
	public static <E> CheckError<E> fail(String errorMessage){
		return new CheckError<E>(errorMessage);
	}
	

}
