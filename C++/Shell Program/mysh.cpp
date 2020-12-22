/*            Christian Lozano                     */
/*               NID:4233003                       */
/*                Fall 2020                        */      
/*                HW3 shell                        */

#include <iostream>
#include <string.h>
#include <sstream>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
using namespace std;


class Shell
{
        private:
        //private directury of the shells current status
        //collection of command strings and pid's vector allows for dynamic adding for history
        string currentDirectory;
        vector<string> recentCommands;
        vector<pid_t> pid_history;
        

        //class for shell and its public functions to be used accross the program, self explaintory function names
        public:
        Shell(string directory)
        {
                currentDirectory = directory;
                recentCommands.clear();
                pid_history.clear();
        };
        
        void saveCommand(string command)
        {
            recentCommands.push_back(command);
        }

        void history () 
        {   
            if(recentCommands.size() == 0)
                return;
            
            cout << "Command History:\n";

            for(int i = 0; i <  recentCommands.size() - 1; i++)
                cout << recentCommands.at(i) << "\n";       
        }
        
        void clearHistory()
        {
            recentCommands.clear();
        }

        string getDirectory() 
        {
            return currentDirectory;
        }
        
        void setDirectory(string newDirectory)
        {
            currentDirectory = newDirectory;
        } 
        
        void catDirectory(string toAppend)
        {
            currentDirectory.append(toAppend);
        }

        void savePID(pid_t toRecord)
        {
            pid_history.push_back(toRecord);
        }
};


//helper function to make the command line arguments into a char array to proccess
char ** stringtoCharArry(string inArgs)
{
        int i;
        stringstream ss(inArgs);
        vector<string> arguments;
        arguments.clear();
        
        while(ss >> inArgs)
            arguments.push_back(inArgs);
                
        char **args = new char*[arguments.size() + 1];
        
        args[0] = new char[arguments.at(0).size()];
        strcpy(args[0], arguments.at(0).c_str());
        
        for(i = 1; i < arguments.size(); i++)
        {
            args[i] = new char[arguments.at(i).size()];
            strcpy(args[i], arguments.at(i).c_str() );
        }            
                
        args[i] = (char *)0;
                
        return args;
}

//Proccess the input from the user
Shell parser(Shell shell, string input)
{
    stringstream ss(input);
    string command;
    string arguments = "";
    string paramters;
    bool directoryFlag = false;

    shell.saveCommand(input);

    ss >> command;

    //moves directory
    if(command.compare("movetodir") == 0)
    {
        const char * tempchar;
        ss >> arguments;
        int isValidDir;

        // if directory is full
        if(arguments[0] == '/')
        {
            string tempString2 = shell.getDirectory() + arguments;
            tempchar = tempString2.c_str();
            isValidDir = access(tempchar, F_OK);
        }

        else
        {
            string tempString = shell.getDirectory() + '/' + arguments;
            tempchar = tempString.c_str();
            directoryFlag = true;
            isValidDir = access(tempchar, F_OK);
        }

        //checks for valid directory
        if(isValidDir == 0)
        {
            if(directoryFlag == true)
            {
                shell.catDirectory("/");
                shell.catDirectory(arguments);
            }

            else
                shell. catDirectory(arguments);

            cout << shell.getDirectory();
            return shell;
        }

        else
        {
            cout << "Error invalid path: " << shell.getDirectory() << "/" <<arguments;
            return shell;
        }
        
    }

    //prints directory of where you are
    else if(command.compare("whereami") == 0)
    {
        cout << shell.getDirectory();
        return shell;
    }

    //history clearing or printing
    else if (command.compare("history") == 0)
    {
        ss >> arguments;
        
        if(arguments.compare("-c")== 0)
            shell.clearHistory();

        else if(arguments == "")
        {
            shell.history();
        }

        else
            cout << "Invalid argument(s) after history";

        return shell;
    }

    //runs program
    else if (command.compare("start") == 0)
    {
        ss >> arguments;
        string programName = "";
        int childStatus;

        //case for absolute directory
        if(arguments[0] == '/')
            programName = arguments;

        //and for relative directory
        else
            programName = shell.getDirectory() + '/' + arguments;

        const char *programNameChar = programName.c_str();

        //check if valid executable
        if(access (programNameChar, X_OK) != 0)
        {
            cout << "Program " <<shell.getDirectory() << " does not exsist";
            return shell;
        }

        pid_t PID = fork();

        //executes program
        if(PID == 0)
        {
            while(ss >> paramters)
            {
                arguments.append(" ");
                arguments.append(paramters);
            }

            char **args = stringtoCharArry(arguments);
            execv(programNameChar, args);
        }

        //error handleing
        else if(PID < 0)
        {
            cout << "Fork failed";
            return shell;
        }

        //waits for child to finish
        else
        {
            waitpid(PID, &childStatus, WUNTRACED);
            return shell;
        }
    }

    //background , same to run but prints PID of program started and returns prompt
    else if (command.compare("background") == 0)
    {
        ss >> arguments;
        string programName = "";
        int childStatus;

        //case for absolute directory
        if(arguments[0] == '/')
            programName = arguments;

        //and for relative directory
        else
            programName = shell.getDirectory() + '/' + arguments;

        const char *programNameChar = programName.c_str();

        //check if valid executable
        if(access (programNameChar, X_OK) != 0)
        {
            cout << "Program " <<shell.getDirectory() << " does not exsist";
            return shell;
        }

         pid_t PID = fork();

        //executes program
        if(PID == 0)
        {
            while(ss >> paramters)
            {
                arguments.append(" ");
                arguments.append(paramters);
            }

            char **args = stringtoCharArry(arguments);
            execv(programNameChar, args);
        }

        //error handleing
        else if(PID < 0)
        {
            cout << "Fork failed";
            return shell;
        }

        //saves pid and prints it out
        else
        {
            cout << "PID:"<< PID;
            shell.savePID(PID);
            return shell;
        }
    }

    //kills a proccess given the PID parmater
    else if (command.compare("exterminate") == 0)
    {
        ss >> arguments;
        pid_t argmentPID = (pid_t)stoi(arguments);
        int killResult = kill(argmentPID , SIGKILL);
        
        if(killResult == -1)
            cout << "Exterminate Failed";

        else
            cout << "Exterminate Successful";

        return shell;
    }

    //if not valid command
    else
    {
        cout << "Invalid commmand!";
        return shell;
    }

    return shell;
}

//start of program keeps reading till byebye input
int main()
{
    std::string input;
    char currentDirectory[1024];
    string workingDir = getcwd(currentDirectory, sizeof(currentDirectory));
    Shell shell(workingDir);
    cout << "# ";
    getline(cin, input);

    while(input.compare("byebye") != 0)
    {
        shell = parser(shell, input);
        cout << "\n# ";
        getline(cin, input);
    }

    return 0;
}