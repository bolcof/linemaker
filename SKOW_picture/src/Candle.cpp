#include "Candle.h"


Candle::Candle(void)
{
}


Candle::~Candle(void)
{
}

//ロウソクを作った時の設定をする関数
void Candle::setpos(float tempXpos, float tempYpos){
	
	//入力された２つの値をもとにxpos,yposを作る。
	xpos = tempXpos;
	ypos = tempYpos;

	//始まりが何フレーム目か。ランダム。
    frame = ofRandom(10);
    //火のサイズ。この書き方をすることでどの解像度でも対応できるようにしている。
	size = 22*ofGetWidth()/1920;

	//火の画像ダウンロード
	for(int i=0;i<NUM;i++){
        char char1[32];
        sprintf(char1, "candle%d.png", i+1);
		candleImg[i].loadImage(char1);
	}
}

//ロウソクのアップデート。フレームごとに呼び出される。
void Candle::update(ofVec2f pos,float scale){
	//どれだけ平行にずれるかとスケールの再定義
	offset = pos;
	localScale = scale;
	//火のフレームの更新。10まで行ったら0に戻る
	frame++;
	if(frame==10){frame=0;}
}

void Candle::display(){
	//火の背景のよくわからない色の長方形の描画
	ofFill();
	ofSetColor(6,25,32);
	ofRect(offset.x+(xpos*localScale*ofGetWidth()/1920),offset.y+(ypos*localScale*ofGetWidth()*9/16/1080),size/2*localScale,size*localScale);
}

void Candle::display_fire(){
	//火の描画
    ofSetColor(255);
    candleImg[frame].draw(offset.x+(xpos*localScale*ofGetWidth()/1920),offset.y+(ypos*localScale*ofGetWidth()*9/16/1080),size/2*localScale,size*localScale);
}

//火が消えた時に描画
void Candle::out(){
	//火の背景のよくわからない色の長方形の描画
	ofFill();
	//ofSetColor(10,42,53);
	ofSetColor(0,0,0);
	ofRect(offset.x+(xpos*localScale*ofGetWidth()/1920),offset.y+(ypos*localScale*ofGetWidth()*9/16/1080),size/2*localScale,size*localScale);
  }

//fix
void Candle::fix(){
	frame--;
}