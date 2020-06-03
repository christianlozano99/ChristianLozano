import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;


public class Hw01
{   
    //public varibles to be manipulated throught the program
    public static int LeftDepth = 0;
    public static int LeftChildren = 0;
    public static int RightDepth = 0;
    public static int RightChildren = 0;
   

    public static boolean searchflag = false; 
    // Class for the BST nodes.
    class Node
    {
        int number;
        Node left, right;
        
        // Declares left and right childs as Null initially.
        public Node (int item)
        {
            number = item;
            left = right = null;
        }
    }

    Node root;

    // Constuctor for the BST.
    Hw01()
    {
        root = null;
    }

    //Insert function takes in root and data then traverses to put correct value in correct tree location.
    Node insertwrapper(Node root, int data)
    {
        if(root == null)
        {
            root = new Node(data);
            return root;
        }

        if (data < root.number)
            root.left = insertwrapper (root.left, data);

        else
            root.right = insertwrapper (root.right, data);

        return root;
    }

    // Searchs for a given number, "data", inside of the BST.
    public void searchwrapper(Node root, int data)
    {
        if (root == null)
          return;

        else
        {
            if (root.number == data)
            {
                searchflag = true;
                return;
            }

            if( searchflag == false && root.left != null)
                searchwrapper(root.left, data);

            if( searchflag == false && root.right != null)
                searchwrapper(root.right, data);
        }
    }
    
    // Deletes a node and has proccedures for specfic delete situations where bst may become incorect.
    Node deletewrapper(Node root, int data)
    {
        if(root == null)
        {
            System.out.println("integer "+data+" NOT found");
            return root;
        }

        if(data < root.number)
            root.left = deletewrapper(root.left, data);

        else if (data > root.number)
            root.right = deletewrapper(root.right, data);

        else
        {
            if(root.left == null)
            {
                return root.right;
            }

            else if(root.right == null)
            {
                return root.left;
            }

            root.number = deleteHelper(root.right);

            root.right = deletewrapper(root.right, root.number);
        }

        return root;
    }

    // Helps deal with deletion on the left side of the BST.
    int deleteHelper (Node root)
    {
        int temp = root.number;

        while(root.left != null)
        {
            temp = root.left.number;
            root = root.left;
        }

        return temp;
    }

    // Prints the inorder of the BST contents.
    Node inorderwrapper(Node root)
    {
        if (root == null)
            return root;

        inorderwrapper(root.left);
        System.out.print(" " + root.number);
        inorderwrapper(root.right);

        return root;
    }

    // Checks BST for intial height and make sure its not passed a null refrence.
    void getDepth(Node root)
    {
        if(root == null  || root.right == null || root.left == null)
            return;

        LeftDepth = leftTreeDepth(root.left);
        RightDepth = rightTreeDepth(root.right);
    }

     // The following two functions are used to calculate the height of the left and right side of the BST.
    int leftTreeDepth(Node root)
    {
        if(root == null)
            return 0;

        int leftSubTree = leftTreeDepth(root.left);
        int rightSubTree = leftTreeDepth(root.right);
        
        return Math.max(leftSubTree, rightSubTree) + 1;
    }

    int rightTreeDepth(Node root)
    {
        if(root == null)
        return 0;

        int leftSubTree = leftTreeDepth(root.left);
        int rightSubTree = leftTreeDepth(root.right);
    
        return Math.max(leftSubTree, rightSubTree) + 1;
    }

    // Passes what side I want to know the amount of children of.
    void countChildren(Node root)
    {
        leftChildrenFinder(root.left);
        righChildrenFinder(root.right);
    }
    
    // The following two functions are used to calculate the amount of left children and right children.
    void leftChildrenFinder(Node root)
    {
        if (root == null)
            return;

            leftChildrenFinder(root.left);
            LeftChildren++;;
            leftChildrenFinder(root.right);
    }

    void righChildrenFinder(Node root)
    {
        if (root == null)
            return;

            righChildrenFinder(root.left);
            RightChildren++;;
            righChildrenFinder(root.right);
    }
    
    // Wrapper clases for functios and inputs to make onto the BST (from here until main function begins).
    void insert(int data)
    {
        root = insertwrapper (root, data);
    }

    //search function, if statments check are to see if private boolean 
    //"searchflag" has been triggered after finding the data searched for.
    void search(int data)
    {
        searchwrapper(root, data);

        if(searchflag == true)
            System.out.println(data + ": found");

        else 
            System.out.println(data + ": NOT found");

        //putting flag back to false state to prepare for future searches
        searchflag = false;
    }

    void delete(int data)
    {
        root = deletewrapper(root, data);
    }

    void inorder()
    {
        inorderwrapper(root);
    }
    // Prints out the information of the right tree and left tree (height and amount of children).
    void printBSTdetails()
    {
        if (root == null)
            return;

        countChildren(root);
        getDepth(root);

        System.out.printf("\nleft children:%11d", LeftChildren);
        System.out.printf("\nleft depth:%14d", LeftDepth);
        System.out.printf("\nright children:%10d", RightChildren);
        System.out.printf("\nright depth:%13d\n", RightDepth);
    }

    public static void complexityIndicator() {
        System.err.println("ch158330;2.5;20");
        return;
    }

    // Main that will proccess all File infomration and sends the actions need to be
    // sent to the BST tree.
    public static void main(String[] args) {
        // Calling constructor to intialize BST Tree
        Hw01 bstTree = new Hw01();
        // trys to read in file and print all of its contents, if file not found then
        // exit,
        try {
            File file = new File(args[0]);
            Scanner scanner = new Scanner(file);

            System.out.println(file + " contains:");

            while (scanner.hasNext()) {
                String s = scanner.nextLine();
                System.out.println(s);
            }

            scanner.close();
        }

        catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        try {
            // Pulls file back up inorder to Complete proccessing after printing its
            // contents to the terminal.
            File file = new File(args[0]);
            Scanner scanner = new Scanner(file);

            // Proccesses all the information inside the file provided in the command line.
            while (scanner.hasNext()) {
                String insertkey = "i";
                String deletekey = "d";
                String quitkey = "q";
                String printkey = "p";
                String searchkey = "s";

                String s = scanner.nextLine();

                String[] filecontents = s.split(" ");

                if (filecontents[0].equals(insertkey))
                    bstTree.insert(Integer.parseInt(filecontents[1]));

                if (filecontents[0].equals(quitkey))
                    break;

                if (filecontents[0].equals(deletekey))
                    bstTree.delete(Integer.parseInt(filecontents[1]));

                if (filecontents[0].equals(searchkey))
                    bstTree.search(Integer.parseInt(filecontents[1]));

                if (filecontents[0].equals(printkey))
                    bstTree.inorder();
            }

            scanner.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        
        // prints tree details if there is one intialized
        if (bstTree != null)
            bstTree.printBSTdetails();

            complexityIndicator();
        }
}