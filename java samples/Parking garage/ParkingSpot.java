/*
 * University of Central Florida
 * COP 3330 Spring 2019
 * Author: Christian Lozano
 */

import java.util.ArrayList;

public interface ParkingSpot 
{
	public String getDimensions(double length, double width);

		
	public double getArea(double length, double width);


	double calculateTotalSpace(ArrayList<Double> cars, int j);	
}
