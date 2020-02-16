/* ------------------------------------------------------------
name: "vintage_mics"
Code generated with Faust 2.21.1 (https://faust.grame.fr)
Compilation options: -lang cpp -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __vintage_mics_H__
#define  __vintage_mics_H__

/************************************************************************
 ************************************************************************
    FAUST Architecture File
    Copyright (C) 2009-2016 Albert Graef <aggraef@gmail.com>
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation; either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with the GNU C Library; if not, write to the Free
    Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA.
 ************************************************************************
 ************************************************************************/

/* LV2 architecture for Faust synths. */

/* NOTE: This requires one of the Boost headers (boost/circular_buffer.hpp),
   so to compile Faust programs created with this architecture you need to
   have at least the Boost headers installed somewhere on your include path
   (the Boost libraries aren't needed). */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <list>
#include <map>
#include <set>

// generic Faust dsp and UI classes
/************************** BEGIN dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;
struct Meta;

/**
 * DSP memory manager.
 */

struct dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    virtual void* allocate(size_t size) = 0;
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'addBtton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceInit(int sample_rate) = 0;

        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (delay lines...) */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = nullptr):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class.
 */

class dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        virtual std::string getName() = 0;
        virtual std::string getSHAKey() = 0;
        virtual std::string getDSPCode() = 0;
        virtual std::string getCompileOptions() = 0;
        virtual std::vector<std::string> getLibraryList() = 0;
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        virtual dsp* createDSPInstance() = 0;
    
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif
/**************************  END  dsp.h **************************/
/************************** BEGIN UI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __UI_H__
#define __UI_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
class UIReal
{
    
    public:
        
        UIReal() {}
        virtual ~UIReal() {}
        
        // -- widget's layouts
        
        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;
        
        // -- active widgets
        
        virtual void addButton(const char* label, REAL* zone) = 0;
        virtual void addCheckButton(const char* label, REAL* zone) = 0;
        virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
        virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
        virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
        
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
        virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
        
        // -- soundfiles
        
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
        
        // -- metadata declarations
        
        virtual void declare(REAL* zone, const char* key, const char* val) {}
};

class UI : public UIReal<FAUSTFLOAT>
{

    public:

        UI() {}
        virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/

using namespace std;

typedef pair<const char*,const char*> strpair;

struct Meta : std::map<const char*, const char*>
{
  void declare(const char *key, const char *value)
  {
    (*this)[key] = value;
  }
  const char* get(const char *key, const char *def)
  {
    if (this->find(key) != this->end())
      return (*this)[key];
    else
      return def;
  }
};

/******************************************************************************
*******************************************************************************

		       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/


/***************************************************************************
   LV2 UI interface
 ***************************************************************************/

enum ui_elem_type_t {
  UI_BUTTON, UI_CHECK_BUTTON,
  UI_V_SLIDER, UI_H_SLIDER, UI_NUM_ENTRY,
  UI_V_BARGRAPH, UI_H_BARGRAPH,
  UI_END_GROUP, UI_V_GROUP, UI_H_GROUP, UI_T_GROUP
};

struct ui_elem_t {
  ui_elem_type_t type;
  const char *label;
  int port;
  float *zone;
  void *ref;
  float init, min, max, step;
};

class LV2UI : public UI
{
public:
  bool is_instr;
  int nelems, nports;
  ui_elem_t *elems;
  map< int, list<strpair> > metadata;

  LV2UI(int maxvoices = 0);
  virtual ~LV2UI();

protected:
  void add_elem(ui_elem_type_t type, const char *label = NULL);
  void add_elem(ui_elem_type_t type, const char *label, float *zone);
  void add_elem(ui_elem_type_t type, const char *label, float *zone,
		float init, float min, float max, float step);
  void add_elem(ui_elem_type_t type, const char *label, float *zone,
		float min, float max);

  bool have_freq, have_gain, have_gate;
  bool is_voice_ctrl(const char *label);

public:
  virtual void addButton(const char* label, float* zone);
  virtual void addCheckButton(const char* label, float* zone);
  virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);
  virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);
  virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);

  virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max);
  virtual void addVerticalBargraph(const char* label, float* zone, float min, float max);
    
  virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}

  virtual void openTabBox(const char* label);
  virtual void openHorizontalBox(const char* label);
  virtual void openVerticalBox(const char* label);
  virtual void closeBox();

  virtual void run();

  virtual void declare(float* zone, const char* key, const char* value);
};

LV2UI::LV2UI(int maxvoices)
{
  is_instr = maxvoices>0;
  have_freq = have_gain = have_gate = false;
  nelems = nports = 0;
  elems = NULL;
}

LV2UI::~LV2UI()
{
  if (elems) free(elems);
}

void LV2UI::declare(float* zone, const char* key, const char* value)
{
  map< int, list<strpair> >::iterator it = metadata.find(nelems);
  if (it != metadata.end())
    it->second.push_back(strpair(key, value));
  else
    metadata[nelems] = list<strpair>(1, strpair(key, value));
}

inline void LV2UI::add_elem(ui_elem_type_t type, const char *label)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].port = -1;
  elems[nelems].zone = NULL;
  elems[nelems].ref = NULL;
  elems[nelems].init = 0.0;
  elems[nelems].min = 0.0;
  elems[nelems].max = 0.0;
  elems[nelems].step = 0.0;
  nelems++;
}

#define portno(label) (is_voice_ctrl(label)?-1:nports++)

inline void LV2UI::add_elem(ui_elem_type_t type, const char *label, float *zone)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].port = portno(label);
  elems[nelems].zone = zone;
  elems[nelems].ref = NULL;
  elems[nelems].init = 0.0;
  elems[nelems].min = 0.0;
  elems[nelems].max = 0.0;
  elems[nelems].step = 0.0;
  nelems++;
}

inline void LV2UI::add_elem(ui_elem_type_t type, const char *label, float *zone,
			     float init, float min, float max, float step)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].port = portno(label);
  elems[nelems].zone = zone;
  elems[nelems].ref = NULL;
  elems[nelems].init = init;
  elems[nelems].min = min;
  elems[nelems].max = max;
  elems[nelems].step = step;
  nelems++;
}

inline void LV2UI::add_elem(ui_elem_type_t type, const char *label, float *zone,
			     float min, float max)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  elems[nelems].type = type;
  elems[nelems].label = label;
  elems[nelems].port = portno(label);
  elems[nelems].zone = zone;
  elems[nelems].ref = NULL;
  elems[nelems].init = 0.0;
  elems[nelems].min = min;
  elems[nelems].max = max;
  elems[nelems].step = 0.0;
  nelems++;
}

inline bool LV2UI::is_voice_ctrl(const char *label)
{
  if (!is_instr)
    return false;
  else if (!have_freq && !strcmp(label, "freq"))
    return (have_freq = true);
  else if (!have_gain && !strcmp(label, "gain"))
    return (have_gain = true);
  else if (!have_gate && !strcmp(label, "gate"))
    return (have_gate = true);
  else
    return false;
}

void LV2UI::addButton(const char* label, float* zone)
{ add_elem(UI_BUTTON, label, zone); }
void LV2UI::addCheckButton(const char* label, float* zone)
{ add_elem(UI_CHECK_BUTTON, label, zone); }
void LV2UI::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_V_SLIDER, label, zone, init, min, max, step); }
void LV2UI::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_H_SLIDER, label, zone, init, min, max, step); }
void LV2UI::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_NUM_ENTRY, label, zone, init, min, max, step); }

void LV2UI::addHorizontalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_H_BARGRAPH, label, zone, min, max); }
void LV2UI::addVerticalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_V_BARGRAPH, label, zone, min, max); }

void LV2UI::openTabBox(const char* label)
{ add_elem(UI_T_GROUP, label); }
void LV2UI::openHorizontalBox(const char* label)
{ add_elem(UI_H_GROUP, label); }
void LV2UI::openVerticalBox(const char* label)
{ add_elem(UI_V_GROUP, label); }
void LV2UI::closeBox()
{ add_elem(UI_END_GROUP); }

void LV2UI::run() {}

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>


