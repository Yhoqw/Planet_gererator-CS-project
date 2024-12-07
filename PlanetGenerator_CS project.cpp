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
    "survived the death star"
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
    int Input;
    do 
	{
        cout << "Planet Generator" << endl;
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