#include<conio.h>
#include<iostream>
//定义：语言
enum Language {cn, en};
//定义：性格
enum Personality {cat, dog};
//定义：按键
enum KeyCode {up = 'H', down = 'P'};
//定义：颜色
enum Color {red, green, blue, white = 6};
//定义：主题
enum ThemeType {Tdef, Tadv, Tele, Tnor};
//定义：用于烹饪头文件
enum CookType {ck, cr};
//定义-菜品
enum MealType {air, soda, indefine, flor, bread, bananas, cake};
//定义宏-菜品口味
enum Taste {sweet, sult, mois, too_sod, flat, floy, Vsweet, Vsult, Vmois, Vfloy, dry};
//0甜腻1咸的2湿乎乎的3充满气体的4平淡的5软绵绵的6非常甜的7非常咸的8非常湿的9非常软绵绵的10很干的

//定义宏-菜品效果
#define lifeup1 0.1 //寿命【+1】 
#define lifeup2 0.2 //寿命【+2】
#define lifelow1 -0.1//寿命【-1】
#define lifelow2 -0.2//寿命【-2】

#define hapup10 1.10//快乐值【+10】
#define hapup15 1.15//快乐值【+15】
#define haplow10 -1.10//快乐值【-10】
#define haplow15 -1.15//快乐值【-15】
#define Hapup5 2.5 //快乐值上限【+5】
#define Hapup15 2.15//快乐值上限+15
#define Haplow5 -2.5//快乐值上限【-5】
#define Haplow15 -2.15//快乐值上限【-15】 

#define sadup5 3.5//悲伤值+5
#define sadup8 3.8//悲伤值+8
#define sadlow5 -3.5//悲伤值【-5】
#define sadlow8 -3.8//悲伤值【-8】
#define Sadup5 4.5//悲伤值上限【+5】
#define Sadup10 4.10//悲伤值上限+10
#define Sadlow5 -4.5//悲伤值上限【-5】
#define Sadlow10 -4.10//悲伤值上限【-10】 

#define none 5.0//无效果-口味平淡 

using namespace std;

bool language;
int theme;

string name = "宠物"; //宠物名称
long long money = 50;		//金钱

char key;//按键

const string vertion = "0.2.2";
const string phase = "beta";

void hyphen(int shan = 0) {
	if (shan == 0)cout << "----------------------------------------\n";
	else if (shan == 1)cout << "****************************************\n";
	else if (shan == 2)cout << "++++++++++++++++++++++++++++++++++++++++\n";
	else if (shan == 3)cout << "========================================\n";
	else if (shan == 4)cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
	else if (shan == 5)cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
	else if (shan == 250)cout << "---Cheating Line-Cheating Line-Cheating Line-Cheating Line-Cheating Line---\n";
}

