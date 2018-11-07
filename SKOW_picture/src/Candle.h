#pragma once
#define NUM 10

#include "ofMain.h"

class Candle
{
public:
	Candle(void);
	~Candle(void);
	
	float xpos, ypos, size;
	int frame;
	ofVec2f offset;
	float localScale;

	void setpos(float tempXpos, float tempYpos);
	void update(ofVec2f pos,float scale);
	void display();
    void display_fire();
	void out();
	void fix();

	ofImage candleImg[NUM];
};

