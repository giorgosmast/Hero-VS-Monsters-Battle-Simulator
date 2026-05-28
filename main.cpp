#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;    

struct weapon{
    string name;
    int minDamage;
    int maxDamage;
};

weapon weaponPool[8] = {
    {"Sword", 10, 20},
    {"Axe", 18, 30},
    {"CrossBow", 8, 18},
    {"Dagger", 5, 15},
    {"Staff", 12, 22},
    {"Pistol", 7, 17},
    {"Mace", 23, 35},
    {"Spear", 10, 17}
};

class Monster; // Οριζω την κλαση Monster ωστε οταν την αναφερω κατω στην κλαση Hero να μην μου βγαλει error

class Hero{
    public:
    // Data
        string name;
        int hp;
        int maxHP;
        int ac;
        int defence;
        int kills;
        int totalDamageDealt;
        int totalDamageTaken;
        weapon weaponName;

    // Constructor
        Hero(string n, weapon w){
            name = n;
            weaponName = w;
            hp = 100;
            maxHP = 100;
            ac = 12;
            defence = 10;
            kills = 0;
            totalDamageDealt = 0;
            totalDamageTaken = 0;
        }   
		
		void attack(Monster &target); // Oριζω την συναρτηση με την οποια θα επιτυθεται ο ηρωας.
		void special_attack(int skillChoice, Monster &target); // Οριζω την συναρτηση με την οποια ο ηρωας θα κανει special attacks.
};

struct MonsterType{
    string name;
    int minHP;
    int maxHP;
    int maxAC;
    int minAC;
    int minDefence;
    int maxDefence;
};

MonsterType Monsters[4] = {
    {"Goblin", 15, 28, 6, 4, 2, 4},
    {"Orc", 40, 58, 12, 8, 4, 8},
    {"Troll", 30, 40, 10, 2, 3, 6},
    {"Skeleton", 10, 15, 4, 2, 1, 3}
};


class Monster{
    public:
    // Data
        string  type;
        int hp;
        int ac;
        int defence;
        weapon weaponName;

    // Constructor
        Monster(){
            int i = rand() % 4; // Τυχαια επιλογη του Monster
            int weaponI = rand() % 8; // Τυχαια επιλογη οπλου του Monster
            
            type = Monsters[i].name; // Διαλεγουμε ενα τυχαιο Monster 
            hp = rand() % (Monsters[i].maxHP - Monsters[i].minHP + 1) + Monsters[i].minHP; // Του βαζουμε ενα τυχαιο hp. Κανουμε την πραξη στις παρενθεσεις για να βρουμε το ευρος το οποιο θα φτανει το modulo και υστερα το μετατοπιζουμε με το + minHP
            ac = rand() % (Monsters[i].maxAC - Monsters[i].minAC + 1) + Monsters[i].minAC; // Το ιδιο ακριβως που καναμε πανω για να βρουμε την αμυνα του AC
            weaponName = weaponPool[weaponI]; // Επιλεγει ενα τυχαιο οπλο απο το weaponPool με τον τυχαιο δεικτη weaponI που φτιαξαμε παραπανω
            defence = rand() % (Monsters[i].maxDefence - Monsters[i].minDefence + 1) + Monsters[i].minDefence; // Τυχαιος υπολογισμος του defence του Monster με βαση το minDefence και MaxDefence
        }
        
