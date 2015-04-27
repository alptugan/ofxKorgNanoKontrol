ofxKorgNanoKontrol v1
================
![Korg Nano Kontrol version 1](http://www.mslinn.com/sites/mike/studio/instruments/Korg/nano/nanoKontrol/nanokontrolb.gif)

If your device is version you can give a try <https://github.com/paulreimer/ofxNanoKontrol2> 

There are differeneces between version 1 and version 2 in terms of MIDI control values. I couldn't make it work. So, I rewrite my own addon for version 1 device.

Currently in development mode. public methods are listed in `ofxKorgNanoKontrol.h` file.

For now, 

`int getVal(int _control, int _type = K_TYPE_SLIDER, int _sceneId = K_SCENE_1);` 

method can be used to get values from Korg Nano Kontrol v1 usb midi device.


E.g. 

There 9x4 sliders, 9x4 potentiometers, 18x4 push buttons and 7 addional buttons to mange scenes and control all of the inputs on Korg Nano Kontrol. 

#####So, if you want to get the first *slider* value 
`_control` should be `0` or `K_SLIDER_1` as follows;

`getVal(0)` returns int value from 0 to 127

or

`getVal(K_SLIDER_1)` returns int value from 0 to 127

---------------------------------


#####if you want to get the tenth(Actually it's the first slider of Scene 2) *slider* value

`_control` should be `0`, `_type` should be `K_TYPE_SLIDER` and `_sceneId` should be `K_SCENE_2` as 
follows;

`getVal(0,K_TYPE_SLIDER,K_SCENE_2)` returns int value from 0 to 127
  

or

`getVal(K_SLIDER_1,K_TYPE_SLIDER,K_SCENE_2)` returns int value from 0 to 127

-------------



#####if you want to get the first *potentiometer* value 
`_control` should be `0` and `_type` should be `K_TYPE_POT` as follows;

`getVal(0,K_TYPE_POT)` returns int value from 0 to 127

or

`getVal(K_POT_1,K_TYPE_POT)` returns int value from 0 to 127

---
Dependencies
--------
1. ofxMidi - download the existing tag from <https://github.com/danomatika/ofxMidi/tree/0.8.4>

2. ofxKorgNanoKontrol is developped with of-0.84 and not tested with other releases of openframeworks

3. If you get failed build messages related with MIDI libs, you should add system CoreMIDI framework. Click [here](https://vimeo.com/124147456) to see how to add.

todo
-------------
1. tests on other platforms
2. feedbacks from users
