#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// Constants
const int MAX_NAME_PARTS = 5;
const int MAX_HISTORY_EVENTS = 10;
const int MAX_RACES = 6;

// String arrays
string name_parts[] = {"Zor", "Arg", "Tron", "Bel", "Nix", "Eld", "Omn", "Qua", "Tal", "Xyn"};
string atmospheres[] = {"Oxygen-rich", "Methane", "Carbon Dioxide", "Nitrogen", "Ammonia", "Helium"};
string size_descriptions[] = {"Tiny", "Small", "Medium", "Large", "Massive"};


//string for planet history prompts
string histories[] = 
{
    "colonized by ancient explorers",
    "destroyed in a cosmic war",
    "thrived as a hub for trade",
    "home to a great empire",
    "witness to a catastrophic event",
    "abandoned due to resource depletion",
    "birthplace of a new religion",
    "known for its unique flora and fauna",
    "a target of space pirates",
    "a secret research outpost",
    "ravaged by nuclear war",
    "survived the death star",
    "probably one of starfields 1,692 planets",
    "They claim that this is where they found out the answer to Life, the Universe and Everything"
    
};

//string for alien race names
string races[] = 
{
    "Mandalorians", "Shanghili", "Xenomorphs", "Vulcans", "Geth", "Jedi", "Turians" 
};

string appearances[] = {"Tall", "Short", "slender", "Reptilian", "Humanoid", "Insect-like"};
string techLevels[] = {"Primitive", "Industrial", "Spacefaring", "Advanced AI", "Interdimensional"};
string governments[] = {"Monarchy", "Republic", "Tribal council", "Technocracy", "Anarchy", "Theocracy"};


// Function prototypes
string generatePlanetName();
string generateAtmosphere();
string generateSize();
void generateHistory(string history[], int &eventCount);
void generateRaces(string raceList[], string raceDetails[], int &raceCount);
void displayPlanet(const string &name, const string &atmosphere, const string &size, const string history[], int eventCount, const string raceList[], const string raceDetails[], int raceCount);
void save_planet_file(const string &name, const string &atmosphere, const string &size, const string history[], int eventCount, const string raceList[], const string raceDetails[], int raceCount);
void load_planet_file();

