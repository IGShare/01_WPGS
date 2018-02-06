# invoke SourceDir generated makefile for rfExamples.pem3
rfExamples.pem3: .libraries,rfExamples.pem3
.libraries,rfExamples.pem3: package/cfg/rfExamples_pem3.xdl
	$(MAKE) -f C:\Users\sj_be\workspace_v7\rfPacketRx_CC1310DK_7XD_TI/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\sj_be\workspace_v7\rfPacketRx_CC1310DK_7XD_TI/src/makefile.libs clean

