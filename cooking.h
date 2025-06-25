#include<iostream>
using namespace std;

int cs;
//所有食材总量
long long Camount;
//原料
long long Msug;//糖
long long Msul;//盐
long long Msod;//苏打
long long Mwat;//水
long long Mflo;//面粉

//热量
int Mcalr;

int Ncook;//菜品名称
int Tcook;//菜品口味
float Ecook;//菜品效果

int meal_effect() {//菜品效果
	if (Tcook == sweet) {
		if (Ncook == soda)Ecook = hapup15; //口味是甜的，菜品是苏打水，快乐+15
		else if (Ncook == flor)Ecook = sadup5; //口味是甜的，菜品是面糊，悲伤+5
		else if (Ncook == cake)Ecook = lifeup1; //口味是甜的，菜品是蛋糕，寿命【+1】
		else if (Ncook == indefine)Ecook = Sadup5; //口味是甜的，菜品是不可名状物体，悲伤值上限【+5】
		else if (Ncook == bananas)Ecook = sadlow5; //口味是甜的，菜品是带水的苏打，悲伤值【-5】
		else Ecook = Hapup5; //其他：快乐值上限【+5】
	}
	else if (Tcook == Vsweet) {
		if (Ncook == soda)Ecook = sadlow8; //口味是非常甜的，菜品是苏打水，寿命【-1】
		else if (Ncook == flor)Ecook = sadup8; //口味是非常甜的，菜品是面糊，悲伤值+8
		else if (Ncook == cake)Ecook = lifeup2; //口味是非常甜的，菜品是蛋糕，生命值上限+15
		else if (Ncook == indefine)Ecook = sadup8; //口味是非常甜的，菜品是不可名状物体，悲伤值+8
		else if (Ncook == bananas)Ecook = sadlow8; //口味是非常甜的，菜品是带水的苏打，生命值【-8】
		else Ecook = Sadup5;//其他：悲伤值上限【+5】
	}
	else if (Tcook == sult) {
		if (Ncook == soda)Ecook = Hapup15; //口味是咸的，菜品是苏打水，快乐值上限【+15】
		else if (Ncook == indefine)Ecook = Sadup10; //口味是咸的，菜品是不可名状物体，悲伤值上限【+10】
		else if (Ncook == flor)Ecook = hapup10; //口味是咸的，菜品是面糊，快乐值【+10】
		else if (Ncook == bread)Ecook = lifeup2; //口味是咸的，菜品是面包，寿命【+2】
		else if (Ncook == bananas)Ecook = sadup8; //口味是咸的，菜品是带水的苏打，悲伤值【+8】
		else if (Ncook == cake)Ecook = sadup5; //口味是咸的，菜品是蛋糕，悲伤值【+5】
		else Ecook = Haplow5; //快乐值上限【-5】
	}
	else if (Tcook == Vsult) {
		if (Ncook == soda)Ecook = lifeup1; //口味是非常咸的，菜品是苏打水，寿命【+1】
		else if (Ncook == flor)Ecook = Sadup10; //口味是非常咸的，菜品是面糊，悲伤值上限【+15】
		else if (Ncook == bread)Ecook = Hapup15; //口味是咸的，菜品是面包，快乐值上限【+15】
		else if (Ncook == bananas)Ecook = lifelow1; //口味是咸的，菜品是带水的苏打，寿命【-1】
		else if (Ncook == cake)Ecook = sadup8; //口味是咸的，菜品是蛋糕，悲伤值【-8】
		else Ecook = Haplow15; //不可名状物体-快乐值上限【-15】
	}
	else if (Tcook == mois) {

	}
	else if (Tcook == Vmois) {

	}
	else if (Tcook == too_sod) {

	}
	else if (Tcook == floy) {

	}
	else if (Tcook == Vfloy) {

	}
	else if (Tcook == dry) {

	}
	else Ecook = none;

	return Ecook;
}

int meal_all() { //总量
	return Camount;
}

