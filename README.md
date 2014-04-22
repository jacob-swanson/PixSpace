# PixSpace

Pilot a large, and often comedic ship throughout the strange solar system of PixSpace!
Visit gas giants, so large you can see them from huge distances away, but so low in mass 
you’d be flung off their surface if you beamed down! Orbit a strange ocean dominated planet
which orbits no sun. Hit tiny rogue asteroids as you attempt to escape orbit. Above all, 
zoom out so far that your ship becomes a single pixel - and all the while, zoom past other 
players, some of whom may be ducks, pigs, or even kittens in cups.


## Database Creation
In order to run the PixSpace Server, you will first need to setup a MySQL database. If you want to run the scripts yourself, the creation script is "db_scripts/mysql_db_create.sql", and the deletion script is "db_scripts/mysql_db_delete.sql". The creation script will create a "pixspace" database and a "pixspace" user with a password of "pixspace". The deletion script will delete the "pixspace" database and user.

The database creation script can be executed with the following command.
```
mysql -u root -p -h DB_HOSTNAME < db_scripts/mysql_db_create.sql
```

## Building PixSpace
PixSpace Client and PixSpace Server can be built via the command line using the following commands.

```
cd pixspace/
mkdir build/
cd build/
qmake ../trunk/
make
```

This will also build the static library, and the unit tests.

If you are not running the MySQL server locally on the default port, an error 
message will appear reporting that the simulation will not work unless the 
configuration is updated. To remedy this, switch to the "Server Configuration" 
tab, update the MySQL configuration to refect your setup, then restart 
PixSpace Server.

To execute PixSpace Server run
```
./Server/pixspaceserver
```

To execute PixSpace Client run
```
./Client/pixspaceclient
```

## Client Controls
- W - Increase Throttle
- S - Decrease Throttle
- A - Rotate Left
- D - Rotate Right
- C - Center on Ship
- Mouse Wheel Scroll Up - Zoom In
- Mouse Wheel Scroll Down - Zoom Out
- Mouse Drag - Move View
