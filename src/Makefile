URI_PREFIX = https://github.com/steveb/gula-plugins

FAUSTARCH = lv2.cpp
FAUSTLIB_SEARCH = /usr/share/faust/$(FAUSTARCH) /usr/local/share/faust/$(FAUSTARCH)
FAUSTLIB = $(shell dirname `ls -f $(FAUSTLIB_SEARCH) 2>/dev/null | tail -1`)
FAUSTINC = $(subst share,include,$(FAUSTLIB))
FAUSTTOOLSFLAGS =

PROCARCH = -fPIC
CXXFLAGS = -std=c++11 -ffast-math -ftree-vectorize
CXX = g++
CPPFLAGS = -DURI_PREFIX=\"$(URI_PREFIX)\" -DFAUST_META=1 -DFAUST_MIDICC=0 -DFAUST_MTS=0

plugins := vibey.lv2 vintage_mics.lv2
cppsrc := $(plugins:.lv2=.cpp)
buildlibs := $(plugins:.lv2=.so)

all: $(buildlibs)

.PRECIOUS: $(cppsrc)

%.so: %.cpp
	$(CXX) -shared $(CXXFLAGS) $(FAUSTTOOLSFLAGS) $(PROCARCH) $(CPPFLAGS) $^ -o $@
	cp $@ ../lv2/$*.lv2/

%.cpp: %.dsp
	faust -i --timeout 3600 -a "$(FAUSTLIB)/$(FAUSTARCH)" -cn $* $< -o $@

clean:
	rm -f $(cppsrc) $(buildlibs)
