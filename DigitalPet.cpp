/*
* @Author: Õ½ÂÔ½ÌÊÚ
* @Date:   2025-06-08 22:35:12
* @Last Modified by:   Wang Ziyan
* @Last Modified time: 2025-07-05 20:39:38
*/
#include<windows.h>
#include<time.h>
#include<cstdlib>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#include<queue>
#include "basicfunc.h"
#include "cooking.h"
#include "event_print.h"

using namespace std;

int days = 1; //ÌìÊý
bool died = false;


int turns = 1; //Ã¿Ò»ÌìÓÐ8´Î²Ù×÷»ú»á
//×÷±×Âë±äÁ¿
string cheating;
const bool cheatable = true;
int Mopluse;
bool Bband = false; //ÊÇ·ñÒÑ¾­Íê³ÉÁËËæ»úÊÂ¼þ4


//Ëæ»úÊÂ¼þ¶þ±äÁ¿£º
bool cheat = false;
bool loser = false;
bool invest = false; //Ëæ»úÊÂ¼þ¶þµÄ±äÁ¿£¬ÊÇ·ñÍ¶×Ê
int Iinvest;//Í¶×ÊµÄ½ð¶î
int IINVEST;
int Dinvest;//Í¶×ÊµÈ´ýµÄÌìÊý
float Einvest;//Í¶×ÊµÄÊÕÒæÂÊ
//Ëæ»úÊÂ¼þÈý±äÁ¿
const int price_mouse = 90, price_slipper = 20, price_heartsaver = 10000, price_lone = 10;

//µÀ¾ß-¼Û¸ñ
const int price_pbutter = 35, price_mbutter = 50;

//Åëâ¿±äÁ¿-¼Û¸ñ
const int price_sug = 8, price_sod = 9, price_wat = 0, price_flo = 6;
//Åëâ¿±äÁ¿-ÓµÓÐ
long long sug;//ÌÇ
long long sul;//ÑÎ
long long sod;//ËÕ´ò
long long wat;//Ë®
long long flo;//Ãæ·Û
//Åëâ¿±äÁ¿-¼ÓÈë
long long Isug;//ÌÇ
long long Isul;//ÑÎ
long long Isod;//ËÕ´ò
long long Iwat;//Ë®
long long Iflo;//Ãæ·Û

//Åëâ¿±äÁ¿-´æ´¢
int Cid = 0; //ÓÃÓÚ¼ÇÂ¼ÏîÊý
vector<string> backpackmeal;//²ËÆ·Ãû³Æ
vector<int> backpackcalr;//²ËÆ·¶ÔÓ¦µÄÈÈÁ¿
vector<int> backpackspend;//²ËÆ·¶ÔÓ¦µÄÖÆ×÷³É±¾£¬ÔÚÖ®ºóµÄ½øÒ»²½¸üÐÂÖÐÊ¹ÓÃ
vector<int> backpackall;//²ËÆ·¶ÔÓ¦µÄ×ÜÁ¿
vector<float> backpackeffect;//²ËÆ·Ð§¹û
int Crow;//ÓÃÓÚ½øÐÐÑ­»·
int CTP;//ÓÃÓÚ½øÐÐÑ¡Ôñ

int cook(long long Psug, long long Psul, long long Psod, long long Pwat, long long Pflo, int cs = 0) { //±äÁ¿cs£ºº¯ÊýµÄÀàÐÍ
	Msug = Psug; Msul = Psul; Msod = Psod; Mwat = Pwat; Mflo = Pflo;
	Camount = Psug + Psul + Psod + Pwat + Pflo;
	if (cs == 0) { //Åëâ¿
		if (Psug == 0 && Psul == 0 && Psod == 0 && Pwat == 0 && Pflo == 0) {
			cout << "After precisely controlling the invisible fire, consistly modifying the temperature of the non-existent frying pan, and the combination of the imaginary delicate seasonings, you successfully made a dish of...";
			Ncook = air;
			return Ncook;
		} else {
			int Rcook = 1 + rand() % (3);
			if (Rcook == 1) {
				cout << "You throw a bunch of inorganic substance (except for the flour) into the pot. Few hours later, you find yourself very tasty. When cooking yourself, you find out that you have already cooked...";
			}
			if (Rcook == 2) {
				cout << "You carefully throw a bunch of materials into the pot, and cook them with strange approaches. A few minutes later, you find the turner very tasty. When trying to chew the turner, you find yourself successfully cooked...";
			}
			if (Rcook == 3) {
				cout << "After throwing a bunch of disgusting inorganic substance, you are chocked by the smoke for two whole hours, and you find yourself totally cooked. In the mean time, you successfully invented...";
			}
		}
	}
	else if (cs == 1) { //ÆÀ¶¨ÈÈÁ¿ £¨Ã¿¿ËÌÇº¬ÓÐ4µãÈÈÁ¿£»ºÍË®½»ÈÚµÄÃæ·Û³ÉÎªÃæºý£¬Ã¿¿Ëº¬ÓÐ2µãÈÈÁ¿£¬¸ÉÃæ·ÛÃ¿¿Ëº¬ÓÐ4µãÈÈÁ¿£©
		Mcalr = Psug * 4;
		if (Pwat > Pflo)Mcalr = Mcalr + Pflo * 2;
		else Mcalr = Mcalr + Pwat * 2 + (Pflo - Pwat) * 4;
		return Mcalr;
	}
}

bool Vacheve = false;
void notice() {
	cout << "\nPRESS 'Q' TO QUIT\nPRESS 'F' TO FEED YOUR PET\nPRESS 'I' TO INTERACT WITH YOUR PET\nPRESS 'C' TO CHECK YOUR PET'S STATUS\n";
	cout << "PRESS 'S' TO CLEAR THE SCREEN\nPRESS 'M' TO [PURCHASE], [APPLY FOR LOAN] OR [COOK]\nPRESS 'B' TO CHECK THE [COOKING INGREDIENT] YOU ALREADY HAD\n";
	cout << "PRESS 'O' TO CHECK THE DISHES YOU ALREADY COOKED\nPRESS 'X' TO RESET THE THEME COLOR\nPRESS '?' TO CHECK THE INSTRUCTIONS\n";
	if (invest == true) {
		cout << "PRESS 'V' TO CHECK THE [STATUS OF INVESTMENT]\n";
		Vacheve = true;
	}
	cout << "There are 8 times to press the key.\nYou have " << 8 + 1 - turns << " times left\n";
}

//Ç°Ê®Ãûµ¥º¯Êý
fstream get_save;//¶ÁÈ¡
int list_id;//Ç°Ê®Ãûµ¥µÄid
int list_row;//½øÐÐÑ­»·
void list_read() {//¶ÁÈ¡
	get_save.open("top10\\Lid.txt");
	get_save >> list_id; //¶ÁÈ¡list_id
	get_save.close();
}

void list_write() {//Ð´Èë
	get_save.open("top10\\Lid.txt");
	get_save << list_id; //Ð´Èëlist_id
	get_save.close();
}

/*void list_queue() {

}*/

//Åëâ¿º¯Êý£¨ÓÉÅëâ¿Í·ÎÄ¼þ¶øÀ´µÄ·­ÒëÆ÷£©
void Cpushback(string bloodyname, int bloodycalr, int bloodyspend, int bloodyall, float bloodyeffect) {//´æ´¢
	backpackmeal.push_back(bloodyname);
	backpackcalr.push_back(bloodycalr);
	backpackspend.push_back(bloodyspend);
	backpackall.push_back(bloodyall);
	backpackeffect.push_back(bloodyeffect);
	Cid++;
}

void Cclean() {//Çå¿Õ
	Crow = 1;
	while (1) {
		if (Crow == Cid)break; //backpackmeal´Ó0¿ªÊ¼
		backpackmeal[Crow - 1] = "";
		Crow++;
	}
	Cid = 0;
}

