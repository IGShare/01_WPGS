# invoke SourceDir generated makefile for rom.prm3
rom.prm3: .libraries,rom.prm3
.libraries,rom.prm3: package/cfg/rom_prm3.xdl
	$(MAKE) -f E:\igs_svn_data\PROJECT_01\02_FW\01_WSM\02_US_TXRX_TEST_SC\projects\iar_tirtos/src/makefile.libs

clean::
	$(MAKE) -f E:\igs_svn_data\PROJECT_01\02_FW\01_WSM\02_US_TXRX_TEST_SC\projects\iar_tirtos/src/makefile.libs clean

