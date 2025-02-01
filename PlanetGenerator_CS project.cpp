#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

const int MAX_NAME_PARTS = 5;
const int MAX_HISTORY_EVENTS = 6;
const int MAX_RACES = 5;

string name_parts[] = {"Zor", "Arg", "Tron", "Bel", "Nix", "Eld", "Omn", "Qua", "Tal", "Xyn", "Arra", "Kis"};
string atmospheres[] = {"Oxygen-rich", "Methane", "Carbon Dioxide", "Nitrogen", "Ammonia"};
string size_descriptions[] = {"Tiny", "Small", "Medium", "Large", "Massive"};

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
    "They claim that this is where they found out the answer to Life, the Universe and Everything",
    "Great source of Spice",
    "Home Planet to the Lisan al-Gaib?",
    "Dr WHO was here",
    "In proximity to a Halo ring",
    "It has multiple moons",
    "Asimov must have written his laws of robotics here"
};

string races[] = {"Mandalorians", "Shanghili", "Xenomorphs", "Vulcans", "Geth", "Jedi", "Turians", "Daleks", "Martians", "Laser Sharks"};
string appearances[] = {"Tall", "Short", "slender", "Reptilian", "Humanoid", "Insect-like"};
string techLevels[] = {"Primitive", "Industrial", "Spacefaring", "Advanced AI", "Interdimensional"};
string governments[] = {"Monarchy", "Republic", "Tribal council", "Technocracy", "Anarchy", "Theocracy"};

class Planet {
private:
    string name;
    string atmosphere;
    string size;
    
    string history[MAX_HISTORY_EVENTS];
    int eventCount;
    
    string raceList[MAX_RACES];
    string raceDetails[MAX_RACES];
    int raceCount;

public:
	//constructor
    Planet() 
	{
        name = generatePlanetName();
        atmosphere = generateAtmosphere();
        size = generateSize();
        generateHistory();
        generateRaces();
    }

	//Methods
    string generatePlanetName() 
	{
        string pname = "";
        for (int i = 0; i < (rand() % 3 + 2); i++) 
		{	pname += name_parts[rand() % MAX_NAME_PARTS];	}
        return pname;
    }

    string generateAtmosphere() 
	{	return atmospheres[rand() % 5];	}

    string generateSize() 
	{	return size_descriptions[rand() % 5];	}

    void generateHistory() 
	{
        eventCount = rand() % MAX_HISTORY_EVENTS + 1;
        for (int i = 0; i < eventCount; i++) 
		{	history[i] = histories[rand() % 3];	}
    }

    void generateRaces() 
	{
        raceCount = rand() % MAX_RACES + 1;
        
        for (int i = 0; i < raceCount; i++) 
		{
            raceList[i] = races[rand() % 5];
            raceDetails[i] = "Appearance { " + appearances[rand() % 5] + " }, " +
                             "Tech Level { " + techLevels[rand() % 5] + " }, " +
                             "Government { " + governments[rand() % 5] + " }";
        }
    }

    void displayPlanet() 
	{
        cout << "\nPlanet Details" << endl;
        cout << "--------------" << endl;
        cout << "Name: " << name << endl;
        cout << "Atmosphere: " << atmosphere << endl;
        cout << "Size: " << size << endl;
        
        cout << "\nHistory:" << endl;
        for (int i = 0; i < eventCount; i++) 
		{	cout << "- " << history[i] << endl;	}
		
        cout << "\nRaces:" << endl;
        for (int i = 0; i < raceCount; i++) 
		{	cout << raceList[i] << " - " << raceDetails[i] << endl;	}
    }

    void saveToFile(const string& filename) 
	{
        ofstream outFile(filename);
        if (outFile) 
		{
            outFile << name << "\n";
            outFile << atmosphere << "\n";
            outFile << size << "\n";
            
            outFile << eventCount << "\n";
            for (int i = 0; i < eventCount; i++) 
			{	outFile << history[i] << "\n";	}
			
            outFile << raceCount << "\n";
            for (int i = 0; i < raceCount; i++) 
			{	outFile << raceList[i] << "\n" << raceDetails[i] << "\n";	}
        }
        outFile.close();
    }

    void loadFromFile(const string& filename) 
	{
        ifstream inFile(filename);
        if (inFile) 
		{
            getline(inFile, name);
            getline(inFile, atmosphere);
            getline(inFile, size);
            
            inFile >> eventCount;
            inFile.ignore();
            for (int i = 0; i < eventCount; i++) 
			{	getline(inFile, history[i]);	}
			
            inFile >> raceCount;
            inFile.ignore();
            for (int i = 0; i < raceCount; i++) 
			{
                getline(inFile, raceList[i]);
                getline(inFile, raceDetails[i]);
            }
        }
        inFile.close();
    }
};

int main() 
{
    srand(static_cast<unsigned int>(time(0)));

    string filename = "planet_data.txt"; 
    
    int Input; 

    do
    {
        cout << "\n================================================" << endl;		
        cout << "1. Explore a New Planet" << endl;
        cout << "2. Explore Previous Planet from File" << endl;
        cout << "3. Exit Program" << endl;
        cout << "Enter your choice: ";
        
        cin >> Input;

        switch (Input)
        {
            case 1:
            {
                Planet planet;
                planet.displayPlanet();

                planet.saveToFile(filename);
                cout << "\nPlanet data saved to " << filename << endl;	
                break;			
            }

            case 2:
            {
                Planet loadedPlanet;
                loadedPlanet.loadFromFile(filename);
                cout << "\nLoaded Planet Details:" << endl;
                loadedPlanet.displayPlanet();	
                break;			
            } 

            case 3:
            {
                cout << "Exiting program. Goodbye!" << endl;
                break;		
			}
			
            default:
            {
                cout << "Invalid choice! Please enter a number between 1 and 3." << endl;
                break;
        	}
        }
    } while (Input != 3);

    return 0;
}
