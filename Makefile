
vibey.lv2/vibey.so:
	mv vibey.lv2 vibey.lv2-orig
	faust2lv2 -keep -uri-prefix https://github.com/steveb vibey.dsp
	mv vibey.lv2 vibey.lv2-faust
	mv vibey.lv2-orig vibey.lv2
	cp vibey.lv2-faust/vibey.so vibey.lv2/vibey.so

clean:
	rm vibey.lv2/vibey.so