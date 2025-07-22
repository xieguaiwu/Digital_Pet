#include"basicfunc.h"

bool have_parts[all_parts];
bool parts_changed;

void have_body_ini() {
	for (int i = 0; i < all_parts; ++i) {
		have_parts[i] = true;
	}
}

void certain_body_give(bool CertainGiveWhich, int CertainStart, int CertainEnd) {
	for (int i = CertainStart; i < CertainEnd; ++i) {
		have_parts[i] = CertainGiveWhich;
	}
}

class TypesGive {
public:
	static void face_type_give(bool FaceGiveWhich) {
		certain_body_give(FaceGiveWhich, body_pieces, body_pieces + face_pieces);
	}

	static void arm_type_give(bool ArmGiveWhich) {
		certain_body_give(ArmGiveWhich, body_pieces + face_pieces, body_pieces + face_pieces + arm_pieces);
	}

	static void leg_type_give(bool LegGiveWhich) {
		certain_body_give(LegGiveWhich, body_pieces + face_pieces + arm_pieces, body_pieces + face_pieces + arm_pieces + leg_pieces);
	}
};

//直接在此函数下增加对器官的描述
void have_body() {
	if (!have_parts[head]) {
		TypesGive::face_type_give(false);
	}
	if (!have_parts[neck]) {
		have_parts[head] = false;
		TypesGive::face_type_give(false);
	}
	if (!have_parts[torso]) {
		TypesGive::arm_type_give(false);
		TypesGive::leg_type_give(false);
	}
	//arm
	if (!have_parts[left_arm]) {
		certain_body_give(false, left_hand, left_hand_finger_nail + 1);
	}
	if (!have_parts[right_arm]) {
		certain_body_give(false, right_hand, right_hand_finger_nail + 1);
	}
	//hand
	if (!have_parts[left_hand]) {
		certain_body_give(false, left_hand_finger, left_hand_finger_nail + 1);
	}
	if (!have_parts[right_hand]) {
		certain_body_give(false, right_hand_finger, right_hand_finger_nail + 1);
	}
	//finger
	if (!have_parts[left_hand_finger]) {
		have_parts[left_hand_finger_nail] = false;
	}
	if (!have_parts[right_hand_finger]) {
		have_parts[right_hand_finger_nail] = false;
	}
	//leg
	if (!have_parts[left_leg]) {
		certain_body_give(false, left_foot, left_foot_toes + 1);
	}
	if (!have_parts[right_leg]) {
		certain_body_give(false, right_foot, right_foot_toes + 1);
	}
	//foot
	if (!have_parts[left_foot]) {
		have_parts[left_foot_toes] = false;
	}
	if (!have_parts[right_foot]) {
		have_parts[right_foot_toes] = false;
	}
}


//编辑宠物身体时修改parts_changes
void body_describe() {
	if (parts_changed)have_body();
	notices::your_pet();

}