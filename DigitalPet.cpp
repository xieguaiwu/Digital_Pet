/*
* @Author: ս�Խ���
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

int lifespan;//�������������������ӣ�
int Mlifespan;//�����������
int Llifespan;//�������

const int pers = 2; //�Ը������
const int events = 6; //����¼��ĸ���
int randomnum;//������ķ���ֵ
int days = 1; //����
bool died = false;


int turns = 1; //ÿһ����8�β�������
//���������
string cheating;
const bool cheatable = true;
int Mopluse;
bool Bband = false; //�Ƿ��Ѿ����������¼�4


//����¼���������
bool cheat = false;
bool loser = false;
bool invest = false; //����¼����ı������Ƿ�Ͷ��
int Iinvest;//Ͷ�ʵĽ��
int IINVEST;
int Dinvest;//Ͷ�ʵȴ�������
float Einvest;//Ͷ�ʵ�������
//����¼�������
const int price_mouse = 90, price_slipper = 20, price_heartsaver = 10000, price_lone = 10;

//����-�۸�
const int price_pbutter = 35, price_mbutter = 50;

//��⿱���-�۸�
const int price_sug = 8, price_sod = 9, price_wat = 0, price_flo = 6;
//��⿱���-ӵ��
long long sug;//��
long long sul;//��
long long sod;//�մ�
long long wat;//ˮ
long long flo;//���
//��⿱���-����
long long Isug;//��
long long Isul;//��
long long Isod;//�մ�
long long Iwat;//ˮ
long long Iflo;//���

//��⿱���
int calr;//����
string Meal;//���Ʒ�����ƣ���ζ+���ƣ�
map<int, string> meal;//���Ʒ����
map<int, string> Tmeal;//���Ʒ��ζ
//��⿱���-�洢
int Cid = 0; //���ڼ�¼����
vector<string> backpackmeal;//��Ʒ����
vector<int> backpackcalr;//��Ʒ��Ӧ������
vector<int> backpackspend;//��Ʒ��Ӧ�������ɱ�����֮��Ľ�һ��������ʹ��
vector<int> backpackall;//��Ʒ��Ӧ������
vector<float> backpackeffect;//��ƷЧ��
map<float, string>effects;//��ƷЧ������
int Crow;//���ڽ���ѭ��
int CTP;//���ڽ���ѡ��

int r_events(int sss = 0, int Mranding = 0, int Lranding = 0) { //��������ɣ���������¼�������Ը��
	if (sss == 0) {
		return 1 + rand() % (events); //���� ����¼�
	}
	else if (sss == 1) {
		return rand() % (pers-1); //���� ����Ը�
	}
	else {
		//if(Mranding<Lranding)cout <<"��������ɴ���\n";
		return Lranding + rand() % (Mranding); //���������
	}
}

int cook(long long Psug, long long Psul, long long Psod, long long Pwat, long long Pflo, int cs = 0) { //����cs������������
	Msug = Psug; Msul = Psul; Msod = Psod; Mwat = Pwat; Mflo = Pflo;
	Camount = Psug + Psul + Psod + Pwat + Pflo;
	if (cs == 0) { //���
		if (Psug == 0 && Psul == 0 && Psod == 0 && Pwat == 0 && Pflo == 0) {
			if (language == cn)cout << "������һ���Բ����ڵĻ���ľ�ȷ�ѿء������ڵ��������ķ������Լ��Բ����ڵ�ʳ�ĵľ��Ĵ��䣬��ɹ��������ˡ���";
			else if (language == en)cout << "After precisely controlling the invisible fire, consistly modifying the temperature of the non-existent frying pan, and the combination of the imaginary delicate seasonings, you successfully made a dish of...";
			Ncook = air;
			return Ncook;
		} else {
			int Rcook = 1 + rand() % (3);
			if (Rcook == 1) {
				if (language == cn)cout << "�Ͷ˶��ĵ�ʳ����������Ҫ������⿡�����ֱ�ӽ�һ���޻���������ۣ��������\n��Сʱ���㷢���Լ��óԼ��ˡ����������ʱ���㷢���Լ��Ѿ��ɹ��������ˡ���";
				else if (language == en)cout << "You throw a bunch of inorganic substance (except for the flour) into the pot. Few hours later, you find yourself very tasty. When cooking yourself, you find out that you have already cooked...";
			}
			if (Rcook == 2) {
				if (language == cn)cout << "��ϸ�ĵذ�һ�Ѷ������������������ֶ���⿡����ţ��㷢����⿺������塣\n�����Ӻ��㷢�ֹ������ʮ�ֺóԡ��ڳ��Ծ׽�������ͬʱ���㷢���Լ��ɹ���⿳��ˡ���";
				else if (language == en)cout << "You carefully throw a bunch of materials into the pot, and cook them with strange approaches. A few minutes later, you find the turner very tasty. When trying to chew the turner, you find yourself successfully cooked...";
			}
			if (Rcook == 3) {
				if (language == cn)cout << "�ڶ���һ�Ѷ��ĵ��޻�����㱻������Ǻ������Сʱ��\n������Сʱ����Ѭ���㳹����͸�ˡ����ͬʱ����ɹ��������ˡ���";
				else if (language == en)cout << "After throwing a bunch of disgusting inorganic substance, you are chocked by the smoke for two whole hours, and you find yourself totally cooked. In the mean time, you successfully invented...";
			}
		}
	}
	else if (cs == 1) { //�������� ��ÿ���Ǻ���4����������ˮ���ڵ���۳�Ϊ�����ÿ�˺���2�������������ÿ�˺���4��������
		Mcalr = Psug * 4;
		if (Pwat > Pflo)Mcalr = Mcalr + Pflo * 2;
		else Mcalr = Mcalr + Pwat * 2 + (Pflo - Pwat) * 4;
		return Mcalr;
	}
}

bool Vacheve = false;
void notice() {
	if (language == cn) {
		cout << "\n����Q�˳�\n����Fιʳ\n����I����ﻥ��\n����C�鿴����״̬\n����S����\n����M���С����򡿡������������⿡�\n����B�鿴���Ѿ�ӵ�еġ����ʳ�ġ�\n";
		cout << "����O�鿴�����������Ʒ\n����X��������������ɫ\n���¡�?���鿴�̳�\n"; //<<"����K����浵����\n";
	}
	else if (language == en) {
		cout << "\nPRESS 'Q' TO QUIT\nPRESS 'F' TO FEED YOUR PET\nPRESS 'I' TO INTERACT WITH YOUR PET\nPRESS 'C' TO CHECK YOUR PET'S STATUS\n";
		cout << "PRESS 'S' TO CLEAR THE SCREEN\nPRESS 'M' TO [PURCHASE], [APPLY FOR LOAN] OR [COOK]\nPRESS 'B' TO CHECK THE [COOKING INGREDIENT] YOU ALREADY HAD\n";
		cout << "PRESS 'O' TO CHECK THE DISHES YOU ALREADY COOKED\nPRESS 'X' TO RESET THE THEME COLOR\nPRESS '?' TO CHECK THE INSTRUCTIONS\n";
	}
	if (invest == true) {
		if (language == cn)cout << "����V�鿴��Ͷ�������\n";
		else if (language == en)cout << "PRESS 'V' TO CHECK THE [STATUS OF INVESTMENT]\n";
		Vacheve = true;
	}
	if (language == cn)cout << "ÿ����8�ΰ��°����Ļ���\n����" << 8 + 1 - turns << "��\n";
	else if (language == en)cout << "There are 8 times to press the key.\nYou have " << 8 + 1 - turns << " times left\n";
}

//ǰʮ��������
fstream get_save;//��ȡ
int list_id;//ǰʮ������id
int list_row;//����ѭ��
void list_read() {//��ȡ
	get_save.open("top10\\Lid.txt");
	get_save >> list_id; //��ȡlist_id
	get_save.close();
}

void list_write() {//д��
	get_save.open("top10\\Lid.txt");
	get_save << list_id; //д��list_id
	get_save.close();
}

/*void list_queue() {

}*/

