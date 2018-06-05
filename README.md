English below 

EKI kõnesüntesaatori intalleerimise juhend ROSile 


Antud juhend on loodud EKI kõnesüntesaatori kasutamiseks ROS operatsiooni süsteemil, kasutades Tartu Ülikooli Roboorika projekti raames loodud ROSi soundplay wrapper-it. Wrapper on loodud töötama ROS Kinetic Kame versioonil.


Juhend wrapper-i kasutamiseks:
* Klooni EstROSi kaust https://github.com/ut-ims-robotics/EstROS oma catkin-i tööruumi.
* Muuda .wav failide loomise asukohta oma tööruumis. Selleks muuda failis your_catkin_workspace/src/est_voice_synthts/src/listener.cpp ridade 39 ja 55 parameetreid. (Pilt!)
* Kopeeri muudetud synthts_et kaust github-ist (https://github.com/ut-ims-robotics/synthts_et) oma synthts_et-master kausta. synthts_et-master kaust asub catkin_workspace kaustat üks tase kõrgemal.
* Kopeeri dct ja hts_voices kaustad synthts_et-master/synthts_et kasutast oma catkin tööruumi peakasuta (main folder).
* Käivita catkin_make käsk oma tööruumil.
* Intalleeri http://wiki.ros.org/audio_common kaust (nagu igat teist programmi, ei pea olema catkin tööruumis) ja testi, kas see töötab.
* Programmi saab testida jooksutades käsku roslaunch est_voice_synth est_voice_synth.launch catkin kaustas. 
* Kui soovid jooksutada pikemaid .wav faile kui 10 sekundit, siis tuleks soundplay_node.py failis muuta 

def get_staleness(self):

.....

position = self.sound.query_position(Gst.Format.TIME)[1] # Muuda 0 -> 1

duration = self.sound.query_duration(Gst.Format.TIME)[1] # Muuda 0 -> 1 

......

(allikas: https://github.com/ros-drivers/audio_common/issues/96)

__

EKI (Institute of the Estonian Language) speech synthesizer installation guide for ROS


This installation guide is created for the use of EKI speech synthesizer on the ROS operation system using the ROS soundplay wrapper created within the Robotics Engineering Project course in University of Tartu. Wrapper is designed to work on the ROS Kinetic Kame version.


Guide:
* Copy the EstROS package from https://github.com/ut-ims-robotics/EstROS to your catkin workspace src folder
* Change the path of the generated .wav files in your_catkin_workspace/src/est_voice_synthts/src/listener.cpp by changing the function parameters in lines 39 and 55
* Get the modified synthts_et package from https://github.com/ut-ims-robotics/synthts_et into a synthts_et-master folder which is located in one folder higher than your catkin_workspace
* Copy the dct and the hts_voices folders from synthts_et-master /synthts_et into your catkin workspace main folder
* Run command catkin_make on your workspace
* Get the http://wiki.ros.org/audio_common package and test that it works
* Test the programme with command roslaunch est_voice_synth est_voice_synth.launch 
* If you want to play .wav files that are longer than 10 seconds, you need to make some modifications inside soundplay_node.py file.

Modifications are following:

def get_staleness(self):

.....

position = self.sound.query_position(Gst.Format.TIME)[1] # HERE change from 0 to 1

duration = self.sound.query_duration(Gst.Format.TIME)[1] # HERE change from 0 to 1 

......

(source: https://github.com/ros-drivers/audio_common/issues/96 ) 




