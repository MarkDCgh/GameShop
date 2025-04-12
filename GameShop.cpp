#include "GameShop.h"

GameShop user; //GLOBAL OBJECT

// MAKE THE PROGRAM TO PAUSE ALLOWING USER READING
static void Pause() {
	std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
	std::cout << "\n\n";
	while (true)
		if (_kbhit()) {
			char ch = _getch();
			break;
		}
	std::cin.clear(); 
}

int main() {
	bool running = true; // THE MENU WILL RESTART IF THIS VARIABLE IS TRUE

	user.FirstRun(); // HANDLE THE ABSOLUTE FIRST RUN OF USER
	user.Set(); // INITIALIZE VARIABLES TO SAVED VALUES FROM THE LAST RUN OF THE PROGRAM

	while (running) 
		Menu(running); 

	user.Save();  // SAVE THE NEW VALUES FOR THE NEXT PROGRAM RUN
}

static void Menu(bool& running) {
	unsigned short choice = 0; 

	// USER INPUT FOR CHOICE 
	while (choice < 1 || choice > 5) {
		system("cls");

		DisplayMenu();

		if (std::cin >> choice)
			continue;
		
		//HANDLE THE INPUT ERROR
		std::cout << "Input Error"; 
		std::cin.clear();
		std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
	}

	switch (choice) {
	case 1: 
		user.Sell(); 
		break; 
	case 2: 
		user.SupplyDeposit(); 
		break; 
	case 3: 
		user.PayEmployee(); 
		break; 
	case 4: 
		user.CheckSituation(); 
		break; 
	case 5: 
		running = false; // THE MENU LOOP IN MAIN WILL BREAK
		break;
	}
}

static void DisplayMenu() {
	std::cout << "___________\n GAME SHOP\n\n";
	std::cout << "1. Sell\n2. Supply Deposit\n3. Pay Employee\n";
	std::cout << "4. Check Situation\n5. Exit\n\n: "; 
}

// CLASS FUNCTIONS
void GameShop::FirstRun() {
	std::string line;

	if (std::filesystem::exists("FirstRun.txt"))
		return; 

	std::fstream firstRunFile("FirstRun.txt");

	if (!(firstRunFile.is_open())) {
		std::cout << "Access failed!";
		Pause(); 
		return;
	}

	firstRunFile.close(); 

	firstRunFile.open("AllGamesShopPrice.txt");

	if (!(firstRunFile.is_open())) {
		std::cout << "Access failed!";
		Pause();
		return;
	}

	// WRITES THE TEXT FOR ALLGAMESSHOPPRICE.TXT, IT CONTAINS FIXED SHOP PRICES FOR GAMES
	firstRunFile << "50\n30\n70\n70\n30\n40\n35\n50\n70\n35\n32\n47\n36\n69\n30\n23\n70\n58\n72\n"; 
	firstRunFile << "47\n62\n41\n45\n31\n32\n68\n42\n48\n71\n23\n42\n80\n23\n51\n26\n25\n60";

	firstRunFile.close(); 

	firstRunFile.open("MarketGamesTitle.txt");

	if (!(firstRunFile.is_open())) {
		std::cout << "Access failed!";
		Pause();
		return;
	}

	//WRITES THE TEXT FOR MARKETGAMESTITLE.TXT, IT CONTAINS FIXED TITLES OF ALL POSSIBLE GAMES
	line = AllTitleGames(); // TAKES ALL THE GAMES
	firstRunFile << line; 

	firstRunFile.close(); 

	firstRunFile.open("Money.txt");

	if (!(firstRunFile.is_open())) {
		std::cout << "Access failed!";
		Pause();
		return;
	}
	
	firstRunFile << "200"; // THE "GAME" STARTS WITH 200 EUROS

	firstRunFile.close();

	firstRunFile.open("EmployeeTurns.txt");

	if (!(firstRunFile.is_open())) {
		std::cout << "Access failed!";
		Pause();
		return;
	}

	firstRunFile << "0"; // THE "GAME" STARTS WITH 0 TURNS

	firstRunFile.close(); 
}

void GameShop::Set() {
	user.SetGames(); 
	user.SetMoney(); 
	user.SetEmployeeTurns(); 
	user.SetMarketGames(); 
	user.SetAllGamesShopPrice(); 
}

