/*
 * University of Central Florida
 * COP 3330 Spring 2019
 * Author: Christian Lozano
 */

import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;


public class GarageTest
{
	public static void main(String [] args) throws IOException
	{
		String filename;
		int i=0,count=0,arrayListSize, small = 0, medium = 0, large = 0;
		double length, width, VacantSpace;
		String userinputfloors;
		String userinputarea;
		ArrayList<String> cars;
		ArrayList<Double> carArea;
		ArrayList<String> parkingType ;


		String cararray1 = null;

		
		Scanner sc = new Scanner(System.in);
		
		System.out.printf("Enter number of floor(s): ");
		userinputfloors = sc.nextLine();
		
		System.out.printf("Enter area at each floor:");
		userinputarea = sc.nextLine();
		
		
		System.out.printf("Enter name of File: ");
		filename = sc.nextLine();
		
		arrayListSize = (int) (Double.parseDouble(userinputfloors)*Double.parseDouble(userinputarea));
	
		try
		{
			File file = new File(filename);
			Scanner input = new Scanner(file);
			input.next();
			input.next();
			input.next();
			
			
			
			cars = new ArrayList<>(arrayListSize);
			carArea = new ArrayList<>(arrayListSize);
			parkingType = new ArrayList<>(arrayListSize);
			
			
			GarageC garc = new GarageC(cararray1, arrayListSize, arrayListSize);
			
	 
			
			while (input.hasNext())
			{

				cars.add(input.next());
				length = Double.parseDouble(input.next());
				width = Double.parseDouble(input.next());
				
				carArea.add(garc.getArea(length , width));
				parkingType.add(garc.getDimensions(length, width));
				count++;
			}

			VacantSpace = arrayListSize;
			
			if(VacantSpace<0 )
		 		System.out.println("Garage is full!");
			
			else if((VacantSpace - carArea.get(i))<0)
		 		System.out.printf("");
						
			else 
				System.out.println("Garage is open!");
			
			for(i=0;i<count;i++)
			{
				if(VacantSpace<0 || (VacantSpace - carArea.get(i))<0)
			 	{
			 		System.out.println("Garage is full!");
			 		break;
			 	}
				
				if(parkingType.get(i) == "Small")
					small++;
				
				else if(parkingType.get(i) == "Medium")
					medium++;
				
				else
					large++;
				
				
				System.out.printf("Cars: %s\tParking type: %s\tArea: %.2f\t", cars.get(i), parkingType.get(i), carArea.get(i));
				System.out.printf("Total area occupied in GarageC: %.0f\t",garc.calculateTotalSpace(carArea,i));
				
				VacantSpace = VacantSpace - carArea.get(i);
				
				System.out.printf("Total vacant area in Garace C: %.0f\n", VacantSpace);
				
			    PrintWriter printWriter = new PrintWriter("out.txt");
			    printWriter.printf("Small: %d\tMedium %d\tLarge: %d", small, medium, large);
			    printWriter.close();
			}

			
			
			input.close();
			}
		
		catch (FileNotFoundException fnfe)
		{
			System.out.println("File not found!");
		}
	}

}