        void attack(Hero &target){
        	system("cls");
        	cout << type << " is planning to attack " << target.name << "!" << endl;
        	Sleep(1500);
        	system("cls");
			int hitRoll = rand() % 20 + 1; // Ριχνω το ζαρι για να δω αν θα φερω μεγαλυτερο αριθμο απο το ac του Hero
           
		    if (hitRoll >= target.ac){	
                int damage = rand() % (weaponName.maxDamage - weaponName.minDamage + 1) + weaponName.minDamage; // Βρισκω το τυχαιο damage με βαση το min και max του οπλου του Monster
                int rawDamage = damage - target.defence;
                int totalDamageDealt = rawDamage;
                
                if (totalDamageDealt <= 0) {
                	totalDamageDealt = 0; // Το κανουμε 0 ωστε να μην γινει αρνητικο και o hero γιατρευτει	
                	cout << type << " hits but the attack was completely blocked by defense! (0 damage)" << endl;
                }
				else{
					cout << type << " hits the " << target.name << " for " << damage << " damage!" << endl;
	                Sleep(1000);
	                system("cls");
	                cout << target.defence << " damage was blocked by the Hero's defence!" << endl;
	                
					target.hp -= totalDamageDealt;
	                if (target.hp < 0){
	                	target.hp = 0;
					}
	                
	                cout << "Total Damage: " << totalDamageDealt << " | " << target.name << " HP: " << target.hp << endl;
	                system("pause");
	                system("cls");	
				}
            }
            else{
                cout << type << " misses the " << target.name << "!" << endl;
                system("pause");
                system("cls");
            }
		}
	
		void special_attack(int skillChoice, Hero &target){
			int hitRoll = rand() % 20 + 1;
			
			if (hitRoll < target.ac){
		        system("cls");
				cout << type << " tried to use a Special Attack but missed!" << endl;
				system("pause");
				system("cls");
				return; // το ιδιο με τ ην συανρτηση του Hero
			}
			
			int damage = rand() % (weaponName.maxDamage - weaponName.minDamage + 1) + weaponName.minDamage; 
		    int rawDamage = damage - target.defence; 
		    int totalDamageDealt = 0;
			
			if(skillChoice == 1){
				totalDamageDealt = rawDamage + 8;
				cout << type << " used Heavy Smash!" << endl;
				system("pause");
				system("cls");
				cout << type << " hits the " << target.name << " for " << damage << " damage + 8 damage from Heavy Smash!" << endl;	
				system("pause");
			    system("cls");
			    cout << target.defence << " damage was blocked by the Hero's defence!" << endl;	
			    
			    target.hp -= totalDamageDealt;
				if (target.hp < 0){
			    	target.hp = 0;
				}
				
			    cout << "Total Damage: " << totalDamageDealt << " | Hero HP: " << target.hp << endl;
			    system("pause");
			    system("cls");	
			}
			else if (skillChoice == 2){
				totalDamageDealt = damage;
				cout << type << " used Poison Fang!" << endl;
				system("pause");
				system("cls");
				cout << type << " hits the " << target.name << " for " << damage << " ignoring Hero's defence!" << endl;	
				system("pause");
			    system("cls");
			    
			    target.hp -= totalDamageDealt;
				if (target.hp < 0){
			    	target.hp = 0;
				}
				
			    cout << "Total Damage: " << totalDamageDealt << " | Hero HP: " << target.hp << endl;
			    system("pause");
			    system("cls");	
			}
			else if (skillChoice == 3){
				totalDamageDealt = rawDamage * 1.25;	
				cout << type << " used Rage Attack!" << endl;
				system("pause");
				system("cls");
				cout << type << " hits the " << target.name << " for " << totalDamageDealt << " * 1.25 damage!" << endl;	
				system("pause");
			    system("cls");
			    
			    target.hp -= totalDamageDealt;
				if (target.hp < 0){
			    	target.hp = 0;
				}
				
			    cout << "Total Damage: " << totalDamageDealt << " | Hero HP: " << target.hp << endl;
			    system("pause");
			    system("cls");	
			}
			else if (skillChoice == 4){
				totalDamageDealt = target.hp / 1.75;	
				cout << type << " used Dark Strike!" << endl;
				system("pause");
				system("cls");
				cout << type << " hits the " << target.name << " for " << totalDamageDealt << " draining Hero's life!" << endl;	
				system("pause");
			    system("cls");
			    
			    target.hp -= totalDamageDealt;
				if (target.hp < 0){
			    	target.hp = 0;
				}
				
			    cout << "Total Damage: " << totalDamageDealt << " | Hero HP: " << target.hp << endl;
			    system("pause");
			    system("cls");	
			}
		}
};



