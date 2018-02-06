# invoke SourceDir generated makefile for rom.prm3
rom.prm3: .libraries,rom.prm3
.libraries,rom.prm3: package/cfg/rom_prm3.xdl
	$(MAKE) -f E:\igs_svn_data\PROJECT_01\02_FW\01_WSM\06_I2C_GMS_US\i2c_light_sensor\projects\iar_tirtos/src/makefile.libs

clean::
	$(MAKE) -f E:\igs_svn_data\PROJECT_01\02_FW\01_WSM\06_I2C_GMS_US\i2c_light_sensor\projects\iar_tirtos/src/makefile.libs clean

