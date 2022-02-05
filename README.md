# Cours de bioautomatique

# Cours de Bioautomatique

## Table des acronymes

SBC : Single Board Computer ( ordinateur mon-carte)
OS : Operating System (système d'exploitation)
MQTT : Message Queue Telemetry

## Serveur et logiciels

### Matériel

Single Board Computer
Carte SD
USB to serial adapter 
Alimentation 5V 2A (micro USB ou type C)
Ecran, cable HDMI, clavier, souris

###  Linux sur un SBC
#### C'est quoi un Single Board Computer ?

[Vidéo de référence](https://youtu.be/Jz3qIB62Gg4)

#### Installation de Linux

[Vidéo de référence](https://youtu.be/AMS-hH0KoLg)

Téléchargement de l'OS
- [Raspberry Pi](https://www.raspberrypi.com/software/operating-systems/)
- [Autres SBC](https://www.armbian.com/download/)

Préparation de la carte SD
 - [RaspberryPi imager ](https://www.raspberrypi.com/software/)
 - [Balena Etcher](https://www.balena.io/etcher/)

#### Setup

[Vidéo de référence](https://youtu.be/mAkHGxhrVCg)

### Node-RED

#### Installation

    $ sudo apt update && sudo apt upgrade -y
    $ sudo apt install curl -y
    $ curl -sL https://deb.nodesource.com/setup_16.x | sudo -E bash -
	$ sudo apt-get install -y nodejs
	$ sudo npm install -g --unsafe-perm node-red

#### Lancement automatique au démarrage

    $ sudo apt install nano -y
    $ sudo nano /etc/systemd/system/node-red.service

    [Unit]
	Description=Node-RED
	After=syslog.target network.target

	[Service]
	ExecStart=/usr/bin/node-red --max-old-space-size=128 -v 
	Restart=on-failure
	KillSignal=SIGINT

	#log output to syslog as 'node-red'
	SyslogIdentifier=node-red
	StandardOutput=syslog

	WorkingDirectory=/home/USERNAME/
	User=USERNAME
	Group=root

	[Install]
	WantedBy=multi-user.target

	$ sudo systemctl start node-red
	$ sudo systemctl status node-red
	$ sudo systemctl enable node-red

### Mosquitto (MQTT)

    $ sudo apt install mosquitto -y
    $ nano /etc/mosquitto/mosquitto.conf

    #Ajouter à la fin du texte
    allow_anonymous true  
	bind_address 0.0.0.0

### Base de données 

Installation de InlfuxDB

	$ sudo apt install influxdb -y
	$ sudo apt install influxdb-client
	$ sudo nano /etc/influxdb/influxdb.conf
	# Décommenter dans [http] :
	enabled = true
	bind-adress = ":8086"

Setup de influx DB

    $ influx
	CREATE USER "user" WITH PASSWORD 'password' WITH ALL PRIVILEGES
	show users
	
	CREATE DATABASE NOMDB
	show databases
	 
### Présentation des données 

Installation de grafana 

	$ wget -q -O - https://packages.grafana.com/gpg.key | sudo apt-key add -
	$ sudo add-apt-repository "deb https://packages.grafana.com/oss/deb stable main"
	$ sudo apt update
	$ sudo apt install grafana -y 
	$ sudo systemctl start grafana-server

Setup de grafana

	 >Config > Data source (ou Add data source menu d'origine)
	 Name : NOM de la BD
	 > Cocher Basic Auth
	> Remplir Basic Auth Details
	> Remplir InfluxDB Details avec NOM de la BD et user login
	Save and TEST

### Arduino et ESP
[Vidéo de référence](https://youtu.be/0mg_jzgKpUI)

[Arduino IDE](https://www.arduino.cc/en/software)

Support ESP32 
https://dl.espressif.com/dl/package_esp32_index.json
    
Support ESP8266
http://arduino.esp8266.com/stable/package_esp8266com_index.json

#### Comment installer et utiliser une bibliothèque

#### Tasmota
[Vidéo de référence](https://youtu.be/2RA9PNGm2Dg)

[Installateur de tasmota](https://tasmota.github.io/install/)


## Capteurs et actionneurs

### Hardware

### Software

### Communication

## Automatisation

### Communication

### Traitement des données

### Workflow (cheminement de l'information)

## Conception 

### Impression 3D

### Modélisation 3D 

### Création et Hack  (Think out of the box ! Sky is the limit)

## Bonnes pratiques

### Où se fournir 

### Où chercher des infos (RTFM)

### Do and Don't 

## A propos de l'auteur

### Réseaux sociaux
 [Youtube](https://www.youtube.com/c/NeodymeTV)
 [Publications](https://scholar.google.com/citations?user=kaca3hsAAAAJ&hl=en)
 [Portfolio]()
 
