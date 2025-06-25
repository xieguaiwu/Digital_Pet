/*
* @Author: 战略教授
* @Date:   2025-06-08 22:35:12
* @Last Modified by:   Wang Ziyan
* @Last Modified time: 2025-06-20 13:08:32
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

int lifespan;//宠物寿命天数，可增加！
int Mlifespan;//极限最大寿命
int Llifespan;//最短寿命

const int pers = 2; //性格随机数
const int events = 6; //随机事件的个数
int randomnum;//随机数的返回值
int days = 1; //天数
bool died = false;


int turns = 1; //每一天有8次操作机会
//作弊码变量
string cheating;
const bool cheatable = true;
int Mopluse;
bool Bband = false; //是否已经完成了随机事件4


//随机事件二变量：
bool cheat = false;
bool loser = false;
bool invest = false; //随机事件二的变量，是否投资
int Iinvest;//投资的金额
int IINVEST;
int Dinvest;//投资等待的天数
float Einvest;//投资的收益率
//随机事件三变量
const int price_mouse = 90, price_slipper = 20, price_heartsaver = 10000, price_lone = 10;

//道具-价格
const int price_pbutter = 35, price_mbutter = 50;

//烹饪变量-价格
const int price_sug = 8, price_sod = 9, price_wat = 0, price_flo = 6;
//烹饪变量-拥有
long long sug;//糖
long long sul;//盐
long long sod;//苏打
long long wat;//水
long long flo;//面粉
//烹饪变量-加入
long long Isug;//糖
long long Isul;//盐
long long Isod;//苏打
long long Iwat;//水
long long Iflo;//面粉

//烹饪变量
int calr;//热量
string Meal;//烹饪品总名称（口味+名称）
map<int, string> meal;//烹饪品名称
map<int, string> Tmeal;//烹饪品口味
//烹饪变量-存储
int Cid = 0; //用于记录项数
vector<string> backpackmeal;//菜品名称
vector<int> backpackcalr;//菜品对应的热量
vector<int> backpackspend;//菜品对应的制作成本，在之后的进一步更新中使用
vector<int> backpackall;//菜品对应的总量
vector<float> backpackeffect;//菜品效果
map<float, string>effects;//菜品效果储存
int Crow;//用于进行循环
int CTP;//用于进行选择

int r_events(int sss = 0, int Mranding = 0, int Lranding = 0) { //随机数生成，用于随机事件和随机性格等
	if (sss == 0) {
		return 1 + rand() % (events); //生成 随机事件
	}
	else if (sss == 1) {
		return rand() % (pers-1); //生成 随机性格
	}
	else {
		//if(Mranding<Lranding)cout <<"随机数生成错误！\n";
		return Lranding + rand() % (Mranding); //其余的生成
	}
}

int cook(long long Psug, long long Psul, long long Psod, long long Pwat, long long Pflo, int cs = 0) { //变量cs：函数的类型
	Msug = Psug; Msul = Psul; Msod = Psod; Mwat = Pwat; Mflo = Pflo;
	Camount = Psug + Psul + Psod + Pwat + Pflo;
	if (cs == 0) { //烹饪
		if (Psug == 0 && Psul == 0 && Psod == 0 && Pwat == 0 && Pflo == 0) {
			if (language == cn)cout << "经过了一番对不存在的火焰的精确把控、不存在的铁锅耐心翻炒，以及对不存在的食材的精心搭配，你成功制作出了……";
			else if (language == en)cout << "After precisely controlling the invisible fire, consistly modifying the temperature of the non-existent frying pan, and the combination of the imaginary delicate seasonings, you successfully made a dish of...";
			Ncook = air;
			return Ncook;
		} else {
			int Rcook = 1 + rand() % (3);
			if (Rcook == 1) {
				if (language == cn)cout << "低端恶心的食材往往不需要经过烹饪——你直接将一堆无机物（请忽略面粉）丢进锅里。\n几小时后，你发现自己好吃极了。在自我烹饪时，你发现自己已经成功制作出了……";
				else if (language == en)cout << "You throw a bunch of inorganic substance (except for the flour) into the pot. Few hours later, you find yourself very tasty. When cooking yourself, you find out that you have already cooked...";
			}
			if (Rcook == 2) {
				if (language == cn)cout << "你细心地把一堆东西丢进锅里，用奇妙的手段烹饪。接着，你发现烹饪毫无意义。\n几分钟后，你发现锅铲变得十分好吃。在尝试咀嚼锅铲的同时，你发现自己成功烹饪出了……";
				else if (language == en)cout << "You carefully throw a bunch of materials into the pot, and cook them with strange approaches. A few minutes later, you find the turner very tasty. When trying to chew the turner, you find yourself successfully cooked...";
			}
			if (Rcook == 3) {
				if (language == cn)cout << "在丢尽一堆恶心的无机物后，你被烟连续呛了两个小时。\n在两个小时的烟熏后，你彻底熟透了。与此同时，你成功发明出了……";
				else if (language == en)cout << "After throwing a bunch of disgusting inorganic substance, you are chocked by the smoke for two whole hours, and you find yourself totally cooked. In the mean time, you successfully invented...";
			}
		}
	}
	else if (cs == 1) { //评定热量 （每克糖含有4点热量；和水交融的面粉成为面糊，每克含有2点热量，干面粉每克含有4点热量）
		Mcalr = Psug * 4;
		if (Pwat > Pflo)Mcalr = Mcalr + Pflo * 2;
		else Mcalr = Mcalr + Pwat * 2 + (Pflo - Pwat) * 4;
		return Mcalr;
	}
}

bool Vacheve = false;
void notice() {
	if (language == cn) {
		cout << "\n按下Q退出\n按下F喂食\n按下I与宠物互动\n按下C查看宠物状态\n按下S清屏\n按下M进行【购买】、【借贷】或【烹饪】\n按下B查看你已经拥有的【烹饪食材】\n";
		cout << "按下O查看你制作的烹饪品\n按下X重新设置主题颜色\n按下“?”查看教程\n"; //<<"按下K进入存档界面\n";
	}
	else if (language == en) {
		cout << "\nPRESS 'Q' TO QUIT\nPRESS 'F' TO FEED YOUR PET\nPRESS 'I' TO INTERACT WITH YOUR PET\nPRESS 'C' TO CHECK YOUR PET'S STATUS\n";
		cout << "PRESS 'S' TO CLEAR THE SCREEN\nPRESS 'M' TO [PURCHASE], [APPLY FOR LOAN] OR [COOK]\nPRESS 'B' TO CHECK THE [COOKING INGREDIENT] YOU ALREADY HAD\n";
		cout << "PRESS 'O' TO CHECK THE DISHES YOU ALREADY COOKED\nPRESS 'X' TO RESET THE THEME COLOR\nPRESS '?' TO CHECK THE INSTRUCTIONS\n";
	}
	if (invest == true) {
		if (language == cn)cout << "按下V查看【投资情况】\n";
		else if (language == en)cout << "PRESS 'V' TO CHECK THE [STATUS OF INVESTMENT]\n";
		Vacheve = true;
	}
	if (language == cn)cout << "每天有8次按下按键的机会\n还有" << 8 + 1 - turns << "次\n";
	else if (language == en)cout << "There are 8 times to press the key.\nYou have " << 8 + 1 - turns << " times left\n";
}

//前十名单函数
fstream get_save;//读取
int list_id;//前十名单的id
int list_row;//进行循环
void list_read() {//读取
	get_save.open("top10\\Lid.txt");
	get_save >> list_id; //读取list_id
	get_save.close();
}

void list_write() {//写入
	get_save.open("top10\\Lid.txt");
	get_save << list_id; //写入list_id
	get_save.close();
}

/*void list_queue() {

}*/

//烹饪函数（由烹饪头文件而来的翻译器）
void Cpushback(string bloodyname, int bloodycalr, int bloodyspend, int bloodyall, float bloodyeffect) {//存储
	backpackmeal.push_back(bloodyname);
	backpackcalr.push_back(bloodycalr);
	backpackspend.push_back(bloodyspend);
	backpackall.push_back(bloodyall);
	backpackeffect.push_back(bloodyeffect);
	Cid++;
}

void Cclean() {//清空
	Crow = 1;
	while (1) {
		if (Crow == Cid)break; //backpackmeal从0开始
		backpackmeal[Crow - 1] = "";
		Crow++;
	}
	Cid = 0;
}

void Cdrop(int IDI) {//除去 IDI=id of the dropped item
	backpackmeal[IDI] = "";
	Cid = Cid - 1;
	Crow = IDI;
	while (1) {
		if (Crow == Cid)break; //注意，此处Crow等于Cid，相当于把最后一个物品赋值为0
		backpackmeal[Crow] = backpackmeal[Crow + 1];
		backpackcalr[Crow] = backpackcalr[Crow + 1];
		backpackspend[Crow] = backpackspend[Crow + 1];
		backpackall[Crow] = backpackall[Crow];
		Crow++;
	}
}

void Mname() {
	if (language == cn) {
		meal[0] = "空气";
		meal[1] = "苏打水";
		meal[2] = "不可名状的黑焦色物体";
		meal[3] = "面糊";
		meal[4] = "面包";
		meal[5] = "带水的苏打";
		meal[6] = "蛋糕";
	}
	else if (language == en) {
		meal[0] = "air";
		meal[1] = "soda water";
		meal[2] = "unnamable black item";
		meal[3] = "paste";
		meal[4] = "bread";
		meal[5] = "soda with water";
		meal[6] = "cake";
	}
}

