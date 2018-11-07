#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//初期設定
	//offset:端からどれくらい絵がずれているか。２次元ベクトル
	//allScale:画面のサイズ
	offset = ofVec2f(0,0);
	al = 255;
	fl = 0;
	allScale = 1;

	//myCandleはロウソクのインスタンス。setposで位置を指定している。
	myCandle[0].setpos(568,495);
	myCandle[1].setpos(584,496);
	myCandle[2].setpos(598,478);
	myCandle[3].setpos(619,494);
	myCandle[4].setpos(1173,494);
	myCandle[5].setpos(1195,472);
	myCandle[6].setpos(1210,493);
	myCandle[7].setpos(1220,493);

	/*　candle_f:trueだったらその引数と同じロウソクを消す
		candle_fix:trueだったらその引数と同じCandleのfixを呼び出す
		candle_all:candle_fを一括でON/OFFする。
		fukaseなど:メンバーの透明度を管理するbool
		一旦すべてfalseに初期化しておく			*/
	for(int i=0;i<8;i++){
		candle_f[i]=false;
		candle_fix[i]=false;
	}
	candle_all=false;
	fukase=saori=love=nakajin=false;

	//それぞれの画像の読み込み
	back.loadImage("vippicture_base4.png");
	trim.loadImage("trim.jpg");
	fukaseImg.loadImage("new_fukase.png");
	saoriImg.loadImage("new_saori.png");
	LOVEImg.loadImage("new_LOVE.png");
	nakajinImg.loadImage("new_nakajin.png");
	light.loadImage("LIGHT_highq.png");

	//フレームレート。とりあえず24
	ofSetFrameRate(24);

	//sec:今の秒数
	//presec:１フレーム前の秒数
	//この二つの数が変わった時を取得し、秒数が更新された瞬間を取得する
	presec=sec=0;

	//idleがtrueの間は絵画全体が静止する。キー入力も効かない。
	idle=false;

	//calibModeがtrueならidleが自動で変化しない。ずっとキャリブレーションできる。本番時にはfalseに戻してください。
	calibMode=false;

	PinMode=true;

	//ポイントの定義
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

	//カーソルの表示について
	if(PinMode){
		ofShowCursor();
	}else{
		ofHideCursor();
	}

	//自動でロウソクと人を消すための状態遷移。おそらくここをいじることはないのでスルー。
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

	//idleがtrueならばCandleクラスのupdateを実行する。
	if(!idle){
		for(int i=0;i<8;i++){
			myCandle[i].update(offset,allScale);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	//背景を描画
	ofBackground(0);
	ofSetColor(180);
	back.draw(offset.x,offset.y,ofGetWidth()*allScale,ofGetWidth()*allScale*9/16);

	//ロウソクの描画
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

	//メンバーの描画
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
  
	//上のライトの描画
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

	//キー入力。idleがfalseの間だけ受け付ける。
	if(!idle){

		//矢印キーで平行入力
		if(key == OF_KEY_UP){
			offset.y -= 0.5;
		}else if(key == OF_KEY_DOWN){
			offset.y += 0.5;
		}else if(key == OF_KEY_RIGHT){
			offset.x += 0.5;
		}else if(key == OF_KEY_LEFT){
			offset.x -= 0.5;
		}
  
		//平行移動以外のキャリブレーション。
		//flとalは何に使ってるか俺はよくわからないけどprocessing時の物を残してあります。
		if(key == '0'){fl = 255;}
		if(key == 'b'){fl = 0;}
		if(key == 'k'){allScale += 0.003;}
		if(key == 'm'){allScale -= 0.002;}
		if(key == 'z'){al = 255;}
		if(key == 'x'){al = 0;}

		if(key == 'p'){PinMode=!PinMode;}

		//CONTROLEで、今の画像のX座標(offset.x)、Y座標(offset.y)、allScaleを「calibration.txt」に保存。
		/*if(key == OF_KEY_CONTROL){
			char calibrationNum[32];
			sprintf(calibrationNum, "%f\n%f\n%f", offset.x,offset.y,allScale);
			ofBuffer buffer = ofBuffer(calibrationNum);
			ofBufferToFile("calibration.txt",buffer);
		}*/

		//メンバーの描画のON/OFF
		if(key == 'f'){if(fukase==1){fukase=0;}else{fukase=1;}}
		if(key == 's'){if(saori==1){saori=0;}else{saori=1;}}
		if(key == 'l'){if(love==1){love=0;}else{love=1;}}
		if(key == 'n'){if(nakajin==1){nakajin=0;}else{nakajin=1;}}

		//ロウソクのON/OFF
		if(key == 'a'){candle_all = !candle_all;}
		if(key == '1'){candle_f[0] = !candle_f[0];}
		if(key == '2'){candle_f[1] = !candle_f[1];} 
		if(key == '3'){candle_f[2] = !candle_f[2];} 
		if(key == '4'){candle_f[3] = !candle_f[3];} 
		if(key == '5'){candle_f[4] = !candle_f[4];}
		if(key == '6'){candle_f[5] = !candle_f[5];}
		if(key == '7'){candle_f[6] = !candle_f[6];} 
		if(key == '8'){candle_f[7] = !candle_f[7];}
		
		//ロウソクのfix
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
