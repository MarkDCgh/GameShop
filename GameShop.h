#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <string>
#include <ios>
#include <vector>
#include <conio.h>

static void Menu(bool&);
static void DisplayMenu();
static void Pause(); 

class GameShop {
private:
	unsigned int employeeTurns = 0; // SELLINGS LEFT, IF 0 CAN'T SELL
	double money = 0; // MONEY'S SHOP
	std::vector <std::string> gamesTitle; // GAME TITLES IN DEPOSIT
	std::vector <std::string> marketGamesTitle; // GAME TITLES OF MARKET
	std::vector <double> gamesPrice; // GAME PRICES IN DEPOSIT
	std::vector <double> marketGamesPrice;  // GAME PRICES OF MARKET, THESE WILL CHANGE EACH RUN
	std::vector <double> allGamesShopPrice; // SHOP PRICES FOR ALL GAMES, REMAINS CONSTANT

public:
	void FirstRun(); // SET THE TXT FILES FOR FIRST RUN

	void Set(); // CALL THE 5 FUNCTIONS BELOW
	void SetGames(); // SET THE 2 GAMES VECTORS
	void SetMoney(); // SET THE VARIABLE MONEY 
	void SetEmployeeTurns(); // SET THE VARIABLE EMPLOYEETURNS 
	void SetMarketGames(); // SET THE TWO MARKET VECTORS
	void SetAllGamesShopPrice(); // SET THE CONSTANT PRICES OF SHOP FOR GAMES

	void RandMarketGamesPrice(); // RANDOMIZE THE PRICE VECTOR IN SETMARKETGAMES()

	void Sell(); // SELL VIDEOGAMES IN DEPOSIT
	void SupplyDeposit(); // UPGRADE DEPOSIT (VECTORS) 
	void PayEmployee(); // ADD EMPLOYEE TURNS VARIABLE
	void CheckSituation(); // DISPLAY ALL PRIVATE VARIABLES

	int ChoiceMenu(); // LOGIC HELPER OF SELL(), SUPPLYDEPOSIT()
	void DisplayGames(); // DISPLAY GAMES VECTORS ON TERMINAL
	double DeleteGame(int); // DELETE A GAME FROM SHOP VECTORS
	void DisplayMarketGames(); // DISPLAYS THE TWO MARKET VECTORS 
	std::string AllTitleGames(); // RETURN A STRING WITH ALL THE TITLES
	
	void Save(); // CALL THE 3 FUNCTIONS BELOW, UPGRADES THE .TXT FILES TO SAVE NEW VARIABLES VALUES
	void SaveGames();
	void SaveMoney();
	void SaveEmployeeTurns();
};

