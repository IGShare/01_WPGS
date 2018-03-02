# invoke SourceDir generated makefile for release.pem3
release.pem3: .libraries,release.pem3
.libraries,release.pem3: package/cfg/release_pem3.xdl
	$(MAKE) -f D:\GIT\01_WPGS\02_FW\01_WSM\12_esayLinkTest_01\tirtos_builds_CC1310_LAUNCHXL_release_ccs/src/makefile.libs

clean::
	$(MAKE) -f D:\GIT\01_WPGS\02_FW\01_WSM\12_esayLinkTest_01\tirtos_builds_CC1310_LAUNCHXL_release_ccs/src/makefile.libs clean