//��⿺����������ͷ�ļ������ķ�������
void Cpushback(string bloodyname, int bloodycalr, int bloodyspend, int bloodyall, float bloodyeffect) {//�洢
	backpackmeal.push_back(bloodyname);
	backpackcalr.push_back(bloodycalr);
	backpackspend.push_back(bloodyspend);
	backpackall.push_back(bloodyall);
	backpackeffect.push_back(bloodyeffect);
	Cid++;
}

void Cclean() {//���
	Crow = 1;
	while (1) {
		if (Crow == Cid)break; //backpackmeal��0��ʼ
		backpackmeal[Crow - 1] = "";
		Crow++;
	}
	Cid = 0;
}

void Cdrop(int IDI) {//��ȥ IDI=id of the dropped item
	backpackmeal[IDI] = "";
	Cid = Cid - 1;
	Crow = IDI;
	while (1) {
		if (Crow == Cid)break; //ע�⣬�˴�Crow����Cid���൱�ڰ����һ����Ʒ��ֵΪ0
		backpackmeal[Crow] = backpackmeal[Crow + 1];
		backpackcalr[Crow] = backpackcalr[Crow + 1];
		backpackspend[Crow] = backpackspend[Crow + 1];
		backpackall[Crow] = backpackall[Crow];
		Crow++;
	}
}

