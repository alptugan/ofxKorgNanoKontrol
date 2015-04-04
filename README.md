ofxKorgNanoKontrol v1
================
![Korg Nano Kontrol version 1](http://www.mslinn.com/sites/mike/studio/instruments/Korg/nano/nanoKontrol/nanokontrolb.gif)
If your device is version you can give a try <https://github.com/paulreimer/ofxNanoKontrol2> 

There are differeneces between version 1 and version 2 in terms of MIDI control values. I couldn't make it work. So, I rewrite my own addon for version 1 device.

Currently in development mode. public methods are listed in `ofxKorgNanoKontrol.h` file.

For now, 

`int getVal(int _control, int _type = SLIDER, int _sceneId = 1);` 

method can be used to get values from Korg Nano Kontrol v1 usb midi device.


E.g. 

There 9x4 sliders, 9x4 potentiometers, 18x4 push buttons and 7 addional buttons to mange scenes and control all of the inputs on Korg Nano Kontrol. 

So, if you want to get the first **slider** value 
`_control` should be `0` as follows;

`getVal(0)` returns int

if you want to get the tenth **slider** value 
`_control` should be `9` as follows;

`getVal(9)` returns int

if you want to get the first **potentiometer** value 
`_control` should be `0` and `_type` should be `POT` as follows;

`getVal(0,POT)` returns int

Dependencies
--------
ofxMidi - download the existing tag from <https://github.com/danomatika/ofxMidi/tree/0.8.4>

ofxKorgNanoKontrol is developped with of-0.84 and not tested with other releases of openframeworks

todo
-------------
1. Example files
2. basic gui
3. tests on other platforms
4. feedbacks from users
