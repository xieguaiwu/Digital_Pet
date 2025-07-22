#include<iostream>

//定义：身体
enum BodyType {
	head,
	neck,
	torso
};//0~body_pieces-1

const char body_pieces = 3;

enum FaceType {
	left_eye = body_pieces,
	right_eye,
	nose,
	mouth,
	face
};//body_pieces~body_pieces+face_pieces-1

const char face_pieces = 5;

enum ArmType {
	left_arm = body_pieces + face_pieces,
	right_arm,
	left_hand,
	left_hand_finger,
	left_hand_finger_nail,
	right_hand,
	right_hand_finger,
	right_hand_finger_nail
};//body_pieces+face_pieces~body_pieces+face_pieces+arm_pieces-1

const char arm_pieces = 8;

enum LegType {
	left_leg = body_pieces + face_pieces + arm_pieces,
	left_foot,
	left_foot_toes,
	right_leg,
	right_foot,
	right_foot_toes
};

const char leg_pieces = 6;

const unsigned char all_parts = body_pieces + face_pieces + arm_pieces + leg_pieces;

bool have_parts[all_parts];

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

void body_describe() {

}