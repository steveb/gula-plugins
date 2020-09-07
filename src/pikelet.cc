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
	fConst2 = (1.3754693876033901e-25 * fConst0);
	fConst3 = (((((((-4.9605280315055998e-22 - fConst2) * fConst0) + -2.1668572793354299e-19) * fConst0) + 7.5605836238962106e-17) * fConst0) + 2.74693428680159e-14);
	fConst4 = (3.1207409169147397e-23 * fConst0);
	fConst5 = (((((((-1.08356865900632e-19 - fConst4) * fConst0) + -4.1010697115448499e-17) * fConst0) + 7.8583908501843601e-15) * fConst0) + 8.8460597961498503e-13);
	fConst6 = (1.37312448052648e-23 * fConst0);
	fConst7 = (((((-3.7694700301388401e-20 - fConst6) * fConst0) + -1.16927112054797e-17) * fConst0) + 5.5356659114295903e-16);
	fConst8 = (1.3731251046723899e-23 * fConst0);
	fConst9 = (((((fConst8 + 2.91836075459373e-20) * fConst0) + 8.0910708403960997e-18) * fConst0) + -3.80577150341025e-16);
	fConst10 = (6.0490127726207098e-26 * fConst0);
	fConst11 = (((((((-1.7426241545897101e-22 - fConst10) * fConst0) + -6.4033013535743402e-20) * fConst0) + 1.4129276073290401e-17) * fConst0) + 1.66069977342888e-15);
	fConst12 = (6.0502638106675195e-26 * fConst0);
	fConst13 = (((((((fConst12 + 1.3678737287183e-22) * fConst0) + 4.5347629508202398e-20) * fConst0) + -9.7664475707901002e-18) * fConst0) + -1.1417314510230801e-15);
	fConst14 = (2.7509387752067898e-25 * fConst0);
	fConst15 = (((((((fConst14 + 3.3070186876704002e-22) * fConst0) + -4.3337145586708598e-19) * fConst0) + -1.5121167247792399e-16) * fConst0) + 1.8312895245343901e-14);
	fConst16 = (6.2414818338294795e-23 * fConst0);
	fConst17 = (((((((fConst16 + 7.2237910600421603e-20) * fConst0) + -8.2021394230896999e-17) * fConst0) + -1.5716781700368701e-14) * fConst0) + 5.8973731974332299e-13);
	fConst18 = (2.7462489610529701e-23 * fConst0);
	fConst19 = (((((fConst18 + 2.51298002009256e-20) * fConst0) + -2.33854224109594e-17) * fConst0) + -1.10713318228592e-15);
	fConst20 = (2.7462502093447697e-23 * fConst0);
	fConst21 = (((((-1.94557383639582e-20 - fConst20) * fConst0) + 1.6182141680792199e-17) * fConst0) + 7.6115430068204999e-16);
	fConst22 = (1.2098025545241399e-25 * fConst0);
	fConst23 = (((((((fConst22 + 1.16174943639314e-22) * fConst0) + -1.28066027071487e-19) * fConst0) + -2.8258552146580698e-17) * fConst0) + 1.10713318228592e-15);
	fConst24 = (1.2100527621335e-25 * fConst0);
	fConst25 = (((((((-9.11915819145532e-23 - fConst24) * fConst0) + 9.0695259016404796e-20) * fConst0) + 1.95328951415802e-17) * fConst0) + -7.6115430068204999e-16);
	fConst26 = (((((((3.3070186876704002e-22 - fConst14) * fConst0) + 4.3337145586708598e-19) * fConst0) + -1.5121167247792399e-16) * fConst0) + -1.8312895245343901e-14);
	fConst27 = (((((((7.2237910600421603e-20 - fConst16) * fConst0) + 8.2021394230896999e-17) * fConst0) + -1.5716781700368701e-14) * fConst0) + -5.8973731974332299e-13);
	fConst28 = (((((2.51298002009256e-20 - fConst18) * fConst0) + 2.33854224109594e-17) * fConst0) + -1.10713318228592e-15);
	fConst29 = (((((fConst20 + -1.94557383639582e-20) * fConst0) + -1.6182141680792199e-17) * fConst0) + 7.6115430068204999e-16);
	fConst30 = (((((((1.16174943639314e-22 - fConst22) * fConst0) + 1.28066027071487e-19) * fConst0) + -2.8258552146580698e-17) * fConst0) + -1.10713318228592e-15);
	fConst31 = (((((((fConst24 + -9.11915819145532e-23) * fConst0) + -9.0695259016404796e-20) * fConst0) + 1.95328951415802e-17) * fConst0) + 7.6115430068204999e-16);
	fConst32 = (((((((fConst2 + -4.9605280315055998e-22) * fConst0) + 2.1668572793354299e-19) * fConst0) + 7.5605836238962106e-17) * fConst0) + -2.74693428680159e-14);
	fConst33 = (((((((fConst4 + -1.08356865900632e-19) * fConst0) + 4.1010697115448499e-17) * fConst0) + 7.8583908501843601e-15) * fConst0) + -8.8460597961498503e-13);
	fConst34 = (((((fConst6 + -3.7694700301388401e-20) * fConst0) + 1.16927112054797e-17) * fConst0) + 5.5356659114295903e-16);
	fConst35 = (((((2.91836075459373e-20 - fConst8) * fConst0) + -8.0910708403960997e-18) * fConst0) + -3.80577150341025e-16);
	fConst36 = (((((((fConst10 + -1.7426241545897101e-22) * fConst0) + 6.4033013535743402e-20) * fConst0) + 1.4129276073290401e-17) * fConst0) + -1.66069977342888e-15);
	fConst37 = (((((((1.3678737287183e-22 - fConst12) * fConst0) + -4.5347629508202398e-20) * fConst0) + -9.7664475707901002e-18) * fConst0) + 1.1417314510230801e-15);
	fConst38 = (2.7509387752067898e-26 * fConst0);
	fConst39 = (((((((1.6535093438352001e-22 - fConst38) * fConst0) + -2.1668572793354299e-19) * fConst0) + 7.5605836238962106e-17) * fConst0) + -9.1564476226719693e-15);
	fConst40 = (6.24148183382948e-24 * fConst0);
	fConst41 = (((((((3.6118955300210801e-20 - fConst40) * fConst0) + -4.1010697115448499e-17) * fConst0) + 7.8583908501843601e-15) * fConst0) + -2.94868659871662e-13);
	fConst42 = (2.7462489610529699e-24 * fConst0);
	fConst43 = (((((1.25649001004628e-20 - fConst42) * fConst0) + -1.16927112054797e-17) * fConst0) + 5.5356659114295903e-16);
	fConst44 = (2.7462502093447701e-24 * fConst0);
	fConst45 = (((((fConst44 + -9.7278691819791104e-21) * fConst0) + 8.0910708403960997e-18) * fConst0) + -3.80577150341025e-16);
	fConst46 = (1.20980255452414e-26 * fConst0);
	fConst47 = (((((((5.8087471819657105e-23 - fConst46) * fConst0) + -6.4033013535743402e-20) * fConst0) + 1.4129276073290401e-17) * fConst0) + -5.5356659114295903e-16);
	fConst48 = (1.2100527621335001e-26 * fConst0);
	fConst49 = (((((((fConst48 + -4.55957909572766e-23) * fConst0) + 4.5347629508202398e-20) * fConst0) + -9.7664475707901002e-18) * fConst0) + 3.80577150341025e-16);
	fConst50 = (((((((fConst38 + 1.6535093438352001e-22) * fConst0) + 2.1668572793354299e-19) * fConst0) + 7.5605836238962106e-17) * fConst0) + 9.1564476226719693e-15);
	fConst51 = (((((((fConst40 + 3.6118955300210801e-20) * fConst0) + 4.1010697115448499e-17) * fConst0) + 7.8583908501843601e-15) * fConst0) + 2.94868659871662e-13);
	fConst52 = (((((fConst42 + 1.25649001004628e-20) * fConst0) + 1.16927112054797e-17) * fConst0) + 5.5356659114295903e-16);
	fConst53 = (((((-9.7278691819791104e-21 - fConst44) * fConst0) + -8.0910708403960997e-18) * fConst0) + -3.80577150341025e-16);
	fConst54 = (((((((fConst46 + 5.8087471819657105e-23) * fConst0) + 6.4033013535743402e-20) * fConst0) + 1.4129276073290401e-17) * fConst0) + 5.5356659114295903e-16);
	fConst55 = (((((((-4.55957909572766e-23 - fConst48) * fConst0) + -4.5347629508202398e-20) * fConst0) + -9.7664475707901002e-18) * fConst0) + -3.80577150341025e-16);
	fConst56 = (3.7531141403921202e-24 * fConst0);
	fConst57 = (((((fConst56 + 2.0863013824789001e-20) * fConst0) + 1.9869155141114799e-17) * fConst0) + 9.9075770641107705e-18);
	fConst58 = (1.8724377072401299e-24 * fConst0);
	fConst59 = (((fConst58 + 1.04076738111564e-20) * fConst0) + 9.9075770641107705e-18);
	fConst60 = (((6.2276198688696203e-21 - fConst58) * fConst0) + 3.1904884396930002e-34);
	fConst61 = (((((1.33318768762005e-20 - fConst56) * fConst0) + 1.0441642646804701e-18) * fConst0) + 3.1904884396930002e-34);
	fConst62 = (1.8765570701960601e-23 * fConst0);
	fConst63 = (((((-6.2589041474367097e-20 - fConst62) * fConst0) + -1.9869155141114799e-17) * fConst0) + 9.9075770641107705e-18);
	fConst64 = (9.3621885362006607e-24 * fConst0);
	fConst65 = (((-3.1223021433469098e-20 - fConst64) * fConst0) + -9.9075770641107705e-18);
	fConst66 = (((fConst64 + -1.8682859606608799e-20) * fConst0) + -3.1904884396930002e-34);
	fConst67 = (((((fConst62 + -3.9995630628601597e-20) * fConst0) + -1.0441642646804701e-18) * fConst0) + 3.1904884396930002e-34);
	fConst68 = (3.7531141403921202e-23 * fConst0);
	fConst69 = (((((fConst68 + 4.1726027649578099e-20) * fConst0) + -3.9738310282229597e-17) * fConst0) + -1.9815154128221501e-17);
	fConst70 = (1.8724377072401301e-23 * fConst0);
	fConst71 = (((fConst70 + 2.08153476223127e-20) * fConst0) + -1.9815154128221501e-17);
	fConst72 = (((1.24552397377392e-20 - fConst70) * fConst0) + -6.3809768793860098e-34);
	fConst73 = (((((2.66637537524011e-20 - fConst68) * fConst0) + -2.0883285293609501e-18) * fConst0) + -6.3809768793860098e-34);
	fConst74 = (((((4.1726027649578099e-20 - fConst68) * fConst0) + 3.9738310282229597e-17) * fConst0) + -1.9815154128221501e-17);
	fConst75 = (((2.08153476223127e-20 - fConst70) * fConst0) + 1.9815154128221501e-17);
	fConst76 = (((fConst70 + 1.24552397377392e-20) * fConst0) + 6.3809768793860098e-34);
	fConst77 = (((((fConst68 + 2.66637537524011e-20) * fConst0) + 2.0883285293609501e-18) * fConst0) + -6.3809768793860098e-34);
	fConst78 = (((((fConst62 + -6.2589041474367097e-20) * fConst0) + 1.9869155141114799e-17) * fConst0) + 9.9075770641107705e-18);
	fConst79 = (((fConst64 + -3.1223021433469098e-20) * fConst0) + 9.9075770641107705e-18);
	fConst80 = (((-1.8682859606608799e-20 - fConst64) * fConst0) + 3.1904884396930002e-34);
	fConst81 = (((((-3.9995630628601597e-20 - fConst62) * fConst0) + 1.0441642646804701e-18) * fConst0) + 3.1904884396930002e-34);
	fConst82 = (((((2.0863013824789001e-20 - fConst56) * fConst0) + -1.9869155141114799e-17) * fConst0) + 9.9075770641107705e-18);
	fConst83 = (((1.04076738111564e-20 - fConst58) * fConst0) + -9.9075770641107705e-18);
	fConst84 = (((fConst58 + 6.2276198688696203e-21) * fConst0) + -3.1904884396930002e-34);
	fConst85 = (((((fConst56 + 1.33318768762005e-20) * fConst0) + -1.0441642646804701e-18) * fConst0) + 3.1904884396930002e-34);
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
		double fTemp0 = ((fConst0 * (fConst50 + ((fRec2[0] * (fConst51 + (fConst0 * (fRec3[0] * (fConst52 + (fConst53 * fRec3[0])))))) + (fRec3[0] * (fConst54 + (fConst55 * fRec3[0])))))) + 2.94868659871662e-13);
		fRec1[0] = (double(input0[i]) - ((((((fRec1[1] * ((fConst0 * (fConst3 + ((fRec2[0] * (fConst5 + (fConst0 * (fRec3[0] * (fConst7 + (fConst9 * fRec3[0])))))) + (fRec3[0] * (fConst11 + (fConst13 * fRec3[0])))))) + 1.47434329935831e-12)) + (fRec1[2] * ((fConst0 * (fConst15 + ((fRec2[0] * (fConst17 + (fConst0 * (fRec3[0] * (fConst19 + (fConst21 * fRec3[0])))))) + (fRec3[0] * (fConst23 + (fConst25 * fRec3[0])))))) + 2.9486865987166201e-12))) + (fRec1[3] * ((fConst0 * (fConst26 + ((fRec2[0] * (fConst27 + (fConst0 * (fRec3[0] * (fConst28 + (fConst29 * fRec3[0])))))) + (fRec3[0] * (fConst30 + (fConst31 * fRec3[0])))))) + 2.9486865987166201e-12))) + (fRec1[4] * ((fConst0 * (fConst32 + ((fRec2[0] * (fConst33 + (fConst0 * (fRec3[0] * (fConst34 + (fConst35 * fRec3[0])))))) + (fRec3[0] * (fConst36 + (fConst37 * fRec3[0])))))) + 1.47434329935831e-12))) + (fRec1[5] * ((fConst0 * (fConst39 + ((fRec2[0] * (fConst41 + (fConst0 * (fRec3[0] * (fConst43 + (fConst45 * fRec3[0])))))) + (fRec3[0] * (fConst47 + (fConst49 * fRec3[0])))))) + 2.94868659871662e-13))) / fTemp0));
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
