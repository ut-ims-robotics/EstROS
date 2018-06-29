# EKI kõnesüntesaatori intalleerimise juhend ROSile 
## English instructions below 

Antud juhend on loodud EKI kõnesüntesaatori kasutamiseks ROS operatsiooni süsteemil, kasutades Tartu Ülikooli Robootika projekti raames loodud ROSi [soundplay](https://github.com/ros-drivers/audio_common/tree/master/sound_play) wrapper-it. Wrapper on loodud töötama [ROS Kinetic Kame](http://wiki.ros.org/kinetic) versioonil.


Juhend kasutamiseks:

1. Klooni EstROSi kaust https://github.com/ut-ims-robotics/EstROS oma 
catkin lähtekoodi kausta.

```bash
cd catkin_ws/src
git clone https://github.com/ut-ims-robotics/est_voice_synth.git
```

2. Muuda .wav failide loomise asukohta oma failisüsteemis, tuleb anda **absoluutne** failitee. Selleks muuda src kaustas olevas estonian_text2speech.cpp failis parameetreid: 

```c++
size_t seconds = ess->convertTextToWave (text, "/abs_path_to_gen_wav/est_synth.wav");
sc->playWaveFromPkg("sound_play", "/abs_path_to_gen_wav/est_synth.wav");
```

3. Klooni [synthts_et-master]((https://github.com/ut-ims-robotics/synthts_et)) kaust Githubist kusagile oma arvutisse.

```bash
cd ~
git clone https://github.com/ut-ims-robotics/synthts_et-master.git
```

4. Kopeeri kloonitud synthts_et-master koodihoidlast kaust nimega dct oma catkin tööruumi peakausta (catkin_ws)

5. Installeeri [Audio common](http://wiki.ros.org/audio_common) ROS pakett.

```bash
sudo apt-get install ros-<distro>-audio-common
```

6. Mine oma catkin tööruumi peakausta ja käivita catkin_make käsk: 

```bash
cd catkin_ws
catkin_make
```

7. Programmi saab testida jooksutades käsku `roslaunch`. Kui see ei tööta proovi sõlmi individuaalset käivitada kasutades `rosrun` käsku.

```bash
source devel/setup.bash
roslaunch est_voice_synth est_voice_synth.launch 
```

8. (VALIKULINE) Kui soovid jooksutada pikemaid `.wav` faile kui 10 sekundit, siis tuleks `soundplay_node.py` faili muuta, et kõrvaldada üks [levinud probleem](https://github.com/ros-drivers/audio_common/issues/96)
 `soundplay_node.py` failis. See peaks asuma asukohas `/opt/ros/kinetic/lib/sound_play/soundplay_node.py` Kuid selle leidmiseks võib ka kasutada käsku `sudo find / -name soundplay_node.py`

```python
def get_staleness(self):
.....
position = self.sound.query_position(Gst.Format.TIME)[1] # Muuda siin 0 üheks nagu näidatud
duration = self.sound.query_duration(Gst.Format.TIME)[1] # Muuda siin 0 üheks nagu näidatud 
......
```
__

# EKI (Institute of the Estonian Language) speech synthesizer installation guide for ROS


This installation guide is created for the use of EKI speech synthesizer on the ROS operation system using the ROS soundplay wrapper created within the Robotics Engineering Project course in University of Tartu. Wrapper is designed to work on the ROS Kinetic Kame version.


Guide:
* Copy the EstROS package from https://github.com/ut-ims-robotics/EstROS to your catkin workspace src folder
* Change the path of the generated .wav files in your_catkin_workspace/src/est_voice_synthts/src/listener.cpp by changing the function parameters in lines 39 and 55
* Clone the synthts_et-master package from https://github.com/ut-ims-robotics/synthts_et into one folder higher than your catkin_workspace
* Copy the dct folder from synthts_et-master /synthts_et into your catkin workspace main folder
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




