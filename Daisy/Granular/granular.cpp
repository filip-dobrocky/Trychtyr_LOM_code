#include "granular.h"

namespace granular {

/****************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER 200k USD in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below 200k USD annual revenue or funding.

For entities with OVER 200k USD in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing (at) cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/360050779193-Gen-Code-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
****************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Data m_loop_wav_6;
	Data m_info_1;
	Delta __m_delta_8;
	Phasor __m_phasor_7;
	Phasor __m_phasor_9;
	Phasor __m_phasor_46;
	int __loopcount;
	int __exception;
	int vectorsize;
	t_sample m_midi_cc_4;
	t_sample __m_count_10;
	t_sample __m_carry_12;
	t_sample m_midi_cc_5;
	t_sample samplerate;
	t_sample m_midi_cc_3;
	t_sample m_midi_cc_2;
	t_sample samples_to_seconds;
	t_sample __m_slide_47;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_info_1.reset("info", ((int)30), ((int)5));
		m_midi_cc_2 = 0.1;
		m_midi_cc_3 = 0.5;
		m_midi_cc_4 = 0.5;
		m_midi_cc_5 = 0;
		m_loop_wav_6.reset("loop_wav", ((int)1660996), ((int)2));
		samples_to_seconds = (1 / samplerate);
		__m_phasor_7.reset(0);
		__m_delta_8.reset(0);
		__m_phasor_9.reset(0);
		__m_count_10 = 0;
		__m_carry_12 = 0;
		__m_phasor_46.reset(0);
		__m_slide_47 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		samples_to_seconds = (1 / samplerate);
		t_sample orange_5422 = (m_midi_cc_2 - m_midi_cc_5);
		__loopcount = (__n * GENLIB_LOOPCOUNT_BAIL);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sub_5411 = (m_midi_cc_4 - ((int)0));
			t_sample scale_5408 = ((safepow((sub_5411 * ((t_sample)1)), ((int)1)) * ((t_sample)39.9)) + ((t_sample)0.1));
			t_sample sub_5415 = (m_midi_cc_3 - ((int)0));
			t_sample scale_5412 = ((safepow((sub_5415 * ((t_sample)1)), ((int)1)) * ((int)100)) + (-50));
			t_sample mul_3620 = (scale_5412 * (-1));
			t_sample sub_5419 = (m_midi_cc_4 - ((int)0));
			t_sample scale_5416 = ((safepow((sub_5419 * ((t_sample)1)), ((int)1)) * ((t_sample)0.219)) + ((t_sample)0.001));
			if ((((int)0) != 0)) {
				__m_phasor_7.phase = 0;
				
			};
			t_sample phasor_3621 = __m_phasor_7(scale_5416, samples_to_seconds);
			t_sample sub_5423 = (phasor_3621 - ((int)0));
			t_sample scale_5420 = ((safepow((sub_5423 * ((t_sample)1)), ((int)1)) * orange_5422) + m_midi_cc_5);
			t_sample rsub_3604 = (((int)1) - m_midi_cc_4);
			t_sample mul_3864 = (rsub_3604 * ((int)100));
			t_sample add_4050 = (mul_3864 + ((int)100));
			t_sample orange_5426 = (add_4050 - mul_3864);
			t_sample sub_5427 = (m_midi_cc_3 - ((int)0));
			t_sample scale_5424 = ((safepow((sub_5427 * ((t_sample)1)), ((int)1)) * orange_5426) + mul_3864);
			if ((((int)0) != 0)) {
				__m_phasor_9.phase = 0;
				
			};
			int p = (__m_delta_8(__m_phasor_9(scale_5408, samples_to_seconds)) < ((int)0));
			__m_count_10 = (((int)0) ? 0 : (fixdenorm(__m_count_10 + p)));
			int carry_11 = 0;
			if ((((int)0) != 0)) {
				__m_count_10 = 0;
				__m_carry_12 = 0;
				
			} else if (((((int)10) > 0) && (__m_count_10 >= ((int)10)))) {
				int wraps_13 = (__m_count_10 / ((int)10));
				__m_carry_12 = (__m_carry_12 + wraps_13);
				__m_count_10 = (__m_count_10 - (wraps_13 * ((int)10)));
				carry_11 = 1;
				
			};
			int c = __m_count_10;
			t_sample sum = ((int)0);
			// for loop initializer;
			int i = ((int)0);
			// for loop condition;
			// abort processing if an infinite loop is suspected;
			if (((__loopcount--) <= 0)) {
				__exception = GENLIB_ERR_LOOP_OVERFLOW;
				break ;
				
			};
			while ((i < ((int)10))) {
				// abort processing if an infinite loop is suspected;
				if (((__loopcount--) <= 0)) {
					__exception = GENLIB_ERR_LOOP_OVERFLOW;
					break ;
					
				};
				int trigger = get_trigger_i_i_dat(c, i, m_info_1);
				t_sample count = get_count_dat_i_i(m_info_1, i, trigger);
				t_sample sz = (scale_5424 * (samplerate * 0.001));
				t_sample sz_5303 = latchy_i_d_dat_i_i(trigger, sz, m_info_1, i, ((int)2));
				t_sample minb_29 = safediv(count, sz_5303);
				t_sample phase = ((minb_29 < ((int)1)) ? minb_29 : ((int)1));
				t_sample amp = (((t_sample)0.5) - (((t_sample)0.5) * cos((phase * ((t_sample)6.2831853071796)))));
				t_sample sprd = (noise() * ((int)12));
				t_sample pitch_hz = safepow(((int)2), ((mul_3620 + sprd) * ((t_sample)0.083333333333333)));
				t_sample pitch_hz_5304 = latchy_i_d_dat_i_i(trigger, pitch_hz, m_info_1, i, ((int)3));
				t_sample spry = (noise() * ((t_sample)0.5));
				int loop_wav_dim = m_loop_wav_6.dim;
				int loop_wav_channels = m_loop_wav_6.channels;
				t_sample start_pos = ((scale_5420 + spry) * loop_wav_dim);
				t_sample start_pos_5305 = latchy_i_d_dat_i_i(trigger, start_pos, m_info_1, i, ((int)4));
				t_sample playhead = (start_pos_5305 + (count * pitch_hz_5304));
				int index_trunc_30 = fixnan(floor(playhead));
				double index_fract_31 = (playhead - index_trunc_30);
				int index_trunc_32 = (index_trunc_30 - 1);
				int index_trunc_33 = (index_trunc_30 + 1);
				int index_trunc_34 = (index_trunc_30 + 2);
				int index_wrap_35 = ((index_trunc_32 < 0) ? ((loop_wav_dim - 1) + ((index_trunc_32 + 1) % loop_wav_dim)) : (index_trunc_32 % loop_wav_dim));
				int index_wrap_36 = ((index_trunc_30 < 0) ? ((loop_wav_dim - 1) + ((index_trunc_30 + 1) % loop_wav_dim)) : (index_trunc_30 % loop_wav_dim));
				int index_wrap_37 = ((index_trunc_33 < 0) ? ((loop_wav_dim - 1) + ((index_trunc_33 + 1) % loop_wav_dim)) : (index_trunc_33 % loop_wav_dim));
				int index_wrap_38 = ((index_trunc_34 < 0) ? ((loop_wav_dim - 1) + ((index_trunc_34 + 1) % loop_wav_dim)) : (index_trunc_34 % loop_wav_dim));
				// samples loop_wav channel 1;
				int chan_39 = ((int)0);
				bool chan_ignore_40 = ((chan_39 < 0) || (chan_39 >= loop_wav_channels));
				double read_loop_wav_41 = (chan_ignore_40 ? 0 : m_loop_wav_6.read(index_wrap_35, chan_39));
				double read_loop_wav_42 = (chan_ignore_40 ? 0 : m_loop_wav_6.read(index_wrap_36, chan_39));
				double read_loop_wav_43 = (chan_ignore_40 ? 0 : m_loop_wav_6.read(index_wrap_37, chan_39));
				double read_loop_wav_44 = (chan_ignore_40 ? 0 : m_loop_wav_6.read(index_wrap_38, chan_39));
				double readinterp_45 = cubic_interp(index_fract_31, read_loop_wav_41, read_loop_wav_42, read_loop_wav_43, read_loop_wav_44);
				t_sample smp = readinterp_45;
				t_sample grain = (amp * smp);
				sum = (sum + grain);
				// for loop increment;
				i = (i + ((int)1));
				
			};
			t_sample out1 = sum;
			if ((((int)0) != 0)) {
				__m_phasor_46.phase = 0;
				
			};
			t_sample phasor_3619 = __m_phasor_46(scale_5408, samples_to_seconds);
			t_sample pow_3618 = safepow(phasor_3619, ((int)2));
			t_sample rsub_3617 = (((int)1) - pow_3618);
			t_sample out3 = rsub_3617;
			t_sample mul_3607 = (sum * ((int)10));
			t_sample mstosamps_3615 = (((int)10) * (samplerate * 0.001));
			t_sample mstosamps_3614 = (((int)300) * (samplerate * 0.001));
			t_sample iup_48 = (1 / maximum(1, abs(mstosamps_3615)));
			t_sample idown_49 = (1 / maximum(1, abs(mstosamps_3614)));
			__m_slide_47 = fixdenorm((__m_slide_47 + (((mul_3607 > __m_slide_47) ? iup_48 : idown_49) * (mul_3607 - __m_slide_47))));
			t_sample slide_3616 = __m_slide_47;
			t_sample rsub_3606 = (((int)1) - slide_3616);
			t_sample out2 = rsub_3606;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			
		};
		return __exception;
		
	};
	inline void set_info(void * _value) {
		m_info_1.setbuffer(_value);
	};
	inline void set_midi_cc3(t_param _value) {
		m_midi_cc_2 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_midi_cc1(t_param _value) {
		m_midi_cc_3 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_midi_cc4(t_param _value) {
		m_midi_cc_4 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_midi_cc2(t_param _value) {
		m_midi_cc_5 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_loop_wav(void * _value) {
		m_loop_wav_6.setbuffer(_value);
	};
	inline int get_trigger_i_i_dat(int _count, int _instance, Data& _dat) {
		int current = (_count == _instance);
		int _dat_dim = _dat.dim;
		int _dat_channels = _dat.channels;
		bool index_ignore_14 = ((_instance >= _dat_dim) || (_instance < 0));
		// samples _dat channel 1;
		int chan_15 = ((int)0);
		bool chan_ignore_16 = ((chan_15 < 0) || (chan_15 >= _dat_channels));
		t_sample previous = ((chan_ignore_16 || index_ignore_14) ? 0 : _dat.read(_instance, chan_15));
		bool index_ignore_17 = ((_instance >= _dat_dim) || (_instance < 0));
		if ((!index_ignore_17)) {
			_dat.write(current, _instance, 0);
			
		};
		return ((current - previous) == ((int)1));
		
	};
	inline t_sample get_count_dat_i_i(Data& _dat, int _instance, int _trig) {
		int _dat_dim = _dat.dim;
		int _dat_channels = _dat.channels;
		bool index_ignore_18 = ((_instance >= _dat_dim) || (_instance < 0));
		// samples _dat channel 1;
		int chan_19 = ((int)1);
		bool chan_ignore_20 = ((chan_19 < 0) || (chan_19 >= _dat_channels));
		t_sample count = ((chan_ignore_20 || index_ignore_18) ? 0 : _dat.read(_instance, chan_19));
		t_sample iffalse_21 = (count + ((int)1));
		t_sample count_5302 = (_trig ? ((int)0) : iffalse_21);
		bool chan_ignore_22 = ((((int)1) < 0) || (((int)1) >= _dat_channels));
		bool index_ignore_23 = ((_instance >= _dat_dim) || (_instance < 0));
		if ((!(chan_ignore_22 || index_ignore_23))) {
			_dat.write(count_5302, _instance, ((int)1));
			
		};
		return count_5302;
		
	};
	inline t_sample latchy_i_d_dat_i_i(int _trigger, t_sample _val, Data& _dat, int _instance, int _channel) {
		t_sample val = _val;
		if (_trigger) {
			int _dat_dim = _dat.dim;
			int _dat_channels = _dat.channels;
			bool chan_ignore_24 = ((_channel < 0) || (_channel >= _dat_channels));
			bool index_ignore_25 = ((_instance >= _dat_dim) || (_instance < 0));
			if ((!(chan_ignore_24 || index_ignore_25))) {
				_dat.write(val, _instance, _channel);
				
			};
			
		} else {
			int _dat_dim = _dat.dim;
			int _dat_channels = _dat.channels;
			bool index_ignore_26 = ((_instance >= _dat_dim) || (_instance < 0));
			// samples _dat channel 1;
			int chan_27 = _channel;
			bool chan_ignore_28 = ((chan_27 < 0) || (chan_27 >= _dat_channels));
			val = ((chan_ignore_28 || index_ignore_26) ? 0 : _dat.read(_instance, chan_27));
			
		};
		return val;
		
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 3;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 6; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "led", "laser" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_info(ref); break;
		case 1: self->set_loop_wav(ref); break;
		case 2: self->set_midi_cc1(value); break;
		case 3: self->set_midi_cc2(value); break;
		case 4: self->set_midi_cc3(value); break;
		case 5: self->set_midi_cc4(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		
		
		case 2: *value = self->m_midi_cc_3; break;
		case 3: *value = self->m_midi_cc_5; break;
		case 4: *value = self->m_midi_cc_2; break;
		case 5: *value = self->m_midi_cc_4; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(6 * sizeof(ParamInfo));
	self->__commonstate.numparams = 6;
	// initialize parameter 0 ("m_info_1")
	pi = self->__commonstate.params + 0;
	pi->name = "info";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_loop_wav_6")
	pi = self->__commonstate.params + 1;
	pi->name = "loop_wav";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_midi_cc_3")
	pi = self->__commonstate.params + 2;
	pi->name = "midi_cc1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_midi_cc_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_midi_cc_5")
	pi = self->__commonstate.params + 3;
	pi->name = "midi_cc2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_midi_cc_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_midi_cc_2")
	pi = self->__commonstate.params + 4;
	pi->name = "midi_cc3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_midi_cc_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_midi_cc_4")
	pi = self->__commonstate.params + 5;
	pi->name = "midi_cc4";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_midi_cc_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // granular::