void Cdrop(int IDI) {//³ýÈ¥ IDI=id of the dropped item
	backpackmeal[IDI] = "";
	Cid = Cid - 1;
	Crow = IDI;
	while (1) {
		if (Crow == Cid)break; //×¢Òâ£¬´Ë´¦CrowµÈÓÚCid£¬Ïàµ±ÓÚ°Ñ×îºóÒ»¸öÎïÆ·¸³ÖµÎª0
		backpackmeal[Crow] = backpackmeal[Crow + 1];
		backpackcalr[Crow] = backpackcalr[Crow + 1];
		backpackspend[Crow] = backpackspend[Crow + 1];
		backpackall[Crow] = backpackall[Crow];
		Crow++;
	}
}

void Cfour() {
	if (sug <= 0) {
		sug = 0;
	}
	if (sod <= 0) {
		sod = 0;
	}
	if (sul <= 0) {
		sul = 0;
	}
	if (wat <= 0) {
		wat = 0;
	}
	if (flo <= 0) {
		flo = 0;
	}
}

bool Jcook = false; //ÔÚÅëâ¿Ê±ÇÐ»»½çÃæÓÃµÄÒ»¸ö±äÁ¿¡­¡­
void Cincook() {
	colorc(blue);
	cout << "You have " << sug << " grams of sugar\nYou have " << sul << " grams of salt\nYou have " << sod << " grams of soda\nYou have " << wat << " milliliter of water (1000 millilitter max)\nYou have " << flo << " grams of flour\n";
	colorc(white);
	pause();
	cout << "Keep cooking? (Press [up button] to continue, press [down button] to quit this menu)\n";
	while (1) {
		key = getch();
		if (key == up) {
			Jcook = false;
			break;
		}
		if (key == down) {
			Jcook = true;
			break;
		}
	}
	if (Jcook == false) {
		while (1) {
			cout << "How much sugar do you want to put in? Input the number of grams:";
			cin >> Isug;
			if (Isug < 0 || Isug > sug)cout << "You don't have any!\n";
			else {
				sug = sug - Isug;
				break;
			}
		}
		while (1) {
			cout << "How much salt do you want to put in? Input the number of grams:";
			cin >> Isul;
			if (Isul < 0 || Isul > sul)cout << "You don't have any!\n";
			else {
				sul = sul - Isul;
				break;
			}
		}
		while (1) {
			cout << "How much sodium bicarbonate do you want to put in£¿ Input the number of grams:";
			cin >> Isod;
			if (Isod < 0 || Isod > sod)cout << "You don't have any!\n";
			else {
				sod = sod - Isod;
				break;
			}
		}
		while (1) {
			cout << "How much water do you want to put in£¿ Input the number of milliliter:";
			cin >> Iwat;
			if (Iwat < 0 || Iwat > wat)cout << "You don't have any!\n";
			else {
				wat = wat - Iwat;
				break;
			}
		}
		while (1) {
			cout << "How much flour do you want to put in£¿ Input the number of grams:";
			cin >> Iflo;
			if (Iflo < 0 || Iflo > flo)cout << "You don't have any!\n";
			else {
				flo = flo - Iflo;
				break;
			}
		}
		cook(Isug, Isul, Isod, Iwat, Iflo, ck);
		if (Isug == 0 && Isul == 0 && Isod == 0 && Iwat == 0 && Iflo == 0)cout << meal[cook(Isug, Isul, Isod, Iwat, Iflo, ck)] << "£¡\n";
		else {
			Meal = Tmeal[meal_tas()] + meal[meal_nam()];
			cout << Meal << "£¡\n";
			calr = cook(Isug, Isul, Isod, Iwat, Iflo, cr);
			cout << "The energy of this dish is " << calr << " calories!\n";
			Cpushback(Meal, calr, Isug * 8 + Isul * 13 + Isod * 9, meal_all(), meal_effect()); //ÑÎµÄ¼Û¸ñÊÇ6~21µÄËæ»úÊý£¬È¡ÖÐ¼äÖµ13.5µÄÕûÊý²¿·Ö13Ôª
		}
	} else {
		Jcook = false;
	}
	hyphen(4);
}

//Ëæ»úÊÂ¼þÃÇ
void r1() {		//Ëæ»úÊÂ¼þ1£º
	randomnum = r_events(3, 35, 0);		//´ø»Ø0~35Ôª
	if (randomnum != 0) {
		cout << "\n This day, you find that your pet disappered. Few hours later, your pet brings you back $" << randomnum << "!\nMoney increase!\n";
		money = money + randomnum;
		pause();
	}
}

void r2() {		//Ëæ»úÊÂ¼þ2£º³èÎïµÄ·çÏÕÍ¶×Ê
	your_pet();
	cout << "walks to you with a paper, which said:\nVENTURE INVESTMENT\nInvestor:" << name << "\nVoucher: You\nSignature:________\n";
	sure();
	while (1) {
		key = getch();
		if (key == 'H') {
			cout << "You sign your name.\n";
			invest = true;
			while (1) {
				cout << "Input the money you want to invest";
				money_have();
				cin >> Iinvest;
				if (!(Iinvest <= 0)) {
					if (!(Iinvest > money))break;
					else {
						cout << "You don't have that much of money! All you have is $ " << money << "!\n\n";
					}
				} else {
					if (Iinvest < 0) {
						cout << "Failed to invest, please reenter!\n\n";
					}
					else {
						cout << "You give up the investment when it is by a hair!\n";
						break;
					}
				}
			}
			if (Iinvest != 0) {
				cout << "You invest $ " << Iinvest << ".\n";
				if (Iinvest == money) {
					cout << "Your pet is very pleased when seeing you invested all your money.\n";
					hap_plus(2);
					sad_minus(3);
					hap += 2;
					sad -= 3;
				}
				money = money - Iinvest;
				IINVEST = Iinvest;
				Dinvest = r_events(3, 2, 1) + days;
				invest = true;
				break;
			} else {
				cout << "Your pet is looking at you as if you are a retard.\n";
				break;
				invest = false;
			}
		}
		else if (key == 'P') {
			cout << "Your pet is looking at you as if you are a retard.\n";
			break;
			invest = false;
		}
		cout << "\n\n";
	}
}