void Mname() {
	if (language == cn) {
		meal[0] = "����";
		meal[1] = "�մ�ˮ";
		meal[2] = "������״�ĺڽ�ɫ����";
		meal[3] = "���";
		meal[4] = "���";
		meal[5] = "��ˮ���մ�";
		meal[6] = "����";
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
		Tmeal[10] = "��Щ�����";
		Tmeal[11] = "��Щ�̵�";
		Tmeal[12] = "��Щʪ������";
		Tmeal[13] = "���������";
		Tmeal[14] = "ƽ����";
		Tmeal[15] = "�������";
		Tmeal[16] = "�ǳ������";
		Tmeal[17] = "�ǳ��̵�";
		Tmeal[18] = "�ǳ�ʪ������";
		Tmeal[19] = "�ǳ��������";
		Tmeal[20] = "��Щ�ɵ�";
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

void Ename() {	//��ƷЧ������
	//����
	if (language == cn) {
		effects[0.1] = "������+1��";
		effects[0.2] = "������+2��";
		effects[-0.1] = "������-1��";
		effects[-0.2] = "������-2��";
	}
	else if (language == en) {
		effects[0.1] = "Lifespan [+1]";
		effects[0.2] = "Lifespan [+2]";
		effects[-0.1] = "Lifespan [-1]";
		effects[-0.2] = "Lifespan [-2]";
	}
	//����ֵ
	if (language == cn) {
		effects[1.10] = "����ֵ��+10��";
		effects[1.15] = "����ֵ��+15��";
		effects[-1.10] = "����ֵ��-10��";
		effects[-1.15] = "����ֵ��-15��";
		effects[2.5] = "����ֵ���ޡ�+5��";
		effects[2.15] = "����ֵ����+15";
		effects[-2.5] = "����ֵ���ޡ�-5��";
		effects[-2.15] = "����ֵ���ޡ�-15��";
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
	//����ֵ
	if (language == cn) {
		effects[3.5] = "����ֵ��+5��";
		effects[3.8] = "����ֵ��+8��";
		effects[-3.5] = "����ֵ��-5��";
		effects[-3.8] = "����ֵ��-8��";
		effects[4.5] = "����ֵ���ޡ�+5��";
		effects[4.10] = "����ֵ����+10";
		effects[-4.5] = "����ֵ���ޡ�-5��";
		effects[-4.10] = "����ֵ���ޡ�-10��";
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
	//ƽ����
	if (language == cn)effects[5.0] = "��Ч��";
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

bool Jcook = false; //�����ʱ�л������õ�һ����������
void Cincook() {
	colorc(blue);
	if (language == cn) {
		cout << "����" << sug << "����\n����" << sul << "����\n����" << sod << "���մ�\n����" << wat << "����ˮ�����ӵ��1000������\n����" << flo << "�����\n";
	}
	else if (language == en) {
		cout << "You have " << sug << " grams of sugar\nYou have " << sul << " grams of salt\nYou have " << sod << " grams of soda\nYou have " << wat << " milliliter of water (1000 millilitter max)\nYou have " << flo << " grams of flour\n";
	}
	colorc(white);
	pause();
	if (language == cn)cout << "��������𣿣����������������˳����棩\n";
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
			if (language == cn)cout << "��Ҫ������ٿ��ǣ����������";
			else if (language == en)cout << "How much sugar do you want to put in�� Input the number of grams:";
			cin >> Isug;
			if (Isug < 0 || Isug > sug)cout << "�������\n";
			else {
				sug = sug - Isug; break;
			}
		}
		while (1) {
			if (language == cn)cout << "��Ҫ������ٿ��Σ����������";
			else if (language == en)cout << "How much salt do you want to put in�� Input the number of grams:";
			cin >> Isul;
			if (Isul < 0 || Isul > sul)cout << "�������\n";
			else {
				sul = sul - Isul; break;
			}
		}
		while (1) {
			if (language == cn)cout << "��Ҫ������ٿ��մ����������";
			else if (language == en)cout << "How much sodium bicarbonate do you want to put in�� Input the number of grams:";
			cin >> Isod;
			if (Isod < 0 || Isod > sod)cout << "�������\n";
			else {
				sod = sod - Isod; break;
			}
		}
		while (1) {
			if (language == cn)cout << "��Ҫ������ٺ���ˮ�������������";
			else if (language == en)cout << "How much water do you want to put in�� Input the number of milliliter:";
			cin >> Iwat;
			if (Iwat < 0 || Iwat > wat)cout << "�������\n";
			else {
				wat = wat - Iwat; break;
			}
		}
		while (1) {
			if (language == cn)cout << "��Ҫ������ٿ���ۣ����������";
			else if (language == en)cout << "How much flour do you want to put in�� Input the number of grams:";
			cin >> Iflo;
			if (Iflo < 0 || Iflo > flo)cout << "�������\n";
			else {
				flo = flo - Iflo; break;
			}
		}
		cook(Isug, Isul, Isod, Iwat, Iflo, ck);
		if (Isug == 0 && Isul == 0 && Isod == 0 && Iwat == 0 && Iflo == 0)cout << meal[cook(Isug, Isul, Isod, Iwat, Iflo, ck)] << "��\n";
		else {
			Meal = Tmeal[meal_tas()] + meal[meal_nam()];
			cout << Meal << "��\n"; calr = cook(Isug, Isul, Isod, Iwat, Iflo, cr);
			if (language == cn)cout << "�����Ʒ��������" << calr << "�㣡\n";
			else if (language == en)cout << "The energy of this dish is " << calr << " calories!\n";
			Cpushback(Meal, calr, Isug * 8 + Isul * 13 + Isod * 9, meal_all(), meal_effect()); //�εļ۸���6~21���������ȡ�м�ֵ13.5����������13Ԫ
		}
	} else {
		Jcook = false;
	}
	hyphen(4);
}


//����ָ��
int age = 0; //���� 10������1
int hap = 50; //����ֵ ��ʼ100-��
int max_hap = 100; //��ʼ���ֵ
int sad = 0; //����ֵ ��ʼ50-��
int max_sad = 50; //��ʼ���ֵ
bool poo = false; //��й
int w_poo;//��й����ʱ�� 10-��
bool eat = false; //��ʳ 5-��
int w_eat;//��ʳ����ʱ��
bool Pab;//�����Ը�

//�����Ը�����
void per() {	//������ɳ�����Ը�
	if (language == cn)cout << "���뵽���" << name << "�������Ǹ����ӣ�";
	else if (language == en)cout << "You remember the day you met " << name << ":";
	randomnum = r_events(1); //���������
	Pab = randomnum;
	if (Pab == dog) {
		if (language == cn)cout << "�ڳ������㿴��һֻС������ϲ�������Ĺ����ӣ�����������˼ҡ�";
		else if (language == en)cout << "You saw a puppy at a pet store. You liked its mad look, so you took it home.";
	}
	else if (Pab == cat) {
		if (language == cn)cout << "��ֽ����㿴����һֻ���ź����Сè��������������㳦������������˼ҡ�";
		else if (language == en)cout << "You saw a snoring pussy in a carton. After giving it some saussages, you took it home.";
	}
	if (language == cn)cout << "������Ѿ������������֡�\n";
	else if (language == en)cout << "And now you've named it.\n";
}

void r_lifespan() { //�������
	if (Pab == cat) lifespan = 20 + rand() % (40 - 20); //è��������2~4���죨�����ӣ�
	else if (Pab == dog) lifespan = 15 + rand() % (50 - 15); //����������1��뵽5�꣨�����ӣ�
}

//����¼���
void r1() {		//����¼�1��
	randomnum = r_events(3, 35, 0);		//����0~35Ԫ
	if (randomnum != 0) {
		if (language == cn) {
			cout << "\n���죬�㷢����ĳ�����ʧ�ˡ���Сʱ����ĳ���Ϊ�������" << randomnum << "Ԫ��\n��Ǯ���ӣ�\n";
		}
		else if (language == en ) cout << "\n This day, you find that your pet disappered. Few hours later, your pet brings you back $" << randomnum << "!\nMoney increase!\n";
		money = money + randomnum; pause();
	}
}

void r2() {		//����¼�2������ķ���Ͷ��
	your_pet();
	if (language == cn) {
		cout << "������������������һ��ֽ������д�ţ�\n����Ͷ��\nͶ���ˣ����" << name << "\n�����ˣ���\n������ǩ����________\n";
	}
	else if (language == en) {
		cout << "walks to you with a paper, which said:\nVENTURE INVESTMENT\nInvestor:" << name << "\nVoucher: You\nSignature:________\n";
	}
	sure();
	while (1) {
		key = getch();
		if (key == 'H')
		{
			if (language == cn)cout << "��ǩ�����Լ������֡�\n";
			else if (language == en)cout << "You sign your name.\n";
			invest = true;
			while (1) {
				if (language == cn)cout << "��ҪͶ�ʵĽ��";
				else if (language == en)cout << "Input the money you want to invest";
				money_have();
				cin >> Iinvest;
				if (!(Iinvest <= 0)) {
					if (!(Iinvest > money))break;
					else {
						if (language == cn)cout << "��û����ô��Ǯ����ֻ��" << money << "Ԫ��\n\n";
						else if (language == en)cout << "You don't have that much of money! All you have is $ " << money << "!\n\n";
					}
				} else {
					if (Iinvest < 0) {
						if (language == cn)cout << "Ͷ��ʧ�ܣ��������룡\n\n";
						else if (language == en)cout << "Failed to invest, please reenter!\n\n";
					}
					else {
						if (language == cn)cout << "����ǧ��һ��֮�ʣ��������Ͷ�ʣ�\n";
						else if (language == en)cout << "You give up the investment when it is by a hair!\n";
						break;
					}
				}
			}
			if (Iinvest != 0) {
				if (language == cn)cout << "��Ͷ����" << Iinvest << "Ԫ��\n";
				else if (language == en)cout << "You invest $ " << Iinvest << ".\n";
				if (Iinvest == money) {
					if (language == cn) cout << "��ĳ��￴����Ͷ�������ϵ�����Ǯ��ʮ�ָ��ˡ�\n";
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
				if (language == cn)cout << "��ĳ��￴�����������һ����̱��\n";
				else if (language == en)cout << "Your pet is looking at you as if you are a retard.\n";
				break; invest = false;
			}
		}
		else if (key == 'P') {
			if (language == cn)cout << "��ĳ��￴�����������һ����̱��\n";
			else if (language == en)cout << "Your pet is looking at you as if you are a retard.\n";
			break; invest = false;
		}
		cout << "\n\n";
	}
}

bool Phouse = false; //�����Ƿ��з���
bool Pmouse = false; //�Ƿ����˳��������
int Pmouse_plus;//��ʦ���������ӵĿ���ֵ��1-10�������
void r3() { //����¼�3������Ա
	if (language == cn)cout << "��ĳ����ܳ��˼ҡ�\n��Сʱ����ĳ���" << name << "��ʼ���š�\n�Ƿ��ţ�\n";
	else if (language == en) {
		cout << "Your pet runs out of the house.\nFew hours later, your pet " << name << " starts to knock on the door.\n";
		cout << "Open the door?\n";
	}
	sure();
	while (1) {
		key = getch();
		if (key == 'H') {
			if (language == cn)cout << "������ţ�";
			else if (language == en)cout << "You open the door, just to realize that";
			randomnum = r_events(114514, 5, 1);
			if (randomnum == 2) {
				if (language == cn)cout << "ȴ������ĳ����Ѿ��Ե��˴����������˷��ӡ�\n";
				else if (language == en)cout << "your pet has already eated the window and entered the house.\n";
				poo = true;
			} else {
				if (language == cn)cout << "��ĳ�������˷��ӡ�\n";
				else if (language == en)cout << "your pet has already entered the house.\n";
			}
			break;
		}
		else if (key == 'P') {
			if (language == cn) {
				cout << "���װ������" << name << "����������������ĳ���һ�ڳԵ����ţ�\n��ĳ���е�������ˬ��\n";
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
	if (language == cn)cout << name << "�����ʾ�����ҵ��ļ�����Ʒ��\n";
	else if (language == en)cout << name << " showed you few items that it found:\n";
	randomnum = r_events(250, 5, 1);
	if (randomnum == 1 || randomnum == 2) {
		cout << "A."; randomnum = r_events(45, 50, 1);
		if (language == cn)cout << randomnum << "Ԫ �۸�10Ԫ\nB.������\n";
		else if (language == en)cout << "$ " << randomnum << " Price: $ 10\nB.Don't buy anything\n";
		while (1) {
			key = getch();
			if (key == 'A' || key == 'a') {
				if (!(money < 10)) {
					money = money - 10;
					if (language == cn)cout << "�㻨10Ԫ����" << randomnum << "Ԫ��";
					else if (language == en)cout << "You spent $ 10 to but $ " << randomnum << ". ";
					if (randomnum > 10) {
						if (language == cn)cout << "����һ����׬��������⣡\n";
						else if (language == en)cout << "What a silly great deal!\n";
					}
					if (randomnum == 10) {
						if (language == cn)cout << "����һ��׬����Ǯ�����⣡\n";
						else if (language == en)cout << "What a balanced profit!\n";
					}
					if (randomnum < 10) {
						if (language == cn)cout << "����һ�����ⲻ׬�����⣡\n";
						else if (language == en)cout << "What a foolish decision!\n";
					}
					money += randomnum;
				} else {
					if (language == cn)cout << "��Ǹ����û���㹻��Ǯ��\n";
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
			cout << "A.�������ʹ����ÿ��Ŀ���ֵ����1~5���������" << price_mouse << "Ԫ\nB.��Ь��ʹ�����Ϊ�з�һ�壩" << price_slipper << "Ԫ\n";
			cout << "C.��Ч������ " << price_heartsaver << "Ԫ\nD.������\n";
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
						if (language == cn)cout << "���������������\n";
						else if (language == en)cout << "You have bought the toy mouse!\n";
						Pmouse = true;
					} else {
						if (language == cn)cout << "��Ǹ����ĳ����Ѿ���һ���ˣ�\n";
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
						if (language == cn)cout << "����������Ь��\n";
						else if (language == en)cout << "You have bought the slipper!\n";
						Phouse = true;
					} else {
						if (language == cn)cout << "��Ǹ����ĳ����Ѿ���Ϊ�з�һ���ˣ�\n";
						else if (language == en)cout << "Sorry, but your pet already have one!\n";
					}
				} else {
					money_not();
				}
				break;
			}
			else if (key == 'C' || key == 'c') {
				if (!(money < 10000)) {
					if (language == cn)cout << "��Ǹ����û���㹻�Ľ�Ǯ�������𣿣������������˳���\n";
					else if (language == en)cout << "Sorry, buy you don't have enough money! Continue? (Press [up button] to continue and press [down button] to quit)\n";
					money = money - 10000;
					while (1) {
						key = getch();
						if (key == up) {
							if (language == cn)cout << "���ޣ�\n����ֵ���㣡����ֵ������\n";
							else if (language == en)cout << "MONSTER!\nHappiness = 0! Sadness maximumizes!\n";
							hap = 0; sad = max_sad;
							break;
						}
						else if (key == down) {
							if (language == cn)cout << "�㱻ƭ�ˣ�\n";
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
		if (language == cn)cout << "A.��į�����������į��10Ԫ\nB.������\n";
		else if (language == en)cout << "A.Lonliness (buy one when you are on your own) $ " << price_lone << "\nB.Don't buy anything\n";
		while (1) {
			key = getch();
			if (key == 'A' || key == 'a') {
				if (!(money < 10)) {
					money = money - 10;
					if (language == cn)cout << "�����˸���į����\n";
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
		cout << "��21st century schizoid pet!��\n�㿴����ĳ���������һ�ѵ缪��������һ�ѵ缪��ѹ�ڵ��ϣ����۹�������������۾���\n";
	}
	else if (language == en) {
		cout << "\"21st century schizoid pet!\"You see your pet is holding a electric guitar (being overwhelmed under the guitar), and the spotlight shines on its eyes.\n";
	}
	pause();
	if (language == cn) {
		cout << "������ӯ����\n�������ں���ĳ����ٴ��ÿ��˼�����š��������㣨��Ҫ����������ô������ģ��ⳡ�ݳ�ȡ���˾޴�ĳɹ���\n";
	}
	else if (language == en)cout << "Tears run out your eyes. Few weeks later, your pet knocks on the door again, and it tells you (don't ask me how) that this performance has made a great success.\n";
	randomnum = r_events(134, 5, 1);
	if (randomnum == 5) {
		BFS = true; randomnum = r_events(214, 3000, 200);
		if (language == cn) {
			cout << "��ĳ����Ϊ�����޵��������ǣ��ڽ���ÿһ�죬�����������ȸ���Ϊ������Ǯ������ĳ���ܲ��ػظ�̳��\n";
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
		cout << "�ⳡ�ݳ�һ�������" << randomnum << "Ԫ��Ϊ�˱�����ĸ�л����ĳ��������Ǯ���������㡣\n";
		pause();
		cout << "�������������ٴι�����ƽ�������\n";
	}
	else if (language == en) {
		cout << "The performance earns you $ " << randomnum << " in total. In order to show thankfulness, your pet hands you all the money.\n";
		pause();
		cout << "And so, the both of you come back to your ordinary life.\n";
	}
	hyphen(4);
}

void Binteract() { //����¼�4
	if (key == 'T' || key == 't') {
		if (language == cn)cout << "����˵���\n";
		else if (language == en)cout << "You open the YV.\n";
		pause(1);
		randomnum = r_events(1874298, 2, 1);
		if (randomnum == 1)Btv1();
		else if (randomnum == 2)Btv2();
		else if (randomnum == 3)Btv3();
		else if (randomnum == 4)Btv4();
		randomnum = r_events(82734, 4, 1);
		if (randomnum == 2) {
			if (language == cn)cout << "���л���Ƶ����ͻȻ���㿴���ˡ���\n\n��ĳ��\n";
			else if (language == en)cout << "You are switching channels, and suddenly, you see...\n\nYour pet!\n";
			pause();
			Bback();
			return;
		}
		else {
			if (language == cn)cout << "�㲻���л���Ƶ������û�п��������κ���Ϣ����\n";
			else if (language == en)cout << "You keep changing the channels, but can't find any information about your pet...\n";
			pause(1);
		}
	}
	else {
		hyphen(3);
		cout << "\n";
		choose_again();
		if (language == cn)cout << "\n����T������\nÿ����1�ΰ��°����Ļ���\n����" << 1 + 1 - Bturns << "��\n";
		else if (language == en)cout << "\nPress 't' to watch TV\nThere are 1 chance to watch TV everyday\nYou have " << 1 + 1 - Bturns << " time left\n";
		key = getch(); Binteract();
	}
}

void band_days() {	//����¼�4
	hyphen(2);
	cout << "���ǵ�" << Bdays << "��\n";
	while (1) {
		if (Bturns == 2)break;
		cout << "\n";
		choose_again();
		if (language == cn)cout << "\n����T������\nÿ����1�ΰ��°����Ļ���\n����" << 1 + 1 - Bturns << "��\n";
		else if (language == en)cout << "\nPlease choose again!\nPress 't' to watch TV\nThere are 1 chance to watch TV everyday\nYou have " << 1 + 1 - Bturns << " time left\n";
		key = getch();
		Binteract();
		if (back == true)break;
		Bturns++;
	}
	Bdays++;
	Bturns = 1;
}

void r4() {//����¼�4�������ǰ��ҡ���ֶ�
	Bband = true;
	if (language == cn) {
		cout << "�⼸����������ĳ���һֱ����һЩ�����ҡ�����֡�\n��ʱ������һЩ�ƺ��ǡ�rape���ĵ��ʴ�" << name << "�����бŷ�����Ҫ���Ҷ��������˵���ģ�\n";
	}
	else if (language == en) {
		cout << "For the past few days, your pet has been listening to some strange rock music.\nYou often hear some words like 'rape' from " << name << "'s mouse (don't ask me how)\n";
	}
	pause();
	if (language == cn) {
		cout << "һ�죬��ĳ�����һЩ����ķ�����������һ����Ϣ�������ᴴ��һֻǰ��ҡ���ֶӡ�\n�������Ѿ�Ϊ��Ͷ��̫�࣬�������ٻ�ʹ����Ľ�Ǯ��\n";
	}
	else if (language == en) {
		cout << "One day, your pet told you through a unimaginable way that it is going to start a progressive rock band.\nBecause you have gave it too much, this band won't cost you any money.\n";
	}
	pause(); eat = false; poo = false;
	if (language == cn) {
		cout << "����������ǰ���ιʳ��һ�γ����ĳ������һ�����˲�����\n��Ŀ���ų�����뿪����\n";
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

void r5() {//����¼�5
	randomnum = r_events(123, 5, 1);
	if (language == cn)cout << "\n���죬�㷢����ĳ�����ʧ�ˡ���Сʱ����ĳ���Ϊ�������";
	else if (language == en)cout << "\nToday, you can't find your pet anywhere. Few hours later, your pet brings you back ";
	if (randomnum == 1) { //��
		randomnum = r_events(1234, 35, 1); //����1-35��ʳ��
		if (language == cn)cout << randomnum << "���ǣ�\n";
		else if (language == en)cout << randomnum << " grams of sugar!\n";
		sug += randomnum;
	}
	else if (randomnum == 2) { //��
		randomnum = r_events(1234, 35, 1); //����1-35��ʳ��
		if (language == cn)cout << randomnum << "���Σ�\n";
		else if (language == en)cout << randomnum << " grams of salt!\n";
		sul += randomnum;
	}
	else if (randomnum == 3) { //�մ�
		randomnum = r_events(1234, 35, 1); //����1-35��ʳ��
		if (language == cn)cout << randomnum << "���մ�\n";
		else if (language == en)cout << randomnum << " grams of soda!\n";
		sod += randomnum;
	}
	else if (randomnum == 4) { //ˮ
		randomnum = r_events(1234, 35, 1); //����1-35��ʳ��
		if (language == cn)cout << randomnum << "����ˮ��\n";
		else if (language == en)cout << randomnum << " milliliters of water!\n";
		if (wat + randomnum <= 1000)wat += randomnum;
	}
	else if (randomnum == 5) { //���
		randomnum = r_events(1234, 35, 1); //����1-35��ʳ��
		if (language == cn)cout << randomnum << "����ۣ�\n";
		else if (language == en)cout << randomnum << " grams of flour!\n";
		flo += randomnum;
	}
	pause();
}

void r_e() {//random events ����
	if (days >= 1) {
		randomnum = r_events();
		//cout <<randomnum<<"\n";//���Դ���
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

//��������
void death() {//���������
	hyphen();
	if (language == cn)cout << "��ĳ���" << name << "����" << age << "�꣬������" << days << "�졣\n����ʱ��" << name;
	else if (language == en) {
		cout << "Your pet " << name << " had been through a life of " << age << " years, and it had been through " << days << " days.\n";
		cout << "When " << name << " was going to die, ";
	}
	if (poo == true) {
		if (language == cn)cout << "��Ȼ��Ҫ��й��\n";
		else if (language == en)cout << "it still wants to defecate.\n";
	}
	if (eat == true) {
		if (language == cn)cout << "��Ȼʮ�ּ�����\n";
		else if (language == en)cout << "it is still very hungry.\n";
	}
	if (language == cn)cout << "����ʱ��" << name;
	else if (language == en)cout << "When it was going to die, " << name << " ";
	if (sad >= 38 && sad < 42 && hap < 50) {
		if (language == cn)cout << "��Щ���ˡ�\n";
		else if (language == en)cout << "was a bit sad.\n";
	}
	if (sad >= 42 && hap < 50) {
		if (language == cn)cout << "ʮ��������\n";
		else if (language == en)cout << "was very depressed.\n";
	}
	if (hap >= 50 && hap < 76 && sad < 38) {
		if (language == cn)cout << "�ܿ��ġ�\n";
		else if (language == en)cout << "was quite happy.\n";
	}
	if (hap >= 76 && sad < 38) {
		if (language == cn)cout << "ʮ�ֿ��֡�\n";
		else if (language == en)cout << "was very happy.\n";
	}
	if (hap >= 50 && sad >= 38) {
		if (language == cn)cout << "����ì�ܡ�\n";
		else if (language == en)cout << "was confused.\n";
	}
	died = true;
	pause(1);
}

//��к���
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
		if (language == cn)cout << "������һ�꣡\n";
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
		if (language == cn)cout << "�������ȣ���ɱ�ˡ�\n";
		else if (language == en)cout << "is so depressed that it committed suicide.\n";
		death();
	}
}

bool Lifespanup_turns = false; //�Ƿ��ڵ��غ����Ѿ�����������
int Lifespanhap;//������������Ŀ���ֵ�ĳ�ʼֵ��һ��85-60֮��������
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
				if (hap >= Lifespanhap && sad <= 15) { //����ֵ>=������������Ŀ���ֵ�ұ���ֵС�ڵ���15����������һ��
					if (turns == 2 || turns == 4 || turns == 6 || turns == 8) {
						if (Lifespanup_turns == false) {
							if (language == cn)cout << "������������+1���죡\n";
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

//��Ǯ����
int cheatmoney;
int uglyprice;//������۸�
int gs;//�������
void M_notice() {
	if (gs < 0) {
		if (language == cn)cout << "���������룡\n";
		else if (language == en)cout << "Please input again!\n";
	}
	else if (gs == 0) {
		if (language == cn)cout << "������˹���\n";
		else if (language == en)cout << "You give up to buy.\n";
	}
}

void M_cok() {  //ʳ��
	while (1) {
		money_have();
		if (language == cn) {
			cout << "ʳ�ģ�\nA.�� " << price_sug << "Ԫÿ��\nB.�� 6��21Ԫÿ��\nC.�մ� " << price_sod << "Ԫÿ��\nD.ˮ " << price_wat << "Ԫÿ����\nE.��� " << price_flo << "Ԫÿ��\nF.���� 20��900Ԫÿ������\nG.�˳�����\n";
		}
		else if (language == en) {
			cout << "Cooking ingredients:\nA.Sugar $ " << price_sug << " per gram\nB.Salt $ 6~12 per gram\nC.Soda $ " << price_sod << " per gram\n";
			cout << "D.Water $ " << price_wat << " per milliliter\nE.Flour $ " << price_flo << " per gram\nF.Air $ 20~900 per square meter\nG.Quit this menu\n";
		}
		key = getch();
		if (key == 'A' || key == 'a') {
			uglyprice = 8;
			while (1) {
				if (language == cn)cout << "���빺�������";
				else if (language == en)cout << "Input the number of grams you want to buy:";
				cin >> gs;
				M_notice();
				if (gs == 0) {
					pause(); turns--; break;
				}
				else {
					if (money >= gs * uglyprice) {
						if (language == cn)cout << "�ѳɹ�����" << gs << "���ǣ�\n";
						else if (language == en)cout << "You have successfully bought " << gs << " grams of sugar!\n";
						money = money - gs * uglyprice; sug += gs; pause(); break;
					} else {
						if (language == cn)cout << "��Ǹ����Ǯ���㣡" << "\n";
						else if (language == en)money_not();
						pause(); break;
					}
				}
			}
			system("cls");
		}
		else if (key == 'B' || key == 'b') {
			uglyprice = r_events(123, 21 - 6, 6);
			if (language == cn)cout << "�۸�" << uglyprice << "\n";
			else if (language == en)cout << "Price: $ " << uglyprice << "\n";
			still_buy();
			while (1) {
				key = getch();
				if (key == up) {
					while (1) {
						if (language == cn)cout << "���빺�������";
						else if (language == en)cout << "Input the number of grams you want to buy:";
						cin >> gs;
						M_notice();
						if (gs == 0) {
							pause(); turns--; break;
						} else {
							if (money >= gs * uglyprice) {
								if (language == cn)cout << "�ѳɹ�����" << gs << "���Σ�\n";
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
				if (language == cn)cout << "���빺�������";
				else if (language == en)cout << "Input the number of grams you want to buy:";
				cin >> gs;
				M_notice();
				if (gs == 0) {
					pause(); turns--; break;
				}
				else {
					if (money >= gs * uglyprice) {
						if (language == cn)cout << "�ѳɹ�����" << gs << "���մ�\n";
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
				if (language == cn)cout << "���빺���������";
				else if (language == en)cout << "Input the number of milliliters you want to buy:";
				cin >> gs;
				if (wat < 1000 && wat + gs <= 1000) {
					wat += gs;
					if (language == cn)cout << "�ɹ�����" << gs << "����ˮ��\n";
					else if (language == en)cout << "You have successfully bought " << gs << " milliliters of water!\n";
					hyphen(4); break;
				}
				else {
					if (language == cn)cout << "��Ǹ�����Ѿ��й���ˮ�ˣ�\n";
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
				if (language == cn)cout << "���빺�������";
				else if (language == en)cout << "Input the number of grams you want to buy:";
				cin >> gs;
				M_notice();
				if (gs == 0) {
					pause(); turns--; break;
				}
				else {
					if (money >= gs * uglyprice) {
						if (language == cn)cout << "�ѳɹ�����" << gs << "����ۣ�\n";
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
			if (language == cn)cout << "�۸�" << uglyprice << "\n";
			else if (language == en)cout << "Price: $ " << uglyprice << "\n";
			still_buy();
			while (1) {
				key = getch();
				if (key == up) {
					while (1) {
						if (language == cn)cout << "���빺���������";
						else if (language == en)cout << "Input the number of milliliters you want to buy:";
						cin >> gs;
						M_notice();
						if (gs == 0) {
							pause(); turns--; break;
						}
						else {
							if (money >= gs * uglyprice) {
								if (language == cn)cout << "�ѳɹ�����" << gs << "�����׿�����\n";
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

void M_stu() {	//����
	while (1) {
		money_have();
		if (language == cn) {
			cout << "���ߣ�\nA.һ��ֲ���ëݢ�����ﱯ��ֵ��-8���� " << price_pbutter << "Ԫ\nB.һ�ַ�񡪡�ëݢ�����ﱯ��ֵ��-15����" << price_mbutter << "Ԫ\n";
			cout << "C.��˪����Ҫ�ڽ���Ͷ�ʵ������ʹ�á�Ͷ�ʳɹ��ʡ�+50��%���۸��������Ǯ�������Ѿ�����Ͷ�ʵĽ�Ǯ������5���ȥһ���������1~�����Ǯ����20��";
			cout << "\nD.��ʯ����Ҫ�ڽ���Ͷ�ʵ������ʹ�á�Ͷ�ʰٷְ�ʧ�ܣ��۸��������Ǯ��ʮ��\nE.�˳�ҳ��\n";
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
				if (language == cn)cout << "��εļ۸��ǣ�" << cheatmoney << "\n";
				else if (language == en)cout << "This time the price is $ " << cheatmoney << "\n";
				sure();
				while (1) {
					key = getch();
					if (key == 'H') {
						if (!(money < cheatmoney)) {
							if (invest == false) {
								if (language == cn)cout << "��Ǹ����û��Ͷ�ʣ�\n";
								else if (language == en)cout << "Sorry, but you don't have any investment!\n";
							} else {
								if (cheat == true) {
									if (language == cn)cout << "��Ǹ�����Ѿ������˴˵��ߣ�\n";
									else if (language == en)cout << "Sorry, buy you have already bought this prop!\n";
								}
								else if (loser == true) {
									if (language == cn)cout << "��Ǹ�������Ѿ������һ������ˡ���\n";
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
				if (language == cn)cout << "��û��Ǯ��\n";
				else if (language == en)cout << "You don't have any money at all!\n";
				hyphen(4); hyphen(4);
			}
		}
		else if (key == 'D' || key == 'd') {
			if (!(money <= 0)) {
				if (language == cn)cout << "�۸���" << money * 10 << "\n";
				else if (language == en)cout << "This time the price is $ " << money * 10 << "\n";
				still_buy();
				while (1) {
					key = getch();
					if (key == 'H') {
						if (money < money * 10 == false) {
							if (language == cn)cout << "������ʲô����\n";
							else if (language == en)cout << "What the hell have you done to the code?!\n";
							hyphen(250);
							if (invest == false) {
								if (language == cn)cout << "��Ǹ����û��Ͷ�ʣ�\n";
								else if (language == en)cout << "Sorry, but you don't have any investment!\n";
							} else {
								if (loser == true) {
									if (language == cn)cout << "��Ǹ�����Ѿ������˴˵��ߣ�\n";
									else if (language == en)cout << "Sorry, buy you have already bought this prop!\n";
								}
								else if (cheat == true) {
									if (language == cn)cout << "��Ǹ�������Ѿ������һ������ˡ���\n";
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
				if (language == cn)cout << "��û��Ǯ��\n";
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

bool det = false; //�Ƿ���
int Mdet;//������
int Pdet;//��ծ���
float Edet;//�����Ϣ
int Ddet;//��ծ����
bool Ldet = false; //�Ƿ���Ƿ����
void M_det() {		//���
	hyphen();
	if (det == false) {
		while (1) {
			if (language == cn)cout << "�����������ܳ������н�Ǯ��ʮ������\n";
			else if (language == en)cout << "Input the amount of loan you want to apply for (no more than (all the money you have)*10):\n";
			cin >> Mdet;
			if (!(Mdet <= 0)) {
				if (!(Mdet > 10 * money) && money != 0) {
					Ddet = r_events(3, 10, 1);
					Edet = r_events(3, 10, 1);
					if (language == cn) {
						cout << "�����" << Mdet << "/����Ϣ" << Edet << "%/��ծ����" << Ddet << "��\nÿ����һ�졾+" << Edet << "��%��\n";
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
							if (language == cn)cout << "�������Э�顣\n";
							else if (language == en)cout << "You give up the contract.\n";
							Mdet = 0; Edet = 0; Ddet = 0; break;
						}
					}
				} else {
					if (money == 0) {
						if (language == cn)cout << "��Ǹ�������в�������һ��һ��Ǯû�еķ��ӣ�\n";
						else if (language == en)cout << "Sorry if this is offensive (obviously this is), but the bank won't trust a nut who don't even have a dime!\n";
					} else {
						if (language == cn)cout << "��Ǹ����Ľ�������������н�Ǯ��ʮ����\n";
						else if (language == en)cout << "Sorry, but this is obviously more than ten times of all the money you have!\n";
					}
					turns--;
				}
				hyphen(4);
				break;
			} else {
				if (Mdet == 0) {
					if (language == cn)cout << "������˽��\n";
					else if (language == en)cout << "You give up the loan\n";
					turns--; break;
				}
				if (Mdet < 0) {
					if (language == cn)cout << "���������������룡\n";
					else if (language == en)cout << "The number is wrong, please input again!\n";
					hyphen(4);
				}
			}
		}
		hyphen(4);
	} else {
		if (language == cn)cout << "��Ǹ�����Ѿ�����ˣ�\n";
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
				if (language == cn)cout << "\n\n����Ҫ��������" << Pdet << "Ԫ���Ƿ񳥻��������¡�ȷ���������ܾ���\n";
				else if (language == en)cout << "\n\nYou need to pay the bank $ " << Pdet << ", are you going to pay? (Press [up button] to confirm, and press [down button] to refuse)\n";
				while (1) {
					key = getch();
					if (key == 'H') {
						if (money >= Pdet) {
							if (language == cn)cout << "�㳥���˴��\n";
							else if (language == en)cout << "You have pay off the loan.\n";
							det = false; Pdet = 0; Ldet = false; Edet = 0; money = money - Pdet;
						} else {
							if (language == cn)cout << "��Ǹ����û����������ծ�\n��������ְԱ������ſڽ������ĳ������һ�١�\n";
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
						if (language == cn)cout << "��ܾ�����ծ���������ְԱ������ſڽ������ĳ������һ�١�\n";
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
				if (language == cn)cout << "��ծ�����ѵ�������Ҫ��������" << Pdet << "Ԫ���Ƿ񳥻��������¡�ȷ���������ܾ���\n";
				else if (language == en)cout << "\n\nIt's time for you to pay back. You need to pay the bank $ " << Pdet << ", are you going to pay? (Press [up button] to confirm, and press [down button] to refuse)\n";
				while (1) {
					key = getch();
					if (key == 'H') {
						if (money >= Pdet) {
							if (language == cn)cout << "�㳥���˴��\n������ĳ��ţ�\n";
							else if (language == en)cout << "You pay off the load. Because of your honesty,\n";
							hap_plus(2);
							sad_minus(1);
							hap += 2; sad = sad - 1;
							money = money - Pdet;
							Pdet = 0; det = false; Mdet = 0; Edet = 0; Ddet = 0;
						} else {
							if (language == cn)cout << "��Ǹ����û����������ծ�\nÿ����һ�죬���ծ�+" << Edet << "��%��\n";
							else if (language == en)cout << "Sorry, but You don't have enough money to pay!\nEach day after this, your debt [+" << Edet << "]%!\n";
							Mdet = 0; Ddet = 0;
							Ldet = true;
						}
						hyphen(3);
						break;
					}
					if (key == 'P') {
						if (language == cn)cout << "��ܾ�����ծ�\nÿ����һ�죬���ծ�+" << Edet << "��%��\n";
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

//��������
void interact() {
	cout << "\n";
	if (key == 'Q' || key == 'q') {
		if (language == cn)cout << "���˳���\n";
		else if (language == en)cout << "You quit the game.\n";
		pause(4);
	}
	else if (key == 'F' || key == 'f') {
		if (language == cn)cout << "��ιʳ�˳���\n";
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
				cout << "\n\n������\nA.�ó�����й������\nB.��������\nC.�˳�ҳ��\n";
			}
			else if (language == en) cout << "\n\nINTERACTIONS:\nA.Let your pet to defecate\nB.Pat your pet\nC.Quit this menu\n";
			key = getch();
			if (key == 'A' || key == 'a') {
				if (language == cn)cout << "������ĳ���" << name << "���������������ϵ����ź���й���ۺ��Թ���\n";
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
				if (language == cn)cout << "�㸧������ĳ���" << name << "\n";
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
		if (language == cn)cout << "---����---\n";
		else if (language == en)cout << "---LIFESPAN---\n";
		your_pet();
		if (Pab == cat) {
			if (language == cn)cout << "��è\n";
			else if (language == en)cout << "is a cat.\n";
		}
		else if (Pab == dog) {
			if (language == cn)cout << "�ǹ�\n";
			else if (language == en)cout << "is a dog.\n";
		}
		your_pet();
		if (language == cn)cout << "����" << age << "��\n";
		else if (language == en)cout << "is " << age << " years old now\n";
		your_pet();
		if (language == cn)cout << "���ܻ�" << lifespan - days + 1 << "��\n";
		else if (language == en)cout << "can still live for " << lifespan - days + 1 << " days\n";
		your_pet();
		if (language == cn)cout << "��Ҫ�ﵽ�����" << Lifespanhap << "�����ֵ���ϲ���ʹ��������\n";
		else if (language == en)cout << "need to have at least reach to [Happiness: " << Lifespanhap << "] to prolong lifespan\n";
		if (language == cn)cout << "---���---\n";
		else if (language == en)cout << "---EMOTION---\n";
		if (language == cn) {
			cout << "������ֵ��" << hap << "/" << max_hap << "��\n������ֵ��" << sad << "/" << max_sad << "��\n";
		}
		else if (language == en) {
			cout << "[Happiness: " << hap << "/" << max_hap << "]\n[Sadness: " << sad << "/" << max_sad << "]\n";
		}
		if (language == cn)cout << "---����---\n";
		else if (language == en)cout << "---PHYSIOLOGY---\n";
		if (language == cn) {
			cout << "��Ҫ��й��";
			if (poo == true) cout << "��\n";
			else cout << "��\n";
		}
		else if (language == en) {
			cout << "Wants to defecate:";
			if (poo == true)cout << "[YES]\n";
			else cout << "[NO]\n";
		}
		if (language == cn) {
			cout << "��Ҫ��ʳ��";
			if (eat == true) cout << "���ǡ�\n";
			else cout << "����\n";
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
				cout << "�㻹��" << money << "ԪǮ\n��Ҫ���е���һ�������ǣ�\nA.�������\nB.����ʳ��\nC.���\nD.���\nE.�˳�ҳ��\n";
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
			if (language == cn)cout << "����Ͷ�ʽ�" << Iinvest << "Ԫ\nͶ�ʹ���ȴ���" << Dinvest - days << "��\n";
			else if (language == en)cout << "Money you have invested: $ " << Iinvest << "\nYou need to wait for: " << Dinvest - days << "days\n";
		} else {
			hyphen(3);
			if (language == cn)cout << "\n������ѡ��\n";
			else if (language == en)cout << "\nPlease choose again!\n";
			notice();
			key = getch(); interact();
		}
	}
	else if (key == 'B' || key == 'b') {
		colorc(blue);
		if (language == cn)cout << "����" << sug << "����\n����" << sul << "����\n����" << sod << "���մ�\n����" << wat << "����ˮ�����ӵ��1000������\n����" << flo << "�����\n";
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
					cout << CDSS << "." << backpackmeal[CDSS] << "|������" << backpackcalr[CDSS] << "|Ч����" << backpackeffect[CDSS] << "|";
					cout << "������" << backpackall[CDSS] << "\n";
				}
				else if (language == en) {
					cout << CDSS << "." << backpackmeal[CDSS] << "|Energy: " << backpackcalr[CDSS] << "|Effect: " << backpackeffect[CDSS] << "|";
					cout << "Amount: " << backpackall[CDSS] << "\n";
				}
				CDSS++;
			}
			pause();
			while (1) {
				if (language == cn)cout << "����Ҫ���в�������Ʒ�ı�ţ����븺���˳���ҳ�棩��";
				else if (language == en) cout << "Input the number of item you want to choose (insert negative number to quit this menu):";
				cin >> CTP;
				if (CTP >= Cid || CTP < 0) {
					break;
				} else {
					hyphen(4);
					if (language == cn)cout << "A.������ʳƷ\nB.����ʳƷι������\nC.����ʳƷ�ӵ�\nD.�˳���ҳ��\n";
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
							if (language == cn)cout << "���ӵ�" << CTP << "��ʳƷ\n";
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
			if (language == cn)cout << "��û���κ����Ʒ��\n";
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
		cout << "A.�˳��˽���\nB.���������̳�\nC.����¼������̳�\nD.���ϵͳ�����̳�\nE.���ϵͳ�����̳�\nF.��������\n";
		while (1) {
			key = getch();
			if (key == 'A' || key == 'a') break;
			else if (key == 'B' || key == 'b') {
				hyphen(4);
				cout << "��.���ڿ�ʼ��Ϸʱ�л�ΪӢ�����뷨\n";
				cout << "��.���������Ϸ�а��°���ѡ��ͬ�ж���һ����8���غ�ѡ���ж�������S����������C���鿴����״̬������ռ�ûغϡ�\n";
				cout << "��.��Ϸ��������������ֵ�������Ƿ���Ҫ��й�����������Ҫ��й��ÿ�ȴ�һ�غϻ�۳�����ֵ�����ӱ���ֵ���������Ƿ�\n��Ҫ��ʳ�����������Ҫ��ʳ��ÿ�ȴ�һ�غϻ�۳�����ֵ�����ӱ���ֵ�����������ֵ��100����\n�����ﱯ��ֵ��50��������ֵ���������������\n";
				pause(); break;
			}
			else if (key == 'C' || key == 'c') {
				hyphen(4);
				cout << "����Ϸ����>=1ʱ��0.1.1�����ϵİ汾�ᴥ������¼�������¼��У�\n";
				cout << "��.����Ϊ����������С�Ľ�Ǯ��0~35Ԫ��Ϊ0Ԫʱ�������� \n��.���ﵣ�����Ͷ���ˣ����Ͷ��ȫ����Ǯ�������ӳ���Ŀ���ֵ�ͼ��ٱ���ֵ��������������������֣���25%���ʳɹ�����Ǯ�ر���10%-50%\n";
				cout << "��.����������Ʒ����������Ʒ���ֱ���40%��40%��20%�ĸ��ʴ���\n��.���ﴴ����һ��ǰ��ҡ���ֶӡ�����Ϊ�������Ǯ����һ��������¼���ֻ���Դ���һ�Σ�\n��.����Ϊ���������ʳ���е�����һ�֣�������һ��1~35�������\n";
				pause(); break;
			}
			else if (key == 'D' || key == 'd') {
				hyphen(4);
				cout << "����M��������Ǯ���档����Ľ��ܴ��ڱ����Ǯ��ʮ������������ǮΪ0���򲻿ɽ����\n�������Ϣ��1%��10%֮�䣬��ծ����Ϊ���������������涨������δ��ծ����ÿ��һ��ծ������ԭ�����ʡ������ծ��������ÿһ�μ��ٿ���ֵ�����ӱ���ֵ\n";
				pause(); break;
			}
			else if (key == 'E' || key == 'e') {
				hyphen(4);
				cout << "δ���ţ�\n";
				pause(); break;
			}
			else if (key == 'F' || key == 'f') {
				hyphen(4);
				cout << "��Ϸ�ڣ�����һ����è���������֡��������ֵļ�����������������ͬ��è�ļ���������2�굽4�������������ļ���������1��뵽5��������\n";
				cout << "\n������¼��������ǰ��ҡ���ֶӡ��жȹ������������ڳ���������ڡ�������ڰ���C��鿴����������������������ǲ��������ģ�������һ��ʼӵ��һ��85-60����������Ϊ������������Ҫ�ﵽ�Ŀ���ֵ�ĵ�������ÿ�죬�����ֵ���᡾+5����һֱ���޷��ٴ�����Ϊֹ���������Ŀ���ֵ�������ֵ���ҳ���ı���ֵС��15����������+1����һ��İ˻غ��ڣ�ֻ�������غ��������ӡ�\n";
				pause(); break;
			}
		}
		system("cls"); turns--;
	}
	/*else if(key=='K'||key=='k') {
		hyphen(4);
		cout <<"A.�浵\nB.�鿴�浵\nC.����\nD.�˳�����\n";
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
		cout << "���������룺"; cin >> cheating; cout << "\n";
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

void o_days() {//ÿһ�캯�����ڼ��������¼�
	hyphen(2);
	Cfour();
	e_hap();
	e_sad();
	e_poo();
	e_eat();
	M_();
	e_age();
	if (cheatable == true)cout << "*";
	if (language == cn)cout << "���ǵ�" << days << "�졣\n";
	else if (language == en)cout << "DAY " << days << " .\n";
	if (det == true && Ldet == true)Dgm = true;
	if (eat == true) {
		if (language == cn)cout << "��ĳ���" << name << "��Ҫ��ʳ\n";
		else if (language == en)cout << "Your pet " << name << " is hungry\n";
	}
	if (poo == true) {
		if (language == cn)cout << "��ĳ���" << name << "��Ҫ��й\n\n";
		else if (language == en) cout << "Your pet " << name << " wants to defecate\n\n";
	}
	if (Pmouse == true) {
		Pmouse_plus = r_events(1784, 5, 1);
		if (language == cn)cout << "��ĳ����������ֻ�������\n";
		else if (language == en)cout << "Your pet is playing with the toy mouse.\n";
		hap_plus(Pmouse_plus);
		hap += Pmouse_plus;
	}
	if (BFS == true) {
		Msenting = r_events(1321, 500, 20);
		if (language == cn)cout << "�������Կ���" << name << "�ػظ�̳��Ϊ�ˣ����Ƿ���" << Msenting << "Ԫ��\n";
		else if (language == en)cout << "Some fans want " << name << " to keep performing, so they put $ " << Msenting << " .\n";
		money_plus(Msenting);
		money = money + Msenting;
	}
	if (lifespan < 0)lifespan = 0; //��ֹ����С��0
	if (days == lifespan) {
		if (language == cn)cout << "��������Ļ����⽫������ĳ������������һ�졣\n";
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
		//cout <<turns<<"\n";//����
		if (lifespan < 0)lifespan = 0; //��ֹ����С��0
		if (days >= lifespan + 1) { //��������������>=��Ϊ�˷�ֹ������ĳ������³�Ϊ����
			death(); died = true;
		}
		//cout <<"poo"<<w_poo<<"eat"<<w_eat<<"\n";//����
		//cout <<"���"<<det<<"/��Ϣ"<<Edet<<"/��"<<Ddet<<"/ծ��"<<Pdet<<"/���"<<Ldet<<"\n\n";//����
		//cout <<"����"<<Dinvest<<"\n";//����
		M_();
		Cfour();
		e_hap();
		e_sad();
		e_poo();
		e_eat();
		if (died == true) break; //����
		notice();
		key = getch();
		interact();
		if (key == 'Q' || key == 'q') break; //�˳�
		turns++; w_eat++;
		if (days != 1) {
			w_poo++;
		}
		if (w_eat > 2)eat = true;
		if (w_poo > 4)poo = true;
		cout << "\n\n";
		if (eat == true) {
			your_pet();
			if (language == cn)cout << "��Ҫ��ʳ\n";
			else if (language == en)cout << "is hungry\n";
		}
		if (poo == true) {
			your_pet();
			if (language == cn)cout << "��Ҫ��й\n\n\n";
			else if (language == en)cout << "wants to defecate\n\n\n";
		}
		hyphen(1);
		cout << "\n\n";
		if (turns == 9) {
			break; hyphen();
		}
	}
	if (invest == true && days == Dinvest) { //����¼�����Ͷ��
		invest = false;
		Dinvest = 0;
		randomnum = r_events(3, 4, 1);
		Einvest = r_events(3, 50, 10);
		if (cheat == false) {
			if (loser == false) {
				if (randomnum == 2) {
					your_pet();
					if (language == cn)cout << "Ͷ�ʳɹ��ˣ�\n������" << Einvest << "%��\n";
					else if (language == en)cout << "has made a successful investment��\nRate of profit " << Einvest << "%!\n";
					money_plus(IINVEST + Einvest / 100 * IINVEST);
					hap_plus(2);
					money = money + IINVEST + Einvest / 100 * IINVEST; hap += 2;
				} else {
					your_pet();
					if (language == cn)cout << "Ͷ��ʧ���ˣ�\n";
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
				if (language == cn)cout << "Ͷ�ʳɹ��ˣ�\n������" << Einvest << "%��\n";
				else if (language == en)cout << "has made a successful investment��\nRate of profit: " << Einvest << "%��\n";
				money_plus(IINVEST + Einvest / 100 * IINVEST);
				hap_plus(2);
				money = money + IINVEST + Einvest / 100 * IINVEST;
				hap += 2;
			} else {
				if (language == cn)cout << "Ͷ��ʧ���ˣ�\n";
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
	Mname(); Mname1(); //��⿱�����ֵ
	cout << "Digital Pet\n" << vertion << " " << phase;
	if (cheatable == true)cout << "*";
	cout << "\nProgramming��֮��\nTesting�����С�Mary Lee\nCreators��֮�ԡ�����\nArt��...\nSound Effect��...\n";
	hyphen(4);
	cout << "���������������������(Press any key to continue...)\n";
	getch();
	language_choose();
	color_choose();
	name_choose();
	per();
	pause();
	if (language == cn)cout << "���ǽ���ȹ����õ�ʱ�⣬������\n�㿴����ĳ��ͻȻ��ʶ����Ҳ����Գ�Ϊ���޸��ǡ�\n";
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