void Mname1() {
	if (language == cn) {
		Tmeal[10] = "有些甜腻的";
		Tmeal[11] = "有些咸的";
		Tmeal[12] = "有些湿乎乎的";
		Tmeal[13] = "充满气体的";
		Tmeal[14] = "平淡的";
		Tmeal[15] = "软绵绵的";
		Tmeal[16] = "非常甜腻的";
		Tmeal[17] = "非常咸的";
		Tmeal[18] = "非常湿乎乎的";
		Tmeal[19] = "非常软绵绵的";
		Tmeal[20] = "有些干的";
	}
	else if (language == en) {
		Tmeal[10] = "a bit too sweet";
		Tmeal[11] = "a bit too salty";
		Tmeal[12] = "a bit too drippy";
		Tmeal[13] = "filled with gas";
		Tmeal[14] = "plain";
		Tmeal[15] = "soft";
		Tmeal[16] = "incredibly sweet";
		Tmeal[17] = "incredibly salty";
		Tmeal[18] = "incredibly drippy";
		Tmeal[19] = "incredibly soft";
		Tmeal[20] = "a bit dry";
	}
}

void Ename() {	//菜品效果名称
	//寿命
	if (language == cn) {
		effects[0.1] = "寿命【+1】";
		effects[0.2] = "寿命【+2】";
		effects[-0.1] = "寿命【-1】";
		effects[-0.2] = "寿命【-2】";
	}
	else if (language == en) {
		effects[0.1] = "Lifespan [+1]";
		effects[0.2] = "Lifespan [+2]";
		effects[-0.1] = "Lifespan [-1]";
		effects[-0.2] = "Lifespan [-2]";
	}
	//生命值
	if (language == cn) {
		effects[1.10] = "快乐值【+10】";
		effects[1.15] = "快乐值【+15】";
		effects[-1.10] = "快乐值【-10】";
		effects[-1.15] = "快乐值【-15】";
		effects[2.5] = "快乐值上限【+5】";
		effects[2.15] = "快乐值上限+15";
		effects[-2.5] = "快乐值上限【-5】";
		effects[-2.15] = "快乐值上限【-15】";
	}
	else if (language == en) {
		effects[1.10] = "Happiness [+10]";
		effects[1.15] = "Happiness [+15]";
		effects[-1.10] = "Happiness [-10]";
		effects[-1.15] = "Happiness [-15]";
		effects[2.5] = "Limit of happiness [+5]";
		effects[2.15] = "Limit of happiness [+15]";
		effects[-2.5] = "Limit of happiness [-5]";
		effects[-2.15] = "Limit of happiness [-15]";
	}
	//悲伤值
	if (language == cn) {
		effects[3.5] = "悲伤值【+5】";
		effects[3.8] = "悲伤值【+8】";
		effects[-3.5] = "悲伤值【-5】";
		effects[-3.8] = "悲伤值【-8】";
		effects[4.5] = "悲伤值上限【+5】";
		effects[4.10] = "悲伤值上限+10";
		effects[-4.5] = "悲伤值上限【-5】";
		effects[-4.10] = "悲伤值上限【-10】";
	}
	else if (language == en) {
		effects[3.5] = "Sadness [+5]";
		effects[3.8] = "Sadness [+8]";
		effects[-3.5] = "Sadness [-5]";
		effects[-3.8] = "Sadness [-8]";
		effects[4.5] = "Limit of Sadness [+5]";
		effects[4.10] = "Limit of Sadness [+10]";
		effects[-4.5] = "Limit of Sadness [-5]";
		effects[-4.10] = "Limit of Sadness [-10]";
	}
	//平淡的
	if (language == cn)effects[5.0] = "无效果";
	else if (language == en)effects[5.0] = "no effect";
}

void Csug() {
	if (sug <= 0) {
		sug = 0;
	}
}

void Csod() {
	if (sod <= 0) {
		sod = 0;
	}
}

void Csul() {
	if (sul <= 0) {
		sul = 0;
	}
}

void Cwat() {
	if (wat <= 0) {
		wat = 0;
	}
}

void Cflo() {
	if (flo <= 0) {
		flo = 0;
	}
}

void Cfour() {
	Csod(); Csul(); Csug(); Cwat(); Cflo();
}

bool Jcook = false; //在烹饪时切换界面用的一个变量……
void Cincook() {
	colorc(blue);
	if (language == cn) {
		cout << "你有" << sug << "克糖\n你有" << sul << "克盐\n你有" << sod << "克苏打\n你有" << wat << "毫升水（最多拥有1000毫升）\n你有" << flo << "克面粉\n";
	}
	else if (language == en) {
		cout << "You have " << sug << " grams of sugar\nYou have " << sul << " grams of salt\nYou have " << sod << " grams of soda\nYou have " << wat << " milliliter of water (1000 millilitter max)\nYou have " << flo << " grams of flour\n";
	}
	colorc(white);
	pause();
	if (language == cn)cout << "继续烹饪吗？（按↑继续，按↓退出界面）\n";
	else if (language == en)cout << "Keep cooking? (Press [up button] to continue, press [down button] to quit this menu)\n";
	while (1) {
		key = getch();
		if (key == up) {
			Jcook = false; break;
		}
		if (key == down) {
			Jcook = true; break;
		}
	}
	if (Jcook == false) {
		while (1) {
			if (language == cn)cout << "你要加入多少克糖？输入克数：";
			else if (language == en)cout << "How much sugar do you want to put in？ Input the number of grams:";
			cin >> Isug;
			if (Isug < 0 || Isug > sug)cout << "输入错误！\n";
			else {
				sug = sug - Isug; break;
			}
		}
		while (1) {
			if (language == cn)cout << "你要加入多少克盐？输入克数：";
			else if (language == en)cout << "How much salt do you want to put in？ Input the number of grams:";
			cin >> Isul;
			if (Isul < 0 || Isul > sul)cout << "输入错误！\n";
			else {
				sul = sul - Isul; break;
			}
		}
		while (1) {
			if (language == cn)cout << "你要加入多少克苏打？输入克数：";
			else if (language == en)cout << "How much sodium bicarbonate do you want to put in？ Input the number of grams:";
			cin >> Isod;
			if (Isod < 0 || Isod > sod)cout << "输入错误！\n";
			else {
				sod = sod - Isod; break;
			}
		}
		while (1) {
			if (language == cn)cout << "你要加入多少毫升水？输入毫升数：";
			else if (language == en)cout << "How much water do you want to put in？ Input the number of milliliter:";
			cin >> Iwat;
			if (Iwat < 0 || Iwat > wat)cout << "输入错误！\n";
			else {
				wat = wat - Iwat; break;
			}
		}
		while (1) {
			if (language == cn)cout << "你要加入多少克面粉？输入克数：";
			else if (language == en)cout << "How much flour do you want to put in？ Input the number of grams:";
			cin >> Iflo;
			if (Iflo < 0 || Iflo > flo)cout << "输入错误！\n";
			else {
				flo = flo - Iflo; break;
			}
		}
		cook(Isug, Isul, Isod, Iwat, Iflo, ck);
		if (Isug == 0 && Isul == 0 && Isod == 0 && Iwat == 0 && Iflo == 0)cout << meal[cook(Isug, Isul, Isod, Iwat, Iflo, ck)] << "！\n";
		else {
			Meal = Tmeal[meal_tas()] + meal[meal_nam()];
			cout << Meal << "！\n"; calr = cook(Isug, Isul, Isod, Iwat, Iflo, cr);
			if (language == cn)cout << "这项菜品的热量是" << calr << "点！\n";
			else if (language == en)cout << "The energy of this dish is " << calr << " calories!\n";
			Cpushback(Meal, calr, Isug * 8 + Isul * 13 + Isod * 9, meal_all(), meal_effect()); //盐的价格是6~21的随机数，取中间值13.5的整数部分13元
		}
	} else {
		Jcook = false;
	}
	hyphen(4);
}


//宠物指标
int age = 0; //年龄 10天增加1
int hap = 50; //快乐值 初始100-满
int max_hap = 100; //初始最大值
int sad = 0; //悲伤值 初始50-满
int max_sad = 50; //初始最大值
bool poo = false; //排泄
int w_poo;//排泄忍耐时间 10-满
bool eat = false; //进食 5-满
int w_eat;//进食忍耐时间
bool Pab;//宠物性格

//宠物性格生成
void per() {	//随机生成宠物的性格
	if (language == cn)cout << "你想到你和" << name << "相遇的那个日子：";
	else if (language == en)cout << "You remember the day you met " << name << ":";
	randomnum = r_events(1); //生成随机数
	Pab = randomnum;
	if (Pab == dog) {
		if (language == cn)cout << "在宠物店里，你看见一只小狗。你喜爱它疯狂的狗样子，便把它带回了家。";
		else if (language == en)cout << "You saw a puppy at a pet store. You liked its mad look, so you took it home.";
	}
	else if (Pab == cat) {
		if (language == cn)cout << "在纸箱里，你看见了一只打着呼噜的小猫。你给了它几段香肠，便把它带回了家。";
		else if (language == en)cout << "You saw a snoring pussy in a carton. After giving it some saussages, you took it home.";
	}
	if (language == cn)cout << "如今你已经给它起了名字。\n";
	else if (language == en)cout << "And now you've named it.\n";
}