void GameShop::SetGames() {
	std::ifstream depositFile("TitlesDeposit.txt");
	std::string line;
	unsigned int i = 0;

	if (!(depositFile.is_open())) {
		std::cout << "Access failed!";
		Pause(); 
		return;
	}

	// TAKES THE LINE (TITLE GAME) FROM FILE, THEN PUSH THE LINE IN THE GAMESTITLE VECTOR
	for (int i = 0; std::getline(depositFile, line); i++)
		user.gamesTitle.push_back(line);

	depositFile.close();

	depositFile.open("PriceDeposit.txt");

	if (!(depositFile.is_open())) {
		std::cout << "Access failed!";
		Pause();
		return;
	}

	// TAKES THE LINE (PRICE GAME) FROM FILE, THEN PUSH THE LINE IN THE GAMESPRICE VECTOR
	for (int i = 0; depositFile >> line; i++)
		user.gamesPrice.push_back(std::stod(line)); // CONVERT LINE STRING INTO DOUBLE

	depositFile.close();
}

void GameShop::SetMoney() {
	std::ifstream moneyFile("Money.txt");
	std::string line; 

	moneyFile >> line; 

	user.money = std::stod(line); 

	moneyFile.close(); 
}

void GameShop::SetEmployeeTurns() {
	std::ifstream turnsFile("EmployeeTurns.txt");
	std::string line;

	turnsFile >> line;

	user.employeeTurns = std::stoi(line);

	turnsFile.close();
}

void GameShop::SetMarketGames() {
	std::ifstream titleFile("MarketGamesTitle.txt");
	std::string line; 

	RandMarketGamesPrice(); // SET MARKET PRICE VECTOR

	if (!(titleFile.is_open())) {
		std::cout << "Access failed!";
		Pause();
		return;
	}

	// SET MARKET TITLE VECTOR
	while (std::getline(titleFile, line))
		marketGamesTitle.push_back(line);

	marketGamesTitle.pop_back(); // FOR SOME REASON AN EMPTY STRING IS ADDED TO THE VECTOR 
	titleFile.close();
}

void GameShop::RandMarketGamesPrice() {
	std::ifstream shopFile("AllGamesShopPrice.txt");
	std::vector <double> tempVector; 
	std::string line; 
	int changeRate = 10; // MAXIMUM EUROS THE MARKET FILE PRICES CAN CHANGE FROM SHOP FILE

	if (!(shopFile.is_open())) {
		std::cout << "Access failed!";
		Pause();
		return;
	}

	while (shopFile >> line)
		tempVector.push_back(std::stod(line)); // MEMORIZE PRICES IN VECTOR

	for (double n : tempVector) {
		int valToAdd = rand() % changeRate * 2;
		n -= changeRate;
		marketGamesPrice.push_back(n + valToAdd);
	}

	shopFile.close(); 
}

void GameShop::SetAllGamesShopPrice() {
	std::ifstream shopPriceFile("AllGamesShopPrice.txt");
	std::string line;

	if (!(shopPriceFile.is_open())) {
		std::cout << "Access failed!";
		Pause();
		return;
	}

	while (shopPriceFile >> line)
		allGamesShopPrice.push_back(std::stod(line));

	shopPriceFile.close();
}

void GameShop::Sell() {
	int choice;
	double moneySell = 0;

	if (user.employeeTurns == 0) {
		std::cout << "Pagah il dipendente prima";
		Pause(); 
		return; 
	}

	while (true) {
		system("cls");

		DisplayGames();

		choice = user.ChoiceMenu(); 
		if (choice >= 0 && choice < gamesTitle.size()) // IF CHOICE IS GREATER WILL CAUSE BUG IN DELETEGAME()
			moneySell = user.DeleteGame(choice);
		else if (choice == -1) // EXIT
			break;
		else
			continue; 

		user.money += moneySell; // ADD MONEY TO SHOP

		employeeTurns--; 

		std::cout << moneySell << " Euro Added!"; 

		Pause(); 
	}
}

