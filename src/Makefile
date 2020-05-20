plugins := vibey.lv2 vintage_mics.lv2 gods_cab.lv2 splits.lv2

URI_PREFIX = https://github.com/steveb/gula-plugins

FAUSTARCH = lv2.cpp
FAUSTLIB_SEARCH = /usr/share/faust/$(FAUSTARCH) /usr/local/share/faust/$(FAUSTARCH)
FAUSTLIB = $(shell dirname `ls -f $(FAUSTLIB_SEARCH) 2>/dev/null | tail -1`)
FAUSTINC = $(subst share,include,$(FAUSTLIB))
FAUSTTOOLSFLAGS = -DURI_PREFIX=\"$(URI_PREFIX)\" -DFAUST_META=1 -DFAUST_MIDICC=0 -DFAUST_MTS=0

# check CPU and supported optimization flags
ifneq ($(shell cat /proc/cpuinfo | grep sse3 ) , )
	SSE_CFLAGS = -msse3 -mfpmath=sse
else ifneq ($(shell cat /proc/cpuinfo | grep sse2 ) , )
	SSE_CFLAGS = -msse2 -mfpmath=sse
else ifneq ($(shell cat /proc/cpuinfo | grep sse ) , )
	SSE_CFLAGS = -msse -mfpmath=sse
	else ifneq ($(shell cat /proc/cpuinfo | grep ARM ) , )
	ifneq ($(shell cat /proc/cpuinfo | grep ARMv7 ) , )
		ifneq ($(shell cat /proc/cpuinfo | grep vfpd32 ) , )
			SSE_CFLAGS = -march=armv7-a -mfpu=vfpv3
		else ifneq ($(shell cat /proc/cpuinfo | grep vfpv3 ) , )
			SSE_CFLAGS = -march=armv7-a -mfpu=vfpv3
		endif
	else
		ARMCPU = "YES"
	endif
else
	SSE_CFLAGS =
endif

CXXFLAGS += -fPIC -DPIC -std=c++11 -ffast-math -ftree-vectorize -fstack-protector \
	-funroll-loops -fomit-frame-pointer -fstrength-reduce -fdata-sections \
	-Wl,--gc-sections -Wl,-z,relro,-z,now $(SSE_CFLAGS)
LDFLAGS += -shared -lm -Wl,-z,noexecstack

cppsrc := $(plugins:.lv2=.cpp)
buildlibs := $(plugins:.lv2=.so)

all: $(buildlibs)

.PRECIOUS: $(cppsrc)

%.so: %.cpp
	$(CXX) $(FAUSTTOOLSFLAGS) $(PROCARCH) $(CXXFLAGS) $(LDFLAGS) $^ -o $@
	cp $@ ../lv2/$*.lv2/

%.cpp: %.dsp
ifneq ($(FAUSTLIB),)
	faust -i --timeout 3600 -a "$(FAUSTLIB)/$(FAUSTARCH)" -cn $* $< -o $@
else
	# Faust installation not found, using pre-generated $@
endif

clean:
	rm -f $(cppsrc) $(buildlibs)