bool Phouse = false; //³èÎïÊÇ·ñÓÐ·¿×Ó
bool Pmouse = false; //ÊÇ·ñ¹ºÂòÁË³èÎïµÄÀÏÊó
int Pmouse_plus;//ÀÏÊ¦¸ø³èÎïÔö¼ÓµÄ¿ìÀÖÖµ£¨1-10Ëæ»úÊý£©
void r3() { //Ëæ»úÊÂ¼þ3£ºÍÆÏúÔ±
	cout << "Your pet runs out of the house.\nFew hours later, your pet " << name << " starts to knock on the door.\n";
	cout << "Open the door?\n";
	sure();
	while (1) {
		key = getch();
		if (key == 'H') {
			cout << "You open the door, just to realize that";
			randomnum = r_events(114514, 5, 1);
			if (randomnum == 2) {
				cout << "your pet has already eated the window and entered the house.\n";
				poo = true;
			} else {
				cout << "your pet has already entered the house.\n";
			}
			break;
		}
		else if (key == 'P') {

			cout << "You pretend that your can't hear " << name << "'s knocking, so your pet eats up the door!\nYour pet feels refreshed.\n";
		}
		hap_plus(2);
		sad_minus(3);
		hap += 2;
		sad -= 3;
		poo = true;
		break;
	}
	cout << "\n\n";
	cout << name << " showed you few items that it found:\n";
	randomnum = r_events(250, 5, 1);
	if (randomnum == 1 || randomnum == 2) {
		cout << "A.";
		randomnum = r_events(45, 50, 1);
		cout << "$ " << randomnum << " Price: $ 10\nB.Don't buy anything\n";
		while (1) {
			key = getch();
			if (key == 'A' || key == 'a') {
				if (!(money < 10)) {
					money = money - 10;
					cout << "You spent $ 10 to but $ " << randomnum << ". ";
					if (randomnum > 10) {
						cout << "What a silly great deal!\n";
					}
					if (randomnum == 10) {
						cout << "What a balanced profit!\n";
					}
					if (randomnum < 10) {
						cout << "What a foolish decision!\n";
					}
					money += randomnum;
				} else {
					money_not();
				}
				break;
			}
			else if (key == 'B' || key == 'b') {
				break;
			}
		}
	}
	if (randomnum == 3 || randomnum == 4) {

		cout << "A.Toy mouse (happiness [+1]~[+5] each day) $ " << price_mouse << "\nB.Slipper (don't you want to buy a house for your pet?) $ " << price_slipper << "\n";
		cout << "C.Heart saver capsule $ " << price_heartsaver << "\nD.Don't buy anything\n";
	}
	while (1) {
		key = getch();
		if (key == 'A' || key == 'a') {
			if (!(money < 90)) {
				if (Pmouse == false) {
					money = money - 90;
					cout << "You have bought the toy mouse!\n";
					Pmouse = true;
				} else {
					cout << "Sorry, but your pet already have one!\n";
				}
			} else {
				money_not();
			}
			break;
		}
		else if (key == 'B' || key == 'b') {
			if (!(money < 20)) {
				if (Phouse == false) {
					money = money - 20;
					cout << "You have bought the slipper!\n";
					Phouse = true;
				} else {
					cout << "Sorry, but your pet already have one!\n";
				}
			} else {
				money_not();
			}
			break;
		}
		else if (key == 'C' || key == 'c') {
			if (!(money < 10000)) {
				cout << "Sorry, buy you don't have enough money! Continue? (Press [up button] to continue and press [down button] to quit)\n";
				money = money - 10000;
				while (1) {
					key = getch();
					if (key == up) {
						cout << "MONSTER!\nHappiness = 0! Sadness maximumizes!\n";
						hap = 0;
						sad = max_sad;
						break;
					}
					else if (key == down) {
						cout << "You are scamed!\n";
						break;
					}
				}
			} else {
				money_not();
			}
			break;
		}
		else if (key == 'D' || key == 'd') {
			break;
		}
	}
	if (randomnum == 5) {
		cout << "A.Lonliness (buy one when you are on your own) $ " << price_lone << "\nB.Don't buy anything\n";
		while (1) {
			key = getch();
			if (key == 'A' || key == 'a') {
				if (!(money < 10)) {
					money = money - 10;
					cout << "You have bought... lonliness...\n";
				} else {
					money_not();
				}
				break;
			}
			else if (key == 'B' || key == 'b') {
				break;
			}
		}
	}
	hyphen(4);
}

int Bturns = 1;
int Bdays = 1;
bool back = false;
bool BFS = false; //BFS=BIG FUCKING STAR
int Msenting;
void Bback() {
	back = true;
	cout << "\"21st century schizoid pet!\"You see your pet is holding a electric guitar (being overwhelmed under the guitar), and the spotlight shines on its eyes.\n";
	pause();
	cout << "Tears run out your eyes. Few weeks later, your pet knocks on the door again, and it tells you (don't ask me how) that this performance has made a great success.\n";
	randomnum = r_events(134, 5, 1);
	if (randomnum == 5) {
		BFS = true;
		randomnum = r_events(214, 3000, 200);
		cout << "Your pet becomes the next Michael Jackson in the world - in fact, hardly anybody still remembers Michael Jackson now. There are a lot of crazy fans come to send you money everyday after that performance, but your pet mysteriously refuses (don't ask me how) to go back to the business.\n";
	}
	else {
		randomnum = r_events(298, 2000, 100);
	}
	money = money + randomnum;
	cout << "The performance earns you $ " << randomnum << " in total. In order to show thankfulness, your pet hands you all the money.\n";
	pause();
	cout << "And so, the both of you come back to your ordinary life.\n";
	hyphen(4);
}

void Binteract() { //Ëæ»úÊÂ¼þ4
	if (key == 'T' || key == 't') {
		cout << "You open the YV.\n";
		pause(1);
		randomnum = r_events(1874298, 2, 1);
		if (randomnum == 1)Btv1();
		else if (randomnum == 2)Btv2();
		else if (randomnum == 3)Btv3();
		else if (randomnum == 4)Btv4();
		randomnum = r_events(82734, 4, 1);
		if (randomnum == 2) {
			cout << "You are switching channels, and suddenly, you see...\n\nYour pet!\n";
			pause();
			Bback();
			return;
		}
		else {
			cout << "You keep changing the channels, but can't find any information about your pet...\n";
			pause(1);
		}
	}
	else {
		hyphen(3);
		cout << "\n";
		choose_again();
		cout << "\nPress 't' to watch TV\nThere are 1 chance to watch TV everyday\nYou have " << 1 + 1 - Bturns << " time left\n";
		key = getch();
		Binteract();
	}
}

void band_days() {	//Ëæ»úÊÂ¼þ4
	hyphen(2);
	cout << "ÕâÊÇµÚ" << Bdays << "Ìì\n";
	while (1) {
		if (Bturns == 2)break;
		cout << "\n";
		choose_again();
		cout << "\nPlease choose again!\nPress 't' to watch TV\nThere are 1 chance to watch TV everyday\nYou have " << 1 + 1 - Bturns << " time left\n";
		key = getch();
		Binteract();
		if (back == true)break;
		Bturns++;
	}
	Bdays++;
	Bturns = 1;
}

void r4() {//Ëæ»úÊÂ¼þ4£º³èÎïµÄÇ°ÎÀÒ¡¹öÀÖ¶Ó
	Bband = true;
	cout << "For the past few days, your pet has been listening to some strange rock music.\nYou often hear some words like 'rape' from " << name << "'s mouse (don't ask me how)\n";
	pause();
	cout << "One day, your pet told you through a unimaginable way that it is going to start a progressive rock band.\nBecause you have gave it too much, this band won't cost you any money.\n";
	pause();
	eat = false;
	poo = false;
	cout << "Before it left, you feed your pet for the last time, and let it defecates for the last time.\nYou witness its leave...\n";
	pause();
	hyphen(4);
	while (1) {
		band_days();
		if (back == true)break;
	}
}

void r5() {//Ëæ»úÊÂ¼þ5
	randomnum = r_events(123, 5, 1);
	cout << "\nToday, you can't find your pet anywhere. Few hours later, your pet brings you back ";
	if (randomnum == 1) { //ÌÇ
		randomnum = r_events(1234, 35, 1); //´øÀ´1-35¸öÊ³²Ä
		cout << randomnum << " grams of sugar!\n";
		sug += randomnum;
	}
	else if (randomnum == 2) { //ÑÎ
		randomnum = r_events(1234, 35, 1); //´øÀ´1-35¸öÊ³²Ä
		cout << randomnum << " grams of salt!\n";
		sul += randomnum;
	}
	else if (randomnum == 3) { //ËÕ´ò
		randomnum = r_events(1234, 35, 1); //´øÀ´1-35¸öÊ³²Ä
		cout << randomnum << " grams of soda!\n";
		sod += randomnum;
	}
	else if (randomnum == 4) { //Ë®
		randomnum = r_events(1234, 35, 1); //´øÀ´1-35¸öÊ³²Ä
		cout << randomnum << " milliliters of water!\n";
		if (wat + randomnum <= 1000)wat += randomnum;
	}
	else if (randomnum == 5) { //Ãæ·Û
		randomnum = r_events(1234, 35, 1); //´øÀ´1-35¸öÊ³²Ä
		cout << randomnum << " grams of flour!\n";
		flo += randomnum;
	}
	pause();
}