void GameShop::SupplyDeposit() {
	int choice = 0; 

	while (true) {
		system("cls"); 

		user.DisplayMarketGames();

		choice = user.ChoiceMenu();
		if (choice == -1) // EXIT
			break;
		else if (!(choice >= 0 && choice < marketGamesPrice.size()))
			continue; 

		// CHECK IF USER HAS ENOUGH MONEY TO PAY
		if (money < marketGamesPrice.at(choice)) {
			std::cout << "You don't have enough money";
			Pause(); 
			continue; 
		}

		gamesTitle.push_back(marketGamesTitle.at(choice)); // APPEND THE PURCHASED TITLE
		gamesPrice.push_back(allGamesShopPrice.at(choice)); // APPEND THE PRICE OF THE TITLE
		money -= marketGamesPrice.at(choice); // PAY THE GAME PURCHASED FOR DEPOSIT

		std::cout << "You purchased " << gamesTitle.at(gamesTitle.size() - 1);
		std::cout << " for " << marketGamesPrice.at(choice) << "$\n";
		Pause();
	}
}

void GameShop::PayEmployee() {
	int salary = 50; // COST OF ESMPLOYEE
	int turns = 20; // TURNS OBTAINED BY PAYING EMPLOYEE
	unsigned int choice = 0;

	while (true) {
		system("cls");

		std::cout << "Are you sure to pay the employee?\n1. Yes\n2. No\n\n: "; 
		std::cin >> choice; 

		if (choice == 1 || choice == 2)
			break; 

		std::cin.clear(); 
		std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
	}
	
	if (choice == 2)
		return; 

	money -= salary; 
	employeeTurns += turns; 

	std::cout << turns << " Turns Added!";

	Pause(); 
}

void GameShop::CheckSituation() {
	system("cls"); 

	std::cout << "__Deposit Games__\n"; 
	user.DisplayGames(); 

	std::cout << "\n__Shop Money__\n" << money << "$";

	std::cout << "\n\n__Employee Turns__\n" << employeeTurns << " Sellings Left\n";

	Pause(); 
}

int GameShop::ChoiceMenu() {
	int choice; 

	std::cout << "\nChoice the Game (-1 to Exit)\n\n: ";

	if (std::cin >> choice)
		return choice; 

	std::cin.clear(); 
	std::cin.ignore (std::numeric_limits <std::streamsize>::max(), '\n');
	return -2; // WON'T EXIT BUT WILL LOOP AGAIN
}

void GameShop::DisplayGames() {
	for (int i = 0; i < user.gamesTitle.size(); i++) {
		std::cout << i << ". " << user.gamesTitle.at(i) << " - ";
		std::cout << user.gamesPrice.at(i) << "\n";
	}
}

double GameShop::DeleteGame(int gameIndex) {
	// SWAP ELEMENT TO REMOVE WITH LAST ELEMENT, THEN REMOVE LAST ELEMENT
	for (int i = 0; i < gamesTitle.size(); i++) {
		if (i == gameIndex) {
			std::swap(gamesTitle.at(i), gamesTitle.at(gamesTitle.size() - 1)); 
			break;
		}
	}
	gamesTitle.pop_back(); 

	for (int i = 0; i < gamesPrice.size(); i++) {
		if (i == gameIndex) {
			std::swap(gamesPrice.at(i), gamesPrice.at(gamesPrice.size() - 1));
			break;
		}
	}
	double price = gamesPrice.at(gamesPrice.size() - 1);
	gamesPrice.pop_back();

	return price; // TO ADD MONEY IN SELL() 
}

void GameShop::DisplayMarketGames() {
	for (int i = 0; i < marketGamesTitle.size(); i++) {
		std::cout << i << ". " << marketGamesTitle.at(i); 
		std::cout << " - " << marketGamesPrice.at(i) << "\n"; 
	}
}

std::string GameShop::AllTitleGames() {
	std::string line; 
	line.append("Super Mario 3D World\n"); 
	line.append("Persona 5 Royale\n"); 
	line.append("Elden Ring\n");
	line.append("Luigi's Mansion 2\n");
	line.append("Sekiro\n");
	line.append("GTA IV\n");
	line.append("Mario Kart 8 Deluxe\n");
	line.append("God of War 4\n");
	line.append("The Legend of Zelda : Tears of the Kingdom\n");
	line.append("Dark Souls 3\n");
	line.append("Splatoon 2\n");
	line.append("The Witcher 3\n");
	line.append("Super Mario 3D Land\n");
	line.append("Outer Wilds\n");
	line.append("Baldur's Gate 3\n");
	line.append("The Last of Us\n");
	line.append("Diablo IV\n");
	line.append("Cuphead\n");
	line.append("Resident Evil 7\n");
	line.append("Super Mario Bros : Wonder\n");
	line.append("The Legend of Zelda : Breath of the Wild\n");
	line.append("Silent Hill 2 Remake\n");
	line.append("The Last Guardian\n");
	line.append("Dark Souls Remastered\n");
	line.append("GTA V\n");
	line.append("Uncharted 4\n");
	line.append("Animal Crossing : New Horizons\n");
	line.append("BioShock\n");
	line.append("Bloodborne\n");
	line.append("Super Mario Maker 2\n");
	line.append("Skyrim\n");
	line.append("Red Dead Redemption 2\n");
	line.append("Resident Evil 4 Remake\n");
	line.append("Super Mario Odissey\n");
	line.append("Doom Eternal\n");
	line.append("Super Smash Bros : Ultimate\n");

	return line;
}