#ifndef FAUSTCLASS 
#define FAUSTCLASS vintage_mics
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class vintage_mics : public dsp {
	
 private:
	
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fHslider0;
	float fRec0[2];
	int IOTA;
	float fVec0[512];
	int fSampleRate;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("filename", "vintage_mics.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("name", "vintage_mics");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
		}
		IOTA = 0;
		for (int l1 = 0; (l1 < 512); l1 = (l1 + 1)) {
			fVec0[l1] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual vintage_mics* clone() {
		return new vintage_mics();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("vintage_mics");
		ui_interface->declare(&fHslider0, "name", "Gain");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("gain", &fHslider0, 0.0f, -40.0f, 40.0f, 0.100000001f);
		ui_interface->declare(&fEntry0, "name", "Impulse Response");
		ui_interface->declare(&fEntry0, "style", "menu{'AKGD12':0;'AKG FaultyD12':1;'Altec 639':2;'Altec 670A':3;'Altec 670B':4;'American R331':5;'Amperite RA':6;'Astatic77':7;'BBCmarconi B':8;'BeO BM2':9;'BeO BM6':10;'Beomic 1000':11;'Beyer M260':12;'Beyer M360':13;'BeyerM500Stock':14;'Coles 4038':15;'Doremi 351':16;'EMI ribbon':17;'EV RE20 Flat':18;'EV RE20 HPF':19;'FilmIndustries M8':20;'FosterDynamicDF1':21;'Framez':22;'GaumontKalee':23;'GEC 2373 Ribbon':24;'GEC bigdynamic':25;'Grampian GR2':26;'Lomo52A5M':27;'Meazzi':28;'Melodium 42B 1':29;'Melodium Model12':30;'MelodiumRM6':31;'OktavaMK18 Overload':32;'OktavaMK18Silver':33;'OktavaML16':34;'Oktava ML19':35;'RCA 44BX 1':36;'RCA 44BX 2':37;'RCA 74B':38;'RCA 77DX 1':39;'RCA 77DX 2':40;'RCA KU3a 1':41;'RCAKU3a':42;'RCA PB90':43;'RCA varacoustic fig8':44;'ResloCR600':45;'ResloDynamic':46;'Reslo RB250':47;'Reslo RB RedLabel':48;'Reslo RV':49;'Reslo SR1':50;'ResloURA':51;'Reslo VMC2':52;'Shure315 flat':53;'Shure315 HPF':54;'Shure510C':55;'Sony C37Fet':56;'STC4033 Cardioid':57;'STC4033 Pressure':58;'STC4033 Ribbon':59;'Telefunken M201':60;'Toshiba TypeG':61;'Toshiba TypeH BK5':62;'Toshiba TypeK flat':63;'Toshiba TypeK HPF':64}");
		ui_interface->addNumEntry("ir", &fEntry0, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		int iSlow0 = (float(fEntry0) >= 1.0f);
		float fSlow1 = (0.00100000005f * std::pow(10.0f, (0.0500000007f * float(fHslider0))));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow1 + (0.999000013f * fRec0[1]));
			float fTemp0 = (float(input0[i]) * fRec0[0]);
			fVec0[(IOTA & 511)] = fTemp0;
			float fTemp1 = fVec0[((IOTA - 511) & 511)];
			float fTemp2 = fVec0[((IOTA - 428) & 511)];
			float fTemp3 = fVec0[((IOTA - 384) & 511)];
			float fTemp4 = fVec0[((IOTA - 231) & 511)];
			float fTemp5 = fVec0[((IOTA - 293) & 511)];
			float fTemp6 = fVec0[((IOTA - 336) & 511)];
			float fTemp7 = fVec0[((IOTA - 476) & 511)];
			float fTemp8 = fVec0[((IOTA - 474) & 511)];
			float fTemp9 = fVec0[((IOTA - 253) & 511)];
			float fTemp10 = fVec0[((IOTA - 351) & 511)];
			float fTemp11 = fVec0[((IOTA - 473) & 511)];
			float fTemp12 = fVec0[((IOTA - 302) & 511)];
			float fTemp13 = fVec0[((IOTA - 303) & 511)];
			float fTemp14 = fVec0[((IOTA - 472) & 511)];
			float fTemp15 = fVec0[((IOTA - 249) & 511)];
			float fTemp16 = fVec0[((IOTA - 19) & 511)];
			float fTemp17 = fVec0[((IOTA - 192) & 511)];
			float fTemp18 = fVec0[((IOTA - 471) & 511)];
			float fTemp19 = fVec0[((IOTA - 470) & 511)];
			float fTemp20 = fVec0[((IOTA - 367) & 511)];
			float fTemp21 = fVec0[((IOTA - 441) & 511)];
			float fTemp22 = fVec0[((IOTA - 30) & 511)];
			float fTemp23 = fVec0[((IOTA - 468) & 511)];
			float fTemp24 = fVec0[((IOTA - 467) & 511)];
			float fTemp25 = fVec0[((IOTA - 466) & 511)];
			float fTemp26 = fVec0[((IOTA - 247) & 511)];
			float fTemp27 = fVec0[((IOTA - 359) & 511)];
			float fTemp28 = fVec0[((IOTA - 465) & 511)];
			float fTemp29 = fVec0[((IOTA - 296) & 511)];
			float fTemp30 = fVec0[((IOTA - 333) & 511)];
			float fTemp31 = fVec0[((IOTA - 464) & 511)];
			float fTemp32 = fVec0[((IOTA - 266) & 511)];
			float fTemp33 = fVec0[((IOTA - 435) & 511)];
			float fTemp34 = fVec0[((IOTA - 459) & 511)];
			float fTemp35 = fVec0[((IOTA - 74) & 511)];
			float fTemp36 = fVec0[((IOTA - 215) & 511)];
			float fTemp37 = fVec0[((IOTA - 451) & 511)];
			float fTemp38 = fVec0[((IOTA - 373) & 511)];
			float fTemp39 = fVec0[((IOTA - 214) & 511)];
			float fTemp40 = fVec0[((IOTA - 265) & 511)];
			float fTemp41 = fVec0[((IOTA - 450) & 511)];
			float fTemp42 = fVec0[((IOTA - 274) & 511)];
			float fTemp43 = fVec0[((IOTA - 414) & 511)];
			float fTemp44 = fVec0[((IOTA - 392) & 511)];
			float fTemp45 = fVec0[((IOTA - 449) & 511)];
			float fTemp46 = fVec0[((IOTA - 402) & 511)];
			float fTemp47 = fVec0[((IOTA - 444) & 511)];
			float fTemp48 = fVec0[((IOTA - 442) & 511)];
			float fTemp49 = fVec0[((IOTA - 267) & 511)];
			float fTemp50 = fVec0[((IOTA - 358) & 511)];
			float fTemp51 = fVec0[((IOTA - 440) & 511)];
			float fTemp52 = fVec0[((IOTA - 234) & 511)];
			float fTemp53 = fVec0[((IOTA - 344) & 511)];
			float fTemp54 = fVec0[((IOTA - 439) & 511)];
			float fTemp55 = fVec0[((IOTA - 432) & 511)];
			float fTemp56 = fVec0[((IOTA - 347) & 511)];
			float fTemp57 = fVec0[((IOTA - 304) & 511)];
			float fTemp58 = fVec0[((IOTA - 84) & 511)];
			float fTemp59 = fVec0[((IOTA - 300) & 511)];
			float fTemp60 = fVec0[((IOTA - 437) & 511)];
			float fTemp61 = fVec0[((IOTA - 431) & 511)];
			float fTemp62 = fVec0[((IOTA - 427) & 511)];
			float fTemp63 = fVec0[((IOTA - 377) & 511)];
			float fTemp64 = fVec0[((IOTA - 278) & 511)];
			float fTemp65 = fVec0[((IOTA - 205) & 511)];
			float fTemp66 = fVec0[((IOTA - 233) & 511)];
			float fTemp67 = fVec0[((IOTA - 425) & 511)];
			float fTemp68 = fVec0[((IOTA - 434) & 511)];
			float fTemp69 = fVec0[((IOTA - 420) & 511)];
			float fTemp70 = fVec0[((IOTA - 370) & 511)];
			float fTemp71 = fVec0[((IOTA - 376) & 511)];
			float fTemp72 = fVec0[((IOTA - 419) & 511)];
			float fTemp73 = fVec0[((IOTA - 408) & 511)];
			float fTemp74 = fVec0[((IOTA - 152) & 511)];
			float fTemp75 = fVec0[((IOTA - 361) & 511)];
			float fTemp76 = fVec0[((IOTA - 418) & 511)];
			float fTemp77 = fVec0[((IOTA - 349) & 511)];
			float fTemp78 = fVec0[((IOTA - 237) & 511)];
			float fTemp79 = fVec0[((IOTA - 285) & 511)];
			float fTemp80 = fVec0[((IOTA - 415) & 511)];
			float fTemp81 = fVec0[((IOTA - 346) & 511)];
			float fTemp82 = fVec0[((IOTA - 314) & 511)];
			float fTemp83 = fVec0[((IOTA - 117) & 511)];
			float fTemp84 = fVec0[((IOTA - 230) & 511)];
			float fTemp85 = fVec0[((IOTA - 412) & 511)];
			float fTemp86 = fVec0[((IOTA - 198) & 511)];
			float fTemp87 = fVec0[((IOTA - 290) & 511)];
			float fTemp88 = fVec0[((IOTA - 411) & 511)];
			float fTemp89 = fVec0[((IOTA - 264) & 511)];
			float fTemp90 = fVec0[((IOTA - 254) & 511)];
			float fTemp91 = fVec0[((IOTA - 199) & 511)];
			float fTemp92 = fVec0[((IOTA - 200) & 511)];
			float fTemp93 = fVec0[((IOTA - 410) & 511)];
			float fTemp94 = fVec0[((IOTA - 307) & 511)];
			float fTemp95 = fVec0[((IOTA - 257) & 511)];
			float fTemp96 = fVec0[((IOTA - 244) & 511)];
			float fTemp97 = fVec0[((IOTA - 245) & 511)];
			float fTemp98 = fVec0[((IOTA - 409) & 511)];
			float fTemp99 = fVec0[((IOTA - 368) & 511)];
			float fTemp100 = fVec0[((IOTA - 318) & 511)];
			float fTemp101 = fVec0[((IOTA - 343) & 511)];
			float fTemp102 = fVec0[((IOTA - 405) & 511)];
			float fTemp103 = fVec0[((IOTA - 203) & 511)];
			float fTemp104 = fVec0[((IOTA - 282) & 511)];
			float fTemp105 = fVec0[((IOTA - 329) & 511)];
			float fTemp106 = fVec0[((IOTA - 404) & 511)];
			float fTemp107 = fVec0[((IOTA - 401) & 511)];
			float fTemp108 = fVec0[((IOTA - 175) & 511)];
			float fTemp109 = fVec0[((IOTA - 270) & 511)];
			float fTemp110 = fVec0[((IOTA - 398) & 511)];
			float fTemp111 = fVec0[((IOTA - 310) & 511)];
			float fTemp112 = fVec0[((IOTA - 350) & 511)];
			float fTemp113 = fVec0[((IOTA - 161) & 511)];
			float fTemp114 = fVec0[((IOTA - 397) & 511)];
			float fTemp115 = fVec0[((IOTA - 160) & 511)];
			float fTemp116 = fVec0[((IOTA - 395) & 511)];
			float fTemp117 = fVec0[((IOTA - 433) & 511)];
			float fTemp118 = fVec0[((IOTA - 276) & 511)];
			float fTemp119 = fVec0[((IOTA - 399) & 511)];
			float fTemp120 = fVec0[((IOTA - 369) & 511)];
			float fTemp121 = fVec0[((IOTA - 142) & 511)];
			float fTemp122 = fVec0[((IOTA - 213) & 511)];
			float fTemp123 = fVec0[((IOTA - 364) & 511)];
			float fTemp124 = fVec0[((IOTA - 366) & 511)];
			float fTemp125 = fVec0[((IOTA - 365) & 511)];
			float fTemp126 = fVec0[((IOTA - 294) & 511)];
			float fTemp127 = fVec0[((IOTA - 281) & 511)];
			float fTemp128 = fVec0[((IOTA - 291) & 511)];
			float fTemp129 = fVec0[((IOTA - 360) & 511)];
			float fTemp130 = fVec0[((IOTA - 259) & 511)];
			float fTemp131 = fVec0[((IOTA - 309) & 511)];
			float fTemp132 = fVec0[((IOTA - 357) & 511)];
			float fTemp133 = fVec0[((IOTA - 354) & 511)];
			float fTemp134 = fVec0[((IOTA - 331) & 511)];
			float fTemp135 = fVec0[((IOTA - 58) & 511)];
			float fTemp136 = fVec0[((IOTA - 272) & 511)];
			float fTemp137 = fVec0[((IOTA - 352) & 511)];
			float fTemp138 = fVec0[((IOTA - 239) & 511)];
			float fTemp139 = fVec0[((IOTA - 256) & 511)];
			float fTemp140 = fVec0[((IOTA - 348) & 511)];
			float fTemp141 = fVec0[((IOTA - 115) & 511)];
			float fTemp142 = fVec0[((IOTA - 325) & 511)];
			float fTemp143 = fVec0[((IOTA - 328) & 511)];
			float fTemp144 = fVec0[((IOTA - 335) & 511)];
			float fTemp145 = fVec0[((IOTA - 334) & 511)];
			float fTemp146 = fVec0[((IOTA - 308) & 511)];
			float fTemp147 = fVec0[((IOTA - 311) & 511)];
			float fTemp148 = fVec0[((IOTA - 207) & 511)];
			float fTemp149 = fVec0[((IOTA - 315) & 511)];
			float fTemp150 = fVec0[((IOTA - 106) & 511)];
			float fTemp151 = fVec0[((IOTA - 138) & 511)];
			float fTemp152 = fVec0[((IOTA - 63) & 511)];
			float fTemp153 = fVec0[((IOTA - 97) & 511)];
			float fTemp154 = fVec0[((IOTA - 424) & 511)];
			float fTemp155 = fVec0[((IOTA - 422) & 511)];
			float fTemp156 = fVec0[((IOTA - 421) & 511)];
			float fTemp157 = fVec0[((IOTA - 407) & 511)];
			float fTemp158 = fVec0[((IOTA - 406) & 511)];
			float fTemp159 = fVec0[((IOTA - 396) & 511)];
			float fTemp160 = fVec0[((IOTA - 394) & 511)];
			float fTemp161 = fVec0[((IOTA - 393) & 511)];
			float fTemp162 = fVec0[((IOTA - 381) & 511)];
			float fTemp163 = fVec0[((IOTA - 380) & 511)];
			float fTemp164 = fVec0[((IOTA - 378) & 511)];
			float fTemp165 = fVec0[((IOTA - 372) & 511)];
			float fTemp166 = fVec0[((IOTA - 371) & 511)];
			float fTemp167 = fVec0[((IOTA - 362) & 511)];
			float fTemp168 = fVec0[((IOTA - 321) & 511)];
			float fTemp169 = fVec0[((IOTA - 320) & 511)];
			float fTemp170 = fVec0[((IOTA - 319) & 511)];
			float fTemp171 = fVec0[((IOTA - 167) & 511)];
			float fTemp172 = fVec0[((IOTA - 166) & 511)];
			float fTemp173 = fVec0[((IOTA - 159) & 511)];
			float fTemp174 = fVec0[((IOTA - 158) & 511)];
			float fTemp175 = fVec0[((IOTA - 151) & 511)];
			float fTemp176 = fVec0[((IOTA - 150) & 511)];
			float fTemp177 = fVec0[((IOTA - 118) & 511)];
			float fTemp178 = fVec0[((IOTA - 114) & 511)];
			float fTemp179 = fVec0[((IOTA - 113) & 511)];
			float fTemp180 = fVec0[((IOTA - 112) & 511)];
			float fTemp181 = fVec0[((IOTA - 111) & 511)];
			float fTemp182 = fVec0[((IOTA - 110) & 511)];
			float fTemp183 = fVec0[((IOTA - 109) & 511)];
			float fTemp184 = fVec0[((IOTA - 108) & 511)];
			float fTemp185 = fVec0[((IOTA - 107) & 511)];
			float fTemp186 = fVec0[((IOTA - 105) & 511)];
			float fTemp187 = fVec0[((IOTA - 104) & 511)];
			float fTemp188 = fVec0[((IOTA - 103) & 511)];
			float fTemp189 = fVec0[((IOTA - 102) & 511)];
			float fTemp190 = fVec0[((IOTA - 101) & 511)];
			float fTemp191 = fVec0[((IOTA - 100) & 511)];
			float fTemp192 = fVec0[((IOTA - 99) & 511)];
			float fTemp193 = fVec0[((IOTA - 88) & 511)];
			float fTemp194 = fVec0[((IOTA - 87) & 511)];
			float fTemp195 = fVec0[((IOTA - 86) & 511)];
			float fTemp196 = fVec0[((IOTA - 85) & 511)];
			float fTemp197 = fVec0[((IOTA - 78) & 511)];
			float fTemp198 = fVec0[((IOTA - 77) & 511)];
			float fTemp199 = fVec0[((IOTA - 76) & 511)];
			float fTemp200 = fVec0[((IOTA - 75) & 511)];
			float fTemp201 = fVec0[((IOTA - 62) & 511)];
			float fTemp202 = fVec0[((IOTA - 61) & 511)];
			float fTemp203 = fVec0[((IOTA - 60) & 511)];
			float fTemp204 = fVec0[((IOTA - 59) & 511)];
			float fTemp205 = fVec0[((IOTA - 54) & 511)];
			float fTemp206 = fVec0[((IOTA - 53) & 511)];
			float fTemp207 = fVec0[((IOTA - 52) & 511)];
			float fTemp208 = fVec0[((IOTA - 51) & 511)];
			float fTemp209 = fVec0[((IOTA - 50) & 511)];
			float fTemp210 = fVec0[((IOTA - 49) & 511)];
			float fTemp211 = fVec0[((IOTA - 48) & 511)];
			float fTemp212 = fVec0[((IOTA - 47) & 511)];
			float fTemp213 = fVec0[((IOTA - 46) & 511)];
			float fTemp214 = fVec0[((IOTA - 45) & 511)];
			float fTemp215 = fVec0[((IOTA - 36) & 511)];
			float fTemp216 = fVec0[((IOTA - 35) & 511)];
			float fTemp217 = fVec0[((IOTA - 34) & 511)];
			float fTemp218 = fVec0[((IOTA - 33) & 511)];
			float fTemp219 = fVec0[((IOTA - 32) & 511)];
			float fTemp220 = fVec0[((IOTA - 31) & 511)];
			float fTemp221 = fVec0[((IOTA - 24) & 511)];
			float fTemp222 = fVec0[((IOTA - 23) & 511)];
			float fTemp223 = fVec0[((IOTA - 22) & 511)];
			float fTemp224 = fVec0[((IOTA - 21) & 511)];
			float fTemp225 = fVec0[((IOTA - 5) & 511)];
			float fTemp226 = fVec0[((IOTA - 6) & 511)];
			float fTemp227 = fVec0[((IOTA - 7) & 511)];
			float fTemp228 = fVec0[((IOTA - 8) & 511)];
			float fTemp229 = fVec0[((IOTA - 10) & 511)];
			float fTemp230 = fVec0[((IOTA - 11) & 511)];
			float fTemp231 = fVec0[((IOTA - 12) & 511)];
			float fTemp232 = fVec0[((IOTA - 13) & 511)];
			float fTemp233 = fVec0[((IOTA - 14) & 511)];
			float fTemp234 = fVec0[((IOTA - 15) & 511)];
			float fTemp235 = fVec0[((IOTA - 16) & 511)];
			float fTemp236 = fVec0[((IOTA - 17) & 511)];
			float fTemp237 = fVec0[((IOTA - 20) & 511)];
			float fTemp238 = fVec0[((IOTA - 509) & 511)];
			float fTemp239 = fVec0[((IOTA - 269) & 511)];
			float fTemp240 = fVec0[((IOTA - 508) & 511)];
			float fTemp241 = fVec0[((IOTA - 506) & 511)];
			float fTemp242 = fVec0[((IOTA - 429) & 511)];
			float fTemp243 = fVec0[((IOTA - 353) & 511)];
			float fTemp244 = fVec0[((IOTA - 280) & 511)];
			float fTemp245 = fVec0[((IOTA - 157) & 511)];
			float fTemp246 = fVec0[((IOTA - 232) & 511)];
			float fTemp247 = fVec0[((IOTA - 505) & 511)];
			float fTemp248 = fVec0[((IOTA - 445) & 511)];
			float fTemp249 = fVec0[((IOTA - 457) & 511)];
			float fTemp250 = fVec0[((IOTA - 504) & 511)];
			float fTemp251 = fVec0[((IOTA - 501) & 511)];
			float fTemp252 = fVec0[((IOTA - 462) & 511)];
			float fTemp253 = fVec0[((IOTA - 337) & 511)];
			float fTemp254 = fVec0[((IOTA - 288) & 511)];
			float fTemp255 = fVec0[((IOTA - 305) & 511)];
			float fTemp256 = fVec0[((IOTA - 503) & 511)];
			float fTemp257 = fVec0[((IOTA - 500) & 511)];
			float fTemp258 = fVec0[((IOTA - 461) & 511)];
			float fTemp259 = fVec0[((IOTA - 323) & 511)];
			float fTemp260 = fVec0[((IOTA - 456) & 511)];
			float fTemp261 = fVec0[((IOTA - 502) & 511)];
			float fTemp262 = fVec0[((IOTA - 446) & 511)];
			float fTemp263 = fVec0[((IOTA - 317) & 511)];
			float fTemp264 = fVec0[((IOTA - 387) & 511)];
			float fTemp265 = fVec0[((IOTA - 499) & 511)];
			float fTemp266 = fVec0[((IOTA - 489) & 511)];
			float fTemp267 = fVec0[((IOTA - 413) & 511)];
			float fTemp268 = fVec0[((IOTA - 386) & 511)];
			float fTemp269 = fVec0[((IOTA - 355) & 511)];
			float fTemp270 = fVec0[((IOTA - 287) & 511)];
			float fTemp271 = fVec0[((IOTA - 345) & 511)];
			float fTemp272 = fVec0[((IOTA - 498) & 511)];
			float fTemp273 = fVec0[((IOTA - 492) & 511)];
			float fTemp274 = fVec0[((IOTA - 482) & 511)];
			float fTemp275 = fVec0[((IOTA - 458) & 511)];
			float fTemp276 = fVec0[((IOTA - 448) & 511)];
			float fTemp277 = fVec0[((IOTA - 240) & 511)];
			float fTemp278 = fVec0[((IOTA - 313) & 511)];
			float fTemp279 = fVec0[((IOTA - 497) & 511)];
			float fTemp280 = fVec0[((IOTA - 487) & 511)];
			float fTemp281 = fVec0[((IOTA - 481) & 511)];
			float fTemp282 = fVec0[((IOTA - 455) & 511)];
			float fTemp283 = fVec0[((IOTA - 400) & 511)];
			float fTemp284 = fVec0[((IOTA - 316) & 511)];
			float fTemp285 = fVec0[((IOTA - 255) & 511)];
			float fTemp286 = fVec0[((IOTA - 297) & 511)];
			float fTemp287 = fVec0[((IOTA - 496) & 511)];
			float fTemp288 = fVec0[((IOTA - 485) & 511)];
			float fTemp289 = fVec0[((IOTA - 416) & 511)];
			float fTemp290 = fVec0[((IOTA - 174) & 511)];
			float fTemp291 = fVec0[((IOTA - 322) & 511)];
			float fTemp292 = fVec0[((IOTA - 495) & 511)];
			float fTemp293 = fVec0[((IOTA - 494) & 511)];
			float fTemp294 = fVec0[((IOTA - 338) & 511)];
			float fTemp295 = fVec0[((IOTA - 262) & 511)];
			float fTemp296 = fVec0[((IOTA - 162) & 511)];
			float fTemp297 = fVec0[((IOTA - 241) & 511)];
			float fTemp298 = fVec0[((IOTA - 493) & 511)];
			float fTemp299 = fVec0[((IOTA - 426) & 511)];
			float fTemp300 = fVec0[((IOTA - 480) & 511)];
			float fTemp301 = fVec0[((IOTA - 491) & 511)];
			float fTemp302 = fVec0[((IOTA - 330) & 511)];
			float fTemp303 = fVec0[((IOTA - 436) & 511)];
			float fTemp304 = fVec0[((IOTA - 490) & 511)];
			float fTemp305 = fVec0[((IOTA - 479) & 511)];
			float fTemp306 = fVec0[((IOTA - 453) & 511)];
			float fTemp307 = fVec0[((IOTA - 438) & 511)];
			float fTemp308 = fVec0[((IOTA - 306) & 511)];
			float fTemp309 = fVec0[((IOTA - 301) & 511)];
			float fTemp310 = fVec0[((IOTA - 298) & 511)];
			float fTemp311 = fVec0[((IOTA - 289) & 511)];
			float fTemp312 = fVec0[((IOTA - 292) & 511)];
			float fTemp313 = fVec0[((IOTA - 488) & 511)];
			float fTemp314 = fVec0[((IOTA - 460) & 511)];
			float fTemp315 = fVec0[((IOTA - 447) & 511)];
			float fTemp316 = fVec0[((IOTA - 443) & 511)];
			float fTemp317 = fVec0[((IOTA - 385) & 511)];
			float fTemp318 = fVec0[((IOTA - 403) & 511)];
			float fTemp319 = fVec0[((IOTA - 486) & 511)];
			float fTemp320 = fVec0[((IOTA - 454) & 511)];
			float fTemp321 = fVec0[((IOTA - 324) & 511)];
			float fTemp322 = fVec0[((IOTA - 263) & 511)];
			float fTemp323 = fVec0[((IOTA - 165) & 511)];
			float fTemp324 = fVec0[((IOTA - 206) & 511)];
			float fTemp325 = fVec0[((IOTA - 484) & 511)];
			float fTemp326 = fVec0[((IOTA - 483) & 511)];
			float fTemp327 = fVec0[((IOTA - 477) & 511)];
			float fTemp328 = fVec0[((IOTA - 463) & 511)];
			float fTemp329 = fVec0[((IOTA - 268) & 511)];
			float fTemp330 = fVec0[((IOTA - 271) & 511)];
			float fTemp331 = fVec0[((IOTA - 243) & 511)];
			float fTemp332 = fVec0[((IOTA - 475) & 511)];
			float fTemp333 = fVec0[((IOTA - 191) & 511)];
			float fTemp334 = fVec0[((IOTA - 469) & 511)];
			float fTemp335 = fVec0[((IOTA - 452) & 511)];
			float fTemp336 = fVec0[((IOTA - 356) & 511)];
			float fTemp337 = fVec0[((IOTA - 279) & 511)];
			float fTemp338 = fVec0[((IOTA - 176) & 511)];
			float fTemp339 = fVec0[((IOTA - 430) & 511)];
			float fTemp340 = fVec0[((IOTA - 95) & 511)];
			float fTemp341 = fVec0[((IOTA - 423) & 511)];
			float fTemp342 = fVec0[((IOTA - 299) & 511)];
			float fTemp343 = fVec0[((IOTA - 417) & 511)];
			float fTemp344 = fVec0[((IOTA - 391) & 511)];
			float fTemp345 = fVec0[((IOTA - 286) & 511)];
			float fTemp346 = fVec0[((IOTA - 382) & 511)];
			float fTemp347 = fVec0[((IOTA - 389) & 511)];
			float fTemp348 = fVec0[((IOTA - 327) & 511)];
			float fTemp349 = fVec0[((IOTA - 250) & 511)];
			float fTemp350 = fVec0[((IOTA - 261) & 511)];
			float fTemp351 = fVec0[((IOTA - 388) & 511)];
			float fTemp352 = fVec0[((IOTA - 339) & 511)];
			float fTemp353 = fVec0[((IOTA - 312) & 511)];
			float fTemp354 = fVec0[((IOTA - 204) & 511)];
			float fTemp355 = fVec0[((IOTA - 295) & 511)];
			float fTemp356 = fVec0[((IOTA - 137) & 511)];
			float fTemp357 = fVec0[((IOTA - 379) & 511)];
			float fTemp358 = fVec0[((IOTA - 134) & 511)];
			float fTemp359 = fVec0[((IOTA - 363) & 511)];
			float fTemp360 = fVec0[((IOTA - 342) & 511)];
			float fTemp361 = fVec0[((IOTA - 116) & 511)];
			float fTemp362 = fVec0[((IOTA - 119) & 511)];
			float fTemp363 = fVec0[((IOTA - 209) & 511)];
			float fTemp364 = fVec0[((IOTA - 341) & 511)];
			float fTemp365 = fVec0[((IOTA - 275) & 511)];
			float fTemp366 = fVec0[((IOTA - 332) & 511)];
			float fTemp367 = fVec0[((IOTA - 143) & 511)];
			float fTemp368 = fVec0[((IOTA - 326) & 511)];
			float fTemp369 = fVec0[((IOTA - 277) & 511)];
			float fTemp370 = fVec0[((IOTA - 149) & 511)];
			float fTemp371 = fVec0[((IOTA - 202) & 511)];
			float fTemp372 = fVec0[((IOTA - 258) & 511)];
			float fTemp373 = fVec0[((IOTA - 242) & 511)];
			float fTemp374 = fVec0[((IOTA - 246) & 511)];
			float fTemp375 = fVec0[((IOTA - 177) & 511)];
			float fTemp376 = fVec0[((IOTA - 251) & 511)];
			float fTemp377 = fVec0[((IOTA - 229) & 511)];
			float fTemp378 = fVec0[((IOTA - 248) & 511)];
			float fTemp379 = fVec0[((IOTA - 144) & 511)];
			float fTemp380 = fVec0[((IOTA - 226) & 511)];
			float fTemp381 = fVec0[((IOTA - 156) & 511)];
			float fTemp382 = fVec0[((IOTA - 225) & 511)];
			float fTemp383 = fVec0[((IOTA - 125) & 511)];
			float fTemp384 = fVec0[((IOTA - 220) & 511)];
			float fTemp385 = fVec0[((IOTA - 18) & 511)];
			float fTemp386 = fVec0[((IOTA - 172) & 511)];
			float fTemp387 = fVec0[((IOTA - 124) & 511)];
			float fTemp388 = fVec0[((IOTA - 133) & 511)];
			float fTemp389 = fVec0[((IOTA - 69) & 511)];
			float fTemp390 = fVec0[((IOTA - 72) & 511)];
			float fTemp391 = fVec0[((IOTA - 507) & 511)];
			float fTemp392 = fVec0[((IOTA - 390) & 511)];
			float fTemp393 = fVec0[((IOTA - 375) & 511)];
			float fTemp394 = fVec0[((IOTA - 374) & 511)];
			float fTemp395 = fVec0[((IOTA - 340) & 511)];
			float fTemp396 = fVec0[((IOTA - 284) & 511)];
			float fTemp397 = fVec0[((IOTA - 283) & 511)];
			float fTemp398 = fVec0[((IOTA - 260) & 511)];
			float fTemp399 = fVec0[((IOTA - 252) & 511)];
			float fTemp400 = fVec0[((IOTA - 236) & 511)];
			float fTemp401 = fVec0[((IOTA - 235) & 511)];
			float fTemp402 = fVec0[((IOTA - 228) & 511)];
			float fTemp403 = fVec0[((IOTA - 227) & 511)];
			float fTemp404 = fVec0[((IOTA - 224) & 511)];
			float fTemp405 = fVec0[((IOTA - 223) & 511)];
			float fTemp406 = fVec0[((IOTA - 222) & 511)];
			float fTemp407 = fVec0[((IOTA - 221) & 511)];
			float fTemp408 = fVec0[((IOTA - 219) & 511)];
			float fTemp409 = fVec0[((IOTA - 218) & 511)];
			float fTemp410 = fVec0[((IOTA - 217) & 511)];
			float fTemp411 = fVec0[((IOTA - 212) & 511)];
			float fTemp412 = fVec0[((IOTA - 211) & 511)];
			float fTemp413 = fVec0[((IOTA - 210) & 511)];
			float fTemp414 = fVec0[((IOTA - 197) & 511)];
			float fTemp415 = fVec0[((IOTA - 196) & 511)];
			float fTemp416 = fVec0[((IOTA - 195) & 511)];
			float fTemp417 = fVec0[((IOTA - 194) & 511)];
			float fTemp418 = fVec0[((IOTA - 193) & 511)];
			float fTemp419 = fVec0[((IOTA - 190) & 511)];
			float fTemp420 = fVec0[((IOTA - 189) & 511)];
			float fTemp421 = fVec0[((IOTA - 188) & 511)];
			float fTemp422 = fVec0[((IOTA - 187) & 511)];
			float fTemp423 = fVec0[((IOTA - 186) & 511)];
			float fTemp424 = fVec0[((IOTA - 185) & 511)];
			float fTemp425 = fVec0[((IOTA - 184) & 511)];
			float fTemp426 = fVec0[((IOTA - 183) & 511)];
			float fTemp427 = fVec0[((IOTA - 182) & 511)];
			float fTemp428 = fVec0[((IOTA - 181) & 511)];
			float fTemp429 = fVec0[((IOTA - 180) & 511)];
			float fTemp430 = fVec0[((IOTA - 179) & 511)];
			float fTemp431 = fVec0[((IOTA - 178) & 511)];
			float fTemp432 = fVec0[((IOTA - 173) & 511)];
			float fTemp433 = fVec0[((IOTA - 171) & 511)];
			float fTemp434 = fVec0[((IOTA - 170) & 511)];
			float fTemp435 = fVec0[((IOTA - 169) & 511)];
			float fTemp436 = fVec0[((IOTA - 164) & 511)];
			float fTemp437 = fVec0[((IOTA - 163) & 511)];
			float fTemp438 = fVec0[((IOTA - 155) & 511)];
			float fTemp439 = fVec0[((IOTA - 154) & 511)];
			float fTemp440 = fVec0[((IOTA - 153) & 511)];
			float fTemp441 = fVec0[((IOTA - 148) & 511)];
			float fTemp442 = fVec0[((IOTA - 147) & 511)];
			float fTemp443 = fVec0[((IOTA - 146) & 511)];
			float fTemp444 = fVec0[((IOTA - 145) & 511)];
			float fTemp445 = fVec0[((IOTA - 141) & 511)];
			float fTemp446 = fVec0[((IOTA - 140) & 511)];
			float fTemp447 = fVec0[((IOTA - 139) & 511)];
			float fTemp448 = fVec0[((IOTA - 136) & 511)];
			float fTemp449 = fVec0[((IOTA - 135) & 511)];
			float fTemp450 = fVec0[((IOTA - 132) & 511)];
			float fTemp451 = fVec0[((IOTA - 131) & 511)];
			float fTemp452 = fVec0[((IOTA - 130) & 511)];
			float fTemp453 = fVec0[((IOTA - 129) & 511)];
			float fTemp454 = fVec0[((IOTA - 128) & 511)];
			float fTemp455 = fVec0[((IOTA - 127) & 511)];
			float fTemp456 = fVec0[((IOTA - 126) & 511)];
			float fTemp457 = fVec0[((IOTA - 123) & 511)];
			float fTemp458 = fVec0[((IOTA - 122) & 511)];
			float fTemp459 = fVec0[((IOTA - 121) & 511)];
			float fTemp460 = fVec0[((IOTA - 120) & 511)];
			float fTemp461 = fVec0[((IOTA - 98) & 511)];
			float fTemp462 = fVec0[((IOTA - 96) & 511)];
			float fTemp463 = fVec0[((IOTA - 94) & 511)];
			float fTemp464 = fVec0[((IOTA - 93) & 511)];
			float fTemp465 = fVec0[((IOTA - 92) & 511)];
			float fTemp466 = fVec0[((IOTA - 91) & 511)];
			float fTemp467 = fVec0[((IOTA - 90) & 511)];
			float fTemp468 = fVec0[((IOTA - 89) & 511)];
			float fTemp469 = fVec0[((IOTA - 83) & 511)];
			float fTemp470 = fVec0[((IOTA - 82) & 511)];
			float fTemp471 = fVec0[((IOTA - 81) & 511)];
			float fTemp472 = fVec0[((IOTA - 80) & 511)];
			float fTemp473 = fVec0[((IOTA - 79) & 511)];
			float fTemp474 = fVec0[((IOTA - 73) & 511)];
			float fTemp475 = fVec0[((IOTA - 71) & 511)];
			float fTemp476 = fVec0[((IOTA - 70) & 511)];
			float fTemp477 = fVec0[((IOTA - 68) & 511)];
			float fTemp478 = fVec0[((IOTA - 67) & 511)];
			float fTemp479 = fVec0[((IOTA - 66) & 511)];
			float fTemp480 = fVec0[((IOTA - 65) & 511)];
			float fTemp481 = fVec0[((IOTA - 64) & 511)];
			float fTemp482 = fVec0[((IOTA - 57) & 511)];
			float fTemp483 = fVec0[((IOTA - 56) & 511)];
			float fTemp484 = fVec0[((IOTA - 55) & 511)];
			float fTemp485 = fVec0[((IOTA - 44) & 511)];
			float fTemp486 = fVec0[((IOTA - 43) & 511)];
			float fTemp487 = fVec0[((IOTA - 42) & 511)];
			float fTemp488 = fVec0[((IOTA - 41) & 511)];
			float fTemp489 = fVec0[((IOTA - 40) & 511)];
			float fTemp490 = fVec0[((IOTA - 39) & 511)];
			float fTemp491 = fVec0[((IOTA - 38) & 511)];
			float fTemp492 = fVec0[((IOTA - 37) & 511)];
			float fTemp493 = fVec0[((IOTA - 29) & 511)];
			float fTemp494 = fVec0[((IOTA - 28) & 511)];
			float fTemp495 = fVec0[((IOTA - 27) & 511)];
			float fTemp496 = fVec0[((IOTA - 26) & 511)];
			float fTemp497 = fVec0[((IOTA - 1) & 511)];
			float fTemp498 = fVec0[((IOTA - 2) & 511)];
			float fTemp499 = (1.00003052f * fVec0[((IOTA - 3) & 511)]);
			float fTemp500 = fVec0[((IOTA - 4) & 511)];
			float fTemp501 = fVec0[((IOTA - 9) & 511)];
			float fTemp502 = fVec0[((IOTA - 25) & 511)];
			float fTemp503 = fVec0[((IOTA - 510) & 511)];
			float fTemp504 = fVec0[((IOTA - 273) & 511)];
			float fTemp505 = fVec0[((IOTA - 208) & 511)];
			float fTemp506 = fVec0[((IOTA - 238) & 511)];
			output0[i] = FAUSTFLOAT((iSlow0 ? (((0.000885036774f * (fTemp1 + (fTemp326 + (fTemp150 + fTemp380)))) + ((0.000671407208f * (fTemp503 + (fTemp397 - fTemp317))) + ((0.000152592547f * (fTemp240 - (fTemp25 - (fTemp33 + fTemp303)))) + ((0.000732444227f * (fTemp72 - fTemp241)) + ((0.00146488845f * (fTemp13 - fTemp298)) + ((0.000457777642f * (fTemp38 - fTemp304)) + ((0.000396740623f * (fTemp313 - (fTemp60 - (fTemp330 - fTemp312)))) + ((0.000640888698f * (fTemp280 + (fTemp274 - (fTemp28 - (fTemp254 + fTemp299))))) + ((0.000823999755f * (fTemp136 + fTemp319)) + ((0.000976592302f * (fTemp288 + (fTemp305 + (fTemp18 + (fTemp19 + (fTemp95 + (fTemp96 + (fTemp434 - fTemp148)))))))) + ((0.00103762932f * (fTemp325 + (fTemp311 - (fTemp66 - fTemp378)))) + ((0.000518814661f * (fTemp281 + (fTemp359 + fTemp102))) + ((0.000701925717f * (fTemp300 - (fTemp343 - (fTemp290 + fTemp128)))) + ((0.00125125889f * (fVec0[((IOTA - 478) & 511)] - (fTemp37 - (fTemp366 - (fTemp57 + (fTemp447 - fTemp104)))))) + ((0.00137333293f * (fTemp327 + (fTemp267 - (fTemp107 - (fTemp3 + (fTemp244 - fTemp5)))))) + ((0.00134281442f * (fTemp7 - (fTemp246 + fTemp355))) + ((0.00115970336f * (fTemp332 - (fTemp289 + fTemp335))) + ((0.000854518265f * (fTemp11 + (fTemp334 - (fTemp2 + (fTemp342 + fTemp80))))) + ((0.000946073793f * (fTemp14 - (fTemp54 - (fTemp90 - fTemp167)))) + ((0.000274666585f * (fTemp270 + fTemp24)) + ((0.00167851802f * (fTemp69 - fTemp258)) + ((0.00180059206f * (fTemp154 - fTemp314)) + ((0.00131229591f * (fTemp67 + (fTemp161 + (fTemp127 + fTemp164)))) + ((9.15555283e-05f * (fTemp43 - (fTemp324 + fTemp345))) + ((0.00234992523f * (fTemp157 - (fTemp374 + fTemp286))) + ((0.00329599902f * (fTemp110 + (fTemp160 + (fTemp165 + (fTemp365 - fTemp27))))) + ((0.00494399853f * (fTemp116 - (fTemp259 - fVec0[((IOTA - 383) & 511)]))) + ((0.00207525864f * (fTemp59 - fTemp264)) + ((0.00164799951f * (fTemp123 + (fTemp399 - (fTemp409 + fTemp97)))) + ((0.00302133244f * (fTemp15 - fTemp133)) + ((0.00186162908f * (fTemp348 - fTemp395)) + ((0.00347911008f * (fTemp64 + fTemp105)) + ((0.00390636921f * (fTemp12 - fTemp321)) + ((0.00369273964f * (fTemp398 + fTemp82)) + ((0.00228888821f * (fTemp84 + fTemp337)) + ((0.00399792474f * (fTemp349 + fTemp118)) + ((0.00448622089f * (fTemp331 + fTemp40)) + ((0.00244148076f * (fTemp358 + fTemp130)) + ((0.0012817774f * (fTemp372 - (fTemp403 - fTemp285))) + ((0.000305185094f * (fTemp506 + (fTemp36 + fTemp4))) + ((0.0308847316f * (fTemp225 + fTemp455)) + ((3.05185094e-05f * fTemp266) + ((0.000610370189f * fTemp23) + ((0.00241096225f * fTemp156) + ((0.00292977691f * fTemp93) + ((0.004852443f * fTemp114) + ((0.00546281319f * fTemp159) + ((0.00881984923f * fTemp346) + ((0.0101931822f * fTemp163) + ((0.00659199804f * fTemp357) + ((0.00488296151f * fTemp70) + ((0.00466933195f * fTemp120) + ((0.00405896176f * fTemp20) + ((0.00344859157f * fTemp124) + ((0.00305185094f * fTemp302) + ((0.00320444349f * fTemp143) + ((0.00411999878f * fTemp149) + ((0.00299081393f * fTemp278) + ((0.00204474013f * fTemp239) + ((0.00500503555f * fTemp49) + ((0.00540177617f * fTemp32) + ((0.0025940733f * fTemp322) + ((0.00375377666f * fTemp350) + ((0.00119022187f * fTemp139) + ((0.00662251655f * fTemp297) + ((0.00491348002f * fTemp277) + ((0.00497451704f * fTemp382) + ((0.00366222113f * fTemp405) + ((0.00335703604f * fTemp432) + ((0.00503555406f * fTemp386) + ((0.00357066561f * fTemp433) + ((0.000366222113f * fTemp435) + ((0.0045167394f * fVec0[((IOTA - 168) & 511)]) + ((0.0101016266f * fTemp171) + ((0.0131839961f * fTemp172) + ((0.0132755516f * fTemp436) + ((0.0152592547f * fTemp437) + ((0.0168462172f * fTemp296) + ((0.0157170333f * fTemp113) + ((0.00994903408f * fTemp115) + ((0.011383404f * fTemp438) + ((0.0231330302f * fTemp439) + ((0.029175695f * fTemp440) + ((0.0292367321f * fTemp74) + ((0.0241401419f * fTemp175) + ((0.0160222184f * fTemp176) + ((0.0058290353f * fTemp370) + ((0.00378429517f * fTemp151) + ((0.0153508103f * fTemp356) + ((0.0230414756f * fTemp449) + ((0.00875881221f * fTemp452) + ((0.0173955504f * fTemp453) + ((0.0207831059f * fTemp454) + ((0.0433362834f * fTemp456) + ((0.0458082817f * fTemp383) + ((0.0316171758f * fTemp387) + ((0.01617481f * fTemp457) + ((0.0108645894f * fTemp458) + ((0.0189519953f * fTemp459) + ((0.0271004364f * fTemp460) + ((0.0249641407f * fTemp362) + ((0.0234992523f * fTemp177) + ((0.0252388082f * fTemp83) + ((0.0387890264f * fTemp361) + ((0.0479750969f * fTemp141) + ((0.0493179113f * fTemp178) + ((0.0417188033f * fTemp179) + ((0.0316782147f * fTemp180) + ((0.0304574724f * fTemp181) + ((0.0267036967f * fTemp182) + ((0.0267342143f * fTemp183) + ((0.0122074038f * fTemp184) + ((0.00570696127f * fTemp185) + ((0.00628681295f * fTemp186) + ((0.00897244178f * fTemp187) + ((0.0122379223f * fTemp188) + ((0.0284432508f * fTemp189) + ((0.0445265062f * fTemp190) + ((0.061403241f * fTemp191) + ((0.0559099093f * fTemp192) + ((0.0541093163f * fTemp461) + ((0.0450453199f * fTemp153) + ((0.0387585089f * fTemp462) + ((0.0131534776f * fTemp340) + ((0.0464186519f * fTemp481) + ((0.102847375f * fTemp152) + ((0.142582476f * fTemp201) + ((0.140202031f * fTemp202) + ((0.10177923f * fTemp203) + ((0.0467238389f * fTemp204) + ((0.00759910885f * fTemp492) + ((0.0500808731f * fTemp215) + ((0.113834038f * fTemp216) + ((0.168767363f * fTemp217) + ((0.183477283f * fTemp218) + ((0.16446425f * fTemp219) + ((0.106448561f * fTemp220) + ((0.0570696145f * fTemp22) + ((0.00802636798f * fTemp493) + ((0.0569475405f * fTemp494) + ((0.106326491f * fTemp495) + ((0.29261148f * fTemp496) + ((0.416150391f * fTemp502) + ((0.503128171f * fTemp221) + ((0.395886093f * fTemp222) + ((0.329660952f * fTemp223) + ((0.266762286f * fTemp224) + ((0.233191937f * fTemp237) + ((0.168980986f * fTemp16) + ((0.0689107925f * fTemp385) + ((0.055238504f * fTemp236) + ((0.0321665108f * fTemp234) + ((0.273689985f * fTemp501) + ((0.570207834f * fTemp228) + ((0.58861047f * fTemp226) + (0.697561562f * fTemp227)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))) - (((0.00112918485f * (fTemp247 + (fTemp31 + (fTemp78 - fTemp87)))) + ((0.00143436994f * (fTemp250 + (fTemp47 - (fTemp119 - fTemp242)))) + ((0.00155644398f * (fTemp41 + fTemp256)) + ((0.001617481f * (fTemp261 + (fTemp169 + fTemp252))) + ((0.00158696249f * (fTemp251 + (fTemp257 + (fTemp265 + (fTemp293 + (fTemp126 - fTemp158)))))) + ((0.00170903653f * (fTemp272 + (fTemp364 + fTemp292))) + ((0.00177007355f * (fTemp279 + (fTemp287 - (fTemp504 - fTemp46)))) + ((0.000915555283f * (fTemp301 + (fTemp307 + (fTemp381 + fTemp65)))) + ((0.00100711081f * (fTemp400 - fTemp8)) + ((0.00149540696f * (fTemp306 + fTemp328)) + ((0.00213629566f * (fTemp34 + (fTemp320 + (fTemp248 - (fTemp377 + fTemp341))))) + ((0.00268562883f * (fTemp6 + fTemp282)) + ((0.00198370311f * (fTemp140 + fTemp45)) + ((0.00238044374f * (fTemp276 + (fTemp131 + fTemp271))) + ((0.00271614734f * (fTemp315 + (fTemp253 - fTemp88))) + ((0.000793481246f * (fTemp316 - (fTemp109 - (fTemp410 - fTemp9)))) + ((0.000335703604f * (fTemp48 + (fTemp79 + fTemp68))) + ((0.000183111057f * (fTemp21 + (fTemp62 + (fTemp283 - (fTemp52 - fTemp30))))) + ((0.00173955504f * (fTemp108 + fTemp55)) + ((0.00201422162f * (fTemp81 + fTemp61)) + ((0.00189214759f * (fTemp344 + fTemp339)) + ((0.00250251777f * (fTemp505 - fTemp155)) + ((0.000122074038f * (fTemp76 + (fTemp111 + (fTemp402 + fTemp396)))) + ((0.00222785119f * (fTemp112 - fTemp85)) + ((0.00308236945f * (fTemp255 - fTemp98)) + ((0.0028992584f * (fTemp243 - fTemp73)) + ((0.00152592547f * (fTemp318 + (fTemp268 + (fTemp145 - (fTemp263 + (fTemp147 + (fTemp173 - fTemp29))))))) + ((0.00262459181f * (fTemp392 + (fTemp101 - fTemp125))) + ((0.00256355479f * (fTemp294 + fTemp351)) + ((0.0110171819f * (fTemp414 - fTemp162)) + ((0.00363170262f * (fTemp63 - (fTemp329 - (fTemp411 + (fTemp446 + fTemp412))))) + ((0.00332651753f * (fTemp394 + (fTemp336 + (fTemp103 - fTemp89)))) + ((0.00473036896f * (fTemp94 - fTemp166)) + ((0.00439466536f * (fTemp92 - fTemp99)) + ((0.0022583697f * (fTemp75 - (fTemp134 - (fTemp406 + fTemp142)))) + ((0.00314340647f * (fTemp168 + fTemp129)) + ((0.00317392498f * (fTemp50 - (fTemp284 - (fTemp371 - fTemp376)))) + ((0.003234962f * (fTemp132 + (fTemp269 + (fTemp363 - fTemp295)))) + ((0.00274666585f * (fTemp137 - (fTemp138 - fTemp53))) + ((0.00247199927f * (fTemp10 - (fTemp42 - fTemp310))) + ((0.00219733268f * (fTemp360 + (fTemp122 + fTemp352))) + ((0.00231940672f * (fTemp144 + (fTemp354 - fTemp353))) + ((6.10370189e-05f * (fTemp368 - (fTemp401 + fTemp100))) + ((0.00424207281f * (fTemp408 + fTemp146)) + ((0.0042115543f * (fTemp308 - (fTemp369 + fTemp309))) + ((0.00671407208f * (fTemp407 - fTemp404)) + ((0.00350962859f * (fTemp441 + fTemp413)) + ((0.0130314035f * (fTemp443 - fTemp323)) + ((0.00650044251f * (fTemp431 - fTemp373)) + ((0.0263069551f * (fTemp450 - fTemp448)) + ((0.000244148076f * fTemp391) + ((0.00122074038f * fTemp273) + ((0.00253303628f * fTemp275) + ((0.00280770287f * fTemp249) + ((0.00296029542f * fTemp260) + ((0.00265511032f * fTemp262) + ((0.00054933317f * fTemp51) + ((0.00106814783f * fTemp117) + ((0.00057985168f * fTemp106) + ((0.000488296151f * fTemp44) + ((0.00286873989f * fTemp347) + ((0.006469924f * fTemp71) + ((0.00607318338f * fTemp393) + ((0.00210577715f * fTemp77) + ((0.0019226661f * fTemp56) + ((0.00442518387f * fTemp291) + ((0.000762962736f * fTemp170) + ((0.00109866634f * fTemp26) + ((0.00668355357f * fTemp384) + ((0.00360118411f * fVec0[((IOTA - 201) & 511)]) + ((0.00592059083f * fTemp91) + ((0.00793481246f * fTemp86) + ((0.014496292f * fTemp415) + ((0.0164189581f * fTemp416) + ((0.0162053294f * fTemp417) + ((0.0143131809f * fTemp418) + ((0.0116275521f * fTemp17) + ((0.00982696004f * fTemp333) + ((0.00955229346f * fTemp419) + ((0.0117496261f * fTemp420) + ((0.0142826624f * fTemp421) + ((0.015991699f * fTemp422) + ((0.0154423658f * fTemp423) + ((0.0148930326f * fTemp424) + ((0.0149235511f * fTemp425) + ((0.016113773f * fTemp426) + ((0.0165410321f * fTemp427) + ((0.0150151066f * fTemp428) + ((0.0119632557f * fTemp429) + ((0.00845362712f * fTemp430) + ((0.00506607257f * fTemp375) + ((0.00372325815f * fTemp338) + ((0.00610370189f * fTemp174) + ((0.00772118289f * fTemp245) + ((0.0101626636f * fTemp442) + ((0.0139774773f * fTemp444) + ((0.0135502182f * fTemp379) + ((0.0115970336f * fTemp367) + ((0.00906399731f * fTemp121) + ((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((fTemp499 + (((0.0950956792f * fTemp0) + (0.36185798f * fTemp497)) + (0.798760951f * fTemp498))) + (0.650654614f * fTemp500)) + (0.0879848599f * fTemp229)) + (0.351451159f * fTemp230)) + (0.407086402f * fTemp231)) + (0.214575633f * fTemp232)) + (0.0857264921f * fTemp233)) + (0.00552385021f * fTemp235)) + (0.0183721427f * fTemp491)) + (0.0547807254f * fTemp490)) + (0.0787682757f * fTemp489)) + (0.119907223f * fTemp488)) + (0.134983361f * fTemp487)) + (0.134159371f * fTemp486)) + (0.119632557f * fTemp485)) + (0.104647972f * fTemp214)) + (0.0944242701f * fTemp213)) + (0.0766930133f * fTemp212)) + (0.0743430927f * fTemp211)) + (0.0694601312f * fTemp210)) + (0.0869472325f * fTemp209)) + (0.0716879815f * fTemp208)) + (0.0605792403f * fTemp207)) + (0.0351878405f * fTemp206)) + (0.0493789501f * fTemp205)) + (0.0661030933f * fTemp484)) + (0.0883816034f * fTemp483)) + (0.0658284277f * fTemp482)) + (0.0210272539f * fTemp135)) + (0.0187994018f * fTemp480)) + (0.0495620593f * fTemp479)) + (0.0656453148f * fTemp478)) + (0.0656758323f * fTemp477)) + (0.0741904974f * fTemp389)) + (0.0741599798f * fTemp476)) + (0.0704977587f * fTemp475)) + (0.0773033872f * fTemp390)) + (0.0935392305f * fTemp474)) + (0.105410933f * fTemp35)) + (0.0877101943f * fTemp200)) + (0.0444044322f * fTemp199)) + (0.0120242927f * fTemp198)) + (0.0145878475f * fTemp197)) + (0.0441908017f * fTemp473)) + (0.0679647177f * fTemp472)) + (0.0827661976f * fTemp471)) + (0.0951261967f * fTemp470)) + (0.10724204f * fTemp469)) + (0.106997892f * fTemp58)) + (0.0892056003f * fTemp196)) + (0.0595416129f * fTemp195)) + (0.0352488793f * fTemp194)) + (0.0262459181f * fTemp193)) + (0.0271309558f * fTemp468)) + (0.0505691692f * fTemp467)) + (0.0723899081f * fTemp466)) + (0.086733602f * fTemp465)) + (0.0648213178f * fTemp464)) + (0.0274971779f * fTemp463)) + (0.0111697745f * fTemp451)) + (0.0215765871f * fTemp388)) + (0.00524918362f * fTemp445))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))) + (0.000427259132f * (fTemp39 - fTemp238)))) : (((0.000152592547f * (fTemp1 + (fTemp2 + (fTemp3 + (fTemp4 + fTemp5))))) + ((0.00149540696f * (fTemp6 + fTemp7)) + ((0.00216681417f * (fTemp8 - (fTemp9 - fTemp10))) + ((0.00207525864f * (fTemp11 + (fTemp12 + fTemp13))) + ((0.00189214759f * (fTemp14 - (fTemp15 - (fTemp16 - fTemp17)))) + ((0.00170903653f * (fTemp18 + (fTemp19 + (fTemp20 + fTemp21)))) + ((0.00198370311f * (fTemp22 + fTemp23)) + ((0.00213629566f * (fTemp24 + (fTemp25 - (fTemp26 - fTemp27)))) + ((0.00183111057f * (fTemp28 + (fTemp29 + fTemp30))) + ((0.00125125889f * (fTemp31 - (fTemp32 - fTemp33))) + ((0.000976592302f * (fTemp34 + (fTemp35 + fTemp36))) + ((6.10370189e-05f * (fTemp37 - (fTemp38 + (fTemp39 + fTemp40)))) + ((0.000274666585f * (fTemp41 - (fTemp42 - fTemp43))) + ((0.00057985168f * (fTemp44 + fTemp45)) + ((0.000366222113f * (fTemp46 + fTemp47)) + ((0.00137333293f * (fTemp48 - (fTemp49 - fTemp50))) + ((0.00155644398f * (fTemp51 - (fTemp52 + fTemp53))) + ((0.00109866634f * (fTemp54 + (fTemp55 + (fTemp56 + (fTemp57 + (fTemp58 - fTemp59)))))) + ((0.000427259132f * (fTemp60 + (fTemp61 + (fTemp62 + (fTemp63 - (fTemp64 + (fTemp65 + fTemp66))))))) + ((0.001617481f * (fTemp67 + fTemp68)) + ((0.00326548051f * (fTemp69 + (fTemp70 - fTemp71))) + ((0.00283822138f * (fTemp72 + (fTemp73 + (fTemp74 + fTemp75)))) + ((0.00231940672f * (fTemp76 + (fTemp77 - (fTemp78 + fTemp79)))) + ((0.000335703604f * (fTemp80 + (fTemp81 - (fTemp82 + (fTemp83 + fTemp84))))) + ((0.00100711081f * (fTemp85 - (fTemp86 + fTemp87))) + ((0.00115970336f * (fTemp88 + (fTemp89 - (fTemp90 - (fTemp91 + fTemp92))))) + ((0.00152592547f * (fTemp93 + (fTemp94 - (fTemp95 + (fTemp96 + fTemp97))))) + ((0.00219733268f * (fTemp98 + (fTemp99 + (fTemp100 - fTemp101)))) + ((0.00210577715f * (fTemp102 - (fTemp103 + fTemp104))) + ((0.00143436994f * (fTemp105 + fTemp106)) + ((0.000518814661f * (fTemp107 + (fTemp108 - fTemp109))) + ((0.0025940733f * (fTemp110 + (fTemp111 + fTemp112))) + ((0.00405896176f * (fTemp113 + fTemp114)) + ((0.00610370189f * (fTemp115 + fTemp116)) + ((0.00158696249f * (fTemp117 - (fTemp118 - fTemp119))) + ((0.00271614734f * (fTemp120 - (fTemp121 + fTemp122))) + ((0.0012817774f * (fTemp123 + fTemp124)) + ((0.00106814783f * (fTemp125 + (fTemp126 - (fTemp127 + fTemp128)))) + ((0.00268562883f * (fTemp129 - (fTemp130 - fTemp131))) + ((0.00054933317f * (fTemp132 - (fTemp133 - (fTemp134 + (fTemp135 - fTemp136))))) + ((0.00122074038f * (fTemp137 + (fTemp138 - fTemp139))) + ((0.00173955504f * (fTemp140 - (fTemp141 - fTemp142))) + ((0.00222785119f * (fTemp143 + fTemp144)) + ((0.00234992523f * (fTemp145 + (fTemp146 + fTemp147))) + ((0.00112918485f * (fTemp148 - fTemp149)) + ((0.00573747978f * (fTemp150 - fTemp151)) + ((0.00991851557f * (fTemp152 - fTemp153)) + ((0.00244148076f * fTemp154) + ((0.00350962859f * fTemp155) + ((0.00357066561f * fTemp156) + ((0.00292977691f * fTemp157) + ((0.00265511032f * fTemp158) + ((0.0054933317f * fTemp159) + ((0.00524918362f * fTemp160) + ((0.00317392498f * fTemp161) + ((0.00427259132f * fTemp162) + ((0.00674459059f * fTemp163) + ((0.00460829493f * fTemp164) + ((0.00238044374f * fTemp165) + ((0.00341807306f * fTemp166) + ((0.00253303628f * fTemp167) + ((0.00204474013f * fTemp168) + ((0.00314340647f * fTemp169) + ((0.00332651753f * fTemp170) + ((0.00589007232f * fTemp171) + ((0.00497451704f * fTemp172) + ((0.00592059083f * fTemp173) + ((0.00393688772f * fTemp174) + ((0.00805688649f * fTemp175) + ((0.00650044251f * fTemp176) + ((0.00140385143f * fTemp177) + ((0.00402844325f * fTemp178) + ((0.0135502182f * fTemp179) + ((0.0261848811f * fTemp180) + ((0.0339060649f * fTemp181) + ((0.0357066579f * fTemp182) + ((0.0284432508f * fTemp183) + ((0.0179448836f * fTemp184) + ((0.00799584948f * fTemp185) + ((0.0127872555f * fTemp186) + ((0.0249946602f * fTemp187) + ((0.0361949541f * fTemp188) + ((0.0436414704f * fTemp189) + ((0.0445875414f * fTemp190) + ((0.0314340666f * fTemp191) + ((0.0101626636f * fTemp192) + ((0.0213019196f * fTemp193) + ((0.0529496148f * fTemp194) + ((0.0629291683f * fTemp195) + ((0.0422070995f * fTemp196) + ((0.00503555406f * fTemp197) + ((0.0116885891f * fTemp198) + ((0.0181890316f * fTemp199) + ((0.0141300699f * fTemp200) + ((0.0585955381f * fTemp201) + ((0.0892971605f * fTemp202) + ((0.0848719776f * fTemp203) + ((0.0473647267f * fTemp204) + ((0.019226661f * fTemp205) + ((0.0603350922f * fTemp206) + ((0.0752281249f * fTemp207) + ((0.0648823529f * fTemp208) + ((0.0487380587f * fTemp209) + ((0.0603045747f * fTemp210) + ((0.098178044f * fTemp211) + ((0.13794367f * fTemp212) + ((0.127445295f * fTemp213) + ((0.0601214655f * fTemp214) + ((0.00576799829f * fTemp215) + ((0.0625629425f * fTemp216) + ((0.077211827f * fTemp217) + ((0.0596942045f * fTemp218) + ((0.0472426526f * fTemp219) + ((0.0365916938f * fTemp220) + ((0.0572832413f * fTemp221) + ((0.251991332f * fTemp222) + ((0.338633388f * fTemp223) + ((0.27149266f * fTemp224) + (((((((((((((0.361003458f * fTemp225) + (0.673177302f * fTemp226)) + (0.45512253f * fTemp227)) + (0.133060709f * fTemp228)) + (0.0334482864f * fTemp229)) + (0.12103641f * fTemp230)) + (0.145207062f * fTemp231)) + (0.112735376f * fTemp232)) + (0.103854485f * fTemp233)) + (0.173436686f * fTemp234)) + (0.166234314f * fTemp235)) + (0.0970183387f * fTemp236)) + (0.122775964f * fTemp237)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))) - (((0.000305185094f * (fTemp238 + (fTemp239 + fTemp240))) + ((9.15555283e-05f * (fTemp241 + (fTemp242 - (fTemp243 - (fTemp244 - (fTemp245 + fTemp246)))))) + ((0.000244148076f * (fTemp247 - (fTemp248 + fTemp249))) + ((0.000396740623f * (fTemp250 + (fTemp251 - (fTemp252 + (fTemp253 - (fTemp254 - fTemp255)))))) + ((0.000488296151f * (fTemp256 + (fTemp257 - (fTemp258 + (fTemp259 - fTemp260))))) + ((0.000457777642f * (fTemp261 - (fTemp262 + (fTemp263 - fTemp264)))) + ((0.000640888698f * (fTemp265 + (fTemp266 - (fTemp267 + (fTemp268 - (fTemp269 + (fTemp270 + fTemp271))))))) + ((0.000823999755f * (fTemp272 + (fTemp273 + (fTemp274 - (fTemp275 + (fTemp276 + (fTemp277 + fTemp278))))))) + ((0.000915555283f * (fTemp279 + (fTemp280 + (fTemp281 + (fTemp282 - (fTemp283 - (fTemp284 + (fTemp285 - fTemp286)))))))) + ((0.000885036774f * (fTemp287 + (fTemp288 - (fTemp289 - (fTemp290 - fTemp291))))) + ((0.000793481246f * (fTemp292 + (fTemp293 + (fTemp294 + (fTemp295 + (fTemp296 + fTemp297)))))) + ((0.000854518265f * (fTemp298 - (fTemp299 - fTemp300))) + ((0.000701925717f * (fTemp301 - (fTemp302 + fTemp303))) + ((0.000610370189f * (fTemp304 + (fTemp305 + (fTemp306 - (fTemp307 + (fTemp308 + (fTemp309 - (fTemp310 + (fTemp311 + fTemp312))))))))) + ((0.000762962736f * (fTemp313 - (fTemp314 + (fTemp315 + (fTemp316 + (fTemp317 + fTemp318)))))) + ((0.000946073793f * (fTemp319 + (fTemp320 - (fTemp321 + (fTemp322 - (fTemp323 - fTemp324)))))) + ((0.000732444227f * (fTemp325 + (fTemp326 - (fTemp327 + (fTemp328 - (fTemp329 + fTemp330)))))) + ((0.00201422162f * (fTemp331 - fTemp332)) + ((0.00180059206f * (fTemp333 - fTemp334)) + ((0.000213629566f * (fTemp335 + (fTemp336 + (fVec0[((IOTA - 216) & 511)] - fTemp337)))) + ((3.05185094e-05f * (fTemp338 + fTemp339)) + ((0.00308236945f * (fTemp340 - fTemp341)) + ((0.00167851802f * (fTemp342 - fTemp343)) + ((0.00146488845f * (fTemp344 + (fTemp345 - fTemp346))) + ((0.00262459181f * (fTemp347 - (fTemp348 - (fTemp349 + fTemp350)))) + ((0.00177007355f * (fTemp351 + (fTemp352 - (fTemp353 - (fTemp354 - fTemp355))))) + ((0.00704977568f * (fTemp356 - fTemp357)) + ((0.00186162908f * (fTemp358 - fTemp359)) + ((0.00250251777f * (fTemp360 + (fTemp361 + fTemp362))) + ((0.00247199927f * (fTemp363 + fTemp364)) + ((0.00103762932f * (fTemp365 - fTemp366)) + ((0.00241096225f * (fTemp367 - fTemp368)) + ((0.00131229591f * (fTemp369 + (fTemp370 + fTemp371))) + ((0.0019531846f * (fTemp372 + (fTemp373 + fTemp374))) + ((0.00338755455f * (fTemp375 + fTemp376)) + ((0.0019226661f * (fTemp377 + fTemp378)) + ((0.00619525742f * (fTemp379 + fTemp380)) + ((0.00482192449f * (fTemp381 + fTemp382)) + ((0.00762962736f * (fTemp383 + fTemp384)) + ((0.00988799706f * (fTemp385 + fTemp386)) + ((0.00753807183f * (fTemp387 + fTemp388)) + ((0.0373851731f * (fTemp389 + fTemp390)) + ((0.000183111057f * fTemp391) + ((0.00256355479f * fTemp392) + ((0.00448622089f * fTemp393) + ((0.00299081393f * fTemp394) + ((0.0022583697f * fTemp395) + ((0.00286873989f * fTemp396) + ((0.00277718436f * fTemp397) + ((0.00320444349f * fTemp398) + ((0.003234962f * fTemp399) + ((0.0035401471f * fTemp400) + ((0.00305185094f * fTemp401) + ((0.00436414685f * fTemp402) + ((0.00622577593f * fTemp403) + ((0.00363170262f * fTemp404) + ((0.00390636921f * fTemp405) + ((0.00531022064f * fTemp406) + ((0.00686666463f * fTemp407) + ((0.00720236823f * fTemp408) + ((0.00540177617f * fTemp409) + ((0.00274666585f * fTemp410) + ((0.00512710959f * fTemp411) + ((0.00585955381f * fTemp412) + ((0.00473036896f * fTemp413) + ((0.00488296151f * fTemp414) + ((0.0087282937f * fTemp415) + ((0.00997955259f * fTemp416) + ((0.008087405f * fTemp417) + ((0.0045167394f * fTemp418) + ((0.00375377666f * fTemp419) + ((0.00692770164f * fTemp420) + ((0.0100711081f * fTemp421) + ((0.0118717002f * fTemp422) + ((0.0114139225f * fTemp423) + ((0.0093691824f * fTemp424) + ((0.00708029419f * fTemp425) + ((0.0058290353f * fTemp426) + ((0.00659199804f * fTemp427) + ((0.00930814538f * fTemp428) + ((0.0120242927f * fTemp429) + ((0.0120548112f * fTemp430) + ((0.0083925901f * fTemp431) + ((0.00457777642f * fTemp432) + ((0.014557329f * fTemp433) + ((0.0147099216f * fTemp434) + ((0.00891140476f * fTemp435) + ((0.00604266487f * fTemp436) + ((0.00555436872f * fTemp437) + ((0.00878933072f * fTemp438) + ((0.00924710836f * fTemp439) + ((0.00479140598f * fTemp440) + ((0.0102847377f * fTemp441) + ((0.0165715516f * fTemp442) + ((0.0171208847f * fTemp443) + ((0.0126346629f * fTemp444) + ((0.00509659108f * fTemp445) + ((0.00598162785f * fTemp446) + ((0.00567644276f * fTemp447) + ((0.00634784997f * fTemp448) + ((0.00335703604f * fTemp449) + ((0.0204779208f * fTemp450) + ((0.0303048808f * fTemp451) + ((0.0289620664f * fTemp452) + ((0.0184636991f * fTemp453) + ((0.00875881221f * fTemp454) + ((0.0057985168f * fTemp455) + ((0.00689718314f * fTemp456) + ((0.00985747855f * fTemp457) + ((0.0148014771f * fTemp458) + ((0.0166631062f * fTemp459) + ((0.0120853297f * fTemp460) + ((0.00747703481f * fTemp461) + ((0.00527970213f * fTemp462) + ((0.0038758507f * fTemp463) + ((0.0127262184f * fTemp464) + ((0.0282601397f * fTemp465) + ((0.042115543f * fTemp466) + ((0.0376293212f * fTemp467) + ((0.0142826624f * fTemp468) + ((0.030915251f * fTemp469) + ((0.0390331745f * fTemp470) + ((0.0299996957f * fTemp471) + ((0.0165105145f * fTemp472) + ((0.00494399853f * fTemp473) + ((0.0212408826f * fTemp474) + ((0.0444959886f * fTemp475) + ((0.0408032462f * fTemp476) + ((0.0415356904f * fTemp477) + ((0.0546891689f * fTemp478) + ((0.0627155378f * fTemp479) + ((0.056184575f * fTemp480) + ((0.0307321399f * fTemp481) + ((0.040192876f * fTemp482) + ((0.0516068004f * fTemp483) + ((0.0281380657f * fTemp484) + ((0.0353709534f * fTemp485) + ((0.102481157f * fTemp486) + ((0.0962858945f * fTemp487) + ((0.0492873937f * fTemp488) + ((0.0235908087f * fTemp489) + ((0.0511490218f * fTemp490) + ((0.0719626471f * fTemp491) + ((0.0510269478f * fTemp492) + ((0.0451979116f * fTemp493) + ((0.0950346366f * fTemp494) + ((0.175481424f * fTemp495) + ((0.218909264f * fTemp496) + (((((((0.162755206f * fTemp0) + (0.538529634f * fTemp497)) + (0.990935981f * fTemp498)) + fTemp499) + (0.393169969f * fTemp500)) + (0.0214850307f * fTemp501)) + (0.150425732f * fTemp502)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))) + (0.000122074038f * (fTemp503 + (fTemp504 + (fTemp505 + fTemp506))))))));
			fRec0[1] = fRec0[0];
			IOTA = (IOTA + 1);
		}
	}

};

//----------------------------------------------------------------------------
//  LV2 interface
//----------------------------------------------------------------------------

#line 286 "lv2.cpp"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <bitset>
#include <boost/circular_buffer.hpp>

#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/ext/dynmanifest/dynmanifest.h>
#include <lv2/lv2plug.in/ns/ext/atom/util.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>

// Set this to the proper shared library extension for your system
#ifndef DLLEXT
#define DLLEXT ".so"
#endif

#ifndef URI_PREFIX
#define URI_PREFIX "https://faustlv2.bitbucket.io"
#endif

#ifndef PLUGIN_URI
#define PLUGIN_URI URI_PREFIX "/vintage_mics"
#endif

#define MIDI_EVENT_URI "http://lv2plug.in/ns/ext/midi#MidiEvent"

/* Setting NVOICES at compile time overrides meta data in the Faust source. If
   set, this must be an integer value >= 0. A nonzero value indicates an
   instrument (VSTi) plugin with the given maximum number of voices. Use 1 for
   a monophonic synthesizer, and 0 for a simple effect plugin. If NVOICES
   isn't defined at compile time then the number of voices of an instrument
   plugin can also be set with the global "nvoices" meta data key in the Faust
   source. This setting also adds a special "polyphony" control to the plugin
   which can be used to dynamically adjust the actual number of voices in the
   range 1..NVOICES. */
//#define NVOICES 16

/* This enables a special "tuning" control for instruments which lets you
   select the MTS tuning to be used for the synth. In order to use this, you
   just drop some sysex (.syx) files with MTS octave-based tunings in 1- or
   2-byte format into the ~/.fautvst/tuning directory (these can be generated
   with the author's sclsyx program, https://bitbucket.org/agraef/sclsyx).
   The control will only be shown if any .syx files were found at startup. 0
   selects the default tuning (standard 12-tone equal temperament), i>0 the
   tuning in the ith sysex file (in alphabetic order). */
#ifndef FAUST_MTS
#define FAUST_MTS 1
#endif

/* This allows various manifest data to be generated from the corresponding
   metadata (author, name, description, license) in the Faust source. */
#ifndef FAUST_META
#define FAUST_META 1
#endif

/* This enables automatic MIDI controller mapping based on the midi:ctrl
   attributes in the Faust source. We have this enabled by default, but you
   may have to disable it if the custom controller mapping gets in the way of
   the automation facilities that the host provides. (But then again if the
   host wants to do its own controller mapping then it probably won't, or at
   least shouldn't, send us the MIDI controllers in the first place.) */
#ifndef FAUST_MIDICC
#define FAUST_MIDICC 1
#endif

/* This enables or disables the plugin's custom Qt GUI (cf. lv2ui.cpp). Note
   that this only affects the plugin manifest, the GUI code itself is in a
   separate module created with the lv2ui.cpp architecture. Also, you'll have
   to use the alternative lv2ui manifest templates to tell the LV2 host about
   the GUI. */
#ifndef FAUST_UI
#define FAUST_UI 0
#endif

// You can define these for various debugging output items.
//#define DEBUG_META 1 // recognized MIDI controller metadata
//#define DEBUG_VOICES 1 // triggering of synth voices
//#define DEBUG_VOICE_ALLOC 1 // voice allocation
//#define DEBUG_MIDI 1 // incoming MIDI messages
//#define DEBUG_NOTES 1 // note messages
//#define DEBUG_MIDICC 1 // controller messages
//#define DEBUG_RPN 1 // RPN messages (pitch bend range, master tuning)
//#define DEBUG_MTS 1 // MTS messages (octave/scale tuning)

// Note and voice data structures.

struct NoteInfo {
  uint8_t ch;
  int8_t note;
};

struct VoiceData {
  // Octave tunings (offsets in semitones) per MIDI channel.
  float tuning[16][12];
  // Allocated voices per MIDI channel and note.
  int8_t notes[16][128];
  // Free and used voices.
  int n_free, n_used;
  boost::circular_buffer<int> free_voices;
  boost::circular_buffer<int> used_voices;
  NoteInfo *note_info;
  // Voices queued for note-offs (zero-length notes).
  set<int> queued;
  // Last gate value during run() for each voice. We need to keep track of
  // these so that we can force the Faust synth to retrigger a note when
  // needed.
  float *lastgate;
  // Current pitch bend and pitch bend range on each MIDI channel, in semitones.
  float bend[16], range[16];
  // Current coarse, fine and total master tuning on each MIDI channel (tuning
  // offset relative to A4 = 440 Hz, in semitones).
  float coarse[16], fine[16], tune[16];
  VoiceData(int n) : free_voices(n), used_voices(n) { }
};

#if FAUST_MTS

// Helper classes to read and store MTS tunings.

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <string>
#include <vector>

struct MTSTuning {
  char *name; // name of the tuning
  int len; // length of sysex data in bytes
  unsigned char *data; // sysex data
  MTSTuning() : name(0), len(0), data(0) {}
  MTSTuning& operator=(const MTSTuning &t)
  {
    if (this == &t) return *this;
    if (name) free(name); if (data) free(data);
    name = 0; data = 0; len = t.len;
    if (t.name) {
      name = strdup(t.name); assert(name);
    }
    if (t.data) {
      data = (unsigned char*)malloc(len); assert(data);
      memcpy(data, t.data, len);
    }
    return *this;
  }
  MTSTuning(const MTSTuning& t) : name(0), len(0), data(0)
  { *this = t; }
  MTSTuning(const char *filename);
  ~MTSTuning()
  { if (name) free(name); if (data) free(data); }
};

MTSTuning::MTSTuning(const char *filename)
{
  FILE *fp = fopen(filename, "rb");
  name = 0; len = 0; data = 0;
  if (!fp) return;
  struct stat st;
  if (fstat(fileno(fp), &st)) return;
  len = st.st_size;
  data = (unsigned char*)calloc(len, 1);
  if (!data) {
    len = 0; fclose(fp);
    return;
  }
  assert(len > 0);
  if (fread(data, 1, len, fp) < len) {
    free(data); len = 0; data = 0; fclose(fp);
    return;
  }
  fclose(fp);
  // Do some basic sanity checks.
  if (data[0] != 0xf0 || data[len-1] != 0xf7 || // not a sysex message
      (data[1] != 0x7e && data[1] != 0x7f) || data[3] != 8 || // not MTS
      !((len == 21 && data[4] == 8) ||
	(len == 33 && data[4] == 9))) { // no 1- or 2-byte tuning
    free(data); len = 0; data = 0;
    return;
  }
  // Name of the tuning is the basename of the file, without the trailing .syx
  // suffix.
  string nm = filename;
  size_t p = nm.rfind(".syx");
  if (p != string::npos) nm.erase(p);
  p = nm.rfind('/');
  if (p != string::npos) nm.erase(0, p+1);
  name = strdup(nm.c_str());
  assert(name);
}

struct MTSTunings {
  vector<MTSTuning> tuning;
  MTSTunings() {}
  MTSTunings(const char *path);
};

static bool compareByName(const MTSTuning &a, const MTSTuning &b)
{
  return strcmp(a.name, b.name) < 0;
}

MTSTunings::MTSTunings(const char *path)
{
  DIR *dp = opendir(path);
  if (!dp) return;
  struct dirent *d;
  while ((d = readdir(dp))) {
    string nm = d->d_name;
    if (nm.length() > 4 && nm.substr(nm.length()-4) == ".syx") {
      string pathname = path;
      pathname += "/";
      pathname += nm;
      MTSTuning t(pathname.c_str());
      if (t.data) tuning.push_back(t);
    }
  }
  closedir(dp);
  // sort found tunings by name
  sort(tuning.begin(), tuning.end(), compareByName);
}

#endif

#if FAUST_MIDICC
static float ctrlval(const ui_elem_t &el, uint8_t v)
{
  // Translate the given MIDI controller value to the range and stepsize
  // indicated by the Faust control.
  switch (el.type) {
  case UI_BUTTON: case UI_CHECK_BUTTON:
    return (float)(v>=64);
  default:
    /* Continuous controllers. The problem here is that the range 0..127 is
       not symmetric. We'd like to map 64 to the center of the range
       (max-min)/2 and at the same time retain the full control range
       min..max. So let's just pretend that there are 128 controller values
       and map value 127 to the max value anyway. */
    if (v==127)
      return el.max;
    else
      // XXXFIXME: We might want to add proper quantization according to
      // el.step here.
      return el.min+(el.max-el.min)*v/128;
  }
}
#endif

/***************************************************************************/

/* Polyphonic Faust plugin data structure. XXXTODO: At present this is just a
   big struct which exposes all requisite data. Some more work is needed to
   make the interface a bit more abstract and properly encapsulate the
   internal data structures, so that implementation details can be changed
   more easily. */

struct LV2Plugin {
  const int maxvoices;	// maximum number of voices (zero if not an instrument)
  const int ndsps;	// number of dsp instances (1 if maxvoices==0)
  bool active;		// activation status
  int rate;		// sampling rate
  int nvoices;		// current number of voices (<= maxvoices)
  int tuning_no;	// current tuning number (<= n_tunings)
  vintage_mics **dsp;		// the dsps
  LV2UI **ui;		// their Faust interface descriptions
  int n_in, n_out;	// number of input and output control ports
  int *ctrls;		// Faust ui elements (indices into ui->elems)
  float **ports;	// corresponding LV2 data
  float *portvals;	// cached port data from the last run
  float *midivals[16];	// per-midi channel data
  int *inctrls, *outctrls;	// indices for active and passive controls
  float **inputs, **outputs;	// audio buffers
  int freq, gain, gate;	// indices of voice controls
  unsigned n_samples;	// current block size
  float **outbuf;	// audio buffers for mixing down the voices
  float **inbuf;	// dummy input buffer
  LV2_Atom_Sequence* event_port; // midi input
  float *poly, *tuning;	// polyphony and tuning ports
  std::map<uint8_t,int> ctrlmap; // MIDI controller map
  // Needed host features.
  LV2_URID_Map* map;	// the urid extension
  LV2_URID midi_event;	// midi event uri
  // Current RPN MSB and LSB numbers, as set with controllers 101 and 100.
  uint8_t rpn_msb[16], rpn_lsb[16];
  // Current data entry MSB and LSB numbers, as set with controllers 6 and 38.
  uint8_t data_msb[16], data_lsb[16];
  // Synth voice data (instruments only).
  VoiceData *vd;

  // Static methods. These all use static data so they can be invoked before
  // instantiating a plugin.

  // Global meta data (dsp name, author, etc.).
  static Meta *meta;
  static void init_meta()
  {
    if (!meta && (meta = new Meta)) {
      // We allocate the temporary dsp object on the heap here, to prevent
      // large dsp objects from running out of stack in environments where
      // stack space is precious (e.g., Reaper). Note that if any of these
      // allocations fail then no meta data will be available, but at least we
      // won't make the host crash and burn.
      vintage_mics* tmp_dsp = new vintage_mics();
      if (tmp_dsp) {
	tmp_dsp->metadata(meta);
	delete tmp_dsp;
      }
    }
  }
  static const char *meta_get(const char *key, const char *deflt)
  {
    init_meta();
    return meta?meta->get(key, deflt):deflt;
  }

  static const char *pluginName()
  {
    return meta_get("name", "vintage_mics");
  }

  static const char *pluginAuthor()
  {
    return meta_get("author", "");
  }

  static const char *pluginDescription()
  {
    return meta_get("description", "");
  }

  static const char *pluginLicense()
  {
    return meta_get("license", "");
  }

  static const char *pluginVersion()
  {
    return meta_get("version", "");
  }

  // Load a collection of sysex files with MTS tunings in ~/.faust/tuning.
  static int n_tunings;
#if FAUST_MTS
  static MTSTunings *mts;

  static MTSTunings *load_sysex_data()
  {
    if (!mts) {
      string mts_path;
      // Look for FAUST_HOME. If that isn't set, try $HOME/.faust. If HOME
      // isn't set either, just assume a .faust subdir of the cwd.
      const char *home = getenv("FAUST_HOME");
      if (home)
	mts_path = home;
      else {
	home = getenv("HOME");
	if (home) {
	  mts_path = home;
	  mts_path += "/.faust";
	} else
	  mts_path = ".faust";
      }
      // MTS tunings are looked for in this subdir.
      mts_path += "/tuning";
      mts = new MTSTunings(mts_path.c_str());
#ifdef __APPLE__
      if (!mts || mts->tuning.size() == 0) {
	// Also check ~/Library/Faust/Tuning on the Mac.
	home = getenv("HOME");
	if (home) {
	  if (mts) delete mts;
	  mts_path = home;
	  mts_path += "/Library/Faust/Tuning";
	  mts = new MTSTunings(mts_path.c_str());
	}
      }
#endif
      n_tunings = mts->tuning.size();
    }
    return mts;
  }
#endif

  // The number of voices of an instrument plugin. We get this information
  // from the global meta data (nvoices key) of the dsp module if present, and
  // you can also override this setting at compile time by defining the
  // NVOICES macro. If neither is defined or the value is zero then the plugin
  // becomes a simple audio effect instead.
  static int numVoices()
  {
#ifdef NVOICES
    return NVOICES;
#else
    const char *numVoices = meta_get("nvoices", "0");
    int nvoices = atoi(numVoices);
    if (nvoices < 0 ) nvoices = 0;
    return nvoices;
#endif
  }

  // Instance methods.

  LV2Plugin(const int num_voices, const int sr)
    : maxvoices(num_voices), ndsps(num_voices<=0?1:num_voices),
      vd(num_voices>0?new VoiceData(num_voices):0)
  {
    // Initialize static data.
    init_meta();
#if FAUST_MTS
    // Synth: load tuning sysex data if present.
    if (num_voices>0) load_sysex_data();
#endif
    // Allocate data structures and set some reasonable defaults.
    dsp = (vintage_mics**)calloc(ndsps, sizeof(vintage_mics*));
    ui = (LV2UI**)calloc(ndsps, sizeof(LV2UI*));
    assert(dsp && ui);
    if (vd) {
      vd->note_info = (NoteInfo*)calloc(ndsps, sizeof(NoteInfo));
      vd->lastgate = (float*)calloc(ndsps, sizeof(float));
      assert(vd->note_info && vd->lastgate);
    }
    active = false;
    rate = sr;
    nvoices = maxvoices;
    tuning_no = 0;
    n_in = n_out = 0;
    map = NULL;
    midi_event = -1;
    event_port = NULL;
    poly = tuning = NULL;
    freq = gain = gate = -1;
    if (vd) {
      vd->n_free = maxvoices;
      for (int i = 0; i < maxvoices; i++) {
	vd->free_voices.push_back(i);
	vd->lastgate[i] = 0.0f;
      }
      for (int i = 0; i < 16; i++) {
	vd->bend[i] = 0.0f;
	vd->range[i] = 2.0f;
	vd->coarse[i] = vd->fine[i] = vd->tune[i] = 0.0f;
	for (int j = 0; j < 12; j++)
	  vd->tuning[i][j] = 0.0f;
      }
      vd->n_used = 0;
      memset(vd->notes, 0xff, sizeof(vd->notes));
    }
    n_samples = 0;
    ctrls = inctrls = outctrls = NULL;
    ports = inputs = outputs = inbuf = outbuf = NULL;
    portvals = NULL;
    memset(midivals, 0, sizeof(midivals));
    // Initialize the Faust DSPs.
    for (int i = 0; i < ndsps; i++) {
      dsp[i] = new vintage_mics();
      ui[i] = new LV2UI(num_voices);
      dsp[i]->init(rate);
      dsp[i]->buildUserInterface(ui[i]);
    }
    // The ports are numbered as follows: 0..k-1 are the control ports, then
    // come the n audio input ports, then the m audio output ports, and
    // finally the midi input port and the polyphony and tuning controls.
    int k = ui[0]->nports, p = 0, q = 0;
    int n = dsp[0]->getNumInputs(), m = dsp[0]->getNumOutputs();
    // Allocate tables for the built-in control elements and their ports.
    ctrls = (int*)calloc(k, sizeof(int));
    inctrls = (int*)calloc(k, sizeof(int));
    outctrls = (int*)calloc(k, sizeof(int));
    ports = (float**)calloc(k, sizeof(float*));
    portvals = (float*)calloc(k, sizeof(float));
    assert(k == 0 || (ctrls && inctrls && outctrls && ports && portvals));
    for (int ch = 0; ch < 16; ch++) {
      midivals[ch] = (float*)calloc(k, sizeof(float));
      assert(k == 0 || midivals[ch]);
    }
    // Scan the Faust UI for active and passive controls which become the
    // input and output control ports of the plugin, respectively.
    for (int i = 0, j = 0; i < ui[0]->nelems; i++) {
      switch (ui[0]->elems[i].type) {
      case UI_T_GROUP: case UI_H_GROUP: case UI_V_GROUP: case UI_END_GROUP:
	// control groups (ignored right now)
	break;
      case UI_H_BARGRAPH: case UI_V_BARGRAPH:
	// passive controls (output ports)
	ctrls[j++] = i;
	outctrls[q++] = i;
	break;
      default:
	// active controls (input ports)
	if (maxvoices == 0)
	  goto noinstr;
	else if (freq == -1 &&
		 !strcmp(ui[0]->elems[i].label, "freq"))
	  freq = i;
	else if (gain == -1 &&
		 !strcmp(ui[0]->elems[i].label, "gain"))
	  gain = i;
	else if (gate == -1 &&
		 !strcmp(ui[0]->elems[i].label, "gate"))
	  gate = i;
	else {
	noinstr:
#if FAUST_MIDICC
	  std::map< int, list<strpair> >::iterator it =
	    ui[0]->metadata.find(i);
	  if (it != ui[0]->metadata.end()) {
	    // Scan for controller mappings.
	    for (std::list<strpair>::iterator jt = it->second.begin();
		 jt != it->second.end(); jt++) {
	      const char *key = jt->first, *val = jt->second;
#if DEBUG_META
	      fprintf(stderr, "ctrl '%s' meta: '%s' -> '%s'\n",
		      ui[0]->elems[i].label, key, val);
#endif
	      if (strcmp(key, "midi") == 0) {
		unsigned num;
		if (sscanf(val, "ctrl %u", &num) < 1) continue;
#if 0 // enable this to get feedback about controller assignments
		fprintf(stderr, "%s: cc %d -> %s\n", PLUGIN_URI, num,
			ui[0]->elems[i].label);
#endif
		ctrlmap.insert(std::pair<uint8_t,int>(num, p));
	      }
	    }
	  }
#endif
	  ctrls[j++] = i;
	  inctrls[p++] = i;
	  int p = ui[0]->elems[i].port;
	  float val = ui[0]->elems[i].init;
	  assert(p>=0);
	  portvals[p] = val;
	  for (int ch = 0; ch < 16; ch++)
	    midivals[ch][p] = val;
	}
	break;
      }
    }
    // Realloc the inctrls and outctrls vectors to their appropriate sizes.
    inctrls = (int*)realloc(inctrls, p*sizeof(int));
    assert(p == 0 || inctrls);
    outctrls = (int*)realloc(outctrls, q*sizeof(int));
    assert(q == 0 || outctrls);
    n_in = p; n_out = q;
    // Allocate vectors for the audio input and output ports. Like
    // ports, these will be initialized in the connect_port callback.
    inputs = (float**)calloc(n, sizeof(float*));
    assert(n == 0 || inputs);
    outputs = (float**)calloc(m, sizeof(float*));
    assert(m == 0 || outputs);
    if (maxvoices > 0) {
      // Initialize the mixdown buffer.
      outbuf = (float**)calloc(m, sizeof(float*));
      assert(m == 0 || outbuf);
      // We start out with a blocksize of 512 samples here. Hopefully this is
      // enough for most realtime hosts so that we can avoid reallocations
      // later when we know what the actual blocksize is.
      n_samples = 512;
      for (int i = 0; i < m; i++) {
	outbuf[i] = (float*)malloc(n_samples*sizeof(float));
	assert(outbuf[i]);
      }
      // Initialize a 1-sample dummy input buffer used for retriggering notes.
      inbuf = (float**)calloc(n, sizeof(float*));
      assert(n == 0 || inbuf);
      for (int i = 0; i < m; i++) {
	inbuf[i] = (float*)malloc(sizeof(float));
	assert(inbuf[i]);
	*inbuf[i] = 0.0f;
      }
    }
  }

  ~LV2Plugin()
  {
    const int n = dsp[0]->getNumInputs();
    const int m = dsp[0]->getNumOutputs();
    for (int i = 0; i < ndsps; i++) {
      delete dsp[i];
      delete ui[i];
    }
    free(ctrls); free(inctrls); free(outctrls);
    free(ports); free(portvals);
    free(inputs); free(outputs);
    for (int ch = 0; ch < 16; ch++)
      free(midivals[ch]);
    if (inbuf) {
      for (int i = 0; i < n; i++)
	free(inbuf[i]);
      free(inbuf);
    }
    if (outbuf) {
      for (int i = 0; i < m; i++)
	free(outbuf[i]);
      free(outbuf);
    }
    free(dsp); free(ui);
    if (vd) {
      free(vd->note_info);
      free(vd->lastgate);
      delete vd;
    }
  }
  // Voice allocation.

#if DEBUG_VOICE_ALLOC
  void print_voices(const char *msg)
  {
    fprintf(stderr, "%s: notes =", msg);
    for (uint8_t ch = 0; ch < 16; ch++)
      for (int note = 0; note < 128; note++)
	if (vd->notes[ch][note] >= 0)
	  fprintf(stderr, " [%d] %d(#%d)", ch, note, vd->notes[ch][note]);
    fprintf(stderr, "\nqueued (%d):", vd->queued.size());
    for (int i = 0; i < nvoices; i++)
      if (vd->queued.find(i) != vd->queued.end()) fprintf(stderr, " #%d", i);
    fprintf(stderr, "\nused (%d):", vd->n_used);
    for (boost::circular_buffer<int>::iterator it = vd->used_voices.begin();
	 it != vd->used_voices.end(); it++)
      fprintf(stderr, " #%d->%d", *it, vd->note_info[*it].note);
    fprintf(stderr, "\nfree (%d):", vd->n_free);
    for (boost::circular_buffer<int>::iterator it = vd->free_voices.begin();
	 it != vd->free_voices.end(); it++)
      fprintf(stderr, " #%d", *it);
    fprintf(stderr, "\n");
  }
#endif

  int alloc_voice(uint8_t ch, int8_t note, int8_t vel)
  {
    int i = vd->notes[ch][note];
    if (i >= 0) {
      // note already playing on same channel, retrigger it
      voice_off(i);
      voice_on(i, note, vel, ch);
      // move this voice to the end of the used list
      for (boost::circular_buffer<int>::iterator it =
	     vd->used_voices.begin();
	   it != vd->used_voices.end(); it++) {
	if (*it == i) {
	  vd->used_voices.erase(it);
	  vd->used_voices.push_back(i);
	  break;
	}
      }
#if DEBUG_VOICE_ALLOC
      print_voices("retrigger");
#endif
      return i;
    } else if (vd->n_free > 0) {
      // take voice from free list
      int i = vd->free_voices.front();
      vd->free_voices.pop_front();
      vd->n_free--;
      vd->used_voices.push_back(i);
      vd->note_info[i].ch = ch;
      vd->note_info[i].note = note;
      vd->n_used++;
      voice_on(i, note, vel, ch);
      vd->notes[ch][note] = i;
#if DEBUG_VOICE_ALLOC
      print_voices("alloc");
#endif
      return i;
    } else {
      // steal a voice
      assert(vd->n_used > 0);
      // FIXME: Maybe we should look for the oldest note on the *current*
      // channel here, but this is faster.
      int i = vd->used_voices.front();
      int oldch = vd->note_info[i].ch;
      int oldnote = vd->note_info[i].note;
      voice_off(i);
      vd->notes[oldch][oldnote] = -1;
      vd->queued.erase(i);
      vd->used_voices.pop_front();
      vd->used_voices.push_back(i);
      vd->note_info[i].ch = ch;
      vd->note_info[i].note = note;
      voice_on(i, note, vel, ch);
      vd->notes[ch][note] = i;
#if DEBUG_VOICE_ALLOC
      print_voices("steal");
#endif
      return i;
    }
  }

  int dealloc_voice(uint8_t ch, int8_t note, int8_t vel)
  {
    int i = vd->notes[ch][note];
    if (i >= 0) {
      if (vd->lastgate[i] == 0.0f && gate >= 0) {
	// zero-length note, queued for later
	vd->queued.insert(i);
	vd->notes[ch][note] = -1;
#if DEBUG_VOICE_ALLOC
	print_voices("dealloc (queued)");
#endif
	return i;
      }
      assert(vd->n_free < nvoices);
      vd->free_voices.push_back(i);
      vd->n_free++;
      voice_off(i);
      vd->notes[ch][note] = -1;
      // erase this voice from the used list
      for (boost::circular_buffer<int>::iterator it =
	     vd->used_voices.begin();
	   it != vd->used_voices.end(); it++) {
	if (*it == i) {
	  vd->used_voices.erase(it);
	  vd->n_used--;
	  break;
	}
      }
#if DEBUG_VOICE_ALLOC
      print_voices("dealloc");
#endif
      return i;
    }
    return -1;
  }


  float midicps(int8_t note, uint8_t chan)
  {
    float pitch = note + vd->tune[chan] +
      vd->tuning[chan][note%12] + vd->bend[chan];
    return 440.0*pow(2, (pitch-69.0)/12.0);
  }

  void voice_on(int i, int8_t note, int8_t vel, uint8_t ch)
  {
    if (vd->lastgate[i] == 1.0f && gate >= 0) {
      // Make sure that the synth sees the 0.0f gate so that the voice is
      // properly retriggered.
      *ui[i]->elems[gate].zone = 0.0f;
      dsp[i]->compute(1, inbuf, outbuf);
    }
#if DEBUG_VOICES
    fprintf(stderr, "voice on: %d %d (%g Hz) %d (%g)\n", i,
	    note, midicps(note, ch), vel, vel/127.0);
#endif
    if (freq >= 0)
      *ui[i]->elems[freq].zone = midicps(note, ch);
    if (gate >= 0)
      *ui[i]->elems[gate].zone = 1.0f;
    if (gain >= 0)
      *ui[i]->elems[gain].zone = vel/127.0;
    // reinitialize the per-channel control data for this voice
    for (int idx = 0; idx < n_in; idx++) {
      int j = inctrls[idx], k = ui[0]->elems[j].port;
      *ui[i]->elems[j].zone = midivals[ch][k];
    }
  }

  void voice_off(int i)
  {
#if DEBUG_VOICES
    fprintf(stderr, "voice off: %d\n", i);
#endif
    if (gate >= 0)
      *ui[i]->elems[gate].zone = 0.0f;
  }

  void update_voices(uint8_t chan)
  {
    // update running voices on the given channel after tuning or pitch bend
    // changes
    for (boost::circular_buffer<int>::iterator it =
	   vd->used_voices.begin();
	 it != vd->used_voices.end(); it++) {
      int i = *it;
      if (vd->note_info[i].ch == chan && freq >= 0) {
	int note = vd->note_info[i].note;
	*ui[i]->elems[freq].zone = midicps(note, chan);
      }
    }
  }

  void all_notes_off()
  {
    for (int i = 0; i < nvoices; i++)
      voice_off(i);
    for (int i = 0; i < 16; i++)
      vd->bend[i] = 0.0f;
    memset(vd->notes, 0xff, sizeof(vd->notes));
    vd->free_voices.clear();
    vd->n_free = nvoices;
    for (int i = 0; i < nvoices; i++)
      vd->free_voices.push_back(i);
    vd->queued.clear();
    vd->used_voices.clear();
    vd->n_used = 0;
  }

  void all_notes_off(uint8_t chan)
  {
    for (boost::circular_buffer<int>::iterator it =
	   vd->used_voices.begin();
	 it != vd->used_voices.end(); ) {
      int i = *it;
      if (vd->note_info[i].ch == chan) {
	assert(vd->n_free < nvoices);
	vd->free_voices.push_back(i);
	vd->n_free++;
	voice_off(i);
	vd->notes[vd->note_info[i].ch][vd->note_info[i].note] = -1;
	vd->queued.erase(i);
	// erase this voice from the used list
	it = vd->used_voices.erase(it);
	vd->n_used--;
#if DEBUG_VOICE_ALLOC
	print_voices("dealloc (all-notes-off)");
#endif
      } else
	it++;
    }
    vd->bend[chan] = 0.0f;
  }

  void queued_notes_off()
  {
    if (vd->queued.empty()) return;
    for (int i = 0; i < nvoices; i++)
      if (vd->queued.find(i) != vd->queued.end()) {
	assert(vd->n_free < nvoices);
	vd->free_voices.push_back(i);
	vd->n_free++;
	voice_off(i);
	vd->notes[vd->note_info[i].ch][vd->note_info[i].note] = -1;
	vd->queued.erase(i);
	// erase this voice from the used list
	for (boost::circular_buffer<int>::iterator it =
	       vd->used_voices.begin();
	     it != vd->used_voices.end(); it++) {
	  if (*it == i) {
	    vd->used_voices.erase(it);
	    vd->n_used--;
	    break;
	  }
	}
#if DEBUG_VOICE_ALLOC
	print_voices("dealloc (unqueued)");
#endif
      }
  }

  // Plugin activation status. suspend() deactivates a plugin (disables audio
  // processing), resume() reactivates it. Also, set_rate() changes the sample
  // rate. Note that the audio and MIDI process functions (see below) can
  // still be called in deactivated state, but this is optional. The plugin
  // tries to do some reasonable processing in either case, no matter whether
  // the host plugin architecture actually executes callbacks in suspended
  // state or not.

  void suspend()
  {
    active = false;
    if (maxvoices > 0) all_notes_off();
  }

  void resume()
  {
    for (int i = 0; i < ndsps; i++)
      dsp[i]->init(rate);
    for (int i = 0, j = 0; i < ui[0]->nelems; i++) {
      int p = ui[0]->elems[i].port;
      if (p >= 0) {
	float val = ui[0]->elems[i].init;
	portvals[p] = val;
      }
    }
    active = true;
  }

  void set_rate(int sr)
  {
    rate = sr;
    for (int i = 0; i < ndsps; i++)
      dsp[i]->init(rate);
  }

  // Audio and MIDI process functions. The plugin should run these in the
  // appropriate real-time callbacks.

  void process_audio(int blocksz, float **inputs, float **outputs)
  {
    int n = dsp[0]->getNumInputs(), m = dsp[0]->getNumOutputs();
    AVOIDDENORMALS;
    if (maxvoices > 0) queued_notes_off();
    if (!active) {
      // Depending on the plugin architecture and host, this code might never
      // be invoked, since the plugin is deactivitated at this point. But
      // let's do something reasonable here anyway.
      if (n == m) {
	// copy inputs to outputs
	for (int i = 0; i < m; i++)
	  for (unsigned j = 0; j < blocksz; j++)
	    outputs[i][j] = inputs[i][j];
      } else {
	// silence
	for (int i = 0; i < m; i++)
	  for (unsigned j = 0; j < blocksz; j++)
	    outputs[i][j] = 0.0f;
      }
      return;
    }
    // Handle changes in the polyphony and tuning controls.
    bool is_instr = maxvoices > 0;
    if (is_instr) {
      if (!poly)
	; // this shouldn't happen but...
      else if (nvoices != (int)*poly &&
	       (int)*poly > 0 && (int)*poly <= maxvoices) {
	for (int i = 0; i < nvoices; i++)
	  voice_off(i);
        nvoices = (int)*poly;
	// Reset the voice allocation.
	memset(vd->notes, 0xff, sizeof(vd->notes));
	vd->free_voices.clear();
	vd->n_free = nvoices;
	for (int i = 0; i < nvoices; i++)
	  vd->free_voices.push_back(i);
	vd->used_voices.clear();
	vd->n_used = 0;
      } else
	*poly = nvoices;
#if FAUST_MTS
      if (tuning && tuning_no != (int)*tuning) change_tuning((int)*tuning);
#endif
    }
    // Only update the controls (of all voices simultaneously) if a port value
    // actually changed. This is necessary to allow MIDI controllers to modify
    // the values for individual MIDI channels (see processEvents below). Also
    // note that this will be done *after* processing the MIDI controller data
    // for the current audio block, so manual inputs can still override these.
    for (int i = 0; i < n_in; i++) {
      int j = inctrls[i], k = ui[0]->elems[j].port;
      float &oldval = portvals[k], newval = *ports[k];
      if (newval != oldval) {
	if (is_instr) {
	  // instrument: update running voices
	  for (boost::circular_buffer<int>::iterator it =
		 vd->used_voices.begin();
	       it != vd->used_voices.end(); it++) {
	    int i = *it;
	    *ui[i]->elems[j].zone = newval;
	  }
	} else {
	  // simple effect: here we only have a single dsp instance
	  *ui[0]->elems[j].zone = newval;
	}
	// also update the MIDI controller data for all channels (manual
	// control input is always omni)
	for (int ch = 0; ch < 16; ch++)
	  midivals[ch][k] = newval;
	// record the new value
	oldval = newval;
      }
    }
    // Initialize the output buffers.
    if (n_samples < blocksz) {
      // We need to enlarge the buffers. We're not officially allowed to do
      // this here (presumably in the realtime thread), but since we usually
      // don't know the hosts's block size beforehand, there's really nothing
      // else that we can do. Let's just hope that doing this once suffices,
      // then hopefully noone will notice.
      if (outbuf) {
	for (int i = 0; i < m; i++) {
	  outbuf[i] = (float*)realloc(outbuf[i],
				      blocksz*sizeof(float));
	  assert(outbuf[i]);
	}
      }
      n_samples = blocksz;
    }
    if (outbuf) {
      // Polyphonic instrument: Mix the voices down to one signal.
      for (int i = 0; i < m; i++)
	for (unsigned j = 0; j < blocksz; j++)
	  outputs[i][j] = 0.0f;
      for (int l = 0; l < nvoices; l++) {
	// Let Faust do all the hard work.
	dsp[l]->compute(blocksz, inputs, outbuf);
	for (int i = 0; i < m; i++)
	  for (unsigned j = 0; j < blocksz; j++)
	    outputs[i][j] += outbuf[i][j];
      }
    } else {
      // Simple effect: We can write directly to the output buffer.
      dsp[0]->compute(blocksz, inputs, outputs);
    }
    // Finally grab the passive controls and write them back to the
    // corresponding control ports. NOTE: Depending on the plugin
    // architecture, this might require a host call to get the control GUI
    // updated in real-time (if the host supports this at all).
    // FIXME: It's not clear how to aggregate the data of the different
    // voices. We compute the maximum of each control for now.
    for (int i = 0; i < n_out; i++) {
      int j = outctrls[i], k = ui[0]->elems[j].port;
      float *z = ui[0]->elems[j].zone;
      *ports[k] = *z;
      for (int l = 1; l < nvoices; l++) {
	float *z = ui[l]->elems[j].zone;
	if (*ports[k] < *z)
	  *ports[k] = *z;
      }
    }
    // Keep track of the last gates set for each voice, so that voices can be
    // forcibly retriggered if needed.
    if (gate >= 0)
      for (int i = 0; i < nvoices; i++)
	vd->lastgate[i] =
	  *ui[i]->elems[gate].zone;
  }

  // This processes just a single MIDI message, so to process an entire series
  // of MIDI events you'll have to loop over the event data in the plugin's
  // MIDI callback. XXXTODO: Sample-accurate processing of MIDI events.
  
  void process_midi(unsigned char *data, int sz)
  {
#if DEBUG_MIDI
    fprintf(stderr, "midi ev (%d bytes):", sz);
    for (int i = 0; i < sz; i++)
      fprintf(stderr, " 0x%0x", data[i]);
    fprintf(stderr, "\n");
#endif
    uint8_t status = data[0] & 0xf0, chan = data[0] & 0x0f;
    bool is_instr = maxvoices > 0;
    switch (status) {
    case 0x90: {
      if (!is_instr) break;
      // note on
#if DEBUG_NOTES
      fprintf(stderr, "note-on  chan %d, note %d, vel %d\n", chan+1,
	      data[1], data[2]);
#endif
      if (data[2] == 0) goto note_off;
      alloc_voice(chan, data[1], data[2]);
      break;
    }
    case 0x80: {
      if (!is_instr) break;
      // note off
#if DEBUG_NOTES
      fprintf(stderr, "note-off chan %d, note %d, vel %d\n", chan+1,
	      data[1], data[2]);
#endif
      note_off:
      dealloc_voice(chan, data[1], data[2]);
      break;
    }
    case 0xe0: {
      if (!is_instr) break;
      // pitch bend
      // data[1] is LSB, data[2] MSB, range is 0..0x3fff (which maps to
      // -2..+2 semitones by default), center point is 0x2000 = 8192
      int val = data[1] | (data[2]<<7);
      vd->bend[chan] =
	(val-0x2000)/8192.0f*vd->range[chan];
#if DEBUG_MIDICC
      fprintf(stderr, "pitch-bend (chan %d): %g cent\n", chan+1,
	      vd->bend[chan]*100.0);
#endif
      update_voices(chan);
      break;
    }
    case 0xb0: {
      // controller change
      switch (data[1]) {
      case 120: case 123:
	if (!is_instr) break;
	// all-sound-off and all-notes-off controllers (these are treated
	// the same in the current implementation)
	all_notes_off(chan);
#if DEBUG_MIDICC
	fprintf(stderr, "all-notes-off (chan %d)\n", chan+1);
#endif
	break;
      case 121:
	// all-controllers-off (in the current implementation, this just
	// resets the RPN-related controllers)
	data_msb[chan] = data_lsb[chan] = 0;
	rpn_msb[chan] = rpn_lsb[chan] = 0x7f;
#if DEBUG_MIDICC
	fprintf(stderr, "all-controllers-off (chan %d)\n", chan+1);
#endif
	break;
      case 101: case 100:
	// RPN MSB/LSB
	if (data[1] == 101)
	  rpn_msb[chan] = data[2];
	else
	  rpn_lsb[chan] = data[2];
	break;
      case 6: case 38:
	// data entry coarse/fine
	if (data[1] == 6)
	  data_msb[chan] = data[2];
	else
	  data_lsb[chan] = data[2];
	goto rpn;
      case 96: case 97:
	// data increment/decrement
	/* NOTE: The specification of these controllers is a complete
	   mess. Originally, the MIDI specification didn't have anything
	   to say about their exact behaviour at all. Nowadays, the
	   behaviour depends on which RPN or NRPN is being modified, which
	   is also rather confusing. Fortunately, as we only handle RPNs
	   0..2 here anyway, it's sufficient to assume the MSB for RPN #2
	   (channel coarse tuning) and the LSB otherwise. */
	if (rpn_msb[chan] == 0 && rpn_lsb[chan] == 2) {
	  // modify the MSB
	  if (data[1] == 96 && data_msb[chan] < 0x7f)
	    data_msb[chan]++;
	  else if (data[1] == 97 && data_msb[chan] > 0)
	    data_msb[chan]--;
	} else {
	  // modify the LSB
	  if (data[1] == 96 && data_lsb[chan] < 0x7f)
	    data_lsb[chan]++;
	  else if (data[1] == 97 && data_lsb[chan] > 0)
	    data_lsb[chan]--;
	}
      rpn:
	if (!is_instr) break;
	if (rpn_msb[chan] == 0) {
	  switch (rpn_lsb[chan]) {
	  case 0:
	    // pitch bend range, coarse value is in semitones, fine value
	    // in cents
	    vd->range[chan] = data_msb[chan]+
	      data_lsb[chan]/100.0;
#if DEBUG_RPN
	    fprintf(stderr, "pitch-bend-range (chan %d): %g cent\n", chan+1,
		    vd->range[chan]*100.0);
#endif
	    break;
	  case 1:
	    {
	      // channel fine tuning (14 bit value, range -100..+100 cents)
	      int value = (data_msb[chan]<<7) |
		data_lsb[chan];
	      vd->fine[chan] = (value-8192)/8192.0f;
	    }
	    goto master_tune;
	  case 2:
	    // channel coarse tuning (only msb is used, range -64..+63
	    // semitones)
	    vd->coarse[chan] = data_msb[chan]-64;
	  master_tune:
	    vd->tune[chan] = vd->coarse[chan]+
	      vd->fine[chan];
#if DEBUG_RPN
	    fprintf(stderr, "master-tuning (chan %d): %g cent\n", chan+1,
		    vd->tune[chan]*100.0);
#endif
	    update_voices(chan);
	    break;
	  default:
	    break;
	  }
	}
	break;
      default: {
#if FAUST_MIDICC
	// interpret all other controller changes according to the MIDI
	// controller map defined in the Faust plugin itself
	std::map<uint8_t,int>::iterator it = ctrlmap.find(data[1]);
	if (it != ctrlmap.end()) {
	  // defined MIDI controller
	  int j = inctrls[it->second],
	    k = ui[0]->elems[j].port;
	  float val = ctrlval(ui[0]->elems[j], data[2]);
	  midivals[chan][k] = val;
	  if (is_instr) {
	    // instrument: update running voices on this channel
	    for (boost::circular_buffer<int>::iterator it =
		   vd->used_voices.begin();
		 it != vd->used_voices.end(); it++) {
	      int i = *it;
	      if (vd->note_info[i].ch == chan)
		*ui[i]->elems[j].zone = val;
	    }
	  } else {
	    // simple effect: here we only have a single dsp instance and
	    // we're operating in omni mode, so we just update the control no
	    // matter what the midi channel is
	    *ui[0]->elems[j].zone = val;
	  }
#if DEBUG_MIDICC
	  fprintf(stderr, "ctrl-change chan %d, ctrl %d, val %d\n", chan+1,
		  data[1], data[2]);
#endif
	}
#endif
	break;
      }
      }
      break;
    }
    default:
      break;
    }
  }

  // Process an MTS sysex message and update the control values accordingly.

  void process_sysex(uint8_t *data, int sz)
  {
    if (!data || sz < 2) return;
#if DEBUG_MIDI
    fprintf(stderr, "midi sysex (%d bytes):", sz);
    for (int i = 0; i < sz; i++)
      fprintf(stderr, " 0x%0x", data[i]);
    fprintf(stderr, "\n");
#endif
    if (data[0] == 0xf0) {
      // Skip over the f0 and f7 status bytes in case they are included in the
      // dump.
      data++; sz--;
      if (data[sz-1] == 0xf7) sz--;
    }
    if ((data[0] == 0x7e || data[0] == 0x7f) && data[2] == 8) {
      // MIDI tuning standard
      bool realtime = data[0] == 0x7f;
      if ((sz == 19 && data[3] == 8) ||
	  (sz == 31 && data[3] == 9)) {
	// MTS scale/octave tuning 1- or 2-byte form
	bool onebyte = data[3] == 8;
	unsigned chanmsk = (data[4]<<14) | (data[5]<<7) | data[6];
	for (int i = 0; i < 12; i++) {
	  float t;
	  if (onebyte)
	    t = (data[i+7]-64)/100.0;
	  else
	    t = (((data[2*i+7]<<7)|data[2*i+8])-8192)/8192.0;
	  for (uint8_t ch = 0; ch < 16; ch++)
	    if (chanmsk & (1<<ch))
	      vd->tuning[ch][i] = t;
	}
	if (realtime) {
	  for (uint8_t ch = 0; ch < 16; ch++)
	    if (chanmsk & (1<<ch)) {
	      // update running voices on this channel
	      update_voices(ch);
	    }
	}
#if DEBUG_MTS
	fprintf(stderr, "octave-tuning-%s (chan ",
		realtime?"realtime":"non-realtime");
	bool first = true;
	for (uint8_t i = 0; i < 16; )
	  if (chanmsk & (1<<i)) {
	    uint8_t j;
	    for (j = i+1; j < 16 && (chanmsk&(1<<j)); )
	      j++;
	    if (first)
	      first = false;
	    else
	      fprintf(stderr, ",");
	    if (j > i+1)
	      fprintf(stderr, "%u-%u", i+1, j);
	    else
	      fprintf(stderr, "%u", i+1);
	    i = j;
	  } else
	    i++;
	fprintf(stderr, "):");
	if (onebyte) {
	  for (int i = 7; i < 19; i++) {
	    int val = data[i];
	    fprintf(stderr, " %d", val-64);
	  }
	} else {
	  for (int i = 7; i < 31; i++) {
	    int val = data[i++] << 7;
	    val |= data[i];
	    fprintf(stderr, " %g", ((double)val-8192.0)/8192.0*100.0);
	  }
	}
	fprintf(stderr, "\n");
#endif
      }
    }
  }

  // Change to a given preloaded tuning. The given tuning number may be in the
  // range 1..PFaustPlugin::n_tunings, zero denotes the default tuning (equal
  // temperament). This is only supported if FAUST_MTS is defined at compile
  // time.

  void change_tuning(int num)
  {
#if FAUST_MTS
    if (!mts || num == tuning_no) return;
    if (num < 0) num = 0;
    if (num > mts->tuning.size())
      num = mts->tuning.size();
    tuning_no = num;
    if (tuning_no > 0) {
      process_sysex(mts->tuning[tuning_no-1].data,
		    mts->tuning[tuning_no-1].len);
    } else {
      memset(vd->tuning, 0, sizeof(vd->tuning));
#if DEBUG_MTS
      fprintf(stderr,
	      "octave-tuning-default (chan 1-16): equal temperament\n");
#endif
    }
#endif
  }

};

Meta *LV2Plugin::meta = 0;
int LV2Plugin::n_tunings = 0;
#if FAUST_MTS
MTSTunings *LV2Plugin::mts = 0;
#endif

/* LV2-specific part starts here. ********************************************/

static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{
  LV2Plugin* plugin =
    new LV2Plugin(LV2Plugin::numVoices(), (int)rate);
  // Scan host features for URID map.
  for (int i = 0; features[i]; i++) {
    if (!strcmp(features[i]->URI, LV2_URID_URI "#map")) {
      plugin->map = (LV2_URID_Map*)features[i]->data;
      plugin->midi_event =
	plugin->map->map(plugin->map->handle, MIDI_EVENT_URI);
    }
  }
  if (!plugin->map) {
    fprintf
      (stderr, "%s: host doesn't support urid:map, giving up\n",
       PLUGIN_URI);
    delete plugin;
    return 0;
  }
  return (LV2_Handle)plugin;
}

static void
cleanup(LV2_Handle instance)
{
  LV2Plugin* plugin = (LV2Plugin*)instance;
  delete plugin;
}

static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
  LV2Plugin* plugin = (LV2Plugin*)instance;
  int i = port, k = plugin->ui[0]->nports;
  int n = plugin->dsp[0]->getNumInputs(), m = plugin->dsp[0]->getNumOutputs();
  if (i < k)
    plugin->ports[i] = (float*)data;
  else {
    i -= k;
    if (i < n)
      plugin->inputs[i] = (float*)data;
    else {
      i -= n;
      if (i < m)
	plugin->outputs[i] = (float*)data;
      else if (i == m)
	plugin->event_port = (LV2_Atom_Sequence*)data;
      else if (i == m+1)
	plugin->poly = (float*)data;
      else if (i == m+2)
	plugin->tuning = (float*)data;
      else
	fprintf(stderr, "%s: bad port number %u\n", PLUGIN_URI, port);
    }
  }
}

static void
run(LV2_Handle instance, uint32_t n_samples)
{
  LV2Plugin* plugin = (LV2Plugin*)instance;
  // Process incoming MIDI events.
  if (plugin->event_port) {
    LV2_ATOM_SEQUENCE_FOREACH(plugin->event_port, ev) {
      if (ev->body.type == plugin->midi_event) {
	uint8_t *data = (uint8_t*)(ev+1);
#if 0
	// FIXME: Consider doing sample-accurate note onsets here. LV2 keeps
	// track of the exact onset in the frames and subframes fields
	// (http://lv2plug.in/ns/doc/html/structLV2__Atom__Event.html), but we
	// can't use that information at present, since our gate parameter is
	// a control variable which can only change at block boundaries. In
	// the future, the gate could be implemented as an audio signal to get
	// sample-accurate note onsets.
	uint32_t frames = ev->body.frames;
#endif
	if (data[0] == 0xf0)
	  plugin->process_sysex(data, ev->body.size);
	else
	  plugin->process_midi(data, ev->body.size);
      }
    }
  }
  // Process audio.
  plugin->process_audio(n_samples, plugin->inputs, plugin->outputs);
}

static void
activate(LV2_Handle instance)
{
  LV2Plugin* plugin = (LV2Plugin*)instance;
  plugin->resume();
}

static void
deactivate(LV2_Handle instance)
{
  LV2Plugin* plugin = (LV2Plugin*)instance;
  plugin->suspend();
}

const void*
extension_data(const char* uri)
{
  return NULL;
}

static const LV2_Descriptor descriptor = {
  PLUGIN_URI,
  instantiate,
  connect_port,
  activate,
  run,
  deactivate,
  cleanup,
  extension_data
};

extern "C"
LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
  switch (index) {
  case 0:
    return &descriptor;
  default:
    return NULL;
  }
}

//----------------------------------------------------------------------------
//  Dynamic manifest
//----------------------------------------------------------------------------

// NOTE: If your LV2 host doesn't offer this extension then you'll have to
// create a static ttl file with the descriptions of the ports. You can do
// this by compiling this code to a standalone executable. Running the
// executable then prints the manifest on stdout.

extern "C"
LV2_SYMBOL_EXPORT
int lv2_dyn_manifest_open(LV2_Dyn_Manifest_Handle *handle,
			  const LV2_Feature *const *features)
{
  LV2Plugin* plugin =
    new LV2Plugin(LV2Plugin::numVoices(), 48000);
  *handle = (LV2_Dyn_Manifest_Handle)plugin;
  return 0;
}

extern "C"
LV2_SYMBOL_EXPORT
int lv2_dyn_manifest_get_subjects(LV2_Dyn_Manifest_Handle handle,
				  FILE *fp)
{
  fprintf(fp, "@prefix lv2:  <http://lv2plug.in/ns/lv2core#> .\n\
<%s> a lv2:Plugin .\n", PLUGIN_URI);
  return 0;
}

#include <string>
#include <ctype.h>

static string mangle(const string &s)
{
  string t = s;
  size_t n = s.size();
  for (size_t i = 0; i < n; i++)
    if ((i == 0 && !isalpha(t[i]) && t[i] != '_') ||
	(!isalnum(t[i]) && t[i] != '_'))
      t[i] = '_';
  return t;
}

static unsigned steps(float min, float max, float step)
{
  if (step == 0.0) return 1;
  int n = (max-min)/step;
  if (n < 0) n = -n;
  if (n == 0) n = 1;
  return n;
}

#if FAUST_META
static bool is_xmlstring(const char *s)
{
  // This is just a basic sanity check. The string must not contain any
  // (unescaped) newlines, carriage returns or double quotes.
  return !strchr(s, '\n') && !strchr(s, '\r') && !strchr(s, '"');
}
#endif

extern "C"
LV2_SYMBOL_EXPORT
int lv2_dyn_manifest_get_data(LV2_Dyn_Manifest_Handle handle,
			      FILE *fp,
			      const char *uri)
{
  LV2Plugin* plugin = (LV2Plugin*)handle;
  int k = plugin->ui[0]->nports;
  int n = plugin->dsp[0]->getNumInputs(), m = plugin->dsp[0]->getNumOutputs();
  bool is_instr = plugin->maxvoices > 0, have_midi = is_instr;
  // Scan the global metadata for plugin name, description, license etc.
  const char *plugin_name = NULL, *plugin_author = NULL, *plugin_descr = NULL,
    *plugin_version = NULL, *plugin_license = NULL;
#if FAUST_META
  plugin_name = plugin->pluginName();
  plugin_descr = plugin->pluginDescription();
  plugin_author = plugin->pluginAuthor();
  plugin_version = plugin->pluginVersion();
  plugin_license = plugin->pluginLicense();
#endif
  if (!plugin_name || !*plugin_name) plugin_name = "vintage_mics";
  fprintf(fp, "@prefix doap:  <http://usefulinc.com/ns/doap#> .\n\
@prefix foaf:  <http://xmlns.com/foaf/0.1/> .\n\
@prefix lv2:   <http://lv2plug.in/ns/lv2core#> .\n\
@prefix ui:    <http://lv2plug.in/ns/extensions/ui#> .\n\
@prefix epp:   <http://lv2plug.in/ns/ext/port-props#> .\n\
@prefix atom:  <http://lv2plug.in/ns/ext/atom#> .\n\
@prefix rdf:   <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n\
@prefix rdfs:  <http://www.w3.org/2000/01/rdf-schema#> .\n\
@prefix units: <http://lv2plug.in/ns/extensions/units#> .\n\
<%s>\n\
       a lv2:Plugin%s ;\n\
       doap:name \"%s\" ;\n\
       lv2:binary <vintage_mics%s> ;\n\
       lv2:optionalFeature epp:supportsStrictBounds ;\n\
       lv2:optionalFeature lv2:hardRtCapable ;\n", PLUGIN_URI,
	  is_instr?", lv2:InstrumentPlugin":"",
	  plugin_name, DLLEXT);
  if (plugin_author && *plugin_author)
    fprintf(fp, "\
       doap:maintainer [ foaf:name \"%s\" ] ;\n", plugin_author);
  // doap:description just seems to be ignored by all LV2 hosts anyway, so we
  // rather use rdfs:comment now which works with Ardour at least.
  if (plugin_descr && *plugin_descr)
    fprintf(fp, "\
       rdfs:comment \"%s\" ;\n", plugin_descr);
  if (plugin_version && *plugin_version)
    fprintf(fp, "\
       doap:revision \"%s\" ;\n", plugin_version);
  if (plugin_license && *plugin_license)
    fprintf(fp, "\
       doap:license \"%s\" ;\n", plugin_license);
#if FAUST_UI
    fprintf(fp, "\
       ui:ui <%sui> ;\n", PLUGIN_URI);
#endif
  int idx = 0;
  // control ports
  for (int i = 0; i < k; i++, idx++) {
    int j = plugin->ctrls[i];
    assert(idx == plugin->ui[0]->elems[j].port);
    fprintf(fp, "%s [\n", idx==0?"    lv2:port":" ,");
    const char *label = plugin->ui[0]->elems[j].label;
    assert(label);
    string sym = mangle(plugin->ui[0]->elems[j].label);
    switch (plugin->ui[0]->elems[j].type) {
    // active controls (input ports)
    case UI_BUTTON: case UI_CHECK_BUTTON:
    fprintf(fp, "\
	a lv2:InputPort ;\n\
	a lv2:ControlPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"%s_%d\" ;\n\
	lv2:name \"%s\" ;\n\
        lv2:portProperty epp:hasStrictBounds ;\n\
        lv2:portProperty lv2:toggled ;\n\
	lv2:default 0.00000 ;\n\
	lv2:minimum 0.00000 ;\n\
	lv2:maximum 1.00000 ;\n", idx, sym.c_str(), idx, label);
      break;
    case UI_NUM_ENTRY: case UI_H_SLIDER: case UI_V_SLIDER:
    fprintf(fp, "\
	a lv2:InputPort ;\n\
	a lv2:ControlPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"%s_%d\" ;\n\
	lv2:name \"%s\" ;\n\
        lv2:portProperty epp:hasStrictBounds ;\n\
        epp:rangeSteps %u ;\n\
	lv2:default %g ;\n\
	lv2:minimum %g ;\n\
	lv2:maximum %g ;\n", idx, sym.c_str(), idx, label,
	    steps(plugin->ui[0]->elems[j].min,
		  plugin->ui[0]->elems[j].max,
		  plugin->ui[0]->elems[j].step),
	    plugin->ui[0]->elems[j].init,
	    plugin->ui[0]->elems[j].min,
	    plugin->ui[0]->elems[j].max);
      break;
    // passive controls (output ports)
    case UI_H_BARGRAPH: case UI_V_BARGRAPH:
    fprintf(fp, "\
	a lv2:OutputPort ;\n\
	a lv2:ControlPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"%s_%d\" ;\n\
	lv2:name \"%s\" ;\n\
	lv2:default %g ;\n\
	lv2:minimum %g ;\n\
	lv2:maximum %g ;\n", idx, sym.c_str(), idx, label,
	    plugin->ui[0]->elems[j].min,
	    plugin->ui[0]->elems[j].min,
	    plugin->ui[0]->elems[j].max);
      break;
    default:
      assert(0 && "this can't happen");
      break;
    }
    // Scan for Faust control metadata we understand and add corresponding
    // hints to the LV2 description of the port.
    std::map< int, list<strpair> >::iterator it =
      plugin->ui[0]->metadata.find(j);
    if (it != plugin->ui[0]->metadata.end()) {
      for (std::list<strpair>::iterator jt = it->second.begin();
	   jt != it->second.end(); jt++) {
	const char *key = jt->first, *val = jt->second;
#if FAUST_MIDICC
	unsigned num;
	if (!strcmp(key, "midi") && sscanf(val, "ctrl %u", &num) == 1)
	  have_midi = true;
#endif
	if (!strcmp(key, "unit"))
	  fprintf(fp, "\
	units:unit [\n\
            a            units:Unit ;\n\
            units:name   \"%s\" ;\n\
            units:symbol \"%s\" ;\n\
            units:render \"%%f %s\"\n\
	] ;\n", val, val, val);
	if (strcmp(key, "lv2")) continue;
	if (!strcmp(val, "integer"))
	  fprintf(fp, "\
	lv2:portProperty lv2:integer ;\n");
	else if (!strcmp(val, "reportsLatency"))
	  fprintf(fp, "\
	lv2:portProperty lv2:reportsLatency ;\n\
	lv2:designation lv2:latency ;\n");
	else if (!strcmp(val, "hidden") || !strcmp(val, "notOnGUI"))
	  fprintf(fp, "\
	lv2:portProperty epp:notOnGUI ;\n");
	else if (!strncmp(val, "scalepoint", 10) ||
		 !strncmp(val, "scalePoint", 10)) {
	  val += 10;
	  if (!isspace(*val)) continue;
	  char *label = (char*)malloc(strlen(val)+1);
	  float point;
	  int pos;
	  while (sscanf(val, "%s %g%n", label, &point, &pos) == 2) {
	    fprintf(fp, "\
	lv2:scalePoint [ rdfs:label \"%s\"; rdf:value %g ] ;\n",
		    label, point);
	    val += pos;
	  }
	  free(label);
	} else
	  fprintf(stderr, "%s: bad port property '%s:%s'\n", PLUGIN_URI,
		  key, val);
      }
    }
    fprintf(fp, "    ]");
  }
  // audio inputs
  for (int i = 0; i < n; i++, idx++)
    fprintf(fp, "%s [\n\
	a lv2:InputPort ;\n\
	a lv2:AudioPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"in%d\" ;\n\
	lv2:name \"in%d\" ;\n\
    ]", idx==0?"    lv2:port":" ,", idx, i, i);
  // audio outputs
  for (int i = 0; i < m; i++, idx++)
    fprintf(fp, "%s [\n\
	a lv2:OutputPort ;\n\
	a lv2:AudioPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"out%d\" ;\n\
	lv2:name \"out%d\" ;\n\
    ]", idx==0?"    lv2:port":" ,", idx, i, i);
  if (have_midi) {
    // midi input
    fprintf(fp, "%s [\n\
	a lv2:InputPort ;\n\
	a atom:AtomPort ;\n\
	atom:bufferType atom:Sequence ;\n\
	atom:supports <http://lv2plug.in/ns/ext/midi#MidiEvent> ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"midiin\" ;\n\
	lv2:name \"midiin\"\n\
    ]", idx==0?"    lv2:port":" ,", idx);
    idx++;
  }
  if (is_instr) {
    // polyphony control
    fprintf(fp, "%s [\n\
	a lv2:InputPort ;\n\
	a lv2:ControlPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"polyphony\" ;\n\
	lv2:name \"polyphony\" ;\n\
        lv2:portProperty epp:hasStrictBounds ;\n\
#       lv2:portProperty epp:expensive ;\n\
        lv2:portProperty lv2:integer ;\n\
        epp:rangeSteps %d ;\n\
	lv2:default %d ;\n\
	lv2:minimum 1 ;\n\
	lv2:maximum %d ;\n\
    ]", idx==0?"    lv2:port":" ,", idx, plugin->maxvoices-1,
      plugin->maxvoices>1?plugin->maxvoices/2:1,
      plugin->maxvoices);
    idx++;
#if FAUST_MTS
    if (plugin->n_tunings > 0) {
      // tuning control
      fprintf(fp, "%s [\n\
	a lv2:InputPort ;\n\
	a lv2:ControlPort ;\n\
	lv2:index %d ;\n\
	lv2:symbol \"tuning\" ;\n\
	lv2:name \"tuning\" ;\n\
        lv2:portProperty epp:hasStrictBounds ;\n\
        lv2:portProperty lv2:integer ;\n\
        epp:rangeSteps %d ;\n\
	lv2:default 0 ;\n\
	lv2:minimum 0 ;\n\
	lv2:maximum %d ;\n",
	idx==0?"    lv2:port":" ,", idx, plugin->n_tunings, plugin->n_tunings);
      for (int i = 0; i <= plugin->n_tunings; i++)
	fprintf(fp, "\
	lv2:scalePoint [ rdfs:label \"%s\"; rdf:value %d ] ;\n",
		(i>0)?plugin->mts->tuning[i-1].name:"default", i);
      fprintf(fp, "    ]");
      idx++;
    }
#endif
  }
  fprintf(fp, "\n.\n");
  return 0;
}

extern "C"
LV2_SYMBOL_EXPORT
void lv2_dyn_manifest_close(LV2_Dyn_Manifest_Handle handle)
{
  LV2Plugin* plugin = (LV2Plugin*)handle;
  delete plugin;
}

int main()
{
  LV2_Dyn_Manifest_Handle handle;
  LV2_Feature **features = { NULL };
  int res = lv2_dyn_manifest_open(&handle, features);
  if (res) return res;
  res = lv2_dyn_manifest_get_data(handle, stdout, PLUGIN_URI);
  return res;
}

#endif