void r_lifespan() { //随机寿命
	if (Pab == cat) lifespan = 20 + rand() % (40 - 20); //猫的寿命：2~4岁天（可增加）
	else if (Pab == dog) lifespan = 15 + rand() % (50 - 15); //狗的寿命：1岁半到5岁（可增加）
}

//随机事件们
void r1() {		//随机事件1：
	randomnum = r_events(3, 35, 0);		//带回0~35元
	if (randomnum != 0) {
		if (language == cn) {
			cout << "\n这天，你发现你的宠物消失了。几小时后，你的宠物为你带回了" << randomnum << "元！\n金钱增加！\n";
		}
		else if (language == en ) cout << "\n This day, you find that your pet disappered. Few hours later, your pet brings you back $" << randomnum << "!\nMoney increase!\n";
		money = money + randomnum; pause();
	}
}

void r2() {		//随机事件2：宠物的风险投资
	your_pet();
	if (language == cn) {
		cout << "向你走来，手里拿着一张纸，上面写着：\n风险投资\n投资人（物）：" << name << "\n担保人：你\n担保人签名：________\n";
	}
	else if (language == en) {
		cout << "walks to you with a paper, which said:\nVENTURE INVESTMENT\nInvestor:" << name << "\nVoucher: You\nSignature:________\n";
	}
	sure();
	while (1) {
		key = getch();
		if (key == 'H')
		{
			if (language == cn)cout << "你签上了自己的名字。\n";
			else if (language == en)cout << "You sign your name.\n";
			invest = true;
			while (1) {
				if (language == cn)cout << "你要投资的金额";
				else if (language == en)cout << "Input the money you want to invest";
				money_have();
				cin >> Iinvest;
				if (!(Iinvest <= 0)) {
					if (!(Iinvest > money))break;
					else {
						if (language == cn)cout << "你没有那么多钱！你只有" << money << "元！\n\n";
						else if (language == en)cout << "You don't have that much of money! All you have is $ " << money << "!\n\n";
					}
				} else {
					if (Iinvest < 0) {
						if (language == cn)cout << "投资失败，重新输入！\n\n";
						else if (language == en)cout << "Failed to invest, please reenter!\n\n";
					}
					else {
						if (language == cn)cout << "在这千钧一发之际，你放弃了投资！\n";
						else if (language == en)cout << "You give up the investment when it is by a hair!\n";
						break;
					}
				}
			}
			if (Iinvest != 0) {
				if (language == cn)cout << "你投入了" << Iinvest << "元。\n";
				else if (language == en)cout << "You invest $ " << Iinvest << ".\n";
				if (Iinvest == money) {
					if (language == cn) cout << "你的宠物看到你投入了身上的所有钱，十分高兴。\n";
					else if (language == en) cout << "Your pet is very pleased when seeing you invested all your money.\n";
					hap_plus(2);
					sad_minus(3);
					hap += 2; sad = sad - 3;
				}
				money = money - Iinvest;
				IINVEST = Iinvest;
				Dinvest = r_events(3, 2, 1) + days;
				invest = true;
				break;
			} else {
				if (language == cn)cout << "你的宠物看你的眼神像看着一个脑瘫。\n";
				else if (language == en)cout << "Your pet is looking at you as if you are a retard.\n";
				break; invest = false;
			}
		}
		else if (key == 'P') {
			if (language == cn)cout << "你的宠物看你的眼神像看着一个脑瘫。\n";
			else if (language == en)cout << "Your pet is looking at you as if you are a retard.\n";
			break; invest = false;
		}
		cout << "\n\n";
	}
}