void Hero::attack(Monster &target){ // Βαζω στην αρχη "Hero::" για να πω στο προγραμμα οτι ειναι η συναρτηση που εχω ορισει πανω στην κλαση Hero.
            system("cls");
			int hitRoll = rand() % 20 + 1; // Ριχνω το ζαρι για να δω αν θα φερω μεγαλυτερο αριθμο απο το ac του Monster 
            
			if (hitRoll >= target.ac){
                int damage = rand() % (weaponName.maxDamage - weaponName.minDamage + 1) + weaponName.minDamage; // Βρισκω το τυχαιο damage με βαση το min και max του οπλου
                int rawDamage = damage - target.defence;
                totalDamageDealt = rawDamage;
                
                cout << "Rolling." << endl;
                Sleep(1000);
                system("cls");
                cout << "Rolling.." << endl;
                Sleep(1000);
                system("cls");
                cout << "Rolling..." << endl;
                Sleep(1000);
                system("cls");
                
                if (totalDamageDealt <= 0) {
                	totalDamageDealt = 0; // Το κανουμε 0 ωστε να μην γινει αρνητικο και το monster γιατρευτει	
                	cout << name << " hits but the attack was completely blocked by defense! (0 damage)" << endl;
                }
				else{
					cout << name << " hits the " << target.type << " for " << damage << " damage!" << endl;
	                Sleep(1000);
	                system("cls");
	                cout << target.defence << " damage was blocked by the Monster's defence!" << endl;
	                
					target.hp -= totalDamageDealt;
					if (target.hp < 0){
	    				target.hp = 0;
					}
					
	                cout << "Total Damage: " << totalDamageDealt << " | Monster HP: " << target.hp << endl;
	                system("pause");
	                system("cls");	
				}
            }
            else{
            	cout << "Rolling." << endl;
                Sleep(1000);
                system("cls");
                cout << "Rolling.." << endl;
                Sleep(1000);
                system("cls");
                cout << "Rolling..." << endl;
                Sleep(1000);
                system("cls");
                
                cout << name << " misses " << target.type << "!" << endl;
                system("pause");
                system("cls");
            }
        }
        