void colorc(int x) { //0.红 1.绿 2.蓝
	if (theme == Tdef) {
		if (x == red)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		if (x == green)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		if (x == blue)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		if (x == white)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
}

void pause(int screen = 0) {
	if (language == cn)cout << "（按下任意键继续……）\n";
	else if (language == en)cout << " (Press any key to continue...)\n";
	getch();
	if (screen == 1)system("cls");
}

void sure(bool besure = true) {
	if (language == cn && besure == true)cout << "你确定吗？";
	else if (language == en && besure == true)cout << "Are you sure?";
	if (language == cn) cout << "（按↑确定，按↓拒绝）\n";
	else if (language == en) cout << " (Press [up button] to confirm, and press [down button] to refuse)\n";
}

//选择设置
void color_choose() {
	if (language == cn) {
		cout << "\n请选择主题颜色：\nA.默认主题（黑底白字）\nB.冒险主题（紫底白字）\nC.淡雅主题（灰底白字）\nD.普通主题（白底黑字）\n";
	}
	else if (language == en) {
		cout << "\nChoose your theme color:\nA.Defalut theme (balck background+white words)\nB.Adventure theme (pureple background+white words)\n";
		cout << "C.Elegent theme (grey background+light white words)\nD.Normal theme (white background+black words)\n";
	}
	while (1) {
		key = getch();
		if (key == 'A' || key == 'a') {
			system("color 07");
			sure();
			while (1) {
				key = getch();
				if (key == up) {
					theme = Tdef;
					break;
				}
				else if (key == down) {
					color_choose();
					break;
				}
			}
			break;
		}
		else if (key == 'B' || key == 'b') {
			system("color df");
			sure();
			while (1) {
				key = getch();
				if (key == up) {
					theme = Tadv;
					break;
				}
				else if (key == down) {
					color_choose();
					break;
				}
			}
			break;
		}
		else if (key == 'C' || key == 'c') {
			system("color 8f");
			sure();
			while (1) {
				key = getch();
				if (key == up) {
					theme = Tele;
					break;
				}
				else if (key == down) {
					color_choose();
					break;
				}
			}
			break;
		}
		else if (key == 'D' || key == 'd') {
			system("color 70");
			sure();
			while (1) {
				key = getch();
				if (key == up) {
					theme = Tnor;
					break;
				}
				else if (key == down) {
					color_choose();
					break;
				}
			}
			break;
		}
	}
}

void language_choose() {
	cout << "选择语言(Choose language)：按↑选择中文，按↓选择英文(Press [up button] to choose Chinese and press [down button] to choose English)\n";
	while (1) {
		key = getch();
		if (key == up) {
			language = cn;
			break;
		}
		else if (key == down) {
			language = en;
			break;
		}
	}
}

void name_choose() {
	if (language == cn)cout << "\n请输入宠物名称：\n";
	else if (language == en)cout << "\nInput the name of your digital pet:\n";
	getline(cin, name);
	while (1) {
		if (name != "" && name != " " && name != "  " && name != "   " && name != "    ")break;
		else {
			if (language == cn)cout << "请重新输入：";
			else if (language == en) cout << "Please input again:";
			getline(cin, name);
		}
	}
	if (name == "毛茛" || name == "毛艮" || name == "morgan" || name == "Morgan") name = "比利";
	if (name == "Rick" || name == "Joker") name = "杀人犯";
	pause(1);
	if (language == cn)cout << "“" << name << "”你想到，";
	else if (language == en)cout << "'" << name << "' you thought.";
	if (name == "比利")cout << "这真是一个疯狂的名字。\n";
	else if (name == "杀人犯")cout << "这像是一个杀人犯的名字。\n";
	else {
		if (language == cn)cout << "这真是一个好名字。\n";
		else if (language == en)cout << "What a good name this is.\n";
	}
}

//提示
void still_buy() {
	if (language == cn)cout << "继续购买？";
	else if (language == en)cout << "Continue to buy?";
	sure(false);
}

void choose_again() {
	if (language == cn)cout << "请重新选择！\n";
	else if (language == en)cout << "Please choose again!\n";
}

void your_pet() {
	if (language == cn)cout << "你的宠物";
	else if (language == en)cout << "Your pet ";
	cout << name;
	if (language == en)cout << " ";
}

void hap_plus(int hapin) {
	colorc(green);
	if (language == cn)cout << "增加快乐值【+" << hapin << "】！\n";
	else if (language == en)cout << "Happiness [+" << hapin << "]!\n";
	colorc(white);
}

void hap_minus(int hapout) {
	colorc(red);
	if (language == cn)cout << "快乐值【-" << hapout << "】！\n";
	else if (language == en)cout << "Happiness [-" << hapout << "]!\n";
	colorc(white);
}

void lifespan_plus(int lifespanin) {
	colorc(red);
	if (language == cn)cout << "寿命增加所需的快乐值【+" << lifespanin << "】！\n";
	else if (language == en)cout << "Happiness needed to increase lifespan [+" << lifespanin << "]!\n";
	colorc(white);
}

void lifespan_minus(int lifespanout) {
	colorc(green);
	if (language == cn)cout << "寿命增加所需的快乐值【-" << lifespanout << "】！\n";
	else if (language == en)cout << "Happiness needed to increase lifespan [-" << lifespanout << "]!\n";
	colorc(white);
}

void sad_plus(int sadin) {
	colorc(red);
	if (language == cn)cout << "悲伤值【+" << sadin << "】！\n";
	else if (language == en)cout << "Sadness [+" << sadin << "]!\n";
	colorc(white);
}

void sad_minus(int sadout) {
	colorc(green);
	if (language == cn)cout << "悲伤值【-" << sadout << "】！\n";
	else if (language == en)cout << "Sadness [-" << sadout << "]!\n";
	colorc(white);
}

void money_plus(int monin) {
	colorc(green);
	if (language == cn)cout << "金钱【+" << monin << "】！\n";
	else if (language == en)cout << "$ [+" << monin << "]!\n";
	colorc(white);
}

void money_minus(int monout) {
	colorc(red);
	if (language == cn)cout << "金钱【-" << monout << "】！\n";
	else if (language == en)cout << "$ [-" << monout << "]!\n";
	colorc(white);
}

void money_not() {
	colorc(red);
	if (language == cn)cout << "抱歉，你没有足够金钱！\n";
	else if (language == en) cout << "Sorry, but you don't have enough money!\n";
	colorc(white);
}

void money_have() {
	colorc(blue);
	if (language == cn) cout << "你有" << money << "元钱！\n";
	else if (language == en)cout << "You have $ " << money << " !\n";
	colorc(white);
}

void bought_success() {
	colorc(blue);
	if (language == cn)cout << "已成功购买！\n";
	else if (language == en) cout << "Bought successfully!\n";
	colorc(white);
}