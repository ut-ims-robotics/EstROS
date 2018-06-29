# EKI kõnesüntesaatori intalleerimise juhend ROSile 
## English instructions below 

Antud juhend on loodud EKI kõnesüntesaatori kasutamiseks ROSis, kasutades Tartu Ülikooli Robootika projekti raames loodud ROSi wrapperit ja [soundplay](https://github.com/ros-drivers/audio_common/tree/master/sound_play) paketti. Wrapper on loodud töötama [ROS Kinetic Kame](http://wiki.ros.org/kinetic) versioonil.


Juhend kasutamiseks:

1. Klooni EstROSi kaust https://github.com/ut-ims-robotics/EstROS oma 
catkin lähtekoodi kausta.

```bash
cd catkin_ws/src
git clone https://github.com/ut-ims-robotics/est_voice_synth.git
```

2. Muuda .wav failide loomise asukohta oma failisüsteemis, tuleb anda **absoluutne** failitee. Selleks muuda src kaustas olevas `estonian_text2speech.cpp` failis parameetreid: 

```c++
size_t seconds = ess->convertTextToWave (text, "/abs_path_to_gen_wav/est_synth.wav");
sc->playWaveFromPkg("sound_play", "/abs_path_to_gen_wav/est_synth.wav");
```

3. Klooni [synthts_et-master](https://github.com/ut-ims-robotics/synthts_et) koodihoidla Githubist kusagile oma arvutisse.

```bash
cd ~
git clone https://github.com/ut-ims-robotics/synthts_et-master.git
```

4. Kopeeri kloonitud [synthts_et-master](https://github.com/ut-ims-robotics/synthts_et-master) koodihoidlast kaust nimega dct oma catkin tööruumi peakausta (catkin_ws)

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

8. (VALIKULINE) Kui soovid jooksutada pikemaid `.wav` faile kui 10 sekundit, siis tuleks kõrvaldada üks [levinud probleem](https://github.com/ros-drivers/audio_common/issues/96)
 `soundplay_node.py` failis. See peaks asuma asukohas `/opt/ros/kinetic/lib/sound_play/soundplay_node.py` Kuid selle leidmiseks võib ka kasutada käsku `sudo find / -name soundplay_node.py`

```python
def get_staleness(self):
.....
position = self.sound.query_position(Gst.Format.TIME)[1] # Muuda siin 0 üheks nagu näidatud
duration = self.sound.query_duration(Gst.Format.TIME)[1] # Muuda siin 0 üheks nagu näidatud 
......
```

------------

# Institute of the Estonian Language (EKI) speech synthesizer installation guide for ROS

This installation guide is meant to help you use the EKI speech synthesizer on the ROS operation system using the [soundplay](https://github.com/ros-drivers/audio_common/tree/master/sound_play) package. It was created during the course called Robotics Engineering Project in University of Tartu. The current wrapper is designed to work on [ROS Kinetic Kame](http://wiki.ros.org/kinetic).


Installation guide:

1. Clone the EstROS folder https://github.com/ut-ims-robotics/EstROS into your catkins_ws src folder. 

```bash
cd catkin_ws/src
git clone https://github.com/ut-ims-robotics/est_voice_synth.git
```

2. Change the location for the generated .wav files according to your file system, you need to give the **absolute** path. You need to change some parameters in the `estonian_text2speech.cpp` file in located your src folder: 

```c++
size_t seconds = ess->convertTextToWave (text, "/abs_path_to_gen_wav/est_synth.wav");
sc->playWaveFromPkg("sound_play", "/abs_path_to_gen_wav/est_synth.wav");
```

3. Clone [synthts_et-master](https://github.com/ut-ims-robotics/synthts_et) repository from Githubist to somewhere in your computer.

```bash
cd ~
git clone https://github.com/ut-ims-robotics/synthts_et-master.git
```

4. Copy a folder called `dct` from the cloned synthts_et-master repository into your workspace's main folder (catkin_ws)

5. Install the [Audio common](http://wiki.ros.org/audio_common) ROS package.

```bash
sudo apt-get install ros-<distro>-audio-common
```

6. Got to your catkin_ws folder and execute the catkin_make command: 

```bash
cd catkin_ws
catkin_make
```

7. You can test the program using the `roslaunch` command. If that doesn't you can try running each node individually using the `rosrun` command.

```bash
source devel/setup.bash
roslaunch est_voice_synth est_voice_synth.launch 
```

8. (OPTIONAL) If you wish to play `.wav` that are longer than 10 seconds then you need fix a [common bug](https://github.com/ros-drivers/audio_common/issues/96) within the `soundplay_node.py` file. The node should be located in at `/opt/ros/kinetic/lib/sound_play/soundplay_node.py` However you can also use the following command to find it `sudo find / -name soundplay_node.py`

```python
def get_staleness(self):
.....
position = self.sound.query_position(Gst.Format.TIME)[1] # Chnage this from 0 to 1
duration = self.sound.query_duration(Gst.Format.TIME)[1] # Chnage this from 0 to 1 
......
```