void r_e() {//random events Éú³É
	if (days >= 1) {
		randomnum = r_events();
		//cout <<randomnum<<"\n";//²âÊÔ´úÂë
		if (!(randomnum > events)) {
			if (randomnum == 1) r1();
			else if (randomnum == 2) {
				if (invest == false)r2();
			}
			else if (randomnum == 3) r3();
			else if (randomnum == 4) {
				if (Bband == false)r4();
			}
			else if (randomnum == 5) r5();
		}
	}
}

//ËÀÍöº¯Êý
void death() {//³èÎïµÄËÀÍö
	hyphen();
	cout << "Your pet " << name << " had been through a life of " << age << " years, and it had been through " << days << " days.\n";
	cout << "When " << name << " was going to die, ";
	if (poo == true) {
		cout << "it still wants to defecate.\n";
	}
	if (eat == true) {
		cout << "it is still very hungry.\n";
	}
	cout << "When it was going to die, " << name << " ";
	if (sad >= 38 && sad < 42 && hap < 50) {
		cout << "was a bit sad.\n";
	}
	if (sad >= 42 && hap < 50) {
		cout << "was very depressed.\n";
	}
	if (hap >= 50 && hap < 76 && sad < 38) {
		cout << "was quite happy.\n";
	}
	if (hap >= 76 && sad < 38) {
		cout << "was very happy.\n";
	}
	if (hap >= 50 && sad >= 38) {
		cout << "was confused.\n";
	}
	died = true;
	pause(1);
}

//Çé¸Ðº¯Êý
void e_poo() {
	if (w_poo > 10) {
		w_poo == 10;
	} else {
		if (w_poo > 5) {
			if (w_poo < 8) {
				hap -= 5;
				sad += 3;
			}
			if (w_poo >= 8) {
				hap -= 8;
				sad += 6;
			}
		}
	}
}

void e_eat() {
	if (w_eat > 5) {
		w_eat == 5;
	} else {
		if (w_eat > 2) {
			if (w_eat < 4) {
				hap -= 4;
				sad += 5;
			}
			if (w_eat >= 4) {
				hap -= 8;
				sad += 7;
			}
		}
	}
}

void e_age() {
	if (days != 0 && days % 10 == 0) {
		age++;
		your_pet();
		cout << "is 1 year older!\n";
	}
}

void e_sad() {
	if (sad < 0)sad = 0;
	if (sad > max_sad)sad = max_sad;
	if (!(sad >= max_sad)) {
		if (sad > 25) {
			if (sad < 38) {
				sad += 3;
				hap = hap - 6;
			}
			if (sad >= 38) {
				sad += 6;
				hap = hap - 10;
			}
		}
	} else {
		your_pet();
		cout << "is so depressed that it committed suicide.\n";
		death();
	}
}

bool Lifespanup_turns = false; //ÊÇ·ñÔÚµ¥»ØºÏÄÚÒÑ¾­Ôö¼ÓÁËÊÙÃü
int Lifespanhap;//ÉúÃüÉÏÏÞËùÐèµÄ¿ìÀÖÖµµÄ³õÊ¼ÖµÊÇÒ»¸ö85-60Ö®¼äµÄËæ»úÊý
void e_hap() {
	if (hap < 0)hap = 0;
	if (hap > max_hap)hap = max_hap;
	if (!(hap >= max_hap)) {
		if (hap > 50) {
			if (hap < 76) {
				hap += 3;
				sad = sad - 3;
			}
			if (hap >= 76) {
				hap += 4;
				sad = sad - 5;
				if (hap >= Lifespanhap && sad <= 15) { //¿ìÀÖÖµ>=ÊÙÃüÔö¼ÓËùÐèµÄ¿ìÀÖÖµÇÒ±¯ÉËÖµÐ¡ÓÚµÈÓÚ15£¬ÊÙÃüÔö¼ÓÒ»Ìì
					if (turns == 2 || turns == 4 || turns == 6 || turns == 8) {
						if (Lifespanup_turns == false) {
							cout << "Your pet's lifespan increace by 1 day!\n";
							lifespan++;
							Lifespanup_turns = true;
						}
					} else {
						Lifespanup_turns = false;
					}
				}
			}
		}
	} else {
		sad = sad - 5;
	}
}

//½ðÇ®º¯Êý
int cheatmoney;
int uglyprice;//Ëæ»úÊý¼Û¸ñ
int gs;//¹ºÂò¿ËÊý
void M_notice() {
	if (gs < 0) {
		cout << "Please input again!\n";
	}
	else if (gs == 0) {
		cout << "You give up to buy.\n";
	}
}

void M_cok() {  //Ê³²Ä
	while (1) {
		money_have();
		cout << "Cooking ingredients:\nA.Sugar $ " << price_sug << " per gram\nB.Salt $ 6~12 per gram\nC.Soda $ " << price_sod << " per gram\n";
		cout << "D.Water $ " << price_wat << " per milliliter\nE.Flour $ " << price_flo << " per gram\nF.Air $ 20~900 per square meter\nG.Quit this menu\n";
		key = getch();
		if (key == 'A' || key == 'a') {
			uglyprice = 8;
			while (1) {
				cout << "Input the number of grams you want to buy:";
				cin >> gs;
				M_notice();
				if (gs == 0) {
					pause();
					turns--;
					break;
				}
				else {
					if (money >= gs * uglyprice) {
						cout << "You have successfully bought " << gs << " grams of sugar!\n";
						money = money - gs * uglyprice;
						sug += gs;
						pause();
						break;
					} else {
						money_not();
						pause();
						break;
					}
				}
			}
			system("cls");
		}
		else if (key == 'B' || key == 'b') {
			uglyprice = r_events(123, 21 - 6, 6);
			cout << "Price: $ " << uglyprice << "\n";
			still_buy();
			while (1) {
				key = getch();
				if (key == up) {
					while (1) {
						cout << "Input the number of grams you want to buy:";
						cin >> gs;
						M_notice();
						if (gs == 0) {
							pause();
							turns--;
							break;
						} else {
							if (money >= gs * uglyprice) {
								cout << "You have successfully bought " << gs << " grams of salt!\n";
								money = money - gs * uglyprice;
								sul += gs;
								pause();
								break;
							} else {
								money_not();
								pause();
								break;
							}
						}
					}
					system("cls");
					break;
				}
				else if (key == down) {
					system("cls");
					break;
				}
			}
		}
		else if (key == 'C' || key == 'c') {
			uglyprice = 9;
			while (1) {
				cout << "Input the number of grams you want to buy:";
				cin >> gs;
				M_notice();
				if (gs == 0) {
					pause();
					turns--;
					break;
				}
				else {
					if (money >= gs * uglyprice) {
						cout << "You have successfully bought " << gs << " grams of soda!\n";
						money = money - gs * uglyprice;
						sod += gs;
						pause();
						break;
					} else {
						money_not();
						pause();
						break;
					}
				}
			}
			system("cls");
		}
		else if (key == 'D' || key == 'd') {
			while (1) {
				cout << "Input the number of milliliters you want to buy:";
				cin >> gs;
				if (wat < 1000 && wat + gs <= 1000) {
					wat += gs;
					cout << "You have successfully bought " << gs << " milliliters of water!\n";
					hyphen(4);
					break;
				}
				else {
					cout << "Sorry, but you have had enough water!\n";
					hyphen(4);
					break;
				}
			}
			pause();
			system("cls");
		}
		else if (key == 'E' || key == 'e') {
			uglyprice = 6;
			while (1) {
				cout << "Input the number of grams you want to buy:";
				cin >> gs;
				M_notice();
				if (gs == 0) {
					pause();
					turns--;
					break;
				}
				else {
					if (money >= gs * uglyprice) {
						cout << "You have successfully bought " << gs << " grams of flour!\n";
						money = money - gs * uglyprice;
						flo += gs;
						pause();
						break;
					} else {
						money_not();
						pause();
						break;
					}
				}
			}
			system("cls");
		}
		else if (key == 'F' || key == 'f') {
			uglyprice = r_events(123, 900 - 20, 20);
			cout << "Price: $ " << uglyprice << "\n";
			still_buy();
			while (1) {
				key = getch();
				if (key == up) {
					while (1) {
						cout << "Input the number of milliliters you want to buy:";
						cin >> gs;
						M_notice();
						if (gs == 0) {
							pause();
							turns--;
							break;
						}
						else {
							if (money >= gs * uglyprice) {
								cout << "You have successfully bought " << gs << " square meters of air!\n";
								money = money - gs * uglyprice;
								pause();
								break;
							} else {
								money_not();
								pause();
								break;
							}
						}
					}
					system("cls");
					break;
				}
				else if (key == down) {
					system("cls");
					break;
				}
			}
		}
		else if (key == 'G' || key == 'g') {
			hyphen(4);
			break;
		}
	}
}