int main() 
{
    //for seeding
	srand(static_cast<unsigned int>(time(0)));

    //Menu
    cout << "=============================================================================================================================" << endl;
    cout << " ######  #          #    #     # ####### #######     #####  ####### #     # ####### ######     #    ####### ####### ######  " << endl;
	cout << " #     # #         # #   ##    # #          #       #     # #       ##    # #       #     #   # #      #    #     # #     # " << endl;
    cout << " ######  #       #     # #  #  # #####      #       #  #### #####   #  #  # #####   ######  #     #    #    #     # ######  " << endl;
    cout << " #       #       ####### #   # # #          #       #     # #       #   # # #       #   #   #######    #    #     # #   #   " << endl;
    cout << " #       #       #     # #    ## #          #       #     # #       #    ## #       #    #  #     #    #    #     # #    #  " << endl;
    cout << " #       ####### #     # #     # #######    #        #####  ####### #     # ####### #     # #     #    #    ####### #     # " << endl;
    cout << "=============================================================================================================================" << endl;    
    
    cout << "A project by Yazdan Ali Khan, Raja Yawar Abbas and Hammad Shahid" << endl;
    
    int Input;
    do 
	{
        cout << "\n" "================================" << endl;		
        cout << "1. Explore a New Planet" << endl;
        cout << "2. Explore previous Planet from File" << endl;
        cout << "3. Exit Program" << endl;
        cout << "Enter your choice: ";
        cin >> Input;

        switch (Input) 
		{	
			
			//case for planet Gereration
            case 1: 
			{	
                string planetName = generatePlanetName();			
                string planetAtmosphere = generateAtmosphere();
                string planetSize = generateSize();

                // Generate history 
                string planetHistory[MAX_HISTORY_EVENTS];
                int historyEventCount = 0;
                generateHistory(planetHistory, historyEventCount);
				
				//Generate Races
                string planetRaces[MAX_RACES];
                string raceDetails[MAX_RACES];  
				              
                int raceCount = 0;
                generateRaces(planetRaces, raceDetails, raceCount);

                // Display and save the planet (using functions)
                displayPlanet(planetName, planetAtmosphere, planetSize, planetHistory, historyEventCount, planetRaces, raceDetails, raceCount);
                save_planet_file(planetName, planetAtmosphere, planetSize, planetHistory, historyEventCount, planetRaces, raceDetails, raceCount);
                
                //Challenge logic
                int Duel_input;
                
                cout << "\n" "---------------------------" << endl;
                cout << "The inhabitants challenge you to a duel if you want to leave their planet. Press" "\n" "1. To play a guessing game " "\n" "2. To play a round of Tic tac toe" << endl;
                cin >> Duel_input;
                
                switch (Duel_input)
                {
                
                	case 1:
                	{
                		
                		//Guessing game logic
                		int secret_number = rand() % 20 + 1;
                		int max_attempts = 5;
                
                		cout << "\n" "---------------------------" << endl;
    					cout << "Welcome to Guess the Number game!" << endl;
    					cout << "You have " << max_attempts << " attempts to guess the number." << endl;                
                
    					// Loop for the guessing game
    					for (int attempt = 1; attempt <= max_attempts; attempt++) 
						{
						
        					cout << "Attempt " << attempt << " of " << max_attempts << endl;
        	
        					// Ask for the user's guess
        					int guess;
        	
    		    			cout << "Enter your guess (1-20): ";
    				    	cin >> guess;

    				    	// Check if the guess is correct or not
    				    	if (guess > secret_number) 
							{
    				    	    cout << "Too high! Try again." << endl;
        					} 
		
							else if (guess < secret_number) 
							{
    				    	    cout << "Too low! Try again." << endl;
    				    	}
        
							else 
							{
    				    	    cout << "Congratulations! You guessed the right number!" << endl;
    				    	    break;
    				    	}

    				    	// after attempts are finished give the answer
    				    	if (attempt == max_attempts) 
							{
        	    				cout << "Sorry, you've used all your attempts. The correct number was " << secret_number << "." << endl;
        					}		
    					}
    					
    					break;
    				}						
				
					case 2:
					{
						char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    					char player = 'X', computer = 'O';
    
    					cout << "Welcome to Tic Tac Toe!\n";

    					while (true) 
						{
        					// Display the board
        					cout << "\n";
        					for (int i = 0; i < 3; i++) 
							{
            					for (int j = 0; j < 3; j++) 
								{
                					cout << board[i][j] << " ";
            					}
        					    cout << "\n";
        					}

        					// Player's turn
        					int move;
        					cout << "Enter your move (1-9): ";
        					cin >> move;

        					int row = (move - 1) / 3, col = (move - 1) % 3;

        					if (move < 1 || move > 9 || board[row][col] == 'X' || board[row][col] == 'O') 
							{
        					    cout << "Invalid move! Try again.\n";
            					continue;
        					}

    					    board[row][col] = player;

        					// Check for player win
        					bool playerWin = false;
        					for (int i = 0; i < 3; i++) 
							{
            					if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || (board[0][i] == player && board[1][i] == player && board[2][i] == player)) 
								{
                					playerWin = true;
                					break;
            					}
        					}
        					
							if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[0][2] == player && board[1][1] == player && board[2][0] == player)) 
							{
        					    playerWin = true;
        					}

        					if (playerWin) 
							{
            					cout << "\n";
            					for (int i = 0; i < 3; i++) 
								{
                					for (int j = 0; j < 3; j++) 
									{
                    					cout << board[i][j] << " ";
                					}
                					cout << "\n";
            					}				
            					cout << "Congratulations! You win!\n";
            					break;
        					}

        					// Check if board is full (draw)
        					bool draw = true;
        					for (int i = 0; i < 3; i++) 
							{
            					for (int j = 0; j < 3; j++) 
								{
                					if (board[i][j] != 'X' && board[i][j] != 'O') 
									{
                    					draw = false;
                					}
            					}
        					}
        					if (draw) 
							{
            					cout << "\n";
            					for (int i = 0; i < 3; i++) 
								{
                					for (int j = 0; j < 3; j++) 
									{
                    					cout << board[i][j] << " ";
                					}
                					cout << "\n";
            					}
            				cout << "It's a draw!\n";
            				break;
        					}

        					// Computer's turn
        					bool moveMade = false;
        					for (int i = 1; i <= 9 && !moveMade; i++) 
							{
            					row = (i - 1) / 3, col = (i - 1) % 3;
            					if (board[row][col] != 'X' && board[row][col] != 'O') 
								{
                					board[row][col] = computer;
                					moveMade = true;
            					}
        					}

        					// Check for computer win
        					bool computerWin = false;
        					for (int i = 0; i < 3; i++) 
							{
            					if ((board[i][0] == computer && board[i][1] == computer && board[i][2] == computer) || (board[0][i] == computer && board[1][i] == computer && board[2][i] == computer)) 
								{
                					computerWin = true;
                					break;
            					}
        					}
        					
							if ((board[0][0] == computer && board[1][1] == computer && board[2][2] == computer) || (board[0][2] == computer && board[1][1] == computer && board[2][0] == computer)) 
							{
           						computerWin = true;
        					}

        					if (computerWin) 
							{
            					cout << "\n";
            					for (int i = 0; i < 3; i++) 
								{
                					for (int j = 0; j < 3; j++) 
									{
                    					cout << board[i][j] << " ";
                					}
                					cout << "\n";
            					}
            					cout << "Computer wins! Better luck next time.\n";
            					break;
        					}
    					}
    					break;
					}
					
				}

                break;
            }
            
            //case for loading saved planet
            case 2:
            {
                load_planet_file();
                break;
        	}
        	
        	//case for exiting program
            case 3:
            {
                cout << "Exiting program. Goodbye!" << endl;
                break;
        	}
        	
            default:
            {	
            	//can use cerr here as well :) I checked 
                cout << "Invalid choice. Please try again." << endl;
        	}
            
        }
    } while (Input != 3);

    return 0;
}

