..\PATCHMEM /M - VMM32.VXD VCACHE.VXD
..\PATCHMEM /M - VMM32.VXD VCACHE.VXD
splitcab win98_54.cab x
mkdir x1
cd x1
extractw /e ..\x0001.cab
xfile c12c - .. .
cabarc -m LZX:21 N ..\x0001a.cab *.*
cd ..
mergecab WIN98_54.CAB x0000.cab x0001a.cab x0002.cab
xfile d1 - x*
del patchcab.zip
pkzip -a PATCHCAB.ZIP WIN98_54.CAB README.TXT
