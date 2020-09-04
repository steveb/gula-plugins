// generated from file '../dkbuild/pikelet//pikelet.dsp' by dsp2cc:
// Code generated with Faust 2.14.4 (https://faust.grame.fr)

#include "pikelet_table.h"

namespace pikelet {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double fConst0;
	double fConst1;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec2[2];
	double fConst4;
	double fConst5;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec3[2];
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fRec1[6];
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;
	double fConst69;
	double fConst70;
	double fConst71;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "pikelet";
	name = N_("Pikelet");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec0[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec3[l2] = 0.0;
	for (int l3 = 0; (l3 < 6); l3 = (l3 + 1)) fRec1[l3] = 0.0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = (1.25816043993714e-25 * fConst0);
	fConst3 = (((((((-8.1877851641899402e-22 - fConst2) * fConst0) + -7.8205110155870598e-19) * fConst0) + 3.1734936528139702e-16) * fConst0) + 1.2231882925638e-13);
	fConst4 = (2.8392292670090203e-23 * fConst0);
	fConst5 = (((((((-1.8168019146172599e-19 - fConst4) * fConst0) + -1.6382556517958899e-16) * fConst0) + 3.48672319805691e-14) * fConst0) + 4.0239966110736602e-12);
	fConst6 = (1.24925903011927e-23 * fConst0);
	fConst7 = (((((-7.0857463184707906e-20 - fConst6) * fConst0) + -5.15372435814672e-17) * fConst0) + 2.5181266078436302e-15);
	fConst8 = (1.24925978723595e-23 * fConst0);
	fConst9 = (((((fConst8 + 6.3114155646899502e-20) * fConst0) + 3.56699115797949e-17) * fConst0) + -1.7312127642308e-15);
	fConst10 = (5.5322030779104703e-26 * fConst0);
	fConst11 = (((((((-3.2007048840865899e-22 - fConst10) * fConst0) + -2.5050197841723399e-19) * fConst0) + 6.2622288721496596e-17) * fConst0) + 7.5543798235309007e-15);
	fConst12 = (5.5337206425879104e-26 * fConst0);
	fConst13 = (((((((fConst12 + 2.8584724160512101e-22) * fConst0) + 1.78097865679046e-19) * fConst0) + -4.3292325964058103e-17) * fConst0) + -5.1936382926924099e-15);
	fConst14 = (2.5163208798742799e-25 * fConst0);
	fConst15 = (((((((fConst14 + 5.45852344279329e-22) * fConst0) + -1.56410220311741e-18) * fConst0) + -6.3469873056279405e-16) * fConst0) + 8.1545886170919904e-14);
	fConst16 = (5.6784585340180499e-23 * fConst0);
	fConst17 = (((((((fConst16 + 1.2112012764115099e-19) * fConst0) + -3.2765113035917799e-16) * fConst0) + -6.9734463961138302e-14) * fConst0) + 2.6826644073824399e-12);
	fConst18 = (2.49851806023853e-23 * fConst0);
	fConst19 = (((((fConst18 + 4.7238308789805299e-20) * fConst0) + -1.0307448716293401e-16) * fConst0) + -5.0362532156872698e-15);
	fConst20 = (2.4985195744719e-23 * fConst0);
	fConst21 = (((((-4.2076103764599702e-20 - fConst20) * fConst0) + 7.1339823159589701e-17) * fConst0) + 3.4624255284615999e-15);
	fConst22 = (1.1064406155820899e-25 * fConst0);
	fConst23 = (((((((fConst22 + 2.1338032560577199e-22) * fConst0) + -5.0100395683446702e-19) * fConst0) + -1.25244577442993e-16) * fConst0) + 5.0362532156872698e-15);
	fConst24 = (1.10674412851758e-25 * fConst0);
	fConst25 = (((((((-1.9056482773674701e-22 - fConst24) * fConst0) + 3.56195731358092e-19) * fConst0) + 8.6584651928116095e-17) * fConst0) + -3.4624255284615999e-15);
	fConst26 = (((((((5.45852344279329e-22 - fConst14) * fConst0) + 1.56410220311741e-18) * fConst0) + -6.3469873056279405e-16) * fConst0) + -8.1545886170919904e-14);
	fConst27 = (((((((1.2112012764115099e-19 - fConst16) * fConst0) + 3.2765113035917799e-16) * fConst0) + -6.9734463961138302e-14) * fConst0) + -2.6826644073824399e-12);
	fConst28 = (((((4.7238308789805299e-20 - fConst18) * fConst0) + 1.0307448716293401e-16) * fConst0) + -5.0362532156872698e-15);
	fConst29 = (((((fConst20 + -4.2076103764599702e-20) * fConst0) + -7.1339823159589701e-17) * fConst0) + 3.4624255284615999e-15);
	fConst30 = (((((((2.1338032560577199e-22 - fConst22) * fConst0) + 5.0100395683446702e-19) * fConst0) + -1.25244577442993e-16) * fConst0) + -5.0362532156872698e-15);
	fConst31 = (((((((fConst24 + -1.9056482773674701e-22) * fConst0) + -3.56195731358092e-19) * fConst0) + 8.6584651928116095e-17) * fConst0) + 3.4624255284615999e-15);
	fConst32 = (((((((fConst2 + -8.1877851641899402e-22) * fConst0) + 7.8205110155870598e-19) * fConst0) + 3.1734936528139702e-16) * fConst0) + -1.2231882925638e-13);
	fConst33 = (((((((fConst4 + -1.8168019146172599e-19) * fConst0) + 1.6382556517958899e-16) * fConst0) + 3.48672319805691e-14) * fConst0) + -4.0239966110736602e-12);
	fConst34 = (((((fConst6 + -7.0857463184707906e-20) * fConst0) + 5.15372435814672e-17) * fConst0) + 2.5181266078436302e-15);
	fConst35 = (((((6.3114155646899502e-20 - fConst8) * fConst0) + -3.56699115797949e-17) * fConst0) + -1.7312127642308e-15);
	fConst36 = (((((((fConst10 + -3.2007048840865899e-22) * fConst0) + 2.5050197841723399e-19) * fConst0) + 6.2622288721496596e-17) * fConst0) + -7.5543798235309007e-15);
	fConst37 = (((((((2.8584724160512101e-22 - fConst12) * fConst0) + -1.78097865679046e-19) * fConst0) + -4.3292325964058103e-17) * fConst0) + 5.1936382926924099e-15);
	fConst38 = (2.5163208798742799e-26 * fConst0);
	fConst39 = (((((((2.7292617213966502e-22 - fConst38) * fConst0) + -7.8205110155870598e-19) * fConst0) + 3.1734936528139702e-16) * fConst0) + -4.0772943085459902e-14);
	fConst40 = (5.6784585340180502e-24 * fConst0);
	fConst41 = (((((((6.0560063820575398e-20 - fConst40) * fConst0) + -1.6382556517958899e-16) * fConst0) + 3.48672319805691e-14) * fConst0) + -1.3413322036912199e-12);
	fConst42 = (2.4985180602385299e-24 * fConst0);
	fConst43 = (((((2.3619154394902601e-20 - fConst42) * fConst0) + -5.15372435814672e-17) * fConst0) + 2.5181266078436302e-15);
	fConst44 = (2.4985195744719e-24 * fConst0);
	fConst45 = (((((fConst44 + -2.10380518822998e-20) * fConst0) + 3.56699115797949e-17) * fConst0) + -1.7312127642308e-15);
	fConst46 = (1.10644061558209e-26 * fConst0);
	fConst47 = (((((((1.0669016280288599e-22 - fConst46) * fConst0) + -2.5050197841723399e-19) * fConst0) + 6.2622288721496596e-17) * fConst0) + -2.5181266078436302e-15);
	fConst48 = (1.10674412851758e-26 * fConst0);
	fConst49 = (((((((fConst48 + -9.5282413868373597e-23) * fConst0) + 1.78097865679046e-19) * fConst0) + -4.3292325964058103e-17) * fConst0) + 1.7312127642308e-15);
	fConst50 = (((((((fConst38 + 2.7292617213966502e-22) * fConst0) + 7.8205110155870598e-19) * fConst0) + 3.1734936528139702e-16) * fConst0) + 4.0772943085459902e-14);
	fConst51 = (((((((fConst40 + 6.0560063820575398e-20) * fConst0) + 1.6382556517958899e-16) * fConst0) + 3.48672319805691e-14) * fConst0) + 1.3413322036912199e-12);
	fConst52 = (((((fConst42 + 2.3619154394902601e-20) * fConst0) + 5.15372435814672e-17) * fConst0) + 2.5181266078436302e-15);
	fConst53 = (((((-2.10380518822998e-20 - fConst44) * fConst0) + -3.56699115797949e-17) * fConst0) + -1.7312127642308e-15);
	fConst54 = (((((((fConst46 + 1.0669016280288599e-22) * fConst0) + 2.5050197841723399e-19) * fConst0) + 6.2622288721496596e-17) * fConst0) + 2.5181266078436302e-15);
	fConst55 = (((((((-9.5282413868373597e-23 - fConst48) * fConst0) + -1.78097865679046e-19) * fConst0) + -4.3292325964058103e-17) * fConst0) + -1.7312127642308e-15);
	fConst56 = (1.13817254203206e-23 * fConst0);
	fConst57 = (((((fConst56 + 1.18789962514037e-19) * fConst0) + 3.0117828241063001e-16) * fConst0) + 1.5022900650790401e-16);
	fConst58 = (5.6783702955102003e-24 * fConst0);
	fConst59 = (((fConst58 + 5.9261766186260899e-20) * fConst0) + 1.5022900650790401e-16);
	fConst60 = (((9.4429661233539798e-20 - fConst58) * fConst0) + 4.8377510007594703e-33);
	fConst61 = (((((1.9185021201326199e-19 - fConst56) * fConst0) + 1.58327065334902e-17) * fConst0) + 4.8377510007594703e-33);
	fConst62 = (5.6908627101603203e-23 * fConst0);
	fConst63 = (((((-3.56369887542111e-19 - fConst62) * fConst0) + -3.0117828241063001e-16) * fConst0) + 1.5022900650790401e-16);
	fConst64 = (2.8391851477550999e-23 * fConst0);
	fConst65 = (((-1.77785298558783e-19 - fConst64) * fConst0) + -1.5022900650790401e-16);
	fConst66 = (((fConst64 + -2.8328898370062001e-19) * fConst0) + -4.8377510007594703e-33);
	fConst67 = (((((fConst62 + -5.7555063603978604e-19) * fConst0) + -1.58327065334902e-17) * fConst0) + 4.8377510007594703e-33);
	fConst68 = (1.1381725420320601e-22 * fConst0);
	fConst69 = (((((fConst68 + 2.37579925028074e-19) * fConst0) + -6.0235656482126001e-16) * fConst0) + -3.00458013015809e-16);
	fConst70 = (5.6783702955101999e-23 * fConst0);
	fConst71 = (((fConst70 + 1.1852353237252199e-19) * fConst0) + -3.00458013015809e-16);
	fConst72 = (((1.8885932246708e-19 - fConst70) * fConst0) + -9.6755020015189406e-33);
	fConst73 = (((((3.8370042402652398e-19 - fConst68) * fConst0) + -3.1665413066980401e-17) * fConst0) + -9.6755020015189406e-33);
	fConst74 = (((((2.37579925028074e-19 - fConst68) * fConst0) + 6.0235656482126001e-16) * fConst0) + -3.00458013015809e-16);
	fConst75 = (((1.1852353237252199e-19 - fConst70) * fConst0) + 3.00458013015809e-16);
	fConst76 = (((fConst70 + 1.8885932246708e-19) * fConst0) + 9.6755020015189406e-33);
	fConst77 = (((((fConst68 + 3.8370042402652398e-19) * fConst0) + 3.1665413066980401e-17) * fConst0) + -9.6755020015189406e-33);
	fConst78 = (((((fConst62 + -3.56369887542111e-19) * fConst0) + 3.0117828241063001e-16) * fConst0) + 1.5022900650790401e-16);
	fConst79 = (((fConst64 + -1.77785298558783e-19) * fConst0) + 1.5022900650790401e-16);
	fConst80 = (((-2.8328898370062001e-19 - fConst64) * fConst0) + 4.8377510007594703e-33);
	fConst81 = (((((-5.7555063603978604e-19 - fConst62) * fConst0) + 1.58327065334902e-17) * fConst0) + 4.8377510007594703e-33);
	fConst82 = (((((1.18789962514037e-19 - fConst56) * fConst0) + -3.0117828241063001e-16) * fConst0) + 1.5022900650790401e-16);
	fConst83 = (((5.9261766186260899e-20 - fConst58) * fConst0) + -1.5022900650790401e-16);
	fConst84 = (((fConst58 + 9.4429661233539798e-20) * fConst0) + -4.8377510007594703e-33);
	fConst85 = (((((fConst56 + 1.9185021201326199e-19) * fConst0) + -1.58327065334902e-17) * fConst0) + 4.8377510007594703e-33);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
	double fSlow0 = (0.004073836948085289 * (std::exp(double(fVslider0)) + -1.0));
	double fSlow1 = (0.00036676987543879196 * (std::exp((3.0 * (1.0 - double(fVslider1)))) + -1.0));
	double fSlow2 = (0.0070000000000000062 * double(fVslider2));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec0[0] = (fSlow0 + (0.99299999999999999 * fRec0[1]));
		fRec2[0] = (fSlow1 + (0.99299999999999999 * fRec2[1]));
		fRec3[0] = (fSlow2 + (0.99299999999999999 * fRec3[1]));
		double fTemp0 = ((fConst0 * (fConst50 + ((fRec2[0] * (fConst51 + (fConst0 * (fRec3[0] * (fConst52 + (fConst53 * fRec3[0])))))) + (fRec3[0] * (fConst54 + (fConst55 * fRec3[0])))))) + 1.3413322036912199e-12);
		fRec1[0] = (double(input0[i]) - ((((((fRec1[1] * ((fConst0 * (fConst3 + ((fRec2[0] * (fConst5 + (fConst0 * (fRec3[0] * (fConst7 + (fConst9 * fRec3[0])))))) + (fRec3[0] * (fConst11 + (fConst13 * fRec3[0])))))) + 6.7066610184560904e-12)) + (fRec1[2] * ((fConst0 * (fConst15 + ((fRec2[0] * (fConst17 + (fConst0 * (fRec3[0] * (fConst19 + (fConst21 * fRec3[0])))))) + (fRec3[0] * (fConst23 + (fConst25 * fRec3[0])))))) + 1.34133220369122e-11))) + (fRec1[3] * ((fConst0 * (fConst26 + ((fRec2[0] * (fConst27 + (fConst0 * (fRec3[0] * (fConst28 + (fConst29 * fRec3[0])))))) + (fRec3[0] * (fConst30 + (fConst31 * fRec3[0])))))) + 1.34133220369122e-11))) + (fRec1[4] * ((fConst0 * (fConst32 + ((fRec2[0] * (fConst33 + (fConst0 * (fRec3[0] * (fConst34 + (fConst35 * fRec3[0])))))) + (fRec3[0] * (fConst36 + (fConst37 * fRec3[0])))))) + 6.7066610184560904e-12))) + (fRec1[5] * ((fConst0 * (fConst39 + ((fRec2[0] * (fConst41 + (fConst0 * (fRec3[0] * (fConst43 + (fConst45 * fRec3[0])))))) + (fRec3[0] * (fConst47 + (fConst49 * fRec3[0])))))) + 1.3413322036912199e-12))) / fTemp0));
		output0[i] = FAUSTFLOAT(double(pikeletclip(double((fConst1 * ((fRec0[0] * ((((((fRec1[0] * (fConst57 + ((fConst0 * (fRec2[0] * (fConst59 + (fConst60 * fRec3[0])))) + (fConst61 * fRec3[0])))) + (fRec1[1] * (fConst63 + ((fConst0 * (fRec2[0] * (fConst65 + (fConst66 * fRec3[0])))) + (fConst67 * fRec3[0]))))) + (fRec1[2] * (fConst69 + ((fConst0 * (fRec2[0] * (fConst71 + (fConst72 * fRec3[0])))) + (fConst73 * fRec3[0]))))) + (fRec1[3] * (fConst74 + ((fConst0 * (fRec2[0] * (fConst75 + (fConst76 * fRec3[0])))) + (fConst77 * fRec3[0]))))) + (fRec1[4] * (fConst78 + ((fConst0 * (fRec2[0] * (fConst79 + (fConst80 * fRec3[0])))) + (fConst81 * fRec3[0]))))) + (fRec1[5] * (fConst82 + ((fConst0 * (fRec2[0] * (fConst83 + (fConst84 * fRec3[0])))) + (fConst85 * fRec3[0])))))) / fTemp0))))));
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		for (int j0 = 5; (j0 > 0); j0 = (j0 - 1)) {
			fRec1[j0] = fRec1[(j0 - 1)];
		}
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DRIVE: 
		fVslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case PRESENCE: 
		fVslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fVslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	default:
		break;
	}
}

void Dsp::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->connect(port, data);
}


PluginLV2 *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginLV2 *p)
{
	delete static_cast<Dsp*>(p);
}

/*
typedef enum
{
   DRIVE, 
   PRESENCE, 
   VOLUME, 
} PortIndex;
*/

} // end namespace pikelet
