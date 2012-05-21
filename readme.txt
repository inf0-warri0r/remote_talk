walkie-talkie application for linux
=======================================

this application can be used to have voice conversations with each other using Local area network(LAN).

compiling source :
---------------------
you need gtk and alsa to compile both "talk" and "listen" . install them by running,

sudo apt-get install libasound-dev
sudo apt-get install libgtk2.0-dev

on terminal. then simply type make. then copy the two binaries, "listen" and "talk" into one folder.

using the app :
---------------------

copy "talk" and "listen" binaries in to a folder in every computer. then run "talk" in every computer in the network. and click "open receiver" in all of them. then "listen" app will be open. if any one is talking, you you will hear it through that app. if you want to talk to some one enter the "ip address" of that computer you want to talk to in the text field of "talk" app and click "play". now you can talk. if you want to talk to every one use the "broadcast address" as the ip ( ex: if your ip is "10.0.2.15" and subnet mask is "255.255.255.0" broadcast address is "10.0.2.255" . you can get this by using "ifconfig" command also. see google for more info on broadcast address) and click play. 

more inf0:
------------------

	http://www.inf0warri0r.blogspot.com
	tcg.galahena@gmail.com 
