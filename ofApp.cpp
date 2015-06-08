#include "ofApp.h"
#include <assert.h>

int xRes = 400;
int yRes = 400;

#define USING_4CHANNELS

//--------------------------------------------------------------
void ofApp::setup(){

  speakers.radius = xRes/32.0; // Radius of the speaker setup in pixels
  speakers.quadSetup();	// Setup quadraphonic system

  phase = 0;
#ifdef USING_4CHANNELS
  ofSoundStreamSetup(4, 0); // 4 output channels, 0 input channels
#else
  ofSoundStreamSetup(2, 0); // 2 output channels, 0 input channels
#endif

}

float compute_gain(ofVec2f &object, ofVec2f &speaker)
{
	float angle = abs(object.angle(speaker));
	float angleRad = abs(object.angleRad(speaker));

	int active;
	if (angle>90) 
		active = 0;
	else 
		active = 1;
	
	// Linear trend
	return active*abs( 1.0 - ( angle / 90 ) );

	// Tangent
	// float tmp = 0.5*( 1 + tan(angleRad - M_PI/4) ) ;
	// cout << "                                                " << tmp << endl;
	// float gain;
	// if(angle > 45) 
	// 	gain = tmp;
	// else 
	// 	gain = 1-tmp;
	// return active*gain;

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
	
	xPos = xPos - xRes*0.5;
	yPos = - yPos + yRes*0.5;

	ofVec2f d(xPos, yPos);

    // *** GAIN MUTEX START ***

    // USING VECTORS (Doesn't work)
// 	gainMutex.lock();
// 	gainFR = 1.0 / ( d.length() / speakers.radius * cos(abs( d.angle(speakers.position[0]))) );
// 	gainFL = 1.0 / ( d.length() / speakers.radius * cos(abs( d.angle(speakers.position[1]))) );
// #ifdef USING_4CHANNELS
// 	gainRL = 1.0 / ( d.length() / speakers.radius * cos(abs( d.angle(speakers.position[2]))) );
// 	gainRR = 1.0 / ( d.length() / speakers.radius * cos(abs( d.angle(speakers.position[3]))) );
// #endif
// 	gainMutex.unlock();

	gainMutex.lock();
	gainFR = compute_gain(d, speakers.position[0]);
	gainFL = compute_gain(d, speakers.position[1]);
#ifdef USING_4CHANNELS
	gainRL = compute_gain(d, speakers.position[2]);
	gainRR = compute_gain(d, speakers.position[3]);
#endif
	gainMutex.unlock();

	// *** GAIN MUTEX END ***

	// cout << gainFR << " " << 
	// 		gainFL << " " <<
	// 		gainRL << " " <<
	// 		gainRR << " " << endl;
}
//--------------------------------------------------------------
void ofApp::draw(){
	ofCircle(xRes/2, yRes/2, speakers.radius);
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