void Hero::special_attack(int skillChoice, Monster &target){
	int hitRoll = rand() % 20 + 1;
	
	if (hitRoll < target.ac){
		system("cls");
		cout << "Rolling." << endl;
        Sleep(1000);
        system("cls");
        cout << "Rolling.." << endl;
        Sleep(1000);
        system("cls");
        cout << "Rolling..." << endl;
        Sleep(1000);
        system("cls");
		cout << name << " tried to use a Special Attack but missed!" << endl;
		system("pause");
		system("cls");
		return; // βαζουμε το return ετσι ωστε αν φτασει εδω μεσα το προγραμμα να κλεισει την συναρτηση. (το εχω μαθει απο το roblox LOL)
	}
	
	int damage = rand() % (weaponName.maxDamage - weaponName.minDamage + 1) + weaponName.minDamage; 
    int rawDamage = damage - target.defence; // oπως και στην κανονικη συναρτηση attack κανουμε το ιδιο για να βρουμε την ζημια
    int totalDamageDealt = 0;
	
	if (skillChoice == 1){
		system("cls");
		cout << "Rolling." << endl;
        Sleep(1000);
        system("cls");
        cout << "Rolling.." << endl;
        Sleep(1000);
        system("cls");
        cout << "Rolling..." << endl;
        Sleep(1000);
        system("cls");
        
		totalDamageDealt = rawDamage + 10;
		cout << name << " used Power Strike!" << endl;
		system("pause");
		system("cls");
		cout << name << " hits the " << target.type << " for " << damage << " damage + 10 damage from Power Strike!" << endl;	
		Sleep(1000);
	    system("cls");
	    cout << target.defence << " damage was blocked by the Monster's defence!" << endl;
	    
		target.hp -= totalDamageDealt;
		if (target.hp < 0){
	    	target.hp = 0;
		}
		
	    cout << "Total Damage: " << totalDamageDealt << " | Monster HP: " << target.hp << endl;
	    system("pause");
	    system("cls");	
	} 
	else if (skillChoice == 2){
		system("cls");
		int secondDamage = rand() % (weaponName.maxDamage - weaponName.minDamage + 1) + weaponName.minDamage; // βρισκουμε με τον ιδιο τροπο με πριν την ζημια του 2ου χτυπηματος
    	totalDamageDealt = (rawDamage + secondDamage );
		
		cout << "Rolling." << endl;
        Sleep(1000);
        system("cls");
        cout << "Rolling.." << endl;
        Sleep(1000);
        system("cls");
        cout << "Rolling..." << endl;
        Sleep(1000);
        system("cls");
		
		cout << name << " used Double Slash!" << endl;
		system("pause");
		system("cls");
		
		cout << name << " hits the " << target.type << " for " << damage << " damage!" << endl;	
		Sleep(1000);
	    system("cls");
	    cout << name << " hits the " << target.type << " for " << secondDamage << " damage!" << endl;	
	    Sleep(1000);
	    system("cls");
	    cout << target.defence << " damage was blocked by the Monster's defence!" << endl;
	    
	    target.hp -= totalDamageDealt;
	    if (target.hp < 0){
	    	target.hp = 0;
		}
	
	    cout << "Total Damage: " << totalDamageDealt << " | Monster HP: " << target.hp << endl;
	    system("pause");
	    system("cls");
	}
	else if (skillChoice == 3){
		system("cls");
		totalDamageDealt = damage;
		
		cout << "Rolling." << endl;
        Sleep(1000);
        system("cls");
        cout << "Rolling.." << endl;
        Sleep(1000);
        system("cls");
        cout << "Rolling..." << endl;
        Sleep(1000);
        system("cls");
        
        cout << name << " used Piercing Thrust!" << endl;
		system("pause");
		system("cls");
		
		cout << name << " hits the " << target.type << " for " << damage << " damage!" << endl;	
		Sleep(1000);
	    system("cls");
	    cout << name << " ignores the " << target.type << " defence!" << endl;
	    
	    target.hp -= totalDamageDealt;
	    if (target.hp < 0){
	    	target.hp = 0;
		}
	    
	    cout << "Total Damage: " << totalDamageDealt << " | Monster HP: " << target.hp << endl;
	    system("pause");
	    system("cls");
	}
	else if (skillChoice == 4){
		system("cls");
		totalDamageDealt = rawDamage * 1.75;
		
		cout << "Rolling." << endl;
        Sleep(1000);
        system("cls");
        cout << "Rolling.." << endl;
        Sleep(1000);
        system("cls");
        cout << "Rolling..." << endl;
        Sleep(1000);
        system("cls");
        
        cout << name << " used Critical Blow!" << endl;
		system("pause");
		system("cls");
		
		cout << name << " hits the " << target.type << " for " << damage << " damage * 1.75 from Critical Blow!" << endl;	
		Sleep(1000);
	    system("cls");
	    cout << target.defence << " damage was blocked by the Monster's defence!" << endl;
	    
	    target.hp -= totalDamageDealt;
	    if (target.hp < 0){
	    	target.hp = 0;
		}
	
	    cout << "Total Damage: " << totalDamageDealt << " | Monster HP: " << target.hp << endl;
	    system("pause");
	    system("cls");
	}
}