void M_stu() {	//µÀ¾ß
	while (1) {
		money_have();
		cout << "Props:\nA.Buttercup - a kind of plant (Sadness [-8]) $ " << price_pbutter << "\nB.Buttercup - a kind of madness (Sadness [-15]) $ " << price_mbutter << "\n";
		cout << "C.Arsenic (Use it when investing. Rate of success [+50]%) Price: (all the money you have, including money for investment)/5, then minus a random number (1~(money you have)/20)";
		cout << "\nD.Diamond (use it when investing, so the [investment will fail 100%]) Price: (all the money you have, including money for investment)*10\nE.Quit this menu\n";
		key = getch();
		if (key == 'A' || key == 'a') {
			if (!(money < 35)) {
				money = money - 35;
				sad = sad - 8;
				bought_success();
				sad_minus(8);
				hyphen(4);
				break;
			} else {
				money_not();
				hyphen(4);
			}
		}
		else if (key == 'B' || key == 'b') {
			if (!(money < 50)) {
				money = money - 50;
				sad = sad - 15;
				bought_success();
				sad_minus(15);
				hyphen(4);
				break;
			} else {
				money_not();
				hyphen(4);
			}
		}
		else if (key == 'C' || key == 'c') {
			if (!(money <= 0)) {
				while (1) {
					cheatmoney = (money + Iinvest) / 5;
					if (money / 20 < 1)cheatmoney = cheatmoney - r_events(131, 1, (money + Iinvest) / 20);
					else cheatmoney = cheatmoney - r_events(131, (money + Iinvest) / 20, 1);
					if (!(cheatmoney <= 0))break;
				}
				cout << "This time the price is $ " << cheatmoney << "\n";
				sure();
				while (1) {
					key = getch();
					if (key == 'H') {
						if (!(money < cheatmoney)) {
							if (invest == false) {
								cout << "Sorry, but you don't have any investment!\n";
							} else {
								if (cheat == true) {
									cout << "Sorry, buy you have already bought this prop!\n";
								}
								else if (loser == true) {
									cout << "Sorry, but you have already bought another prop...\n";
								}
								else {
									money = money - cheatmoney;
									bought_success();
									cheat = true;
								}
							}
							pause();
						} else {
							money_not();
							pause();
						}
						system("cls");
						break;
					}
					if (key == 'P') {
						system("cls");
						break;
					}
				}
			} else {
				cout << "You don't have any money at all!\n";
				hyphen(4);
				hyphen(4);
			}
		}
		else if (key == 'D' || key == 'd') {
			if (!(money <= 0)) {
				cout << "This time the price is $ " << money * 10 << "\n";
				still_buy();
				while (1) {
					key = getch();
					if (key == 'H') {
						if (money < money * 10 == false) {
							cout << "What the hell have you done to the code?!\n";
							hyphen(250);
							if (invest == false) {
								cout << "Sorry, but you don't have any investment!\n";
							} else {
								if (loser == true) {
									cout << "Sorry, buy you have already bought this prop!\n";
								}
								else if (cheat == true) {
									cout << "Sorry, but you have already bought another prop...\n";
								}
								else {
									money = money - money * 10;
									bought_success();
									loser = true;
								}
							}
							pause(1);
						} else {
							money_not();
							pause(1);
						}
						break;
					}
					if (key == 'P') {
						system("cls");
						break;
					}
				}
			} else {
				cout << "You don't have any money at all!\n";
				hyphen(4);
				hyphen(4);
			}

		}
		else if (key == 'E' || key == 'e') {
			hyphen(4);
			break;
		}
	}
}

bool det = false; //ÊÇ·ñ½è´û
int Mdet;//½è´û½ð¶î
int Pdet;//»¹Õ®½ð¶î
float Edet;//½è´ûÀûÏ¢
int Ddet;//»¹Õ®ÆÚÏÞ
bool Ldet = false; //ÊÇ·ñÍÏÇ·´û¿î
void M_det() {		//借贷
	hyphen();
	if (det == false) {
		while (1) {
			cout << "Input the amount of loan you want to apply for (no more than (all the money you have)*10):\n";
			cin >> Mdet;
			if (!(Mdet <= 0)) {
				if (!(Mdet > 10 * money) && money != 0) {
					Ddet = r_events(3, 10, 1);
					Edet = r_events(3, 10, 1);
					{
						cout << "Loan $ " << Mdet << "/Total interest " << Edet << "%/On the terms of " << Ddet << " days\nEach day after that [+" << Edet << "]%!\n";
					}
					sure();
					while (1) {
						key = getch();
						if (key == 'H') {
							money_plus(Mdet);
							money = money + Mdet;
							Ddet = Ddet + days;
							Pdet = Mdet;
							det = true;
							Edet = Edet / 100;
							break;
						} if (key == 'P') {
							cout << "You give up the contract.\n";
							Mdet = 0;
							Edet = 0;
							Ddet = 0;
							break;
						}
					}
				} else {
					if (money == 0) {
						cout << "Sorry if this is offensive (obviously this is), but the bank won't trust a nut who don't even have a dime!\n";
					} else {
						cout << "Sorry, but this is obviously more than ten times of all the money you have!\n";
					}
					turns--;
				}
				hyphen(4);
				break;
			} else {
				if (Mdet == 0) {
					cout << "You give up the loan\n";
					turns--;
					break;
				}
				if (Mdet < 0) {
					cout << "The number is wrong, please input again!\n";
					hyphen(4);
				}
			}
		}
		hyphen(4);
	} else {
		cout << "Sorry, but you have already appied for a loan!\n";
		hyphen(4);
	}
}


