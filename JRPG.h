#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;
//Project By Yazdan Ali Khan (2024665), Hammad Shahid (2024389)

#define DEBUG  // Comment this line to disable debug messages

//Windows .h 
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void SetColor(int color) 
{	SetConsoleTextAttribute(hConsole, color);	}

void PlaySoundEffect(const string &effect) 
{
    if (effect == "attack") Beep(800, 400); // Parameters take frequency and duration
    else if (effect == "miss") Beep(300, 200);
    else if (effect == "buff") Beep(700, 200);
}

//Variables Arrays and constants (Dont mind the names these are taken from a list of popular JRPGs)
string first_names[] = {"Rei", "Kai", "Akira", "Shiro", "Kris", "Ren", "Ash", "Taro", "Luca ", "Raven", "Skyler", "Noa", "Sage", "Shin", "Jin"};
string last_names[] = {" Van Damme", " Dimitrescu", " Lynx", " Kitagawa", " Crescent", " Reynolds", " Tatsumi", " Yamada", " Miyamoto", " Sakamoto", " Dracula", " Kazama", " Kisaragi", " Lion-Heart" };

string Team_name1[] = {"Midgard", "Zanarkand", "Palmacosta", "Alcamoth", "Tortuga", "Shevat", "Gilito", "Lindblum", "Asgard"};
string Team_name2[] = {" Blades", " Sentinels", " Vanguard", " Covenant", " Syndicate", " Stormbringers", " Knights", " Abysswalkers", " Pact"};

const int NUMBER_OF_TEAMS = 4, PLAYERS_PER_TEAM = 3, TOTAL_MATCHES = 11; //I could use #define for this instead lol

//Prototypes
class Entity;
class PLayer;
class Team;
class PlayerTeam;
class BattleManager;
class Schedule;
class GameManager;
class ConsoleManager;	

//CLASSES
class Entity{															//Base class for all NPCs
	protected:
		string name;	
		bool Is_Alive;
		int HP = 20, ATK, SPD, DEF;
		int Cur_HP = HP, Cur_ATK = ATK, Cur_SPD = SPD, Cur_DEF = DEF;
		
	public:
		void* Opposing_TeamPtr = nullptr;
		
		virtual void Display_Stats();	
		void generate_character();
		void Reset_Stats();
		void Attack_Check(Entity &Target);
			
		//Getters
		string get_Name()	{	return(name);	}
		bool get_Is_Alive() {	return Is_Alive;}
		int get_HP()		{	return(HP);		}	
		int get_ATK()		{	return(ATK);	}		
		int get_SPD()		{	return(SPD);	}
		int get_DEF()		{	return(DEF);	}
		
		int get_Cur_HP()		{	return(Cur_HP);		}	
		int get_Cur_ATK()		{	return(Cur_ATK);	}			
		int get_Cur_SPD()		{	return(Cur_SPD);	}
		int get_Cur_DEF()		{	return(Cur_DEF);	}
		
		//Setters
		void set_HP(int new_HP) 	  {Cur_HP = new_HP;}
		void set_Is_Alive(bool Alive) {Is_Alive = Alive;} 
		void set_ATK(int new_ATK) 	  {Cur_ATK = new_ATK;}
		void set_SPD(int new_SPD) 	  {Cur_SPD = new_SPD;}
		void set_DEF(int new_DEF)     {Cur_DEF = new_DEF;}
		
		virtual void Choose_Target(Team &enemy_Team);       //Overloaded Choose Target because it kept messing up
		virtual void Choose_Target(PlayerTeam &enemy_Team); 
		virtual void Actions();
		
		Entity() : ATK(0), SPD(0), DEF(0), Is_Alive(true) 
		{ 
			generate_character(); 
			Reset_Stats(); 
		}
};

class Player : public Entity {										
    public:
    	void Modify_Stat(int &stat, int amount, const string statName);
    	
    	void Choose_Target(Team &enemy_Team) override;		//Overridden methods
    	void Actions() override;
    	void Display_Stats() override;
    	
        Player()											
		{
            generate_character();
            Reset_Stats();
        }
};
 
class Team{																//Base Team class contains NPCS(Entities)
	protected:
		string name;
		short ID, wins = 0, losses = 0;
		int OVR_ATK;
		bool Is_Team_Alive;
	
	public:	
		Entity Members[PLAYERS_PER_TEAM];
		
		void Run_For_All_Members(void (Entity::*method)()); 
		void Display_Members();
		
		void Display_stats();
										//Getters
		string get_Name() {	return(name);	};
		int get_OVR();
		int get_Wins()    {	return(wins);	};
		int get_Losses()  { return(losses);	};
										//Setters
		void add_Win() { wins++; };
		void add_Loss() { losses++; };	
		void reset_Stats();	
		
		Team()							//Constructor
		{	
			name = Team_name1[rand() % (sizeof(Team_name1) / sizeof(Team_name1[0]))] + Team_name2[rand() % (sizeof(Team_name2) / sizeof(Team_name2[0]))];	
			get_OVR();
		}
};

class PlayerTeam : public Team{ 										//Team Class contains PCs
	public:
		Player Members[PLAYERS_PER_TEAM];	
		
		void Display_Members();
		
        PlayerTeam() : Team()				//Constructor
		{
			for (int i = 0; i < PLAYERS_PER_TEAM; i++) 
			{
				Members[i] = Player(); // Explicitly initialize each Player
			}
		}
};

class BattleManager{													//All Combat functions are contained here
	public: 
		static void Battle_Simulation(Team &team1, Team &team2);
		static void PC_Battle(PlayerTeam &PC_Team, Team &Opposing_Team); 
		static void Declare_Winner(Team &winner, Team &loser);
		static void Display_Round_Summary(PlayerTeam &PC_Team, Team &Opposing_Team); 
};

class Schedule{															//Sets the Matchups based on day contained in GameManager class
	private:
		int Day = 0;
		int matchups[TOTAL_MATCHES][2] = {	{0,0}, {4, 3}, {1, 0} ,{2, 3}, {4, 0}, {0, 2}, {1, 3}, {4, 1}, {0, 3}, {1, 2}, {4, 2}};
		Team* teams;
		PlayerTeam* playerTeam;
	
	public:
		void reset() {Day = 0;}	// Reset for a new season
		void Matchup(); 
		int get_Days() {   return Day;	}	
		
    Schedule(Team* teamsPtr, PlayerTeam* playerPtr) : teams(teamsPtr), playerTeam(playerPtr) {	Day = 0;	}
};	

class GameManager {														//Essentially the Main Game class
    private:	
        Team NPC_Teams[NUMBER_OF_TEAMS];
        PlayerTeam PC_Team;
        Schedule season;

    public:
    	void Run_For_All_Teams(void (Team::*method)()); 
    	void Display_Standings();
    	void Display_Roster()  	 {Run_For_All_Teams(&Team::Display_Members); PC_Team.Display_Members();}; 
    	
    	void Run_Game();
    	void Management_Mode(); 
    	void Final();
    	void Trade();
    	void Reset_TeamStats(); 
		void Swap_Entities(int teamA_id, int playerA_id, int teamB_id, int playerB_id);
    	
    	GameManager() : season(NPC_Teams, &PC_Team) {}
};

class ConsoleManager {													//Handles UI and Static Methods
    public:
        static void PrintTitle();
		static void PrintMenu();
		static void ClearScreen();
		static void PrintManagementMenu();
};