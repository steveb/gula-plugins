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
	fConst2 = (1.38895690673003e-25 * fConst0);
	fConst3 = (((((((-4.6278585366917597e-22 - fConst2) * fConst0) + -1.5794130323098001e-19) * fConst0) + 5.0470182457096803e-17) * fConst0) + 1.7604533034337702e-14);
	fConst4 = (3.1499984683358298e-23 * fConst0);
	fConst5 = (((((((-1.0072943939025e-19 - fConst4) * fConst0) + -2.8236045880922003e-17) * fConst0) + 5.0490612832169501e-15) * fConst0) + 5.5806190335684598e-13);
	fConst6 = (1.38599692420801e-23 * fConst0);
	fConst7 = (((((-3.4245041450573099e-20 - fConst6) * fConst0) + -7.5482720507550702e-18) * fConst0) + 3.4922256722666099e-16);
	fConst8 = (1.3859979085767601e-23 * fConst0);
	fConst9 = (((((fConst8 + 2.5654163543238501e-20) * fConst0) + 5.2224520468393397e-18) * fConst0) + -2.4009063219974599e-16);
	fConst10 = (6.1065961019148196e-26 * fConst0);
	fConst11 = (((((((-1.59184450269569e-22 - fConst10) * fConst0) + -4.4647729488082803e-20) * fConst0) + 9.0857107594048705e-18) * fConst0) + 1.04766770167998e-15);
	fConst12 = (6.10856917064323e-26 * fConst0);
	fConst13 = (((((((fConst12 + 1.2135794470977901e-22) * fConst0) + 3.1549359439799899e-20) * fConst0) + -6.2796761376860898e-18) * fConst0) + -7.2027189659923703e-16);
	fConst14 = (2.77791381346006e-25 * fConst0);
	fConst15 = (((((((fConst14 + 3.0852390244611798e-22) * fConst0) + -3.1588260646195901e-19) * fConst0) + -1.00940364914194e-16) * fConst0) + 1.1736355356225101e-14);
	fConst16 = (6.2999969366716502e-23 * fConst0);
	fConst17 = (((((((fConst16 + 6.7152959593499901e-20) * fConst0) + -5.6472091761844105e-17) * fConst0) + -1.00981225664339e-14) * fConst0) + 3.72041268904564e-13);
	fConst18 = (2.77199384841601e-23 * fConst0);
	fConst19 = (((((fConst18 + 2.2830027633715401e-20) * fConst0) + -1.50965441015101e-17) * fConst0) + -6.9844513445332198e-16);
	fConst20 = (2.7719958171535202e-23 * fConst0);
	fConst21 = (((((-1.71027756954923e-20 - fConst20) * fConst0) + 1.0444904093678699e-17) * fConst0) + 4.8018126439949099e-16);
	fConst22 = (1.22131922038296e-25 * fConst0);
	fConst23 = (((((((fConst22 + 1.06122966846379e-22) * fConst0) + -8.9295458976165702e-20) * fConst0) + -1.8171421518809701e-17) * fConst0) + 6.9844513445332198e-16);
	fConst24 = (1.2217138341286499e-25 * fConst0);
	fConst25 = (((((((-8.0905296473186097e-23 - fConst24) * fConst0) + 6.3098718879599894e-20) * fConst0) + 1.25593522753722e-17) * fConst0) + -4.8018126439949099e-16);
	fConst26 = (((((((3.0852390244611798e-22 - fConst14) * fConst0) + 3.1588260646195901e-19) * fConst0) + -1.00940364914194e-16) * fConst0) + -1.1736355356225101e-14);
	fConst27 = (((((((6.7152959593499901e-20 - fConst16) * fConst0) + 5.6472091761844105e-17) * fConst0) + -1.00981225664339e-14) * fConst0) + -3.72041268904564e-13);
	fConst28 = (((((2.2830027633715401e-20 - fConst18) * fConst0) + 1.50965441015101e-17) * fConst0) + -6.9844513445332198e-16);
	fConst29 = (((((fConst20 + -1.71027756954923e-20) * fConst0) + -1.0444904093678699e-17) * fConst0) + 4.8018126439949099e-16);
	fConst30 = (((((((1.06122966846379e-22 - fConst22) * fConst0) + 8.9295458976165702e-20) * fConst0) + -1.8171421518809701e-17) * fConst0) + -6.9844513445332198e-16);
	fConst31 = (((((((fConst24 + -8.0905296473186097e-23) * fConst0) + -6.3098718879599894e-20) * fConst0) + 1.25593522753722e-17) * fConst0) + 4.8018126439949099e-16);
	fConst32 = (((((((fConst2 + -4.6278585366917597e-22) * fConst0) + 1.5794130323098001e-19) * fConst0) + 5.0470182457096803e-17) * fConst0) + -1.7604533034337702e-14);
	fConst33 = (((((((fConst4 + -1.0072943939025e-19) * fConst0) + 2.8236045880922003e-17) * fConst0) + 5.0490612832169501e-15) * fConst0) + -5.5806190335684598e-13);
	fConst34 = (((((fConst6 + -3.4245041450573099e-20) * fConst0) + 7.5482720507550702e-18) * fConst0) + 3.4922256722666099e-16);
	fConst35 = (((((2.5654163543238501e-20 - fConst8) * fConst0) + -5.2224520468393397e-18) * fConst0) + -2.4009063219974599e-16);
	fConst36 = (((((((fConst10 + -1.59184450269569e-22) * fConst0) + 4.4647729488082803e-20) * fConst0) + 9.0857107594048705e-18) * fConst0) + -1.04766770167998e-15);
	fConst37 = (((((((1.2135794470977901e-22 - fConst12) * fConst0) + -3.1549359439799899e-20) * fConst0) + -6.2796761376860898e-18) * fConst0) + 7.2027189659923703e-16);
	fConst38 = (2.7779138134600601e-26 * fConst0);
	fConst39 = (((((((1.5426195122305899e-22 - fConst38) * fConst0) + -1.5794130323098001e-19) * fConst0) + 5.0470182457096803e-17) * fConst0) + -5.8681776781125701e-15);
	fConst40 = (6.2999969366716501e-24 * fConst0);
	fConst41 = (((((((3.3576479796749902e-20 - fConst40) * fConst0) + -2.8236045880922003e-17) * fConst0) + 5.0490612832169501e-15) * fConst0) + -1.86020634452282e-13);
	fConst42 = (2.77199384841601e-24 * fConst0);
	fConst43 = (((((1.1415013816857701e-20 - fConst42) * fConst0) + -7.5482720507550702e-18) * fConst0) + 3.4922256722666099e-16);
	fConst44 = (2.77199581715352e-24 * fConst0);
	fConst45 = (((((fConst44 + -8.5513878477461693e-21) * fConst0) + 5.2224520468393397e-18) * fConst0) + -2.4009063219974599e-16);
	fConst46 = (1.2213192203829599e-26 * fConst0);
	fConst47 = (((((((5.3061483423189702e-23 - fConst46) * fConst0) + -4.4647729488082803e-20) * fConst0) + 9.0857107594048705e-18) * fConst0) + -3.4922256722666099e-16);
	fConst48 = (1.2217138341286501e-26 * fConst0);
	fConst49 = (((((((fConst48 + -4.0452648236593101e-23) * fConst0) + 3.1549359439799899e-20) * fConst0) + -6.2796761376860898e-18) * fConst0) + 2.4009063219974599e-16);
	fConst50 = (((((((fConst38 + 1.5426195122305899e-22) * fConst0) + 1.5794130323098001e-19) * fConst0) + 5.0470182457096803e-17) * fConst0) + 5.8681776781125701e-15);
	fConst51 = (((((((fConst40 + 3.3576479796749902e-20) * fConst0) + 2.8236045880922003e-17) * fConst0) + 5.0490612832169501e-15) * fConst0) + 1.86020634452282e-13);
	fConst52 = (((((fConst42 + 1.1415013816857701e-20) * fConst0) + 7.5482720507550702e-18) * fConst0) + 3.4922256722666099e-16);
	fConst53 = (((((-8.5513878477461693e-21 - fConst44) * fConst0) + -5.2224520468393397e-18) * fConst0) + -2.4009063219974599e-16);
	fConst54 = (((((((fConst46 + 5.3061483423189702e-23) * fConst0) + 4.4647729488082803e-20) * fConst0) + 9.0857107594048705e-18) * fConst0) + 3.4922256722666099e-16);
	fConst55 = (((((((-4.0452648236593101e-23 - fConst48) * fConst0) + -3.1549359439799899e-20) * fConst0) + -6.2796761376860898e-18) * fConst0) + -2.4009063219974599e-16);
	fConst56 = (3.7882969653559799e-24 * fConst0);
	fConst57 = (((((fConst56 + 1.9326137134131801e-20) * fConst0) + 1.25377092642718e-17) * fConst0) + 6.2502835515415401e-18);
	fConst58 = (1.88999050357013e-24 * fConst0);
	fConst59 = (((fConst58 + 9.6409135619777794e-21) * fConst0) + 6.2502835515415401e-18);
	fConst60 = (((3.9287496609689597e-21 - fConst58) * fConst0) + 2.01274815093113e-34);
	fConst61 = (((((8.7319824224744893e-21 - fConst56) * fConst0) + 6.5872035982246302e-19) * fConst0) + 2.01274815093113e-34);
	fConst62 = (1.8941484826779899e-23 * fConst0);
	fConst63 = (((((-5.7978411402395503e-20 - fConst62) * fConst0) + -1.25377092642718e-17) * fConst0) + 6.2502835515415401e-18);
	fConst64 = (9.4499525178506701e-24 * fConst0);
	fConst65 = (((-2.8922740685933298e-20 - fConst64) * fConst0) + -6.2502835515415401e-18);
	fConst66 = (((fConst64 + -1.17862489829069e-20) * fConst0) + -2.01274815093113e-34);
	fConst67 = (((((fConst62 + -2.6195947267423501e-20) * fConst0) + -6.5872035982246302e-19) * fConst0) + 2.01274815093113e-34);
	fConst68 = (3.7882969653559797e-23 * fConst0);
	fConst69 = (((((fConst68 + 3.8652274268263699e-20) * fConst0) + -2.5075418528543699e-17) * fConst0) + -1.25005671030831e-17);
	fConst70 = (1.8899905035701299e-23 * fConst0);
	fConst71 = (((fConst70 + 1.9281827123955601e-20) * fConst0) + -1.25005671030831e-17);
	fConst72 = (((7.8574993219379194e-21 - fConst70) * fConst0) + -4.0254963018622599e-34);
	fConst73 = (((((1.7463964844949e-20 - fConst68) * fConst0) + -1.3174407196449301e-18) * fConst0) + -4.0254963018622599e-34);
	fConst74 = (((((3.8652274268263699e-20 - fConst68) * fConst0) + 2.5075418528543699e-17) * fConst0) + -1.25005671030831e-17);
	fConst75 = (((1.9281827123955601e-20 - fConst70) * fConst0) + 1.25005671030831e-17);
	fConst76 = (((fConst70 + 7.8574993219379194e-21) * fConst0) + 4.0254963018622599e-34);
	fConst77 = (((((fConst68 + 1.7463964844949e-20) * fConst0) + 1.3174407196449301e-18) * fConst0) + -4.0254963018622599e-34);
	fConst78 = (((((fConst62 + -5.7978411402395503e-20) * fConst0) + 1.25377092642718e-17) * fConst0) + 6.2502835515415401e-18);
	fConst79 = (((fConst64 + -2.8922740685933298e-20) * fConst0) + 6.2502835515415401e-18);
	fConst80 = (((-1.17862489829069e-20 - fConst64) * fConst0) + 2.01274815093113e-34);
	fConst81 = (((((-2.6195947267423501e-20 - fConst62) * fConst0) + 6.5872035982246302e-19) * fConst0) + 2.01274815093113e-34);
	fConst82 = (((((1.9326137134131801e-20 - fConst56) * fConst0) + -1.25377092642718e-17) * fConst0) + 6.2502835515415401e-18);
	fConst83 = (((9.6409135619777794e-21 - fConst58) * fConst0) + -6.2502835515415401e-18);
	fConst84 = (((fConst58 + 3.9287496609689597e-21) * fConst0) + -2.01274815093113e-34);
	fConst85 = (((((fConst56 + 8.7319824224744893e-21) * fConst0) + -6.5872035982246302e-19) * fConst0) + 2.01274815093113e-34);
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
		double fTemp0 = ((fConst0 * (fConst50 + ((fRec2[0] * (fConst51 + (fConst0 * (fRec3[0] * (fConst52 + (fConst53 * fRec3[0])))))) + (fRec3[0] * (fConst54 + (fConst55 * fRec3[0])))))) + 1.86020634452282e-13);
		fRec1[0] = (double(input0[i]) - ((((((fRec1[1] * ((fConst0 * (fConst3 + ((fRec2[0] * (fConst5 + (fConst0 * (fRec3[0] * (fConst7 + (fConst9 * fRec3[0])))))) + (fRec3[0] * (fConst11 + (fConst13 * fRec3[0])))))) + 9.3010317226141003e-13)) + (fRec1[2] * ((fConst0 * (fConst15 + ((fRec2[0] * (fConst17 + (fConst0 * (fRec3[0] * (fConst19 + (fConst21 * fRec3[0])))))) + (fRec3[0] * (fConst23 + (fConst25 * fRec3[0])))))) + 1.8602063445228201e-12))) + (fRec1[3] * ((fConst0 * (fConst26 + ((fRec2[0] * (fConst27 + (fConst0 * (fRec3[0] * (fConst28 + (fConst29 * fRec3[0])))))) + (fRec3[0] * (fConst30 + (fConst31 * fRec3[0])))))) + 1.8602063445228201e-12))) + (fRec1[4] * ((fConst0 * (fConst32 + ((fRec2[0] * (fConst33 + (fConst0 * (fRec3[0] * (fConst34 + (fConst35 * fRec3[0])))))) + (fRec3[0] * (fConst36 + (fConst37 * fRec3[0])))))) + 9.3010317226141003e-13))) + (fRec1[5] * ((fConst0 * (fConst39 + ((fRec2[0] * (fConst41 + (fConst0 * (fRec3[0] * (fConst43 + (fConst45 * fRec3[0])))))) + (fRec3[0] * (fConst47 + (fConst49 * fRec3[0])))))) + 1.86020634452282e-13))) / fTemp0));
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
