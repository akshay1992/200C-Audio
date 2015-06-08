#include "ofApp.h"

int xRes = 400;
int yRes = 400;


//--------------------------------------------------------------
void ofApp::setup(){
  phase = 0;
  ofSoundStreamSetup(4, 0); // 2 output channels (stereo), 0 input channels
}

//--------------------------------------------------------------
void ofApp::update(){

	int xPos, yPos;
	mouseMutex.lock();
	xPos = mouseX;
	yPos = mouseY;
	mouseMutex.unlock();
		
	if(xPos > xRes)
		xPos = xRes-1;
	else if(xPos < 0)
		xPos = 0;
	
	if(xPos > xRes)
		yPos = xRes-1;
	else if(xPos < 0)
		yPos = 0;
	
	gainMutex.lock();
	gainFR = (float)xPos/xRes;
	gainFL = 1-(float)xPos/xRes;
	gainRR = (float)xPos/xRes;
	gainRL = 1-(float)xPos/xRes;
	gainMutex.unlock();
}
//--------------------------------------------------------------
void ofApp::draw(){
	ofCircle(xRes/2, yRes/2, xRes/8);
}
//--------------------------------------------------------------
void ofApp::audioOut( float * output, int bufferSize, int nChannels ) {

  static float gFL , gFR, gRL, gRR;
	

  gainMutex.lock();
  gFL = gainFL;
  gFR = gainFR;
  gainMutex.unlock();

  //cout << "                " << gFL << " " << gFR << endl;

  for(int i = 0; i < bufferSize * nChannels; i += 2) {
    float sample = sin(phase); // generating a sine wave sample
    output[i] = gFL*sample; // writing to the left channel
    output[i+1] = gFR*sample; // writing to the right channel
    output[i+2] = gRL*sample;
	output[i+3] = gRR*sample;  
	phase += 0.01;
  }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch(key)
	{
		case 'q': 
		std::exit(0);
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	mouseX = x;
	mouseY = y;

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
