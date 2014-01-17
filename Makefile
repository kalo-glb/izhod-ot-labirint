ARDUINOLIBS = /home/kalo/sketchbook/libraries

getLibs:
	rm -r ./libs;
	cp -R $(ARDUINOLIBS) ./libs

commit: getLibs
	git commit -m $(MESSAGE)
    
push:
	git push -u origin master
    
setLibs:
	rm -r $(ARDUINOLIBS)
	cp ./libs $(ARDUINOLIBS)