bool Dgm = false;
void M_() {
	if (money < 0) {
		money = 0;
	}
	if (det == true) {
		if (Ldet == true) {
			if (Dgm == true) {
				Pdet = Pdet + Edet * Pdet;
				cout << "\n\nYou need to pay the bank $ " << Pdet << ", are you going to pay? (Press [up button] to confirm, and press [down button] to refuse)\n";
				while (1) {
					key = getch();
					if (key == 'H') {
						if (money >= Pdet) {
							cout << "You have pay off the loan.\n";
							det = false;
							Pdet = 0;
							Ldet = false;
							Edet = 0;
							money = money - Pdet;
						} else {
							cout << "Sorry, but you don't have enough money to pay!\nA few bank clerks are scolding you and your pet at your front door.\n";
							sad_plus(15);
							hap_minus(10);
							hap = hap - 10;
							sad += 15;
						}
						hyphen(3);
						Dgm = false;
						break;
					}
					if (key == 'P') {
						cout << "You refuse to pay.\nA few bank clerks are scolding you and your pet at your front door.\n";
						sad_plus(15);
						hap_minus(10);
						sad += 15;
						hap = hap - 10;
						hyphen(3);
						Dgm = false;
						break;
					}
				}
			}
		} else {
			if (days == Ddet) {
				Pdet = Pdet + Edet * Pdet;
				cout << "\n\nIt's time for you to pay back. You need to pay the bank $ " << Pdet << ", are you going to pay? (Press [up button] to confirm, and press [down button] to refuse)\n";
				while (1) {
					key = getch();
					if (key == 'H') {
						if (money >= Pdet) {
							cout << "You pay off the load. Because of your honesty,\n";
							hap_plus(2);
							sad_minus(1);
							hap += 2;
							sad -= 1;
							money -= Pdet;
							Pdet = 0;
							det = false;
							Mdet = 0;
							Edet = 0;
							Ddet = 0;
						} else {
							cout << "Sorry, but You don't have enough money to pay!\nEach day after this, your debt [+" << Edet << "]%!\n";
							Mdet = 0;
							Ddet = 0;
							Ldet = true;
						}
						hyphen(3);
						break;
					}
					if (key == 'P') {
						cout << "You refuse to pay!\nEach day after this, your debt [+" << Edet << "]%!\n";
						Ldet = true;
						Mdet = 0;
						Ddet = 0;
						hyphen(3);
						break;
					}
				}
			}
		}
	}
}

