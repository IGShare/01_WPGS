# invoke SourceDir generated makefile for rom.prm3
rom.prm3: .libraries,rom.prm3
.libraries,rom.prm3: package/cfg/rom_prm3.xdl
	$(MAKE) -f C:\Users\myeom\DOCUME~1\TEXASI~1\SENSOR~1\examples\i2c_light_sensor\projects\iar_tirtos/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\myeom\DOCUME~1\TEXASI~1\SENSOR~1\examples\i2c_light_sensor\projects\iar_tirtos/src/makefile.libs clean

