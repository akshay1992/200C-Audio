#include "ofApp.h"

int xRes = 400;
int yRes = 400;

// #define USING_4CHANNELS

//--------------------------------------------------------------
void ofApp::setup(){
  phase = 0;

#ifdef USING_4CHANNELS
  ofSoundStreamSetup(4, 0); // 4 output channels, 0 input channels
#else
  ofSoundStreamSetup(2, 0); // 2 output channels, 0 input channels
#endif

}

//--------------------------------------------------------------
void ofApp::update(){

	int xPos, yPos;

	// *** MOUSE MUTEX ***
	mouseMutex.lock();
	xPos = mouseX;
	yPos = mouseY;
	mouseMutex.unlock();
	// *** MOUSE MUTEX ***
		
	if(xPos > xRes)
		xPos = xRes-1;
	else if(xPos < 0)
		xPos = 0;
	
	if(xPos > xRes)
		yPos = xRes-1;
	else if(xPos < 0)
		yPos = 0;
	
    // *** GAIN MUTEX START ***
	gainMutex.lock();
	gainFR = (float)xPos/xRes;
	gainFL = 1-(float)xPos/xRes;
#ifdef USING_4CHANNELS
	gainRR = (float)xPos/xRes;
	gainRL = 1-(float)xPos/xRes;
#endif
	gainMutex.unlock();
	// *** GAIN MUTEX END ***
}
//--------------------------------------------------------------
void ofApp::draw(){
	ofCircle(xRes/2, yRes/2, xRes/8);
}
//--------------------------------------------------------------
void ofApp::audioOut( float * output, int bufferSize, int nChannels ) {

  static float gFL , gFR;
#ifdef USING_4CHANNELS
  static float gRL, gRR;
#endif	

  // *** GAIN MUTEX START ***
  gainMutex.lock();
  gFL = gainFL;
  gFR = gainFR;
  gainMutex.unlock();
  // *** GAIN MUTEX END ***

  //cout << "                " << gFL << " " << gFR << endl;

  for(int i = 0; i < bufferSize * nChannels; i += 2) {
    float sample = sin(phase); // generating a sine wave sample
    output[i] = gFL*sample; 
    output[i+1] = gFR*sample; 
#ifdef USING_4CHANNELS    
    output[i+2] = gRL*sample;
	output[i+3] = gRR*sample;  
#endif
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

	// *** MOUSE MUTEX START ***
	mouseMutex.lock();
	mouseX = x;
	mouseY = y;
	mouseMutex.unlock();
	// ** MOUSE MUTEX END ***

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