int main() {
    // Λογικη του random
    srand(time(0));
    
    int answer;
    do{
	    // Οριζει ο παιτκης το ονομα του Ηρωα και του αντιστοιχιζεται ενα τυχαιο οπλο.
	    cout << "----- Welcome to the Hero vs Monsters RPG! -----" << endl;
	    cout << "------------------------------------------------" << endl;
	    Sleep(1000);
	    cout << "Enter your hero's name: ";
	    
	    string heroName;
	    cin >> heroName;
	    
	    weapon randomWeapon = weaponPool[rand() % 8];
	    Hero hero(heroName, randomWeapon); // Καλουμε στην main συναρτηση τον Ηρωα
	    cout << "\nYour hero, " << hero.name << ", has been equipped with a " << hero.weaponName.name << "!" << endl;
	   
	    Monster monster; // Καλουμε στην main συναρτηση το Monster
	    system("pause");
		system("cls");
	
		bool monsterSeen = 0; // οριζω αυτη τη λογικη μεταβλητη ετσι ωστε οταν ο παικτης δει οτι ηρθε ενα τερας μια φορα να μη το ξανα παιζει στη λουπα
	    while (hero.hp > 0){
	        // Λογικη του παιχνιδιου
	        
	        if (!monsterSeen){
	        	cout << "A wild " << monster.type << " appears with a " << monster.weaponName.name << "!" << endl;
	        	system("pause");
				monsterSeen = 1;
			}
			
			system("cls");
	        cout << "Hero HP: " << hero.hp << " | Monster HP: " << monster.hp << "\n" << endl;
	        int choice;
	       do{
	       	cout << "What will you do?" << endl;
	        cout << "1. Simple Attack." << endl;
	        cout << "2. Special Attack." << endl;
	        cout << "3. Heal." << endl;
	       	cout << "Choose Action: ";
	        cin >> choice; // Περνουμε την κινηση του παικτη και ελεγχουμε:
	        if (choice < 1 || choice > 3){
			   	system("cls");
			    cout << "Please select a valid option!";
			    Sleep(1500);
			    system("cls");
			}
		   }while(choice < 1 || choice > 3);
	        
	        if (choice == 1){
	        	hero.attack(monster);
	        	if (monster.hp <= 0){
	        		hero.kills += 1;
	        		cout << monster.type << " has been defeated! " << hero.name << " won the battle." << endl;
	        		cout << "Hero HP: " << hero.hp << " | Kills: " << hero.kills << endl;
	        		
	        		system("pause");
	        		system("cls");
	        		
	        		cout << "You hear something approaching." << endl;
	        		Sleep(2000);
	        		system("cls");
	        		cout << "You hear something approaching.." << endl;
	        		system("pause");
					system("cls");
	        		
	        		monsterSeen = 0;
	        		monster = Monster(); // Ξανα ζωντανευουμε ενα Monster ωστε να παιξει παλι η λουπα
	        		
	        		if (hero.kills > 0 && hero.kills % 5 == 0){ // βαζω ενα boss ανα 5 kills !!!
	        			monster.type = "BOSS: The Fallen Dragon";
	        			monster.hp = 200;
	        			monster.ac = 14;
	        			monster.defence = 8;
	        			
	        			monster.weaponName.name = "The Corrupted GreatAxe"; // του δινουμε νεο οπλο εκτους του πινακα struct
	        			monster.weaponName.minDamage = 20; // του δινουμε νεα min και max ζημια
	        			monster.weaponName.maxDamage = 33;
	        			
	        			cout << "\nWARNING! The ground shakes... A Legendary Boss has appeared! ??" << endl;
					    system("pause");
					    system("cls");
					}
	        	}
	        	else{
	        		int monsterCPU = rand() % 10 + 1; // βαζουμε μια μεταβλητη να βρισκει αριθμους απο το 1 ως το 10 για να συνεχισουμε αντιστοιχα στην επιθεση του monster
	        		if (monsterCPU <= 7){
	        			monster.attack(hero);
					}
					else{
						int randomSkill = rand() % 4 + 1; // αφου μπηκε εκει ο κωδικας σημαινει οτι θα κανει σπεσιαλ ατακ το monster βρισκουμε ποιο σπεσιαλ ατακ θα κανει με αυτο το random
						monster.special_attack(randomSkill, hero);
					}
				}
			}
			else if (choice == 2){
				int skill;
				system("cls");
				do{
					cout << "Special Attacks:" << endl;
			       	cout << "1. Power Strike." << endl;
			       	cout << "2. Double Slash." << endl;
			       	cout << "3. Piercing Thrust." << endl;
			       	cout << "4. Critical Blow." << endl;
			       	cout << "Choose Action: ";
			       	cin >> skill;	
			       	
			       	if (skill < 1 || skill > 4){
			       		system("cls");
			       		cout << "Please select a valid option!";
			       		Sleep(1500);
			       		system("cls");
					   }
				}while(skill < 1 || skill > 4);
		        
				hero.special_attack(skill , monster);
				
				if (monster.hp <= 0){
	        		hero.kills += 1;
	        		cout << monster.type << " has been defeated! " << hero.name << " won the battle." << endl;
	        		cout << "Hero HP: " << hero.hp << " | Kills: " << hero.kills << endl;
	        		
	        		system("pause");
	        		system("cls");
	        		
	        		cout << "You hear something approaching." << endl;
	        		Sleep(2000);
	        		system("cls");
	        		cout << "You hear something approaching.." << endl;
	        		system("pause");
					system("cls");
	        		
	        		monsterSeen = 0;
	        		monster = Monster(); // Ξανα ζωντανευουμε ενα Monster ωστε να παιξει παλι η λουπα
	        		if (hero.kills > 0 && hero.kills % 5 == 0){ // βαζω ενα boss ανα 5 kills !!!
	        			monster.type = "BOSS: The Fallen Dragon";
	        			monster.hp = 200;
	        			monster.ac = 14;
	        			monster.defence = 8;
	        			
	        			monster.weaponName.name = "The Corrupted GreatAxe"; // του δινουμε νεο οπλο εκτους του πινακα struct
	        			monster.weaponName.minDamage = 20; // του δινουμε νεα min και max ζημια
	        			monster.weaponName.maxDamage = 33;
	        			
	        			cout << "WARNING! The ground shakes... A Legendary Boss has appeared! ??" << endl;
					    system("pause");
					    system("cls");
					}
	        	}
				else{ // OTI ακριβως καναμε και πανω
	        		int monsterCPU = rand() % 10 + 1; 
	        		if (monsterCPU <= 7){
	        			monster.attack(hero);
					}
					else{
						int randomSkill = rand() % 4 + 1;
						monster.special_attack(randomSkill, hero);
					}
				}  
			}
			else if(choice == 3){
				system("cls");
				
				int healAmount = rand() % 16 + 15; // υπολογιζουμε το heal του παικτη απο 15 ως 30 hp
				hero.hp += healAmount;
				
				if(hero.hp > 100) {
					hero.hp = 100; // ελεγχος για να μη ξεφευγει το heal
				}
				
				cout << hero.name << " used a Healing Potion and recovered " << healAmount << " HP!" << endl;
				cout << "Hero HP: " << hero.hp << endl;
				system("pause");
				system("cls");
				
				int monsterCPU = rand() % 10 + 1;
			    if (monsterCPU <= 7) {
			        monster.attack(hero);
			    } 
				else{
			        int randomSkill = rand() % 4 + 1;
			        monster.special_attack(randomSkill, hero);
			    }
			}
	    }
	    
	    system("cls"); // Game over screen
	    cout << hero.name << " died... GAME OVER!" << endl;
	    cout << "Total Kills: " << hero.kills << endl;
	    cout << "\nDo you want to play again?" << endl;
	    cout << "1. Yes\n2. No" << endl;
	    cout << "Choice: ";
	    cin >> answer;
	    system("cls");
	    
    }while (answer == 1);
    
    cout << "Thank you for playing!" << endl; // χαιρεταμε τον χρηστη αφου επελεξε να κλεισει το παιχνιδι!
    return 0;
}
