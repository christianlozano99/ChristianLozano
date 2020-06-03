import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;
import java.util.Random;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;



public class Hw02
{
	public static int numposInfinity = Integer.MAX_VALUE;
    public static int numnegInfinity = Integer.MIN_VALUE;

	public static void main(String[] args)
    {
		complexityIndicator();
		int seeder = 42;

		// checks to see if more than one command line
		if (args.length > 0)
        {
            
            // check to see user input for seed
            boolean seedflag = true;
            File fileName = new File(args[0]);
            
            //if seed found then set seeder to given number
            if (args.length == 2 && args[1] != null)
            {
				seeder = Integer.parseInt(args[1]);
                seedflag = false;
			}
			
            
			// constucting skip list and calling to proccess file
			Hw02 callingprocess = new Hw02();
			skipList list = new Hw02().new skipList();
			callingprocess.proccessFile(fileName, list, seedflag,seeder);
        
        }

        else
        {
            System.err.println("Input file not specified!, try again");
        }
    }

	// class for nodes in skipList
	public class Node
	{
	    int data;
	    
	    public Node left;
	    public Node right;
	    public Node down;
	    public Node up;
	    
	    //constructor for node in skiplist
	    public Node(int item)
	    {
	        this.left = this.right = null;
	        this.up = this.down = null;
	        this.data = item;
	    }
	}

	//class for the whole skip list
	public class skipList
	{

	    public Node negInfinity;
	    public Node posInfinity;

	    public Node head;
	    public int size, maxlvl;
	    public Node bottom;
	    public Node tail;
	    
	    // Declares left and right childs as Null initially.
	    public skipList()
	    {
	        negInfinity = new Node(Integer.MIN_VALUE);
	        posInfinity = new Node(Integer.MAX_VALUE);

	        negInfinity.right = posInfinity;
	        posInfinity.left = negInfinity;

	        this.head = negInfinity;
	        this.tail = posInfinity;
	        this.maxlvl = 1;
	        this.size = 0;

	    }

		//creates new layer for list when called and updates max lvl
	    private void createNewLayer()
		{

		    Node newnegInfinity = new Node(Integer.MIN_VALUE);
		    Node newposInfinity = new Node(Integer.MAX_VALUE);

		    newnegInfinity.down = head;
		    newnegInfinity.right = newposInfinity;
		    newposInfinity.down = tail;
		    newposInfinity.left = newnegInfinity;
		    head.up = newnegInfinity;
		    tail.up = newposInfinity;

		    head = newnegInfinity;
		    tail = newposInfinity;
		    maxlvl++;
		}


	}
		// fucntion to call to print the skip list from p command 
		public void printAll(skipList listy)
		{
			Node temp = listy.head;
	        
	        // getting to the bottom level where all the information is
	        while (temp.down != null)
	        {
	            temp = temp.down;
	        }
	        
			//goes through each level then prints that rows infomration
	        System.out.println("the current Skip List is shown below: ");
	        System.out.println("---infinity");
			while (temp.data != listy.tail.data)
			{
				temp = temp.right;
				
	            if (temp.data != listy.posInfinity.data) 
	                printerUpper(temp);
	        }
	        System.out.println("+++infinity");
	        System.out.println("---End of Skip List---");
		}

		//print helper prints all the levels of the specfic number
	    public void printerUpper(Node printer)
	    {
	        System.out.print(" " + printer.data + "; ");

			//automatically prints new line then moves onto next number if at bottom lvl
	        if (printer.up == null)
	            System.out.print("\n");
			//prints above lvls that exist for the number
			while (printer.up != null)
			{
				printer = printer.up;
				
				System.out.print(" " + printer.data + "; ");
				
				if (printer.up == null)
				{
	                System.out.print("\n");
	                break;
	            }
	        }
	    }

