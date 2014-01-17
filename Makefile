LIBS = /home/kalo/sketchbook/libraries

getLibs:
	rm -r ./libs;
	cp -R $(LIBS) ./libs

comit: getLibs
	git comit -m $MESSAGE
    
setLibs:
	rm -r /home/kalo/sketchbook/libraries
	cp ./libs /home/kalo/sketchbook/libraries