void GameShop::Save() {
	SaveGames(); 
	SaveMoney(); 
	SaveEmployeeTurns(); 
}

void GameShop::SaveGames() {
	std::ofstream gamesFile("TitlesDeposit.txt", std::ios::out);
	std::string line;

	if (!(gamesFile.is_open())) {
		std::cout << "Access failed!";
		Pause();
		return;
	}

	for (int i = 0; i < gamesTitle.size(); i++) {
		gamesFile << gamesTitle.at(i) << "\n";
	}

	gamesFile.close();

	gamesFile.open("PriceDeposit.txt", std::ios::out);

	if (!(gamesFile.is_open())) {
		std::cout << "Access failed!";
		Pause();
		return;
	}

	for (int i = 0; i < gamesPrice.size(); i++) {
		line = std::to_string(gamesPrice.at(i)); // CONVERTS DOUBLE ELEMENT INTO STRING
		gamesFile << line << "\n";
	}

	gamesFile.close();
}

void GameShop::SaveMoney() {
	std::ofstream moneyFile("Money.txt", std::ios::out);

	if (!(moneyFile.is_open())) {
		std::cout << "Access failed!";
		Pause();
		return;
	}

	moneyFile << std::to_string(money);

	moneyFile.close();
}

void GameShop::SaveEmployeeTurns() {
	std::ofstream turnsFile("EmployeeTurns.txt", std::ios::out);

	if (!(turnsFile.is_open())) {
		std::cout << "Access failed!";
		Pause();
		return;
	}

	turnsFile << std::to_string(employeeTurns);

	turnsFile.close();
}


// CLASSE: GAMESHOP
// OGGETTI: USER
// ATTIVITA: 
	// VENDERE ROBA (-1 GIOCO,+N SOLDI) 
	// RIFORNIRE DEPOSITO PER IL NEGOZIO (+GIOCO,-N SOLDI) 
		// CI SARA UN ALLGAMES SHOP PRICE .TXT CHE INDICHERA I PREZZI DEL NEGOZIO DI TUTTI I GIOCHI POSSIBILI
		// CI SARA UNO MARKETGAMES PRICE .TXT CHE INDICHERA I PREZZI DI TUTTI I GIOCHI POSSIBILI ACQUISTABILI 
		// QUESTI ULTIMI CAMBIERANNO AD OGNI RUN IN BASE AD UN RANDOMIZER IN MODO DA ESSERE PIU O MENO 
		// ALTI RISPETTO AI PREZZI A CUI LI VENDE IL NEGOZIO, COSI L USER COMPRERA SOLAMENTE CIO 
		// CHE CONVIENE, SIMULA IL MERCATO
	// PAGARE IL DIPENDENTE (DOPO N VENDITE DI ROBA, -SOLDI +N VENDITE PER DIPENDENTE) 
		// SE NON SI PAGA IL DIPENDENTE, VENDERE ROBA NON SARA DISPONIBILE 
	// LEGGERE TUTTI I VIDEOGIOCHI DEL DEPOSITO , LEGGERE QUANTI SOLDI SI HA, LEGGERE LE VENDITE RIMASTE DEL DIPENDENTE 
// OBIETTIVO: FARE PIU SOLDI POSSIBILI
// AD OGNI RUN, ALL INIZIO SI SETTANO LE VARIABILI DAI .TXT FILE (LOADING GAME), SET() FUNCTION
// ALLA FINE SI SALVANO I NUOVI VALORI DELLE VARIABILI NEI .TXT FILE (SAVE GAME) 
