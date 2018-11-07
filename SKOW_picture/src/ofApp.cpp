#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//�����ݒ�
	//offset:�[����ǂꂭ�炢�G������Ă��邩�B�Q�����x�N�g��
	//allScale:��ʂ̃T�C�Y
	offset = ofVec2f(0,0);
	al = 255;
	fl = 0;
	allScale = 1;

	//myCandle�̓��E�\�N�̃C���X�^���X�Bsetpos�ňʒu���w�肵�Ă���B
	myCandle[0].setpos(568,495);
	myCandle[1].setpos(584,496);
	myCandle[2].setpos(598,478);
	myCandle[3].setpos(619,494);
	myCandle[4].setpos(1173,494);
	myCandle[5].setpos(1195,472);
	myCandle[6].setpos(1210,493);
	myCandle[7].setpos(1220,493);

	/*�@candle_f:true�������炻�̈����Ɠ������E�\�N������
		candle_fix:true�������炻�̈����Ɠ���Candle��fix���Ăяo��
		candle_all:candle_f���ꊇ��ON/OFF����B
		fukase�Ȃ�:�����o�[�̓����x���Ǘ�����bool
		��U���ׂ�false�ɏ��������Ă���			*/
	for(int i=0;i<8;i++){
		candle_f[i]=false;
		candle_fix[i]=false;
	}
	candle_all=false;
	fukase=saori=love=nakajin=false;

	//���ꂼ��̉摜�̓ǂݍ���
	back.loadImage("vippicture_base4.png");
	trim.loadImage("trim.jpg");
	fukaseImg.loadImage("new_fukase.png");
	saoriImg.loadImage("new_saori.png");
	LOVEImg.loadImage("new_LOVE.png");
	nakajinImg.loadImage("new_nakajin.png");
	light.loadImage("LIGHT_highq.png");

	//�t���[�����[�g�B�Ƃ肠����24
	ofSetFrameRate(24);

	//sec:���̕b��
	//presec:�P�t���[���O�̕b��
	//���̓�̐����ς���������擾���A�b�����X�V���ꂽ�u�Ԃ��擾����
	presec=sec=0;

	//idle��true�̊Ԃ͊G��S�̂��Î~����B�L�[���͂������Ȃ��B
	idle=false;

	//calibMode��true�Ȃ�idle�������ŕω����Ȃ��B�����ƃL�����u���[�V�����ł���B�{�Ԏ��ɂ�false�ɖ߂��Ă��������B
	calibMode=false;

	PinMode=true;

	//�|�C���g�̒�`
	point[3] = ofPoint(50,50);
	point[2] = ofPoint(ofGetWidth()-400,75);
	point[1] = ofPoint(ofGetWidth()-400,ofGetHeight()-175);
	point[0] = ofPoint(75,ofGetHeight()-175);

	for(int i=0;i<4;i++){
		pointSelected[i]=false;
	}
}