// Function to generate a random planet name
string generatePlanetName() 
{
    int parts = rand() % 3 + 2; // Between 2 and 4 parts
    string name = "";
    
    // Combining together multiple names to make one name essentially
    for (int i = 0; i < parts; ++i) 
	{
		
        name += name_parts[rand() % MAX_NAME_PARTS];
        
    }
    
    return name;
}

// Function to generate a random atmosphere
string generateAtmosphere() 
{
	
    return atmospheres[rand() % (sizeof(atmospheres) / sizeof(atmospheres[0]))];
    
}

// Function to generate a random size
string generateSize() 
{
	
    return size_descriptions[rand() % (sizeof(size_descriptions) / sizeof(size_descriptions[0]))];
    
}

// Function to generate a random history
void generateHistory(string history[], int &eventCount) 
{
    eventCount = rand() % MAX_HISTORY_EVENTS + 1; // Between 1 and MAX_HISTORY_EVENTS
    
    for (int i = 0; i < eventCount; ++i) 
	{
		
        history[i] = histories[rand() % (sizeof(histories) / sizeof(histories[0]))];       
    }
    
}

// Function to generate random races
void generateRaces(string raceList[], string raceDetails[], int &raceCount) 
{
    raceCount = rand() % MAX_RACES + 1; // Between 1 and MAX_RACES
    for (int i = 0; i < raceCount; ++i) 
	{
		
        raceList[i] = races[rand() % (sizeof(races) / sizeof(races[0]))];
        
        //randmly generates (apearance, tech and government of alien races
        raceDetails[i] = "Appearance { " + appearances[rand() % (sizeof(appearances) / sizeof(appearances[0]))] + " }, " +
                         "Tech Level { " + techLevels[rand() % (sizeof(techLevels) / sizeof(techLevels[0]))] + " }, " +
                         "Government { " + governments[rand() % (sizeof(governments) / sizeof(governments[0]))] + " }";		        
    
	}
}

// Function to display the planet details
void displayPlanet(const string &name, const string &atmosphere, const string &size, const string history[], int eventCount, const string raceList[], const string raceDetails[], int raceCount) 
{
    cout << "\n" "Planet Details" << endl;
    cout << "--------------" << endl;
    cout << "Name: " << name << endl;
    cout << "Atmosphere: " << atmosphere << endl;
    cout << "Size: " << size << endl;

    cout << "\nHistory:" << endl;
    for (int i = 0; i < eventCount; ++i) 
	{
		
        cout << "- " << history[i] << endl;
        
    }

    cout << "\nRaces:" << endl;
    for (int i = 0; i < raceCount; ++i) 
	{
		
        cout << "- " << raceList[i] << ": " << raceDetails[i] << endl;
	        
    }
}

// Function to save the planet details to a file
void save_planet_file(const string &name, const string &atmosphere, const string &size, const string history[], int eventCount, const string raceList[], const string raceDetails[], int raceCount) 
{
    ofstream outFile("planet.txt");
    if (outFile.is_open()) 
	{
        outFile << name << endl;
        outFile << atmosphere << endl;
        outFile << size << endl;
        outFile << eventCount << endl;
        
        //for saving histories
        for (int i = 0; i < eventCount; ++i) 
		{
			
            outFile << history[i] << endl;
            
        }
        
        //for saving races
        outFile << raceCount << endl;
        for (int i = 0; i < raceCount; ++i) 
		{
			
            outFile << raceList[i] << endl;
           	outFile << raceDetails[i] << endl;           
           	
        }
        
        outFile.close();
        cout << "\nPlanet saved to 'planet.txt' successfully." << endl;
        
    } 
    
	else 
	{
        cerr << "\nError: Unable to open file for writing." << endl;
    }
    
}

// Function to load and display planet details from a file
void load_planet_file() 
{
    ifstream inFile("planet.txt");
    
	if (inFile.is_open()) 
	{
        string name, atmosphere, size;
        int eventCount, raceCount;

        getline(inFile, name);
        getline(inFile, atmosphere);
        getline(inFile, size);
        inFile >> eventCount;
        inFile.ignore(); // Ignore newline

        string history[MAX_HISTORY_EVENTS];
        for (int i = 0; i < eventCount; ++i) 
		{
			
            getline(inFile, history[i]);
            
        }

        inFile >> raceCount;
        inFile.ignore(); // Ignore newline

        string raceList[MAX_RACES];
        string raceDetails[MAX_RACES];       
        
        for (int i = 0; i < raceCount; ++i) 
		{
			
            getline(inFile, raceList[i]);
            getline(inFile, raceDetails[i]);
            
        }

        inFile.close();

        // Display the loaded planet details
        displayPlanet(name, atmosphere, size, history, eventCount, raceList, raceDetails, raceCount);
    }
	 
	else 
	{
        cerr << "\nError: Unable to open file for reading." << endl;
    }
}
