/*
 * University of Central Florida
 * COP 3330 Spring 2019
 * Author: Christian Lozano
 */

import java.util.ArrayList;

public class GarageC extends Garage implements ParkingSpot
{
	private int floors;
	private double area;
	private static GarageC garageC; 
	
	GarageC (String name, int Gfloors, double area)
	{
		super(name);
		floors = Gfloors;
		this.area = area;
	}
	
	public static GarageC getInstance(String name, int Gfloors, double area)
	{
		if (garageC != null)
			return garageC;
		
		else
			garageC = new GarageC(name, Gfloors, area);
		
		
		
		return garageC;		
	
	}
	
	public int getFloors()
	{
		return floors;
	}
	
	public double getArea()
	{
		return area;
	}
	

    @Override
	public double calculateTotalSpace(ArrayList<Double> carsArea, int j)
    {
    	double totalArea = 0.0;
    	
    	for(int i =0 ; i <= j; i++)
    	{
            totalArea += carsArea.get(i);
        }
        return totalArea;
    }

    @Override
    public String getDimensions(double length, double width)
    {
		if(length <= 15)
			return "Small";
		
		else if(length  >15 && length <= 17)
			return "Medium";
		
		else
			return "Large";
    }

    @Override
    public double getArea(double length, double width)
    {
        return length*width;
    }
}