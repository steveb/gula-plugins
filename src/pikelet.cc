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
	fConst2 = (1.3886006410869099e-25 * fConst0);
	fConst3 = (((((((-4.5910658504056396e-22 - fConst2) * fConst0) + -1.52052548124057e-19) * fConst0) + 4.7970706996158301e-17) * fConst0) + 1.6626552882205201e-14);
	fConst4 = (3.1529271546140299e-23 * fConst0);
	fConst5 = (((((((-9.9974973662943805e-20 - fConst4) * fConst0) + -2.6971013443348599e-17) * fConst0) + 4.77085087451104e-15) * fConst0) + 5.25723667291112e-13);
	fConst6 = (1.3872864094060801e-23 * fConst0);
	fConst7 = (((((-3.3903711083245097e-20 - fConst6) * fConst0) + -7.1378471280310796e-18) * fConst0) + 3.2898608543453502e-16);
	fConst8 = (1.3872870399897199e-23 * fConst0);
	fConst9 = (((((fConst8 + 2.5304835973914901e-20) * fConst0) + 4.9383709193679401e-18) * fConst0) + -2.26178004416799e-16);
	fConst10 = (6.1076819771025801e-26 * fConst0);
	fConst11 = (((((((-1.5758419659865399e-22 - fConst10) * fConst0) + -4.2716797693033201e-20) * fConst0) + 8.5857683500044207e-18) * fConst0) + 9.8695825630360397e-16);
	fConst12 = (6.1085675687746404e-26 * fConst0);
	fConst13 = (((((((fConst12 + 1.19737331918088e-22) * fConst0) + 3.0172198059012197e-20) * fConst0) + -5.9339160232470302e-18) * fConst0) + -6.7853401325039602e-16);
	fConst14 = (2.7772012821738198e-25 * fConst0);
	fConst15 = (((((((fConst14 + 3.0607105669370901e-22) * fConst0) + -3.0410509624811401e-19) * fConst0) + -9.5941413992316503e-17) * fConst0) + 1.10843685881368e-14);
	fConst16 = (6.3058543092280598e-23 * fConst0);
	fConst17 = (((((((fConst16 + 6.6649982441962597e-20) * fConst0) + -5.39420268866971e-17) * fConst0) + -9.54170174902208e-15) * fConst0) + 3.5048244486074098e-13);
	fConst18 = (2.7745728188121602e-23 * fConst0);
	fConst19 = (((((fConst18 + 2.2602474055496699e-20) * fConst0) + -1.4275694256062199e-17) * fConst0) + -6.5797217086906895e-16);
	fConst20 = (2.7745740799794498e-23 * fConst0);
	fConst21 = (((((-1.68698906492766e-20 - fConst20) * fConst0) + 9.8767418387358694e-18) * fConst0) + 4.5235600883359702e-16);
	fConst22 = (1.2215363954205199e-25 * fConst0);
	fConst23 = (((((((fConst22 + 1.05056131065769e-22) * fConst0) + -8.5433595386066499e-20) * fConst0) + -1.7171536700008801e-17) * fConst0) + 6.5797217086906895e-16);
	fConst24 = (1.2217135137549299e-25 * fConst0);
	fConst25 = (((((((-7.9824887945391805e-23 - fConst24) * fConst0) + 6.0344396118024298e-20) * fConst0) + 1.18678320464941e-17) * fConst0) + -4.5235600883359702e-16);
	fConst26 = (((((((3.0607105669370901e-22 - fConst14) * fConst0) + 3.0410509624811401e-19) * fConst0) + -9.5941413992316503e-17) * fConst0) + -1.10843685881368e-14);
	fConst27 = (((((((6.6649982441962597e-20 - fConst16) * fConst0) + 5.39420268866971e-17) * fConst0) + -9.54170174902208e-15) * fConst0) + -3.5048244486074098e-13);
	fConst28 = (((((2.2602474055496699e-20 - fConst18) * fConst0) + 1.4275694256062199e-17) * fConst0) + -6.5797217086906895e-16);
	fConst29 = (((((fConst20 + -1.68698906492766e-20) * fConst0) + -9.8767418387358694e-18) * fConst0) + 4.5235600883359702e-16);
	fConst30 = (((((((1.05056131065769e-22 - fConst22) * fConst0) + 8.5433595386066499e-20) * fConst0) + -1.7171536700008801e-17) * fConst0) + -6.5797217086906895e-16);
	fConst31 = (((((((fConst24 + -7.9824887945391805e-23) * fConst0) + -6.0344396118024298e-20) * fConst0) + 1.18678320464941e-17) * fConst0) + 4.5235600883359702e-16);
	fConst32 = (((((((fConst2 + -4.5910658504056396e-22) * fConst0) + 1.52052548124057e-19) * fConst0) + 4.7970706996158301e-17) * fConst0) + -1.6626552882205201e-14);
	fConst33 = (((((((fConst4 + -9.9974973662943805e-20) * fConst0) + 2.6971013443348599e-17) * fConst0) + 4.77085087451104e-15) * fConst0) + -5.25723667291112e-13);
	fConst34 = (((((fConst6 + -3.3903711083245097e-20) * fConst0) + 7.1378471280310796e-18) * fConst0) + 3.2898608543453502e-16);
	fConst35 = (((((2.5304835973914901e-20 - fConst8) * fConst0) + -4.9383709193679401e-18) * fConst0) + -2.26178004416799e-16);
	fConst36 = (((((((fConst10 + -1.5758419659865399e-22) * fConst0) + 4.2716797693033201e-20) * fConst0) + 8.5857683500044207e-18) * fConst0) + -9.8695825630360397e-16);
	fConst37 = (((((((1.19737331918088e-22 - fConst12) * fConst0) + -3.0172198059012197e-20) * fConst0) + -5.9339160232470302e-18) * fConst0) + 6.7853401325039602e-16);
	fConst38 = (2.7772012821738202e-26 * fConst0);
	fConst39 = (((((((1.53035528346855e-22 - fConst38) * fConst0) + -1.52052548124057e-19) * fConst0) + 4.7970706996158301e-17) * fConst0) + -5.5421842940683999e-15);
	fConst40 = (6.3058543092280698e-24 * fConst0);
	fConst41 = (((((((3.3324991220981299e-20 - fConst40) * fConst0) + -2.6971013443348599e-17) * fConst0) + 4.77085087451104e-15) * fConst0) + -1.7524122243037099e-13);
	fConst42 = (2.7745728188121602e-24 * fConst0);
	fConst43 = (((((1.13012370277484e-20 - fConst42) * fConst0) + -7.1378471280310796e-18) * fConst0) + 3.2898608543453502e-16);
	fConst44 = (2.7745740799794501e-24 * fConst0);
	fConst45 = (((((fConst44 + -8.4349453246382804e-21) * fConst0) + 4.9383709193679401e-18) * fConst0) + -2.26178004416799e-16);
	fConst46 = (1.22153639542052e-26 * fConst0);
	fConst47 = (((((((5.2528065532884499e-23 - fConst46) * fConst0) + -4.2716797693033201e-20) * fConst0) + 8.5857683500044207e-18) * fConst0) + -3.2898608543453502e-16);
	fConst48 = (1.2217135137549299e-26 * fConst0);
	fConst49 = (((((((fConst48 + -3.9912443972695903e-23) * fConst0) + 3.0172198059012197e-20) * fConst0) + -5.9339160232470302e-18) * fConst0) + 2.26178004416799e-16);
	fConst50 = (((((((fConst38 + 1.53035528346855e-22) * fConst0) + 1.52052548124057e-19) * fConst0) + 4.7970706996158301e-17) * fConst0) + 5.5421842940683999e-15);
	fConst51 = (((((((fConst40 + 3.3324991220981299e-20) * fConst0) + 2.6971013443348599e-17) * fConst0) + 4.77085087451104e-15) * fConst0) + 1.7524122243037099e-13);
	fConst52 = (((((fConst42 + 1.13012370277484e-20) * fConst0) + 7.1378471280310796e-18) * fConst0) + 3.2898608543453502e-16);
	fConst53 = (((((-8.4349453246382804e-21 - fConst44) * fConst0) + -4.9383709193679401e-18) * fConst0) + -2.26178004416799e-16);
	fConst54 = (((((((fConst46 + 5.2528065532884499e-23) * fConst0) + 4.2716797693033201e-20) * fConst0) + 8.5857683500044207e-18) * fConst0) + 3.2898608543453502e-16);
	fConst55 = (((((((-3.9912443972695903e-23 - fConst48) * fConst0) + -3.0172198059012197e-20) * fConst0) + -5.9339160232470302e-18) * fConst0) + -2.26178004416799e-16);
	fConst56 = (8.8559167206375797e-24 * fConst0);
	fConst57 = (((((fConst56 + 4.4783619323988098e-20) * fConst0) + 2.7596038577121101e-17) * fConst0) + 1.96269972852042e-17);
	fConst58 = (6.30583645730389e-24 * fConst0);
	fConst59 = (((fConst58 + 3.18835897803552e-20) * fConst0) + 1.96269972852042e-17);
	fConst60 = (((1.2336969722128299e-20 - fConst58) * fConst0) + -2.7280199994059999e-32);
	fConst61 = (((((2.01860237400742e-20 - fConst56) * fConst0) + 2.0684985900768099e-18) * fConst0) + -2.7280199994059999e-32);
	fConst62 = (4.4279583603187902e-23 * fConst0);
	fConst63 = (((((-1.34350857971964e-19 - fConst62) * fConst0) + -2.7596038577121101e-17) * fConst0) + 1.96269972852042e-17);
	fConst64 = (3.15291822865194e-23 * fConst0);
	fConst65 = (((-9.5650769341065502e-20 - fConst64) * fConst0) + -1.96269972852042e-17);
	fConst66 = (((fConst64 + -3.7010909166384903e-20) * fConst0) + 2.7280199994059999e-32);
	fConst67 = (((((fConst62 + -6.0558071220222497e-20) * fConst0) + -2.0684985900768099e-18) * fConst0) + -2.7280199994059999e-32);
	fConst68 = (8.8559167206375803e-23 * fConst0);
	fConst69 = (((((fConst68 + 8.9567238647976195e-20) * fConst0) + -5.5192077154242301e-17) * fConst0) + -3.9253994570408401e-17);
	fConst70 = (6.3058364573038906e-23 * fConst0);
	fConst71 = (((fConst70 + 6.3767179560710303e-20) * fConst0) + -3.9253994570408401e-17);
	fConst72 = (((2.4673939444256599e-20 - fConst70) * fConst0) + 5.4560399988119899e-32);
	fConst73 = (((((4.0372047480148399e-20 - fConst68) * fConst0) + -4.1369971801536297e-18) * fConst0) + 5.4560399988119899e-32);
	fConst74 = (((((8.9567238647976195e-20 - fConst68) * fConst0) + 5.5192077154242301e-17) * fConst0) + -3.9253994570408401e-17);
	fConst75 = (((6.3767179560710303e-20 - fConst70) * fConst0) + 3.9253994570408401e-17);
	fConst76 = (((fConst70 + 2.4673939444256599e-20) * fConst0) + -5.4560399988119899e-32);
	fConst77 = (((((fConst68 + 4.0372047480148399e-20) * fConst0) + 4.1369971801536297e-18) * fConst0) + 5.4560399988119899e-32);
	fConst78 = (((((fConst62 + -1.34350857971964e-19) * fConst0) + 2.7596038577121101e-17) * fConst0) + 1.96269972852042e-17);
	fConst79 = (((fConst64 + -9.5650769341065502e-20) * fConst0) + 1.96269972852042e-17);
	fConst80 = (((-3.7010909166384903e-20 - fConst64) * fConst0) + -2.7280199994059999e-32);
	fConst81 = (((((-6.0558071220222497e-20 - fConst62) * fConst0) + 2.0684985900768099e-18) * fConst0) + -2.7280199994059999e-32);
	fConst82 = (((((4.4783619323988098e-20 - fConst56) * fConst0) + -2.7596038577121101e-17) * fConst0) + 1.96269972852042e-17);
	fConst83 = (((3.18835897803552e-20 - fConst58) * fConst0) + -1.96269972852042e-17);
	fConst84 = (((fConst58 + 1.2336969722128299e-20) * fConst0) + 2.7280199994059999e-32);
	fConst85 = (((((fConst56 + 2.01860237400742e-20) * fConst0) + -2.0684985900768099e-18) * fConst0) + -2.7280199994059999e-32);
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
		double fTemp0 = ((fConst0 * (fConst50 + ((fRec2[0] * (fConst51 + (fConst0 * (fRec3[0] * (fConst52 + (fConst53 * fRec3[0])))))) + (fRec3[0] * (fConst54 + (fConst55 * fRec3[0])))))) + 1.7524122243037099e-13);
		fRec1[0] = (double(input0[i]) - ((((((fRec1[1] * ((fConst0 * (fConst3 + ((fRec2[0] * (fConst5 + (fConst0 * (fRec3[0] * (fConst7 + (fConst9 * fRec3[0])))))) + (fRec3[0] * (fConst11 + (fConst13 * fRec3[0])))))) + 8.7620611215185303e-13)) + (fRec1[2] * ((fConst0 * (fConst15 + ((fRec2[0] * (fConst17 + (fConst0 * (fRec3[0] * (fConst19 + (fConst21 * fRec3[0])))))) + (fRec3[0] * (fConst23 + (fConst25 * fRec3[0])))))) + 1.7524122243037101e-12))) + (fRec1[3] * ((fConst0 * (fConst26 + ((fRec2[0] * (fConst27 + (fConst0 * (fRec3[0] * (fConst28 + (fConst29 * fRec3[0])))))) + (fRec3[0] * (fConst30 + (fConst31 * fRec3[0])))))) + 1.7524122243037101e-12))) + (fRec1[4] * ((fConst0 * (fConst32 + ((fRec2[0] * (fConst33 + (fConst0 * (fRec3[0] * (fConst34 + (fConst35 * fRec3[0])))))) + (fRec3[0] * (fConst36 + (fConst37 * fRec3[0])))))) + 8.7620611215185303e-13))) + (fRec1[5] * ((fConst0 * (fConst39 + ((fRec2[0] * (fConst41 + (fConst0 * (fRec3[0] * (fConst43 + (fConst45 * fRec3[0])))))) + (fRec3[0] * (fConst47 + (fConst49 * fRec3[0])))))) + 1.7524122243037099e-13))) / fTemp0));
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