int meal_nam() {	//菜名
	//cout <<"sod"<<Msod<<"|sul"<<Msul<<"|sug"<<Msug<<"|wat"<<Mwat<<"\n";//-调试用
	if (Msod > 0 && Mwat > 0) {
		if (Mwat <= Msod && Mflo > 0 && Mwat <= (Msug + Msul + Msod + Mwat + Mflo) / 5 && Mflo > Msod && Msug <= Msul && Msug <= Msod && Msug <= Mwat && Msug <= Mflo) {
			Ncook = bread; //面包：水含量小于等于苏打含量、面粉含量大于零、水含量小于等于20% 、面粉含量大于小苏打含量、糖分含量小于等于其他全部
		}
		else if (Mwat <= Msod && Mflo > 0 && Mwat <= (Msug + Msul + Msod + Mwat + Mflo) / 5 && Mflo > Msod && Msug > Msul && Msug > Msod && Msug > Mwat && Msug > Mflo) {
			Ncook = cake; //蛋糕：水含量小于等于苏打含量、面粉含量大于零、水含量小于等于20% 、面粉含量大于小苏打含量、糖分含量大于其他全部成分
		}
		else if (Mwat > Msod) {
			Ncook = soda; //苏打水：水含量大于苏打含量
		}
		else if (Msod > Mwat) {
			Ncook = bananas; //带水的苏打 ：苏打含量大于水含量
		}
		else  Ncook = indefine; //不可名状
	}
	else if (Mflo > 0 && Mwat > 0) {
		if (Mwat <= Msod && Msod > 0 && Mwat <= (Msug + Msul + Msod + Mwat + Mflo) / 5 && Mflo > Msod && Msug <= Msul && Msug <= Msod && Msug <= Mwat && Msug <= Mflo) {
			Ncook = bread; //面包：水含量小于等于苏打含量、面粉含量大于零、水含量小于等于20% 、面粉含量大于小苏打含量、糖分含量小于等于其他全部
		}
		else if (Mwat <= Msod && Msod > 0 && Mwat <= (Msug + Msul + Msod + Mwat + Mflo) / 5 && Mflo > Msod && Msug > Msul && Msug > Msod && Msug > Mwat && Msug > Mflo) {
			Ncook = cake; //蛋糕：水含量小于等于苏打含量、面粉含量大于零、水含量小于等于20% 、面粉含量大于小苏打含量、糖分含量大于其他全部成分
		}
		else Ncook = flor; //面糊：面粉含量和水含量都大于零
	}
	else {
		Ncook = indefine; //不可名状
	}
	return Ncook;
}

int meal_tas() { //菜品口味
	if (Msug > Msul && Msug > Msod && Msug > Mwat && Msug > Mflo) { //糖分含量大于其他全部成分
		if (Msug >= (Msug + Msul + Msod + Mwat + Mflo) / 2)Tcook = Vsweet; //当糖分含量大于全体50%时，口味过甜
		else Tcook = sweet;
	}
	else if (Msul > Msug && Msul > Msod && Msul > Mwat && Msul > Mflo) { //盐分含量大于其他全部成分
		if (Msul >= (Msug + Msul + Msod + Mwat + Mflo) / 2)Tcook = Vsult; //当盐分含量大于全体50%时，口味过咸
		else Tcook = sult;
	}
	else if (Mwat > Msug && Mwat > Msod && Mwat > Msul && Mwat > Mflo) { //水分含量大于其他全部成分
		if (Mwat >= (Msug + Msul + Msod + Mwat + Mflo) / 2)Tcook = Vmois; //当水分含量大于全体50%时，口味过湿
		else Tcook = mois;
	}
	else if (Msod > Msug && Msod > Mwat && Msod > Msul && Msod > Mflo) { //苏打含量大于其他全部成分
		Tcook = too_sod;
	}
	else if (Mflo > Msug && Mflo > Msod && Mflo > Msul && Mflo <= Mwat) { //面粉含量大于其他全部成分，且小于等于水分含量
		if (Mflo >= (Msug + Msul + Msod + Mwat + Mflo) / 2)Tcook = Vfloy; //当面粉含量大于全体50%时，口味过软
		else Tcook = floy;
	}
	else if (Mflo > 0 && Mwat == 0) { //面粉含量大于零，水含量等于0
		Tcook = dry;
	}
	else {
		Tcook = flat; //平淡
	}
	return Tcook;
}