//²Ù×÷º¯Êý
void interact() {
	cout << "\n";
	if (key == 'Q' || key == 'q') {
		cout << "You quit the game.\n";
		pause(4);
	}
	else if (key == 'F' || key == 'f') {
		cout << "You feed your pet.\n";
		w_eat = 0;
		if (eat == true) {
			hap += 2;
			hap_plus(2);
		}
		eat = false;
		pause();
	}
	else if (key == 'I' || key == 'i') {
		while (1) {
			cout << "\n\nINTERACTIONS:\nA.Let your pet to defecate\nB.Pat your pet\nC.Quit this menu\n";
			key = getch();
			if (key == 'A' || key == 'a') {
				cout << "You let your pet " << name << " defecates\n";
				w_poo = 0;
				if (poo == true) {
					hap_plus(1);
					hap++;
				}
				poo = false;
				pause();
				break;
			}
			else if (key == 'B' || key == 'b') {
				cout << "You pat your pet " << name << "\n";
				hap += 4;
				sad = sad - 3;
				hap_plus(4);
				sad_minus(3);
				pause();
				break;
			}
			else if (key == 'C' || key == 'c') {
				hyphen(4);
				notice();
				key = getch();
				interact();
				break;
			}
			else {
				cout << "\n";
				choose_again();
			}
		}
		cout << "\n\n";
	}
	else if (key == 'C' || key == 'c') {
		cout << "---LIFESPAN---\n";
		your_pet();
		Pab == cat ? cout << "is a cat.\n" : cout << "is a dog.\n";
		your_pet();
		cout << "is " << age << " years old now\n";
		your_pet();
		cout << "can still live for " << lifespan - days + 1 << " days\n";
		your_pet();
		cout << "need to have at least reach to [Happiness: " << Lifespanhap << "] to prolong lifespan\n";
		cout << "---EMOTION---\n";
		cout << "[Happiness: " << hap << "/" << max_hap << "]\n[Sadness: " << sad << "/" << max_sad << "]\n";
		cout << "---PHYSIOLOGY---\n";
		cout << "Wants to defecate:";
		poo == true ? cout << "[YES]\n" : cout << "[NO]\n";
		cout << "Wants to eat:";
		eat == true ? cout << "[YES]\n" : cout << "[NO]\n";
		turns--;
		pause();
	}
	else if (key == 'S' || key == 's') {
		system("cls");
		turns--;
	}
	else if (key == 'M' || key == 'm') {
		while (1) {
			cout << "You have $ " << money << "\nWhat do you want to do next?\nA.Buy items\nB.Buy [cooking ingredients]\nC.Apply for loan\nD.Start cookingE.Quit this menu\n";
			key = getch();
			if (key == 'A' || key == 'a') {
				hyphen();
				M_stu();
				break;
			}
			else if (key == 'B' || key == 'b') {
				hyphen();
				M_cok();
				break;
			}
			else if (key == 'C' || key == 'c') {
				hyphen();
				M_det();
				break;
			}
			else if (key == 'D' || key == 'd') {
				Cincook();
				break;
			}
			else if (key == 'E' || key == 'e') {
				hyphen();
				notice();
				key = getch();
				interact();
				break;
			}
			else {
				cout << "\n";
				choose_again();
			}
		}
	}
	else if (key == 'V' || key == 'v') {
		if (Vacheve == true) {
			turns--;
			Vacheve = false;
			hyphen(5);
			cout << "Money you have invested: $ " << Iinvest << "\nYou need to wait for: " << Dinvest - days << "days\n";
		} else {
			hyphen(3);
			cout << "\nPlease choose again!\n";
			notice();
			key = getch();
			interact();
		}
	}
	else if (key == 'B' || key == 'b') {
		colorc(blue);
		cout << "You have " << sug << " grams of sugar\nYou have " << sul << " grams of salt\nYou have " << sod << " grams of soda\nYou have " << wat << " milliliter of water (1000 milliliter max)\nYou have " << flo << " grams of flour\n";
		colorc(white);
		pause(1);
		turns--;
		hyphen(4);
	}
	else if (key == 'O' || key == 'o') {//waiting to update
		hyphen(4);
		if (Cid != 0) {
			int CDSS = 0;
			while (1) {
				if (CDSS == Cid)break;
				cout << CDSS << "." << backpackmeal[CDSS] << "|Energy: " << backpackcalr[CDSS] << "|Effect: " << backpackeffect[CDSS] << "|";
				cout << "Amount: " << backpackall[CDSS] << "\n";
				CDSS++;
			}
			pause();
			while (1) {
				cout << "Input the number of item you want to choose (insert negative number to quit this menu):";
				cin >> CTP;
				if (CTP >= Cid || CTP < 0) {
					break;
				} else {
					hyphen(4);
					cout << "A.Sell this dish\nB.Feed this dish to your pet\nC.Dump this dish\nD.Quit this menu\n";
					while (1) {
						key = getch();
						if (key == 'A' || key == 'a') {

							break;
						}
						else if (key == 'B' || key == 'b') {

							break;
						}
						else if (key == 'C' || key == 'c') {
							cout << "Item NO. " << CTP << " has been dropped\n";
							Cdrop(CTP);
							break;
						}
						else if (key == 'D' || key == 'd') {
							break;
						}
					}
				}
			}
		} else {
			cout << "You don't have any dish!\n";
			pause();
		}
		turns--;
		hyphen(4);
	}
	else if (key == 'X' || key == 'x') {
		color_choose();
		turns --;
	}
	/*else if (key == '?') {
		hyphen(4);
		cout << "A.ÍË³ö´Ë½çÃæ\nB.»ù´¡²Ù×÷½Ì³Ì\nC.Ëæ»úÊÂ¼þ²Ù×÷½Ì³Ì\nD.½è´ûÏµÍ³²Ù×÷½Ì³Ì\nE.Åëâ¿ÏµÍ³²Ù×÷½Ì³Ì\nF.³èÎïËÀÍö\n";
		while (1) {
			key = getch();
			if (key == 'A' || key == 'a') break;
			else if (key == 'B' || key == 'b') {
				hyphen(4);
				cout << "¢Ù.ÇëÔÚ¿ªÊ¼ÓÎÏ·Ê±ÇÐ»»ÎªÓ¢ÎÄÊäÈë·¨\n";
				cout << "¢Ú.Äã¿ÉÒÔÔÚÓÎÏ·ÖÐ°´ÏÂ°´¼üÑ¡Ôñ²»Í¬ÐÐ¶¯£¬Ò»ÌìÓÐ8¸ö»ØºÏÑ¡ÔñÐÐ¶¯£¬µ«°´S£¨ÇåÆÁ£©»ò°´C£¨²é¿´³èÎï×´Ì¬£©²¢²»Õ¼ÓÃ»ØºÏ¡£\n";
				cout << "¢Û.ÓÎÏ·ÖÐÓÐÕâÑù¼¸¸öÊýÖµ£º³èÎïÊÇ·ñÏëÒªÅÅÐ¹£¨Èç¹û³èÎïÏëÒªÅÅÐ¹£¬Ã¿µÈ´ýÒ»»ØºÏ»á¿Û³ý¿ìÀÖÖµ¡¢Ôö¼Ó±¯ÉËÖµ£©¡¢³èÎïÊÇ·ñ\nÏëÒª½øÊ³£¨Èç¹û³èÎïÏëÒª½øÊ³£¬Ã¿µÈ´ýÒ»»ØºÏ»á¿Û³ý¿ìÀÖÖµ¡¢Ôö¼Ó±¯ÉËÖµ£©¡¢³èÎï¿ìÀÖÖµ£¨100Âú£©\n¡¢³èÎï±¯ÉËÖµ£¨50Âú£¬±¯ÉËÖµ³äÂúºó³èÎïËÀÍö£©\n";
				pause();
				break;
			}
			else if (key == 'C' || key == 'c') {
				hyphen(4);
				cout << "µ±ÓÎÏ·ÌìÊý>=1Ê±£¬0.1.1¼°ÒÔÉÏµÄ°æ±¾»á´¥·¢Ëæ»úÊÂ¼þ¡£Ëæ»úÊÂ¼þÓÐ£º\n";
				cout << "¢Ù.³èÎïÎªÄã´øÀ´Ëæ»ú´óÐ¡µÄ½ðÇ®£¨0~35Ôª£¬Îª0ÔªÊ±²»´¥·¢£© \n¢Ú.³èÎïµ£µ±ÄãµÄÍ¶×ÊÈË£¬Èç¹ûÍ¶ÈëÈ«²¿½ðÇ®£¬»áÔö¼Ó³èÎïµÄ¿ìÀÖÖµºÍ¼õÉÙ±¯ÉËÖµ¡£½á¹û»áÔÚËæ»úÌìÊýºó³öÏÖ£¬ÓÐ25%¸ÅÂÊ³É¹¦£¬½ðÇ®»Ø±¨ÂÊ10%-50%\n";
				cout << "¢Û.³èÎïÍÆÏúÉÌÆ·£¬ÓÐÈýÌ×ÉÌÆ·£¬·Ö±ðÓÐ40%¡¢40%ºÍ20%µÄ¸ÅÂÊ´¥·¢\n¢Ü.³èÎï´´Á¢ÁËÒ»¸öÇ°ÎÀÒ¡¹öÀÖ¶Ó¡£¿ÉÒÔÎªÄã´øÀ´½ðÇ®£¡£¨Ò»´ÎÐÔËæ»úÊÂ¼þ£¬Ö»¿ÉÒÔ´¥·¢Ò»´Î£©\n¢Ý.³èÎïÎªÄã´øÀ´ÎåÖÖÊ³²ÄÖÐµÄÈÎÒâÒ»ÖÖ£¬ÊýÁ¿ÊÇÒ»¸ö1~35µÄËæ»úÊý\n";
				pause();
				break;
			}
			else if (key == 'D' || key == 'd') {
				hyphen(4);
				cout << "°´ÏÂM¼üºó½øÈë½ðÇ®½çÃæ¡£½è´ûµÄ½ð¶î²»ÄÜ´óÓÚ±¾Éí½ðÇ®µÄÊ®±¶£¬Èç¹û±¾Éí½ðÇ®Îª0£¬Ôò²»¿É½è´û¡£\n½è´ûµÄÀûÏ¢ÔÚ1%µ½10%Ö®¼ä£¬»¹Õ®ÆÚÏÞÎªËæ»úÌìÊý¡£Èç¹ûµ½¹æ¶¨ÆÚÏÞÈÔÎ´»¹Õ®£¬ÔòÃ¿¶àÒ»ÌìÕ®¿îÔö¼ÓÔ­ÏÈÀûÂÊ¡£Èç¹û´ßÕ®²»»»£¬ÔòÃ¿Ò»´Î¼õÉÙ¿ìÀÖÖµ¡¢Ôö¼Ó±¯ÉËÖµ\n";
				pause();
				break;
			}
			else if (key == 'E' || key == 'e') {
				hyphen(4);
				cout << "Î´¿ª·Å£¡\n";
				pause();
				break;
			}
			else if (key == 'F' || key == 'f') {
				hyphen(4);
				cout << "ÓÎÏ·ÄÚ£¬³èÎïÒ»¹²ÓÐÃ¨¹·Á½¸öÎïÖÖ¡£Á½¸öÎïÖÖµÄ¼«ÏÞÊÙÃü£¨ÌìÊý£©²»Í¬£¬Ã¨µÄ¼«ÏÞÊÙÃüÊÇ2Ëêµ½4ËêµÄËæ»úÊý£»¹·µÄ¼«ÏÞÊÙÃüÊÇ1Ëê°ëµ½5ËêµÄËæ»úÊý\n";
				cout << "\nÔÚËæ»úÊÂ¼þ¡°³èÎïµÄÇ°ÎÀÒ¡¹öÀÖ¶Ó¡±ÖÐ¶È¹ýµÄÌìÊý²»ËãÔÚ³èÎïµÄÊÙÃüÄÚ¡£Äã¿ÉÒÔÔÚ°´ÏÂCºó²é¿´³èÎïµÄÊÙÃü¡£µ«ÊÙÃü²¢²»ÊÇ²»¿ÉÌáÉýµÄ£¬³èÎïÔÚÒ»¿ªÊ¼ÓµÓÐÒ»¸ö85-60¼äµÄËæ»úÊý×÷ÎªÊÙÃüÔö¼ÓËùÐèÒª´ïµ½µÄ¿ìÀÖÖµµÄµãÊý£¬¶øÃ¿Ìì£¬Õâ¸öÊýÖµ¶¼»á¡¾+5¡¿£¬Ò»Ö±µ½ÎÞ·¨ÔÙ´ÎÔö¼ÓÎªÖ¹¡£Èç¹û³èÎïµÄ¿ìÀÖÖµ´óÓÚÕâ¸öÖµ£¬ÇÒ³èÎïµÄ±¯ÉËÖµÐ¡ÓÚ15£¬ÔòÊÙÃü¡¾+1¡¿£¬Ò»ÌìµÄ°Ë»ØºÏÄÚ£¬Ö»ÓÐÆæÊý»ØºÏÊÙÃüÔö¼Ó¡£\n";
				pause();
				break;
			}
		}
		system("cls");
		turns--;
	}*/
	/*else if(key=='K'||key=='k') {
		hyphen(4);
		cout <<"A.´æµµ\nB.²é¿´´æµµ\nC.¶Áµµ\nD.ÍË³ö½çÃæ\n";
		while(1) {
			key=getch();
			if(key=='A'||key=='a') {
				get_save.open("save\name");
				get_save.clear();
				get_save<<name;
				get_save.close();
				break;
			}
			else if(key=='D'||key=='d') break;
		}
		pause(1);
	}*/
	else if ((key == 'L' || key == 'l') && cheatable == true) {
		hyphen(250);
		cout << "ÊäÈë×÷±×Âë£º";
		cin >> cheating;
		cout << "\n";
		if (cheating == "Gmoney") {
			cin >> Mopluse;
			money += Mopluse;
		}
		else if (cheating == "Clean") {
			hap = 50;
			sad = 0;
			poo = false;
			eat = false;
		}
		else if (cheating == "Turns") {
			turns = 1;
		}
		else if (cheating == "Smoney") {
			cin >> Mopluse;
			money = Mopluse;
		}
		else if (cheating == "Suicide") {
			hap = 0;
			sad = 10;
		}
		else if (cheating == "Days") {
			cin >> Mopluse;
			days = Mopluse;
		}
		else if (cheating == "r1")r1();
		else if (cheating == "r2")r2();
		else if (cheating == "r3")r3();
		else if (cheating == "r4")r4();
		else if (cheating == "r5")r5();
		else if (cheating == "Bdays")band_days();
		else if (cheating == "Btv1")Btv1();
		else if (cheating == "Btv2")Btv2();
		else if (cheating == "Btv3")Btv3();
		else if (cheating == "Btv4")Btv4();
		else if (cheating == "Sug") {
			cin >> Mopluse;
			sug = Mopluse;
		}
		else if (cheating == "Sul") {
			cin >> Mopluse;
			sul = Mopluse;
		}
		else if (cheating == "Sod") {
			cin >> Mopluse;
			sod = Mopluse;
		}
		else if (cheating == "Wat") {
			cin >> Mopluse;
			wat = Mopluse;
		}
		else if (cheating == "Flo") {
			cin >> Mopluse;
			flo = Mopluse;
		}
		/*
		else if (cheating == "Walk") {
			system("cls");
			start();
		}
		*/
		else if (cheating == "Cooking") {
			wat = 100;
			sug = 100;
			sul = 100;
			sod = 100;
			flo = 100;
		}
		cout << "\n";
		hyphen(250);
		turns--;
	}
	else {
		hyphen(3);
		cout << "\n";
		choose_again();
		notice();
		key = getch();
		interact();
	}
}

