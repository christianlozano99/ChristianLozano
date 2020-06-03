/*
 * University of Central Florida
 * COP 3330 Spring 2019
 * Author: Christian Lozano
 */
import java.util.ArrayList;

public abstract class Garage
{
	private String garageName;
	
	public Garage(String garageName)
	{
		this.garageName = garageName;
	}
	
	public String getGarageName()
	{
		return garageName;
	}
	
	public void setGarageName(String garageName)
	{
		this.garageName = garageName;
	}

	
	public abstract double calculateTotalSpace(ArrayList<Double>cars,int j);

}