//--------------------------------------------------------------
void ofApp::update(){

	//�J�[�\���̕\���ɂ���
	if(PinMode){
		ofShowCursor();
	}else{
		ofHideCursor();
	}

	//�����Ń��E�\�N�Ɛl���������߂̏�ԑJ�ځB�����炭�����������邱�Ƃ͂Ȃ��̂ŃX���[�B
	if(!calibMode){
		sec=ofGetSeconds();
		if(presec != sec && sec%5==0){
			cout<<sec<<endl;

			if(sec%10==5){
				idle=true;

				int seed = ofRandom(0,100);
				if(seed<25){
					nakajin=true;
				}else if(seed<50){
					saori=true;
				}else if(seed<75){
					fukase=true;
				}else{
					love=true;
				}
				int seed2 = ofRandom(0,100);
				if(seed2<8){
					nakajin=true;
				}else if(seed2<16){
					saori=true;
				}else if(seed2<24){
					fukase=true;
				}else if(seed2<32){
					love=true;
				}

				for(int i=0;i<8;i++){
					int seed3 = ofRandom(0,100);
					if(seed3<24){
						candle_f[i]=true;
					}
				}

			}else if(sec%10==0){
				idle=false;
			}

			if(sec==50){
				idle=false;
				for(int i=0;i<8;i++){
					candle_f[i]=true;
				}
				fukase=true;
				nakajin=true;
				love=true;
				saori=true;
			}else if(sec==0){
				idle=false;
				for(int i=0;i<8;i++){
					candle_f[i]=false;
				}
				fukase=false;
				nakajin=false;
				love=false;
				saori=false;
			}
		}
		presec=sec;
	}

	//idle��true�Ȃ��Candle�N���X��update�����s����B
	if(!idle){
		for(int i=0;i<8;i++){
			myCandle[i].update(offset,allScale);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	//�w�i��`��
	ofBackground(0);
	ofSetColor(180);
	back.draw(offset.x,offset.y,ofGetWidth()*allScale,ofGetWidth()*allScale*9/16);

	//���E�\�N�̕`��
	for(int i=0;i<8;i++){
		myCandle[i].display();
		if(candle_f[i]){
			myCandle[i].out();
		}
		if(candle_fix[i]){
			myCandle[i].fix();
		}
	}
    for(int i=0;i<8;i++){
		if(!candle_f[i]){
			myCandle[i].display_fire();
		}
    }
	if(candle_all){
		for(int i=0;i<8;i++){
			candle_f[i]=0;
			myCandle[i].out();
		}
	}

	//�����o�[�̕`��
	if(!fukase){
		fukase_alpha=0;
	}else{
		ofSetColor(180,fukase_alpha);
		fukaseImg.draw(offset.x,offset.y,ofGetWidth()*allScale,ofGetWidth()*allScale*9/16);
		if(fukase_alpha<255){fukase_alpha+=32;}
	}

	if(!saori){
		saori_alpha=0;
	}else{
		ofSetColor(180,saori_alpha);
		saoriImg.draw(offset.x,offset.y,ofGetWidth()*allScale,ofGetWidth()*allScale*9/16);
		if(saori_alpha<255){saori_alpha+=32;}
	}
	
	if(!love){
		love_alpha=0;
	}else{
		ofSetColor(180,love_alpha);
		LOVEImg.draw(offset.x,offset.y,ofGetWidth()*allScale,ofGetWidth()*allScale*9/16);
		if(love_alpha<255){love_alpha+=32;}
	}
	
	if(!nakajin){
		nakajin_alpha=0;
	}else{
		ofSetColor(180,nakajin_alpha);
		nakajinImg.draw(offset.x,offset.y,ofGetWidth()*allScale,ofGetWidth()*allScale*9/16);
		if(nakajin_alpha<255){nakajin_alpha+=32;}
	}
  
	//��̃��C�g�̕`��
	ofSetColor(255);
	light.draw(offset.x+(166*allScale),offset.y,
               light.getWidth()*ofGetWidth()/1920*allScale,
               light.getHeight()*ofGetWidth()*9/16/1080*allScale);
	light.draw(offset.x+(-599*allScale),offset.y,
               light.getWidth()*ofGetWidth()/1920*allScale,
               light.getHeight()*ofGetWidth()*9/16/1080*allScale);
	light.draw(offset.x+(931*allScale),offset.y,
               light.getWidth()*ofGetWidth()/1920*allScale,
               light.getHeight()*ofGetWidth()*9/16/1080*allScale);

	ofTexture tex;
	ofLoadImage(tex,"new_fukase.png");
	tex.loadScreenData(0,0,ofGetWidth(),ofGetHeight());

	ofBackground(0);
	if(PinMode){
		for(int i=0;i<4;i++){
			ofNoFill();
			ofSetColor(255);
			if(pointSelected[i]){
				ofSetColor(255,0,0);
			}
			ofSetLineWidth(2);
			ofCircle(point[i],20);
		}
	}
	ofSetColor(255);
	tex.draw(point[0],point[1],point[2],point[3]);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	//�L�[���́Bidle��false�̊Ԃ����󂯕t����B
	if(!idle){

		//���L�[�ŕ��s����
		if(key == OF_KEY_UP){
			offset.y -= 0.5;
		}else if(key == OF_KEY_DOWN){
			offset.y += 0.5;
		}else if(key == OF_KEY_RIGHT){
			offset.x += 0.5;
		}else if(key == OF_KEY_LEFT){
			offset.x -= 0.5;
		}
  
		//���s�ړ��ȊO�̃L�����u���[�V�����B
		//fl��al�͉��Ɏg���Ă邩���͂悭�킩��Ȃ�����processing���̕����c���Ă���܂��B
		if(key == '0'){fl = 255;}
		if(key == 'b'){fl = 0;}
		if(key == 'k'){allScale += 0.003;}
		if(key == 'm'){allScale -= 0.002;}
		if(key == 'z'){al = 255;}
		if(key == 'x'){al = 0;}

		if(key == 'p'){PinMode=!PinMode;}

		//CONTROLE�ŁA���̉摜��X���W(offset.x)�AY���W(offset.y)�AallScale���ucalibration.txt�v�ɕۑ��B
		/*if(key == OF_KEY_CONTROL){
			char calibrationNum[32];
			sprintf(calibrationNum, "%f\n%f\n%f", offset.x,offset.y,allScale);
			ofBuffer buffer = ofBuffer(calibrationNum);
			ofBufferToFile("calibration.txt",buffer);
		}*/

		//�����o�[�̕`���ON/OFF
		if(key == 'f'){if(fukase==1){fukase=0;}else{fukase=1;}}
		if(key == 's'){if(saori==1){saori=0;}else{saori=1;}}
		if(key == 'l'){if(love==1){love=0;}else{love=1;}}
		if(key == 'n'){if(nakajin==1){nakajin=0;}else{nakajin=1;}}

		//���E�\�N��ON/OFF
		if(key == 'a'){candle_all = !candle_all;}
		if(key == '1'){candle_f[0] = !candle_f[0];}
		if(key == '2'){candle_f[1] = !candle_f[1];} 
		if(key == '3'){candle_f[2] = !candle_f[2];} 
		if(key == '4'){candle_f[3] = !candle_f[3];} 
		if(key == '5'){candle_f[4] = !candle_f[4];}
		if(key == '6'){candle_f[5] = !candle_f[5];}
		if(key == '7'){candle_f[6] = !candle_f[6];} 
		if(key == '8'){candle_f[7] = !candle_f[7];}
		
		//���E�\�N��fix
		if(key == 'q'){candle_fix[0] = !candle_fix[0];}
		if(key == 'w'){candle_fix[1] = !candle_fix[1];}
		if(key == 'e'){candle_fix[2] = !candle_fix[2];}
		if(key == 'r'){candle_fix[3] = !candle_fix[3];}
		if(key == 't'){candle_fix[4] = !candle_fix[4];}
		if(key == 'y'){candle_fix[5] = !candle_fix[5];}
		if(key == 'u'){candle_fix[6] = !candle_fix[6];}
		if(key == 'i'){candle_fix[7] = !candle_fix[7];}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	for(int i=0;i<4;i++){
		if(pointSelected[i]){
			point[i] = ofPoint(x,y);
		}
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	for(int i=0;i<4;i++){
		if(((x-point[i].x)*(x-point[i].x)+(y-point[i].y)*(y-point[i].y))<400){
			pointSelected[i]=true;
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	for(int i=0;i<4;i++){
		pointSelected[i]=false;
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
