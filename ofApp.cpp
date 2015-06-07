#include "ofApp.h"

int xRes = 400;
int yRes = 400;


//--------------------------------------------------------------
void ofApp::setup(){
  phase = 0;
  ofSoundStreamSetup(2, 0); // 2 output channels (stereo), 0 input channels
}

//--------------------------------------------------------------
void ofApp::update(){
	static ofVec2f center(xRes/2.0, yRes/2.0);
	static ofVec2f sourcePos;
	mouseMutex.lock();
	sourcePos = ofVec2f(mouseX, mouseY);
	mouseMutex.unlock();

	float diff = 1- ((center-sourcePos).length() / (float) xRes );

	gainMutex.lock();
	gainR = gainL = diff;
	gainMutex.unlock();
}
//--------------------------------------------------------------
void ofApp::draw(){
	ofCircle(xRes/2, yRes/2, xRes/8);
}
//--------------------------------------------------------------
void ofApp::audioOut( float * output, int bufferSize, int nChannels ) {

  static float gL , gR;

  gainMutex.lock();
  gL = gainL;
  gR = gainR;
  gainMutex.unlock();

  // cout << "                " << gL << " " << gR << endl;

  for(int i = 0; i < bufferSize * nChannels; i += 2) {
    float sample = sin(phase); // generating a sine wave sample
    output[i] = gL*sample; // writing to the left channel
    output[i+1] = gR*sample; // writing to the right channel
    phase += 0.05;
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
