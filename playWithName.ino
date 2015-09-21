/*
 * playWithName.ino
 * Example sketch for MusicShield 2.0
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jack Shao (jacky.shaoxg@gmail.com)
 * Create Time: Mar 2014
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include <SD.h>
#include <SPI.h>
#include <arduino.h>
#include <MusicPlayer.h>

int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;
int val = 0;                    // variable for reading the pin status


void setup(void)
{
  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);
  player.begin();                      //will initialize the hardware and set default mode to be normal.
  player.setPlayMode(PM_NORMAL_PLAY); //set mode to repeat playing a song
  //player.addToPlaylist("1.mp3");
  //player.addToPlaylist("2.mp3");
  //player.addToPlaylist("3.mp3");
  //player.addToPlaylist("3.wav");

  randomSeed(analogRead(0));
}
void loop(void)
{
val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH

    if (pirState == LOW) {
      // we have just turned on
      long randNumber = random(1,4);
      Serial.print("Rand Number: ");
      Serial.println(randNumber);
      String fileName;
      fileName = getFilename(randNumber);
      char array[6];
      fileName.toCharArray(array, 6);
      player.playOne(array);
      player.play();  //do some leisurely job
      Serial.println("Motion detected!");
      Serial.println("Currently playing: "+ fileName);
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {

    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
  
}

String getFilename(long sampleNumber){
  Serial.print("In getfilname, current samplenumber: ");
  Serial.println( sampleNumber);
  switch(sampleNumber){
case 1:    
      return("3.wav");
      break;
    case 2:    
      return("1.mp3");
      break;
    case 3:    
      return("2.mp3");
      break;
    case 4:    
      return("3.mp3");
      break;
    case 5:    
      return("5.wav");
      break;
    default:
    return("No choice");
    }
}
/*
char fileNameToChar(String filename){
//char charName;
//char charBuf[filename.length()+1];
//filename.toCharArray(charName,10);
//return charName;
char array[9];
return filename.toCharArray(array, 9);

}
*/