bool Phouse = false; //宠物是否有房子
bool Pmouse = false; //是否购买了宠物的老鼠
int Pmouse_plus;//老师给宠物增加的快乐值（1-10随机数）
void r3() { //随机事件3：推销员
	if (language == cn)cout << "你的宠物跑出了家。\n几小时后，你的宠物" << name << "开始敲门。\n是否开门？\n";
	else if (language == en) {
		cout << "Your pet runs out of the house.\nFew hours later, your pet " << name << " starts to knock on the door.\n";
		cout << "Open the door?\n";
	}
	sure();
	while (1) {
		key = getch();
		if (key == 'H') {
			if (language == cn)cout << "你打开了门，";
			else if (language == en)cout << "You open the door, just to realize that";
			randomnum = r_events(114514, 5, 1);
			if (randomnum == 2) {
				if (language == cn)cout << "却发现你的宠物已经吃掉了窗户，进入了房子。\n";
				else if (language == en)cout << "your pet has already eated the window and entered the house.\n";
				poo = true;
			} else {
				if (language == cn)cout << "你的宠物进入了房子。\n";
				else if (language == en)cout << "your pet has already entered the house.\n";
			}
			break;
		}
		else if (key == 'P') {
			if (language == cn) {
				cout << "你假装听不见" << name << "的敲门声。于是你的宠物一口吃掉了门！\n你的宠物感到神清气爽。\n";
			}
			else if (language == en) {
				cout << "You pretend that your can't hear " << name << "'s knocking, so your pet eats up the door!\nYour pet feels refreshed.\n";
			}
			hap_plus(2);
			sad_minus(3);
			hap += 2; sad = sad - 3;
			poo = true;
			break;
		}
		cout << "\n\n";
	}
	if (language == cn)cout << name << "向你出示了它找到的几样物品：\n";
	else if (language == en)cout << name << " showed you few items that it found:\n";
	randomnum = r_events(250, 5, 1);
	if (randomnum == 1 || randomnum == 2) {
		cout << "A."; randomnum = r_events(45, 50, 1);
		if (language == cn)cout << randomnum << "元 价格：10元\nB.不购买\n";
		else if (language == en)cout << "$ " << randomnum << " Price: $ 10\nB.Don't buy anything\n";
		while (1) {
			key = getch();
			if (key == 'A' || key == 'a') {
				if (!(money < 10)) {
					money = money - 10;
					if (language == cn)cout << "你花10元买了" << randomnum << "元，";
					else if (language == en)cout << "You spent $ 10 to but $ " << randomnum << ". ";
					if (randomnum > 10) {
						if (language == cn)cout << "真是一门稳赚不赔的生意！\n";
						else if (language == en)cout << "What a silly great deal!\n";
					}
					if (randomnum == 10) {
						if (language == cn)cout << "真是一门赚不到钱的生意！\n";
						else if (language == en)cout << "What a balanced profit!\n";
					}
					if (randomnum < 10) {
						if (language == cn)cout << "真是一门稳赔不赚的生意！\n";
						else if (language == en)cout << "What a foolish decision!\n";
					}
					money += randomnum;
				} else {
					if (language == cn)cout << "抱歉，你没有足够金钱！\n";
					else if (language == en)money_not();
				}
				break;
			}
			else if (key == 'B' || key == 'b') {
				break;
			}
		}
	}
	if (randomnum == 3 || randomnum == 4) {
		if (language == cn) {
			cout << "A.玩具老鼠（使宠物每天的快乐值增加1~5的随机数）" << price_mouse << "元\nB.拖鞋（使宠物成为有房一族）" << price_slipper << "元\n";
			cout << "C.速效救心丸 " << price_heartsaver << "元\nD.不购买\n";
		}
		else if (language == en) {
			cout << "A.Toy mouse (happiness [+1]~[+5] each day) $ " << price_mouse << "\nB.Slipper (don't you want to buy a house for your pet?) $ " << price_slipper << "\n";
			cout << "C.Heart saver capsule $ " << price_heartsaver << "\nD.Don't buy anything\n";
		}
		while (1) {
			key = getch();
			if (key == 'A' || key == 'a') {
				if (!(money < 90)) {
					if (Pmouse == false) {
						money = money - 90;
						if (language == cn)cout << "你买下了玩具老鼠！\n";
						else if (language == en)cout << "You have bought the toy mouse!\n";
						Pmouse = true;
					} else {
						if (language == cn)cout << "抱歉，你的宠物已经有一个了！\n";
						else if (language == en)cout << "Sorry, but your pet already have one!\n";
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
						if (language == cn)cout << "你买下了拖鞋！\n";
						else if (language == en)cout << "You have bought the slipper!\n";
						Phouse = true;
					} else {
						if (language == cn)cout << "抱歉，你的宠物已经成为有房一族了！\n";
						else if (language == en)cout << "Sorry, but your pet already have one!\n";
					}
				} else {
					money_not();
				}
				break;
			}
			else if (key == 'C' || key == 'c') {
				if (!(money < 10000)) {
					if (language == cn)cout << "抱歉，你没有足够的金钱！继续吗？（↑继续，↓退出）\n";
					else if (language == en)cout << "Sorry, buy you don't have enough money! Continue? (Press [up button] to continue and press [down button] to quit)\n";
					money = money - 10000;
					while (1) {
						key = getch();
						if (key == up) {
							if (language == cn)cout << "禽兽！\n快乐值清零！悲伤值拉满！\n";
							else if (language == en)cout << "MONSTER!\nHappiness = 0! Sadness maximumizes!\n";
							hap = 0; sad = max_sad;
							break;
						}
						else if (key == down) {
							if (language == cn)cout << "你被骗了！\n";
							else if (language == en)cout << "You are scamed!\n";
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
	}
	if (randomnum == 5) {
		if (language == cn)cout << "A.寂寞（让你买个寂寞）10元\nB.不购买\n";
		else if (language == en)cout << "A.Lonliness (buy one when you are on your own) $ " << price_lone << "\nB.Don't buy anything\n";
		while (1) {
			key = getch();
			if (key == 'A' || key == 'a') {
				if (!(money < 10)) {
					money = money - 10;
					if (language == cn)cout << "你买了个寂寞……\n";
					else if (language == en)cout << "You have bought... lonliness...\n";
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
	if (language == cn) {
		cout << "“21st century schizoid pet!”\n你看见你的宠物正举着一把电吉他（正被一把电吉他压在地上），聚光灯照亮了它的眼睛。\n";
	}
	else if (language == en) {
		cout << "\"21st century schizoid pet!\"You see your pet is holding a electric guitar (being overwhelmed under the guitar), and the spotlight shines on its eyes.\n";
	}
	pause();
	if (language == cn) {
		cout << "你热泪盈眶。\n几个星期后，你的宠物再次敲开了家里的门。它告诉你（不要问我它是怎么告诉你的）这场演出取得了巨大的成功。\n";
	}
	else if (language == en)cout << "Tears run out your eyes. Few weeks later, your pet knocks on the door again, and it tells you (don't ask me how) that this performance has made a great success.\n";
	randomnum = r_events(134, 5, 1);
	if (randomnum == 5) {
		BFS = true; randomnum = r_events(214, 3000, 200);
		if (language == cn) {
			cout << "你的宠物成为了亚洲的著名歌星，在今后的每一天，都会有许多狂热歌迷为你们送钱。但你的宠物拒不重回歌坛。\n";
		}
		else if (language == en) {
			cout << "Your pet becomes the next Michael Jackson in the world - in fact, hardly anybody still remembers Michael Jackson now. There are a lot of crazy fans come to send you money everyday after that performance, but your pet mysteriously refuses (don't ask me how) to go back to the business.\n";
		}
	}
	else {
		randomnum = r_events(298, 2000, 100);
	}
	money = money + randomnum;
	if (language == cn) {
		cout << "这场演出一共获得了" << randomnum << "元。为了表达对你的感谢，你的宠物把所有钱都交给了你。\n";
		pause();
		cout << "就这样，你们再次过回了平淡的生活。\n";
	}
	else if (language == en) {
		cout << "The performance earns you $ " << randomnum << " in total. In order to show thankfulness, your pet hands you all the money.\n";
		pause();
		cout << "And so, the both of you come back to your ordinary life.\n";
	}
	hyphen(4);
}

void Binteract() { //随机事件4
	if (key == 'T' || key == 't') {
		if (language == cn)cout << "你打开了电视\n";
		else if (language == en)cout << "You open the YV.\n";
		pause(1);
		randomnum = r_events(1874298, 2, 1);
		if (randomnum == 1)Btv1();
		else if (randomnum == 2)Btv2();
		else if (randomnum == 3)Btv3();
		else if (randomnum == 4)Btv4();
		randomnum = r_events(82734, 4, 1);
		if (randomnum == 2) {
			if (language == cn)cout << "你切换着频道，突然，你看见了……\n\n你的宠物！\n";
			else if (language == en)cout << "You are switching channels, and suddenly, you see...\n\nYour pet!\n";
			pause();
			Bback();
			return;
		}
		else {
			if (language == cn)cout << "你不断切换着频道，但没有看见宠物任何信息……\n";
			else if (language == en)cout << "You keep changing the channels, but can't find any information about your pet...\n";
			pause(1);
		}
	}
	else {
		hyphen(3);
		cout << "\n";
		choose_again();
		if (language == cn)cout << "\n按下T看电视\n每天有1次按下按键的机会\n还有" << 1 + 1 - Bturns << "次\n";
		else if (language == en)cout << "\nPress 't' to watch TV\nThere are 1 chance to watch TV everyday\nYou have " << 1 + 1 - Bturns << " time left\n";
		key = getch(); Binteract();
	}
}

void band_days() {	//随机事件4
	hyphen(2);
	cout << "这是第" << Bdays << "天\n";
	while (1) {
		if (Bturns == 2)break;
		cout << "\n";
		choose_again();
		if (language == cn)cout << "\n按下T看电视\n每天有1次按下按键的机会\n还有" << 1 + 1 - Bturns << "次\n";
		else if (language == en)cout << "\nPlease choose again!\nPress 't' to watch TV\nThere are 1 chance to watch TV everyday\nYou have " << 1 + 1 - Bturns << " time left\n";
		key = getch();
		Binteract();
		if (back == true)break;
		Bturns++;
	}
	Bdays++;
	Bturns = 1;
}

void r4() {//随机事件4：宠物的前卫摇滚乐队
	Bband = true;
	if (language == cn) {
		cout << "这几天以来，你的宠物一直在听一些奇妙的摇滚音乐。\n你时常听见一些似乎是“rape”的单词从" << name << "的嘴中迸发（不要问我动物是如何说话的）\n";
	}
	else if (language == en) {
		cout << "For the past few days, your pet has been listening to some strange rock music.\nYou often hear some words like 'rape' from " << name << "'s mouse (don't ask me how)\n";
	}
	pause();
	if (language == cn) {
		cout << "一天，你的宠物用一些奇妙的方法告诉你了一个消息：它将会创建一只前卫摇滚乐队。\n由于你已经为它投入太多，它将不再会使用你的金钱。\n";
	}
	else if (language == en) {
		cout << "One day, your pet told you through a unimaginable way that it is going to start a progressive rock band.\nBecause you have gave it too much, this band won't cost you any money.\n";
	}
	pause(); eat = false; poo = false;
	if (language == cn) {
		cout << "你在它临行前最后喂食了一次宠物，你的宠物最后一次上了厕所。\n你目送着宠物的离开……\n";
	}
	else if (language == en) {
		cout << "Before it left, you feed your pet for the last time, and let it defecates for the last time.\nYou witness its leave...\n";
	}
	pause(); hyphen(4);
	while (1) {
		band_days();
		if (back == true)break;
	}
}

void r5() {//随机事件5
	randomnum = r_events(123, 5, 1);
	if (language == cn)cout << "\n这天，你发现你的宠物消失了。几小时后，你的宠物为你带回了";
	else if (language == en)cout << "\nToday, you can't find your pet anywhere. Few hours later, your pet brings you back ";
	if (randomnum == 1) { //糖
		randomnum = r_events(1234, 35, 1); //带来1-35个食材
		if (language == cn)cout << randomnum << "克糖！\n";
		else if (language == en)cout << randomnum << " grams of sugar!\n";
		sug += randomnum;
	}
	else if (randomnum == 2) { //盐
		randomnum = r_events(1234, 35, 1); //带来1-35个食材
		if (language == cn)cout << randomnum << "克盐！\n";
		else if (language == en)cout << randomnum << " grams of salt!\n";
		sul += randomnum;
	}
	else if (randomnum == 3) { //苏打
		randomnum = r_events(1234, 35, 1); //带来1-35个食材
		if (language == cn)cout << randomnum << "克苏打！\n";
		else if (language == en)cout << randomnum << " grams of soda!\n";
		sod += randomnum;
	}
	else if (randomnum == 4) { //水
		randomnum = r_events(1234, 35, 1); //带来1-35个食材
		if (language == cn)cout << randomnum << "毫升水！\n";
		else if (language == en)cout << randomnum << " milliliters of water!\n";
		if (wat + randomnum <= 1000)wat += randomnum;
	}
	else if (randomnum == 5) { //面粉
		randomnum = r_events(1234, 35, 1); //带来1-35个食材
		if (language == cn)cout << randomnum << "克面粉！\n";
		else if (language == en)cout << randomnum << " grams of flour!\n";
		flo += randomnum;
	}
	pause();
}

void r_e() {//random events 生成
	if (days >= 1) {
		randomnum = r_events();
		//cout <<randomnum<<"\n";//测试代码
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

//死亡函数
void death() {//宠物的死亡
	hyphen();
	if (language == cn)cout << "你的宠物" << name << "享年" << age << "岁，经历了" << days << "天。\n在死时，" << name;
	else if (language == en) {
		cout << "Your pet " << name << " had been through a life of " << age << " years, and it had been through " << days << " days.\n";
		cout << "When " << name << " was going to die, ";
	}
	if (poo == true) {
		if (language == cn)cout << "仍然想要排泄。\n";
		else if (language == en)cout << "it still wants to defecate.\n";
	}
	if (eat == true) {
		if (language == cn)cout << "仍然十分饥饿。\n";
		else if (language == en)cout << "it is still very hungry.\n";
	}
	if (language == cn)cout << "在死时，" << name;
	else if (language == en)cout << "When it was going to die, " << name << " ";
	if (sad >= 38 && sad < 42 && hap < 50) {
		if (language == cn)cout << "有些悲伤。\n";
		else if (language == en)cout << "was a bit sad.\n";
	}
	if (sad >= 42 && hap < 50) {
		if (language == cn)cout << "十分抑郁。\n";
		else if (language == en)cout << "was very depressed.\n";
	}
	if (hap >= 50 && hap < 76 && sad < 38) {
		if (language == cn)cout << "很开心。\n";
		else if (language == en)cout << "was quite happy.\n";
	}
	if (hap >= 76 && sad < 38) {
		if (language == cn)cout << "十分快乐。\n";
		else if (language == en)cout << "was very happy.\n";
	}
	if (hap >= 50 && sad >= 38) {
		if (language == cn)cout << "内心矛盾。\n";
		else if (language == en)cout << "was confused.\n";
	}
	died = true;
	pause(1);
}

//情感函数
void e_poo() {
	if (w_poo > 10) {
		w_poo == 10;
	} else {
		if (w_poo > 5) {
			if (w_poo < 8) {
				hap = hap - 5; sad = sad + 3;
			}
			if (w_poo >= 8) {
				hap = hap - 8; sad = sad + 6;
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
				hap = hap - 4; sad = sad + 5;
			}
			if (w_eat >= 4) {
				hap = hap - 8; sad = sad + 7;
			}
		}
	}
}

void e_age() {
	if (days != 0 && days % 10 == 0) {
		age++;
		your_pet();
		if (language == cn)cout << "长大了一岁！\n";
		else if (language == en)cout << "is 1 year older!\n";
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
		if (language == cn)cout << "抑郁过度，自杀了。\n";
		else if (language == en)cout << "is so depressed that it committed suicide.\n";
		death();
	}
}

bool Lifespanup_turns = false; //是否在单回合内已经增加了寿命
int Lifespanhap;//生命上限所需的快乐值的初始值是一个85-60之间的随机数
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
				if (hap >= Lifespanhap && sad <= 15) { //快乐值>=寿命增加所需的快乐值且悲伤值小于等于15，寿命增加一天
					if (turns == 2 || turns == 4 || turns == 6 || turns == 8) {
						if (Lifespanup_turns == false) {
							if (language == cn)cout << "宠物寿命增【+1】天！\n";
							else if (language == en)cout << "Your pet's lifespan increace by 1 day!\n";
							lifespan++; Lifespanup_turns = true;
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

//金钱函数
int cheatmoney;
int uglyprice;//随机数价格
int gs;//购买克数
void M_notice() {
	if (gs < 0) {
		if (language == cn)cout << "请重新输入！\n";
		else if (language == en)cout << "Please input again!\n";
	}
	else if (gs == 0) {
		if (language == cn)cout << "你放弃了购买。\n";
		else if (language == en)cout << "You give up to buy.\n";
	}
}

void M_cok() {  //食材
	while (1) {
		money_have();
		if (language == cn) {
			cout << "食材：\nA.糖 " << price_sug << "元每克\nB.盐 6到21元每克\nC.苏打 " << price_sod << "元每克\nD.水 " << price_wat << "元每毫升\nE.面粉 " << price_flo << "元每克\nF.空气 20到900元每立方米\nG.退出界面\n";
		}
		else if (language == en) {
			cout << "Cooking ingredients:\nA.Sugar $ " << price_sug << " per gram\nB.Salt $ 6~12 per gram\nC.Soda $ " << price_sod << " per gram\n";
			cout << "D.Water $ " << price_wat << " per milliliter\nE.Flour $ " << price_flo << " per gram\nF.Air $ 20~900 per square meter\nG.Quit this menu\n";
		}
		key = getch();
		if (key == 'A' || key == 'a') {
			uglyprice = 8;
			while (1) {
				if (language == cn)cout << "输入购买克数：";
				else if (language == en)cout << "Input the number of grams you want to buy:";
				cin >> gs;
				M_notice();
				if (gs == 0) {
					pause(); turns--; break;
				}
				else {
					if (money >= gs * uglyprice) {
						if (language == cn)cout << "已成功购买" << gs << "克糖！\n";
						else if (language == en)cout << "You have successfully bought " << gs << " grams of sugar!\n";
						money = money - gs * uglyprice; sug += gs; pause(); break;
					} else {
						if (language == cn)cout << "抱歉，金钱不足！" << "\n";
						else if (language == en)money_not();
						pause(); break;
					}
				}
			}
			system("cls");
		}
		else if (key == 'B' || key == 'b') {
			uglyprice = r_events(123, 21 - 6, 6);
			if (language == cn)cout << "价格：" << uglyprice << "\n";
			else if (language == en)cout << "Price: $ " << uglyprice << "\n";
			still_buy();
			while (1) {
				key = getch();
				if (key == up) {
					while (1) {
						if (language == cn)cout << "输入购买克数：";
						else if (language == en)cout << "Input the number of grams you want to buy:";
						cin >> gs;
						M_notice();
						if (gs == 0) {
							pause(); turns--; break;
						} else {
							if (money >= gs * uglyprice) {
								if (language == cn)cout << "已成功购买" << gs << "克盐！\n";
								else if (language == en)cout << "You have successfully bought " << gs << " grams of salt!\n";
								money = money - gs * uglyprice; sul += gs; pause(); break;
							} else {
								money_not();
								pause(); break;
							}
						}
					}
					system("cls"); break;
				}
				else if (key == down) {
					system("cls"); break;
				}
			}
		}
		else if (key == 'C' || key == 'c') {
			uglyprice = 9;
			while (1) {
				if (language == cn)cout << "输入购买克数：";
				else if (language == en)cout << "Input the number of grams you want to buy:";
				cin >> gs;
				M_notice();
				if (gs == 0) {
					pause(); turns--; break;
				}
				else {
					if (money >= gs * uglyprice) {
						if (language == cn)cout << "已成功购买" << gs << "克苏打！\n";
						else if (language == en)cout << "You have successfully bought " << gs << " grams of soda!\n";
						money = money - gs * uglyprice; sod += gs; pause(); break;
					} else {
						money_not();
						pause(); break;
					}
				}
			}
			system("cls");
		}
		else if (key == 'D' || key == 'd') {
			while (1) {
				if (language == cn)cout << "输入购买毫升数：";
				else if (language == en)cout << "Input the number of milliliters you want to buy:";
				cin >> gs;
				if (wat < 1000 && wat + gs <= 1000) {
					wat += gs;
					if (language == cn)cout << "成功购买" << gs << "毫升水！\n";
					else if (language == en)cout << "You have successfully bought " << gs << " milliliters of water!\n";
					hyphen(4); break;
				}
				else {
					if (language == cn)cout << "抱歉，你已经有够多水了！\n";
					else if (language == en)cout << "Sorry, but you have had enough water!\n";
					hyphen(4); break;
				}
			}
			pause();
			system("cls");
		}
		else if (key == 'E' || key == 'e') {
			uglyprice = 6;
			while (1) {
				if (language == cn)cout << "输入购买克数：";
				else if (language == en)cout << "Input the number of grams you want to buy:";
				cin >> gs;
				M_notice();
				if (gs == 0) {
					pause(); turns--; break;
				}
				else {
					if (money >= gs * uglyprice) {
						if (language == cn)cout << "已成功购买" << gs << "克面粉！\n";
						else if (language == en)cout << "You have successfully bought " << gs << " grams of flour!\n";
						money = money - gs * uglyprice; flo += gs; pause(); break;
					} else {
						money_not();
						pause(); break;
					}
				}
			}
			system("cls");
		}
		else if (key == 'F' || key == 'f') {
			uglyprice = r_events(123, 900 - 20, 20);
			if (language == cn)cout << "价格：" << uglyprice << "\n";
			else if (language == en)cout << "Price: $ " << uglyprice << "\n";
			still_buy();
			while (1) {
				key = getch();
				if (key == up) {
					while (1) {
						if (language == cn)cout << "输入购买毫升数：";
						else if (language == en)cout << "Input the number of milliliters you want to buy:";
						cin >> gs;
						M_notice();
						if (gs == 0) {
							pause(); turns--; break;
						}
						else {
							if (money >= gs * uglyprice) {
								if (language == cn)cout << "已成功购买" << gs << "立方米空气！\n";
								else if (language == en)cout << "You have successfully bought " << gs << " square meters of air!\n";
								money = money - gs * uglyprice; pause(); break;
							} else {
								money_not(); pause(); break;
							}
						}
					}
					system("cls"); break;
				}
				else if (key == down) {
					system("cls"); break;
				}
			}
		}
		else if (key == 'G' || key == 'g') {
			hyphen(4);
			break;
		}
	}
}

void M_stu() {	//道具
	while (1) {
		money_have();
		if (language == cn) {
			cout << "道具：\nA.一种植物——毛茛（宠物悲伤值【-8】） " << price_pbutter << "元\nB.一种疯狂——毛茛（宠物悲伤值【-15】）" << price_mbutter << "元\n";
			cout << "C.砒霜（需要在进行投资的情况下使用。投资成功率【+50】%）价格是自身金钱（加上已经用于投资的金钱）除以5后减去一个随机数（1~自身金钱除以20）";
			cout << "\nD.钻石（需要在进行投资的情况下使用。投资百分百失败）价格是自身金钱的十倍\nE.退出页面\n";
		}
		else if (language == en) {
			cout << "Props:\nA.Buttercup - a kind of plant (Sadness [-8]) $ " << price_pbutter << "\nB.Buttercup - a kind of madness (Sadness [-15]) $ " << price_mbutter << "\n";
			cout << "C.Arsenic (Use it when investing. Rate of success [+50]%) Price: (all the money you have, including money for investment)/5, then minus a random number (1~(money you have)/20)";
			cout << "\nD.Diamond (use it when investing, so the [investment will fail 100%]) Price: (all the money you have, including money for investment)*10\nE.Quit this menu\n";
		}
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
				if (language == cn)cout << "这次的价格是：" << cheatmoney << "\n";
				else if (language == en)cout << "This time the price is $ " << cheatmoney << "\n";
				sure();
				while (1) {
					key = getch();
					if (key == 'H') {
						if (!(money < cheatmoney)) {
							if (invest == false) {
								if (language == cn)cout << "抱歉，你没有投资！\n";
								else if (language == en)cout << "Sorry, but you don't have any investment!\n";
							} else {
								if (cheat == true) {
									if (language == cn)cout << "抱歉，你已经购买了此道具！\n";
									else if (language == en)cout << "Sorry, buy you have already bought this prop!\n";
								}
								else if (loser == true) {
									if (language == cn)cout << "抱歉，但你已经买过另一款道具了……\n";
									else if (language == en)cout << "Sorry, but you have already bought another prop...\n";
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
				if (language == cn)cout << "你没有钱！\n";
				else if (language == en)cout << "You don't have any money at all!\n";
				hyphen(4); hyphen(4);
			}
		}
		else if (key == 'D' || key == 'd') {
			if (!(money <= 0)) {
				if (language == cn)cout << "价格是" << money * 10 << "\n";
				else if (language == en)cout << "This time the price is $ " << money * 10 << "\n";
				still_buy();
				while (1) {
					key = getch();
					if (key == 'H') {
						if (money < money * 10 == false) {
							if (language == cn)cout << "你做了什么？！\n";
							else if (language == en)cout << "What the hell have you done to the code?!\n";
							hyphen(250);
							if (invest == false) {
								if (language == cn)cout << "抱歉，你没有投资！\n";
								else if (language == en)cout << "Sorry, but you don't have any investment!\n";
							} else {
								if (loser == true) {
									if (language == cn)cout << "抱歉，你已经购买了此道具！\n";
									else if (language == en)cout << "Sorry, buy you have already bought this prop!\n";
								}
								else if (cheat == true) {
									if (language == cn)cout << "抱歉，但你已经买过另一款道具了……\n";
									else if (language == en)cout << "Sorry, but you have already bought another prop...\n";
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
				if (language == cn)cout << "你没有钱！\n";
				else if (language == en)cout << "You don't have any money at all!\n";
				hyphen(4); hyphen(4);
			}

		}
		else if (key == 'E' || key == 'e') {
			hyphen(4);
			break;
		}
	}
}

bool det = false; //是否借贷
int Mdet;//借贷金额
int Pdet;//还债金额
float Edet;//借贷利息
int Ddet;//还债期限
bool Ldet = false; //是否拖欠贷款
void M_det() {		//借贷
	hyphen();
	if (det == false) {
		while (1) {
			if (language == cn)cout << "输入借贷金额（不能超过已有金钱的十倍）：\n";
			else if (language == en)cout << "Input the amount of loan you want to apply for (no more than (all the money you have)*10):\n";
			cin >> Mdet;
			if (!(Mdet <= 0)) {
				if (!(Mdet > 10 * money) && money != 0) {
					Ddet = r_events(3, 10, 1);
					Edet = r_events(3, 10, 1);
					if (language == cn) {
						cout << "借款金额" << Mdet << "/总利息" << Edet << "%/还债期限" << Ddet << "天\n每超过一天【+" << Edet << "】%！\n";
					}
					else if (language == en) {
						cout << "Loan $ " << Mdet << "/Total interest " << Edet << "%/On the terms of " << Ddet << " days\nEach day after that [+" << Edet << "]%!\n";
					}
					sure();
					while (1) {
						key = getch();
						if (key == 'H') {
							money_plus(Mdet);
							money = money + Mdet; Ddet = Ddet + days; Pdet = Mdet; det = true; Edet = Edet / 100;
							break;
						} if (key == 'P') {
							if (language == cn)cout << "你放弃了协议。\n";
							else if (language == en)cout << "You give up the contract.\n";
							Mdet = 0; Edet = 0; Ddet = 0; break;
						}
					}
				} else {
					if (money == 0) {
						if (language == cn)cout << "抱歉，但银行不会相信一个一分钱没有的疯子！\n";
						else if (language == en)cout << "Sorry if this is offensive (obviously this is), but the bank won't trust a nut who don't even have a dime!\n";
					} else {
						if (language == cn)cout << "抱歉，你的借贷金额超过了你已有金钱的十倍！\n";
						else if (language == en)cout << "Sorry, but this is obviously more than ten times of all the money you have!\n";
					}
					turns--;
				}
				hyphen(4);
				break;
			} else {
				if (Mdet == 0) {
					if (language == cn)cout << "你放弃了借贷\n";
					else if (language == en)cout << "You give up the loan\n";
					turns--; break;
				}
				if (Mdet < 0) {
					if (language == cn)cout << "金额错误，请重新输入！\n";
					else if (language == en)cout << "The number is wrong, please input again!\n";
					hyphen(4);
				}
			}
		}
		hyphen(4);
	} else {
		if (language == cn)cout << "抱歉，你已经借贷了！\n";
		else if (language == en)cout << "Sorry, but you have already appied for a loan!\n";
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
				if (language == cn)cout << "\n\n你需要偿还银行" << Pdet << "元，是否偿还？（按下↑确定，按↓拒绝）\n";
				else if (language == en)cout << "\n\nYou need to pay the bank $ " << Pdet << ", are you going to pay? (Press [up button] to confirm, and press [down button] to refuse)\n";
				while (1) {
					key = getch();
					if (key == 'H') {
						if (money >= Pdet) {
							if (language == cn)cout << "你偿还了贷款。\n";
							else if (language == en)cout << "You have pay off the loan.\n";
							det = false; Pdet = 0; Ldet = false; Edet = 0; money = money - Pdet;
						} else {
							if (language == cn)cout << "抱歉，你没有能力偿还债款！\n几个银行职员在你家门口将你和你的宠物臭骂一顿。\n";
							else if (language == en)cout << "Sorry, but you don't have enough money to pay!\nA few bank clerks are scolding you and your pet at your front door.\n";
							sad_plus(15);
							hap_minus(10);
							hap = hap - 10;
							sad += 15;
						}
						hyphen(3); Dgm = false;
						break;
					}
					if (key == 'P') {
						if (language == cn)cout << "你拒绝偿还债款。几个银行职员在你家门口将你和你的宠物臭骂一顿。\n";
						else if (language == en)cout << "You refuse to pay.\nA few bank clerks are scolding you and your pet at your front door.\n";
						sad_plus(15);
						hap_minus(10);
						sad += 15;
						hap = hap - 10;
						hyphen(3); Dgm = false;
						break;
					}
				}
			}
		} else {
			if (days == Ddet) {
				Pdet = Pdet + Edet * Pdet;
				if (language == cn)cout << "还债期限已到，你需要偿还银行" << Pdet << "元，是否偿还？（按下↑确定，按↓拒绝）\n";
				else if (language == en)cout << "\n\nIt's time for you to pay back. You need to pay the bank $ " << Pdet << ", are you going to pay? (Press [up button] to confirm, and press [down button] to refuse)\n";
				while (1) {
					key = getch();
					if (key == 'H') {
						if (money >= Pdet) {
							if (language == cn)cout << "你偿还了贷款。\n由于你的诚信，\n";
							else if (language == en)cout << "You pay off the load. Because of your honesty,\n";
							hap_plus(2);
							sad_minus(1);
							hap += 2; sad = sad - 1;
							money = money - Pdet;
							Pdet = 0; det = false; Mdet = 0; Edet = 0; Ddet = 0;
						} else {
							if (language == cn)cout << "抱歉，你没有能力偿还债款！\n每延期一天，你的债款【+" << Edet << "】%！\n";
							else if (language == en)cout << "Sorry, but You don't have enough money to pay!\nEach day after this, your debt [+" << Edet << "]%!\n";
							Mdet = 0; Ddet = 0;
							Ldet = true;
						}
						hyphen(3);
						break;
					}
					if (key == 'P') {
						if (language == cn)cout << "你拒绝偿还债款！\n每延期一天，你的债款【+" << Edet << "】%！\n";
						else if (language == en)cout << "You refuse to pay!\nEach day after this, your debt [+" << Edet << "]%!\n";
						Ldet = true; Mdet = 0; Ddet = 0;
						hyphen(3);
						break;
					}
				}
			}
		}
	}
}

//操作函数
void interact() {
	cout << "\n";
	if (key == 'Q' || key == 'q') {
		if (language == cn)cout << "你退出了\n";
		else if (language == en)cout << "You quit the game.\n";
		pause(4);
	}
	else if (key == 'F' || key == 'f') {
		if (language == cn)cout << "你喂食了宠物\n";
		else if (language == en)cout << "You feed your pet.\n";
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
			if (language == cn) {
				cout << "\n\n互动：\nA.让宠物排泄和排遗\nB.爱抚宠物\nC.退出页面\n";
			}
			else if (language == en) cout << "\n\nINTERACTIONS:\nA.Let your pet to defecate\nB.Pat your pet\nC.Quit this menu\n";
			key = getch();
			if (key == 'A' || key == 'a') {
				if (language == cn)cout << "你让你的宠物" << name << "进行了生物意义上的排遗和排泄的综合性过程\n";
				else if (language == en)cout << "You let your pet " << name << " defecates\n";
				w_poo = 0;
				if (poo == true) {
					hap_plus(1);
					hap++;
				}
				poo = false;
				pause(); break;
			}
			else if (key == 'B' || key == 'b') {
				if (language == cn)cout << "你抚摸了你的宠物" << name << "\n";
				else if (language == en)cout << "You pat your pet " << name << "\n";
				hap += 4; sad = sad - 3;
				hap_plus(4);
				sad_minus(3);
				pause(); break;
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
		if (language == cn)cout << "---寿命---\n";
		else if (language == en)cout << "---LIFESPAN---\n";
		your_pet();
		if (Pab == cat) {
			if (language == cn)cout << "是猫\n";
			else if (language == en)cout << "is a cat.\n";
		}
		else if (Pab == dog) {
			if (language == cn)cout << "是狗\n";
			else if (language == en)cout << "is a dog.\n";
		}
		your_pet();
		if (language == cn)cout << "现在" << age << "岁\n";
		else if (language == en)cout << "is " << age << " years old now\n";
		your_pet();
		if (language == cn)cout << "还能活" << lifespan - days + 1 << "天\n";
		else if (language == en)cout << "can still live for " << lifespan - days + 1 << " days\n";
		your_pet();
		if (language == cn)cout << "需要达到或等于" << Lifespanhap << "点快乐值以上才能使寿命增加\n";
		else if (language == en)cout << "need to have at least reach to [Happiness: " << Lifespanhap << "] to prolong lifespan\n";
		if (language == cn)cout << "---情感---\n";
		else if (language == en)cout << "---EMOTION---\n";
		if (language == cn) {
			cout << "【快乐值：" << hap << "/" << max_hap << "】\n【悲伤值：" << sad << "/" << max_sad << "】\n";
		}
		else if (language == en) {
			cout << "[Happiness: " << hap << "/" << max_hap << "]\n[Sadness: " << sad << "/" << max_sad << "]\n";
		}
		if (language == cn)cout << "---生理---\n";
		else if (language == en)cout << "---PHYSIOLOGY---\n";
		if (language == cn) {
			cout << "想要排泄：";
			if (poo == true) cout << "是\n";
			else cout << "否\n";
		}
		else if (language == en) {
			cout << "Wants to defecate:";
			if (poo == true)cout << "[YES]\n";
			else cout << "[NO]\n";
		}
		if (language == cn) {
			cout << "想要进食：";
			if (eat == true) cout << "【是】\n";
			else cout << "【否】\n";
		}
		else if (language == en) {
			cout << "Wants to eat:";
			if (eat == true) cout << "[YES]\n";
			else cout << "[NO]\n";
		}
		turns--; pause();
	}
	else if (key == 'S' || key == 's') {
		system("cls");
		turns--;
	}
	else if (key == 'M' || key == 'm') {
		while (1) {
			if (language == cn) {
				cout << "你还有" << money << "元钱\n你要进行的下一步操作是：\nA.购买道具\nB.购买食材\nC.借贷\nD.烹饪\nE.退出页面\n";
			}
			else if (language == en) {
				cout << "You have $ " << money << "\nWhat do you want to do next?\nA.Buy items\nB.Buy [cooking ingredients]\nC.Apply for loan\nD.Start cookingE.Quit this menu\n";
			}
			key = getch();
			if (key == 'A' || key == 'a') {
				hyphen();
				M_stu(); break;
			}
			else if (key == 'B' || key == 'b') {
				hyphen();
				M_cok(); break;
			}
			else if (key == 'C' || key == 'c') {
				hyphen();
				M_det(); break;
			}
			else if (key == 'D' || key == 'd') {
				Cincook(); break;
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
			Vacheve = false; hyphen(5);
			if (language == cn)cout << "您的投资金额：" << Iinvest << "元\n投资共需等待：" << Dinvest - days << "天\n";
			else if (language == en)cout << "Money you have invested: $ " << Iinvest << "\nYou need to wait for: " << Dinvest - days << "days\n";
		} else {
			hyphen(3);
			if (language == cn)cout << "\n请重新选择！\n";
			else if (language == en)cout << "\nPlease choose again!\n";
			notice();
			key = getch(); interact();
		}
	}
	else if (key == 'B' || key == 'b') {
		colorc(blue);
		if (language == cn)cout << "你有" << sug << "克糖\n你有" << sul << "克盐\n你有" << sod << "克苏打\n你有" << wat << "毫升水（最多拥有1000毫升）\n你有" << flo << "克面粉\n";
		else if (language == en)cout << "You have " << sug << " grams of sugar\nYou have " << sul << " grams of salt\nYou have " << sod << " grams of soda\nYou have " << wat << " milliliter of water (1000 milliliter max)\nYou have " << flo << " grams of flour\n";
		colorc(white);
		pause(1); turns--;
		hyphen(4);
	}
	else if (key == 'O' || key == 'o') {
		hyphen(4);
		if (Cid != 0) {
			int CDSS = 0;
			while (1) {
				if (CDSS == Cid)break;
				if (language == cn) {
					cout << CDSS << "." << backpackmeal[CDSS] << "|热量：" << backpackcalr[CDSS] << "|效果：" << backpackeffect[CDSS] << "|";
					cout << "总量：" << backpackall[CDSS] << "\n";
				}
				else if (language == en) {
					cout << CDSS << "." << backpackmeal[CDSS] << "|Energy: " << backpackcalr[CDSS] << "|Effect: " << backpackeffect[CDSS] << "|";
					cout << "Amount: " << backpackall[CDSS] << "\n";
				}
				CDSS++;
			}
			pause();
			while (1) {
				if (language == cn)cout << "输入要进行操作的物品的编号（输入负数退出此页面）：";
				else if (language == en) cout << "Input the number of item you want to choose (insert negative number to quit this menu):";
				cin >> CTP;
				if (CTP >= Cid || CTP < 0) {
					break;
				} else {
					hyphen(4);
					if (language == cn)cout << "A.贩卖此食品\nB.将此食品喂给宠物\nC.将此食品扔掉\nD.退出此页面\n";
					else if (language == en)cout << "A.Sell this dish\nB.Feed this dish to your pet\nC.Dump this dish\nD.Quit this menu\n";
					while (1) {
						key = getch();
						if (key == 'A' || key == 'a') {

							break;
						}
						else if (key == 'B' || key == 'b') {

							break;
						}
						else if (key == 'C' || key == 'c') {
							if (language == cn)cout << "已扔掉" << CTP << "号食品\n";
							else if (language == en)cout << "Item NO. " << CTP << " has been dropped\n";
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
			if (language == cn)cout << "你没有任何烹饪品！\n";
			else if (language == en)cout << "You don't have any dish!\n";
			pause();
		}
		turns--;
		hyphen(4);
	}
	else if (key == 'X' || key == 'x') {
		color_choose();
		turns --;
	}
	else if (key == '?') {
		hyphen(4);
		cout << "A.退出此界面\nB.基础操作教程\nC.随机事件操作教程\nD.借贷系统操作教程\nE.烹饪系统操作教程\nF.宠物死亡\n";
		while (1) {
			key = getch();
			if (key == 'A' || key == 'a') break;
			else if (key == 'B' || key == 'b') {
				hyphen(4);
				cout << "①.请在开始游戏时切换为英文输入法\n";
				cout << "②.你可以在游戏中按下按键选择不同行动，一天有8个回合选择行动，但按S（清屏）或按C（查看宠物状态）并不占用回合。\n";
				cout << "③.游戏中有这样几个数值：宠物是否想要排泄（如果宠物想要排泄，每等待一回合会扣除快乐值、增加悲伤值）、宠物是否\n想要进食（如果宠物想要进食，每等待一回合会扣除快乐值、增加悲伤值）、宠物快乐值（100满）\n、宠物悲伤值（50满，悲伤值充满后宠物死亡）\n";
				pause(); break;
			}
			else if (key == 'C' || key == 'c') {
				hyphen(4);
				cout << "当游戏天数>=1时，0.1.1及以上的版本会触发随机事件。随机事件有：\n";
				cout << "①.宠物为你带来随机大小的金钱（0~35元，为0元时不触发） \n②.宠物担当你的投资人，如果投入全部金钱，会增加宠物的快乐值和减少悲伤值。结果会在随机天数后出现，有25%概率成功，金钱回报率10%-50%\n";
				cout << "③.宠物推销商品，有三套商品，分别有40%、40%和20%的概率触发\n④.宠物创立了一个前卫摇滚乐队。可以为你带来金钱！（一次性随机事件，只可以触发一次）\n⑤.宠物为你带来五种食材中的任意一种，数量是一个1~35的随机数\n";
				pause(); break;
			}
			else if (key == 'D' || key == 'd') {
				hyphen(4);
				cout << "按下M键后进入金钱界面。借贷的金额不能大于本身金钱的十倍，如果本身金钱为0，则不可借贷。\n借贷的利息在1%到10%之间，还债期限为随机天数。如果到规定期限仍未还债，则每多一天债款增加原先利率。如果催债不换，则每一次减少快乐值、增加悲伤值\n";
				pause(); break;
			}
			else if (key == 'E' || key == 'e') {
				hyphen(4);
				cout << "未开放！\n";
				pause(); break;
			}
			else if (key == 'F' || key == 'f') {
				hyphen(4);
				cout << "游戏内，宠物一共有猫狗两个物种。两个物种的极限寿命（天数）不同，猫的极限寿命是2岁到4岁的随机数；狗的极限寿命是1岁半到5岁的随机数\n";
				cout << "\n在随机事件“宠物的前卫摇滚乐队”中度过的天数不算在宠物的寿命内。你可以在按下C后查看宠物的寿命。但寿命并不是不可提升的，宠物在一开始拥有一个85-60间的随机数作为寿命增加所需要达到的快乐值的点数，而每天，这个数值都会【+5】，一直到无法再次增加为止。如果宠物的快乐值大于这个值，且宠物的悲伤值小于15，则寿命【+1】，一天的八回合内，只有奇数回合寿命增加。\n";
				pause(); break;
			}
		}
		system("cls"); turns--;
	}
	/*else if(key=='K'||key=='k') {
		hyphen(4);
		cout <<"A.存档\nB.查看存档\nC.读档\nD.退出界面\n";
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
		cout << "输入作弊码："; cin >> cheating; cout << "\n";
		if (cheating == "Gmoney") {
			cin >> Mopluse; money = money + Mopluse;
		}
		else if (cheating == "Clean") {
			hap = 50; sad = 0; poo = false; eat = false;
		}
		else if (cheating == "Turns") {
			turns = 1;
		}
		else if (cheating == "Smoney") {
			cin >> Mopluse; money = Mopluse;
		}
		else if (cheating == "Suicide") {
			hap = 0; sad = 10;
		}
		else if (cheating == "Days") {
			cin >> Mopluse; days = Mopluse;
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
			cin >> Mopluse; sug = Mopluse;
		}
		else if (cheating == "Sul") {
			cin >> Mopluse; sul = Mopluse;
		}
		else if (cheating == "Sod") {
			cin >> Mopluse; sod = Mopluse;
		}
		else if (cheating == "Wat") {
			cin >> Mopluse; wat = Mopluse;
		}
		else if (cheating == "Flo") {
			cin >> Mopluse; flo = Mopluse;
		}
		/*
		else if (cheating == "Walk") {
			system("cls");
			start();
		}
		*/
		else if (cheating == "Cooking") {
			wat = 100; sug = 100; sul = 100; sod = 100; flo = 100;
		}
		cout << "\n"; hyphen(250);
		turns--;
	}
	else {
		hyphen(3);
		cout << "\n";
		choose_again();
		notice();
		key = getch(); interact();
	}
}

void o_days() {//每一天函数，期间插入随机事件
	hyphen(2);
	Cfour();
	e_hap();
	e_sad();
	e_poo();
	e_eat();
	M_();
	e_age();
	if (cheatable == true)cout << "*";
	if (language == cn)cout << "这是第" << days << "天。\n";
	else if (language == en)cout << "DAY " << days << " .\n";
	if (det == true && Ldet == true)Dgm = true;
	if (eat == true) {
		if (language == cn)cout << "你的宠物" << name << "想要进食\n";
		else if (language == en)cout << "Your pet " << name << " is hungry\n";
	}
	if (poo == true) {
		if (language == cn)cout << "你的宠物" << name << "想要排泄\n\n";
		else if (language == en) cout << "Your pet " << name << " wants to defecate\n\n";
	}
	if (Pmouse == true) {
		Pmouse_plus = r_events(1784, 5, 1);
		if (language == cn)cout << "你的宠物把玩着那只玩具老鼠。\n";
		else if (language == en)cout << "Your pet is playing with the toy mouse.\n";
		hap_plus(Pmouse_plus);
		hap += Pmouse_plus;
	}
	if (BFS == true) {
		Msenting = r_events(1321, 500, 20);
		if (language == cn)cout << "几个歌迷渴望" << name << "重回歌坛，为此，她们放了" << Msenting << "元。\n";
		else if (language == en)cout << "Some fans want " << name << " to keep performing, so they put $ " << Msenting << " .\n";
		money_plus(Msenting);
		money = money + Msenting;
	}
	if (lifespan < 0)lifespan = 0; //防止寿命小于0
	if (days == lifespan) {
		if (language == cn)cout << "不出意外的话，这将会是你的宠物在世的最后一天。\n";
		else if (language == en)cout << "If nothing goes wrong, this is the last day of your pet.\n";
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
		//cout <<turns<<"\n";//测试
		if (lifespan < 0)lifespan = 0; //防止寿命小于0
		if (days >= lifespan + 1) { //宠物寿命结束，>=是为了防止寿命在某种情况下成为负数
			death(); died = true;
		}
		//cout <<"poo"<<w_poo<<"eat"<<w_eat<<"\n";//测试
		//cout <<"借贷"<<det<<"/利息"<<Edet<<"/天"<<Ddet<<"/债款"<<Pdet<<"/拖沓"<<Ldet<<"\n\n";//测试
		//cout <<"天数"<<Dinvest<<"\n";//测试
		M_();
		Cfour();
		e_hap();
		e_sad();
		e_poo();
		e_eat();
		if (died == true) break; //死亡
		notice();
		key = getch();
		interact();
		if (key == 'Q' || key == 'q') break; //退出
		turns++; w_eat++;
		if (days != 1) {
			w_poo++;
		}
		if (w_eat > 2)eat = true;
		if (w_poo > 4)poo = true;
		cout << "\n\n";
		if (eat == true) {
			your_pet();
			if (language == cn)cout << "想要进食\n";
			else if (language == en)cout << "is hungry\n";
		}
		if (poo == true) {
			your_pet();
			if (language == cn)cout << "想要排泄\n\n\n";
			else if (language == en)cout << "wants to defecate\n\n\n";
		}
		hyphen(1);
		cout << "\n\n";
		if (turns == 9) {
			break; hyphen();
		}
	}
	if (invest == true && days == Dinvest) { //随机事件二，投资
		invest = false;
		Dinvest = 0;
		randomnum = r_events(3, 4, 1);
		Einvest = r_events(3, 50, 10);
		if (cheat == false) {
			if (loser == false) {
				if (randomnum == 2) {
					your_pet();
					if (language == cn)cout << "投资成功了！\n收益率" << Einvest << "%！\n";
					else if (language == en)cout << "has made a successful investment！\nRate of profit " << Einvest << "%!\n";
					money_plus(IINVEST + Einvest / 100 * IINVEST);
					hap_plus(2);
					money = money + IINVEST + Einvest / 100 * IINVEST; hap += 2;
				} else {
					your_pet();
					if (language == cn)cout << "投资失败了！\n";
					else if (language == en)cout << "has failed the investment!\n";
					hap_minus(1);
					sad_plus(2);
					hap = hap - 1; sad = sad + 2;
				}
			} else {
				randomnum = 114514; loser = false;
			}
		}
		else {
			your_pet();
			if (randomnum != 1) {
				if (language == cn)cout << "投资成功了！\n收益率" << Einvest << "%！\n";
				else if (language == en)cout << "has made a successful investment！\nRate of profit: " << Einvest << "%！\n";
				money_plus(IINVEST + Einvest / 100 * IINVEST);
				hap_plus(2);
				money = money + IINVEST + Einvest / 100 * IINVEST;
				hap += 2;
			} else {
				if (language == cn)cout << "投资失败了！\n";
				else if (language == en)cout << "has failed in the investment!\n";
				hap_minus(1);
				sad_plus(2);
				hap = hap - 1; sad = sad + 2;
			}
			cheat = false;
		}
		Iinvest = 0; IINVEST = 0; Einvest = 0;
		hyphen(); pause(); cout << "\n\n";
	}
	r_e();
	turns = 1;
	days++;
}

int main() {
	srand(time(NULL));
	Mname(); Mname1(); //烹饪变量赋值
	cout << "Digital Pet\n" << vertion << " " << phase;
	if (cheatable == true)cout << "*";
	cout << "\nProgramming：之言\nTesting：地有、Mary Lee\nCreators：之言、地有\nArt：...\nSound Effect：...\n";
	hyphen(4);
	cout << "（按下任意键继续……）(Press any key to continue...)\n";
	getch();
	language_choose();
	color_choose();
	name_choose();
	per();
	pause();
	if (language == cn)cout << "你们将会度过美好的时光，不是吗？\n你看着你的宠物，突然意识到它也许可以成为亚洲歌星。\n";
	else if (language == en)cout << "You will have a great time together, won't you?\nYou look at your pet, then suddenly realize that it might become the next Michael Jackson.\n";
	pause(1);
	r_lifespan(); Lifespanhap = r_events(1242, 85 - 60, 60);
	while (1) {
		o_days();
		if (key == 'Q' || key == 'q')break;
		if (died == true)break;
	}
	return 0;
}