		//inserts numbers as a node into the skip list
	    public void insert (skipList skippylisty, int datainsert, Random rand)
	    {
	    	Node insert = new Node (datainsert);
	    	Node temp = search(skippylisty, datainsert);
	    	int height = 1;

	    	if(temp.data != datainsert)
	    	{
				//intalizing the new node to be inserted
	    		insert.left = temp;
	    		insert.right = temp.right;
	    		temp.right = insert;
	    		insert.right.left = insert;

				//randomizer to see if it will lcreate a new layer
	    		while ((rand.nextInt()%2) == 1)
	    		{
	    			if(height >= skippylisty.maxlvl)
	    				skippylisty.createNewLayer();

	    			while(temp.up == null)
	    				temp = temp.left;

	    			temp = temp.up;

					//links new level and updates the list information
	    			Node linknewlvl = new Node(datainsert);
	    			linknewlvl.left = temp;
	    			linknewlvl.right = temp.right;
	    			temp.right.left = linknewlvl;
	    			temp.right = linknewlvl;
	    			linknewlvl.down = insert;
	    			insert.up = linknewlvl;

	    			insert = linknewlvl;
	    			height++;
	    		}

	    		skippylisty.size++;

	    		if(height > skippylisty.maxlvl)
	    			skippylisty.maxlvl = height;
	    	}


		}

		//function to delete numbers from skip list
	 	public void delete(skipList listy, int deletekey)
	    {
			Node deletenode = search(listy, deletekey);

			//checks to see if we found number in list in the first place
			if (deletenode.data == deletekey)
			{
				//reconnecting the list to remove the varible we want to delete
				while (deletenode != null)
				{
					deletenode.left.right = deletenode.right;
					deletenode.right.left = deletenode.left;
					deletenode = deletenode.up;
				}

				System.out.println(deletekey + " deleted");
				listy.size--;
			}

			else
				System.out.println(deletekey + " integer not found - delete not successful");
	    }

		//searchs for a number in the skip list and returns its node
	    public Node search(skipList skippylisty, int searchkey)
	    {
	    	Node temp = skippylisty.head;

	    	for(int i = skippylisty.maxlvl; i > 0; i--)
	    	{
	    		while(temp.right.data != Integer.MAX_VALUE && temp.right.data <= searchkey)
	    			temp = temp.right;

	    		if(temp.down != null)
	    			temp = temp.down;

	    		else
	    			break;
	    	}

	    	return temp;
	    }

	    static void complexityIndicator()
	    {
	        System.err.println("ch158330;2.5;20");
	        return;
	    }

	//proccess the file and its commands
    public void proccessFile (File filename, skipList listy, boolean seedflag, int seeder)
    {
    	try{
			Random randomizer = new Random();
			Scanner scanner = new Scanner(filename);
			
			System.out.println("For the input file named " + filename);

			// if seed is unseeded
			if(seedflag)
			{
				randomizer.setSeed(seeder);
                System.out.println("With the RNG unseeded,");
			}

			//if seed is seeded
			else
			{
				System.out.println("With the RNG seeded,");
				randomizer.setSeed(seeder);
			}
            // Proccesses all the information inside the file provided in the command line.
            while (scanner.hasNext())
            {
                String insertkey = "i";
                String deletekey = "d";
                String quitkey = "q";
                String printkey = "p";
                String searchkey = "s";

                String s = scanner.nextLine();

                String[] filecontents = s.split(" ");

                if (filecontents[0].equals(insertkey))
                    insert(listy ,Integer.parseInt(filecontents[1]),randomizer);

                if (filecontents[0].equals(quitkey))
                    break;

                if (filecontents[0].equals(deletekey))
                    delete(listy, Integer.parseInt(filecontents[1]));

				if (filecontents[0].equals(searchkey))
				{
					Node temp = search(listy,Integer.parseInt(filecontents[1]));
						if(temp.data  == Integer.parseInt(filecontents[1]))
							System.out.println(Integer.parseInt(filecontents[1]) + " found");
						
						else
							System.out.println(Integer.parseInt(filecontents[1]) + " NOT FOUND");
				}

                if (filecontents[0].equals(printkey))
                    printAll(listy);
            }

            scanner.close();
        }

        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }

    }
}
