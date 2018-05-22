#include "ros/ros.h"
#include "std_msgs/String.h"
#include <cstdlib>
#include <fstream>
#include <sound_play/sound_play.h>
#include <chrono>
#include "estsynth.h"


sound_play::SoundClient* sc = 0; //eemaldada tärn ja väärtustaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamine. Sevice´í või action´ipõhine,
using namespace std;
using namespace std::chrono;

EstonianSpeechSynthesis* ess = 0;
                                                 
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{ 
  ROS_INFO("I heard: [%s]", msg->data.c_str());
  // Start the timer for measuring the time elapsed for creating the text file
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  // Create the text file
  //std::ofstream f("/home/jan/synthts_et-master/synthts_et/in.txt");
  //f << msg->data.c_str();
  //f.close();
  // Stop the timer
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  // Calculate the duration of the function and output the result
  auto duration = duration_cast<microseconds>( t2 - t1 ).count();
  ROS_INFO("Time elapsed for text file creation: [%li]", duration);

  // Start the timer for measuring the time elapsed for the system call performing the synthesis
  t1 = high_resolution_clock::now();
  // Invoke the system call creating the .wav file from the text file
  char* text = new char[msg->data.length()];
  strcpy (text, msg->data.c_str());
  size_t seconds = ess->convertTextToWave (text, "/home/kasutaja/synthts_et-master/synthts_et/out_tnu.wav");
  delete[] text;

  ROS_INFO("Generated sound duration: [%li]", seconds);

  // Stop the timer
  t2 = high_resolution_clock::now();
  // Calculate the duration of the function and output the result
  duration = duration_cast<microseconds>( t2 - t1 ).count();
  ROS_INFO("Time elapsed for synthesis: [%li]", duration);
  
  // Start the timer for measuring the time elapsed for playing the .wav file
  t1 = high_resolution_clock::now();
  //sc.playWaveFromPkg("sound_play", "sounds/BACKINGUP.ogg");
  //sc->stopAll();
  
  sc->playWaveFromPkg("sound_play", "/home/kasutaja/synthts_et-master/synthts_et/out_tnu.wav");
  sleep(seconds + 1);
  sc->stopAll();
  //sc->stopWaveFromPkg("sound_play", "/home/jan/synthts_et-master/synthts_et/out_tnu.wav");
  // Stop the timer
  t2 = high_resolution_clock::now();
  // Calculate the duration of the function and output the result
  duration = duration_cast<microseconds>( t2 - t1 ).count();
  ROS_INFO("Time elapsed for playback: [%li]", duration);
  ROS_INFO("--------------------");
}

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "listener");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;
  	
  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
  ros::Subscriber sub = n.subscribe("chatter", 1, chatterCallback);
  
  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */

   sc = new sound_play::SoundClient ();
   
   ess = new EstonianSpeechSynthesis();
   ess->initialize();
   
   
  ros::spin();
  ess->destroy();
  delete ess;
  delete sc;
   
  return 0;
}