void o_days() {//Ã¿Ò»Ììº¯Êý£¬ÆÚ¼ä²åÈëËæ»úÊÂ¼þ
	hyphen(2);
	Cfour();
	e_hap();
	e_sad();
	e_poo();
	e_eat();
	M_();
	e_age();
	if (cheatable == true)cout << "*";
	cout << "DAY " << days << " .\n";
	if (det == true && Ldet == true)Dgm = true;
	if (eat == true) {
		cout << "Your pet " << name << " is hungry\n";
	}
	if (poo == true) {
		cout << "Your pet " << name << " wants to defecate\n\n";
	}
	if (Pmouse == true) {
		Pmouse_plus = r_events(1784, 5, 1);
		cout << "Your pet is playing with the toy mouse.\n";
		hap_plus(Pmouse_plus);
		hap += Pmouse_plus;
	}
	if (BFS == true) {
		Msenting = r_events(1321, 500, 20);
		cout << "Some fans want " << name << " to keep performing, so they put $ " << Msenting << " .\n";
		money_plus(Msenting);
		money = money + Msenting;
	}
	if (lifespan < 0)lifespan = 0; //·ÀÖ¹ÊÙÃüÐ¡ÓÚ0
	if (days == lifespan) {
		cout << "If nothing goes wrong, this is the last day of your pet.\n";
	}
	if (Lifespanhap + 5 <= max_hap && days != 1) {
		your_pet();
		lifespan_plus(5);
		Lifespanhap += 5;
	} else if (days != 1 && Lifespanhap != max_hap) {
		your_pet();
		lifespan_plus(max_hap - Lifespanhap);
		Lifespanhap = max_hap;
	}
	while (1) {
		//cout <<turns<<"\n";//²âÊÔ
		if (lifespan < 0)lifespan = 0; //·ÀÖ¹ÊÙÃüÐ¡ÓÚ0
		if (days >= lifespan + 1) { //³èÎïÊÙÃü½áÊø£¬>=ÊÇÎªÁË·ÀÖ¹ÊÙÃüÔÚÄ³ÖÖÇé¿öÏÂ³ÉÎª¸ºÊý
			death(); died = true;
		}
		//cout <<"poo"<<w_poo<<"eat"<<w_eat<<"\n";//²âÊÔ
		//cout <<"½è´û"<<det<<"/ÀûÏ¢"<<Edet<<"/Ìì"<<Ddet<<"/Õ®¿î"<<Pdet<<"/ÍÏí³"<<Ldet<<"\n\n";//²âÊÔ
		//cout <<"ÌìÊý"<<Dinvest<<"\n";//²âÊÔ
		M_();
		Cfour();
		e_hap();
		e_sad();
		e_poo();
		e_eat();
		if (died == true) break; //ËÀÍö
		notice();
		key = getch();
		interact();
		if (key == 'Q' || key == 'q') break; //ÍË³ö
		turns++; w_eat++;
		if (days != 1) {
			w_poo++;
		}
		if (w_eat > 2)eat = true;
		if (w_poo > 4)poo = true;
		cout << "\n\n";
		if (eat == true) {
			your_pet();
			cout << "is hungry\n";
		}
		if (poo == true) {
			your_pet();
			cout << "wants to defecate\n\n\n";
		}
		hyphen(1);
		cout << "\n\n";
		if (turns == 9) {
			break;
			hyphen();
		}
	}
	if (invest == true && days == Dinvest) { //Ëæ»úÊÂ¼þ¶þ£¬Í¶×Ê
		invest = false;
		Dinvest = 0;
		randomnum = r_events(3, 4, 1);
		Einvest = r_events(3, 50, 10);
		if (cheat == false) {
			if (loser == false) {
				if (randomnum == 2) {
					your_pet();
					cout << "has made a successful investment£¡\nRate of profit " << Einvest << "%!\n";
					money_plus(IINVEST + Einvest / 100 * IINVEST);
					hap_plus(2);
					money = money + IINVEST + Einvest / 100 * IINVEST; hap += 2;
				} else {
					your_pet();
					cout << "has failed the investment!\n";
					hap_minus(1);
					sad_plus(2);
					hap -= 1;
					sad += 2;
				}
			} else {
				randomnum = 114514;
				loser = false;
			}
		}
		else {
			your_pet();
			if (randomnum != 1) {
				cout << "has made a successful investment£¡\nRate of profit: " << Einvest << "%£¡\n";
				money_plus(IINVEST + Einvest / 100 * IINVEST);
				hap_plus(2);
				money = money + IINVEST + Einvest / 100 * IINVEST;
				hap += 2;
			} else {
				cout << "has failed in the investment!\n";
				hap_minus(1);
				sad_plus(2);
				hap -= 1;
				sad += 2;
			}
			cheat = false;
		}
		Iinvest = 0;
		IINVEST = 0;
		Einvest = 0;
		hyphen();
		pause();
		cout << "\n\n";
	}
	r_e();
	turns = 1;
	days++;
}

int main() {
	srand(time(NULL));
	Mname();
	Mname1(); //Åëâ¿±äÁ¿¸³Öµ
	cout << "Digital Pet\n" << vertion << " " << phase;
	if (cheatable == true)cout << "*";
	hyphen(4);
	pause();
	color_choose();
	name_choose();
	per();
	pause();
	cout << "You will have a great time together, won't you?\nYou look at your pet, then suddenly realize that it might become the next Michael Jackson.\n";
	pause(1);
	r_lifespan();
	Lifespanhap = r_events(1242, 85 - 60, 60);
	while (1) {
		o_days();
		if (key == 'Q' || key == 'q')break;
		if (died == true)break;
	}
	return 0;
}