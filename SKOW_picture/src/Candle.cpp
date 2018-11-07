#include "Candle.h"


Candle::Candle(void)
{
}


Candle::~Candle(void)
{
}

//���E�\�N����������̐ݒ������֐�
void Candle::setpos(float tempXpos, float tempYpos){
	
	//���͂��ꂽ�Q�̒l�����Ƃ�xpos,ypos�����B
	xpos = tempXpos;
	ypos = tempYpos;

	//�n�܂肪���t���[���ڂ��B�����_���B
    frame = ofRandom(10);
    //�΂̃T�C�Y�B���̏����������邱�Ƃłǂ̉𑜓x�ł��Ή��ł���悤�ɂ��Ă���B
	size = 22*ofGetWidth()/1920;

	//�΂̉摜�_�E�����[�h
	for(int i=0;i<NUM;i++){
        char char1[32];
        sprintf(char1, "candle%d.png", i+1);
		candleImg[i].loadImage(char1);
	}
}

//���E�\�N�̃A�b�v�f�[�g�B�t���[�����ƂɌĂяo�����B
void Candle::update(ofVec2f pos,float scale){
	//�ǂꂾ�����s�ɂ���邩�ƃX�P�[���̍Ē�`
	offset = pos;
	localScale = scale;
	//�΂̃t���[���̍X�V�B10�܂ōs������0�ɖ߂�
	frame++;
	if(frame==10){frame=0;}
}

void Candle::display(){
	//�΂̔w�i�̂悭�킩��Ȃ��F�̒����`�̕`��
	ofFill();
	ofSetColor(6,25,32);
	ofRect(offset.x+(xpos*localScale*ofGetWidth()/1920),offset.y+(ypos*localScale*ofGetWidth()*9/16/1080),size/2*localScale,size*localScale);
}

void Candle::display_fire(){
	//�΂̕`��
    ofSetColor(255);
    candleImg[frame].draw(offset.x+(xpos*localScale*ofGetWidth()/1920),offset.y+(ypos*localScale*ofGetWidth()*9/16/1080),size/2*localScale,size*localScale);
}

//�΂����������ɕ`��
void Candle::out(){
	//�΂̔w�i�̂悭�킩��Ȃ��F�̒����`�̕`��
	ofFill();
	//ofSetColor(10,42,53);
	ofSetColor(0,0,0);
	ofRect(offset.x+(xpos*localScale*ofGetWidth()/1920),offset.y+(ypos*localScale*ofGetWidth()*9/16/1080),size/2*localScale,size*localScale);
  }

//fix
void Candle::fix(){
	frame--;
}